"""
Help:
This script will run using python3.
Run using: python3 Plotter.py
"""

import ROOT
import sys

if sys.version_info[0] < 3:
    print("This script requires Python 3. Please use Python 3 to run this script.")
    sys.exit()

def plot_and_save(tree, branch_name, variables):
    c = ROOT.TCanvas(branch_name, branch_name, 800, 600)
    for var in variables:
        tree.Draw(f"{branch_name}.{var}")
        c.SaveAs(f"{branch_name}_{var}.png")

def main():
    # Load the ROOT file
    f = ROOT.TFile.Open("output_tvvj/tvvj_all_decayed.root")
    tree = f.Get("tree")

    # Define the branches and the variables in each branch
    branches = {
        "leadingLeptonFromZ": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "subleadingLeptonFromZ": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "leptonFromW": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "neutrinoFromW": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "leadingQuarkFromW": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "subleadingQuarkFromW": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "wBosonKinematics": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "bQuarkFromTopKinematics": ["pt", "eta", "phi", "energy", "mass", "pdgID"],
        "forwardQuarkKinematics": ["pt", "eta", "phi", "energy", "mass", "pdgID"]
    }

    # Loop through each branch and plot the variables
    for branch, variables in branches.items():
        plot_and_save(tree, branch, variables)

    f.Close()

if __name__ == "__main__":
    main()
