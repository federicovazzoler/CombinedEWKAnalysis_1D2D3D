#bin/bash

WORKDIR=$1
cd $WORKDIR

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

CHANNELS="ele muo"

BOSON=$2

for PAR in $PARS; do
  mkdir -p $WORKDIR/data/${BOSON}/${PAR}
  python python/doFit.py --config="$WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR" --output="$WORKDIR/data/${BOSON}/${PAR}" --rangeDir="$WORKDIR/cards"
  for CHANNEL in $CHANNELS; do
    root-6.12 -l -b -q macros/fundraw.C\(\"$WORKDIR/data/${BOSON}/${PAR}/signal_proc_ch_${CHANNEL}.root\",\"$WORKDIR/data/${BOSON}/input/${PAR}_${CHANNEL}.root\",\"$WORKDIR/html/${BOSON}/${PAR}/signal_proc_ch_${CHANNEL}\",$(cat $WORKDIR/cards/range_${PAR}.txt)\)
  done
done
