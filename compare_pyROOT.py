import ROOT
from ROOT import TCanvas, gROOT, TLine
gROOT.SetBatch(True)
from array import array
import sys

# Open the root files
file1 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_150to600_4f_NLO_FXFX_10.root", "read")
file2 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_600to800_4f_NLO_FXFX_10.root", "read")
file3 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_800toInf_4f_NLO_FXFX_10.root", "read")

# Get the branches you want to plot
tree1 = file1.Get("tree")
tree2 = file2.Get("tree")
tree3 = file3.Get("tree")

dicts = {
    "mWW_PDG": "M_{W(#rightarrow l#nu)W(#rightarrow qq)}",
    "WHad_pT": "p_{T}(W#rightarrow qq)",
    "WLep_pT": "p_{T}(W#rightarrow l#nu)"
}
if len(sys.argv) < 2:
    InputVarToCompare = "mWW_PDG"
    title = dicts[InputVarToCompare]
else:
    InputVarToCompare = sys.argv[1]
    title = dicts[InputVarToCompare]

# Define the variable bin for the mWW_PDG histogram
# varBins = [0, 50, 70, 100, 120, 150, 170, 200, 225, 250, 275, 300, 350, 400, 450, 500, 550, 600, 625, 650, 675, 700, 725, 750, 775, 800]
# if InputVarToCompare == "mWW_PDG":
    # for i in range(850,2050,50):
        # varBins.append(i)
varBins = []
for i in range(0, 2050,25):
    varBins.append(i)
bin_edges = array('f', varBins)
nbins = len(varBins)-1
print(bin_edges)

# Define the histograms
hist1 = ROOT.TH1F("hist1", title + ";" + title + ";Entries", nbins, bin_edges)
hist2 = ROOT.TH1F("hist2", title + ";" + title + ";Entries", nbins, bin_edges)
hist3 = ROOT.TH1F("hist3", title + ";" + title + ";Entries", nbins, bin_edges)


# Fill the histograms with the branch values from the trees
tree1.Draw(InputVarToCompare + ">>hist1")
tree2.Draw(InputVarToCompare + ">>hist2")
tree3.Draw(InputVarToCompare + ">>hist3")

# Use error bars
hist1.Sumw2();
hist2.Sumw2();
hist3.Sumw2();

# Scale each histogram to unity
# hist1.Scale((1./hist1.Integral())*3.781)
# hist2.Scale((1./hist2.Integral())*0.6855)
# hist3.Scale((1./hist3.Integral())*0.7582)

hist1.Scale((138.0*3.781)/hist1.Integral())
hist2.Scale((138.0*0.6855)/hist2.Integral())
hist3.Scale((138.0*0.7582)/hist3.Integral())

print(hist1.GetMaximum())
print(hist2.GetMaximum())
print(hist3.GetMaximum())
print(max(max(hist1.GetMaximum(), hist2.GetMaximum()),max(hist3.GetMaximum(), hist2.GetMaximum())))

hist1.SetMaximum(max(max(hist1.GetMaximum(), hist2.GetMaximum()),max(hist3.GetMaximum(), hist2.GetMaximum()))*1.1)

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
hist1.SetMarkerColor(ROOT.kBlue)
hist2.SetMarkerColor(ROOT.kRed)
hist3.SetMarkerColor(ROOT.kGreen)

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
    line.DrawLine(150, 0, 150, hist1.GetMaximum())
else:
    pass
# Add a legend
legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend.AddEntry(hist1, "150-600", "l")
legend.AddEntry(hist2, "600-800", "l")
legend.AddEntry(hist3, "800-Inf", "l")
legend.Draw()

# Update and save the canvas
c.SetLogy(0)
c.Update()
c.SaveAs("compare_branches_"+InputVarToCompare+".pdf")
# c.SaveAs("compare_branches_"+InputVarToCompare+"_log.pdf")
