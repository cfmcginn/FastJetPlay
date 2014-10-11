#!/bin/bash

if [ $# -ne 5 ]
then
  echo "Usage: ./makeFastJetAnaSkim.sh <inputList> <MCBool> <outDir> <#> <isGenBool>"
  exit 1
fi

echo | awk -v inputList=$1 -v MCBool=$2 -v num=$4 -v isGenBool=$5 '{print "./makeFastJetAnaSkim.exe \""inputList"\" \""MCBool"\" \""num"\" \""isGenBool"\""}' | bash

rm cent*.root
rm hist*.root
rm eff*.root
rm fake*.root
rm secondary*.root
mv *Skim*.root $3
rm *.root

echo "job done successfully"
