#bin/bash

WORKDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $WORKDIR

BOSON=$1

if [ ! -z "$2" ]; then
  if [ "$2" == "all" ]; then
    PARS=""
    PARS=$PARS" FM0" 
    PARS=$PARS" FM1"
    PARS=$PARS" FM2"
    PARS=$PARS" FM3"
    PARS=$PARS" FM4"
    PARS=$PARS" FM5"
    PARS=$PARS" FM6"
    PARS=$PARS" FM7"
    PARS=$PARS" FT0"
    PARS=$PARS" FT1"
    PARS=$PARS" FT2"
    PARS=$PARS" FT5"
    PARS=$PARS" FT6"
    PARS=$PARS" FT7"
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

echo '---------------------------------'
echo '0. Prepare input cards           '
echo '---------------------------------'
echo ''
./scripts/card_generator.sh $WORKDIR $BOSON

echo ''
if [ "$3" == fit ]; then
  echo '---------------------------------'
  echo '1. Prepare aGC signal input file '
  echo '---------------------------------'
  echo ''
  ./scripts/launch_doFit.sh $WORKDIR $BOSON
  if [ $? -ne 0 ]; then
    echo '[ERROR]: launch_doFit.sh crashed'
    exit 1
  fi
else
  echo 'Fits skipped'
