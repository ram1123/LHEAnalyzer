echo "Compiling LHEanalyzer.cpp.................."
c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp
echo "Done Compilation."
echo "Running the code... Present time $(date +"%T")"


#For Test
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpHadwmLep.lhe  pp_WWJJ_LL_wpHadwmLep.root

#For Run 
./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWpLep1.lhe  /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpHadWmLep1.root
./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad1.lhe /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpLepWmHad1.root
./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe  /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpHadWmLep.root
./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe  /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpHadwmLep.lhe  /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpLepwmHad.lhe  /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpLepwmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LT/Default_Cut/unweighted_events_decayedwpLepwmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpLepwmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LT/Default_Cut/unweighted_events_decayedwpHadwmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpHadwmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TT/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TT/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpHadWmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TOT/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TOT/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpHadWmLep.root
echo "Job Completed... Present time $(date +"%T")"
