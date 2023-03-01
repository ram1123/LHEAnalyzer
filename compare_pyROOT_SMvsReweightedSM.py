import ROOT
from ROOT import TCanvas, gROOT, TLine, gStyle
gROOT.SetBatch(True)
gStyle.SetOptStat(0)
from array import array
import sys

IfnQCut = False
IfLog = True
IFNORMUnity = False

if IfnQCut:
    cut_string = "nQuarks == 2"
    # cut_string = "nQuarks > 2"
else:
    cut_string = "NA"

if sys.version_info[0] >= 3:
    print("WARNING: This script requires Python 2. Please use Python 2 to run this script.")
    # sys.exit()

# Open the root files
file1 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-150to600.root", "read")
file2 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-600to800.root", "read")
file3 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/WmWpToLmNujj_01j_aTGC_pTW-150toInf_mWV-800toInf.root", "read")
file4 = ROOT.TFile.Open("/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_SM_WWToLNuQQ_4f.root", "read")

# Get the branches you want to plot
tree1 = file1.Get("tree")
tree2 = file2.Get("tree")
tree3 = file3.Get("tree")
tree4 = file4.Get("tree")

dicts = {
    "mWW_PDG": "M_{W(#rightarrow l#nu)W(#rightarrow qq)}",
    "WHad_pT": "p_{T}(W#rightarrow qq)",
    "WLep_pT": "p_{T}(W#rightarrow l#nu)",
    "nQuarks": "Number of quarks in final state",
    "mWHad": "M_{W(#rightarrow qq)}",
    "mWLep": "M_{W(#rightarrow l#nu)}"
}
if len(sys.argv) < 2:
    InputVarToCompare = "WHad_pT"
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
if InputVarToCompare == "nQuarks":
    varBins = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
if InputVarToCompare == "WHad_pT" or InputVarToCompare == "mWLep":
    varBins = []
    for i in range(150, 2000, 50):
        varBins.append(i)
bin_edges = array('f', varBins)
nbins = len(varBins)-1
print(bin_edges)




# Define the histograms
hist1 = ROOT.TH1F("hist1", title + ";" + title + ";Entries", nbins, bin_edges)
hist2 = ROOT.TH1F("hist2", title + ";" + title + ";Entries", nbins, bin_edges)
hist3 = ROOT.TH1F("hist3", title + ";" + title + ";Entries", nbins, bin_edges)
hist7 = ROOT.TH1F("hist7", title + ";" + title + ";Entries", nbins, bin_edges)
if IfnQCut:
    hist4 = ROOT.TH1F("hist4", title + ";" + title + ";Entries", nbins, bin_edges)
    hist5 = ROOT.TH1F("hist5", title + ";" + title + ";Entries", nbins, bin_edges)
    hist6 = ROOT.TH1F("hist6", title + ";" + title + ";Entries", nbins, bin_edges)

# Fill the histograms with the branch values from the trees
tree1.Draw(InputVarToCompare + ">>hist1","SM_Weight")
tree2.Draw(InputVarToCompare + ">>hist2","SM_Weight")
tree3.Draw(InputVarToCompare + ">>hist3","SM_Weight")
tree4.Draw(InputVarToCompare + ">>hist7","(mWW_PDG>150 && WHad_pT>150)")
# tree4.Draw(InputVarToCompare + ">>hist7","mWW_PDG>150")
if IfnQCut:
    tree1.Draw(InputVarToCompare + ">>hist4",cut_string)
    tree2.Draw(InputVarToCompare + ">>hist5",cut_string)
    tree3.Draw(InputVarToCompare + ">>hist6",cut_string)

# Use error bars
hist1.Sumw2();
hist2.Sumw2();
hist3.Sumw2();
hist7.Sumw2();
if IfnQCut:
    hist4.Sumw2();
    hist5.Sumw2();
    hist6.Sumw2();

# Scaling of  histogram
if IFNORMUnity:
    hist1.Scale(1./hist1.Integral())
    hist2.Scale(1./hist2.Integral())
    hist3.Scale(1./hist3.Integral())
    if IfnQCut:
        hist4.Scale(1./hist4.Integral())
        hist5.Scale(1./hist5.Integral())
        hist6.Scale(1./hist6.Integral())
else:
    hist1.Scale((138.0*3.781)/hist1.Integral())
    hist2.Scale((138.0*0.6855)/hist2.Integral())
    hist3.Scale((138.0*0.7582)/hist3.Integral())
    hist7.Scale((138.0*50.9)/hist3.Integral())    # TO-DO: Update the cross-section for SM sample
    if IfnQCut:
        hist4.Scale((138.0*3.781)/hist4.Integral())
        hist5.Scale((138.0*0.6855)/hist5.Integral())
        hist6.Scale((138.0*0.7582)/hist6.Integral())

hist1.Add(hist2)
hist1.Add(hist3)
# hist1.Add(hist7)

