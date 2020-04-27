#bin/bash

WORKDIR=$1
cd $WORKDIR

URL=$2
CHANNELS="ele muo"

BOSON=$3

LASTBINS=$4

FLAGS="reference"
FLAGS=$FLAGS" pileup_up"
FLAGS=$FLAGS" pileup_down"
#FLAGS=$FLAGS" jec_up"
#FLAGS=$FLAGS" jec_down"
#FLAGS=$FLAGS" jer_up"
#FLAGS=$FLAGS" jer_down"
FLAGS=$FLAGS" sf_ele_eff_up"
FLAGS=$FLAGS" sf_ele_eff_down"
FLAGS=$FLAGS" sf_ele_reco_up"
FLAGS=$FLAGS" sf_ele_reco_down"
FLAGS=$FLAGS" sf_ele_trig_up"
FLAGS=$FLAGS" sf_ele_trig_down"
FLAGS=$FLAGS" sf_muo_id_up"
FLAGS=$FLAGS" sf_muo_id_down"
FLAGS=$FLAGS" sf_muo_iso_up"
FLAGS=$FLAGS" sf_muo_iso_down"
FLAGS=$FLAGS" sf_muo_trig_up"
FLAGS=$FLAGS" sf_muo_trig_down"
FLAGS=$FLAGS" sf_pho_eff_up"
FLAGS=$FLAGS" sf_pho_eff_down"
FLAGS=$FLAGS" sf_pho_veto_up"
FLAGS=$FLAGS" sf_pho_veto_down"
FLAGS=$FLAGS" l1prefiring_up"
FLAGS=$FLAGS" l1prefiring_down"
FLAGS=$FLAGS" eg_misid_up"
FLAGS=$FLAGS" eg_misid_down"
FLAGS=$FLAGS" jet_misid_syst"

YEARS="2016 2017 2018 Run2"

