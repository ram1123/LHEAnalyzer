/*
this program plots histogram form different root file on the same canvas

tree = 0 if we need to read histogram 
tree = 1 if we need to read branch of tree  NOTE: CHANGE THE NAME OF TREE 
var1 is the variable that we want to plot

var2 is the xtitle

n is the number of input rootfiles 

format to enter

	$root -l
	root[].L CompareAdvanced.C
	root[]compareQuantities(0/1,"branch_name","x-axis Title",10,0,200,Cut,2,"abc.root","abc","xyz.root","xyz");


abc.root is the name of root file  --->>> abc is the legend of abc.root;   similarly others.

19 August: Trying to add ratio plot at bottom of each plot.
*/

#include <cstdio>
#include <cstdarg>

void compareQuantities(bool ratio,int tree, string var1, string var2, int nbins, float min, float max, string cut="",int n,...){
	
	float a1=0.04;
	float a2=0.20;
	int color[9] = {2,3,6,4,1,9,7,8,9};
	int style[9] = {1,4,3,1,1,4};
	float yMax = 0.1;

// TCanvas *Canvas1 = new TCanvas("Canvas1","example",600,700);
   TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
   pad1->SetBottomMargin(0);
   pad1->Draw();
   pad1->cd();

	if (var2 == "") var2 = var1;
	
	cout<<var1<<"\t"<<var2<<endl;

	gStyle->SetOptStat(0);
	gROOT->ForceStyle(kTRUE);

	va_list list;
	va_start(list, n);
	cout<<"n  = "<<n<<endl;
	char** fname=new char*[n];
	TFile** tf = new TFile*[n];
	TTree** tt = 0;
	if (tree == 1) tt = new TTree*[n];
	TH1F** th = new TH1F*[n];
	TPaveStats** tp = new TPaveStats*[n];
	TLegend** leg = new TLegend*[n];

	gPad->SetLogy(1);

	for (int i=0;i<n;i++)
	{

		fname[i]=va_arg(list, char*);
		tf[i] = new TFile(fname[i]);
		


		if (tree == 0){
			th[i] = (TH1F*)tf[i]->Get(Form("%s",var1.c_str()));
			th[i]->SetTitle("");
			th[i]->Rebin(nbins);
			th[i]->GetXaxis()->SetRangeUser(min,max);
			}

		if (tree == 1){
			//tt[i] = (TTree*) tf[i]->Get("demo/tree");
			tt[i] = (TTree*) tf[i]->Get("tree");
			th[i] = new TH1F(Form("th%i",i),"",nbins,min,max);
			tt[i]->Draw(Form("%s>>th%i",var1.c_str(),i), cut.c_str(), "goff");
			}

		th[i]->SetDirectory(0); // (0) or (gROOT)
		gROOT->cd();
		delete tf[i]; // automatically deletes the tt[i] tree, too

		th[i]->SetStats(0);
		th[i]->SetLineWidth(2);
		th[i]->SetLineStyle(style[i]);
		th[i]->SetLineColor(color[i]);
		
		th[i]->GetYaxis()->SetTitle("Fraction of Events");
		th[i]->GetYaxis()->CenterTitle();

		th[i]->GetXaxis()->SetTitle(var2.c_str());
		th[i]->GetXaxis()->SetTitle(var2.c_str());
		th[i]->GetXaxis()->CenterTitle();
		th[i]->GetYaxis()->SetTitleOffset(1.3);

		th[i]->Scale(1/th[i]->Integral());
		
	//	cout<<"################################################\n"<<fname[i]<<endl;
	//	 for (Int_t k=0;k<th[i]->GetNbinsX();k++)cout<<k<<"\t"<<th[i]->GetBinContent(k)<<endl;

	//	th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.10,yMax));
	//	yMax = TMath::Max(th[i]->GetMaximum()*1.10,yMax);
		
		th[0]->SetMaximum(0.9);

		if (i==0) th[i]->Draw(); else th[i]->Draw("sames");


		leg[i] = new TLegend(a1,0.85,a2,0.99);
		leg[i]->AddEntry(th[i],va_arg(list, char*),"l");

		int entries = th[i]->GetEntries();
		char c[20];
		sprintf(c,"%d",entries);

		leg[i]->AddEntry(th[i],TString(c),"l");
		leg[i]->Draw("sames");

		a1 = a2;
		a2 = a2+0.16;

		
	}
	va_end(list);
			
  TH1F* hh0 = (TH1F*)(th[0]->Clone("hh0"));
  TH1F* hh1 = (TH1F*)(th[1]->Clone("hh1"));
  TH1F* hh2 = (TH1F*)(th[2]->Clone("hh2"));
  TH1F* hh3 = (TH1F*)(th[3]->Clone("hh3"));

  c1->cd();
   if(ratio) TPad *pad2 = new TPad("pad2","pad2",0.008,0.0,0.492,0.3);
   else      TPad *pad2 = new TPad("pad2","pad2",0.508,0.0,0.992,0.3);

   pad2->SetTopMargin(0);
   pad2->Draw();
   pad2->cd();
   hh0->SetStats(0);
   hh0->SetMinimum(-0.1);
   hh0->SetMaximum(2.5);
   hh0->GetYaxis()->SetTitle("Ratio");
  // for (Int_t i=0;i<hh0->GetNbinsX();i++)cout<<i<<"\t"<<hh0->GetBinContent(i)<<"\t hh5 "<<th[4]->GetBinContent(i)<<"\thh3 = "<<hh3->GetBinContent(i)<<"\t0/5 = "<<(hh0->GetBinContent(i))/(th[5]->GetBinContent(i))<<"\t\t"<<(hh3->GetBinContent(i))/(th[5]->GetBinContent(i))<<endl;
//   std::cout<<"bin con "<<hh0->GetBinContent()<<endl;
   hh0->Divide(th[4]);
   hh0->SetMarkerStyle(21);
   hh0->Draw();
   hh1->Divide(th[4]);
   hh1->Draw("same");
   hh2->Divide(th[4]);
   hh2->Draw("same");
   hh3->Divide(th[4]);
   hh3->Draw("same");   

   TLine *line = new TLine(min, 1, max, 1);
   line->SetLineWidth(1);
   line->SetLineColor(kBlack);
   line->Draw();
}
