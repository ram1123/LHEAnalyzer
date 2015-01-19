#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

#include <iostream>

int Analyze_LHE_Coyte()
{
  TFile *lhe = new TFile( "/eos/uscms/store/user/rasharma/LHE_outputs/13TeV/pp_WWJJ_TOT/lhe.root", "READ");
  if (!(lhe && lhe->IsOpen())) { delete lhe; return -1; }
  
  ////////////////////////////////////////////////////////////////////////
  //		CREATE TREE 
  ////////////////////////////////////////////////////////////////////////
  TFile *file = new TFile("Analyze_Lhe.root","RECREATE");
  TTree* TPartInfo = new TTree("TPartInfo","Particles Info");

  float Lep_Pt, Lep_Eta, Lep_Phi;
  float Met_Pt, Met_Eta, Met_Phi;
  float WQrk0_Pt, WQrk0_Eta, WQrk0_Phi;
  float WQrk1_Pt, WQrk1_Eta, WQrk1_Phi;
  float IQrk0_Pt, IQrk0_Eta, IQrk0_Phi;
  float IQrk1_Pt, IQrk1_Eta, IQrk1_Phi;
  float FSQrk_Pt, FSQrk_Eta, FSQrk_Phi, FSQrk_Mass;

  float mWW_,b_mWW, mWLep_,b_mWLep, mWHad_,b_mWHad, costheta1_,b_costheta1, costheta2_,b_costheta2, costhetastar_,b_costhetastar, phi_,b_phi, phi1_,b_phi1;   
  float dEtajj_,b_dEtajj, dPhijj_,b_dPhijj, mjj_,b_mjj; 
  
  TPartInfo->Branch( "b_mjj"	,		&b_mjj		,	"b_mjj/F");
  TPartInfo->Branch( "b_dPhijj" ,		&b_dPhijj	,	"b_dPhijj/F");
  TPartInfo->Branch( "b_dEtajj" ,		&b_dEtajj	,	"b_dEtajj/F");
  TPartInfo->Branch( "b_phi1"	,		&b_phi1		,	"b_phi1/F");
  TPartInfo->Branch( "b_phi" 	,		&b_phi		,	"b_phi/F");
  TPartInfo->Branch( "b_costhetastar"	,	&b_costhetastar	,	"b_costhetastar/F");
  TPartInfo->Branch( "b_costheta2" 	,	&b_costheta2	,	"b_costheta2/F");
  TPartInfo->Branch( "b_costheta1" 	,	&b_costheta1	,	"b_costheta1/F");
  TPartInfo->Branch( "b_mWHad" 	,		&b_mWHad	,	"b_mWHad/F");
  TPartInfo->Branch( "b_mWLep" 	,		&b_mWLep	,	"b_mWLep/F");
  TPartInfo->Branch( "b_mWW" 	,		&b_mWW		,	"b_mWW/F");
  TPartInfo->Branch( "Lep_Pt" 	,		&Lep_Pt		,	"Lep_Pt/F");
  TPartInfo->Branch( "Lep_Eta"	,		&Lep_Eta	,	"Lep_Eta/F");
  TPartInfo->Branch( "Lep_Phi"	,		&Lep_Phi	,	"Lep_Phi/F");
  TPartInfo->Branch( "Met_Pt" 	,		&Met_Pt		,	"Met_Pt/F");
  TPartInfo->Branch( "Met_Eta"	,		&Met_Eta	,	"Met_Eta/F");
  TPartInfo->Branch( "Met_Phi"	,		&Met_Phi	,	"Met_Phi/F");
  TPartInfo->Branch( "WQrk0_Pt" 	,	&WQrk0_Pt 	,	"WQrk0_Pt/F");
  TPartInfo->Branch( "WQrk0_Eta"	,	&WQrk0_Eta	,	"WQrk0_Eta/F");
  TPartInfo->Branch( "WQrk0_Phi"	,	&WQrk0_Phi	,	"WQrk0_Phi/F");
  TPartInfo->Branch( "WQrk1_Pt" 	,	&WQrk1_Pt	,	"WQrk1_Pt/F");
  TPartInfo->Branch( "WQrk1_Eta"	,	&WQrk1_Eta	,	"WQrk1_Eta/F");
  TPartInfo->Branch( "WQrk1_Phi"	,	&WQrk1_Phi	,	"WQrk1_Phi/F");
  TPartInfo->Branch( "IQrk0_Pt" 	,	&IQrk0_Pt	,	"IQrk0_Pt/F");
  TPartInfo->Branch( "IQrk0_Eta"	,	&IQrk0_Eta	,	"IQrk0_Eta/F");
  TPartInfo->Branch( "IQrk0_Phi"	,	&IQrk0_Phi	,	"IQrk0_Phi/F");
  TPartInfo->Branch( "IQrk1_Pt" 	,	&IQrk1_Pt	,	"IQrk1_Pt/F");
  TPartInfo->Branch( "IQrk1_Eta"	,	&IQrk1_Eta	,	"IQrk1_Eta/F");
  TPartInfo->Branch( "IQrk1_Phi"	,	&IQrk1_Phi	,	"IQrk1_Phi/F");
  TPartInfo->Branch( "FSQrk_Pt" 	,	&FSQrk_Pt	,	"FSQrk_Pt/F");
  TPartInfo->Branch( "FSQrk_Eta"	,	&FSQrk_Eta	,	"FSQrk_Eta/F");
  TPartInfo->Branch( "FSQrk_Phi"	,	&FSQrk_Phi	,	"FSQrk_Phi/F");
  TPartInfo->Branch( "FSQrk_Mass"	,	&FSQrk_Mass	,	"FSQrk_Mass/F");

  ////////////////////////////////////////////////////////////////////////

  TTree *tree;
  lhe->GetObject("tree", tree);
  if (!tree) { delete lhe; return -2; }
  

  tree->SetMakeClass(1); // all branches in decomposed object mode
  tree->SetBranchStatus("*", 0); // disable all branches
  

  tree->SetBranchStatus(	"mjj", 1); // activate "Llep0"
  tree->GetBranch(	"mjj")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"mjj", &mjj_);


  tree->SetBranchStatus(	"dPhijj", 1); // activate "Llep0"
  tree->GetBranch(	"dPhijj")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"dPhijj", &dPhijj_);


  tree->SetBranchStatus(	"dEtajj", 1); // activate "Llep0"
  tree->GetBranch(	"dEtajj")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"dEtajj", &dEtajj_);


  tree->SetBranchStatus(	"phi1", 1); // activate "Llep0"
  tree->GetBranch(	"phi1")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"phi1", &phi1_);


  tree->SetBranchStatus(	"phi", 1); // activate "Llep0"
  tree->GetBranch(	"phi")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"phi", &phi_);


  tree->SetBranchStatus(	"costhetastar", 1); // activate "Llep0"
  tree->GetBranch(	"costhetastar")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"costhetastar", &costhetastar_);


  tree->SetBranchStatus(	"costheta2", 1); // activate "Llep0"
  tree->GetBranch(	"costheta2")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"costheta2", &costheta2_);


  tree->SetBranchStatus(	"costheta1", 1); // activate "Llep0"
  tree->GetBranch(	"costheta1")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"costheta1", &costheta1_);


  tree->SetBranchStatus(	"mWHad", 1); // activate "Llep0"
  tree->GetBranch(	"mWHad")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"mWHad", &mWHad_);


  tree->SetBranchStatus(	"mWLep", 1); // activate "Llep0"
  tree->GetBranch(	"mWLep")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress(	"mWLep", &mWLep_);


  tree->SetBranchStatus("mWW", 1); // activate "Llep0"
  tree->GetBranch("mWW")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("mWW", &mWW_);

  TClonesArray *Llep0_ = new TClonesArray("TLorentzVector");
  tree->SetBranchStatus("Llep0", 1); // activate "Llep0"
  tree->GetBranch("Llep0")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("Llep0", &Llep0_);
  
  TClonesArray *Llep1_ = new TClonesArray("TLorentzVector");
  tree->SetBranchStatus("Llep1", 1); // activate "Llep0"
  tree->GetBranch("Llep1")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("Llep1", &Llep1_);

  TClonesArray *LWqrk0_ = new TClonesArray("TLorentzVector");
  tree->SetBranchStatus("LWqrk0", 1); // activate "Llep0"
  tree->GetBranch("LWqrk0")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("LWqrk0", &LWqrk0_);

  TClonesArray *LWqrk1_ = new TClonesArray("TLorentzVector");
  tree->SetBranchStatus("LWqrk1", 1); // activate "Llep0"
  tree->GetBranch("LWqrk1")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("LWqrk1", &LWqrk1_);

  TClonesArray *LIqrk1_ = new TClonesArray("TLorentzVector");
  tree->SetBranchStatus("LIqrk1", 1); // activate "Llep0"
  tree->GetBranch("LIqrk1")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("LIqrk1", &LIqrk1_);

  TClonesArray *LIqrk0_ = new TClonesArray("TLorentzVector");
  tree->SetBranchStatus("LIqrk0", 1); // activate "Llep0"
  tree->GetBranch("LIqrk0")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("LIqrk0", &LIqrk0_);

  TClonesArray *LFrdQrkSum_ = new TClonesArray("TLorentzVector");
  tree->SetBranchStatus("LFrdQrkSum", 1); // activate "Llep0"
  tree->GetBranch("LFrdQrkSum")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("LFrdQrkSum", &LFrdQrkSum_);

  Long64_t nevent = tree->GetEntries();
  
  std::cout << "####### tree->GetEntries() = " << nevent << std::endl;

  for (Long64_t i = 0; i < nevent; i++) {
    if (Llep0_) Llep0_->Clear();
    if (Llep1_) Llep1_->Clear();
    if (LWqrk0_) LWqrk0_->Clear();
    if (LWqrk1_) LWqrk1_->Clear();
    if (LIqrk1_) LIqrk1_->Clear();
    if (LIqrk1_) LIqrk0_->Clear();
    if (LFrdQrkSum_) LFrdQrkSum_->Clear();
    tree->GetEntry(i);
//    std::cout << "i = " << i << std::endl;
    
	b_dEtajj	=	dEtajj_;
	b_phi1		=	phi1_;
	b_dPhijj	=	dPhijj_;
	b_mjj		=	mjj_;
	b_phi		=	phi_;
	b_costhetastar	=	costhetastar_;
	b_costheta2	=	costheta2_;
	b_costheta1	=	costheta1_;
	b_mWHad		=	mWHad_;
	b_mWLep		=	mWLep_;
	b_mWW 		= 	mWW_;

    if (!Llep0_) continue; // just a precaution
    Int_t nvectors = Llep0_->GetEntriesFast();
    for (Int_t j = 0; j < nvectors; j++) {
      TLorentzVector *v = ((TLorentzVector *)(LIqrk0_->At(j)));
      if (!v) continue; // skip an "empty slot"
	IQrk0_Pt	= v->Pt();
	IQrk0_Eta	= v->Eta();
	IQrk0_Phi	= v->Phi();
	}

    for (Int_t j = 0; j < nvectors; j++) {
      TLorentzVector *v = ((TLorentzVector *)(LIqrk1_->At(j)));
      if (!v) continue; // skip an "empty slot"
	IQrk1_Pt	= v->Pt();
	IQrk1_Eta	= v->Eta();
	IQrk1_Phi	= v->Phi();
	}

    for (Int_t j = 0; j < nvectors; j++) {
      TLorentzVector *v = ((TLorentzVector *)(LWqrk0_->At(j)));
      if (!v) continue; // skip an "empty slot"
	WQrk0_Pt	= v->Pt();
	WQrk0_Eta	= v->Eta();
	WQrk0_Phi	= v->Phi();
	}
    
    for (Int_t j = 0; j < nvectors; j++) {
      TLorentzVector *v = ((TLorentzVector *)(LWqrk1_->At(j)));
      if (!v) continue; // skip an "empty slot"
	WQrk1_Pt	= v->Pt();
	WQrk1_Eta	= v->Eta();
	WQrk1_Phi	= v->Phi();
	}

    for (Int_t j = 0; j < nvectors; j++) {
      TLorentzVector *v = ((TLorentzVector *)(Llep1_->At(j)));
      if (!v) continue; // skip an "empty slot"
	Met_Pt	= v->Pt();
	Met_Eta	= v->Eta();
	Met_Phi	= v->Phi();
	}
    for (Int_t j = 0; j < nvectors; j++) {
      TLorentzVector *v = ((TLorentzVector *)(Llep0_->At(j)));
      if (!v) continue; // skip an "empty slot"
	Lep_Pt	= v->Pt();
	Lep_Eta	= v->Eta();
	Lep_Phi	= v->Phi();
    }
    for (Int_t j = 0; j < nvectors; j++) {
      TLorentzVector *v = ((TLorentzVector *)(LFrdQrkSum_->At(j)));
      if (!v) continue; // skip an "empty slot"
	FSQrk_Pt	= v->Pt();
	FSQrk_Eta	= v->Eta();
	FSQrk_Phi	= v->Phi();
	FSQrk_Mass	= v->M();
    }
	TPartInfo->Fill();
  }
  
  tree->ResetBranchAddresses(); // "detach" from local variables
  delete lhe; // it will automatically delete "tree", too
  delete Llep0_; // cleanup
  delete Llep1_; // cleanup
  delete LWqrk0_; // cleanup
  delete LWqrk1_; // cleanup
  delete LIqrk0_; // cleanup
  delete LIqrk1_; // cleanup
  file->cd();
  TPartInfo->Write();
  file->Close();
  
  return 0;
}
