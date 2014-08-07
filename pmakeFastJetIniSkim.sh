if [ $# -ne 5 ]
then 
  echo "Usage: ./makeFastJetIniSkim.sh <inputList> <sampleType> <outName> <outDir> <isGenBool>"
  exit 1
fi

now="FastJetIniSkimJob_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now
mkdir -p $4
len=`wc -l $1 | awk '{print $1}'`
cp makeFastJetIniSkim.sh $now
cp $1 $now

NAME="makeFastJetIniSkim.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "${NAME/%.C/}.exe" `../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` 
cp makeFastJetIniSkim.exe $now

cat pmakeFastJetIniSkim.condor | sed "s@log_flag@$now@g" | sed "s@dir_flag@$PWD/$now@g" | sed "s@arg1@$1@g" | sed "s@arg2@$2@g" | sed "s@arg3@$3@g" | sed "s@arg4@$4@g" | sed "s@arg5@$5@g" | sed "s@njobs@$len@g" > $now/pmakeFastJetIniSkim.condor
echo -=-
cat $now/pmakeFastJetIniSkim.condor
echo -=-
