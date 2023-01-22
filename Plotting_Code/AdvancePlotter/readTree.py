import ROOT
from ROOT import TCanvas, gROOT
gROOT.SetBatch(True)

class TreeDrawer:
    def __init__(self, file, branch, tree, OutPutPlotName, NameAppend):
        self.file = file
        self.branch = branch
        self.tree = tree
        self.OutPutPlotName = OutPutPlotName
        self.NameAppend = NameAppend

    def treeDraw(self):
        if self.OutPutPlotName == "":
            self.OutPutPlotName = self.branch

        f = ROOT.TFile.Open(self.file, "read")
        t = f.Get(self.tree)
        c = ROOT.TCanvas('mycanvas', 'mycanvas')
        if self.branch == "mWW":
            t.Draw(self.branch+'>>h(1000, 0, 2000)')
            c.SetLogy(1)
        else:
            t.Draw(self.branch)

        c.SaveAs(self.OutPutPlotName+"_"+self.NameAppend+".pdf")

# Define the input files
file1 = "/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_150to600_4f_NLO_FXFX.root"
file2 = "/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_600to800_4f_NLO_FXFX.root"
file3 = "/afs/cern.ch/user/r/rasharma/work/aTGC/CMSSW_10_2_13/src/LHEAnalyzer/output_hadd_800toInf_4f_NLO_FXFX.root"

# Usage
treeDrawer = TreeDrawer(file1, "mWW", "tree", "", "150"); treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file1, "mWLep", "tree", "", "150");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file1, "mWHad", "tree", "", "150");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file1, "initialQuarks", "tree", "", "150");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file1, "outgoingParticles", "tree", "", "150");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file1, "intermediateParticles", "tree", "", "150");	treeDrawer.treeDraw()

treeDrawer = TreeDrawer(file2, "mWW", "tree", "", "600"); treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file2, "mWLep", "tree", "", "600");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file2, "mWHad", "tree", "", "600");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file2, "initialQuarks", "tree", "", "600");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file2, "outgoingParticles", "tree", "", "600");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file2, "intermediateParticles", "tree", "", "600");	treeDrawer.treeDraw()

treeDrawer = TreeDrawer(file3, "mWW", "tree", "", "800"); treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file3, "mWLep", "tree", "", "800");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file3, "mWHad", "tree", "", "800");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file3, "initialQuarks", "tree", "", "800");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file3, "outgoingParticles", "tree", "", "800");	treeDrawer.treeDraw()
treeDrawer = TreeDrawer(file3, "intermediateParticles", "tree", "", "800");	treeDrawer.treeDraw()


