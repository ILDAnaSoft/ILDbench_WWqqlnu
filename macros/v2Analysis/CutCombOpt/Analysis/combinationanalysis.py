import sys
import subprocess
#NOTE all output text files will have run1 in them (that doesnt mean they are specific to run1 its just reused for convenience)
def bash( bashCommand ):
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        #process = subprocess.Popen(bashCommand.split())
        output, error = process.communicate()
        return output ,error
#
runnumber = sys.argv[1]
choosex = sys.argv[2]

outfilename = "run"+runnumber+"choose"+choosex+".out"
outfilepath = "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/"
ofile=open(outfilepath+outfilename, "w")

#input polstuff
epol = sys.argv[3]
Epol = sys.argv[4]
Lumi = sys.argv[5]


#get the list of choose x files
#loose and tight

#tight
tightpath = "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/cutcombs/r"+str(runnumber)+"TIGHT/"

#loose 
loosepath = "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/cutcombs/r"+str(runnumber)+"LOOSE/"

cmd = " ls "+tightpath#+choosex+"_*"
out = bash(cmd)
#print(out)

allfiles = out[0].split("\n")

choosefiles = []
for afile in allfiles:
	splitfile = afile.split("_")
	if(splitfile[0] == choosex):
		choosefiles.append(afile)


print choosefiles

run1log = "run"+str(choosex)+".log"
run1Slog = "run"+str(choosex)+"S.log"
run1Looselog = "run"+str(choosex)+"Loose.log"
run1SLooselog = "run"+str(choosex)+"SLoose.log"
run1table = "run"+str(choosex)+".table"
run1Loosetable = "run"+str(choosex)+"Loose.table"
testsummary = "test"+str(choosex)+"summary.out"

for afile in choosefiles:
	#run tight bg
	cmd = "./runmyanalysis.sh TIGHT "+tightpath+afile+" /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/test"+choosex+"Tight.root "+str(epol)+" "+str(Epol)+" "+str(Lumi)
	print cmd


	subprocess.call(cmd, stdout=open(run1log,"w"), shell = True)
	#run loose bg

	loosefile = afile[:-13] + "LOOSE.cutlist"

	cmd = "./runmyanalysis.sh LOOSE "+loosepath+loosefile+" /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/test"+choosex+"Loose.root "+str(epol)+" "+str(Epol)+" "+str(Lumi)
	print cmd
	subprocess.call(cmd, stdout=open(run1Looselog,"w"), shell = True) 



#	cmd = "cd ../AnalysisSignal"
#	subprocess.call(cmd, shell = True )
	


#	print tight sig
	cmd = "./runmyanalysis.sh TIGHT "+tightpath+afile+" /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/test"+choosex+"STight.root "+str(epol)+" "+str(Epol)+" "+str(Lumi)
	print cmd
	subprocess.call(cmd, stdout=open(run1Slog,"w"), shell = True, cwd= "../AnalysisSignal")
	#run loose sig
	cmd = "./runmyanalysis.sh LOOSE "+loosepath+loosefile+" /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutCombOptFiles/intermediateRootFile/test"+choosex+"SLoose.root "+epol+" "+Epol+" "+Lumi
	print cmd
	subprocess.call(cmd, stdout=open(run1SLooselog,"w"), shell = True, cwd="../AnalysisSignal")	
	

#	cmd = "cd ../Analysis"
#	subprocess.call(cmd, shell = True)
	#all logs are created 
	#do seltables
#	run1table = "run"+str(choosex)+".table"
#	run1Loosetable = "run"+str(choosex)+"Loose.table"
#	testsummary = "test"+str(choosex)+"summary.out"

	cmd = "python selTables.py "+ run1log +" "+ run1Slog+ " "+run1table
	print cmd
	subprocess.call(cmd, shell = True)
	
	cmd = "python selTables.py "+run1Looselog+" "+ run1SLooselog+" "+run1Loosetable
	print cmd
	subprocess.call(cmd, shell = True)

	cmd = "python summarizerun.py "+run1table+" "+run1Loosetable+" "+ testsummary
	subprocess.call(cmd, shell = True)

	#last add summary to file
	summary = open(testsummary)
	summarylines = summary.readlines()
	ofile.write(afile+"\n")
	for line in summarylines:
		if len(line.strip()) == 0:
			continue
		line = line.split();
		if(line[0] == "***"):
			ofile.write(line[1]+" "+line[2]+" "+line[3]+"\n")
	ofile.write("\n")
	summary.close()
			
ofile.close();