print(hist1.GetMaximum())
print(hist2.GetMaximum())
print(hist3.GetMaximum())
print(hist7.GetMaximum())
if IfnQCut:
    print(hist4.GetMaximum())
    print(hist5.GetMaximum())
    print(hist6.GetMaximum())

peak1 =max(max(max(hist1.GetMaximum(), hist2.GetMaximum()),max(hist3.GetMaximum(), hist2.GetMaximum())), hist7.GetMaximum())
if IfnQCut:
    peak2 = max(max(hist4.GetMaximum(), hist5.GetMaximum()),max(hist6.GetMaximum(), hist5.GetMaximum()))
else:
    peak2 = 0.0
peak = max(peak1, peak2)
print("Max y-axis value: ",peak)

if IfLog:
    scaling = 2
else:
    scaling = 1.2
hist1.SetMaximum(peak*scaling)

# Create a canvas
c = ROOT.TCanvas("c", "c", 800, 600)

# hist1.Scale(1./hist1.Integral())
# hist7.Scale(1./hist7.Integral())

# Draw the branches on the canvas
hist1.Draw()
# hist2.Draw("same")
# hist3.Draw("same")
hist7.Draw("same")
if IfnQCut:
    hist4.Draw("same")
    hist5.Draw("same")
    hist6.Draw("same")

# Set the colors of the histograms
hist1.SetLineColor(ROOT.kBlue)
hist2.SetLineColor(ROOT.kBlue)
hist3.SetLineColor(ROOT.kBlue)
hist7.SetLineColor(ROOT.kRed)
hist1.SetMarkerColor(ROOT.kBlue)
hist2.SetMarkerColor(ROOT.kBlue)
hist3.SetMarkerColor(ROOT.kBlue)
hist7.SetMarkerColor(ROOT.kRed)
hist1.SetMarkerSize(1)
hist2.SetMarkerSize(1)
hist3.SetMarkerSize(1)
hist7.SetMarkerSize(1)
hist1.SetMarkerStyle(2)
hist2.SetMarkerStyle(4)
hist3.SetMarkerStyle(26)
hist7.SetMarkerStyle(28)
if IfnQCut:
    hist4.SetLineColor(ROOT.kRed)
    hist5.SetLineColor(ROOT.kRed)
    hist6.SetLineColor(ROOT.kRed)
    hist4.SetMarkerColor(ROOT.kRed)
    hist5.SetMarkerColor(ROOT.kRed)
    hist6.SetMarkerColor(ROOT.kRed)
    hist4.SetMarkerSize(1)
    hist5.SetMarkerSize(1)
    hist6.SetMarkerSize(1)
    hist4.SetMarkerStyle(2)
    hist5.SetMarkerStyle(4)
    hist6.SetMarkerStyle(26)

# # Create a line object
# line = TLine()
# # Set the line properties
# line.SetLineColor(1) # red
# line.SetLineWidth(3)
# line.SetLineStyle(3)
# # Draw the line on the histogram
# # The arguments are x1, y1, x2, y2
# if InputVarToCompare == "mWW_PDG":
#     line.DrawLine(150, 0, 150, hist1.GetMaximum())
#     line.DrawLine(600, 0, 600, hist1.GetMaximum())
#     line.DrawLine(800, 0, 800, hist1.GetMaximum())
# elif  "_pT" in InputVarToCompare:
#     line.DrawLine(150, 0, 150, hist1.GetMaximum())
# else:
#     pass
# Add a legend
legend = ROOT.TLegend(0.5, 0.7, 0.9, 0.9)
# legend.AddEntry(hist1, "150-600", "p")
# legend.AddEntry(hist2, "600-800", "p")
# legend.AddEntry(hist3, "800-Inf", "p")
legend.AddEntry(hist1, "Reweighted SM", "p")
legend.AddEntry(hist7, "SM", "p")
if IfnQCut:
    legend.AddEntry(hist4, "150-600" + "("+cut_string+")", "p")
    legend.AddEntry(hist5, "600-800" + "("+cut_string+")", "p")
    legend.AddEntry(hist6, "800-Inf" + "("+cut_string+")", "p")

legend.Draw()

# Update and save the canvas
if IfLog:
    c.SetLogy(1)
else:
    c.SetLogy(0)

c.Update()
if IfLog:
    c.SaveAs("compare_branches_"+InputVarToCompare+"_"+"_SMComp_UpTo400GeV_log.pdf")
else:
    c.SaveAs("compare_branches_"+InputVarToCompare+"_"+"_SMComp_UpTo400GeV.pdf")

# if IfLog:
#     c.SaveAs("compare_branches_"+InputVarToCompare+"_"+"nQuarkEquals2"+"_SMComp_UpTo400GeV_log.pdf")
# else:
#     c.SaveAs("compare_branches_"+InputVarToCompare+"_"+"nQuarkEquals2"+"_SMComp_UpTo400GeV.pdf")
