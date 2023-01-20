LHEAnalyzers
============

**To compile:**

```bash
c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp

./LHEanalyzer /eos/user/a/anmehta/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-150to600_4f_NLO_FXFX/cmsgrid_final_seed7898675.lhe cmsgrid_final_seed7898675.root
```


**To run:**

```bash
./LHEanalyzer  /path/of/inputFile.lhe   /path/of/outputfile/filename.root
```

**Location of files to run on:**

/eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples



Location of output files go into 'plotting'.  Inside of 'plotting' dir you can find a small script for plotting the output.  This can obviously be modified to make the plots you would like.


**To Read Root File created by the ExRootAnalysis Use the code ReadLHE.C & ReadLHE.h**
