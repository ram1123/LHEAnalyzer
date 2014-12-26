/*
Based on code by Nahan

Date: 24/08/2014
	
	Tring to add info about number of electrons and different types of quark.
*/

#include "LHEF.h"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLorentzVector.h"

#include <cmath>
#include "TTree.h"
#include <vector>

/*
 
 TO COMPILE:
 
 export ROOTSYS=~/Desktop/root
 export PATH=$ROOTSYS/bin:$PATH
 export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
 export DYLD_LIBRARY_PATH=$ROOTSYS/lib:$DYLD_LIBRARY_PATH 
 
 c++ -o analysis01 `root-config --glibs --cflags` -lm hFactory.cc hChain.cc h2Factory.cc h2Chain.cc analysis01.cpp
 
 TO RUN:     
 
 ./analysis01 ../madevent_3/Events/pietro_test14_unweighted_events.lhe ../Z2j/run_01_unweighted_events.lhe 
 
 numerazione dei plot:
 
 2 -- segnale selezionati
 4 -- segnale persi
 0 -- segnale totale
 3 -- bkg irr selezionati
 5 -- bkg irr persi
 1 -- bkg irr totale
 7 -- bkg qcd selezionati
 8 -- bkg qcd persi
 6 -- bkg qcd totale
 */

void computeAngles(TLorentzVector thep4H, TLorentzVector thep4Z1, TLorentzVector thep4M11, TLorentzVector thep4M12, TLorentzVector thep4Z2, TLorentzVector thep4M21, TLorentzVector thep4M22, double& costheta1, double& costheta2, double& Phi, double& costhetastar, double& Phi1);


double deltaPhi (double phi1, double phi2)
{
    double deltaphi=fabs(phi1-phi2);
    if (deltaphi > 6.283185308) deltaphi -= 6.283185308;
    if (deltaphi > 3.141592654) deltaphi = 6.283185308-deltaphi;
    return deltaphi;
}


//! ========================================================================================


