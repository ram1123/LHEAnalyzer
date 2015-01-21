#echo "c++ -o anaPhantom `root-config --glibs --cflags` anaPhantom.cpp"
echo "Compiling anaPhantom.cpp.................."
c++ -o anaPhantom `root-config --glibs --cflags` anaPhantom.cpp
echo "Done Compilation."
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/13TeVSample/ /eos/uscms/store/user/rasharma/LHE_outputs/13TeV/pp_WWJJ_TT/lhe_wplepwmhad_LL.root"
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/13TeVSample/pp_WWJJ_TOT/unweighted_events_decayed.lhe /eos/uscms/store/user/rasharma/LHE_outputs/13TeV/pp_WWJJ_TOT/lhe.root"
#./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/13TeVSample/pp_WWJJ_TOT/unweighted_events_decayed.lhe /eos/uscms/store/user/rasharma/LHE_outputs/13TeV/pp_WWJJ_TOT/lhe.root
#./anaPhantom /eos/usqcms/store/user/rasharma/lhe_files/POLARIZED_Samples/13TeVSample/unweighted_events.lhe TT_wphad_wmlep.root
#./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/13TeVSample/pp_WWJJ_LL/NoPtEtaCut/unweighted_events_decayed_wpLepwmHad.lhe /eos/uscms/store/user/rasharma/WlWl_wpHadwmLep_NoptEtaCut.root
