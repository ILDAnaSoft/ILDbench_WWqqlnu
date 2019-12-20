



import sys


# combinations of given length 
from itertools import combinations 


#read in cuts
mastercutfilename = sys.argv[1]
ifile = open(mastercutfilename,"r")
lines =  ifile.readlines()
ncuts = len(lines)

ofiledirectory = sys.argv[2]

print lines, ncuts
# Get all combinations of [1, 2, 3] 
# and length 2 
for i in xrange(2,ncuts+1):
	comb = combinations(lines, i) 
 	#print list( comb )
	counter = 1
	for j in list(comb):
		#counter = 1
		ofile = open(ofiledirectory+str(i)+"_"+str(counter)+"_"+mastercutfilename[20:], "w")
		for item in j:
			ofile.write(str(item))
		ofile.close();
		counter = counter +1

# Print the obtained combinations 
#for i in list(comb): 
 #   print i 
