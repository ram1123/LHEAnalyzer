/*
 * =====================================================================================
 *
 *       Filename:  LHEanalyzer.cpp
 *
 *    Description:  This macro reades the lhe file and convert it into root file.
 *
 *        Version:  1.0
 *        Created:  Friday 02 January 2015 04:45:09  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nhan Viet Tran
 *	Edited By:  Ramkrishna Sharma
 *   Organization:  CERN
 *
 * =====================================================================================
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
#include "TClonesArray.h"
#include "TApplication.h"
// #include "LHEanalyzer.h"
// #include "hFactory.h"
// #include "h2Factory.h"
// #include "hFunctions.h"

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

    // Name of variables:
    // costheta1 :
    // costheta2 :
    // costhetastar :
    // phi :
    // phi1 :
    // costhetaV1 :
    // costhetaV2 :
    //

 */

void computeAngles(TLorentzVector thep4H, TLorentzVector thep4Z1, TLorentzVector thep4M11, TLorentzVector thep4M12, TLorentzVector thep4Z2, TLorentzVector thep4M21, TLorentzVector thep4M22, double &costheta1, double &costheta2, double &Phi, double &costhetastar, double &Phi1);

double deltaPhi(double phi1, double phi2)
{
    double deltaphi = fabs(phi1 - phi2);
    if (deltaphi > 6.283185308)
        deltaphi -= 6.283185308;
    if (deltaphi > 3.141592654)
        deltaphi = 6.283185308 - deltaphi;
    return deltaphi;
}

//! ========================================================================================

