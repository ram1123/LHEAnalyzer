#define ReadLHE_cxx
#include "ReadLHE.h"
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TLorentzVector.h"

#include <cstdlib>
#include <cmath>
#include <iostream>

int ReadLHE()
{
	ReadLHE t;
	t.Loop();
	return 0;
}

void ReadLHE::Loop()
{
    //   In a ROOT session, you can do:
    //      Root > .L ReadLHE.C
    //      Root > ReadLHE t
    //      Root > t.GetEntry(12); // Fill t data members with entry number 12
    //      Root > t.Show();       // Show values of entry 12
    //      Root > t.Show(16);     // Read and show values of entry 16
    //      Root > t.Loop();       // Loop on all entries
    //

    //     This is the loop skeleton where:
    //    jentry is the global entry number in the chain
    //    ientry is the entry number in the current Tree
    //  Note that the argument to GetEntry must be:
    //    jentry for TChain::GetEntry
    //    ientry for TTree::GetEntry and TBranch::GetEntry
    //
    //       To read only selected branches, Insert statements like:
    // METHOD1:
    //    fChain->SetBranchStatus("*",0);  // disable all branches
    //    fChain->SetBranchStatus("branchname",1);  // activate branchname
    // METHOD2: replace line
    //    fChain->GetEntry(jentry);       //read all branches
    //by  b_branchname->GetEntry(ientry); //read only this branch
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    TFile file("Ntuple_ppzzjj.root","RECREATE");
    file.SetCompressionLevel(2);
    TTree* tree = new TTree("tree","Particles Info");

    //TH1F * h1 = new TH1F("h1","h1",50,-5.,5.);
    //TH1F * h2 = new TH1F("h2","h1",50,-5.,5.);

    float Theta_V1, Theta_V2,CosTheta_V1,CosTheta_V2;

    tree->Branch("Theta_V1",&Theta_V1,"Theta_V1/F");
    tree->Branch("Theta_V2",&Theta_V2,"Theta_V2/F");
    tree->Branch("CosTheta_V1",&CosTheta_V1,"CosTheta_V1/F");
    tree->Branch("CosTheta_V2",&CosTheta_V2,"CosTheta_V2/F");


    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) 
    {
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	if (jentry > 10) break; // just the first 2 entries
	#if 0 /* 0 or 1 */
	nb = fChain->GetEntry(jentry); nbytes += nb;
	#else /* 0 or 1 */
	nb = 0;
	nb += b_Particle_->GetEntry(ientry);
	nb += b_Particle_PID->GetEntry(ientry);
	nb += b_Particle_Px->GetEntry(ientry);
	nb += b_Particle_Py->GetEntry(ientry);
	nb += b_Particle_Pz->GetEntry(ientry);
	nb += b_Particle_E->GetEntry(ientry);
	nbytes += nb;
	#endif /* 0 or 1 */
	// if (Cut(ientry) < 0) continue;
	//std::cout << "nb = " << nb << std::endl;
	int quakr_count = 0;
	int w_count = 0;
	//cout<<"Particle_ = "<<Particle_<<endl;
	for (int im = 0; im < Particle_; im++) {
	    //std::cout << im << "\tParticle_Py = " << Particle_E[im] << std::endl;
	    //std::cout << im << "\tParticle_PID = " << Particle_PID[im] << std::endl;
	    if (std::abs(Particle_PID[im]) == 23)
	    {
		w_count++;
		if (w_count==1)
		{
		    #if 1
		    TLorentzVector Z0(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		    #else
		    cout<<Particle_Px[im]<<"\t"<<Particle_Py[im]<<"\t"<<Particle_Pz[im]<<"\t"<<Particle_E[im]<<endl;
		    TLorentzVector Z0;
		    Z0.SetPxPyPzE(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		    #endif
		}
		if (w_count==2)
		{
		    #if 1
		    TLorentzVector Z1(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		    #else
		    cout<<Particle_Px[im]<<"\t"<<Particle_Py[im]<<"\t"<<Particle_Pz[im]<<"\t"<<Particle_E[im]<<endl;
		    TLorentzVector Z1;
		    Z1.SetPxPyPzE(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		    #endif
		}
		//if (w_count > 2 )
		//{
		//	std::cout<<"Some Problem: there are more than 2 w's."<<std::endl;
		//	exit();
		//}
	    }
	    if ((std::abs(Particle_PID[im]) < 9) || (Particle_PID[im] == 21)) {
		quakr_count++;
		//std::cout << "quakr_count = " << quakr_count << "\t For loop no = "<<im<<std::endl;
		if (quakr_count==1) {
		#if 1 /* 0 or 1 */
		    TLorentzVector Iqrk0(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#else /* 0 or 1 */
		    cout<<Particle_PID[im]<<"\t"<<Particle_Px[im]<<"\t"<<Particle_Py[im]<<"\t"<<Particle_Pz[im]<<"\t"<<Particle_E[im]<<endl;
		    TLorentzVector Iqrk0;
		    Iqrk0.SetPxPyPzE(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#endif /* 0 or 1 */
		    //std::cout << im << "\tParticle_ AFTER Iqrk0 = " << Particle_ << std::endl;
		}
		if (quakr_count==2)
		{
		#if 1
		    TLorentzVector Iqrk1(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#else
		    cout<<Particle_PID[im]<<"\t"<<Particle_Px[im]<<"\t"<<Particle_Py[im]<<"\t"<<Particle_Pz[im]<<"\t"<<Particle_E[im]<<endl;
		    TLorentzVector Iqrk1;
		    Iqrk1.SetPxPyPzE(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#endif
		}
		if (quakr_count==3)
		{
		#if 1
		    TLorentzVector Fqrk0(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#else
		    cout<<Particle_PID[im]<<"\t"<<Particle_Px[im]<<"\t"<<Particle_Py[im]<<"\t"<<Particle_Pz[im]<<"\t"<<Particle_E[im]<<endl;
		    TLorentzVector Fqrk0;
		    Fqrk0.SetPxPyPzE(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#endif
		}
		if (quakr_count==4)
		{
		#if 1
		    TLorentzVector Fqrk1(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#else
		    cout<<Particle_PID[im]<<"\t"<<Particle_Px[im]<<"\t"<<Particle_Py[im]<<"\t"<<Particle_Pz[im]<<"\t"<<Particle_E[im]<<endl;
		TLorentzVector Fqrk1;
		Fqrk1.SetPxPyPzE(Particle_Px[im], Particle_Py[im], Particle_Pz[im], Particle_E[im]);
		#endif
		}
		if (quakr_count > 4 )
		{
		    std::cout<<"Some Problem: there are more than 4 quarks."<<std::endl;
		    exit();
		}
	    }
	}
	//cout<<"Angle between q1 ("<<Iqrk0.Theta()<<" ) and q2 ("<<Fqrk0.Theta()<<" ) two quarks = "<<Iqrk0.Angle(Fqrk0.Vect())<<endl;
	//cout<<"####################################################################################"<<endl;
	//cout<<"Iq1 = "<<Iqrk0.Theta()<<"\tIq2 = "<<Iqrk1.Theta()<<"\tFq1 = "<<Fqrk0.Theta()<<"\tFq2 = "<<Fqrk1.Theta()<<endl;
	//cout<<"Z0 = "<<Z0.Theta()<<"\tZ1 = "<<Z1.Theta()<<endl;
	//cout<<"theta_V = "<<(Iqrk0-Fqrk1).Theta()-Z1.Theta()<<"\t"<<(Iqrk0-Fqrk1).Theta()-Z0.Theta()<<endl;
	
	//cout<<"#########################"<<endl;
	//h1->Fill((Iqrk0-Fqrk1).Theta()-Z1.Theta());
	//h2->Fill((Iqrk0-Fqrk1).Theta()-Z0.Theta());
	Theta_V1 =(float)( (Iqrk0-Fqrk1).Theta()-Z1.Theta());
	Theta_V2 =(float)( (Iqrk0-Fqrk1).Theta()-Z0.Theta());
	CosTheta_V1 =(float)(cos( (Iqrk0-Fqrk1).Theta()-Z1.Theta()));
	CosTheta_V2 =(float)(cos( (Iqrk0-Fqrk1).Theta()-Z0.Theta()));

	tree->Fill();
    }
    file.cd();
    tree->Write();
    file.Close();

    //h1->Draw();
    //h2->Draw();

}
