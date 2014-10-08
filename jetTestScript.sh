#!/bin/bash

if [ $# -ne 4 ]
then
  echo "Usage: ./jetTestScript.sh <inputList> <MCBool> <outputFile> <outDir>"
  exit 1
fi

echo | awk -v inputList=$1 -v MCBool=$2 -v outputFile=$3 '{print "./jetTestScript.exe \""inputList"\" \""MCBool"\" \""outputFile"\""}' | bash
mv $3.root $4
rm *.root
rm *.txt

echo "job done successfully"