int main (int argc, char **argv) {
    
//    gSystem->Load("libPhysics");
      TFile file(argv[2],"RECREATE");
    TTree* tree = new TTree("tree","tree");
    
    float mWW, mWLep, mWHad, costheta1, costheta2, costhetastar, phi, phi1;
    int NumberOfBQuark,NumberOftQuark,NumberOfLeptonsAndNu,NumberOfMuonsAndNu;
    
    int genMuonNumMuon, genMuonCharge, genEleNumEle,  genEleCharge; 
    float   genMuonPx, genMuonPy, genMuonPz, genMuonPt, genMuonP3, genMuonEt, genMuonMt, genMuonMass, genMuonEnergy, genMuonEta, genMuonTheta, genMuonPhi, genElePx, genElePy, genElePz, genElePt, genEleP3, genEleEt, genEleMt, genEleMass, genEleEnergy, genEleEta, genEleTheta, genElePhi, mgenPx, mgenPy, mgenPz, mgenPt, mgenP3, mgenEt, mgenMt, mgenMass, mgenEnergy, mgenEta, mgenTheta, mgenPhi;

//    std::vector<float> jgenPx, jgenPy, jgenPz, jgenPt, jgenP3, jgenEt, jgenMt, jgenMass, jgenEnergy, jgenEta, jgenTheta, jgenPhi; 
    
    float j0genPx, j0genPy, j0genPz, j0genPt, j0genP3, j0genEt, j0genMt, j0genMass, j0genEnergy, j0genEta, j0genTheta, j0genPhi, j1genPx, j1genPy, j1genPz, j1genPt, j1genP3, j1genEt, j1genMt, j1genMass, j1genEnergy, j1genEta, j1genTheta, j1genPhi, j2genPx, j2genPy, j2genPz, j2genPt, j2genP3, j2genEt, j2genMt, j2genMass, j2genEnergy, j2genEta, j2genTheta, j2genPhi, j3genPx, j3genPy, j3genPz, j3genPt, j3genP3, j3genEt, j3genMt, j3genMass, j3genEnergy, j3genEta, j3genTheta, j3genPhi;

    float dEtajj, dEtaWW, dPhijj, dPhiWW,mjj;
    int isSignal,isMuMinus;
    std::vector<int> ParticleOut,ParticleIn,ParticleIntermediate,bQuark,tQuark,tQuarkStatus,bQuarkStatus,Lepton,Muon,LeptonStatus,MuonStatus,LeptonpdgId;
    
    int tQuarkCount = 0, bQuarkCount = 0, LepCount = 0, MuonCount = 0;

    tree->Branch("ParticleIn",&ParticleIn);
    tree->Branch("ParticleIntermediate",&ParticleIntermediate);
    tree->Branch("ParticleOut",&ParticleOut);
    tree->Branch("Lepton",&Lepton);
    tree->Branch("LeptonStatus",&LeptonStatus);
    tree->Branch("LeptonpdgId",&LeptonpdgId);
    tree->Branch("Muon",&Muon);
    tree->Branch("MuonStatus",&MuonStatus);
    tree->Branch("NumberOfLeptonsAndNu",&NumberOfLeptonsAndNu,"NumberOfLeptonsAndNu/I");
    tree->Branch("NumberOfMuonsAndNu",&NumberOfMuonsAndNu,"NumberOfMuonsAndNu/I");
    tree->Branch("bQuark",&bQuark);
    tree->Branch("NumberOfBQuark",&NumberOfBQuark,"NumberOfBQuark/I");
    tree->Branch("bQuarkStatus",&bQuarkStatus);
    tree->Branch("tQuark",&tQuark);
    tree->Branch("NumberOftQuark",&NumberOftQuark,"NumberOftQuark/I");
    tree->Branch("tQuarkStatus",&tQuarkStatus);
    tree->Branch("mWW",&mWW,"mWW/F");
    tree->Branch("mWLep",&mWLep,"mWLep/F");
    tree->Branch("mWHad",&mWHad,"mWHad/F");
    tree->Branch("costheta1",&costheta1,"costheta1/F");
    tree->Branch("costheta2",&costheta2,"costheta2/F");
    tree->Branch("costhetastar",&costhetastar,"costhetastar/F");
    tree->Branch("phi",&phi,"phi/F");
    tree->Branch("phi1",&phi1,"phi1/F");
    tree->Branch("dEtajj",&dEtajj,"dEtajj/F");
    tree->Branch("dEtaWW",&dEtaWW,"dEtaWW/F");
    tree->Branch("dPhijj",&dPhijj,"dPhijj/F");
    tree->Branch("dPhiWW",&dPhiWW,"dPhiWW/F");
    tree->Branch("mjj",&mjj,"mjj/F");
    
    tree->Branch("genMuonNumMuon" 	,&genMuonNumMuon,	"genMuonNumMuon/I");
    tree->Branch("genMuonCharge" 	,&genMuonCharge,	"genMuonCharge/I");
    tree->Branch("genMuonPx" 		,&genMuonPx,		"genMuonPx/F");
    tree->Branch("genMuonPy" 		,&genMuonPy,		"genMuonPy/F");
    tree->Branch("genMuonPz" 		,&genMuonPz,		"genMuonPz/F");
    tree->Branch("genMuonPt" 		,&genMuonPt,		"genMuonPt/F");

//    TClonesArray *LMuon = new TClonesArray("TLorentzVector");
//    TClonesArray &aaMuon = *LMuon;
//
//    tree->Branch("LgenMuon",&LMuon);

    tree->Branch("genMuonP3" 		,&genMuonP3,		"genMuonP3/F");
    tree->Branch("genMuonEt" 		,&genMuonEt,		"genMuonEt/F");
    tree->Branch("genMuonMt" 		,&genMuonMt,		"genMuonMt/F");
    tree->Branch("genMuonMass" 	,&genMuonMass,		"genMuonMass/F");
    tree->Branch("genMuonEnergy"	,&genMuonEnergy,	"genMuonEnergy/F");
    tree->Branch("genMuonEta" 		,&genMuonEta,		"genMuonEta/F");
    tree->Branch("genMuonTheta" 	,&genMuonTheta,		"genMuonTheta/F");
    tree->Branch("genMuonPhi" 		,&genMuonPhi,		"genMuonPhi/F");
    tree->Branch("genEleNumEle" 	,&genEleNumEle,		"genEleNumEle/I");
    tree->Branch("genEleCharge" 	,&genEleCharge,		"genEleCharge/I");
    tree->Branch("genElePx" 		,&genElePx,		"genElePx/F");
    tree->Branch("genElePy" 		,&genElePy,		"genElePy/F");
    tree->Branch("genElePz" 		,&genElePz,		"genElePz/F");
    tree->Branch("genElePt" 		,&genElePt,		"genElePt/F");
    tree->Branch("genEleP3" 		,&genEleP3,		"genEleP3/F");
    tree->Branch("genEleEt" 		,&genEleEt,		"genEleEt/F");
    tree->Branch("genEleMt" 		,&genEleMt,		"genEleMt/F");
    tree->Branch("genEleMass" 		,&genEleMass,		"genEleMass/F");
    tree->Branch("genEleEnergy" 	,&genEleEnergy,		"genEleEnergy/F");
    tree->Branch("genEleEta" 		,&genEleEta,		"genEleEta/F");
    tree->Branch("genEleTheta" 	,&genEleTheta,		"genEleTheta/F");
    tree->Branch("genElePhi" 		,&genElePhi,		"genElePhi/F");
    tree->Branch("mgenPx" 		,&mgenPx,		"mgenPx/F");
    tree->Branch("mgenPy" 		,&mgenPy,		"mgenPy/F");
    tree->Branch("mgenPz" 		,&mgenPz,		"mgenPz/F");
    tree->Branch("mgenPt" 		,&mgenPt,		"mgenPt/F");
    tree->Branch("mgenP3" 		,&mgenP3,		"mgenP3/F");
    tree->Branch("mgenEt" 		,&mgenEt,		"mgenEt/F");
    tree->Branch("mgenMt" 		,&mgenMt,		"mgenMt/F");
    tree->Branch("mgenMass" 		,&mgenMass,		"mgenMass/F");
    tree->Branch("mgenEnergy" 		,&mgenEnergy,		"mgenEnergy/F");
    tree->Branch("mgenEta" 		,&mgenEta,		"mgenEta/F");
    tree->Branch("mgenTheta" 		,&mgenTheta,		"mgenTheta/F");
    tree->Branch("mgenPhi" 		,&mgenPhi,		"mgenPhi/F");
//    tree->Branch("jgenPx" 		,&jgenPx,		"jgenPx/F");
//    tree->Branch("jgenPy" 		,&jgenPy,		"jgenPy/F");
//    tree->Branch("jgenPz" 		,&jgenPz,		"jgenPz/F");
//    tree->Branch("jgenPt" 		,&jgenPt,		"jgenPt/F");
//    tree->Branch("jgenP3" 		,&jgenP3,		"jgenP3/F");
//    tree->Branch("jgenEt" 		,&jgenEt,		"jgenEt/F");
//    tree->Branch("jgenMt" 		,&jgenMt,		"jgenMt/F");
//    tree->Branch("jgenMass" 		,&jgenMass,		"jgenMass/F");
//    tree->Branch("jgenEnergy" 		,&jgenEnergy,		"jgenEnergy/F");
//    tree->Branch("jgenEta" 		,&jgenEta,		"jgenEta/F");
//    tree->Branch("jgenTheta" 		,&jgenTheta,		"jgenTheta/F");
//    tree->Branch("jgenPhi" 		,&jgenPhi,		"jgenPhi/F");
///*
    tree->Branch("j0genPx" 		,&j0genPx,		"j0genPx/F");
    tree->Branch("j0genPy" 		,&j0genPy,		"j0genPy/F");
    tree->Branch("j0genPz" 		,&j0genPz,		"j0genPz/F");
    tree->Branch("j0genPt" 		,&j0genPt,		"j0genPt/F");
    tree->Branch("j0genP3" 		,&j0genP3,		"j0genP3/F");
    tree->Branch("j0genEt" 		,&j0genEt,		"j0genEt/F");
    tree->Branch("j0genMt" 		,&j0genMt,		"j0genMt/F");
    tree->Branch("j0genMass" 		,&j0genMass,		"j0genMass/F");
    tree->Branch("j0genEnergy" 		,&j0genEnergy,		"j0genEnergy/F");
    tree->Branch("j0genEta" 		,&j0genEta,		"j0genEta/F");
    tree->Branch("j0genTheta" 		,&j0genTheta,		"j0genTheta/F");
    tree->Branch("j0genPhi" 		,&j0genPhi,		"j0genPhi/F");
    tree->Branch("j1genPx" 		,&j1genPx,		"j1genPx/F");
    tree->Branch("j1genPy" 		,&j1genPy,		"j1genPy/F");
    tree->Branch("j1genPz" 		,&j1genPz,		"j1genPz/F");
    tree->Branch("j1genPt" 		,&j1genPt,		"j1genPt/F");
    tree->Branch("j1genP3" 		,&j1genP3,		"j1genP3/F");
    tree->Branch("j1genEt" 		,&j1genEt,		"j1genEt/F");
    tree->Branch("j1genMt" 		,&j1genMt,		"j1genMt/F");
    tree->Branch("j1genMass" 		,&j1genMass,		"j1genMass/F");
    tree->Branch("j1genEnergy" 		,&j1genEnergy,		"j1genEnergy/F");
    tree->Branch("j1genEta" 		,&j1genEta,		"j1genEta/F");
    tree->Branch("j1genTheta" 		,&j1genTheta,		"j1genTheta/F");
    tree->Branch("j1genPhi" 		,&j1genPhi,		"j1genPhi/F");
    tree->Branch("j2genPx" 		,&j2genPx,		"j2genPx/F");
    tree->Branch("j2genPy" 		,&j2genPy,		"j2genPy/F");
    tree->Branch("j2genPz" 		,&j2genPz,		"j2genPz/F");
    tree->Branch("j2genPt" 		,&j2genPt,		"j2genPt/F");
    tree->Branch("j2genP3" 		,&j2genP3,		"j2genP3/F");
    tree->Branch("j2genEt" 		,&j2genEt,		"j2genEt/F");
    tree->Branch("j2genMt" 		,&j2genMt,		"j2genMt/F");
    tree->Branch("j2genMass" 		,&j2genMass,		"j2genMass/F");
    tree->Branch("j2genEnergy" 		,&j2genEnergy,		"j2genEnergy/F");
    tree->Branch("j2genEta" 		,&j2genEta,		"j2genEta/F");
    tree->Branch("j2genTheta" 		,&j2genTheta,		"j2genTheta/F");
    tree->Branch("j2genPhi" 		,&j2genPhi,		"j2genPhi/F");
    tree->Branch("j3genPx" 		,&j3genPx,		"j3genPx/F");
    tree->Branch("j3genPy" 		,&j3genPy,		"j3genPy/F");
    tree->Branch("j3genPz" 		,&j3genPz,		"j3genPz/F");
    tree->Branch("j3genPt" 		,&j3genPt,		"j3genPt/F");
    tree->Branch("j3genP3" 		,&j3genP3,		"j3genP3/F");
    tree->Branch("j3genEt" 		,&j3genEt,		"j3genEt/F");
    tree->Branch("j3genMt" 		,&j3genMt,		"j3genMt/F");
    tree->Branch("j3genMass" 		,&j3genMass,		"j3genMass/F");
    tree->Branch("j3genEnergy" 		,&j3genEnergy,		"j3genEnergy/F");
    tree->Branch("j3genEta" 		,&j3genEta,		"j3genEta/F");
    tree->Branch("j3genTheta" 		,&j3genTheta,		"j3genTheta/F");
    tree->Branch("j3genPhi" 		,&j3genPhi,		"j3genPhi/F");

    tree->Branch("isSignal",&isSignal,"isSignal/I");
    tree->Branch("isMuMinus",&isMuMinus,"isMuMinus/I");
    
    //PG loop over bkg
    //PG -------------
    
    int BKGnumber = 0 ;
    int BKGnumberWithObj = 0 ;
    int VBFBKGnumber = 0 ;
    
    int NSignal = 0;
    int NTotal = 0;
    
    std::ifstream ifsbkg (argv[1]) ;
    // Create the Reader object
    LHEF::Reader bkgReader (ifsbkg) ;
    
    //PG loop over BKG
    while ( bkgReader.readEvent () ) {
        ++BKGnumber;
        if (BKGnumber % 100000 == 0) std::cout << "BKG event " << BKGnumber << "\n" ;
        //if (BKGnumber > 500000) break;
        
        std::vector<int> leptons ;      
        std::vector<int> finalQuarks ;      
        std::vector<int> initialQuarks ;   
        std::vector<int> intermediates ;
        std::vector<int> tops ;        
        //PG loop over particles in the event
	bQuarkCount = 0;
	tQuarkCount = 0;
	LepCount = 0;
	MuonCount = 0;
//	std::cout<<"For event number 1"<<std::endl;
        for (int iPart = 0 ; iPart < bkgReader.hepeup.IDUP.size (); ++iPart){
            
            int mother1 = bkgReader.hepeup.MOTHUP.at(iPart).first;
            
//            std::cout << "\t part type [" << iPart << "] " << bkgReader.hepeup.IDUP.at (iPart)
//            << "\t status " << bkgReader.hepeup.ISTUP.at(iPart)
//            << "\t mother " << bkgReader.hepeup.MOTHUP.at(iPart).first
//            << "\t mother id " << bkgReader.hepeup.IDUP.at(mother1)
//            << "\n" ;
            
	if (bkgReader.hepeup.ISTUP.at (iPart) == 1 && abs(bkgReader.hepeup.IDUP.at(iPart)) == 13 )
		{
		TLorentzVector muon
		 (
		 bkgReader.hepeup.PUP.at(iPart).at(0),
		 bkgReader.hepeup.PUP.at(iPart).at(1),
		 bkgReader.hepeup.PUP.at(iPart).at(2),
		 bkgReader.hepeup.PUP.at(iPart).at(3)
		 );
		 //new(aaMuon[iPart]) TLorentzVector(muon(0),muon(1),muon(2),muon(3));

		 genMuonPx 	= muon(0); 
		 genMuonPy 	= muon(1);
		 genMuonPz 	= muon(2);
		 genMuonPt 	= muon.Perp();
		 genMuonP3 	= (muon.Vect()).Mag();
		 genMuonEt 	= muon.Et(); 
		 genMuonMt 	= muon.Mt();
		 genMuonMass 	= muon.M();
		 genMuonEnergy 	= muon(3);
                 genMuonEta 	= muon.Eta();
		 genMuonTheta	= muon.Theta();
                 genMuonPhi 	= muon.Phi();
		 }
	if (bkgReader.hepeup.ISTUP.at (iPart) == 1 && abs(bkgReader.hepeup.IDUP.at(iPart)) == 11 )
		{
		TLorentzVector ele
		 (
		 bkgReader.hepeup.PUP.at(iPart).at(0),
		 bkgReader.hepeup.PUP.at(iPart).at(1),
		 bkgReader.hepeup.PUP.at(iPart).at(2),
		 bkgReader.hepeup.PUP.at(iPart).at(3)
		 );
		 genElePx 	= ele(0); 
		 genElePy 	= ele(1);
		 genElePz 	= ele(2);
		 genElePt 	= ele.Perp();
		 genEleP3 	= (ele.Vect()).Mag();
		 genEleEt 	= ele.Et(); 
		 genEleMt 	= ele.Mt();
		 genEleMass 	= ele.M();
		 genEleEnergy 	= ele(3);
                 genEleEta 	= ele.Eta();
		 genEleTheta	= ele.Theta();
                 genElePhi 	= ele.Phi();
		 }
	if (bkgReader.hepeup.ISTUP.at (iPart) == 1 && (abs(bkgReader.hepeup.IDUP.at(iPart)) == 12 || bkgReader.hepeup.ISTUP.at (iPart) == 1 && abs(bkgReader.hepeup.IDUP.at(iPart)) == 14) )
		{
		TLorentzVector met
		 (
		 bkgReader.hepeup.PUP.at(iPart).at(0),
		 bkgReader.hepeup.PUP.at(iPart).at(1),
		 bkgReader.hepeup.PUP.at(iPart).at(2),
		 bkgReader.hepeup.PUP.at(iPart).at(3)
		 );
		 mgenPx 	= met(0); 
		 mgenPy 	= met(1);
		 mgenPz 	= met(2);
		 mgenPt 	= met.Perp();
		 mgenP3 	= (met.Vect()).Mag();
		 mgenEt 	= met.Et(); 
		 mgenMt 	= met.Mt();
		 mgenMass 	= met.M();
		 mgenEnergy 	= met(3);
                 mgenEta 	= met.Eta();
		 mgenTheta	= met.Theta();
                 mgenPhi 	= met.Phi();
		 }

            //PG incoming particle          
            if (bkgReader.hepeup.ISTUP.at (iPart) == -1){
                initialQuarks.push_back (iPart) ;
            }

	    //All final state particles
	    if (bkgReader.hepeup.ISTUP.at (iPart) == 1){
		ParticleOut.push_back(bkgReader.hepeup.IDUP.at (iPart));
	    }
	    if (bkgReader.hepeup.ISTUP.at (iPart) == -1){
		ParticleIn.push_back(bkgReader.hepeup.IDUP.at (iPart));
	    }
	    if (bkgReader.hepeup.ISTUP.at (iPart) == 2 || bkgReader.hepeup.ISTUP.at (iPart) == -2){
		ParticleIntermediate.push_back(bkgReader.hepeup.IDUP.at (iPart));
	    }
	    if (abs(bkgReader.hepeup.IDUP.at (iPart))==5){
		bQuarkCount++;
		bQuark.push_back(1);
		bQuarkStatus.push_back(bkgReader.hepeup.ISTUP.at (iPart));
	    }


	    if (abs(bkgReader.hepeup.IDUP.at (iPart))==6){
		tQuarkCount++;
		tQuark.push_back(1);
		tQuarkStatus.push_back(bkgReader.hepeup.ISTUP.at (iPart));
		//std::cout<<"found t quark\n";
	    }


	    if (abs(bkgReader.hepeup.IDUP.at (iPart))==11 || abs(bkgReader.hepeup.IDUP.at (iPart))==13 || abs(bkgReader.hepeup.IDUP.at (iPart))==15){
		LepCount++;
		Lepton.push_back(1);
		LeptonStatus.push_back(bkgReader.hepeup.ISTUP.at (iPart));
		LeptonpdgId.push_back(bkgReader.hepeup.IDUP.at (iPart));
	    }
            //PG outgoing particles          
            if (bkgReader.hepeup.ISTUP.at (iPart) == 1){
                //PG leptons
                if (abs (bkgReader.hepeup.IDUP.at (iPart)) == 11 ||   //PG electron
                    abs (bkgReader.hepeup.IDUP.at (iPart)) == 13 ||   //PG muon
                    abs (bkgReader.hepeup.IDUP.at (iPart)) == 15 ||   //PG tau
                    abs (bkgReader.hepeup.IDUP.at (iPart)) == 12 ||   //PG neutrino
                    abs (bkgReader.hepeup.IDUP.at (iPart)) == 14 ||   //PG neutrino
                    abs (bkgReader.hepeup.IDUP.at (iPart)) == 16)     //PG neutrino                    
                    {
                    leptons.push_back (iPart) ;
                    } //PG leptons
                else
                    {
                    finalQuarks.push_back (iPart) ;
                    }
                
            } 
            
            //PG intermediates
            if (bkgReader.hepeup.ISTUP.at(iPart) == 2){
                intermediates.push_back (iPart) ;
            }
            
            //PG tops
            if (abs(bkgReader.hepeup.IDUP.at(iPart)) == 6){
                tops.push_back (iPart) ;
            }
        } //PG loop over particles in the event
	 if(bQuarkCount != 0) 
	 	{
	 	NumberOfBQuark = bQuarkCount;
		}
	else 
		NumberOfBQuark = -10;

	if(tQuarkCount != 0)
		{	
		NumberOftQuark = tQuarkCount;
		}
	else 
		NumberOftQuark = -10;
    
	if(LepCount != 0)
		{	
		NumberOfLeptonsAndNu = LepCount;
		}
	else 
		NumberOfLeptonsAndNu = -10;

	if(MuonCount != 0)
		{	
		NumberOfMuonsAndNu = MuonCount;
		}
	else 
		NumberOfMuonsAndNu = -10;
        // --------------- Indices for final state particles  -------------------
        int i_olep_part = -1;
        int i_olep_anti = -1;        
        int i_wqrk_1 = -1;
        int i_wqrk_2 = -1;        
        int i_iqrk_1 = -1;
        int i_iqrk_2 = -1;        

        int tmpfill1 = 0;
        int signalFlag = 0;
        int signalWCtr = 0;
        isMuMinus = 0;
        
        if (leptons.size() == 2){
            if (bkgReader.hepeup.IDUP.at(leptons.at(0)) > 0){
                i_olep_part = leptons.at(0);
                i_olep_anti = leptons.at(1);
                if (bkgReader.hepeup.IDUP.at(leptons.at(0)) == 11 ||   //PG electron
                    bkgReader.hepeup.IDUP.at(leptons.at(0)) == 13 ||   //PG muon
                    bkgReader.hepeup.IDUP.at(leptons.at(0)) == 15) isMuMinus = 1;           
            }
            else{
                i_olep_part = leptons.at(1);
                i_olep_anti = leptons.at(0);    
                if (bkgReader.hepeup.IDUP.at(leptons.at(1)) == 11 ||   //PG electron
                    bkgReader.hepeup.IDUP.at(leptons.at(1)) == 13 ||   //PG muon
                    bkgReader.hepeup.IDUP.at(leptons.at(1)) == 15) isMuMinus = 1;           
                            
            }
        }
        else{
            std::cout << "Problem!" << std::endl;
        }
    std::cout<<"####################### Ramkrishna ######################";
        
        // --------------- If signal, find the quarks from the W  -------------------
        if (finalQuarks.size() == 4){
            for (unsigned int a = 0; a < finalQuarks.size(); ++a ){
                int tmpMoth = bkgReader.hepeup.MOTHUP.at(finalQuarks.at(a)).first - 1;

                if ( abs(bkgReader.hepeup.IDUP.at(tmpMoth)) == 24 && bkgReader.hepeup.IDUP.at(finalQuarks.at(a)) > 0 ){
                    signalWCtr++;
                }
                if ( abs(bkgReader.hepeup.IDUP.at(tmpMoth)) == 24 && bkgReader.hepeup.IDUP.at(finalQuarks.at(a)) < 0 ){
                    signalWCtr++;
                }
                if ( abs(bkgReader.hepeup.IDUP.at(tmpMoth)) != 24 && tmpfill1){
                    signalWCtr++;
                }
                if ( abs(bkgReader.hepeup.IDUP.at(tmpMoth)) != 24 && !tmpfill1){
                    signalWCtr++;
                    tmpfill1++;
                }
            }
        }
        else{
            std::cout << "Problem!" << std::endl;
        }
        
        if (signalWCtr == 4 && tops.size() == 0){ signalFlag = 1; NSignal++; }
        
        // --------------- Assign quarks based on W invariant mass -------------------
        float distanceToWMass = 9999.;
        for (unsigned int a = 0; a < finalQuarks.size(); ++a ){
            for (unsigned int b = a+1; b < finalQuarks.size(); ++b ){
                TLorentzVector qrk0
                (
                 bkgReader.hepeup.PUP.at (finalQuarks.at (a)).at (0), //PG px
                 bkgReader.hepeup.PUP.at (finalQuarks.at (a)).at (1), //PG py
                 bkgReader.hepeup.PUP.at (finalQuarks.at (a)).at (2), //PG pz
                 bkgReader.hepeup.PUP.at (finalQuarks.at (a)).at (3) //PG E
                 ) ;
                TLorentzVector qrk1
                (
                 bkgReader.hepeup.PUP.at (finalQuarks.at (b)).at (0), //PG px
                 bkgReader.hepeup.PUP.at (finalQuarks.at (b)).at (1), //PG py
                 bkgReader.hepeup.PUP.at (finalQuarks.at (b)).at (2), //PG pz
                 bkgReader.hepeup.PUP.at (finalQuarks.at (b)).at (3) //PG E
                 ) ;

                float tmpDistance = abs( (qrk0+qrk1).M() - 80.2 );
                if (tmpDistance < distanceToWMass){
                    i_wqrk_1 = finalQuarks.at(a);
                    i_wqrk_2 = finalQuarks.at(b);                    
                    distanceToWMass = tmpDistance;
                }
            }
        }
        
        // quarks based on particle-antiparticle
        if (bkgReader.hepeup.IDUP.at(i_wqrk_1) < 0){
            int tmpint = i_wqrk_1;
            i_wqrk_1 = i_wqrk_2;
            i_wqrk_2 = tmpint;
        }
        
        // assign the other quarks
        std::vector<int> finalQuarksNotW;
        for (unsigned int a = 0; a < finalQuarks.size(); ++a ){
            if (finalQuarks.at(a) != i_wqrk_1 && finalQuarks.at(a) != i_wqrk_2){
                finalQuarksNotW.push_back( finalQuarks.at(a) );
            }
        }
        if (finalQuarksNotW.size() == 2){
            i_iqrk_1 = finalQuarksNotW.at(0);
            i_iqrk_2 = finalQuarksNotW.at(1);                
        }

//        std::cout << "signalFlag = " << signalFlag << std::endl;
//        std::cout << "isMuMinus = " << isMuMinus << std::endl;        
//        std::cout << "lep1 = " << bkgReader.hepeup.IDUP.at(i_olep_part) << std::endl;
//        std::cout << "lep2 = " << bkgReader.hepeup.IDUP.at(i_olep_anti) << std::endl;        
//        std::cout << "qrk1 = " << bkgReader.hepeup.IDUP.at(i_wqrk_1) << std::endl;
//        std::cout << "qrk2 = " << bkgReader.hepeup.IDUP.at(i_wqrk_2) << std::endl;        
//        std::cout << "i-qrk1 = " << bkgReader.hepeup.IDUP.at(i_iqrk_1) << std::endl;
//        std::cout << "i-qrk2 = " << bkgReader.hepeup.IDUP.at(i_iqrk_2) << std::endl;        

        TLorentzVector fs_lep0
        (
         bkgReader.hepeup.PUP.at(i_olep_part).at(0), //PG px
         bkgReader.hepeup.PUP.at(i_olep_part).at(1), //PG py
         bkgReader.hepeup.PUP.at(i_olep_part).at(2), //PG pz
         bkgReader.hepeup.PUP.at(i_olep_part).at(3) //PG E
         ) ;
        TLorentzVector fs_lep1
        (
         bkgReader.hepeup.PUP.at(i_olep_anti).at(0), //PG px
         bkgReader.hepeup.PUP.at(i_olep_anti).at(1), //PG py
         bkgReader.hepeup.PUP.at(i_olep_anti).at(2), //PG pz
         bkgReader.hepeup.PUP.at(i_olep_anti).at(3) //PG E
         ) ;
    
        TLorentzVector fs_Wqrk0
        (
         bkgReader.hepeup.PUP.at(i_wqrk_1).at(0), //PG px
         bkgReader.hepeup.PUP.at(i_wqrk_1).at(1), //PG py
         bkgReader.hepeup.PUP.at(i_wqrk_1).at(2), //PG pz
         bkgReader.hepeup.PUP.at(i_wqrk_1).at(3) //PG E
         ) ;
//	 	jgenPx.push_back( 	 fs_Wqrk0(0)); 
//		jgenPy.push_back( 	 fs_Wqrk0(1));
//		jgenPz.push_back( 	 fs_Wqrk0(2));
//		jgenPt.push_back( 	 fs_Wqrk0.Perp());
//		jgenP3.push_back( 	 (fs_Wqrk0.Vect()).Mag());
//		jgenEt.push_back( 	 fs_Wqrk0.Et()); 
//		jgenMt.push_back( 	 fs_Wqrk0.Mt());
//		jgenMass.push_back( 	 fs_Wqrk0.M());
//		jgenEnergy.push_back( 	 fs_Wqrk0(3));
//		jgenEta .push_back(	 fs_Wqrk0.Eta());
//		jgenTheta.push_back( 	 fs_Wqrk0.Theta());
//		jgenPhi .push_back(	 fs_Wqrk0.Phi());

        TLorentzVector fs_Wqrk1
        (
         bkgReader.hepeup.PUP.at(i_wqrk_2).at(0), //PG px
         bkgReader.hepeup.PUP.at(i_wqrk_2).at(1), //PG py
         bkgReader.hepeup.PUP.at(i_wqrk_2).at(2), //PG pz
         bkgReader.hepeup.PUP.at(i_wqrk_2).at(3) //PG E
         ) ;
//	 	jgenPx.push_back( 	 fs_Wqrk1(0)); 
//		jgenPy.push_back( 	 fs_Wqrk1(1));
//		jgenPz.push_back( 	 fs_Wqrk1(2));
//		jgenPt.push_back( 	 fs_Wqrk1.Perp());
//		jgenP3.push_back( 	 (fs_Wqrk1.Vect()).Mag());
//		jgenEt.push_back( 	 fs_Wqrk1.Et()); 
//		jgenMt.push_back( 	 fs_Wqrk1.Mt());
//		jgenMass.push_back( 	 fs_Wqrk1.M());
//		jgenEnergy.push_back( 	 fs_Wqrk1(3));
//		jgenEta .push_back(	 fs_Wqrk1.Eta());
//		jgenTheta.push_back( 	 fs_Wqrk1.Theta());
//		jgenPhi .push_back(	 fs_Wqrk1.Phi());

        TLorentzVector fs_Iqrk0
        (
         bkgReader.hepeup.PUP.at(i_iqrk_1).at(0), //PG px
         bkgReader.hepeup.PUP.at(i_iqrk_1).at(1), //PG py
         bkgReader.hepeup.PUP.at(i_iqrk_1).at(2), //PG pz
         bkgReader.hepeup.PUP.at(i_iqrk_1).at(3) //PG E
         ) ;
//	 	jgenPx.push_back( 	 fs_Iqrk0(0)); 
//		jgenPy.push_back( 	 fs_Iqrk0(1));
//		jgenPz.push_back( 	 fs_Iqrk0(2));
//		jgenPt.push_back( 	 fs_Iqrk0.Perp());
//		jgenP3.push_back( 	 (fs_Iqrk0.Vect()).Mag());
//		jgenEt.push_back( 	 fs_Iqrk0.Et()); 
//		jgenMt.push_back( 	 fs_Iqrk0.Mt());
//		jgenMass.push_back( 	 fs_Iqrk0.M());
//		jgenEnergy.push_back( 	 fs_Iqrk0(3));
//		jgenEta .push_back(	 fs_Iqrk0.Eta());
//		jgenTheta.push_back( 	 fs_Iqrk0.Theta());
//		jgenPhi .push_back(	 fs_Iqrk0.Phi());

        TLorentzVector fs_Iqrk1
        (
         bkgReader.hepeup.PUP.at(i_iqrk_2).at(0), //PG px
         bkgReader.hepeup.PUP.at(i_iqrk_2).at(1), //PG py
         bkgReader.hepeup.PUP.at(i_iqrk_2).at(2), //PG pz
         bkgReader.hepeup.PUP.at(i_iqrk_2).at(3) //PG E
         ) ;
//	 	jgenPx.push_back( 	 fs_Iqrk1(0)); 
//		jgenPy.push_back( 	 fs_Iqrk1(1));
//		jgenPz.push_back( 	 fs_Iqrk1(2));
//		jgenPt.push_back( 	 fs_Iqrk1.Perp());
//		jgenP3.push_back( 	 (fs_Iqrk1.Vect()).Mag());
//		jgenEt.push_back( 	 fs_Iqrk1.Et()); 
//		jgenMt.push_back( 	 fs_Iqrk1.Mt());
//		jgenMass.push_back( 	 fs_Iqrk1.M());
//		jgenEnergy.push_back( 	 fs_Iqrk1(3));
//		jgenEta .push_back(	 fs_Iqrk1.Eta());
//		jgenTheta.push_back( 	 fs_Iqrk1.Theta());
//		jgenPhi .push_back(	 fs_Iqrk1.Phi());

        

        TLorentzVector p4_WHad = fs_Wqrk0 + fs_Wqrk1;
        TLorentzVector p4_WLep = fs_lep0 + fs_lep1;        
        TLorentzVector p4_WW = p4_WHad + p4_WLep;
        
        double a_costheta1, a_costheta2, a_costhetastar, a_Phi, a_Phi1;
        computeAngles( p4_WW, p4_WLep, fs_lep0, fs_lep1, p4_WHad, fs_Wqrk0, fs_Wqrk1, 
                      a_costheta1, a_costheta2, a_Phi, a_costhetastar, a_Phi1);
        
	
//	/*
		j0genPx 	= fs_Iqrk0(0); 
		j0genPy 	= fs_Iqrk0(1);
		j0genPz 	= fs_Iqrk0(2);
		j0genPt 	= fs_Iqrk0.Perp();
		j0genP3 	= (fs_Iqrk0.Vect()).Mag();
		j0genEt 	= fs_Iqrk0.Et(); 
		j0genMt 	= fs_Iqrk0.Mt();
		j0genMass 	= fs_Iqrk0.M();
		j0genEnergy 	= fs_Iqrk0(3);
		j0genEta 	= fs_Iqrk0.Eta();
		j0genTheta 	= fs_Iqrk0.Theta();
		j0genPhi 	= fs_Iqrk0.Phi();
		j1genPx 	= fs_Iqrk1(0); 
		j1genPy 	= fs_Iqrk1(1);
		j1genPz 	= fs_Iqrk1(2);
		j1genPt 	= fs_Iqrk1.Perp();
		j1genP3 	= (fs_Iqrk1.Vect()).Mag();
		j1genEt 	= fs_Iqrk1.Et(); 
		j1genMt 	= fs_Iqrk1.Mt();
		j1genMass 	= fs_Iqrk1.M();
		j1genEnergy 	= fs_Iqrk1(3);
		j1genEta 	= fs_Iqrk1.Eta();
		j1genTheta 	= fs_Iqrk1.Theta();
		j1genPhi 	= fs_Iqrk1.Phi();
		j2genPx 	= fs_Wqrk0(0); 
		j2genPy 	= fs_Wqrk0(1);
		j2genPz 	= fs_Wqrk0(2);
		j2genPt 	= fs_Wqrk0.Perp();
		j2genP3 	= (fs_Wqrk0.Vect()).Mag();
		j2genEt 	= fs_Wqrk0.Et(); 
		j2genMt 	= fs_Wqrk0.Mt();
		j2genMass 	= fs_Wqrk0.M();
		j2genEnergy 	= fs_Wqrk0(3);
		j2genEta 	= fs_Wqrk0.Eta();
		j2genTheta 	= fs_Wqrk0.Theta();
		j2genPhi 	= fs_Wqrk0.Phi();
		j3genPx 	= fs_Wqrk1(0); 
		j3genPy 	= fs_Wqrk1(1);
		j3genPz 	= fs_Wqrk1(2);
		j3genPt 	= fs_Wqrk1.Perp();
		j3genP3 	= (fs_Wqrk1.Vect()).Mag();
		j3genEt 	= fs_Wqrk1.Et(); 
		j3genMt 	= fs_Wqrk1.Mt();
		j3genMass 	= fs_Wqrk1.M();
		j3genEnergy 	= fs_Wqrk1(3);
		j3genEta 	= fs_Wqrk1.Eta();
		j3genTheta 	= fs_Wqrk1.Theta();
		j3genPhi 	= fs_Wqrk1.Phi();
//*/

        mWW = (float) p4_WW.M();
        mWLep = (float) p4_WLep.M();
        mWHad = (float) p4_WHad.M();        
        costheta1 = (float) a_costheta1;                
        costheta2 = (float) a_costheta2;
        phi = (float) a_Phi;
        costhetastar = (float) a_costhetastar;
        phi1 = (float) a_Phi1;

        dEtajj = (float) fabs( fs_Iqrk0.Eta() - fs_Iqrk1.Eta() );
        dEtaWW = (float) fabs( p4_WHad.Eta() - p4_WLep.Eta() );
        dPhijj = (float) deltaPhi(fs_Iqrk0.Phi(),fs_Iqrk1.Phi());     
	dPhiWW = (float) deltaPhi(p4_WLep.Phi(),p4_WHad.Phi());
        mjj = (float) (fs_Iqrk0 + fs_Iqrk1).M();

        isSignal = signalFlag;
        
        tree->Fill();
	ParticleOut.clear();
	ParticleIn.clear();
	ParticleIntermediate.clear();
	bQuark.clear();
	tQuark.clear();
	bQuarkStatus.clear();
	tQuarkStatus.clear();

//	jgenPx.clear();
//	jgenPy.clear();
//	jgenPz.clear();
//	jgenPt.clear();
//	jgenP3.clear();
//	jgenEt.clear();
//	jgenMt.clear();
//	jgenMass.clear();
//	jgenEnergy.clear();
//	jgenEta.clear();
//	jgenTheta.clear();
//	jgenPhi.clear(); 
	Lepton.clear();
	Muon.clear();
	LeptonStatus.clear();
	LeptonpdgId.clear();
	MuonStatus.clear();

        
    }
    
    std::cout << "BKGnumber = " << BKGnumber << ", and NSignal = " << NSignal << std::endl;
    
    file.cd();
    tree->Write();
    file.Close();
    
    
// Now we are done.
return 0 ;
}

