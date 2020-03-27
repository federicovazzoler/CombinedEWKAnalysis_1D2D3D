#bin/bash

CHANNELS="ele muo lep"

BOSONS="WGG ZGG"

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

rm latex.txt
touch latex.txt
rm param.txt
touch param.txt

for PAR in $PARS; do

  WRITEPAR=${PAR:0:1}_{${PAR:1:1},${PAR:2:1}}
  echo -n $WRITEPAR | sed 's/F/f/g' >> latex.txt

  for BOSON in $BOSONS; do

    for CHANNEL in $CHANNELS; do

      if [[ "$BOSON" = "ZGG" ]]; then
        if [[ "$PAR" = "FM0" ]] || [[ "$PAR" = "FM1" ]] || [[ "$PAR" = "FM2" ]] || [[ "$PAR" = "FM3" ]] || [[ "$PAR" = "FM4" ]] || [[ "$PAR" = "FM5" ]] || [[ "$PAR" = "FM6" ]] || [[ "$PAR" = "FM7" ]]; then
          echo -n "& " >> latex.txt
          continue
        fi
      fi

      if [[ "$BOSON" = "WGG" ]]; then
        if [[ "$PAR" = "FT8" ]] || [[ "$PAR" = "FT9" ]]; then
          echo -n "& " >> latex.txt
          continue
        fi
      fi

      first=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_exp_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]//g' | cut -f1 -d",")
      line=$(tail -1 ../data/${BOSON}/${PAR}/${BOSON}_${PAR}_${CHANNEL}_exp_1000.txt | sed 's/95\% CL Limit: \[//g' | sed 's/\]//g')
      second=${line#*,}

      if [[ "$first" = "Sorry" ]]; then

        if [[ "$CHANNEL" != "lep" ]]; then
          echo -n "& " >> latex.txt
        fi

      else
    
        root-6.18 -l -b -q convert.C\(${first}\)
        minval=$(cat out.txt)
        rm out.txt
    
        root-6.18 -l -b -q convert.C\(${second}\)
        maxval=$(cat out.txt)
        rm out.txt
    
        if [[ "$CHANNEL" != "lep" ]]; then
          echo -n "& ${minval}, ${maxval} " >> latex.txt
        fi

        echo "float ${PAR}_${BOSON}_${CHANNEL}_DOWN = ${minval};" >> param.txt
        echo "float ${PAR}_${BOSON}_${CHANNEL}_UP = ${maxval};" >> param.txt

      fi

    done

  done

  echo "\\\\" >> latex.txt

done

