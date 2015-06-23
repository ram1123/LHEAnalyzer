#!/bin/env python

import ROOT
from ROOT import TCanvas, gROOT

gROOT.SetBatch(0) 
def treeDraw(
	file="/afs/cern.ch/user/r/rasharma/work/WW_Scattering/LheAnalyzer/CMSSW_7_4_0_pre2/src/LHEAnalyzer/pp_WpWm_LL.root",
	branch="mjj",
	tree="tree",
	OutPutPlotName=""
	):

	if OutPutPlotName == "":
		OutPutPlotName = branch

	f = ROOT.TFile.Open(file, "read")
	t = f.Get(tree)
	c = ROOT.TCanvas('mycanvas', 'mycanvas')
      	t.Draw(branch)
	c.SaveAs(OutPutPlotName+".pdf")
	#c.Update()
	#Save->c.pdf

treeDraw(branch="Iqrk0_theta")
treeDraw(branch="Iqrk1_theta")
