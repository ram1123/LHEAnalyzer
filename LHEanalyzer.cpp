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
#include "TFile.h"
#include "TLorentzVector.h"
#include <cmath>
#include "TTree.h"
#include <vector>
#include <stdexcept> // for std::runtime_error

const int STATUS_INCOMING = -1;
const int STATUS_OUTGOING = 1;
const int STATUS_INTERMEDIATE = 2;
const int PDG_TOP = 6;
const int PDG_W_BOSON = 24;
const int PDG_Z_BOSON = 23;
const int PDG_B_QUARK = 5;
const int PDG_ANTI_B_QUARK = -5;
int COUNTER = 0;

bool Verbose = false;
bool DEBUG = false;
const int EVENTSTORUN = -1;

int counter_forwardQuarks = 0;

// Kinematic variables
struct Kinematics
{
    double pt;
    double eta;
    double phi;
    double energy;
    double mass;
    int pdgID;
};

Kinematics leadingLeptonFromZ, subleadingLeptonFromZ, leptonFromW, neutrinoFromW, leadingQuarkFromW, subleadingQuarkFromW, wBosonKinematics, bQuarkFromTopKinematics, forwardQuarkKinematics;

std::vector<int> *PDG_IncomingParticles = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles_LEPW = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles_NeutrinoW = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles_LEPZ = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles_QuarkW = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles_QuarkTop = new std::vector<int>;
std::vector<int> *PDG_OutgoingParticles_OtherQuark = new std::vector<int>;
std::vector<int> *PDG_IntermediateParticles = new std::vector<int>;
std::vector<int> *PDG_ForwardQuarks = new std::vector<int>;

    // Convert TLorentzVector to Kinematics
    Kinematics
    convertToKinematics(TLorentzVector vec, int pdgID)
{
    Kinematics k;
    k.pt = vec.Pt();
    k.eta = vec.Eta();
    k.phi = vec.Phi();
    k.energy = vec.E();
    k.mass = vec.M();
    k.pdgID = pdgID;
    return k;
}