fi
#echo ''
#echo '---------------------------------'
#echo '2. Prepare data and MC input file'
#echo '---------------------------------'
#echo ''
#./scripts/launch_merge_histo.sh
#if [ $? -ne 0 ]; then
#  echo '[ERROR]: launch_merge_histo crashed'
#  exit 1
#fi
#./scripts/prepare_folder.sh
#if [ $? -ne 0 ]; then
#  echo '[ERROR]: prepare_folder crashed'
#  exit 1
#fi
#echo ''
#echo '---------------------------------'
#echo '3. Build the workspace'
#echo '---------------------------------'
#echo ''
#for PAR in $PARS; do
#  python python/buildWorkspace_AC.py --config="cards/config_wgg_13TeV_buildWorkspace_$PAR" --path="$WORKDIR/data/$PAR"
#  if [ $? -ne 0 ]; then
#    echo '[ERROR]: builWorkspace_AC.py crashed'
#    exit 1
#  fi
#  mkdir -p output/$PAR
#  mv aC_ch_ele.txt aC_ch_muo.txt ch_ele_ws.root ch_muo_ws.root output/$PAR
#done
#echo ''
#echo '---------------------------------'
#echo '4. Convert combine card to ws'
#echo '---------------------------------'
#echo ''
#for PAR in $PARS; do
#  for CHANNEL in $CHANNELS; do
#    cp -p output/$PAR/ch_${CHANNEL}_ws.root ${WORKDIR//\/agc_wgg/}/data/anomalousCoupling
#    cp -p data/$PAR/ch_${CHANNEL}.root ${WORKDIR//\/agc_wgg/}/data/anomalousCoupling
#    cp -p data/$PAR/signal_proc_ch_${CHANNEL}.root ${WORKDIR//\/agc_wgg/}/data/anomalousCoupling
#    text2workspace.py -m 126 output/$PAR/aC_ch_${CHANNEL}.txt -o output/$PAR/WGG_${PAR}_${CHANNEL}.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=ch_$CHANNEL --PO poi=$PAR --PO range_$PAR=-$(cat cards/range_${PAR}.txt),$(cat cards/range_${PAR}.txt)
#    if [ $? -ne 0 ]; then
#      echo '[ERROR]: text2workspace.py crashed'
#      exit 1
#    fi
#  done
#  combineCards.py output/$PAR/aC_ch_ele.txt output/$PAR/aC_ch_muo.txt > output/$PAR/aC_ch_lep.txt
#  text2workspace.py -m 126 output/$PAR/aC_ch_lep.txt -o output/$PAR/WGG_${PAR}_lep.root -P CombinedEWKAnalysis.CommonTools.ACModel:par1_TF1_Model --PO channels=ch_ele,ch_muo --PO poi=$PAR --PO range_$PAR=-$(cat cards/range_${PAR}.txt),$(cat cards/range_${PAR}.txt)
#done
#echo ''
#echo '---------------------------------'
#echo '5. Set limits                    '
#echo '---------------------------------'
#echo ''
#CHANNELS="ele muo lep"
#n_points=1000
#for PAR in $PARS; do
#  for CHANNEL in $CHANNELS; do
#    # observed limits
#    combine output/$PAR/WGG_${PAR}_${CHANNEL}.root -M MultiDimFit -P $PAR --floatOtherPOIs=0 --algo=grid --points=$n_points --minimizerStrategy=2
#    if [ $? -ne 0 ]; then
#      echo '[ERROR]: combine crashed'
#      exit 1
#    fi
#    mv higgsCombineTest.MultiDimFit.mH120.root output/$PAR/WGG_${PAR}_${CHANNEL}_obs.root
#    # expected limits
#    combine output/$PAR/WGG_${PAR}_${CHANNEL}.root -M MultiDimFit -P $PAR --floatOtherPOIs=0 --algo=grid --points=$n_points --minimizerStrategy=2 -t -1 --expectSignal=1
#    if [ $? -ne 0 ]; then
#      echo '[ERROR]: combine crashed'
#      exit 1
#    fi
#    mv higgsCombineTest.MultiDimFit.mH120.root output/$PAR/WGG_${PAR}_${CHANNEL}_exp.root
#  done
#done
#echo ''
#echo '---------------------------------'
#echo '6. Build 1D interval'
#echo '---------------------------------'
#echo ''
#for PAR in $PARS; do
#  for CHANNEL in $CHANNELS; do
#    echo ''
#    echo '---'
#    echo $CHANNEL
#    echo '---'
#    echo '' > output/$PAR/WGG_${PAR}_${CHANNEL}_exp_${n_points}.txt
#    echo '**************' >> output/$PAR/WGG_${PAR}_${CHANNEL}_exp_${n_points}.txt
#    echo 'Expected limit' >> output/$PAR/WGG_${PAR}_${CHANNEL}_exp_${n_points}.txt
#    echo '**************' >> output/$PAR/WGG_${PAR}_${CHANNEL}_exp_${n_points}.txt
#    python python/build1DInterval.py -$(cat cards/range_${PAR}.txt) $(cat cards/range_${PAR}.txt) output/$PAR/WGG_${PAR}_${CHANNEL}_exp.root $PAR >> output/$PAR/WGG_${PAR}_${CHANNEL}_exp_${n_points}.txt 
#    cat output/$PAR/WGG_${PAR}_${CHANNEL}_exp_${n_points}.txt
#    echo '' > output/$PAR/WGG_${PAR}_${CHANNEL}_obs_${n_points}.txt
#    echo '**************' >> output/$PAR/WGG_${PAR}_${CHANNEL}_obs_${n_points}.txt
#    echo 'Observed limit' >> output/$PAR/WGG_${PAR}_${CHANNEL}_obs_${n_points}.txt
#    echo '**************' >> output/$PAR/WGG_${PAR}_${CHANNEL}_obs_${n_points}.txt
#    python python/build1DInterval.py -$(cat cards/range_${PAR}.txt) $(cat cards/range_${PAR}.txt) output/$PAR/WGG_${PAR}_${CHANNEL}_obs.root $PAR >> output/$PAR/WGG_${PAR}_${CHANNEL}_obs_${n_points}.txt 
#    cat output/$PAR/WGG_${PAR}_${CHANNEL}_obs_${n_points}.txt
#  done
#done
#echo ''
#echo 'Cleaning '${WORKDIR//\/agc_wgg/}'/data/anomalousCoupling...'
#for CHANNEL in $CHANNELS; do
#  rm -f ${WORKDIR//\/agc_wgg/}/data/anomalousCoupling/ch_${CHANNEL}_ws.root
#  rm -f ${WORKDIR//\/agc_wgg/}/data/anomalousCoupling/ch_${CHANNEL}.root
#  rm -f ${WORKDIR//\/agc_wgg/}/data/anomalousCoupling/signal_proc_ch_${CHANNEL}.root
#done
#echo ''
#echo '---------------------------------'
#echo '7. Get expected significance     '
#echo '   (following AN-17-053)         '
#echo '---------------------------------'
#echo ''
#if [ "$model" == 'par1_TF1' ]; then
#  echo ''
#  echo '*********************'
#  echo 'Expected significance'
#  echo '*********************'
#  combine -v0 -M ProfileLikelihood --significance aC_ch_ee_TF1.txt --expectSignal=1 -t -1
#elif [ "$model" == 'par1_TH1' ]; then
#  echo ''
#  echo '*********************'
#  echo 'Expected significance'
#  echo '*********************'
#  combine -v0 -M ProfileLikelihood --significance aC_ch_ee_TH1.txt --expectSignal=1 -t -1
#fi

exit
