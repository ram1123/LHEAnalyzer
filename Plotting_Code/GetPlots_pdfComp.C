/*
 * Compare Root Files
 *
 */
{
 gROOT->Reset();

 gROOT->ProcessLine(".L CompareAdvanced.C");

//const string Cut = "(abs(Lep1_eta)<2.5) && (abs(Lep0_eta)<2.5) && (Lep0_pt>20) && (Lep1_pt>20) && (Wqrk1_pt>10) && (Wqrk0_pt>10) && (Iqrk0_pt>10) && (Iqrk1_pt>10) && (mjj > 500.) && (Iqrk1_eta-Iqrk0_eta > 4.0) ";
const string Cut = " (Iqrk0_pt>30) && (Iqrk1_pt>30) && (Iqrk0_eta<4.5) && (Iqrk1_eta<4.5) && (Iqrk1_eta-Iqrk0_eta > 4.0) && (Iqrk1_eta*Iqrk0_eta*cos(Iqrk1_theta-Iqrk1_theta)<0) && (Wqrk1_pt>20) && (Wqrk0_pt>20) && (Wqrk1_E>50) && (Wqrk0_E > 50) && (mjj > 500) && (Lep0_pt>20) && (Lep1_pt>20) && (abs(Lep1_eta)<2.5) && (abs(Lep0_eta)<2.5) && (abs((Wqrk0_E+Wqrk1_E) - 80.385) <25)";//  && (abs((Lep0_E+Lep1_E) - 80.385) < 15)" ;

//const string Cut = "";
// TCanvas *Canvas1 = new TCanvas("Canvas1","example",600,700);
 TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);

/*
compareQuantities( 1, 0, 0, "","","",30,-1.,1.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/../pp_WWJJ_LL_cteq.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "_pdf.pdf");
Canvas1->Clear();

*/
compareQuantities( 1, 0, 0, "Lep1_eta-Iqrk0_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L1Q0_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep1_eta-Iqrk1_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L1Q1_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep1_eta-Wqrk0_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L1W0_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep1_eta-Wqrk1_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L1W1_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep0_eta-Iqrk0_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L0Q0_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep0_eta-Iqrk1_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L0Q1_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep0_eta-Wqrk0_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L0W0_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep0_eta-Wqrk1_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L0W1_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Lep0_eta-Lep1_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "L0L1_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Wqrk0_eta-Iqrk1_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "W0Q1_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Wqrk0_eta-Iqrk0_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "W0Q0_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Wqrk1_eta-Iqrk0_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "W1Q0_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Wqrk1_eta-Iqrk1_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "W1Q1_D_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Wqrk1_eta-Wqrk0_eta","","",30,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "WJet_Delta_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0, "Iqrk1_eta-Iqrk0_eta","","",30,0.,12.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs( "TagJet_Delta_eta_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"(Wqrk1_pt * Wqrk0_pt * cos(Wqrk1_theta-Wqrk1_theta))/(Iqrk1_pt*Iqrk0_pt* cos(Iqrk1_theta-Iqrk0_theta))","","R",30,-4.,4.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("Rvar_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"(Wqrk1_pt-Wqrk0_pt)/(Wqrk1_pt+Wqrk0_pt)","","",30,-1.,1.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("AssymetryWJetPt_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"(Wqrk1_pt-Wqrk0_pt)/(Wqrk1_pt+Wqrk0_pt)","","",30,-1.,1.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("AssymetryWJetPt_pdf.pdf");
Canvas1->Clear();


compareQuantities( 1, 0, 0,"(Iqrk1_pt-Iqrk0_pt)/(Iqrk1_pt+Iqrk0_pt)","","",30,-1.,1.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("AssymetryJetPt_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"Wqrk0_eta-((Iqrk1_eta+Iqrk0_eta)/2)","","",20,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("Zeppenfeld0_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"Wqrk1_eta-((Iqrk1_eta+Iqrk0_eta)/2)","","",20,-8.,8.,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("Zeppenfeld1_pdf.pdf");
Canvas1->Clear();


compareQuantities( 1, 0, 0,"mjj","","",20,0,5000,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("mjj_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"mWW","","",20,100,1000 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("mWW_pdf.pdf");
Canvas1->Clear();
compareQuantities( 1, 0, 0,"mWLep","","",20,70 ,90 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("mWLep_pdf.pdf");
Canvas1->Clear();
compareQuantities( 1, 0, 0,"mWHad","","",20,70 ,90 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("mWHad_pdf.pdf");
Canvas1->Clear();
compareQuantities( 1, 0, 0,"costheta1","","",20,-1. ,1. ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("costheta1_pdf.pdf");
Canvas1->Clear();
compareQuantities( 1, 0, 0,"costheta2","","",20,-1 ,1 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("costheta2_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"costhetastar","","",20,-1 ,1 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("costhetastar_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"costhetaV1","","",20,-3.5 ,3.5 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("costhetaV1_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"costhetaV2","","",20,-3.5 ,3.5 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("costhetaV2_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"costhetaV3","","",20,-3.5 ,3.5 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("costhetaV3_pdf.pdf");
Canvas1->Clear();

compareQuantities( 1, 0, 0,"costhetaV4","","",20,-3.5 ,3.5 ,Cut,2,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("costhetaV4_pdf.pdf");
Canvas1->Clear();


/*
compareQuantities( 1, 0, 0,"","","","",20, , ,"","",4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL_nn23lo1","../pp_WWJJ_LL_cteq.root","LL_cteq6l1");
Canvas1->SaveAs("_pdf.pdf");
Canvas1->Clear();
*/
// compareQuantities( 1, 0, 0,"mjj","","",20,0,500,"","",4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL_nn23lo1","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL_nn23lo1","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root","TOT");
 //compareQuantities( 1, 0, 0,0,1,"mjj","","",20,0,500,"","",4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL_nn23lo1","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL_nn23lo1","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root","TOT");



}
