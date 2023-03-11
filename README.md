LHEAnalyzers
============

This tool is designed to analyze LHE (Les Houches Event) files and extract information from them. The output is a root file that contains histograms and other information that can be used for further analysis.


# Compiling & running
## Compiling
To compile the code, run the following command:

```bash
c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp
```

# Running
To run the code on a single LHE file, use the following command:

```bash
./LHEanalyzer  /path/of/inputFile.lhe   /path/of/outputfile/filename.root
```

To run the code on all LHE files present in a directory, use the following command:

```bash
python3 run_lhe.py
```

In the above script, you just need to update the path where the LHE files are present (also the output root file name) and run.

**Inside the plotting directory, you can find a small script for plotting the output. This can be modified to make the plots you would like.**

# ExRootAnalysis

To read the root file created by the `ExRootAnalysis`, use the code `ReadLHE.C` and `ReadLHE.h`.




