python selTables.py run1.log ../AnalysisSignal/run1S.log run1.table 
python selTables.py run1Loose.log ../AnalysisSignal/run1SLoose.log run1Loose.table


python summarizerun.py run1.table run1Loose.table testsummary.out