void handleParticle(int iPart, LHEF::Reader &bkgReader)
{
    counter_forwardQuarks = 0;
    int particlePDG = bkgReader.hepeup.IDUP.at(iPart);
    int status = bkgReader.hepeup.ISTUP.at(iPart);

    int mother1 = bkgReader.hepeup.MOTHUP.at(iPart).first - 1;  // Adjusting to 0-indexed
    int mother2 = bkgReader.hepeup.MOTHUP.at(iPart).second - 1; // Adjusting to 0-indexed

    if (Verbose && status > 0)
        std::cout << "particle PDGID " << particlePDG << "\t status: " << status << "\t mother: " << bkgReader.hepeup.IDUP.at(mother1) << ", " << bkgReader.hepeup.IDUP.at(mother2) << std::endl;

    double px = bkgReader.hepeup.PUP.at(iPart)[0];
    double py = bkgReader.hepeup.PUP.at(iPart)[1];
    double pz = bkgReader.hepeup.PUP.at(iPart)[2];
    double energy = bkgReader.hepeup.PUP.at(iPart)[3];

    TLorentzVector particleMomentum(px, py, pz, energy);

    // Handle incoming particles
    if (status == STATUS_INCOMING)
    {
        PDG_IncomingParticles->push_back(particlePDG);
        if (Verbose)
            std::cout << "Incoming particle: " << particlePDG << std::endl;
    }

    // Handle outgoing particles
    if (status == STATUS_OUTGOING)
    {
        PDG_OutgoingParticles->push_back(particlePDG);

        // Storing kinematics of leptons from Z boson
        if (abs(particlePDG) >= 11 && abs(particlePDG) <= 16)
        {
            if (Verbose)
                std::cout << "outgoing LEP PDGID: " << particlePDG << std::endl;
            if (bkgReader.hepeup.IDUP.at(mother1) == PDG_Z_BOSON || bkgReader.hepeup.IDUP.at(mother2) == PDG_Z_BOSON)
            {
                if (Verbose)
                    std::cout << "outgoing LEPZ PDGID: " << particlePDG << std::endl;
                PDG_OutgoingParticles_LEPZ->push_back(particlePDG);
                if (leadingLeptonFromZ.pt < particleMomentum.Pt())
                {
                    subleadingLeptonFromZ = leadingLeptonFromZ;
                    leadingLeptonFromZ = convertToKinematics(particleMomentum, particlePDG);
                }
                else
                {
                    subleadingLeptonFromZ = convertToKinematics(particleMomentum, particlePDG);
                }
            }

            // Storing kinematics of lepton and neutrino from W boson
            // if (abs(particlePDG) >= 11 && abs(particlePDG) <= 16)
            // if (bkgReader.hepeup.IDUP.at(mother1) == PDG_Z_BOSON || bkgReader.hepeup.IDUP.at(mother2) == PDG_Z_BOSON)
            if (Verbose)
                std::cout << "bkgReader.hepeup.IDUP.at(mother1): " << bkgReader.hepeup.IDUP.at(mother1) << "\t" << PDG_W_BOSON << std::endl;
            if (abs(bkgReader.hepeup.IDUP.at(mother1)) == PDG_W_BOSON || abs(bkgReader.hepeup.IDUP.at(mother2))== PDG_W_BOSON)
            {
                if (Verbose)
                    std::cout << "outgoing LEPW PDGID: " << particlePDG << std::endl;
                if (abs(particlePDG) == 12 || abs(particlePDG) == 14 || abs(particlePDG) == 16)
                {
                    neutrinoFromW = convertToKinematics(particleMomentum, particlePDG);
                    PDG_OutgoingParticles_NeutrinoW->push_back(particlePDG);
                }
                else
                {
                    leptonFromW = convertToKinematics(particleMomentum, particlePDG);
                    PDG_OutgoingParticles_LEPW->push_back(particlePDG);
                }
                }
        }

        // Storing kinematics of quarks from W boson that decays from top
        if (abs(particlePDG) <= 6)
        {
            if (bkgReader.hepeup.IDUP.at(mother1) == PDG_W_BOSON || bkgReader.hepeup.IDUP.at(mother2) == PDG_W_BOSON)
            {
                PDG_OutgoingParticles_QuarkW->push_back(particlePDG);
                if (leadingQuarkFromW.pt < particleMomentum.Pt())
                {
                    subleadingQuarkFromW = leadingQuarkFromW;
                    leadingQuarkFromW = convertToKinematics(particleMomentum, particlePDG);
                }
                else
                {
                    subleadingQuarkFromW = convertToKinematics(particleMomentum, particlePDG);
                }
            }

            // Storing kinematics of the W-boson and the b-quark from top
            if (bkgReader.hepeup.IDUP.at(mother1) == PDG_TOP || bkgReader.hepeup.IDUP.at(mother2) == PDG_TOP)
            {
                if (abs(particlePDG) == PDG_W_BOSON)
                {
                    wBosonKinematics = convertToKinematics(particleMomentum, particlePDG);
                }
                else if (abs(particlePDG) == PDG_B_QUARK || abs(particlePDG) == PDG_ANTI_B_QUARK)
                {
                    bQuarkFromTopKinematics = convertToKinematics(particleMomentum, particlePDG);
                    PDG_OutgoingParticles_QuarkTop->push_back(particlePDG);
                }
            }
        }

        // Storing kinematics of other forward quark
        if (abs(particlePDG) <= 6 && particleMomentum.Pz() > 0)
        {

            if (abs(bkgReader.hepeup.IDUP.at(mother1)) != PDG_W_BOSON && abs(bkgReader.hepeup.IDUP.at(mother2)) != PDG_W_BOSON &&
                abs(bkgReader.hepeup.IDUP.at(mother1)) != PDG_Z_BOSON && abs(bkgReader.hepeup.IDUP.at(mother2)) != PDG_Z_BOSON &&
                abs(bkgReader.hepeup.IDUP.at(mother1)) != PDG_TOP && abs(bkgReader.hepeup.IDUP.at(mother2)) != PDG_TOP)
            {
                PDG_OutgoingParticles_OtherQuark->push_back(particlePDG);
                // if (forwardQuarkKinematics.pt < particleMomentum.Pt())
                // {

                forwardQuarkKinematics = convertToKinematics(particleMomentum, particlePDG);
                PDG_ForwardQuarks->push_back(particlePDG);

                if (PDG_ForwardQuarks->size() > 1)
                {
                    std::cout << "number of forward quarks = " << PDG_ForwardQuarks->size() << std::endl;
                    std::cout << "number of forward quarks mother1 = " << mother1 << "\t" << bkgReader.hepeup.IDUP.at(mother1) << std::endl;
                    std::cout << "number of forward quarks mother2= " << mother2 << "\t" << bkgReader.hepeup.IDUP.at(mother2) << "\n\n"
                              << std::endl;
                    COUNTER++;
                    throw std::runtime_error("More than one forward quark detected");
                }
            }
        }
    }

    // Handle intermediate particles
    if (status == STATUS_INTERMEDIATE)
    {
        PDG_IntermediateParticles->push_back(particlePDG);
    }
}

