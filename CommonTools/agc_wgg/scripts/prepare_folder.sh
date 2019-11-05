#bin/bash

WORKDIR=$HOME/work/aTGC_tool/CMSSW_7_1_5/src/CombinedEWKAnalysis/CommonTools/agc_wgg
cd $WORKDIR

PARS="FM0 FM1 FM2 FM3 FM4 FM5 FM6 FM7 FT0 FT1 FT2 FT5 FT6 FT7"
CHANNELS="ele muo"

for PAR in $PARS; do
  mkdir -p data/$PAR
  for CHANNEL in $CHANNELS; do
    cp -p data/ch_${CHANNEL}.root data/$PAR/ch_${CHANNEL}.root
    cp -p data/post_fit/FIT_${PAR}_ch_${CHANNEL}.root data/$PAR/signal_proc_ch_${CHANNEL}.root
  done
done

exit
