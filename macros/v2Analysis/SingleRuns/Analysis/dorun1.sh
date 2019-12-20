#!/bin/bash
#POLS
e="-0.8"
E="0.3"
L="1600"
run=1
choosex=$1
#python combinationanalysis.py $run 2 $e $E $L
#python combinationanalysis.py $run 3 $e $E $L
#python combinationanalysis.py $run 4 $e $E $L
#python combinationanalysis.py $run 5 $e $E $L
#python combinationanalysis.py $run 6 $e $E $L
#python combinationanalysis.py $run 7 $e $E $L
#python combinationanalysis.py $run 8 $e $E $L
#python combinationanalysis.py $run 9 $e $E $L
#python combinationanalysis.py $run $choosex $e $E $L











./runmyanalysis.sh TIGHT mastercuts/mastercutR1_TIGHT.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/testTight.root $e $E $L  > run1.log
./runmyanalysis.sh LOOSE mastercuts/mastercutR1_LOOSE.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/testLoose.root $e $E $L > run1Loose.log

cd ../AnalysisSignal

./runmyanalysis.sh TIGHT ../Analysis/mastercuts/mastercutR1_TIGHT.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/test2Tight.root $e $E $L > run1S.log
./runmyanalysis.sh LOOSE ../Analysis/mastercuts/mastercutR1_LOOSE.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/test2Loose.root $e $E $L> run1SLoose.log

cd ../Analysis
#./runcombineEff.sh /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/testTight.root /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/test2Tight.root r1tight.root TIGHT
#./runcombineEff.sh /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/testLoose.root /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/test2Loose.root r1loose.root LOOSE


#less /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/TIGHT*.out > /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/run1summary/TIGHTsummary1.out
#less /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/LOOSE*.out > /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/run1summary/LOOSEsummary1.out

#rm /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/*.out


#need move all output text files

python selTables.py run1.log ../AnalysisSignal/run1S.log run1.table
python selTables.py run1Loose.log ../AnalysisSignal/run1SLoose.log run1Loose.table


#some other macro to print summary?
python summarizerun.py run1.table run1Loose.table summary1.out
