#bin/bash

pars="FM0 FM1 FM2 FM3 FM4 FM5 FM6 FM7 FT0 FT1 FT2 FT5 FT6 FT7"
#pars="FM0"
channels="ele muo"

WORKDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $WORKDIR

for par in $pars; do
  python python/doFit.py --config="$WORKDIR/cards/config_wgg_13TeV_inputSignalModelFit_$par" --output="$WORKDIR"
  for channel in $channels; do
    root-6.12 -l -b -q src/fundraw.C\(\"$WORKDIR/data\",\"FIT_$(echo $par)_ch_${channel}.root\",\"${par}_${channel}.root\",1000\)
  done
done
