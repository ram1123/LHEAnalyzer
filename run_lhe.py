# ```Help:
# This script will run using python3.
# python3 run_lhe.py
# ```
import glob
import os

path = '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-150to600_4f_NLO_FXFX/*.lhe'
haddCommand = 'hadd -f output_hadd_150to600_4f_NLO_FXFX_10.root '

# path = '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-600to800_4f_NLO_FXFX/*.lhe'
# haddCommand = 'hadd -f output_hadd_600to800_4f_NLO_FXFX.root '

# path = '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-800toInf_4f_NLO_FXFX/*.lhe'
# haddCommand = 'hadd -f output_hadd_800toInf_4f_NLO_FXFX.root '

print("Compile the LHEanalyzer...")
os.system('c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp')
print("compilation done...\n")

count = 1
for file in glob.glob(path,recursive=True):
    print("="*51)
    if count > 10: break
    outputFile = (file.split('/')[-1]).replace('.lhe','.root')
    haddCommand += ' '+outputFile
    command = './LHEanalyzer {inputFile} {outputFile}'.format(inputFile = file, outputFile=outputFile)
    print(command)
    os.system(command)
    count += 1

print(haddCommand)
os.system(haddCommand)
