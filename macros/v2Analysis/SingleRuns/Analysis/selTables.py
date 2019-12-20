import sys
from operator import add 
import math
from operator import sub
def efferr(num,den):
	eff = num/den
	n = den
	print num, den, eff
	return math.sqrt( eff*(1-eff)/ n ) 
		
def eff(num,den):
	return num/den

ifilename = sys.argv[1]
ifile =  open(ifilename,"r")

#establish cut flow
CUT = []
Lumi = 0
lines = ifile.readlines()
for line in lines:
	line = line.split()
	if(line[0] == "Running"):
		Lumi = float( line[2])	
	if(line[0] == '*'):
		if(line[2] =='cut'):
			CUT = line[3:]
			break

print CUT
ifile.close()
ifile = open(ifilename,"r")

list2f = ['BHAg','ZHAD', 'ZL']
list4f = ['WL','ZEEL','ZNUL', 'ZNUS', 'WWHAD','WWL','ZZHAD','ZZL','ZZS', 'ZWML', 'ZZWWH', 'ZZWWL']
list6f = ['EEWW', 'LLWW', 'TTB', 'VVWW','XXWW', 'XXZ', 'YYZ']
listH = ['EEH', 'MUH', 'TAUH', 'QQH', 'NNH']
listS = ['WS', 'WWS']

count2f = [0.] * len(CUT)
count4f = [0.] * len(CUT)
count6f = [0.] * len(CUT)
countH = [0.] * len(CUT)
countS = [0.] * len(CUT)
#keep also a set of non normalized numbers
#then we can calculate proper errors
#count2f
count2fmc = [0.] * len(CUT)
count4fmc = [0.] * len(CUT)
count6fmc = [0.] * len(CUT)
countHmc = [0.] * len(CUT)
countSmc = [0.] * len(CUT)
# need to include modified gen seperations

listWWS1=['WWS1']
listWWS2=['WWS2']
listWS1=['WS1']
listWSBG=['WSBG']
listWWS1BG=['WWS1BG']
listWWS2BG=['WWS2BG']

countWWS1 = [0.] * len(CUT)
countWWS2 = [0.] * len(CUT)
countWS1 =  [0.] * len(CUT)
countWSBG = [0.] * len(CUT)
countWWS1BG = [0.] * len(CUT)
countWWS2BG = [0.] * len(CUT)

countWWS1mc = [0.] * len(CUT)
countWWS2mc = [0.] * len(CUT)
countWS1mc = [0.] * len(CUT)
countWSBGmc = [0.] * len(CUT)
countWWS1BGmc = [0.] * len(CUT)
countWWS2BGmc = [0.] * len(CUT)

#parse file for wildcard
lines = ifile.readlines()
for line in lines:
	line = line.split()
	if(line[0] == '*'):
		#print line
		if(line[2] == 'tot'):
			counts = map(float, line[3:])
			#seprate tags
			tag = line[1]
			if tag in list2f:
				count2f = list(map(add,count2f,counts))
			if tag in list4f:
				count4f = list(map(add,count4f,counts))
			if tag in list6f:
				count6f = list(map(add,count6f,counts))
			if tag in listH:
				countH = list(map(add,countH,counts))
		#	if tag in listS:
				#countS = list(map(add,countS,counts))	
	
	if(line[0] == '$$'):
                #print line
                if(line[2] == 'tot'):
                        counts = map(float, line[3:])
                        #seprate tags
                        tag = line[1]
                        if tag in list2f:
                                count2fmc = list(map(add,count2fmc,counts))
                        if tag in list4f:
                                count4fmc = list(map(add,count4fmc,counts))
                        if tag in list6f:
                                count6fmc = list(map(add,count6fmc,counts))
                        if tag in listH:
                                countHmc = list(map(add,countHmc,counts))
                #       if tag in listS:
                                #countS = list(map(add,countS,counts))

print "pre gen corrections"
print count2f
print count4f
print count6f
print countH
print countS

