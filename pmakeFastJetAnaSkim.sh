#!/bin/bash

if [ $# -ne 4 ]
then
  echo "Usage: ./pmakeFastJetAnaSkim.sh <inputList> <sType> <outDir> <isGenBool>"
  exit 1
fi

now="jobFastJetAnaSkim_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now
mkdir -p $3

len=`wc -l $1 | awk '{print $1}'`
cp makeFastJetAnaSkim.sh $now
cp $1 $now

NAME="makeFastJetAnaSkim.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "${NAME/%.C/}.exe" `../fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` -lNsubjettiness -lJetFFMoments
mv makeFastJetAnaSkim.exe $now

cat pmakeFastJetAnaSkim.condor | sed "s@log_flag@$now@g" | sed "s@dir_flag@$PWD/$now@g" | sed "s@arg1@$1@g" | sed "s@arg2@$2@g" | sed "s@arg3@$3@g" | sed "s@arg4@$4@g" | sed "s@njobs@$len@g" > $now/pmakeFastJetAnaSkim.condor

echo -=-
cat $now/pmakeFastJetAnaSkim.condor
echo -=-
