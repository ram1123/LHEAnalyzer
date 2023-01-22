import uproot
import matplotlib.pyplot as plt

# Define the path to the root files
file1_path = "/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_150to600_4f_NLO_FXFX_2.root"
file2_path = "/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_800toInf_4f_NLO_FXFX_2.root"

# Open the root files using uproot
file1 = uproot.open(file1_path)
file2 = uproot.open(file2_path)

# Define the branches you want to plot
branches = ["mWW"]

# Loop over the branches and plot them
print("start...")
for branch in branches:
    # Get the branch data from the root file
    data1 = file1[branch].array()
    data2 = file2[branch].array()

    # Plot the data using matplotlib
    plt.hist(data1, bins=1000, alpha=0.5, label="File 1 - {}".format(branch))
    plt.hist(data2, bins=1000, alpha=0.5, label="File 2 - {}".format(branch))
    plt.legend()
    plt.show()
    plt.savefig(branch + "_compare.pdf")
