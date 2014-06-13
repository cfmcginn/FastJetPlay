if [ $# -ne 4 ]
then
  echo: "Usage: ./pJetTestScript.sh <inputList> <sType> <outName> <outDir>"
  exit 1
fi

now="skimTreeJob_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now
mkdir -p $4

len=`wc -l $1 | awk '{print $1}'`
cp jetTestScript.sh $now
cp $1 $now

NAME="jetTestScript.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "${NAME/%.C/}.exe" `../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins`
cp jetTestScript.exe $now