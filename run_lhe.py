# ```Help:
# This script will run using python3.
# python3 run_lhe.py
# ```
import glob
import os
import sys
from condor_helper import condor_jdl, condor_sh, make_directory, RemoveFile

if sys.version_info[0] < 3:
    print("This script requires Python 3. Please use Python 3 to run this script.")
    sys.exit()

print("Compile the LHEanalyzer...")
os.system('c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp')
print("compilation done...\n")

OUTPUTPATH = "/eos/user/r/rasharma/post_doc_ihep/aTGC/LHEAnalyzer"
ifCondor = True
InputFiles = {
    'output_hadd_150to600_4f_NLO_FXFX':  '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-150to600_4f_NLO_FXFX/*.lhe',
    'output_hadd_600to800_4f_NLO_FXFX': '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-600to800_4f_NLO_FXFX/*.lhe',
    'output_hadd_800toInf_4f_NLO_FXFX': '/eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-800toInf_4f_NLO_FXFX/*.lhe',
    'output_hadd_600to800_4f_NLO_FXFX_NEW': '/eos/user/a/anmehta/gridpacks_cutchks/WWToLNujj_01j_aTGC_pTW-150toInf_mWV-600to800_4f_NLO_FXFX/*.lhe'
}

year = "final_v2"

make_directory('output/{}'.format(year))
with open("condor_job_{}.jdl".format(year), "w") as cnd_out:
    cnd_out.write(condor_jdl.format(year = year))
with open("run_script_{}.sh".format(year), "w") as scriptfile:
    scriptfile.write(condor_sh)

RemoveFile('arguments_{}.txt'.format(year)) # Delete old argument files as the main script will append.

for files in InputFiles:
    print("*"*5,files)
    print("*"*5,InputFiles[files])

    OutputPath = OUTPUTPATH + '/' + files
    make_directory(OutputPath)

    # Decide over how many .lhe file we need to run
    if (not ifCondor):
        if len(sys.argv) < 2:
            print("No argument given, so it will take default number of files to run with. ")
            nFilesToRun = 1
        elif sys.argv[1] == "n":
            # nFilesToRun = sum(1 for _ in os.scandir(InputFiles[files]) if _.is_file())
            nFilesToRun = len(glob.glob(InputFiles[files]))
        else:
            nFilesToRun = sys.argv[1]
    else:
        nFilesToRun = len(glob.glob(InputFiles[files]))

    # Remove all unwanted files
    # os.system('rm -f cmsgrid_final_seed*.root')

    count = 1
    print("Running on file : {}/{}\n".format(count,count))
    # hadd command to hadd root files. Below command the 'files' is the name of output file
    if not ifCondor:
        haddCommand = 'hadd -f  '+files + '_' + str(nFilesToRun) + '.root'
    for file in glob.glob(InputFiles[files],recursive=True):
        print("="*51)
        print("Running on file : {}/{}\n".format(count,nFilesToRun))
        if count > int(nFilesToRun):
            print("As nFiles > {}, breaking the loop".format(nFilesToRun))
            break
        outputFile = (file.split('/')[-1]).replace('.lhe','.root')
        if not ifCondor: haddCommand += ' '+outputFile
        command = './LHEanalyzer {inputFile} {outputFile}'.format(inputFile = file, outputFile=outputFile)
        # print(command)

        LocalDir = os.getcwd()
        print('PWD: {}'.format(LocalDir))
        with open("arguments_{}.txt".format(year), "a") as inArgFile:
            inArgFile.write("{inputFile}  {LOCAL}  {outputPath}  {OutputFile}\n".format(inputFile = file, LOCAL = LocalDir, outputPath=OutputPath, OutputFile = outputFile))

        # os.system(command)
        count += 1

    if not ifCondor: print(haddCommand)
    # os.system(haddCommand)

# Delete each files after run
# os.system('rm -f cmsgrid_final_seed*.root')

if ifCondor:
    print('For running condor jobs do following:')
    print('1. set up proxy:')
    print('\nvoms-proxy-init --voms cms --valid 168:00')
    print('2. Submit the condor jobs:')
    print("\ncondor_submit condor_job_{}.jdl".format(year))
