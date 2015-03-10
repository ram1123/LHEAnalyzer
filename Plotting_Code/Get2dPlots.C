/*
 * Compare Root Files
 *
 */
{
 gROOT->Reset();

 gROOT->ProcessLine(".L CompareAdvanced_2dPlots.C");

 //const string Cut = "(abs(Lep1_eta)<2.5) && (abs(Lep0_eta)<2.5) && (Lep0_pt>20) && (Lep1_pt>20) && (Wqrk1_pt>10) && (Wqrk0_pt>10) && (Iqrk0_pt>10) && (Iqrk1_pt>10) && (mjj > 500.) && (Iqrk1_eta-Iqrk0_eta > 4.0) ";
 const string Cut = "";

// TCanvas *Canvas1 = new TCanvas("Canvas1","example",600,700);
 TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,900,700);

compareQuantities("Wqrk1_eta","cosh(Wqrk1_eta)/2",20,-7.,7.,20,-5.,85.,Cut,1,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","LL");
Canvas1->SaveAs("mjj.pdf");
Canvas1->Clear();
compareQuantities("Wqrk1_eta","Wqrk1_pt",20,-7.,7.,20,-100.,1000.,Cut,1,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","LL");
compareQuantities("Iqrk1_eta","Iqrk1_pt",20,-7.,7.,20,-100.,2500.,Cut,1,"/eos/uscms/store/user/rasharma/WWScattering/OutPut_LHEanalyzer/DefaultCut/pp_WWJJ_TT.root","LL");

Canvas1->SaveAs("mjj.pdf");
Canvas1->Clear();
}
