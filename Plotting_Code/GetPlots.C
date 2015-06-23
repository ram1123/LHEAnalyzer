/*
 * Compare Root Files
 *
 */
{
 gROOT->Reset();

 gROOT->ProcessLine(".L CompareAdvanced.C");

// const string Cut = "(abs(Lep1_eta)<2.5) && (abs(Lep0_eta)<2.5) && (Lep0_pt>20) && (Lep1_pt>20) && (Wqrk1_pt>10) && (Wqrk0_pt>10) && (Iqrk0_pt>10) && (Iqrk1_pt>10) && (mjj > 500.) && (Iqrk1_eta-Iqrk0_eta > 4.0) ";

//const string Cut = " (Iqrk0_pt>30) && (Iqrk1_pt>30) && (Iqrk0_eta<4.5) && (Iqrk1_eta<4.5) && (Iqrk1_eta-Iqrk0_eta > 4.0) && (Iqrk1_eta*Iqrk0_eta*cos(Iqrk1_theta-Iqrk1_theta)<0) && (Wqrk1_pt>20) && (Wqrk0_pt>20) && (Wqrk1_E>50) && (Wqrk0_E > 50) && (mjj > 500) && (Lep0_pt>20) && (Lep1_pt>20) && (abs(Lep1_eta)<2.5) && (abs(Lep0_eta)<2.5) && (abs((Wqrk0_E+Wqrk1_E) - 80.385) <25) && (abs((Lep0_E+Lep1_E) - 80.385) < 15)" ;

//const string Cut = "";

// TCanvas *Canvas1 = new TCanvas("Canvas1","example",600,700);
 TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);
//	LINE NUMBER 148 STARTS BASIC PLOTS
/* 
compareQuantities(1 , 0 , 1 , "sqrt(Lep1_pt*Lep1_pt+Lep0_pt*Lep0_pt+Lep0_pt*Lep1_pt*cos(Lep0_theta - Lep1_theta))","","",100,0,150,"",3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "test.pdf");
Canvas1->Clear();
 */
