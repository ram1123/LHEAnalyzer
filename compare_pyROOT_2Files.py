import ROOT
from ROOT import TCanvas, gROOT, TLine
gROOT.SetBatch(True)
from array import array
import sys

# Open the root files
file1 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_800toInf_4f_NLO_FXFX_all_v2.root", "read")
file2 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_800toInf_4f_NLO_FXFX_all_v2.root", "read")

FileAppend = "800_nqG2"
# Get the branches you want to plot
tree1 = file1.Get("tree")
tree2 = file2.Get("tree")

dicts = {
    "mWW": "M_{W(#rightarrow l#nu)W(#rightarrow qq)}",
    "mWW_PDG": "M_{W(#rightarrow l#nu)W(#rightarrow qq)}",
    # "WHad_pT": "p_{T}(W#rightarrow qq)",
    # "WLep_pT": "p_{T}(W#rightarrow l#nu)",
    "WHad_pT": "p_{T}(W)",
    "WLep_pT": "p_{T}(W)"
}
if len(sys.argv) < 3:
    InputVarToCompare = "WHad_pT"
    InputVarToCompare2 = "WHad_pT"
    title = dicts[InputVarToCompare]
    title2 = dicts[InputVarToCompare2]
else:
    InputVarToCompare = sys.argv[1]
    InputVarToCompare2 = sys.argv[2]
    title = dicts[InputVarToCompare]
    title2 = dicts[InputVarToCompare2]

# Define the variable bin for the mWW histogram
varBins = [0, 15, 30, 50, 60, 70, 80, 90, 100, 120, 150, 170, 200, 225, 250, 275, 300, 350, 400, 450, 500, 550, 600, 625, 650, 675, 700, 725, 750, 775, 800]
# if InputVarToCompare == "mWW" or InputVarToCompare == "mWW_PDG":
for i in range(850,2050,50):
        varBins.append(i)

bin_edges = array('f', varBins)
nbins = len(varBins)-1
print(bin_edges)

# Define the histograms
hist1 = ROOT.TH1F("hist1", title + ";" + title + ";Entries", nbins, bin_edges)
hist2 = ROOT.TH1F("hist2", title2 + ";" + title2 + ";Entries", nbins, bin_edges)

# Fill the histograms with the branch values from the trees
tree1.Draw(InputVarToCompare + ">>hist1","nQuarks==2")
tree2.Draw(InputVarToCompare2 + ">>hist2","nQuarks>2")

# hist1.Scale(1./hist1.Integral())
# hist2.Scale(1./hist2.Integral())
# hist3.Scale(1./hist3.Integral())

# hist1.SetMaximum(10000.)

# Create a canvas
c = ROOT.TCanvas("c", "c", 800, 600)

# Draw the branches on the canvas
hist1.Draw()
hist2.Draw("same")
hist1.Scale(1/hist1.Integral())
hist2.Scale(1/hist2.Integral())

# hist1.Sumw2();
# hist2.Sumw2();

# Set the colors of the histograms
hist1.SetLineColor(ROOT.kBlue)
hist2.SetLineColor(ROOT.kRed)


# Add a legend
legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend.AddEntry(hist1, "nQuarks==2", "l")
legend.AddEntry(hist2, "nQuarks>2", "l")
legend.Draw()

# Create a line object
line = TLine()
# Set the line properties
line.SetLineColor(7) # red
line.SetLineWidth(2)
line.SetLineStyle(3)
# Draw the line on the histogram
# The arguments are x1, y1, x2, y2
if InputVarToCompare == "mWW_PDG":
    line.DrawLine(150, 0, 150, hist1.GetMaximum())
    line.DrawLine(600, 0, 600, hist1.GetMaximum())
    line.DrawLine(800, 0, 800, hist1.GetMaximum())
elif  "_pT" in InputVarToCompare:
    line.DrawLine(150, 0, 150, hist1.GetMaximum()*1.5)
else:
    pass
# Update and save the canvas
c.SetLogy(1)
c.Update()
# c.SaveAs("compare_mWW_mWWPDG_old.pdf")
c.SaveAs("compare_branchesSameTree_"+InputVarToCompare+"_"+InputVarToCompare2+"_"+FileAppend+".pdf")