#read a separate file for gen splitting
genfilename = sys.argv[2]
genfile = open( genfilename, "r")
lines = genfile.readlines()
for line in lines:
	line = line.split()
	if(line[0] == '*'):
		if(line[2] == 'tot'):
			counts = map(float, line[3:])
			tag = line[1]
			if tag in listWWS1:
				countWWS1 = list(map(add,countWWS1,counts))
			if tag in listWWS2:
				countWWS2 = list(map(add,countWWS2,counts))
			if tag in listWS1:
				print countWS1, counts
				countWS1 =  list(map(add,countWS1, counts))
			if tag in listWSBG:		
				countWSBG = list(map(add,countWSBG, counts))
			if tag in listWWS1BG:
				countWWS1BG = list(map(add,countWWS1BG,counts))
			if tag in listWWS2BG:
				countWWS2BG = list(map(add,countWWS2BG,counts))
			
	if(line[0] == '$$'):
                if(line[2] == 'tot'):
                        counts = map(float, line[3:])
                        tag = line[1]
                        if tag in listWWS1:
                                countWWS1mc = list(map(add,countWWS1mc,counts))
                        if tag in listWWS2:
                                countWWS2mc = list(map(add,countWWS2mc,counts))
                        if tag in listWS1:
                                #print countWS1, counts
                                countWS1mc =  list(map(add,countWS1mc, counts))
                        if tag in listWSBG:
                                countWSBGmc = list(map(add,countWSBGmc, counts))
                        if tag in listWWS1BG:
                                countWWS1BGmc = list(map(add,countWWS1BGmc,counts))
                        if tag in listWWS2BG:
                                countWWS2BGmc = list(map(add,countWWS2BGmc,counts))
	

#do corrections to WS
##countS = list(map(sub, countS, countWSBG))
#count4f = list(map(add, count4f, countWSBG))
countS = list(map(add,countS, countWWS1))
countS = list(map(add,countS, countWWS2))
countS = list(map(add,countS, countWS1))

countSmc = list(map(add,countSmc, countWWS1mc))
countSmc = list(map(add,countSmc, countWWS2mc))
countSmc = list(map(add,countSmc, countWS1mc))







print "corrections"
print countWWS1
print countWWS2
print countWS1
print countS
print count2f
print count4f
print count6f
print countH


samp = ['Prompt $\mu$','Prompt $e$','$\\tau$','Tot. Sig.','2f','4f','6f','Higgs']
ofilename = sys.argv[3]
ofile = open(ofilename,"w")
ofile.write(" \\begin{tabular}{");
for col in xrange(len(samp)+1):
	ofile.write("|p{0.08\\textwidth}|");
ofile.write("}\n")
ofile.write("\\hline \n   & ")
for i in xrange(len(samp)):
	if i == len(samp)-1 :
		ofile.write(samp[i] + " \\\\ ")
	else:
		ofile.write(samp[i]+ " & ")
	
ofile.write("\\hline \n")
for i in xrange(len(CUT)):

	#ofile.write( CUT[i] +" & "+str(countS[i])+" & "+str(count2f[i])+" & "+str(count4f[i])+ " & " +str(count6f[i])+ " & "+str(countH[i]) + " \\\\ \n")
	ofile.write(CUT[i]+" &\\num{"+"{:.2e}".format(countWWS1[i])+" } & \\num{"+"{:.2e}".format(countWS1[i])+" } & \\num{"+"{:.2e}".format(countWWS2[i])+  "} &\\num{"+"{:.2e}".format(countS[i])+"} & \\num{"+ "{:.2e}".format(count2f[i]) +"} & \\num{"+"{:.2e}".format(count4f[i])+"} & \\num{"+ "{:.2e}".format(count6f[i])+"} & \\num{"+"{:.2e}".format(countH[i]) + "} \\\\ \n")
	ofile.write("\\hline \n")

ofile.write(" $\epsilon$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ &  ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ \\\\ \n".format(eff(countWWS1[-1],countWWS1[0]), efferr(countWWS1mc[-1],countWWS1mc[0]), eff(countWS1[-1],countWS1[0]), efferr(countWS1mc[-1],countWS1mc[0]), eff(countWWS2[-1],countWWS2[0]), efferr(countWWS2mc[-1],countWWS2mc[0]), eff(countS[-1],countS[0]), efferr(countSmc[-1],countSmc[0]), eff(count2f[-1],count2f[0]), efferr(count2fmc[-1],count2fmc[0]), eff(count4f[-1],count4f[0]), efferr(count4fmc[-1],count4fmc[0]), eff(count6f[-1],count6f[0]), efferr(count6fmc[-1],count6fmc[0]), eff(countH[-1],countH[0]), efferr(countHmc[-1],countHmc[0])))


#special off shell signal table
#consists of WWS1BG WWS2BG WSBG
samp2 = ['Prompt $\mu O.S.', 'Prompt e O.S.', 'Tau O.S.']

ofile.write(" \\begin{tabular}{");
for col in xrange(len(samp2)+1):
        ofile.write("|p{0.08\\textwidth}|");
ofile.write("}\n")
ofile.write("\\hline \n   & ")
for i in xrange(len(samp2)):
        if i == len(samp2)-1 :
                ofile.write(samp2[i] + " \\\\ ")
        else:
                ofile.write(samp2[i]+ " & ")

