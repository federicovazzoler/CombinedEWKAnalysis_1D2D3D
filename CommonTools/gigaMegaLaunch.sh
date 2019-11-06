#bin/bash

WORKDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $WORKDIR

URL="https://wwwusers.ts.infn.it/~dellaric/tmp/Vgg/v13.default/"

BOSON=$1

if [ ! -z "$2" ]; then
  if [ "$2" == "all" ]; then
    PARS=""
    if [ $BOSON == "WGG" ]; then
      PARS=$PARS" FM0" 
      PARS=$PARS" FM1"
      PARS=$PARS" FM2"
      PARS=$PARS" FM3"
      PARS=$PARS" FM4"
      PARS=$PARS" FM5"
      PARS=$PARS" FM6"
      PARS=$PARS" FM7"
    fi
    PARS=$PARS" FT0"
    PARS=$PARS" FT1"
    PARS=$PARS" FT2"
    PARS=$PARS" FT5"
    PARS=$PARS" FT6"
    PARS=$PARS" FT7"
    if [ $BOSON == "ZGG" ]; then
      PARS=$PARS" FT8"
      PARS=$PARS" FT9"
    fi
  else
    PARS=$2
  fi
else
  echo 'Missing parameter(s) to test!'
  exit 1
fi

CHANNELS="ele muo"

echo '*********************************'
echo '*            '$BOSON' AGC            *'
echo '*********************************'
echo ''
echo 'FUNDAMENTAL! Fetching data from: '$URL
echo ''
wait 1
echo '              TAH!'
wait 1
echo ''
echo '---------------------------------'
echo '0. Prepare input cards           '
echo '---------------------------------'
echo ''
./scripts/card_generator.sh $WORKDIR $BOSON
echo ''
echo '---------------------------------'
echo '1. Prepare aGC signal input file '
echo '---------------------------------'
echo ''
if [ "$3" == fit ]; then
  ./scripts/launch_doFit.sh $WORKDIR $BOSON
  if [ $? -ne 0 ]; then
    echo '[ERROR]: launch_doFit.sh crashed'
    exit 1
  fi
else
  echo 'Fits skipped'
fi
echo ''
echo '---------------------------------'
echo '2. Prepare data and MC input file'
echo '---------------------------------'
echo ''
./scripts/launch_merge_histo.sh $WORKDIR $URL $BOSON
if [ $? -ne 0 ]; then
  echo '[ERROR]: launch_merge_histo crashed'
  exit 1
fi
echo ''
echo '---------------------------------'
echo '3. Build the workspace'
echo '---------------------------------'
echo ''
for PAR in $PARS; do
  cp -p data/$BOSON/ch_*.root data/$BOSON/$PAR/
  python python/buildWorkspace_AC.py --config="cards/config_${BOSON}_13TeV_buildWorkspace_$PAR" --path="$WORKDIR/data/$BOSON/$PAR"
  if [ $? -ne 0 ]; then
    echo '[ERROR]: builWorkspace_AC.py crashed'
    exit 1
  fi
  mv aC_ch_ele.txt aC_ch_muo.txt ch_ele_ws.root ch_muo_ws.root data/$BOSON/$PAR
done
echo ''
echo '---------------------------------'
echo '4. Convert combine card to ws'
echo '---------------------------------'
echo ''
for PAR in $PARS; do
  for CHANNEL in $CHANNELS; do
    cp -p data/$BOSON/$PAR/ch_${CHANNEL}_ws.root data/anomalousCoupling
    cp -p data/$BOSON/$PAR/ch_${CHANNEL}.root data/anomalousCoupling
    cp -p data/$BOSON/$PAR/signal_proc_ch_${CHANNEL}.root data/anomalousCoupling
    text2workspace.py -m 126 data/$BOSON/$PAR/aC_ch_${CHANNEL}.txt -o data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=ch_$CHANNEL --PO poi=$PAR --PO range_$PAR=-$(cat cards/range_${PAR}.txt),$(cat cards/range_${PAR}.txt)
    if [ $? -ne 0 ]; then
      echo '[ERROR]: text2workspace.py crashed'
      exit 1
    fi
  done
  combineCards.py data/$BOSON/$PAR/aC_ch_ele.txt data/$BOSON/$PAR/aC_ch_muo.txt > data/$BOSON/$PAR/aC_ch_lep.txt
  text2workspace.py -m 126 data/$BOSON/$PAR/aC_ch_lep.txt -o data/$BOSON/$PAR/${BOSON}_${PAR}_lep.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=ch_ele,ch_muo --PO poi=$PAR --PO range_$PAR=-$(cat cards/range_${PAR}.txt),$(cat cards/range_${PAR}.txt)
  rm -f data/anomalousCoupling/*
  rm -f data/$BOSON/$PAR/ch_ele.root data/$BOSON/$PAR/ch_muo.root
done
echo ''
echo '---------------------------------'
echo '5. Set limits                    '
echo '---------------------------------'
echo ''
CHANNELS="ele muo lep"
n_points=1000
for PAR in $PARS; do
  for CHANNEL in $CHANNELS; do
    cp -p data/$BOSON/$PAR/signal_proc_ch_${CHANNEL}.root data/anomalousCoupling
    # observed limits
    combine -v -1 data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}.root -M MultiDimFit -P $PAR --floatOtherPOIs=0 --algo=grid --points=$n_points --minimizerStrategy=2
    if [ $? -ne 0 ]; then
      echo '[ERROR]: combine crashed'
      exit 1
    fi
    mv higgsCombineTest.MultiDimFit.mH120.root data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_obs.root
    # expected limits
    combine -v -1 data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}.root -M MultiDimFit -P $PAR --floatOtherPOIs=0 --algo=grid --points=$n_points --minimizerStrategy=2 -t -1 --expectSignal=1
    if [ $? -ne 0 ]; then
      echo '[ERROR]: combine crashed'
      exit 1
    fi
    mv higgsCombineTest.MultiDimFit.mH120.root data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_exp.root
  done
  rm -f data/anomalousCoupling/*
done
echo ''
echo '---------------------------------'
echo '6. Build 1D interval'
echo '---------------------------------'
echo ''
for PAR in $PARS; do
  for CHANNEL in $CHANNELS; do
    rm -f data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_exp_${n_points}.txt
    rm -f data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_obs_${n_points}.txt
    touch data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_exp_${n_points}.txt
    touch data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_obs_${n_points}.txt
    echo 'Expected limit' >> data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_exp_${n_points}.txt
    python python/build1DInterval.py -$(cat cards/range_${PAR}.txt) $(cat cards/range_${PAR}.txt) data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_exp.root $PAR >> data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_exp_${n_points}.txt 
    echo 'Observed limit' >> data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_obs_${n_points}.txt
    python python/build1DInterval.py -$(cat cards/range_${PAR}.txt) $(cat cards/range_${PAR}.txt) data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_obs.root $PAR >> data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_obs_${n_points}.txt 
    echo '******************'
    echo $PAR ' - ' $CHANNEL
    cat data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_exp_${n_points}.txt
    cat data/$BOSON/$PAR/${BOSON}_${PAR}_${CHANNEL}_obs_${n_points}.txt
    echo '******************'
    echo ''
  done
done

exit