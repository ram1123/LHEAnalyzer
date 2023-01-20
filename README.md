LHEAnalyzers
============

**To compile:**

```bash
c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp
```


**To run:**

```bash
./LHEanalyzer  /path/of/inputFile.lhe   /path/of/outputfile/filename.root
```

**Location of files to run on:**

/eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples



Location of output files go into 'plotting'.  Inside of 'plotting' dir you can find a small script for plotting the output.  This can obviously be modified to make the plots you would like.


**To Read Root File created by the ExRootAnalysis Use the code ReadLHE.C & ReadLHE.h**
