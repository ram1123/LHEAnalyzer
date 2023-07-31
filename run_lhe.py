"""
Help:
This script will run using python3.
Run using: python3 run_lhe.py
"""

import glob
import os
import sys
from condor_helper import condor_jdl, condor_sh, make_directory, RemoveFile


def compile_analyzer():
    print("Compile the LHEanalyzer...")
    os.system('c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp')
    print("Compilation done...\n")


def setup_condor(year):
    make_directory(f'output/{year}')
    with open(f"condor_job_{year}.jdl", "w") as cnd_out:
        cnd_out.write(condor_jdl.format(year=year))
    with open(f"run_script_{year}.sh", "w") as scriptfile:
        scriptfile.write(condor_sh)
    RemoveFile(f'arguments_{year}.txt')


def process_files(input_dict, year, condor=True):
    OUTPUTPATH = "./"

    for file_key, file_value in input_dict.items():
        print("*" * 5, file_key)
        print("*" * 5, file_value)

        output_path = f"{OUTPUTPATH}/{file_key}"
        make_directory(output_path)

        n_files_to_run = len(glob.glob(file_value))

        print(f"Running on files: 1/{n_files_to_run}\n")

        if not condor:
            hadd_command = f'hadd -f {output_path}/{file_key}_{n_files_to_run}.root'

        local_dir = os.getcwd()
        print(f'PWD: {local_dir}')

        for count, file in enumerate(glob.glob(file_value, recursive=True), start=1):
            print("=" * 51)
            print(f"Running on file: {count}/{n_files_to_run}\n")

            output_file = file.split('/')[-1].replace('.lhe', '.root')
            if not condor:
                hadd_command += f'{output_path}/{output_file}'
            command = f'./LHEanalyzer {file} {output_path}/{output_file}'

            # Execute the command
            if not condor:
                os.system(command)

            if condor:
                with open(f"arguments_{year}.txt", "a") as in_arg_file:
                    in_arg_file.write(f"{file}  {local_dir}  {output_path}  {output_file}\n")

        if not condor:
            print(hadd_command)
            os.system(hadd_command)


def main():
    if sys.version_info[0] < 3:
        print("This script requires Python 3. Please use Python 3 to run this script.")
        sys.exit()

    compile_analyzer()

    INPUT_FILES = {
        # 'output_hadd_WpWmToLpNujj_mWV-150to600': '/eos/user/a/anmehta/WpWmToLpNujj_01j_aTGC_pTW-150toInf_mWV-150to600_4f_NLO_FXFX/*.lhe',
        # 'output_hadd_WpWmToLpNujj_mWV-600to800': '/eos/user/a/anmehta/WpWmToLpNujj_01j_aTGC_pTW-150toInf_mWV-600to800_4f_NLO_FXFX/*.lhe',
        # 'output_hadd_WpWmToLpNujj_mWV-800toInf': '/eos/user/a/anmehta/WpWmToLpNujj_01j_aTGC_pTW-150toInf_mWV-800toInf_4f_NLO_FXFX/*.lhe',
        'output_tvvj': "tvvj_all_decayed.lhe"
    }

    YEAR = "2018"
    ifCondor = False

    if ifCondor: setup_condor(YEAR)
    process_files(INPUT_FILES, YEAR, ifCondor)

    if ifCondor:
        print('For running condor jobs do the following:')
        print('1. Set up proxy:')
        print('\nvoms-proxy-init --voms cms --valid 168:00')
        print('2. Submit the condor jobs:')
        print(f"\ncondor_submit condor_job_{YEAR}.jdl")


if __name__ == "__main__":
    main()
