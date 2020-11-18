#bin/bash

CHANNELS="ele muo lep"

BOSONS="WGG ZGG"

BLINDING="obs"

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

PARS=$PARS" FT8"
PARS=$PARS" FT9"

rm latex_${BLINDING}.txt
touch latex_${BLINDING}.txt
rm latex_lep_${BLINDING}.txt
touch latex_lep_${BLINDING}.txt
rm param_${BLINDING}.txt
touch param_${BLINDING}.txt

for PAR in $PARS; do

  echo -n "\$" >> latex_${BLINDING}.txt
  echo -n "\$" >> latex_lep_${BLINDING}.txt
  WRITEPAR=${PAR:0:1}_{${PAR:1:1},${PAR:2:1}}
  echo -n $WRITEPAR | sed 's/F/f/g' >> latex_${BLINDING}.txt
  echo -n $WRITEPAR | sed 's/F/f/g' >> latex_lep_${BLINDING}.txt
  echo -n "\$" >> latex_${BLINDING}.txt
  echo -n "\$" >> latex_lep_${BLINDING}.txt

  errors=0

  for BOSON in $BOSONS; do

    for CHANNEL in $CHANNELS; do

      if [[ "$BOSON" = "ZGG" ]]; then
        if [[ "$PAR" = "FM0" ]] || [[ "$PAR" = "FM1" ]] || [[ "$PAR" = "FM2" ]] || [[ "$PAR" = "FM3" ]] || [[ "$PAR" = "FM4" ]] || [[ "$PAR" = "FM5" ]] || [[ "$PAR" = "FM6" ]] || [[ "$PAR" = "FM7" ]]; then
          if [[ "$CHANNEL" != "lep" ]]; then
            echo -n "& " >> latex_${BLINDING}.txt
          else
            echo -n "& " >> latex_lep_${BLINDING}.txt
          fi
          continue
        fi
      fi

      if [[ "$BOSON" = "WGG" ]]; then
        if [[ "$PAR" = "FT8" ]] || [[ "$PAR" = "FT9" ]]; then
          if [[ "$CHANNEL" != "lep" ]]; then
            echo -n "& " >> latex_${BLINDING}.txt
          else
            echo -n "& " >> latex_lep_${BLINDING}.txt
          fi
          continue
        fi
      fi

      lastline=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_${BLINDING}_1000.txt)

      if [[ $lastline = *"]U["* ]]; then
        lastline=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_${BLINDING}_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]U\[/_/g' | sed 's/\]//g')
        firstelement=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_${BLINDING}_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]U\[/_/g' | sed 's/\]//g' | cut -f1 -d"_" | cut -f1 -d",")
        firstline=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_${BLINDING}_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]U\[/_/g' | sed 's/\]//g' | cut -f1 -d"_")
        secondelement=${firstline#*,}

        secondline=${lastline#*_}
        thirdelement=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_${BLINDING}_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]U\[/_/g' | sed 's/\]//g'| cut -d "_" -f2 | cut -f1 -d",")
        fourthelement=${secondline#*,}

        if [[ ${firstelement:0:1} != ${secondelement:0:1} ]]; then
          first=$firstelement
          second=$secondelement
        elif [[ ${thirdelement:0:1} != ${fourthelement:0:1} ]]; then 
          first=$thirdelement
          second=$fourthelement
        else
          first=0
          second=0
          errors=$errors+1
        fi

        echo $first $second

      else

        first=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_${BLINDING}_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]//g' | cut -f1 -d",")
        line=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_${BLINDING}_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]//g')
        second=${line#*,}

      fi

      if [[ "$first" = "Sorry" ]]; then

        if [[ "$CHANNEL" != "lep" ]]; then
          echo -n "& " >> latex_${BLINDING}.txt
        else
          echo -n "& " >> latex_lep_${BLINDING}.txt
        fi 

      else
    
        root-6.18 -l -b -q convert.C\(${first}\)
        minval=$(cat out.txt)
        rm out.txt
    
        root-6.18 -l -b -q convert.C\(${second}\)
        maxval=$(cat out.txt)
        rm out.txt

        if [[ "$CHANNEL" != "lep" ]]; then
          echo -n "& ${minval}, ${maxval} " >> latex_${BLINDING}.txt
        else
          echo -n "& ${minval}, ${maxval} " >> latex_lep_${BLINDING}.txt
        fi

        echo "float ${PAR}_${BOSON}_${CHANNEL}_DOWN = ${minval};" >> param_${BLINDING}.txt
        echo "float ${PAR}_${BOSON}_${CHANNEL}_UP = ${maxval};" >> param_${BLINDING}.txt

      fi

    done

  done

  echo "\\\\" >> latex_${BLINDING}.txt
  echo "\\\\" >> latex_lep_${BLINDING}.txt

done

echo "There have been $errors errors."

