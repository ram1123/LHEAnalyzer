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
#include <vector>

const int STATUS_INCOMING = -1;
const int STATUS_OUTGOING = 1;
const int STATUS_INTERMEDIATE = 2;
const int PDG_TOP = 6;
const int PDG_W_BOSON = 24;
const int PDG_Z_BOSON = 23;
const int PDG_B_QUARK = 5;
const int PDG_ANTI_B_QUARK = -5;

bool Verbose = false;

// Assuming these are some of the variables you want to store in the tree
int nGluons, nQuarks, nIncomingParticles, nOutgoingParticles, nIntermediateParticles, nLeptons;
double SM_Weight;
bool isSignal;

std::vector<int> *PDG_IncomingParticles = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles = new std::vector<int>;
std::vector<int> *PDG_IntermediateParticles = new std::vector<int>;

// Function to handle the particle classification and data storage
void handleParticle(int iPart, LHEF::Reader &bkgReader, std::vector<int> &leptons, std::vector<int> &finalGluons, std::vector<int> &finalQuarks)
{
    // Handle incoming particles
    if (bkgReader.hepeup.ISTUP.at(iPart) == STATUS_INCOMING)
    {
        PDG_IncomingParticles->push_back(bkgReader.hepeup.IDUP.at(iPart));
    }

    // Handle outgoing particles
    if (bkgReader.hepeup.ISTUP.at(iPart) == STATUS_OUTGOING)
    {
        PDG_OutgoingParticles->push_back(bkgReader.hepeup.IDUP.at(iPart));

        // Classify leptons, gluons, and quarks
        int abs_id = abs(bkgReader.hepeup.IDUP.at(iPart));
        if (abs_id == 11 || abs_id == 13 || abs_id == 15 || abs_id == 12 || abs_id == 14 || abs_id == 16)
        {
            leptons.push_back(iPart);
        }
        else if (abs_id == 21)
        {
            finalGluons.push_back(iPart);
        }
        else if (abs_id > 0 && abs_id <= 6)
        {
            finalQuarks.push_back(iPart);
        }
    }

    // Handle intermediate particles
    if (bkgReader.hepeup.ISTUP.at(iPart) == STATUS_INTERMEDIATE)
    {
        PDG_IntermediateParticles->push_back(bkgReader.hepeup.IDUP.at(iPart));
    }
}

int main(int argc, char **argv)
{
    TFile file(argv[2], "RECREATE");
    file.SetCompressionLevel(2);
    TTree *tree = new TTree("tree", "Particles Info");

    // Declare branches for the TTree
    tree->Branch("nIncomingParticles", &nIncomingParticles, "nIncomingParticles/I");
    tree->Branch("nOutgoingParticles", &nOutgoingParticles, "nOutgoingParticles/I");
    tree->Branch("nIntermediateParticles", &nIntermediateParticles, "nIntermediateParticles/I");
    tree->Branch("nQuarks", &nQuarks, "nQuarks/I");
    tree->Branch("nGluons", &nGluons, "nGluons/I");
    tree->Branch("SM_Weight", &SM_Weight, "SM_Weight/D");
    tree->Branch("isSignal", &isSignal, "isSignal/O");
    tree->Branch("PDG_IncomingParticles", &PDG_IncomingParticles);
    tree->Branch("PDG_OutgoingParticles", &PDG_OutgoingParticles);
    tree->Branch("PDG_IntermediateParticles", &PDG_IntermediateParticles);
    tree->Branch("nLeptons", &nLeptons, "nLeptons/I");

    std::ifstream ifsbkg(argv[1]);
    LHEF::Reader bkgReader(ifsbkg);

    std::vector<int> leptons;
    std::vector<int> finalQuarks;
    std::vector<int> finalGluons;

    // Loop over events
    int nEvents = 0;
    while (bkgReader.readEvent())
    {
        ++nEvents;

        PDG_IncomingParticles->clear();
        PDG_OutgoingParticles->clear();
        PDG_IntermediateParticles->clear();
        leptons.clear();

        if (Verbose)
            std::cout
                << "====> BKG event " << nEvents << "\\n";

        // Loop over particles in the event
        for (int iPart = 0; iPart < bkgReader.hepeup.IDUP.size(); ++iPart)
        {
            handleParticle(iPart, bkgReader, leptons, finalGluons, finalQuarks);
        }

        // Further processing and set tree variables...
        nQuarks = finalQuarks.size(); // Example assignment
        nGluons = finalGluons.size();
        nIncomingParticles = PDG_IncomingParticles->size();
        nOutgoingParticles = PDG_OutgoingParticles->size();
        nIntermediateParticles = PDG_IntermediateParticles->size();
        nLeptons = leptons.size();

        // Fill the tree with the current event's data
        tree->Fill();
    }

    std::cout << "Total Events = " << nEvents << std::endl;

    file.cd();
    tree->Write();
    file.Close();

    return 0;
}
