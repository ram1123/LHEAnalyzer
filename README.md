LHEAnalyzers
============

To compile:
c++ -o LHEanalyzer &#39; root-config --glibs --cflags &#39; LHEanalyzer.cpp

To run:
./LHEanalyzer  /path/of/inputFile.lhe   /path/of/outputfile/filename.root

Location of files to run on:
/eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples

Location of output files go into 'plotting'.  Inside of 'plotting' dir you can find a small script for plotting the output.  This can obviously be modified to make the plots you would like.
