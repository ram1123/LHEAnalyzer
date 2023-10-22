#include "LHEF.h"
#include "TH1.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"
#include "TCanvas.h"

#include <map>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>

#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"

#include "TChain.h"
#include "TNtuple.h"

#include "TAxis.h"
#include "TMath.h"

#include "conversions.h"
#include "vbf.h"
#include <cmath>

struct JetInfo {
    int index;
    double pt;
};



void Parton_level()

{

// Define histogram here

    TH1D *h_Particle_Px = new TH1D("Particle_Px ", "Particle_Px ", 50, -500, 500);
    TH1D *h_Particle_Py = new TH1D("Particle_Py ", "Particle_Py ", 50, -1, 1000);
    TH1D *h_Particle_Pz = new TH1D("Particle_Pz ", "Particle_Pz ", 50, -1, 1000);
    TH1D *h_Particle_E = new TH1D("Particle_E ", "Particle_E ", 50, 0, 3000);
    TH1D *h_lepton1_Pt = new TH1D("h_lepton1_Pt", "h_lepton1_Pt", 50, 0, 100) ;
    TH1D *h_lepton1_Eta = new TH1D("h_lepton1_Eta", "h_lepton1_Eta", 50, -4, 6) ;
    TH1D *h_lepton1_Phi = new TH1D("h_lepton1_Phi", "h_lepton1_Phi", 50, -5, 5) ;
    TH1D *h_lepton2_Pt = new TH1D ("h_lepton2_Pt", "h_lepton2_Pt", 50, 0, 100) ;
    TH1D *h_lepton2_Eta = new TH1D("h_lepton2_Eta", "h_lepton2_Eta", 50, -5, 5) ;
    TH1D *h_lepton2_Phi = new TH1D("h_lepton2_Phi", "h_lepton2_Phi", 50, -5, 5) ;
    TH1D *h_lepton3_Pt = new TH1D ("h_lepton3_Pt", "h_lepton3_Pt", 50, 0, 100) ;
    TH1D *h_lepton3_Eta = new TH1D("h_lepton3_Eta", "h_lepton3_Eta", 50, -5, 5) ;
    TH1D *h_lepton3_Phi = new TH1D("h_lepton3_Phi", "h_lepton3_Phi", 50, -5, 5) ;
    TH1D *h_quarks1_Pt = new TH1D("h_quarks1_Pt", "h_quarks1_Pt", 50, 0, 100) ;
    TH1D *h_quarks1_Eta = new TH1D("h_quarks1_Eta", "h_quarks1_Eta", 50, -5, 5) ;
    TH1D *h_quarks1_Phi = new TH1D("h_quarks1_Phi", "h_quarks1_Phi", 50, -5, 5) ;
    TH1D *h_quarks2_Pt = new TH1D("h_quarks2_Pt", "h_quarks2_Pt", 50, 0, 100) ;
    TH1D *h_quarks2_Eta = new TH1D("h_quarks2_Eta", "h_quarks2_Eta", 50, -5, 5) ;
    TH1D *h_quarks2_Phi = new TH1D("h_quarks2_Phi", "h_quarks2_Phi", 50, -5, 5) ;
    TH1D *h_b_quark_Pt = new TH1D("h_b_quark_Pt", "h_b_quark_Pt", 50, 0, 100) ;
    TH1D *h_b_quark_Eta = new TH1D("h_b_quark_Eta", "h_b_quark_Eta", 50, -5, 5) ;
    TH1D *h_b_quark_Phi = new TH1D("h_b_quark_Phi", "h_b_quark_Phi", 50, -5, 5) ;
    TH1D *h_MET_Pt = new TH1D("h_MET_Pt", "h_MET_Pt", 50, 0, 100) ;
    TH1D *h_MET_Eta = new TH1D("h_MET_Eta", "h_MET_Eta", 50, -4, 6) ;
    TH1D *h_MET_Phi = new TH1D("h_MET_Phi", "h_MET_Phi", 50, -5, 5) ;
    TH1D *h_forw_jet_Pt = new TH1D("h_forw_jet_Pt", "h_forw_jet_Pt", 50, 0, 100) ;
    TH1D *h_forw_jet_Eta = new TH1D("h_forw_jet_Eta", "h_forw_jet_Eta", 50, -4, 6) ;
    TH1D *h_forw_jet_Phi = new TH1D("h_forw_jet_Phi", "h_forw_jet_Phi", 50, -5, 5) ;
    TH1D *h_forw_jet_PDG = new TH1D("h_forw_jet_PDG", "h_forw_jet_PDG", 100, 0, 10) ;
    TH1D *h_top_quark_M = new TH1D("h_top_quark_M", "h_top_quark_M", 100, 150, 200) ;

TFile *f = new TFile("unweighted_events.root");

TTree *LHEF = (TTree*)f->Get("LHEF");

//Declaration of leaves types----------------------------------------------------------------------------------------------------------------------------------------

   Int_t           Particle_size;
   Int_t           Particle_PID[14];
   Double_t        Particle_Px[14];
   Double_t        Particle_Py[14];
   Double_t        Particle_Pz[14];
   Double_t        Particle_E[14];
   Double_t        Particle_PT[14];
   Double_t        Particle_Eta[14];
   Double_t        Particle_Phi[14];
   Double_t        Particle_M[14];
   Int_t           Particle_Mother1[14];
   Int_t           Particle_Mother2[14];


// Set branch addresses----------------------------------------------------------------------------------------------------------------------------------------------

   LHEF->SetBranchAddress("Particle_size",&Particle_size);
   LHEF->SetBranchAddress("Particle.PID",Particle_PID);
   LHEF->SetBranchAddress("Particle.Px",Particle_Px);
   LHEF->SetBranchAddress("Particle.Py",Particle_Py);
   LHEF->SetBranchAddress("Particle.Pz",Particle_Pz);
   LHEF->SetBranchAddress("Particle.E",Particle_E);
   LHEF->SetBranchAddress("Particle.PT",Particle_PT);
   LHEF->SetBranchAddress("Particle.Eta",Particle_Eta);
   LHEF->SetBranchAddress("Particle.Phi",Particle_Phi);
   LHEF->SetBranchAddress("Particle.M",Particle_M);
   LHEF->SetBranchAddress("Particle.Mother1",Particle_Mother1);
   LHEF->SetBranchAddress("Particle.Mother2",Particle_Mother2);


Int_t nentries = (Int_t)LHEF->GetEntries();


// for (Int_t i = 0; i < nentries; i++) {

for (Int_t i = 0; i < 10; i++) {
cout<< i << "\n" ;

LHEF->GetEntry(i);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //  std::vector<int> electrons ;
      std::vector<JetInfo> leptons ;
    //  std::vector<int> muons ;
      std::vector<JetInfo> MET ;
    //  std::vector<int> bosons ;
      std::vector<JetInfo> quarks ;
      std::vector<JetInfo> b_quarks ;
    // std::vector<int> up ;
    //  std::vector<int> strange ;
    //   std::vector<int> charm ;



for (int j = 0; j < Particle_size; j++){


        //  std::cout << "\t part type [" << j << "] " << abs(Particle_PID[j]) << "  [" <<Particle_PT[j] << "]"
          //          << "\n" ;

if (abs(Particle_PID[j]) == 11 || abs(Particle_PID[j]) == 13 ){

leptons.push_back({j, Particle_PT[j]});

}

/*if(leptons.size() == 4){

int momIdZ_0 = Particle_Mother1[leptons[0].index]   ;
int momIdZ_1 = Particle_Mother1[leptons[1].index]   ;
int momIdZ_2 = Particle_Mother1[leptons[2].index]   ;
int momIdZ_3 = Particle_Mother1[leptons[3].index]   ;

std::cout << " leptons1 " << abs(Particle_PID[leptons[1].index]) << " mom_leptons1 " << abs(Particle_PID[momIdZ_1]) <<  " leptons2 " << abs(Particle_PID[leptons[2].index]) << " mom_leptons2 " << abs(Particle_PID[momIdZ_2]) << "\n" ;


}*/

if (abs(Particle_PID[j]) < 11 && abs(Particle_PID[j]) != 5){

quarks.push_back({j, Particle_PT[j]}) ;

}


/*if(quarks.size() == 4 && abs(Particle_PID[quarks[0].index]) == abs(Particle_PID[quarks[1].index])){

int momIdW2_0 = Particle_Mother1[quarks[0].index]   ;
int momIdW2_1 = Particle_Mother1[quarks[1].index]   ;
int momIdW2_2 = Particle_Mother1[quarks[2].index]   ;
int momIdW2_3 = Particle_Mother1[quarks[3].index]   ;
if(abs(Particle_PID[momIdW2_0]) == abs(Particle_PID[momIdW2_1])){
std::cout <<" quark0 " << abs(Particle_PID[quarks[0].index]) << " mom_quark0 " << abs(Particle_PID[momIdW2_0])<< " || " <<" quark1 " << abs(Particle_PID[quarks[1].index]) << " mom_quark1 " << abs(Particle_PID[momIdW2_1]) <<" || " << " quark2 " << abs(Particle_PID[quarks[2].index]) << " mom_quark2 " << abs(Particle_PID[momIdW2_2])<< " || "<<" quark3 " << abs(Particle_PID[quarks[3].index]) << " mom_quark3 " << abs(Particle_PID[momIdW2_3]) << "\n" ;
}
}*/


if (abs(Particle_PID[j]) == 5 ) {

b_quarks.push_back({j, Particle_PT[j]}) ;

}

/*if(b_quarks.size() == 1)
{  int momIdt_b = Particle_Mother1[b_quarks[0].index];
std::cout << "\t part type [" << b_quarks[0].index << "] " << abs(Particle_PID[b_quarks[0].index]) << "  [" <<Particle_PT[b_quarks[0].index] << "]" << Particle_PID[momIdt_b]
                << "\n" ;}*/

if (abs(Particle_PID[j]) == 12 || abs(Particle_PID[j]) == 14 ){

MET.push_back({j, Particle_PT[j]}) ;

}

/*if(MET.size() == 1)
{std::cout << "\t part type [" << MET[0].index << "] " << abs(Particle_PID[MET[0].index]) << "  [" <<Particle_PT[MET[0].index] << "]" << MET.size()
                << "\n" ;}*/

//if(leptons.size() == 3 && quarks.size() == 4 )


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------



std::sort(leptons.begin(), leptons.end(), [](const JetInfo& a, const JetInfo& b) {
    return a.pt > b.pt;
});

//std::cout << "\t index of lepton 0 [" << leptons[0].index << "\n";

//if(!leptons.empty())
/*if(leptons.size() == 3 && quarks.size() == 3 && b_quarks.size() == 1 &&  MET.size() == 1)
{
h_lepton1_Pt->Fill (Particle_PT[leptons[0].index]);}*/

std::sort(quarks.begin(), quarks.end(), [](const JetInfo& a, const JetInfo& b) {
    return a.pt > b.pt;
});

std::sort(b_quarks.begin(), b_quarks.end(), [](const JetInfo& a, const JetInfo& b) {
    return a.pt > b.pt;
});

std::sort(MET.begin(), MET.end(), [](const JetInfo& a, const JetInfo& b) {
    return a.pt > b.pt;
});






//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


     // int momIdW1;
    //  int momIdW2_0;




    //  bool isforw_jet = true ;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

      if(leptons.size() == 3 && quarks.size() == 3 && b_quarks.size() == 1 &&  MET.size() == 1)

      {

       bool isWboson1 = true ;
       int momIdW1 = Particle_Mother1[leptons[0].index]   ;

       std::cout << "test momIdW1 [" << momIdW1 << "] " << Particle_PID[momIdW1]  << "\n" ;
       std::cout << "test leptons num " << leptons.size () << "\n" ;

       if(leptons.size () != 3) isWboson1 = false ;
       else if (abs(Particle_PID[momIdW1]) != 24)  isWboson1 = false ;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


      bool isZboson = true ;
      int momIdZ_0 = Particle_Mother1[leptons[0].index]   ;
      int momIdZ_1 = Particle_Mother1[leptons[1].index]   ;
      int momIdZ_2 = Particle_Mother1[leptons[2].index]   ;


      std::cout << "test momIdZ_0  [" << momIdZ_0 << "] " << Particle_PID[momIdZ_0]  << "\n" ;
      std::cout << "test momIdZ_1  [" << momIdZ_1 << "] " << Particle_PID[momIdZ_1]  << "\n" ;
      std::cout << "test momIdZ_2  [" << momIdZ_2 << "] " << Particle_PID[momIdZ_2]  << "\n" ;

      std::cout << "test leptons num " << leptons.size () << "\n" ;


      if(leptons.size ()  != 3) isZboson = false ;




      if (abs (Particle_PID[leptons[0].index]) !=
          abs (Particle_PID[leptons[1].index])||
          abs (Particle_PID[leptons[0].index]) !=
          abs (Particle_PID[leptons[2].index])||
          abs (Particle_PID[leptons[1].index]) !=
          abs (Particle_PID[leptons[2].index])) isZboson = false ;

      else   if (Particle_Mother1[leptons[1].index] !=
                 Particle_Mother1[leptons[2].index])  isZboson = false ;

      else    if (Particle_PID[momIdZ_1] != 23 ||
                 Particle_PID[momIdZ_2] != 23)  isZboson = false;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


      bool isMET = true ;
      int momIdMET = Particle_Mother1[MET[0].index]   ;

      std::cout << "test momIdMET [" << momIdMET << "] " << Particle_PID[momIdMET]  << "\n" ;
       std::cout << "test MET num " << MET.size () << "\n" ;

      if(MET.size () != 1) isMET = false ;

      else if (Particle_Mother1[MET[0].index] !=
                 Particle_Mother1[leptons[0].index])  isMET = false ;

      else if (abs(Particle_PID[momIdW1]) != 24) isMET = false ;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


     bool isWboson2 = true ;
     int momIdW2_0 = Particle_Mother1[quarks[0].index]   ;
     int momIdW2_1 = Particle_Mother1[quarks[1].index]   ;
     int momIdW2_2 = Particle_Mother1[quarks[2].index]   ;

     int grandmomIdW2_1 = Particle_Mother1[momIdW2_1]  ;
     int grandmomIdW2_2 = Particle_Mother1[momIdW2_2]  ;

     std::cout << "test momIdW2_0 [" << momIdW2_0 << "] " << Particle_PID[momIdW2_0]  << "\n" ;
     std::cout << "test momIdW2_1 [" << momIdW2_1 << "] " << Particle_PID[momIdW2_1]  << "\n" ;
     std::cout << "test momIdW2_2 [" << momIdW2_2 << "] " << Particle_PID[momIdW2_2]  << "\n" ;
   //  std::cout << "test grandmomIdW2_1 [" << grandmomIdW2_1 << "] " << Particle_PID[grandmomIdW2_1]  << "\n" ;
   //  std::cout << "test grandmomIdW2_2 [" << grandmomIdW2_2 << "] " << Particle_PID[grandmomIdW2_2]  << "\n" ;

     std::cout << "test quarks num " << quarks.size () << "\n" ;

     if (quarks.size () != 3) isWboson2 = false ;

     else if (Particle_Mother1[quarks[1].index] !=
                 Particle_Mother1[quarks[2].index]  )  isWboson2 = false ;

  //   else if (Particle_Mother2[quarks[1].index] !=
  //               Particle_Mother2[quarks[2].index]  )  isWboson2 = false ;


     else if (abs(Particle_PID[momIdW2_1]) != 24)  isWboson2 = false ;
     else if (abs(Particle_PID[grandmomIdW2_1]) != 6)  isWboson2 = false ;





//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

     bool isb_quark = true ;
     int momIdt_b = Particle_Mother1[b_quarks[0].index]   ;

     std::cout << "test momIdt_b [" << momIdt_b << "] " << Particle_PID[momIdt_b]  << "\n" ;
     std::cout << "test b_quarks num " << b_quarks.size () << "\n" ;

     if (b_quarks.size () != 1) isb_quark = false ;
     else if (Particle_PID[momIdt_b] != 6)  isb_quark= false ;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------



   //  if (abs(Particle_PID[momIdW2_0]) != 24)  isforw_jet = false ;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

     TLorentzVector lepton1;

if (!leptons.empty() && leptons.size() > 0) { lepton1.SetPtEtaPhiE(Particle_PT[leptons[0].index], Particle_Eta[leptons[0].index], Particle_Phi[leptons[0].index], Particle_E[leptons[0].index]);}

     TLorentzVector lepton2;

 if (leptons.size() > 1) { lepton2.SetPtEtaPhiE(Particle_PT[leptons[1].index], Particle_Eta[leptons[1].index], Particle_Phi[leptons[1].index], Particle_E[leptons[1].index]);}

     TLorentzVector lepton3;

 if (leptons.size() > 2) { lepton3.SetPtEtaPhiE(Particle_PT[leptons[2].index], Particle_Eta[leptons[2].index], Particle_Phi[leptons[2].index], Particle_E[leptons[2].index]);}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------


   TLorentzVector quark0;

   if (!quarks.empty()) {quark0.SetPtEtaPhiE(Particle_PT[quarks[0].index], Particle_Eta[quarks[0].index], Particle_Phi[quarks[0].index], Particle_E[quarks[0].index]);}

    TLorentzVector quark1;

   if (quarks.size() > 1) {quark1.SetPtEtaPhiE(Particle_PT[quarks[1].index], Particle_Eta[quarks[1].index], Particle_Phi[quarks[1].index], Particle_E[quarks[1].index]);}

    //   cout<< " jet2 eta =" << Jet_Eta[leadingJets[1].index] << "\n";

   TLorentzVector quark2;

   if (quarks.size() > 2) {quark2.SetPtEtaPhiE(Particle_PT[quarks[2].index], Particle_Eta[quarks[2].index], Particle_Phi[quarks[2].index], Particle_E[quarks[2].index]);}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

   TLorentzVector b_quark;

   if(!b_quarks.empty())b_quark.SetPtEtaPhiE(Particle_PT[b_quarks[0].index], Particle_Eta[b_quarks[0].index], Particle_Phi[b_quarks[0].index], Particle_E[b_quarks[0].index]);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

  TLorentzVector Met;

  if(!MET.empty()) {Met.SetPtEtaPhiE(Particle_PT[MET[0].index], Particle_Eta[MET[0].index], Particle_Phi[MET[0].index], Particle_E[MET[0].index] );}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


h_Particle_Px->Fill(Particle_Px[j]);
h_Particle_Py->Fill(Particle_Py[j]);
h_Particle_Pz->Fill(Particle_Pz[j]);
h_Particle_E->Fill(Particle_E[j]);
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


         if (isWboson1 )
         {
         h_lepton1_Pt->Fill (lepton1.Pt()) ;
         h_lepton1_Eta->Fill (lepton1.Eta()) ;
         h_lepton1_Phi->Fill (lepton1.Phi()) ;

         }


         if (isZboson)
         {
         h_lepton2_Pt->Fill (lepton2.Pt()) ;
         h_lepton2_Eta->Fill (lepton2.Eta()) ;
         h_lepton2_Phi->Fill (lepton2.Phi()) ;
         h_lepton3_Pt->Fill (lepton3.Pt()) ;
         h_lepton3_Eta->Fill (lepton3.Eta()) ;
         h_lepton3_Phi->Fill (lepton3.Phi()) ;

         }



         h_forw_jet_Pt->Fill (quark0.Pt()) ;
         h_forw_jet_Eta->Fill (quark0.Eta()) ;
         h_forw_jet_Phi->Fill (quark0.Phi()) ;
      //   h_forw_jet_PDG->Fill (abs (Particle_PID[quarks.at (0)]) ) ;
       //  h_left_over_quarks.Fill (quark0.size());


         if (isWboson2 )
         {
         h_quarks1_Pt->Fill (quark1.Pt()) ;
         h_quarks1_Eta->Fill (quark1.Eta()) ;
         h_quarks1_Phi->Fill (quark1.Phi()) ;
         h_quarks2_Pt->Fill (quark2.Pt()) ;
         h_quarks2_Eta->Fill (quark2.Eta()) ;
         h_quarks2_Phi->Fill (quark2.Phi()) ;
         }

         if (isb_quark )
         {
         h_b_quark_Pt->Fill (b_quark.Pt()) ;
         h_b_quark_Eta->Fill (b_quark.Eta()) ;
         h_b_quark_Phi->Fill (b_quark.Phi()) ;

         }

         if (isMET )
         {
         h_MET_Pt->Fill (Met.Pt()) ;
         h_MET_Eta->Fill (Met.Eta()) ;
         h_MET_Phi->Fill (Met.Phi()) ;

         }
}

//TFile Plot ("Plot.C", "recreate");

   TFile histosFile ("file2.root","recreate") ;
 //  Plot.cd ();
   histosFile.cd () ;

   h_lepton1_Pt->Write ();
   h_lepton1_Eta->Write ();
   h_lepton1_Phi->Write ();
   h_lepton2_Pt->Write ();
   h_lepton2_Eta->Write ();
   h_lepton2_Phi->Write ();
   h_lepton3_Pt->Write ();
   h_lepton3_Eta->Write ();
   h_lepton3_Phi->Write ();
   h_MET_Pt->Write() ;
   h_MET_Eta->Write() ;
   h_MET_Phi->Write() ;
   h_quarks1_Pt->Write ();
   h_quarks1_Eta->Write ();
   h_quarks1_Phi->Write ();
   h_quarks2_Pt->Write ();
   h_quarks2_Eta->Write ();
   h_quarks2_Phi->Write ();
   h_b_quark_Pt->Write ();
   h_b_quark_Eta->Write ();
   h_b_quark_Phi->Write ();
   h_forw_jet_Pt->Write ();
   h_forw_jet_Eta->Write ();
   h_forw_jet_Phi->Write ();
   h_forw_jet_PDG->Write ();
   h_top_quark_M->Write ();
 //  h_DeltaR_top_forw_jet.Write();
 //  histosFile.Close () ;
 //  outputFile.Close();
/*h_Particle_Px->Write();
h_Particle_Py->Write();
h_Particle_Pz->Write();
h_Particle_E->Write();*/

histosFile.Close();

}
}


// Save histograms as PNG files------------------------------------------------------------------------------------------------------------------------------------



/*TCanvas *c1 = new TCanvas();

top_mass ->Draw();
c1->SaveAs("top_mass.png");


TCanvas *c2 = new TCanvas();

W_mass ->Draw();
c2->SaveAs("W_mass.png");

TCanvas *c3 = new TCanvas();

Z_mass ->Draw();
c3->SaveAs("Z_mass.png");*/

TCanvas *c4 = new TCanvas();

h_lepton1_Pt ->Draw();
c4->SaveAs("h_lepton1_Pt.png");


TCanvas *c5 = new TCanvas();

h_lepton1_Eta ->Draw();
c5->SaveAs("h_lepton1_Eta.png");

TCanvas *c6 = new TCanvas();

h_lepton1_Phi ->Draw();
c6->SaveAs("h_lepton1_Phi.png");

TCanvas *c7 = new TCanvas();

h_MET_Pt ->Draw();
c7->SaveAs("h_MET_Pt.png");

TCanvas *c8 = new TCanvas();

h_b_quark_Pt ->Draw();
c8->SaveAs("h_b_quark_Pt.png");

TCanvas *c9 = new TCanvas();

h_b_quark_Eta ->Draw();
c9->SaveAs("h_b_quark_Eta.png");

TCanvas *c10 = new TCanvas();

h_b_quark_Phi ->Draw();
c10->SaveAs("h_b_quark_Phi.png");

TCanvas *c11 = new TCanvas();

h_forw_jet_Pt ->Draw();
c11->SaveAs("h_forw_jet_Pt.png");

TCanvas *c12 = new TCanvas();

h_forw_jet_Eta ->Draw();
c12->SaveAs("h_forw_jet_Eta.png");

TCanvas *c13 = new TCanvas();

h_forw_jet_Phi ->Draw();
c13->SaveAs("h_forw_jet_Phi.png");

TCanvas *c14 = new TCanvas();

h_quarks1_Pt ->Draw();
c14->SaveAs("h_quarks1_Pt.png");

TCanvas *c15 = new TCanvas();

h_quarks1_Eta ->Draw();
c15->SaveAs("h_quarks1_Eta.png");

TCanvas *c16 = new TCanvas();

h_quarks1_Phi ->Draw();
c16->SaveAs("h_quarks1_Phi.png");

TCanvas *c17 = new TCanvas();

h_quarks2_Pt ->Draw();
c17->SaveAs("h_quarks2_Pt.png");

TCanvas *c18 = new TCanvas();

h_quarks2_Eta ->Draw();
c18->SaveAs("h_quarks2_Eta.png");

TCanvas *c19 = new TCanvas();

h_quarks2_Phi ->Draw();
c19->SaveAs("h_quarks2_Phi.png");

TCanvas *c20 = new TCanvas();

h_lepton2_Pt ->Draw();
c20->SaveAs("h_lepton2_Pt.png");


TCanvas *c21 = new TCanvas();

h_lepton2_Eta ->Draw();
c21->SaveAs("h_lepton2_Eta.png");

TCanvas *c22 = new TCanvas();

h_lepton2_Phi ->Draw();
c22->SaveAs("h_lepton2_Phi.png");

TCanvas *c23 = new TCanvas();

h_lepton3_Pt ->Draw();
c20->SaveAs("h_lepton3_Pt.png");


TCanvas *c24 = new TCanvas();

h_lepton3_Eta ->Draw();
c24->SaveAs("h_lepton3_Eta.png");

TCanvas *c25 = new TCanvas();

h_lepton3_Phi ->Draw();
c25->SaveAs("h_lepton3_Phi.png");

TCanvas *c26 = new TCanvas();

h_MET_Eta ->Draw();
c26->SaveAs("h_MET_Eta.png");

TCanvas *c27 = new TCanvas();

h_MET_Phi ->Draw();
c27->SaveAs("h_MET_Phi.png");




   return 0 ;

/*TCanvas *c1 = new TCanvas();

h_Particle_Px->Draw();
c1->SaveAs("h_Particle_Px.png");


TCanvas *c2 = new TCanvas();

h_Particle_Py->Draw();
c2->SaveAs("h_Particle_Py.png");

TCanvas *c3 = new TCanvas();


h_Particle_Pz->Draw();
c3->SaveAs("h_Particle_Pz.png");


TCanvas *c4 = new TCanvas();


h_Particle_E->Draw();
c4->SaveAs("h_Particle_E.png");*/

f->Close();
}

