#include "LHEF.h"
#include "TROOT.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <cmath>
#include "TTree.h"
#include <vector>
#include <stdexcept> // for std::runtime_error
#include <iostream>
#include <string>

#define LOG(level, msg) log(level, msg, __LINE__)

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

// This is the current logging level. Adjust this to change the verbosity of your logs.
LogLevel CURRENT_LOG_LEVEL = LogLevel::INFO;

// ANSI escape codes for text coloring
const std::string RESET = "\033[0m";
const std::string BLACK = "\033[30m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string BOLD = "\033[1m";

void log(LogLevel level, const std::string &message, int line)
{
    if (level < CURRENT_LOG_LEVEL)
    {
        return;
    }

    std::string lineInfo = "[Line#" + std::to_string(line) + "]";

    switch (level)
    {
    case LogLevel::DEBUG:
        std::cout << CYAN << lineInfo << " [DEBUG] " << RESET << message << std::endl;
        break;
    case LogLevel::INFO:
        std::cout << GREEN << lineInfo << " [INFO] " << RESET << message << std::endl;
        break;
    case LogLevel::WARNING:
        std::cout << YELLOW << lineInfo << " [WARNING] " << RESET << message << std::endl;
        break;
    case LogLevel::ERROR:
        std::cerr << BOLD << RED << lineInfo << " [ERROR] " << RESET << message << std::endl;
        break;
    }
}

// Function to set log level from command line argument
void setLogLevelFromArg(const std::string &arg)
{
    if (arg == "DEBUG")
    {
        CURRENT_LOG_LEVEL = LogLevel::DEBUG;
    }
    else if (arg == "INFO")
    {
        CURRENT_LOG_LEVEL = LogLevel::INFO;
    }
    else if (arg == "WARNING")
    {
        CURRENT_LOG_LEVEL = LogLevel::WARNING;
    }
    else if (arg == "ERROR")
    {
        CURRENT_LOG_LEVEL = LogLevel::ERROR;
    }
    else
    {
        std::cerr << "Unknown log level: " << arg << ". Using default (DEBUG)." << std::endl;
    }
}

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
const int EVENTSTORUN = 5;

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

    // default constructor
    Kinematics() : pt(0.0), eta(0.0), phi(0.0), energy(0.0), mass(0.0), pdgID(0) {}

    void reset()
    {
        pt = 0.0;
        eta = 0.0;
        phi = 0.0;
        energy = 0.0;
        mass = 0.0;
        pdgID = 0;
    }
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

    int mother1Index = bkgReader.hepeup.MOTHUP.at(iPart).first - 1;  // Adjusting to 0-indexed
    int mother2Index = bkgReader.hepeup.MOTHUP.at(iPart).second - 1; // Adjusting to 0-indexed

    int grandmother1IndexForMother1 = bkgReader.hepeup.MOTHUP[mother1Index].first-1;
    int grandmother2IndexForMother1 = bkgReader.hepeup.MOTHUP[mother1Index].second-1;

    int grandmother1IndexForMother2 = bkgReader.hepeup.MOTHUP[mother2Index].first-1;
    int grandmother2IndexForMother2 = bkgReader.hepeup.MOTHUP[mother2Index].second-1;

    // if (particlePDG 4= 6 ) {
    //     std::cout << "pdgID: " << particlePDG << "\n"
    //             << "Mother: " << bkgReader.hepeup.IDUP.at(mother1Index) << ", " << bkgReader.hepeup.IDUP.at(mother2Index) << "\n"
    //             << "GM1 (Mother 1): " << bkgReader.hepeup.IDUP.at(grandmother1IndexForMother1) << "\n"
    //             << "GM2 (Mother 1): " << bkgReader.hepeup.IDUP.at(grandmother2IndexForMother1) << "\n"
    //             << "GM1 (Mother 2): " << bkgReader.hepeup.IDUP.at(grandmother1IndexForMother2) << "\n"
    //             << "GM2 (Mother 2): " << bkgReader.hepeup.IDUP.at(grandmother2IndexForMother2) << std::endl;
    // }

    if (status > 0)
        LOG(LogLevel::DEBUG, "particle PDGID " + std::to_string(particlePDG) + "\t status: " + std::to_string(status) + "\t mother: " + std::to_string(bkgReader.hepeup.IDUP.at(mother1Index)) + ", " + std::to_string(bkgReader.hepeup.IDUP.at(mother2Index)));
    else
        LOG(LogLevel::DEBUG, "particle PDGID " + std::to_string(particlePDG) + "\t status: " + std::to_string(status));

    double px = bkgReader.hepeup.PUP.at(iPart)[0];
    double py = bkgReader.hepeup.PUP.at(iPart)[1];
    double pz = bkgReader.hepeup.PUP.at(iPart)[2];
    double energy = bkgReader.hepeup.PUP.at(iPart)[3];

    TLorentzVector particleMomentum(px, py, pz, energy);

    // Handle incoming particles
    if (status == STATUS_INCOMING)
    {
        PDG_IncomingParticles->push_back(particlePDG);
        LOG(LogLevel::DEBUG, "Incoming particle: " + std::to_string(particlePDG));
    }

    // Handle outgoing particles
    if (status == STATUS_OUTGOING)
    {
        PDG_OutgoingParticles->push_back(particlePDG);

        // Storing kinematics of leptons from Z boson
        if (abs(particlePDG) >= 11 && abs(particlePDG) <= 16)
        {
            LOG(LogLevel::DEBUG, "Outgoing LEP PDGID: " + std::to_string(particlePDG));

            if (bkgReader.hepeup.IDUP.at(mother1Index) == PDG_Z_BOSON || bkgReader.hepeup.IDUP.at(mother2Index) == PDG_Z_BOSON)
            {
                LOG(LogLevel::DEBUG, "Outgoing LEP PDGID: " + std::to_string(particlePDG));
                LOG(LogLevel::DEBUG, "leadingLeptonFromZ.pt: " + std::to_string(leadingLeptonFromZ.pt) + "\t" + std::to_string(particleMomentum.Pt()));

                if (leadingLeptonFromZ.pt < particleMomentum.Pt())
                {
                    subleadingLeptonFromZ = leadingLeptonFromZ;
                    leadingLeptonFromZ = convertToKinematics(particleMomentum, particlePDG);
                }
                else
                {
                    subleadingLeptonFromZ = convertToKinematics(particleMomentum, particlePDG);
                }

                LOG(LogLevel::DEBUG, "leading lepton from Z: pT: " + std::to_string(leadingLeptonFromZ.pt) + "\t" + std::to_string(leadingLeptonFromZ.pdgID));
                LOG(LogLevel::DEBUG, "sub-leading lepton from Z: pT: " + std::to_string(subleadingLeptonFromZ.pt) + "\t" + std::to_string(subleadingLeptonFromZ.pdgID));

                }

            // Storing kinematics of lepton and neutrino from W boson
            // if (abs(particlePDG) >= 11 && abs(particlePDG) <= 16)
            // if (bkgReader.hepeup.IDUP.at(mother1Index) == PDG_Z_BOSON || bkgReader.hepeup.IDUP.at(mother2Index) == PDG_Z_BOSON)
            if (Verbose)
                std::cout << "bkgReader.hepeup.IDUP.at(mother1Index): " << bkgReader.hepeup.IDUP.at(mother1Index) << "\t" << PDG_W_BOSON << std::endl;
            if (abs(bkgReader.hepeup.IDUP.at(mother1Index)) == PDG_W_BOSON || abs(bkgReader.hepeup.IDUP.at(mother2Index))== PDG_W_BOSON)
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
        if ((abs(bkgReader.hepeup.IDUP.at(mother1Index)) == PDG_W_BOSON || abs(bkgReader.hepeup.IDUP.at(mother2Index)) == PDG_W_BOSON) && abs(particlePDG) <= 6)
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

            // Storing kinematics of the b-quark from top
            if ((abs(bkgReader.hepeup.IDUP.at(mother1Index)) == PDG_TOP || abs(bkgReader.hepeup.IDUP.at(mother2Index)) == PDG_TOP))
            {
                if (abs(particlePDG) == PDG_B_QUARK || abs(particlePDG) == PDG_ANTI_B_QUARK)
                {
                    bQuarkFromTopKinematics = convertToKinematics(particleMomentum, particlePDG);
                    PDG_OutgoingParticles_QuarkTop->push_back(particlePDG);
                }
            }

        // Storing kinematics of other forward quark
        if (abs(particlePDG) <= 6 && particleMomentum.Pz() > 0)
        {

            if (abs(bkgReader.hepeup.IDUP.at(mother1Index)) != PDG_W_BOSON && abs(bkgReader.hepeup.IDUP.at(mother2Index)) != PDG_W_BOSON &&
                abs(bkgReader.hepeup.IDUP.at(mother1Index)) != PDG_Z_BOSON && abs(bkgReader.hepeup.IDUP.at(mother2Index)) != PDG_Z_BOSON &&
                abs(bkgReader.hepeup.IDUP.at(mother1Index)) != PDG_TOP && abs(bkgReader.hepeup.IDUP.at(mother2Index)) != PDG_TOP)
            {
                PDG_OutgoingParticles_OtherQuark->push_back(particlePDG);
                // if (forwardQuarkKinematics.pt < particleMomentum.Pt())
                // {

                forwardQuarkKinematics = convertToKinematics(particleMomentum, particlePDG);
                PDG_ForwardQuarks->push_back(particlePDG);

                if (PDG_ForwardQuarks->size() > 1)
                {
                    std::cout << "number of forward quarks = " << PDG_ForwardQuarks->size() << std::endl;
                    std::cout << "number of forward quarks mother1Index = " << mother1Index << "\t" << bkgReader.hepeup.IDUP.at(mother1Index) << std::endl;
                    std::cout << "number of forward quarks mother2Index= " << mother2Index << "\t" << bkgReader.hepeup.IDUP.at(mother2Index) << "\n\n"
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

        if ((abs(bkgReader.hepeup.IDUP.at(mother1Index)) == PDG_TOP || abs(bkgReader.hepeup.IDUP.at(mother2Index)) == PDG_TOP))
        {
            if (abs(particlePDG) == PDG_W_BOSON)
            {
                wBosonKinematics = convertToKinematics(particleMomentum, particlePDG);
            }
        }

    }
}

// A helper function to log particle information
void logParticleInfo(const std::string &particleType, std::vector<int> *particles)
{
    std::stringstream ss;
    ss << particleType << " (" << particles->size() << "): ";
    for (int id : *particles)
    {
        ss << id << " ";
    }
    LOG(LogLevel::DEBUG, ss.str());
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        LOG(LogLevel::ERROR, "You must provide both an input and output file.");
        return 1;
    }

    // Check if a log level is provided in the command line arguments
    if (argc > 3)
    {
        setLogLevelFromArg(argv[3]);
    }

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

        // Reset kinematic values before processing the event
        leadingLeptonFromZ.reset();
        subleadingLeptonFromZ.reset();
        leptonFromW.reset();
        neutrinoFromW.reset();
        leadingQuarkFromW.reset();
        subleadingQuarkFromW.reset();
        wBosonKinematics.reset();
        bQuarkFromTopKinematics.reset();
        forwardQuarkKinematics.reset();

        if (nEvents > EVENTSTORUN && DEBUG)
            break;

        LOG(LogLevel::DEBUG, "\n\n====> BKG event " + std::to_string(nEvents));

        // Loop over particles in the event
        LOG(LogLevel::INFO, "Total number of particles: " + std::to_string(bkgReader.hepeup.IDUP.size()));

        for (int iPart = 0; iPart < bkgReader.hepeup.IDUP.size(); ++iPart)
        {
            handleParticle(iPart, bkgReader);
        }

        LOG(LogLevel::DEBUG, "leading lepton from Z: pT: " + std::to_string(leadingLeptonFromZ.pt) + "\t" + std::to_string(leadingLeptonFromZ.pdgID));
        LOG(LogLevel::DEBUG, "sub-leading lepton from Z: pT: " + std::to_string(subleadingLeptonFromZ.pt) + "\t" + std::to_string(subleadingLeptonFromZ.pdgID));


        // Usage in main code (or wherever this block resides)
        if (Verbose)
        {
            logParticleInfo("Incoming particles", PDG_IncomingParticles);
            logParticleInfo("Intermediate particles", PDG_IntermediateParticles);
            logParticleInfo("Outgoing particles", PDG_OutgoingParticles);
            logParticleInfo("Outgoing LEPW", PDG_OutgoingParticles_LEPW);
            logParticleInfo("Outgoing NeutrinoW", PDG_OutgoingParticles_NeutrinoW);
            logParticleInfo("Outgoing LEPZ", PDG_OutgoingParticles_LEPZ);
            logParticleInfo("Outgoing QuarkW", PDG_OutgoingParticles_QuarkW);
            logParticleInfo("Outgoing QuarkTop", PDG_OutgoingParticles_QuarkTop);
            logParticleInfo("Outgoing OtherQuark", PDG_OutgoingParticles_OtherQuark);
        }

        // Fill the tree with the current event's data
        tree->Fill();
    }

    LOG(LogLevel::INFO, "Total Events = " + std::to_string(nEvents));
    LOG(LogLevel::INFO, "Total number of events having > 1 forward quark: " + std::to_string(COUNTER));

    file.cd();
    tree->Write();
    file.Close();

    return 0;
}