Canvas1->Divide(2,2);
Canvas1->cd(1);
compareQuantities(1 , 0 , 1 , "sqrt(Lep1_pt*Lep1_pt+Lep0_pt*Lep0_pt+Lep0_pt*Lep1_pt*cos(Lep0_theta - Lep1_theta))","","W_pt_WithoutCut",50,0.,150.,"",3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
//Canvas1->SaveAs( "W_pt_WithoutCut.pdf");
//Canvas1->Clear();

Canvas1->cd(2);
compareQuantities(1 , 0 , 1 , "sqrt(Lep1_pt*Lep1_pt+Lep0_pt*Lep0_pt+Lep0_pt*Lep1_pt*cos(Lep0_theta - Lep1_theta))","","W_pt_L0g10",50,0.,150.,"Lep0_pt>10",3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
//Canvas1->SaveAs( "W_pt_L0g10.pdf");
//Canvas1->Clear();

Canvas1->cd(3);
compareQuantities(1 , 0 , 1 , "sqrt(Lep1_pt*Lep1_pt+Lep0_pt*Lep0_pt+Lep0_pt*Lep1_pt*cos(Lep0_theta - Lep1_theta))","","W_pt_L1g10",50,0.,150.,"Lep1_pt>10",3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
//Canvas1->SaveAs( "W_pt_L1g10.pdf");
//Canvas1->Clear();

Canvas1->cd(4);
compareQuantities(1 , 0 , 1 , "sqrt(Lep1_pt*Lep1_pt+Lep0_pt*Lep0_pt+Lep0_pt*Lep1_pt*cos(Lep0_theta - Lep1_theta))","","W_pt_L0pL1g10",50,0.,150.,"(Lep0_pt+Lep1_pt) > 10",3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "W_pt_L0pL1g10.pdf");
Canvas1->Clear();

 

#if 0
compareQuantities(1 , 0 , 1 , "Lep1_eta-Iqrk0_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L1Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_eta-Iqrk1_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L1Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_eta-Wqrk0_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L1W0_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_eta-Wqrk1_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L1W1_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_eta-Iqrk0_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L0Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_eta-Iqrk1_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L0Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_eta-Wqrk0_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L0W0_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_eta-Wqrk1_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L0W1_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_eta-Lep1_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "L0L1_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_eta-Iqrk1_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "W0Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_eta-Iqrk0_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "W0Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_eta-Iqrk0_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "W1Q0_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_eta-Iqrk1_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "W1Q1_D_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_eta-Wqrk0_eta","","",30,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "WJet_Delta_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_eta-Iqrk0_eta","","",30,0.,12.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs( "TagJet_Delta_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"(Wqrk1_pt * Wqrk0_pt * cos(Wqrk1_theta-Wqrk1_theta))/(Iqrk1_pt*Iqrk0_pt* cos(Iqrk1_theta-Iqrk0_theta))","","R",30,-4.,4.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("Rvar.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"(Wqrk1_pt-Wqrk0_pt)/(Wqrk1_pt+Wqrk0_pt)","","",30,-1.,1.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("AssymetryWJetPt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"(Wqrk1_pt-Wqrk0_pt)/(Wqrk1_pt+Wqrk0_pt)","","",30,-1.,1.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("AssymetryWJetPt.pdf");
Canvas1->Clear();


compareQuantities(1 , 0 , 1 ,"(Iqrk1_pt-Iqrk0_pt)/(Iqrk1_pt+Iqrk0_pt)","","",30,-1.,1.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("AssymetryJetPt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"Wqrk0_eta-((Iqrk1_eta+Iqrk0_eta)/2)","","",20,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("Zeppenfeld0.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"Wqrk1_eta-((Iqrk1_eta+Iqrk0_eta)/2)","","",20,-8.,8.,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("Zeppenfeld1.pdf");
Canvas1->Clear();


compareQuantities(1 , 0 , 1 ,"mjj","","",20,0,5000,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("mjj.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"mWW","","",20,100,1000 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("mWW.pdf");
Canvas1->Clear();
compareQuantities(1 , 0 , 1 ,"mWLep","","",20,70 ,90 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("mWLep.pdf");
Canvas1->Clear();
compareQuantities(1 , 0 , 1 ,"mWHad","","",20,70 ,90 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("mWHad.pdf");
Canvas1->Clear();
compareQuantities(1 , 0 , 1 ,"costheta1","","",20,-1. ,1. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("costheta1.pdf");
Canvas1->Clear();
compareQuantities(1 , 0 , 1 ,"costheta2","","",20,-1 ,1 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("costheta2.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"costhetastar","","",20,-1 ,1 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("costhetastar.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"costhetaV1","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("costhetaV1.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"costhetaV2","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("costhetaV2.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"costhetaV3","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("costhetaV3.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 ,"costhetaV4","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs("costhetaV4.pdf");
Canvas1->Clear();



compareQuantities(1 , 0 , 1 , "dPhijj","","",20,0. ,4. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" dPhijj.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "dEtajj","","",20,0. ,10. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" dEtajj.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_px","","",20,-200. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_px.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_py","","",20,-200. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_py.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_pz","","",20,-1000. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_pz.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_E","","",20,0. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_E.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_px","","",20,-200. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_px.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_py","","",20,-200. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_py.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_pz","","",20,-1000. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_pz.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_E","","",20,0. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_E.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_px","","",20,-300. ,300. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_px.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_py","","",20,-300. ,300. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_py.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_pz","","",20,-1000. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_pz.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_E","","",20,0. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_E.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_px","","",20,-300. ,300. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_px.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_py","","",20,-300. ,300. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_py.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_pz","","",20,-1000. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_pz.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_E","","",20,0. ,1000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_E.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_px","","",20,-500. ,500. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_px.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_py","","",20,-500. ,500. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_py.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_pz","","",20,-3000. ,3000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_pz.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_E","","",20,0. ,3000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_E.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_px","","",20,-500. ,500. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_px.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_py","","",20,-500. ,500. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_py.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_pz","","",20,-3000. ,3000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_pz.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_E","","",20,0. ,3000. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_E.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_pt","","",20,0. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_pt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_eta","","",20,-6. ,6. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_pt","","",20,0. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_pt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_eta","","",20,-6. ,6. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_pt","","",20,0. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_pt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_eta","","",20,-6. ,6. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_pt","","",20,0. ,200. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_pt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_eta","","",20,-6. ,6. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_pt","","",20,0. ,400. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_pt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_eta","","",20,-6. ,6. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_pt","","",20,0. ,400. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_pt.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_eta","","",20,-6. ,6. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_eta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_phi","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_phi.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_phi","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_phi.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_phi","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_phi.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_phi","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_phi.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_phi","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_phi.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_phi","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_phi.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk1_theta","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk1_theta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Iqrk0_theta","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Iqrk0_theta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk1_theta","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk1_theta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Wqrk0_theta","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Wqrk0_theta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep1_theta","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep1_theta.pdf");
Canvas1->Clear();

compareQuantities(1 , 0 , 1 , "Lep0_theta","","",20,-3.5 ,3.5 ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" Lep0_theta.pdf");
Canvas1->Clear();


/*
dPhijj  dEtajj Lep0_px Lep0_py Lep0_pz Lep0_E Lep1_px Lep1_py Lep1_pz Lep1_E Wqrk0_px Wqrk0_py Wqrk0_pz Wqrk0_E Wqrk1_px Wqrk1_py Wqrk1_pz Wqrk1_E Iqrk0_px Iqrk0_py Iqrk0_pz Iqrk0_E Iqrk1_px Iqrk1_py Iqrk1_pz Iqrk1_E Lep0_pt Lep0_eta Lep1_pt Lep1_eta Wqrk0_pt Wqrk0_eta Wqrk1_pt Wqrk1_eta Iqrk0_pt Iqrk0_eta Iqrk1_pt Iqrk1_eta Iqrk1_phi Iqrk0_phi Wqrk1_phi Wqrk0_phi Lep1_phi Lep0_phi Iqrk1_theta Iqrk0_theta Wqrk1_theta Wqrk0_theta Lep1_theta Lep0_theta



compareQuantities(1 , 0 , 1 , "","","",20,-1. ,1. ,Cut,3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(" .pdf");
Canvas1->Clear();
compareQuantities(1 , 0 , 1 ,"","","","",20, , ,"","",3,"../pp_WpWm_LL.root","LL","../pp_WpWm_LT.root","LT","../pp_WpWm_TT.root","TT");
Canvas1->SaveAs(".pdf");
Canvas1->Clear();
*/
// compareQuantities(1 , 0 , 1 ,"mjj","","",20,0,500,"","",3,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpHadwmLep.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root","TOT");
 //compareQuantities(1 , 0 , 1 ,0,1,"mjj","","",20,0,500,"","",3,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LL_wpHadwmLep.root","LL","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_LT_wpHadwmLep.root","LT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT_WpLepWmHad.root","TT","/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TOT_WpLepWmHad.root","TOT");

#endif 
}
