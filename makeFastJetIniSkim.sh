if [ $# -ne 6 ]
then 
  echo "Usage: ./makeFastJetIniSkim.sh <inputList> <sampleType> <outputFile> <outDir> <#> <isGenBool>"
  exit 1
fi

echo | awk -v inputList=$1 -v MCBool=$2 -v outputFile=$3 -v num=$5 -v isGenBool=$6 '{print "./makeFastJetIniSkim.exe \""inputList"\" \""MCBool"\" \""outputFile"\" \""num"\" \""isGenBool"\""}' | bash
mv $3_$5.root $4

echo "job done successfully"