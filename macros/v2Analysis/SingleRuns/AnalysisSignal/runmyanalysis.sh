

#input is: num files, numthreads,  yourdata.list, Treename, DataTag (A unique identifier for a specific dataset), outputfile name, outputfile option
#0 is all files, optimal threads is 8 at t3.unl

# last three inputs are Pe- Pe+ and luminosity fb-1 for (Pe-,Pe+) scenario
python runmacro.py 0 8 "datalists/4f_singleW_semileptonic.list" "tree" "WS1" "$1" "$2" "$3"  "RECREATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_singleW_semileptonic.list" "tree" "WSBG" "$1" "$2" "$3"  "UPDATE" "$4" "$5" "$6"


python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS1" "$1" "$2" "$3"   "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS2" "$1" "$2" "$3"   "UPDATE" "$4" "$5" "$6"

python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS1BG" "$1" "$2" "$3"   "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS2BG" "$1" "$2" "$3"   "UPDATE" "$4" "$5" "$6"