# merge histos
for YEAR in ${YEARS}; do
  echo "Processing : "${YEAR}
  for CHANNEL in $CHANNELS; do
    rm -f data/$BOSON/ch_${CHANNEL}_${YEAR}_unequalBinning.root
    for FLAG in $FLAGS; do
      if [[ "$FLAG" == "jec_up" || "$FLAG" == "jec_down" || "$FLAG" == "jer_up" || "$FLAG" == "jer_down" || "$FLAG" == "sf_pho_veto_up" || "$FLAG" == "sf_pho_veto_down" ]]; then
        if [[ "${YEAR}" == "2016" ]]; then
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root $URL/${FLAG}_2016/${YEAR}.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          root-6.12 -l -b -q macros/merge_histo.C\(\"$WORKDIR/data/$BOSON\",\"$BOSON\",\"$CHANNEL\",\"$FLAG\",\"$YEAR\",$LASTBINS\)
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root
        elif [[ "${YEAR}" == "2017" ]]; then
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root $URL/${FLAG}_2017/${YEAR}.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          root-6.12 -l -b -q macros/merge_histo.C\(\"$WORKDIR/data/$BOSON\",\"$BOSON\",\"$CHANNEL\",\"$FLAG\",\"$YEAR\",$LASTBINS\)
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root
        elif [[ "${YEAR}" == "2018" ]]; then
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root $URL/${FLAG}_2018/${YEAR}.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          root-6.12 -l -b -q macros/merge_histo.C\(\"$WORKDIR/data/$BOSON\",\"$BOSON\",\"$CHANNEL\",\"$FLAG\",\"$YEAR\",$LASTBINS\)
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root
        elif [[ "${YEAR}" == "Run2" ]]; then
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference.root $URL/reference/Run2.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference_2016.root $URL/reference/2016.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference_2017.root $URL/reference/2017.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference_2018.root $URL/reference/2018.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}_2016.root $URL/${FLAG}_2016/Run2.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}_2017.root $URL/${FLAG}_2017/Run2.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}_2018.root $URL/${FLAG}_2018/Run2.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
          root-6.12 -l -b -q macros/combine_syst.C\(\"$WORKDIR/data/$BOSON\",\"$BOSON\",\"$CHANNEL\",\"$FLAG\",\"$YEAR\",$LASTBINS\)
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference.root
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference_2016.root
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference_2017.root
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference_2018.root
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}_2016.root
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}_2017.root
          rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}_2018.root
        fi
      elif [[ "$FLAG" == "jet_misid_syst" ]]; then
        wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference.root $URL/reference/${YEAR}.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
        wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root $URL/$FLAG/${YEAR}.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
        root-6.12 -l -b -q macros/syst_symmetriser.C\(\"$WORKDIR/data/$BOSON\",\"$BOSON\",\"$CHANNEL\",\"$FLAG\",\"$YEAR\",$LASTBINS\)
        rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root
        rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_reference.root
      else
        wget -q -O data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root $URL/$FLAG/${YEAR}.matrix/root/h_${BOSON}_${CHANNEL}_pho0_pho1_pt.root
        root-6.12 -l -b -q macros/merge_histo.C\(\"$WORKDIR/data/$BOSON\",\"$BOSON\",\"$CHANNEL\",\"$FLAG\",\"$YEAR\",$LASTBINS\)
        rm -f data/$BOSON/h_${BOSON}_${CHANNEL}_pho0_pho1_pt_${FLAG}.root
      fi
    done
    root-6.12 -l -b -q macros/dealWith_unEqualBinning.C\(\"${WORKDIR}/data/$BOSON/ch_${CHANNEL}_${YEAR}_unequalBinning.root\"\)
    mv data/$BOSON/ch_${CHANNEL}_${YEAR}_unequalBinning_uniformBins.root data/$BOSON/ch_${CHANNEL}_${YEAR}.root
    rm -f data/$BOSON/ch_${CHANNEL}_${YEAR}_unequalBinning.root
  done
done

# write builworkspace
PARS=""
if [ $BOSON = "WGG" ]; then
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
if [ $BOSON = "ZGG" ]; then
  PARS=$PARS" FT8"
  PARS=$PARS" FT9"
fi

FLAGS=$(echo $FLAGS | sed -e "s; jet_misid_syst; jet_misid_up jet_misid_down;")

for PAR in $PARS; do
  rm -f $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  touch $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "[Global]" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "model = par1_TF1" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "par1Name = $PAR" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "par1Low = -$(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "par1High = $(cat $WORKDIR/cards/range_${PAR}.txt)" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "NlnN = 1" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  echo "lnN1_name = lumi" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  if [ $BOSON = "WGG" ]; then
    echo "lnN1_value = 1.018,1.018,1.018,1.018,1.018,1.018,1.018,1.018" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    echo "lnN1_for = ch_ele_signal,ch_ele_bkg_jetpho_misid,ch_ele_bkg_irred,ch_ele_bkg_egmisid,ch_muo_signal,ch_muo_bkg_jetpho_misid,ch_muo_bkg_irred,ch_muo_bkg_egmisid" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  fi
  if [ $BOSON = "ZGG" ]; then
    echo "lnN1_value = 1.018,1.018,1.018,1.018,1.018,1.018" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    echo "lnN1_for = ch_ele_signal,ch_ele_bkg_jetpho_misid,ch_ele_bkg_irred,ch_muo_signal,ch_muo_bkg_jetpho_misid,ch_muo_bkg_irred" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
  fi
  for CHANNEL in $CHANNELS; do
    echo "[ch_${CHANNEL}]" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    if [ $BOSON = "WGG" ]; then
      echo "Nbkg = 3" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    fi
    if [ $BOSON = "ZGG" ]; then
      echo "Nbkg = 2" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
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
    echo "bkg2_name = bkg_irred" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    echo -n "bkg2_shape_syst = " >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    for FLAG in $FLAGS; do
      if [ ${FLAG:(-3)} == "_up" ]; then
        FLAG=${FLAG//_up/}
        echo -n "bkg_irred_${FLAG}," >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      fi
    done
    echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
    if [ $BOSON = "WGG" ]; then
      echo "bkg3_name = bkg_egmisid" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      echo -n "bkg3_shape_syst = " >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
      for FLAG in $FLAGS; do
        if [ ${FLAG:(-3)} == "_up" ]; then
          FLAG=${FLAG//_up/}
          echo -n "bkg_egmisid_${FLAG}," >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
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
        if [ $BOSON = "WGG" ]; then
          echo -n "correlated_SigBkg_unc${nSyst} = diboson_$FLAG,bkg_jetpho_misid_$FLAG,bkg_irred_$FLAG,bkg_egmisid_$FLAG" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        fi
        if [ $BOSON = "ZGG" ]; then
          echo -n "correlated_SigBkg_unc${nSyst} = diboson_$FLAG,bkg_jetpho_misid_$FLAG,bkg_irred_$FLAG" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        fi
        echo "" >> $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
        nSyst=$(( $nSyst + 1 ))
      fi
    done
  done
  sed -i -e 's/,$//' $WORKDIR/cards/config_${BOSON}_13TeV_buildWorkspace_$PAR
done
