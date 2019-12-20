

import sys

ifilename = sys.argv[1]
ofilename = sys.argv[2]



ifile = open(ifilename,"r")
ofile = open(ofilename,"w")

lines = ifile.readlines()
for line in lines:
	line = line.split()
	if(line[0] == "Best:"):
		ofile.write("$ "+line[1]+" "+line[2]+"\n")	

ofile.close();
ifile.close();	