int main(int argc, char **argv)
{
    TFile file(argv[2], "RECREATE");
    file.SetCompressionLevel(2);
    TTree *tree = new TTree("tree", "Particles Info");

    // Declare branches for the TTree
    tree->Branch("leadingLeptonFromZ", &leadingLeptonFromZ, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("subleadingLeptonFromZ", &subleadingLeptonFromZ, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("leptonFromW", &leptonFromW, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("neutrinoFromW", &neutrinoFromW, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("leadingQuarkFromW", &leadingQuarkFromW, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("subleadingQuarkFromW", &subleadingQuarkFromW, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("wBosonKinematics", &wBosonKinematics, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("bQuarkFromTopKinematics", &bQuarkFromTopKinematics, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("forwardQuarkKinematics", &forwardQuarkKinematics, "pt/D:eta:phi:energy:mass:pdgID/I");
    tree->Branch("PDG_IncomingParticles", &PDG_IncomingParticles);
    tree->Branch("PDG_OutgoingParticles", &PDG_OutgoingParticles);
    tree->Branch("PDG_IntermediateParticles", &PDG_IntermediateParticles);
    tree->Branch("PDG_OutgoingParticles_LEPW", &PDG_OutgoingParticles_LEPW);
    tree->Branch("PDG_OutgoingParticles_NeutrinoW", &PDG_OutgoingParticles_NeutrinoW);
    tree->Branch("PDG_OutgoingParticles_LEPZ", &PDG_OutgoingParticles_LEPZ);
    tree->Branch("PDG_OutgoingParticles_QuarkW", &PDG_OutgoingParticles_QuarkW);
    tree->Branch("PDG_OutgoingParticles_QuarkTop", &PDG_OutgoingParticles_QuarkTop);
    tree->Branch("PDG_OutgoingParticles_OtherQuark", &PDG_OutgoingParticles_OtherQuark);

    std::ifstream ifsbkg(argv[1]);
    LHEF::Reader bkgReader(ifsbkg);

    // Loop over events
    int nEvents = 0;
    while (bkgReader.readEvent())
    {
        ++nEvents;

        PDG_IncomingParticles->clear();
        PDG_OutgoingParticles->clear();
        PDG_IntermediateParticles->clear();
        PDG_ForwardQuarks->clear();

        PDG_OutgoingParticles_LEPW->clear();
        PDG_OutgoingParticles_LEPZ->clear();
        PDG_OutgoingParticles_NeutrinoW->clear();
        PDG_OutgoingParticles_OtherQuark->clear();
        PDG_OutgoingParticles_QuarkTop->clear();
        PDG_OutgoingParticles_QuarkW->clear();

        if (nEvents > EVENTSTORUN && DEBUG)
            break;

        if (Verbose)
            std::cout << "\n\n====> BKG event " << nEvents << "\n";

        // Loop over particles in the event
        if (Verbose)
            std::cout << "Total number of partices: " << bkgReader.hepeup.IDUP.size() << std::endl;
        for (int iPart = 0; iPart < bkgReader.hepeup.IDUP.size(); ++iPart)
        {
            handleParticle(iPart, bkgReader);
        }
        // std::cout << " " << std::endl;
        // std::cout << "Incoming particles: \t" << PDG_IncomingParticles->size() << std::endl;
        // std::cout << "Intermediate particles\t" << PDG_IntermediateParticles->size() << std::endl;
        // std::cout << "Outgoing particles\t" << PDG_OutgoingParticles->size() << std::endl;
        // std::cout << "Outgoing LEPW\t" << PDG_OutgoingParticles_LEPW->size() << std::endl;
        // std::cout << "Outgoing NeutrinoW\t" << PDG_OutgoingParticles_NeutrinoW->size() << std::endl;
        // std::cout << "Outgoing LEPZ\t" << PDG_OutgoingParticles_LEPZ->size() << std::endl;
        // std::cout << "Outgoing QuarkW\t" << PDG_OutgoingParticles_QuarkW->size() << std::endl;
        // std::cout << "Outgoing QuarkTop\t" << PDG_OutgoingParticles_QuarkTop->size() << std::endl;
        // std::cout << "Outgoing OtherQuark\t" << PDG_OutgoingParticles_OtherQuark->size() << std::endl;

        // std::cout << "Outgoing LEPZ (" << PDG_OutgoingParticles_LEPZ->size() << "): ";
        // for_each(PDG_OutgoingParticles_LEPZ->begin(), PDG_OutgoingParticles_LEPZ->end(), [](int id)
        //          { std::cout << id << " "; });
        // std::cout << std::endl;

        if(Verbose)
        {
        std::cout << "Incoming particles (" << PDG_IncomingParticles->size() << "): ";
        for_each(PDG_IncomingParticles->begin(), PDG_IncomingParticles->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Intermediate particles (" << PDG_IntermediateParticles->size() << "): ";
        for_each(PDG_IntermediateParticles->begin(), PDG_IntermediateParticles->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Outgoing particles (" << PDG_OutgoingParticles->size() << "): ";
        for_each(PDG_OutgoingParticles->begin(), PDG_OutgoingParticles->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Outgoing LEPW (" << PDG_OutgoingParticles_LEPW->size() << "): ";
        for_each(PDG_OutgoingParticles_LEPW->begin(), PDG_OutgoingParticles_LEPW->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Outgoing NeutrinoW (" << PDG_OutgoingParticles_NeutrinoW->size() << "): ";
        for_each(PDG_OutgoingParticles_NeutrinoW->begin(), PDG_OutgoingParticles_NeutrinoW->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Outgoing LEPZ (" << PDG_OutgoingParticles_LEPZ->size() << "): ";
        for_each(PDG_OutgoingParticles_LEPZ->begin(), PDG_OutgoingParticles_LEPZ->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Outgoing QuarkW (" << PDG_OutgoingParticles_QuarkW->size() << "): ";
        for_each(PDG_OutgoingParticles_QuarkW->begin(), PDG_OutgoingParticles_QuarkW->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Outgoing QuarkTop (" << PDG_OutgoingParticles_QuarkTop->size() << "): ";
        for_each(PDG_OutgoingParticles_QuarkTop->begin(), PDG_OutgoingParticles_QuarkTop->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;

        std::cout << "Outgoing OtherQuark (" << PDG_OutgoingParticles_OtherQuark->size() << "): ";
        for_each(PDG_OutgoingParticles_OtherQuark->begin(), PDG_OutgoingParticles_OtherQuark->end(), [](int id)
                 { std::cout << id << " "; });
        std::cout << std::endl;
        }

        // Fill the tree with the current event's data
        tree->Fill();
    }

    std::cout << "Total Events = " << nEvents << std::endl;
    std::cout << "Total number of events having > 1 forward quark: " << COUNTER << std::endl;
    file.cd();
    tree->Write();
    file.Close();

    return 0;
}
