

#input is: num files, numthreads,  yourdata.list, Treename, DataTag (A unique identifier for a specific dataset), outputfile name, outputfile option
#0 is all files, optimal threads is 8 at t3.unl

#1= selection mode "TIGHT or LOOSE"
#2 = cutlist file
#3 = outputfile name
# last three inputs are Pe- Pe+ and luminosity fb-1 for (Pe-,Pe+) scenario
 python runmacro.py 0 8 "datalists/2f_Z_bhabhag.list" "tree" "BHAg" "$1" "$2" "$3" "RECREATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/2f_Z_hadronic.list" "tree" "ZHAD" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/2f_Z_leptonic.list" "tree" "ZL" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_singleW_leptonic.list" "tree" "WL" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_singleW_semileptonic.list" "tree" "WS" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_singleZee_leptonic.list" "tree" "ZEEL" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_singleZee_semileptonic.list" "tree" "ZEES" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_singleZnunu_leptonic.list" "tree" "ZNUL" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_singleZnunu_semileptonic.list" "tree" "ZNUS" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_WW_hadronic.list" "tree" "WWHAD" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"

python runmacro.py 0 8 "datalists/4f_WW_leptonic.list" "tree" "WWL" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_ZZ_hadronic.list" "tree" "ZZHAD" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_ZZ_leptonic.list" "tree" "ZZL" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_ZZ_semileptonic.list" "tree" "ZZS" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"

python runmacro.py 0 8 "datalists/eeH.list" "tree" "EEH" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/mumuH.list" "tree" "MUH" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/tautauH.list" "tree" "TAUH" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/qqH.list" "tree" "QQH" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/nunuH.list" "tree" "NNH" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"

python runmacro.py 0 8 "datalists/4f_singleZsingleWMix_leptonic.list" "tree" "ZWML" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_ZZWWMix_hadronic.list" "tree" "ZZWWH" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/4f_ZZWWMix_leptonic.list" "tree" "ZZWWL" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/6f_eeWW.list" "tree" "EEWW" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/6f_llWW.list" "tree" "LLWW" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/6f_ttbar.list" "tree" "TTB" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/6f_vvWW.list" "tree" "VVWW" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/6f_xxWW.list" "tree" "XXWW" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/6f_xxxxZ.list" "tree" "XXZ" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"
python runmacro.py 0 8 "datalists/6f_yyyyZ.list" "tree" "YYZ" "$1" "$2" "$3" "UPDATE" "$4" "$5" "$6"








