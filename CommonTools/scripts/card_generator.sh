#bin/bash

WORKDIR=$1

BOSON=$2

NLASTBINS=$3

PARS=""
if [ "$BOSON" == "WGG" ]; then
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
if [ "$BOSON" == "ZGG" ]; then
  PARS=$PARS" FT8"
  PARS=$PARS" FT9"
fi

for PAR in $PARS; do
  rm -f $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  touch $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "[Global]" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "obsBins = 0.,20.,40.,60.,80.,180.,300." >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "nLastBins = $3" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "par1Name = $PAR" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "nGridPar1Bins = 16" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "outputgridpoints = 10000" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "par1GridMin = -$(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "par1GridMax = $(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "function = [0] + [1]*x + [2]*x*x" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "model = par1_TF1" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "[ch_ele]" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "obsBins = 0.,20.,40.,60.,80.,180.,300." >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "signal_model = $WORKDIR/data/$BOSON/input/${PAR}_ele.root" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "[ch_muo]" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "obsBins = 0.,20.,40.,60.,80.,180.,300." >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
  echo "signal_model = $WORKDIR/data/$BOSON/input/${PAR}_muo.root" >> $WORKDIR/cards/config_${BOSON}_13TeV_inputSignalModelFit_$PAR
done