//////////////////////////////////
//// P A P E R   4 - V E C T O R   D E F I N I T I O N   O F   P H I   A N D   P H I 1
//////////////////////////////////
void computeAngles(TLorentzVector thep4H, TLorentzVector thep4Z1, TLorentzVector thep4M11, TLorentzVector thep4M12, TLorentzVector thep4Z2, TLorentzVector thep4M21, TLorentzVector thep4M22, double& costheta1, double& costheta2, double& Phi, double& costhetastar, double& Phi1){
    
    ///////////////////////////////////////////////
    // check for z1/z2 convention, redefine all 4 vectors with convention
    ///////////////////////////////////////////////	
    TLorentzVector p4H, p4Z1, p4M11, p4M12, p4Z2, p4M21, p4M22;
    p4H = thep4H;
    
    p4Z1 = thep4Z1; p4M11 = thep4M11; p4M12 = thep4M12;
    p4Z2 = thep4Z2; p4M21 = thep4M21; p4M22 = thep4M22;
    //// costhetastar
	TVector3 boostX = -(thep4H.BoostVector());
	TLorentzVector thep4Z1inXFrame( p4Z1 );
	TLorentzVector thep4Z2inXFrame( p4Z2 );	
	thep4Z1inXFrame.Boost( boostX );
	thep4Z2inXFrame.Boost( boostX );
	TVector3 theZ1X_p3 = TVector3( thep4Z1inXFrame.X(), thep4Z1inXFrame.Y(), thep4Z1inXFrame.Z() );
	TVector3 theZ2X_p3 = TVector3( thep4Z2inXFrame.X(), thep4Z2inXFrame.Y(), thep4Z2inXFrame.Z() );    
    costhetastar = theZ1X_p3.CosTheta();
    
    //// --------------------------- costheta1
    TVector3 boostV1 = -(thep4Z1.BoostVector());
    TLorentzVector p4M11_BV1( p4M11 );
	TLorentzVector p4M12_BV1( p4M12 );	
    TLorentzVector p4M21_BV1( p4M21 );
	TLorentzVector p4M22_BV1( p4M22 );
    p4M11_BV1.Boost( boostV1 );
	p4M12_BV1.Boost( boostV1 );
	p4M21_BV1.Boost( boostV1 );
	p4M22_BV1.Boost( boostV1 );
    
    TLorentzVector p4V2_BV1 = p4M21_BV1 + p4M22_BV1;
    //// costheta1
    costheta1 = -p4V2_BV1.Vect().Dot( p4M11_BV1.Vect() )/p4V2_BV1.Vect().Mag()/p4M11_BV1.Vect().Mag();
    
    //// --------------------------- costheta2
    TVector3 boostV2 = -(thep4Z2.BoostVector());
    TLorentzVector p4M11_BV2( p4M11 );
	TLorentzVector p4M12_BV2( p4M12 );	
    TLorentzVector p4M21_BV2( p4M21 );
	TLorentzVector p4M22_BV2( p4M22 );
    p4M11_BV2.Boost( boostV2 );
	p4M12_BV2.Boost( boostV2 );
	p4M21_BV2.Boost( boostV2 );
	p4M22_BV2.Boost( boostV2 );
    
    TLorentzVector p4V1_BV2 = p4M11_BV2 + p4M12_BV2;
    //// costheta2
    costheta2 = -p4V1_BV2.Vect().Dot( p4M21_BV2.Vect() )/p4V1_BV2.Vect().Mag()/p4M21_BV2.Vect().Mag();
    
    //// --------------------------- Phi and Phi1
    //    TVector3 boostX = -(thep4H.BoostVector());
    TLorentzVector p4M11_BX( p4M11 );
	TLorentzVector p4M12_BX( p4M12 );	
    TLorentzVector p4M21_BX( p4M21 );
	TLorentzVector p4M22_BX( p4M22 );	
    
	p4M11_BX.Boost( boostX );
	p4M12_BX.Boost( boostX );
	p4M21_BX.Boost( boostX );
	p4M22_BX.Boost( boostX );
    
    TVector3 tmp1 = p4M11_BX.Vect().Cross( p4M12_BX.Vect() );
    TVector3 tmp2 = p4M21_BX.Vect().Cross( p4M22_BX.Vect() );    
    
    TVector3 normal1_BX( tmp1.X()/tmp1.Mag(), tmp1.Y()/tmp1.Mag(), tmp1.Z()/tmp1.Mag() ); 
    TVector3 normal2_BX( tmp2.X()/tmp2.Mag(), tmp2.Y()/tmp2.Mag(), tmp2.Z()/tmp2.Mag() ); 
    
    //// Phi
    TLorentzVector p4Z1_BX = p4M11_BX + p4M12_BX;    
    double tmpSgnPhi = p4Z1_BX.Vect().Dot( normal1_BX.Cross( normal2_BX) );
    double sgnPhi = tmpSgnPhi/fabs(tmpSgnPhi);
    Phi = sgnPhi * acos( -1.*normal1_BX.Dot( normal2_BX) );
    
    
    //////////////
    
    TVector3 beamAxis(0,0,1);
    TVector3 tmp3 = (p4M11_BX + p4M12_BX).Vect();
    
    TVector3 p3V1_BX( tmp3.X()/tmp3.Mag(), tmp3.Y()/tmp3.Mag(), tmp3.Z()/tmp3.Mag() );
    TVector3 tmp4 = beamAxis.Cross( p3V1_BX );
    TVector3 normalSC_BX( tmp4.X()/tmp4.Mag(), tmp4.Y()/tmp4.Mag(), tmp4.Z()/tmp4.Mag() );
    
    //// Phi1
    double tmpSgnPhi1 = p4Z1_BX.Vect().Dot( normal1_BX.Cross( normalSC_BX) );
    double sgnPhi1 = tmpSgnPhi1/fabs(tmpSgnPhi1);    
    Phi1 = sgnPhi1 * acos( normal1_BX.Dot( normalSC_BX) );    
    
    //    std::cout << "extractAngles: " << std::endl;
    //    std::cout << "costhetastar = " << costhetastar << ", costheta1 = " << costheta1 << ", costheta2 = " << costheta2 << std::endl;
    //    std::cout << "Phi = " << Phi << ", Phi1 = " << Phi1 << std::endl;    
    
}

