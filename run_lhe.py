# ```Help:
# This script will run using python3.
# python3 run_lhe.py
# ```
import glob
import os
import sys

ifRunAllFiles = sys.argv[1]

print("Compile the LHEanalyzer...")
os.system('c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp')
print("compilation done...\n")

InputFiles = {
    'output_hadd_150to600_4f_NLO_FXFX_2.root':  '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-150to600_4f_NLO_FXFX/*.lhe',
    'output_hadd_600to800_4f_NLO_FXFX_2.root': '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-600to800_4f_NLO_FXFX/*.lhe',
    'output_hadd_800toInf_4f_NLO_FXFX_2.root': '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-800toInf_4f_NLO_FXFX/*.lhe'
}

for files in InputFiles:
    print("*"*5,files)
    print("*"*5,InputFiles[files])

    if str(ifRunAllFiles) == "n":
        # nFilesToRun = sum(1 for _ in os.scandir(InputFiles[files]) if _.is_file())
        nFilesToRun = len(glob.glob(InputFiles[files]))
    # elif ifRunAllFiles == "":
        # nFilesToRun = 1
    else:
        nFilesToRun = int(ifRunAllFiles)

    print (nFilesToRun, ifRunAllFiles)

    # Remove all unwanted files
    os.system('rm -f cmsgrid_final_seed*.root')

    count = 1

    # hadd command to hadd root files. Below command the 'files' is the name of output file
    haddCommand = 'hadd -f  '+files.replace('_2','_'+str(nFilesToRun))
    for file in glob.glob(InputFiles[files],recursive=True):
        if count > nFilesToRun: break
        print("="*51)
        print("Running on file : {}/{}\n".format(count,nFilesToRun))
        outputFile = (file.split('/')[-1]).replace('.lhe','.root')
        haddCommand += ' '+outputFile
        command = './LHEanalyzer {inputFile} {outputFile}'.format(inputFile = file, outputFile=outputFile)
        print(command)
        os.system(command)
        count += 1

    print(haddCommand)
    # os.system(haddCommand)

    # Delete each files after run
    os.system('rm -f cmsgrid_final_seed*.root')
