#echo "c++ -o anaPhantom `root-config --glibs --cflags` anaPhantom.cpp"
echo "Compiling anaPhantom.cpp.................."
c++ -o anaPhantom `root-config --glibs --cflags` anaPhantom.cpp
echo "Done Compilation."
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LL/Events/run_01/wplepwmhad_LL.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_LL.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LL/Events/run_01/wplepwmhad_LL.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_LL.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LL/Events/run_01/wphadwmlep_LL.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_LL.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LL/Events/run_01/wphadwmlep_LL.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_LL.root
echo "Removing /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_LL.root file"
rm /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_LL.root
echo "Adding lhe_wplepwmhad_LL.root and lhe_wphadwmlep_LL.root using hadd command"
hadd /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_LL.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_LL.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_LL.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LT/Events/run_01/wplepwmhad_LT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_LT.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LT/Events/run_01/wplepwmhad_LT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_LT.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LT/Events/run_01/wphadwmlep_LT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_LT.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_LT/Events/run_01/wphadwmlep_LT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_LT.root
echo "Removing lhe_LT.root"
rm /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_LT.root
echo "Adding lhe_wplepwmhad_LT.root and lhe_wphadwmlep_LT.root using hadd command"
hadd /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_LT.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_LT.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_LT.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_TT/Events/run_01/wplepwmhad_TT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_TT.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_TT/Events/run_01/wplepwmhad_TT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_TT.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_TT/Events/run_01/wphadwmlep_TT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_TT.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_TT/Events/run_01/wphadwmlep_TT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_TT.root
echo "Removing lhe_TT.root"
rm /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_TT.root
echo "Adding lhe_wplepwmhad_TT.root and lhe_wphadwmlep_TT.root through hadd command"
hadd /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_TT.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_TT.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_TT.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_TOT/Events/run_01/wplepwmhad_TOT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_TOT.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop/Events/run_01/wplepwmhad_TOT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_TOT.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop_TOT/Events/run_01/wphadwmlep_TOT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_TOT.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/pp_WWJJ_notop/Events/run_01/wphadwmlep_TOT.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_TOT.root
echo "Removing lhe_TOT.root"
rm /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_TOT.root
echo "Adding lhe_wplepwmhad_TOT.root and lhe_wphadwmlep_TOT.root using hadd command"
hadd /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_TOT.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wplepwmhad_TOT.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_wphadwmlep_TOT.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1/gen4jmu+v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mupv.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1/gen4jmu+v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mupv.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1/gen4jmu-v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mumv.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1/gen4jmu-v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mumv.root
echo "Removing lhe_Phantom.root"
rm /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_Phantom.root
echo "Adding lhe_Phantom_mupv.root and lhe_Phantom_mumv.root through hadd command"
hadd /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_Phantom.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mupv.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mumv.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1_qcd/gen4jmu+v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mupv_qcd.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1_qcd/gen4jmu+v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mupv_qcd.root
echo "./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1_qcd/gen4jmu-v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mumv_qcd.root"
./anaPhantom /eos/uscms/store/user/rasharma/lhe_files/POLARIZED_Samples/gen_126_scale1_qcd/gen4jmu-v/total.lhe /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mumv_qcd.root
echo "Removing /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_qcd.root"
rm /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_Phantom_qcd.root
echo "Adding /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mupv_qcd.root and /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mumv_qcd.root through hadd command"
hadd /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/merged/lhe_Phantom_qcd.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mupv_qcd.root /eos/uscms/store/user/rasharma/LHE_outputs/ppWW_8TeV_150k/lhe_Phantom_mumv_qcd.root
