import ROOT
from ROOT import TCanvas, gROOT
gROOT.SetBatch(True)
from array import array

# Open the root files
file1 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_150to600_4f_NLO_FXFX_2.root", "read")
file2 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_600to800_4f_NLO_FXFX_2.root", "read")
file3 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_800toInf_4f_NLO_FXFX_2.root", "read")

# Get the branches you want to plot
tree1 = file1.Get("tree")
tree2 = file2.Get("tree")
tree3 = file3.Get("tree")

# Define the variable bin for the mWW histogram
varBins = [0, 50, 70, 100, 120, 150, 170, 200, 225, 250, 275, 300, 350, 400, 450, 500, 550, 600, 625, 650, 675, 700, 725, 750, 775, 800]
for i in range(850,2050,50):
    varBins.append(i)

bin_edges = array('f', varBins)
nbins = len(varBins)-1
print(bin_edges)

# Define the histograms
hist1 = ROOT.TH1F("hist1", "M_{W(#rightarrow l#nu)W(#rightarrow qq)};M_{W(#rightarrow l#nu)W(#rightarrow qq)};Entries", nbins, bin_edges)
hist2 = ROOT.TH1F("hist2", "M_{W(#rightarrow l#nu)W(#rightarrow qq)};M_{W(#rightarrow l#nu)W(#rightarrow qq)};Entries", nbins, bin_edges)
hist3 = ROOT.TH1F("hist3", "M_{W(#rightarrow l#nu)W(#rightarrow qq)};M_{W(#rightarrow l#nu)W(#rightarrow qq)};Entries", nbins, bin_edges)

# Fill the histograms with the branch values from the trees
tree1.Draw("mWW_PDG>>hist1")
tree2.Draw("mWW_PDG>>hist2")
tree3.Draw("mWW_PDG>>hist3")

# hist1.Scale(1./hist1.Integral())
# hist2.Scale(1./hist2.Integral())
# hist3.Scale(1./hist3.Integral())

hist1.SetMaximum(10000.)

# Create a canvas
c = ROOT.TCanvas("c", "c", 800, 600)

# Draw the branches on the canvas
hist1.Draw()
hist2.Draw("same")
hist3.Draw("same")

# Set the colors of the histograms
hist1.SetLineColor(ROOT.kBlue)
hist2.SetLineColor(ROOT.kRed)
hist3.SetLineColor(ROOT.kGreen)


# Add a legend
legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend.AddEntry(hist1, "150-600", "l")
legend.AddEntry(hist2, "600-800", "l")
legend.AddEntry(hist3, "800-Inf", "l")
legend.Draw()

# Update and save the canvas
c.SetLogy(1)
c.Update()
c.SaveAs("compare_branches.pdf")
