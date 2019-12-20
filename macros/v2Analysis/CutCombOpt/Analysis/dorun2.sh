#!/bin/bash
#POLS
e="0.8"
E="-0.3"
L="1600"


./runmyanalysis.sh TIGHT cut0.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/testTight.root $e $E $L  > run2.log
./runmyanalysis.sh LOOSE cut0.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/testLoose.root $e $E $L > run2Loose.log

cd ../AnalysisSignal

./runmyanalysis.sh TIGHT ../Analysis/cut0.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/test2Tight.root $e $E $L > run2S.log
./runmyanalysis.sh LOOSE ../Analysis/cut0.cutlist /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/test2Loose.root $e $E $L> run2SLoose.log

cd ../Analysis
./runcombineEff.sh /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/testTight.root /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/test2Tight.root r2tight.root TIGHT
./runcombineEff.sh /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/testLoose.root /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/intermediateRootFile/test2Loose.root r2loose.root LOOSE


less /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/TIGHT*.out > /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/run2summary/TIGHTsummary2.out
less /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/LOOSE*.out > /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/run2summary/LOOSEsummary2.out

rm /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/*.out


#need move all output text files

#python selTables.py run1.log ../AnalysisSignal/run1S.log run1.table
#python selTables.py run1T.log ../AnalysisSignal/run1ST.log run1T.table


#some other macro to print summary?
#python summarizerun.py run1.table run1T.table summary1.out
