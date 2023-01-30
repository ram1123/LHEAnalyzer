import os

# Prepare condor jobs
condor_jdl = '''executable              = run_script_{year}.sh
output                  = output/{year}/strips.$(ClusterId).$(ProcId).out
error                   = output/{year}/strips.$(ClusterId).$(ProcId).out
log                     = output/{year}/strips.$(ClusterId).$(ProcId).out
transfer_input_files    = run_script_{year}.sh
on_exit_remove          = (ExitBySignal == False) && (ExitCode == 0)
periodic_release        = (NumJobStarts < 3) && ((CurrentTime - EnteredCurrentStatus) > (60*60))

+JobFlavour             = "espresso"
+AccountingGroup        = "group_u_CMS.CAF.ALCA"
queue arguments from arguments_{year}.txt
'''


condor_sh = '''#!/bin/sh -e
echo "Starting job on " `date`
echo "Running on: `uname -a`"
echo "System software: `cat /etc/redhat-release`"
INPUTFILE=$1;
LOCAL=$2;
OUTPUTPATH=$3;
OUTPUTFILE=$4
echo "Print arguments: "
echo "INPUTFILE: ${INPUTFILE}"
echo "LOCAL: ${LOCAL}"
echo "OUTPUTPATH: ${OUTPUTPATH}"
echo "OUTPUTFILE: ${OUTPUTFILE}"
echo "========="

echo "Print local path: `pwd`"
cd ${LOCAL}
echo "Print local path: `pwd`"
echo "Print local path: `pwd`"

eval `scramv1 ru -sh`
echo "========="
echo "./LHEanalyzer ${INPUTFILE} ${OUTPUTPATH}/${OUTPUTFILE}"
echo "========="
./LHEanalyzer ${INPUTFILE} ${OUTPUTPATH}/${OUTPUTFILE}
echo "========="

echo -e "DONE";
echo "Ending job on " `date`
'''

def make_directory( sub_dir_name):
    if not os.path.exists(sub_dir_name):
        print("{}{}\nCreate directory: {}".format('\t\n', '#'*51, sub_dir_name))
        os.makedirs(sub_dir_name)
    else:
        print('Directory '+sub_dir_name+' already exists. Exiting...')

def RemoveFile(FileName):
    if os.path.exists(FileName):
        os.remove(FileName)
    else:
        print("File, {}, does not exist".format(FileName))