ofile.write("\\hline \n")
for i in xrange(len(CUT)):

        #ofile.write( CUT[i] +" & "+str(countS[i])+" & "+str(count2f[i])+" & "+str(count4f[i])+ " & " +str(count6f[i])+ " & "+str(countH[i]) + " \\\\ \n")
        ofile.write(CUT[i]+" &\\num{"+"{:.2e}".format(countWWS1BG[i])+" } & \\num{"+"{:.2e}".format(countWSBG[i])+" } & \\num{"+"{:.2e}".format(countWWS2BG[i])+  "}\\\\ \n")
        ofile.write("\\hline \n")

ofile.write(" $\epsilon$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ \\\\ \n".format(eff(countWWS1BG[-1],countWWS1BG[0]), efferr(countWWS1BGmc[-1],countWWS1BGmc[0]), eff(countWSBG[-1],countWSBG[0]), efferr(countWSBGmc[-1],countWSBGmc[0]), eff(countWWS2BG[-1],countWWS2BG[0]), efferr(countWWS2BGmc[-1],countWWS2BGmc[0])))



countAllBkg = [0.] * len(CUT)
countAllBkg = list(map(add,countAllBkg, count2f))
countAllBkg = list(map(add,countAllBkg, count4f))
countAllBkg = list(map(add,countAllBkg, count6f))
countAllBkg = list(map(add,countAllBkg, countH))


countALLOS = [0.] * len(CUT)
countALLOS = list(map(add, countALLOS, countWWS1BG))
countALLOS = list(map(add, countALLOS, countWWS1BG))
countALLOS = list(map(add, countALLOS, countWSBG))
countALLOSmc = [0.] * len(CUT)
countALLOSmc = list(map(add, countALLOSmc, countWWS1BGmc))
countALLOSmc = list(map(add, countALLOSmc, countWWS1BGmc))
countALLOSmc = list(map(add, countALLOSmc, countWSBGmc))

countALLS_noOS = [0.] *len(CUT)
countALLS_noOS = list(map(add, countALLS_noOS, countWWS1))
countALLS_noOS = list(map(add, countALLS_noOS, countWWS2))
countALLS_noOSmc = [0.] *len(CUT)
countALLS_noOSmc = list(map(add, countALLS_noOSmc, countWWS1mc))
countALLS_noOSmc = list(map(add, countALLS_noOSmc, countWWS2mc))



countALLS_withOS = [0.] *len(CUT)
countALLS_withOS = list(map(add, countALLS_withOS, countALLS_noOS))
countALLS_withOS = list(map(add, countALLS_withOS, countALLOS))
countALLS_withOSmc = [0.] *len(CUT)
countALLS_withOSmc = list(map(add, countALLS_withOSmc, countALLS_noOSmc))
countALLS_withOSmc = list(map(add, countALLS_withOSmc, countALLOSmc))



purity_noOS = countALLS_noOS[-1]/(countALLS_noOS[-1]+countAllBkg[-1])

purity_withOS = countALLS_withOS[-1]/(countALLS_withOS[-1]+countAllBkg[-1])
ofile.write("--------------\n")
ofile.write(" ** allBG "+str(countAllBkg[-1])+" "+str(countAllBkg[0])+ " "+str(countAllBkg[-1]/countAllBkg[0]) + "\n") #num den eff
ofile.write(" ** S "+str(countALLS_noOS[-1])+" "+str(countALLS_noOS[0])+ " "+str(countALLS_noOS[-1]/countALLS_noOS[0]) +" "+str(purity_noOS)+ "\n") #num den eff purity
ofile.write(" ** OS "+str(countALLOS[-1])+" "+str(countALLOS[0])+ " "+str(countALLOS[-1]/countALLOS[0]) + "\n")  #num den eff
ofile.write(" ** SOS  "+str(countALLS_withOS[-1])+" "+str(countALLS_withOS[0])+ " "+str(countALLS_withOS[-1]/countALLS_withOS[0]) +" "+str(purity_withOS)+ "\n")
#write out eff errors
ofile.write(" ** Serr "+str(efferr(countALLS_noOSmc[-1],countALLS_noOSmc[0]))+" \n")
ofile.write(" ** OSerr "+str(efferr(countALLOSmc[-1],countALLOSmc[0]))+" \n")
ofile.write(" ** SOSerr "+str(efferr(countALLS_withOSmc[-1],countALLS_withOSmc[0]))+" \n")
ofile.write(" ** LUMI "+str(Lumi)+"\n")
ofile.write(" ** NSOS "+str(countALLS_withOS[-1])+" \n")

totaleffs = eff(countALLS_withOS[-1],countALLS_withOS[0])
totaleffserr = efferr(countALLS_withOSmc[-1], countALLS_withOSmc[0])
totalNs = float(countALLS_withOS[-1])
sosxsec = totalNs/(Lumi * totaleffs)
sosxsecerr = math.sqrt(     (sosxsec/totaleffs)**2 * (totaleffserr)**2 )
ofile.write(" ** xsecSOS "+str(sosxsec)+" "+str(sosxsecerr)+"\n")

