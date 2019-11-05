#bin/bash

WORKDIR=$HOME/work/AGC/CMSSW_7_1_5/src/CombinedEWKAnalysis/CommonTools/agc_wgg
cd $WORKDIR

URL="https://wwwusers.ts.infn.it/~dellaric/tmp/Vgg/v13.default/"
CHANNELS="ele muo"

FLAGS="reference"
FLAGS=$FLAGS" pileup_up"
FLAGS=$FLAGS" pileup_down"
#FLAGS=$FLAGS" jec_up_2016"
#FLAGS=$FLAGS" jec_up_2017"
#FLAGS=$FLAGS" jec_up_2018"
#FLAGS=$FLAGS" jec_down_2016"
#FLAGS=$FLAGS" jec_down_2017"
#FLAGS=$FLAGS" jec_down_2018"
#FLAGS=$FLAGS" jer_up_2016"
#FLAGS=$FLAGS" jer_up_2017"
#FLAGS=$FLAGS" jer_up_2018"
#FLAGS=$FLAGS" jer_down_2016"
#FLAGS=$FLAGS" jer_down_2017"
#FLAGS=$FLAGS" jer_down_2018"
#FLAGS=$FLAGS" sf_ele_eff_up"
#FLAGS=$FLAGS" sf_ele_eff_down"
#FLAGS=$FLAGS" sf_ele_reco_up"
#FLAGS=$FLAGS" sf_ele_reco_down"
#FLAGS=$FLAGS" sf_ele_trig_up"
#FLAGS=$FLAGS" sf_ele_trig_down"
#FLAGS=$FLAGS" sf_muo_id_up"
#FLAGS=$FLAGS" sf_muo_id_down"
#FLAGS=$FLAGS" sf_muo_iso_up"
#FLAGS=$FLAGS" sf_muo_iso_down"
#FLAGS=$FLAGS" sf_muo_trig_up"
#FLAGS=$FLAGS" sf_muo_trig_down"
#FLAGS=$FLAGS" sf_pho_eff_up"
#FLAGS=$FLAGS" sf_pho_eff_down"
#FLAGS=$FLAGS" sf_pho_veto_up_2016"
#FLAGS=$FLAGS" sf_pho_veto_up_2017"
#FLAGS=$FLAGS" sf_pho_veto_up_2018"
#FLAGS=$FLAGS" sf_pho_veto_down_2016"
#FLAGS=$FLAGS" sf_pho_veto_down_2017"
#FLAGS=$FLAGS" sf_pho_veto_down_2018"
FLAGS=$FLAGS" l1prefiring_up"
FLAGS=$FLAGS" l1prefiring_down"
#FLAGS=$FLAGS" eg_misid_up"
#FLAGS=$FLAGS" eg_misid_down"
#FLAGS=$FLAGS" jet_misid_iso0"
#FLAGS=$FLAGS" jet_misid_iso1"
#FLAGS=$FLAGS" jet_misid_iso2"
#FLAGS=$FLAGS" jet_bkg_mc"

# merge histos
for CHANNEL in $CHANNELS; do
  rm -f data/ch_${CHANNEL}_unequalBinning.root
  for FLAG in $FLAGS; do
    wget -q -O data/h_WGG_${CHANNEL}_pho0_pho1_pt_${FLAG}.root $URL/$FLAG/Run2.matrix/root/h_WGG_${CHANNEL}_pho0_pho1_pt.root 
    root-6.12 -l -b -q src/merge_histo.C\(\"$WORKDIR/data\",\"$CHANNEL\",\"$FLAG\"\)
    rm -f data/h_WGG_${CHANNEL}_pho0_pho1_pt_${FLAG}.root
  done
  root-6.12 -l -b -q src/dealWith_unEqualBinning.C\(\"${WORKDIR}/data/ch_${CHANNEL}_unequalBinning.root\"\)
  mv data/ch_${CHANNEL}_unequalBinning_uniformBins.root data/ch_${CHANNEL}.root
  rm -f data/ch_${CHANNEL}_unequalBinning.root
done

# write builworkspace
PARS="FM0 FM1 FM2 FM3 FM4 FM5 FM6 FM7 FT0 FT1 FT2 FT5 FT6 FT7"
#PARS="FM0"

for PAR in $PARS; do
  rm -f $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
  touch $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
  echo "[Global]" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
  echo "model = par1_TF1" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
  echo "par1Name = $PAR" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
  echo "par1Low = -$(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
  echo "par1High = $(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
  for CHANNEL in $CHANNELS; do
    echo "[ch_${CHANNEL}]" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo "Nbkg = 3" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo "bkg1_name = bkg_jetpho_misid" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo -n "bkg1_shape_syst = " >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    nSyst=0
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo -n "bkg_jetpho_misid_${FLAG}," >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
        nSyst=$(( $nSyst + 1 ))
      fi
    done
    echo "" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo "bkg2_name = bkg_zg" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo -n "bkg2_shape_syst = " >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo -n "bkg_zg_${FLAG}," >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
      fi
    done
    echo "" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo "bkg3_name = bkg_zgg" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo -n "bkg3_shape_syst = " >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo -n "bkg_zgg_${FLAG}," >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
      fi
    done
    echo "" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo -n "signal_shape_syst = " >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo -n "diboson_${FLAG}," >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
      fi
    done
    echo "" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    echo "NSigBkg_corr_unc = $nSyst" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
    nSyst=1
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo "correlated_SigBkg_unc${nSyst}_name = $FLAG" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
        echo -n "correlated_SigBkg_unc${nSyst} = diboson_$FLAG,bkg_jetpho_misid_$FLAG,bkg_zg_$FLAG,bkg_zgg_$FLAG" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
        echo "" >> $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
        nSyst=$(( $nSyst + 1 ))
      fi 
    done
  done
  sed -i -e 's/,$//' $WORKDIR/cards/config_wgg_13TeV_buildWorkspace_$PAR
done
