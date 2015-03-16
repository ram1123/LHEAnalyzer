/*
 * Compare Root Files
 *
 */
{
 gROOT->Reset();

 gROOT->ProcessLine(".L CompareAdvanced.C");

 const string Cut = "(abs(Lep1_eta)<2.5) && (abs(Lep0_eta)<2.5) && (Lep0_pt>20) && (Lep1_pt>20) && (Wqrk1_pt>10) && (Wqrk0_pt>10) && (Iqrk0_pt>10) && (Iqrk1_pt>10) && (mjj > 500.) && (Iqrk1_eta-Iqrk0_eta > 4.0) ";

// TCanvas *Canvas1 = new TCanvas("Canvas1","example",600,700);
 TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);

/*
compareQuantities( "","","",30,-1.,1.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( ".pdf");
Canvas1->Clear();

*/
compareQuantities( "Lep1_eta-Iqrk0_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L1Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep1_eta-Iqrk1_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L1Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep1_eta-Wqrk0_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L1W0_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep1_eta-Wqrk1_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L1W1_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep0_eta-Iqrk0_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L0Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep0_eta-Iqrk1_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L0Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep0_eta-Wqrk0_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L0W0_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep0_eta-Wqrk1_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L0W1_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Lep0_eta-Lep1_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "L0L1_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Wqrk0_eta-Iqrk1_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "W0Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Wqrk0_eta-Iqrk0_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "W0Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Wqrk1_eta-Iqrk0_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "W1Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Wqrk1_eta-Iqrk1_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "W1Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities( "Wqrk1_eta-Wqrk0_eta","","",30,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "WJet_Delta_eta.pdf");
Canvas1->Clear();

compareQuantities( "Iqrk1_eta-Iqrk0_eta","","",30,0.,12.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs( "TagJet_Delta_eta.pdf");
Canvas1->Clear();

compareQuantities("(Wqrk1_pt * Wqrk0_pt * cos(Wqrk1_theta-Wqrk1_theta))/(Iqrk1_pt*Iqrk0_pt* cos(Iqrk1_theta-Iqrk0_theta))","","R",30,-4.,4.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("Rvar.pdf");
Canvas1->Clear();

compareQuantities("(Wqrk1_pt-Wqrk0_pt)/(Wqrk1_pt+Wqrk0_pt)","","",30,-1.,1.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("AssymetryWJetPt.pdf");
Canvas1->Clear();

compareQuantities("(Wqrk1_pt-Wqrk0_pt)/(Wqrk1_pt+Wqrk0_pt)","","",30,-1.,1.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("AssymetryWJetPt.pdf");
Canvas1->Clear();


compareQuantities("(Iqrk1_pt-Iqrk0_pt)/(Iqrk1_pt+Iqrk0_pt)","","",30,-1.,1.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("AssymetryJetPt.pdf");
Canvas1->Clear();

compareQuantities("Wqrk0_eta-((Iqrk1_eta+Iqrk0_eta)/2)","","",20,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("Zeppenfeld0.pdf");
Canvas1->Clear();

compareQuantities("Wqrk1_eta-((Iqrk1_eta+Iqrk0_eta)/2)","","",20,-8.,8.,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("Zeppenfeld1.pdf");
Canvas1->Clear();


compareQuantities("mjj","","",20,0,5000,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("mjj.pdf");
Canvas1->Clear();

compareQuantities("mWW","","",20,100,1000 ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("mWW.pdf");
Canvas1->Clear();
compareQuantities("mWLep","","",20,70 ,90 ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("mWLep.pdf");
Canvas1->Clear();
compareQuantities("mWHad","","",20,70 ,90 ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("mWHad.pdf");
Canvas1->Clear();
compareQuantities("costheta1","","",20,-1. ,1. ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("costheta1.pdf");
Canvas1->Clear();
compareQuantities("costheta2","","",20,-1 ,1 ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("costheta2.pdf");
Canvas1->Clear();

compareQuantities("costhetastar","","",20,-1 ,1 ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("costhetastar.pdf");
Canvas1->Clear();

compareQuantities("costhetaV1","","",20,-1. ,1. ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("costhetaV1.pdf");
Canvas1->Clear();

compareQuantities("costhetaV2","","",20,-1. ,1. ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("costhetaV2.pdf");
Canvas1->Clear();

compareQuantities("costhetaV3","","",20,-1. ,1. ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("costhetaV3.pdf");
Canvas1->Clear();

compareQuantities("costhetaV4","","",20,-1. ,1. ,Cut,4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs("costhetaV4.pdf");
Canvas1->Clear();



/*
compareQuantities("","","","",20, , ,"","",4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT.root","TOT");
Canvas1->SaveAs(".pdf");
Canvas1->Clear();
*/
// compareQuantities("mjj","","",20,0,500,"","",4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpHadwmLep.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root","TOT");
 //compareQuantities(0,1,"mjj","","",20,0,500,"","",4,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpHadwmLep.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root","TOT");



}
