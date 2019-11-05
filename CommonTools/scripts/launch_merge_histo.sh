#bin/bash

WORKDIR=$1
cd $WORKDIR

URL=$2
CHANNELS="ele muo"

BOSON=$3

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
  rm -f data/$BOSON/ch_${CHANNEL}_unequalBinning.root
  for FLAG in $FLAGS; do
    wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root $URL/$FLAG/Run2.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
    root-6.12 -l -b -q macros/merge_histo.C\(\"$WORKDIR/data/$BOSON\",\"$BOSON\",\"$CHANNEL\",\"$FLAG\"\)
    rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root
  done
  root-6.12 -l -b -q macros/dealWith_unEqualBinning.C\(\"${WORKDIR}/data/$BOSON/ch_${CHANNEL}_unequalBinning.root\"\)
  mv data/$BOSON/ch_${CHANNEL}_unequalBinning_uniformBins.root data/$BOSON/ch_${CHANNEL}.root
  rm -f data/$BOSON/ch_${CHANNEL}_unequalBinning.root
done

# write builworkspace
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

for PAR in $PARS; do
  rm -f $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  touch $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "[Global]" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "model = par1_TF1" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "par1Name = $PAR" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "par1Low = -$(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "par1High = $(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  for CHANNEL in $CHANNELS; do
    echo "[ch_${CHANNEL}]" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    if [ $BOSON == "WGG" ]; then
      echo "Nbkg = 3" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    fi
    if [ $BOSON == "ZGG" ]; then
      echo "Nbkg = 1" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    fi
    echo "bkg1_name = bkg_jetpho_misid" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    echo -n "bkg1_shape_syst = " >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    nSyst=0
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo -n "bkg_jetpho_misid_${FLAG}," >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        nSyst=$(( $nSyst + 1 ))
      fi
    done
    echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    if [ $BOSON == "WGG" ]; then
      echo "bkg2_name = bkg_zg" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      echo -n "bkg2_shape_syst = " >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      for FLAG in $FLAGS; do
        if [ ${FLAG:(-3)} == "_up" ]; then
          FLAG=${FLAG//_up/}
          echo -n "bkg_zg_${FLAG}," >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        fi
      done
      echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      echo "bkg3_name = bkg_zgg" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      echo -n "bkg3_shape_syst = " >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      for FLAG in $FLAGS; do
        if [ ${FLAG:(-3)} == "_up" ]; then
          FLAG=${FLAG//_up/}
          echo -n "bkg_zgg_${FLAG}," >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        fi
      done
      echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    fi
    echo -n "signal_shape_syst = " >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo -n "diboson_${FLAG}," >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      fi
    done
    echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    echo "NSigBkg_corr_unc = $nSyst" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    nSyst=1
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo "correlated_SigBkg_unc${nSyst}_name = $FLAG" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        if [ $BOSON == "WGG" ]; then
          echo -n "correlated_SigBkg_unc${nSyst} = diboson_$FLAG,bkg_jetpho_misid_$FLAG,bkg_zg_$FLAG,bkg_zgg_$FLAG" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        fi
        if [ $BOSON == "ZGG" ]; then
          echo -n "correlated_SigBkg_unc${nSyst} = diboson_$FLAG,bkg_jetpho_misid_$FLAG" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        fi
        echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        nSyst=$(( $nSyst + 1 ))
      fi 
    done
  done
  sed -i -e 's/,$//' $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
done
