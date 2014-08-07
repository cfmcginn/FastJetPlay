if [ $# -ne 5 ]
then
  echo: "Usage: ./pmakeFastJetAnaSkim.sh <inputList> <sType> <outName> <outDir> <isGenBool>"
  exit 1
fi

now="skimTreeJob_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now
mkdir -p $4

len=`wc -l $1 | awk '{print $1}'`
cp makeFastJetAnaSkim.sh $now
cp $1 $now

NAME="makeFastJetAnaSkim.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "${NAME/%.C/}.exe" `../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` -lNsubjettiness
cp makeFastJetAnaSkim.exe $now