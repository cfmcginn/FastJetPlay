if [ $# -ne 5 ]
then
  echo "Usage: ./makeFastJetAnaSkim.sh <inputList> <MCBool> <outputFile> <outDir> <isGenBool>"
  exit 1
fi

echo | awk -v inputList=$1 -v MCBool=$2 -v outputFile=$3 -v isGenBool=$5 '{print "./makeFastJetAnaSkim.exe \""inputList"\" \""MCBool"\" \""outputFile"\" \""isGenBool"\""}' | bash
mv $3.root $4
rm *.root
rm *.txt

echo "job done successfully"
