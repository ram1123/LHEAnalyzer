echo "Compiling LHEanalyzer.cpp.................."
#c++ -o LHEanalyzer `root-config --glibs --cflags` LHEanalyzer.cpp
echo "Done Compilation."
echo "Running the code... Present time $(date +"%T")"


#For Test
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpHadwmLep.lhe  pp_WWJJ_LL_wpHadwmLep.root

#For Run 

#pdf cteq 
./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/pdf_cteq/unweighted_events_decayed_WpHadWmLep.lhe pp_WWJJ_LL_WpHadWmLep_cteq.root
./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/pdf_cteq/unweighted_events_decayed_WpLepWmHad.lhe pp_WWJJ_LL_WpLepWmHad_cteq.root


#14TeV sample
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/14TeV/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe pp_WWJJ_LL_WpHadWmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/14TeV/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe pp_WWJJ_LL_WpLepWmHad.root

#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/  /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_ .root

#
##
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad5.lhe	pp_WWJJ_LL_WpLepWmHad5.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep5.lhe	pp_WWJJ_LL_WpHadWmLep5.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad6.lhe	pp_WWJJ_LL_WpLepWmHad6.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep6.lhe	pp_WWJJ_LL_WpHadWmLep6.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad7.lhe	pp_WWJJ_LL_WpLepWmHad7.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep7.lhe	pp_WWJJ_LL_WpHadWmLep7.root
##./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad4.lhe	pp_WWJJ_LL_WpLepWmHad4.root
##./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep4.lhe	pp_WWJJ_LL_WpHadWmLep4.root
##./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad3.lhe	pp_WWJJ_LL_WpLepWmHad3.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep3.lhe	pp_WWJJ_LL_WpHadWmLep3.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad2.lhe	pp_WWJJ_LL_WpLepWmHad2.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep2.lhe	pp_WWJJ_LL_WpHadWmLep2.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWpLep1.lhe	pp_WWJJ_LL_WpHadWmLep1.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad1.lhe	pp_WWJJ_LL_WpLepWmHad1.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	pp_WWJJ_LL_WpHadWmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	pp_WWJJ_LL_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpHadwmLep.lhe	pp_WWJJ_LL_wpHadwmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpLepwmHad.lhe	pp_WWJJ_LL_wpLepwmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LT/Default_Cut/unweighted_events_decayedwpLepwmHad.lhe	pp_WWJJ_LT_wpLepwmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LT/Default_Cut/unweighted_events_decayedwpHadwmLep.lhe	pp_WWJJ_LT_wpHadwmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TT/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	pp_WWJJ_TT_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TT/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	pp_WWJJ_TT_WpHadWmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TOT/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	pp_WWJJ_TOT_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TOT/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	pp_WWJJ_TOT_WpHadWmLep.root
echo "Job Completed... Present time $(date +"%T")"
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/  /eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_ .root
#
##
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad4.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpLepWmHad4.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep4.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpHadWmLep4.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad3.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpLepWmHad3.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep3.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpHadWmLep3.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad2.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpLepWmHad2.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep2.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpHadWmLep2.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWpLep1.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpHadWmLep1.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad1.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpLepWmHad1.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpHadWmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpHadwmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LL/Default_Cut/unweighted_events_decayed_wpLepwmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpLepwmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LT/Default_Cut/unweighted_events_decayedwpLepwmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpLepwmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_LT/Default_Cut/unweighted_events_decayedwpHadwmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpHadwmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TT/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TT/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpHadWmLep.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TOT/Default_Cut/unweighted_events_decayed_WpLepWmHad.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root
#./LHEanalyzer /eos/uscms/store/user/rasharma/WWScattering/lhefiles/pp_WWJJ_TOT/Default_Cut/unweighted_events_decayed_WpHadWmLep.lhe	/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpHadWmLep.root
#echo "Job Completed... Present time $(date +"%T")"
