#echo "c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp"
echo "Compiling LHEanalyzer.cpp.................."
#c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp
c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer_ppzz.cpp
echo "Done Compilation."
#./LHEanalyzer /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/13TeVSample/pp_WWJJ_LL/NoPtEtaCut/unweighted_events_decayed_wpLepwmHad.lhe /eos/uscms/store/user/rasharma/WlWl_wpHadwmLep_NoptEtaCut.root
./LHEanalyzer /eos/uscms/store/user/rasharma/lhe_files/unweighted_events_decayed.lhe pp_zzjj.root 