int main(int argc, char **argv)
{

    // gSystem->Load("libPhysics");

    // TApplication a("a", 0, 0); // just to make sure that the autoloading of ROOT libraries works

    TFile file(argv[2], "RECREATE");
    file.SetCompressionLevel(2);
    //   TFile file("phantom.root","RECREATE");
    TTree *tree = new TTree("tree", "Particles Info");

    float mWW, mWLep, mWHad, costheta1, costheta2, costhetastar, phi, phi1;
    float costhetaV1, costhetaV2;
    float costhetaV3, costhetaV4;
    float dEtajj, dPhijj, mjj;
    int isSignal, isMuMinus;
    float Lep0_px, Lep0_py, Lep0_pz, Lep0_pt, Lep0_eta, Lep0_theta, Lep0_phi, Lep0_E;
    float Lep1_px, Lep1_py, Lep1_pz, Lep1_pt, Lep1_eta, Lep1_theta, Lep1_phi, Lep1_E;
    float Wqrk0_px, Wqrk0_py, Wqrk0_pz, Wqrk0_pt, Wqrk0_eta, Wqrk0_theta, Wqrk0_phi, Wqrk0_E;
    float Wqrk1_px, Wqrk1_py, Wqrk1_pz, Wqrk1_pt, Wqrk1_eta, Wqrk1_theta, Wqrk1_phi, Wqrk1_E;
    float Iqrk0_px, Iqrk0_py, Iqrk0_pz, Iqrk0_pt, Iqrk0_eta, Iqrk0_theta, Iqrk0_phi, Iqrk0_E;
    float Iqrk1_px, Iqrk1_py, Iqrk1_pz, Iqrk1_pt, Iqrk1_eta, Iqrk1_theta, Iqrk1_phi, Iqrk1_E;

    //    tree->Branch( "",	&	,	"/F" );
    tree->Branch("Lep0_theta", &Lep0_theta, "Lep0_theta/F");
    tree->Branch("Lep1_theta", &Lep1_theta, "Lep1_theta/F");
    tree->Branch("Wqrk0_theta", &Wqrk0_theta, "Wqrk0_theta/F");
    tree->Branch("Wqrk1_theta", &Wqrk1_theta, "Wqrk1_theta/F");
    tree->Branch("Iqrk0_theta", &Iqrk0_theta, "Iqrk0_theta/F");
    tree->Branch("Iqrk1_theta", &Iqrk1_theta, "Iqrk1_theta/F");
    tree->Branch("Lep0_phi", &Lep0_phi, "Lep0_phi/F");
    tree->Branch("Lep1_phi", &Lep1_phi, "Lep1_phi/F");
    tree->Branch("Wqrk0_phi", &Wqrk0_phi, "Wqrk0_phi/F");
    tree->Branch("Wqrk1_phi", &Wqrk1_phi, "Wqrk1_phi/F");
    tree->Branch("Iqrk0_phi", &Iqrk0_phi, "Iqrk0_phi/F");
    tree->Branch("Iqrk1_phi", &Iqrk1_phi, "Iqrk1_phi/F");
    tree->Branch("Iqrk1_eta", &Iqrk1_eta, "Iqrk1_eta/F");
    tree->Branch("Iqrk1_pt", &Iqrk1_pt, "Iqrk1_pt/F");
    tree->Branch("Iqrk0_eta", &Iqrk0_eta, "Iqrk0_eta/F");
    tree->Branch("Iqrk0_pt", &Iqrk0_pt, "Iqrk0_pt/F");
    tree->Branch("Wqrk1_eta", &Wqrk1_eta, "Wqrk1_eta/F");
    tree->Branch("Wqrk1_pt", &Wqrk1_pt, "Wqrk1_pt/F");
    tree->Branch("Wqrk0_eta", &Wqrk0_eta, "Wqrk0_eta/F");
    tree->Branch("Wqrk0_pt", &Wqrk0_pt, "Wqrk0_pt/F");
    tree->Branch("Lep1_eta", &Lep1_eta, "Lep1_eta/F");
    tree->Branch("Lep1_pt", &Lep1_pt, "Lep1_pt/F");
    tree->Branch("Lep0_eta", &Lep0_eta, "Lep0_eta/F");
    tree->Branch("Lep0_pt", &Lep0_pt, "Lep0_pt/F");
    tree->Branch("Iqrk1_E", &Iqrk1_E, "Iqrk1_E/F");
    tree->Branch("Iqrk1_pz", &Iqrk1_pz, "Iqrk1_pz/F");
    tree->Branch("Iqrk1_py", &Iqrk1_py, "Iqrk1_py/F");
    tree->Branch("Iqrk1_px", &Iqrk1_px, "Iqrk1_px/F");
    tree->Branch("Iqrk0_E", &Iqrk0_E, "Iqrk0_E/F");
    tree->Branch("Iqrk0_pz", &Iqrk0_pz, "Iqrk0_pz/F");
    tree->Branch("Iqrk0_py", &Iqrk0_py, "Iqrk0_py/F");
    tree->Branch("Iqrk0_px", &Iqrk0_px, "Iqrk0_px/F");
    tree->Branch("Wqrk1_E", &Wqrk1_E, "Wqrk1_E/F");
    tree->Branch("Wqrk1_pz", &Wqrk1_pz, "Wqrk1_pz/F");
    tree->Branch("Wqrk1_py", &Wqrk1_py, "Wqrk1_py/F");
    tree->Branch("Wqrk1_px", &Wqrk1_px, "Wqrk1_px/F");
    tree->Branch("Wqrk0_E", &Wqrk0_E, "Wqrk0_E/F");
    tree->Branch("Wqrk0_pz", &Wqrk0_pz, "Wqrk0_pz/F");
    tree->Branch("Wqrk0_py", &Wqrk0_py, "Wqrk0_py/F");
    tree->Branch("Wqrk0_px", &Wqrk0_px, "Wqrk0_px/F");
    tree->Branch("Lep1_E", &Lep1_E, "Lep1_E/F");
    tree->Branch("Lep1_pz", &Lep1_pz, "Lep1_pz/F");
    tree->Branch("Lep1_py", &Lep1_py, "Lep1_py/F");
    tree->Branch("Lep1_px", &Lep1_px, "Lep1_px/F");
    tree->Branch("Lep0_E", &Lep0_E, "Lep0_E/F");
    tree->Branch("Lep0_pz", &Lep0_pz, "Lep0_pz/F");
    tree->Branch("Lep0_py", &Lep0_py, "Lep0_py/F");
    tree->Branch("Lep0_px", &Lep0_px, "Lep0_px/F");
    tree->Branch("mWW", &mWW, "mWW/F");
    tree->Branch("mWLep", &mWLep, "mWLep/F");
    tree->Branch("mWHad", &mWHad, "mWHad/F");
    tree->Branch("costheta1", &costheta1, "costheta1/F");
    tree->Branch("costheta2", &costheta2, "costheta2/F");
    tree->Branch("costhetaV1", &costhetaV1, "costhetaV1/F");
    tree->Branch("costhetaV2", &costhetaV2, "costhetaV2/F");
    tree->Branch("costhetaV3", &costhetaV3, "costhetaV3/F");
    tree->Branch("costhetaV4", &costhetaV4, "costhetaV4/F");
    tree->Branch("costhetastar", &costhetastar, "costhetastar/F");
    tree->Branch("phi", &phi, "phi/F");
    tree->Branch("phi1", &phi1, "phi1/F");
    tree->Branch("dEtajj", &dEtajj, "dEtajj/F");
    tree->Branch("dPhijj", &dPhijj, "dPhijj/F");
    tree->Branch("mjj", &mjj, "mjj/F");

    tree->Branch("isSignal", &isSignal, "isSignal/I");
    tree->Branch("isMuMinus", &isMuMinus, "isMuMinus/I");

    // PG loop over bkg
    // PG -------------

    int BKGnumber = 0;
    int BKGnumberWithObj = 0;
    int VBFBKGnumber = 0;
    int count = 0;
    int NSignal = 0;
    int NTotal = 0;
    double SM_Weight = 0.0;

    std::ifstream ifsbkg(argv[1]);
    // Create the Reader object
    LHEF::Reader bkgReader(ifsbkg);

    std::vector<int> initialQuarks_;
    // AddBranch(&initialQuarks_,"initialQuarks");
    tree->Branch("initialQuarks", &initialQuarks_);

    // PG loop over BKG
    while (bkgReader.readEvent())
    {
        ++BKGnumber;
        if (BKGnumber % 1000 == 0)
            std::cout << "BKG event " << BKGnumber << "\n";
        // if (BKGnumber > 1) break;
        /*
            std::cout<< "Number of particles = "<<bkgReader.hepeup.NUP<<std::endl;
            std::cout<< "Event weight = "<<bkgReader.hepeup.XWGTUP<<std::endl;
            std::cout<<"rwgt size = "<<bkgReader.hepeup.namedweights.size()<<std::endl;
            std::cout<<"rwgt size = "<<bkgReader.hepeup.weights.size()<<std::endl;
        */
        for (int iPart = 0; iPart < bkgReader.hepeup.namedweights.size(); ++iPart)
        {
            if (bkgReader.hepeup.namedweights[iPart].name == "fs0_0p0")
            {
                // std::cout<<iPart+1<<"\tWeight info : "<<std::scientific<<bkgReader.hepeup.namedweights[iPart].weights[0]<<"\t"<< bkgReader.hepeup.namedweights[iPart].name <<std::endl;
                // std::cout<<iPart+1<<"\tWeight info : "<<std::setprecision(10)<<bkgReader.hepeup.namedweights[iPart].weights[0]<<"\t"<< bkgReader.hepeup.namedweights[iPart].name <<std::endl;
                SM_Weight = bkgReader.hepeup.namedweights[iPart].weights[0];
            }
        }

        std::vector<int> leptons;
        std::vector<int> finalQuarks;
        std::vector<int> intermediates;
        std::vector<int> tops;
        TLorentzVector Is_Iqrk1, Is_Iqrk0;
        // PG loop over particles in the event
        int incomingPart = 0;
        for (int iPart = 0; iPart < bkgReader.hepeup.IDUP.size(); ++iPart)
        {

            int mother1 = bkgReader.hepeup.MOTHUP.at(iPart).first;

            // PG incoming particle
            if (bkgReader.hepeup.ISTUP.at(iPart) == -1)
            {
                initialQuarks_.push_back(bkgReader.hepeup.IDUP.at(iPart));
                incomingPart++;
                if (incomingPart == 1)
                {
                    Is_Iqrk0.SetPxPyPzE(
                        bkgReader.hepeup.PUP.at(incomingPart).at(0), // PG px
                        bkgReader.hepeup.PUP.at(incomingPart).at(1), // PG py
                        bkgReader.hepeup.PUP.at(incomingPart).at(2), // PG pz
                        bkgReader.hepeup.PUP.at(incomingPart).at(3)  // PG E
                    );
                }
                if (incomingPart == 2)
                {
                    Is_Iqrk1.SetPxPyPzE(
                        bkgReader.hepeup.PUP.at(incomingPart).at(0), // PG px
                        bkgReader.hepeup.PUP.at(incomingPart).at(1), // PG py
                        bkgReader.hepeup.PUP.at(incomingPart).at(2), // PG pz
                        bkgReader.hepeup.PUP.at(incomingPart).at(3)  // PG E
                    );
                }
                // std::cout<<"incoming particle = "<<incomingPart<<std::endl;
                count++;
            }

            // PG outgoing particles
            if (bkgReader.hepeup.ISTUP.at(iPart) == 1)
            {
                // PG leptons
                if (abs(bkgReader.hepeup.IDUP.at(iPart)) == 11 || // PG electron
                    abs(bkgReader.hepeup.IDUP.at(iPart)) == 13 || // PG muon
                    abs(bkgReader.hepeup.IDUP.at(iPart)) == 15 || // PG tau
                    abs(bkgReader.hepeup.IDUP.at(iPart)) == 12 || // PG neutrino
                    abs(bkgReader.hepeup.IDUP.at(iPart)) == 14 || // PG neutrino
                    abs(bkgReader.hepeup.IDUP.at(iPart)) == 16)   // PG neutrino
                {
                    leptons.push_back(iPart);
                } // PG leptons
                else
                {
                    finalQuarks.push_back(iPart);
                }
            }

            // PG intermediates
            if (bkgReader.hepeup.ISTUP.at(iPart) == 2)
            {
                intermediates.push_back(iPart);
            }

            // PG tops
            if (abs(bkgReader.hepeup.IDUP.at(iPart)) == 6)
            {
                tops.push_back(iPart);
            }
        } // PG loop over particles in the event

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

        if (leptons.size() == 2)
        {
            if (bkgReader.hepeup.IDUP.at(leptons.at(0)) > 0)
            {
                i_olep_part = leptons.at(0);
                i_olep_anti = leptons.at(1);
                if (bkgReader.hepeup.IDUP.at(leptons.at(0)) == 11 || // PG electron
                    bkgReader.hepeup.IDUP.at(leptons.at(0)) == 13 || // PG muon
                    bkgReader.hepeup.IDUP.at(leptons.at(0)) == 15)
                    isMuMinus = 1;
            }
            else
            {
                i_olep_part = leptons.at(1);
                i_olep_anti = leptons.at(0);
                if (bkgReader.hepeup.IDUP.at(leptons.at(1)) == 11 || // PG electron
                    bkgReader.hepeup.IDUP.at(leptons.at(1)) == 13 || // PG muon
                    bkgReader.hepeup.IDUP.at(leptons.at(1)) == 15)
                    isMuMinus = 1;
            }
        }
        else
        {
            std::cout << "Problem!" << std::endl;
        }

        // --------------- If signal, find the quarks from the W  -------------------
        if (finalQuarks.size() == 4)
        {
            for (unsigned int a = 0; a < finalQuarks.size(); ++a)
            {
                int tmpMoth = bkgReader.hepeup.MOTHUP.at(finalQuarks.at(a)).first - 1;

                if (abs(bkgReader.hepeup.IDUP.at(tmpMoth)) == 24 && bkgReader.hepeup.IDUP.at(finalQuarks.at(a)) > 0)
                {
                    signalWCtr++;
                }
                if (abs(bkgReader.hepeup.IDUP.at(tmpMoth)) == 24 && bkgReader.hepeup.IDUP.at(finalQuarks.at(a)) < 0)
                {
                    signalWCtr++;
                }
                if (abs(bkgReader.hepeup.IDUP.at(tmpMoth)) != 24 && tmpfill1)
                {
                    signalWCtr++;
                }
                if (abs(bkgReader.hepeup.IDUP.at(tmpMoth)) != 24 && !tmpfill1)
                {
                    signalWCtr++;
                    tmpfill1++;
                }
            }
        }
        else
        {
            std::cout << "Problem!" << std::endl;
        }

        if (signalWCtr == 4 && tops.size() == 0)
        {
            signalFlag = 1;
            NSignal++;
        }

        // --------------- Assign quarks based on W invariant mass -------------------
        float distanceToWMass = 9999.;
        for (unsigned int a = 0; a < finalQuarks.size(); ++a)
        {
            for (unsigned int b = a + 1; b < finalQuarks.size(); ++b)
            {
                TLorentzVector qrk0(
                    bkgReader.hepeup.PUP.at(finalQuarks.at(a)).at(0), // PG px
                    bkgReader.hepeup.PUP.at(finalQuarks.at(a)).at(1), // PG py
                    bkgReader.hepeup.PUP.at(finalQuarks.at(a)).at(2), // PG pz
                    bkgReader.hepeup.PUP.at(finalQuarks.at(a)).at(3)  // PG E
                );
                TLorentzVector qrk1(
                    bkgReader.hepeup.PUP.at(finalQuarks.at(b)).at(0), // PG px
                    bkgReader.hepeup.PUP.at(finalQuarks.at(b)).at(1), // PG py
                    bkgReader.hepeup.PUP.at(finalQuarks.at(b)).at(2), // PG pz
                    bkgReader.hepeup.PUP.at(finalQuarks.at(b)).at(3)  // PG E
                );

                float tmpDistance = std::abs((qrk0 + qrk1).M() - 80.2);
                if (tmpDistance < distanceToWMass)
                {
                    i_wqrk_1 = finalQuarks.at(a);
                    i_wqrk_2 = finalQuarks.at(b);
                    distanceToWMass = tmpDistance;
                }
            }
        }

        // quarks based on particle-antiparticle
        if (bkgReader.hepeup.IDUP.at(i_wqrk_1) < 0)
        {
            int tmpint = i_wqrk_1;
            i_wqrk_1 = i_wqrk_2;
            i_wqrk_2 = tmpint;
        }

        // assign the other quarks
        std::vector<int> finalQuarksNotW;
        for (unsigned int a = 0; a < finalQuarks.size(); ++a)
        {
            if (finalQuarks.at(a) != i_wqrk_1 && finalQuarks.at(a) != i_wqrk_2)
            {
                finalQuarksNotW.push_back(finalQuarks.at(a));
            }
        }
        if (finalQuarksNotW.size() == 2)
        {
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

        TLorentzVector fs_lep0(
            bkgReader.hepeup.PUP.at(i_olep_part).at(0), // PG px
            bkgReader.hepeup.PUP.at(i_olep_part).at(1), // PG py
            bkgReader.hepeup.PUP.at(i_olep_part).at(2), // PG pz
            bkgReader.hepeup.PUP.at(i_olep_part).at(3)  // PG E
        );
        Lep0_px = bkgReader.hepeup.PUP.at(i_olep_part).at(0);
        Lep0_py = bkgReader.hepeup.PUP.at(i_olep_part).at(1);
        Lep0_pz = bkgReader.hepeup.PUP.at(i_olep_part).at(2);
        Lep0_E = bkgReader.hepeup.PUP.at(i_olep_part).at(3);
        Lep0_pt = fs_lep0.Pt() * SM_Weight;
        Lep0_eta = fs_lep0.Eta();
        Lep0_phi = fs_lep0.Phi();
        Lep0_theta = fs_lep0.Phi();
        TLorentzVector fs_lep1(
            bkgReader.hepeup.PUP.at(i_olep_anti).at(0), // PG px
            bkgReader.hepeup.PUP.at(i_olep_anti).at(1), // PG py
            bkgReader.hepeup.PUP.at(i_olep_anti).at(2), // PG pz
            bkgReader.hepeup.PUP.at(i_olep_anti).at(3)  // PG E
        );
        Lep1_px = bkgReader.hepeup.PUP.at(i_olep_anti).at(0);
        Lep1_py = bkgReader.hepeup.PUP.at(i_olep_anti).at(1);
        Lep1_pz = bkgReader.hepeup.PUP.at(i_olep_anti).at(2);
        Lep1_E = bkgReader.hepeup.PUP.at(i_olep_anti).at(3);
        Lep1_pt = fs_lep1.Pt();
        Lep1_eta = fs_lep1.Eta();
        Lep1_phi = fs_lep1.Phi();
        Lep1_theta = fs_lep1.Phi();

        TLorentzVector fs_Wqrk0(
            bkgReader.hepeup.PUP.at(i_wqrk_1).at(0), // PG px
            bkgReader.hepeup.PUP.at(i_wqrk_1).at(1), // PG py
            bkgReader.hepeup.PUP.at(i_wqrk_1).at(2), // PG pz
            bkgReader.hepeup.PUP.at(i_wqrk_1).at(3)  // PG E
        );
        Wqrk0_px = bkgReader.hepeup.PUP.at(i_wqrk_1).at(0);
        Wqrk0_py = bkgReader.hepeup.PUP.at(i_wqrk_1).at(1);
        Wqrk0_pz = bkgReader.hepeup.PUP.at(i_wqrk_1).at(2);
        Wqrk0_E = bkgReader.hepeup.PUP.at(i_wqrk_1).at(3);
        Wqrk0_pt = fs_Wqrk0.Pt();
        Wqrk0_eta = fs_Wqrk0.Eta();
        Wqrk0_phi = fs_Wqrk0.Phi();
        Wqrk0_theta = fs_Wqrk0.Phi();

        TLorentzVector fs_Wqrk1(
            bkgReader.hepeup.PUP.at(i_wqrk_2).at(0), // PG px
            bkgReader.hepeup.PUP.at(i_wqrk_2).at(1), // PG py
            bkgReader.hepeup.PUP.at(i_wqrk_2).at(2), // PG pz
            bkgReader.hepeup.PUP.at(i_wqrk_2).at(3)  // PG E
        );
        Wqrk1_px = bkgReader.hepeup.PUP.at(i_wqrk_2).at(0);
        Wqrk1_py = bkgReader.hepeup.PUP.at(i_wqrk_2).at(1);
        Wqrk1_pz = bkgReader.hepeup.PUP.at(i_wqrk_2).at(2);
        Wqrk1_E = bkgReader.hepeup.PUP.at(i_wqrk_2).at(3);
        Wqrk1_pt = fs_Wqrk1.Pt();
        Wqrk1_eta = fs_Wqrk1.Eta();
        Wqrk1_phi = fs_Wqrk1.Phi();
        Wqrk1_theta = fs_Wqrk1.Phi();

        TLorentzVector fs_Iqrk0(
            bkgReader.hepeup.PUP.at(i_iqrk_1).at(0), // PG px
            bkgReader.hepeup.PUP.at(i_iqrk_1).at(1), // PG py
            bkgReader.hepeup.PUP.at(i_iqrk_1).at(2), // PG pz
            bkgReader.hepeup.PUP.at(i_iqrk_1).at(3)  // PG E
        );
        Iqrk0_px = bkgReader.hepeup.PUP.at(i_iqrk_1).at(0);
        Iqrk0_py = bkgReader.hepeup.PUP.at(i_iqrk_1).at(1);
        Iqrk0_pz = bkgReader.hepeup.PUP.at(i_iqrk_1).at(2);
        Iqrk0_E = bkgReader.hepeup.PUP.at(i_iqrk_1).at(3);
        Iqrk0_pt = fs_Iqrk0.Pt();
        Iqrk0_eta = fs_Iqrk0.Eta();
        Iqrk0_phi = fs_Iqrk0.Phi();
        Iqrk0_theta = fs_Iqrk0.Phi();

        TLorentzVector fs_Iqrk1(
            bkgReader.hepeup.PUP.at(i_iqrk_2).at(0), // PG px
            bkgReader.hepeup.PUP.at(i_iqrk_2).at(1), // PG py
            bkgReader.hepeup.PUP.at(i_iqrk_2).at(2), // PG pz
            bkgReader.hepeup.PUP.at(i_iqrk_2).at(3)  // PG E
        );
        Iqrk1_px = bkgReader.hepeup.PUP.at(i_iqrk_2).at(0);
        Iqrk1_py = bkgReader.hepeup.PUP.at(i_iqrk_2).at(1);
        Iqrk1_pz = bkgReader.hepeup.PUP.at(i_iqrk_2).at(2);
        Iqrk1_E = bkgReader.hepeup.PUP.at(i_iqrk_2).at(3);
        Iqrk1_pt = fs_Iqrk1.Pt();
        Iqrk1_eta = fs_Iqrk1.Eta();
        Iqrk1_phi = fs_Iqrk1.Phi();
        Iqrk1_theta = fs_Iqrk1.Phi();

        TLorentzVector p4_WHad = fs_Wqrk0 + fs_Wqrk1;
        TLorentzVector p4_WLep = fs_lep0 + fs_lep1;
        TLorentzVector p4_WW = p4_WHad + p4_WLep;

        double a_costheta1, a_costheta2, a_costhetastar, a_Phi, a_Phi1;
        computeAngles(p4_WW, p4_WLep, fs_lep0, fs_lep1, p4_WHad, fs_Wqrk0, fs_Wqrk1,
                      a_costheta1, a_costheta2, a_Phi, a_costhetastar, a_Phi1);

        mWW = (float)p4_WW.M();
        mWLep = (float)p4_WLep.M();
        mWHad = (float)p4_WHad.M();
        costheta1 = (float)a_costheta1;
        costheta2 = (float)a_costheta2;
        costhetaV1 = (float)((fs_Iqrk0 - Is_Iqrk0).Theta() - fs_Wqrk0.Theta());
        costhetaV2 = (float)((fs_Iqrk0 - Is_Iqrk1).Theta() - fs_Wqrk0.Theta());
        costhetaV3 = (float)((fs_Iqrk0 - Is_Iqrk0).Theta() - fs_Wqrk1.Theta());
        costhetaV4 = (float)((fs_Iqrk0 - Is_Iqrk1).Theta() - fs_Wqrk1.Theta());
        phi = (float)a_Phi;
        costhetastar = (float)a_costhetastar;
        phi1 = (float)a_Phi1;

        dEtajj = (float)fabs(fs_Iqrk0.Eta() - fs_Iqrk1.Eta());
        dPhijj = (float)deltaPhi(fs_Iqrk0.Phi(), fs_Iqrk1.Phi());
        mjj = (float)(fs_Iqrk0 + fs_Iqrk1).M();

        isSignal = signalFlag;

        tree->Fill();
        initialQuarks_.clear();

        //	if (BKGnumber > 24000)  break;
    }

    std::cout << "BKGnumber = " << BKGnumber << ", and NSignal = " << NSignal << std::endl;

    file.cd();
    tree->Write();
    file.Close();

    std::cout << "Count = " << count << std::endl;
    std::cout << "initialQuarks_ = " << initialQuarks_.size() << std::endl;

    // Now we are done.
    return 0;
}

//////////////////////////////////
//// P A P E R   4 - V E C T O R   D E F I N I T I O N   O F   P H I   A N D   P H I 1
//////////////////////////////////
void computeAngles(TLorentzVector thep4H, TLorentzVector thep4Z1, TLorentzVector thep4M11, TLorentzVector thep4M12, TLorentzVector thep4Z2, TLorentzVector thep4M21, TLorentzVector thep4M22, double &costheta1, double &costheta2, double &Phi, double &costhetastar, double &Phi1)
{

    ///////////////////////////////////////////////
    // check for z1/z2 convention, redefine all 4 vectors with convention
    ///////////////////////////////////////////////
    TLorentzVector p4H, p4Z1, p4M11, p4M12, p4Z2, p4M21, p4M22;
    p4H = thep4H;

    p4Z1 = thep4Z1;
    p4M11 = thep4M11;
    p4M12 = thep4M12;
    p4Z2 = thep4Z2;
    p4M21 = thep4M21;
    p4M22 = thep4M22;
    //// costhetastar
    TVector3 boostX = -(thep4H.BoostVector());
    TLorentzVector thep4Z1inXFrame(p4Z1);
    TLorentzVector thep4Z2inXFrame(p4Z2);
    thep4Z1inXFrame.Boost(boostX);
    thep4Z2inXFrame.Boost(boostX);
    TVector3 theZ1X_p3 = TVector3(thep4Z1inXFrame.X(), thep4Z1inXFrame.Y(), thep4Z1inXFrame.Z());
    TVector3 theZ2X_p3 = TVector3(thep4Z2inXFrame.X(), thep4Z2inXFrame.Y(), thep4Z2inXFrame.Z());
    costhetastar = theZ1X_p3.CosTheta();

    //// --------------------------- costheta1
    TVector3 boostV1 = -(thep4Z1.BoostVector());
    TLorentzVector p4M11_BV1(p4M11);
    TLorentzVector p4M12_BV1(p4M12);
    TLorentzVector p4M21_BV1(p4M21);
    TLorentzVector p4M22_BV1(p4M22);
    p4M11_BV1.Boost(boostV1);
    p4M12_BV1.Boost(boostV1);
    p4M21_BV1.Boost(boostV1);
    p4M22_BV1.Boost(boostV1);

    TLorentzVector p4V2_BV1 = p4M21_BV1 + p4M22_BV1;
    //// costheta1
    costheta1 = -p4V2_BV1.Vect().Dot(p4M11_BV1.Vect()) / p4V2_BV1.Vect().Mag() / p4M11_BV1.Vect().Mag();

    //// --------------------------- costheta2
    TVector3 boostV2 = -(thep4Z2.BoostVector());
    TLorentzVector p4M11_BV2(p4M11);
    TLorentzVector p4M12_BV2(p4M12);
    TLorentzVector p4M21_BV2(p4M21);
    TLorentzVector p4M22_BV2(p4M22);
    p4M11_BV2.Boost(boostV2);
    p4M12_BV2.Boost(boostV2);
    p4M21_BV2.Boost(boostV2);
    p4M22_BV2.Boost(boostV2);

    TLorentzVector p4V1_BV2 = p4M11_BV2 + p4M12_BV2;
    //// costheta2
    costheta2 = -p4V1_BV2.Vect().Dot(p4M21_BV2.Vect()) / p4V1_BV2.Vect().Mag() / p4M21_BV2.Vect().Mag();

    //// --------------------------- Phi and Phi1
    //    TVector3 boostX = -(thep4H.BoostVector());
    TLorentzVector p4M11_BX(p4M11);
    TLorentzVector p4M12_BX(p4M12);
    TLorentzVector p4M21_BX(p4M21);
    TLorentzVector p4M22_BX(p4M22);

    p4M11_BX.Boost(boostX);
    p4M12_BX.Boost(boostX);
    p4M21_BX.Boost(boostX);
    p4M22_BX.Boost(boostX);

    TVector3 tmp1 = p4M11_BX.Vect().Cross(p4M12_BX.Vect());
    TVector3 tmp2 = p4M21_BX.Vect().Cross(p4M22_BX.Vect());

    TVector3 normal1_BX(tmp1.X() / tmp1.Mag(), tmp1.Y() / tmp1.Mag(), tmp1.Z() / tmp1.Mag());
    TVector3 normal2_BX(tmp2.X() / tmp2.Mag(), tmp2.Y() / tmp2.Mag(), tmp2.Z() / tmp2.Mag());

    //// Phi
    TLorentzVector p4Z1_BX = p4M11_BX + p4M12_BX;
    double tmpSgnPhi = p4Z1_BX.Vect().Dot(normal1_BX.Cross(normal2_BX));
    double sgnPhi = tmpSgnPhi / fabs(tmpSgnPhi);
    Phi = sgnPhi * acos(-1. * normal1_BX.Dot(normal2_BX));

    //////////////

    TVector3 beamAxis(0, 0, 1);
    TVector3 tmp3 = (p4M11_BX + p4M12_BX).Vect();

    TVector3 p3V1_BX(tmp3.X() / tmp3.Mag(), tmp3.Y() / tmp3.Mag(), tmp3.Z() / tmp3.Mag());
    TVector3 tmp4 = beamAxis.Cross(p3V1_BX);
    TVector3 normalSC_BX(tmp4.X() / tmp4.Mag(), tmp4.Y() / tmp4.Mag(), tmp4.Z() / tmp4.Mag());

    //// Phi1
    double tmpSgnPhi1 = p4Z1_BX.Vect().Dot(normal1_BX.Cross(normalSC_BX));
    double sgnPhi1 = tmpSgnPhi1 / fabs(tmpSgnPhi1);
    Phi1 = sgnPhi1 * acos(normal1_BX.Dot(normalSC_BX));

    //    std::cout << "extractAngles: " << std::endl;
    //    std::cout << "costhetastar = " << costhetastar << ", costheta1 = " << costheta1 << ", costheta2 = " << costheta2 << std::endl;
    //    std::cout << "Phi = " << Phi << ", Phi1 = " << Phi1 << std::endl;
}
