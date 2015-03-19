/*
this program plots one branch of different trees on the same histogram 

var1 is the variable that we want to plot

var2: Presently not used

n is the number of input rootfiles 


format to enter

	$root -l
	root[].L CompareAdvanced.C
	root[]compareQuantities( 1 , 0 , 0 , 0 , "branch_name", " " , "x-axis Title",10,0,200,Cut,2,"abc.root","abc","xyz.root","xyz");

abc.root is the name of root file  --->>> abc is the legend of abc.root;   similarly others.
*/
#include <string>
//#include "CrossSection.h"

void compareQuantities(bool NormUnity, bool NormLumi, bool ShowEvents, bool GetFOMCut , string var1, string var2, string xtitle, int nbins, float min, float max, string cut="",int n,...){
	
	float a1=0.29;
	float a2;
		if (n<=3) a2=0.59;
		else 
		if (n==4) a2=0.42;
		else
		{
		cout<<"Please Enter the Correct value of size of legend"<<endl;
		a2=0.42;
		}

	int color[9] = {2,4,3,1,5,1,7,8,9};
	int style[9] = {1,2,3,4,1,4};
	float yMax = 0.0;	// Initialize Maximum value of y-axis

	float xSec; 		// Cross-section
	float Lumi=0.075;	// Luminosity

	cmsprem = new TLatex(0,0.45,"CMS Preliminary");
	cmsprem->SetTextSize(0.04);

	if (var2 == "") var2 = var1;
	if (xtitle == "") xtitle = var1;
	
	//	cout<<var1<<"\t"<<var2<<endl;

	gStyle->SetOptStat(0);
	gROOT->ForceStyle(kTRUE);
	TGaxis::SetMaxDigits(3);

	#if 0
	vector<int> VecA, VecB, VecC, VecD;
		VecA.clear();
		VecB.clear();
		VecC.clear();
		VecD.clear();
	#else
	float VecA[50] , VecB[50] , VecC[50] , VecD[50] , VecE[50];
	#endif

	va_list list;
	va_start(list, n);
	char** fname=new char*[n];
	TFile** tf = new TFile*[n];
	TTree** tt = new TTree*[n];
	TH1F** th = new TH1F*[n];
	TPaveStats** tp = new TPaveStats*[n];
	TLegend** leg = new TLegend*[n];
	TH1F * hs = new TH1F("hs","",nbins,min,max);

	for (int i=0;i<n;i++)
	{


		fname[i]=va_arg(list, char*);
		tf[i] = new TFile(fname[i]);
		//tt[i] = (TTree*) tf[i]->Get("demo/tree");
		tt[i] = (TTree*) tf[i]->Get("tree");		// Put the name of tree here
		th[i] = new TH1F(Form("th%i",i),"",nbins,min,max);
		tt[i]->Draw(Form("%s>>th%i",var1.c_str(),i), cut.c_str());
		
		th[i]->SetStats(0);
		th[i]->SetLineWidth(2);
		th[i]->SetLineStyle(style[i]);
		th[i]->SetLineColor(color[i]);
		
		th[i]->GetYaxis()->CenterTitle();
		th[i]->GetYaxis()->SetTitleOffset(1.30);
		th[i]->GetXaxis()->SetTitle(xtitle.c_str());
		th[i]->GetXaxis()->CenterTitle();

		string tmp_str=va_arg(list,char*);

		if (NormLumi)
		{
		if (tmp_str.find("TT")==0) xSec= 0.0653247402978 ;
		if (tmp_str.find("LL")==0) xSec= 0.00602216848487 ;
		if (tmp_str.find("LT")==0) xSec= 0.0383084772305 ;
		if (tmp_str.find("TOT")==0) xSec= 0.109528995006 ;
		if (tmp_str.find("LL_nn23lo1")==0) xSec=0.0060286880679;
		if (tmp_str.find("LL_cteq6l1")==0) xSec=0.00617863847773;

		//cout<<"xSec = "<<xSec<<endl;

		//cout<<"Max before scale = "<<th[i]->GetMaximum()<<endl;
		if (i==0) th[i]->Scale((Lumi*xSec)/th[i]->Integral());
		th[i]->Scale((Lumi*xSec)/th[i]->Integral());

		//cout<<"Max after scale = "<<th[i]->GetMaximum()<<endl;
		
		#if 0
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum(th[i]->GetMaximumBin())*1.10,yMax));
		yMax = TMath::Max(th[i]->GetMaximum(th[i]->GetMaximumBin())*1.10,yMax);
		#else
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.15,yMax));
		yMax = TMath::Max(th[i]->GetMaximum()*1.15,yMax);
		#endif

		th[i]->GetYaxis()->SetTitle("Normalized to Lumi");
		}

		if (i>0) hs->Add(th[i]);
		if (i==0)TH1F *hist_new=(TH1F*)th[i]->Clone();
		if (NormUnity)
		{
		if (i==0) th[i]->Scale(1./th[i]->Integral());
		th[i]->Scale(1./th[i]->Integral());
		th[i]->GetYaxis()->SetTitle("Fraction of Events");
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.10,yMax));
		yMax = TMath::Max(th[i]->GetMaximum()*1.10,yMax);
		}
		if (GetFOMCut)
		{
		cout<<"##################################################################"<<endl;
		for (int j = 1;  j<nbins; j++ )
		{
			//cout<<j<<"th\tBin Content = "<<th[i]->Integral(j)<<endl;
			#if 1
			//if (i==0) VecA.push_back(th[i]->Integral(j));
			//if (i==1) VecB.push_back(th[i]->Integral(j));
			//if (i==2) VecC.push_back(th[i]->Integral(j));
			//if (i==3) VecD.push_back(th[i]->Integral(j));
			if (i==0) {VecA[j]=th[i]->Integral(j,nbins)/th[i]->Integral();
			VecE[j]=th[i]->GetBinCenter(j);

			cout<<"VecA = "<<VecA[j]<<endl;
			//cout<<"VecE = "<<VecE[j]<<endl;
			}
			if (i==1) {
			VecB[j]=th[i]->Integral(j,nbins)/th[i]->Integral();
			cout<<"VecB = "<<VecB[j]<<endl;
			}
			if (i==2) {
			VecC[j]=th[i]->Integral(j,nbins)/th[i]->Integral();
			cout<<"VecC = "<<VecC[j]<<endl;
			}
			if (i==3) {
			VecD[j]=th[i]->Integral(j,nbins)/th[i]->Integral();
			cout<<"VecD = "<<VecD[j]<<endl;
			}
			#else
			//if(i==0) VecA[0]=th[i]->Integral();
			//else VecB[0]+=th[i]->Integral();
			cout<<j<<"\t"<<th[i]->Integral(j,nbins)<<endl;
			#endif
		}
		}  // if (GetFOMCut)
	
		//th[0]->SetMaximum(0.0014);
		if (i==0) th[i]->Draw(); else th[i]->Draw("sames");

		if (ShowEvents)
		{
		if (n==2) leg[i] = new TLegend(a1,0.89,a2,0.99);
		else leg[i] = new TLegend(a1,0.82,a2,0.99);
		leg[i]->AddEntry(th[i],tmp_str.c_str(),"l");

		int entries = th[i]->GetEntries();
		char c[20];
		sprintf(c,"%d",entries);

		leg[i]->AddEntry(th[i],TString(c),"l");
		}
		else
		{
		if (n==2) leg[i] = new TLegend(a1,0.89,a2,0.95);
		else leg[i] = new TLegend(a1,0.89,a2,0.95);
		leg[i]->AddEntry(th[i],tmp_str.c_str(),"l");
		}
		//leg[i]->AddEntry(th[i],va_arg(list, char*),"l");
		if (n==2) leg[i]->SetTextSize(0.05);

		leg[i]->Draw("sames");
		//cmsprem->Draw();

		a1 = a2;
		if (n==2) a2=a2+0.30;
		else a2 = a2+0.16;
//		cout<<"histogram  "<<Form("th%i",i)<<"  entries = "<<th[i]->GetEntries()<<endl;

	}
	va_end(list);


hs->Scale(1/hs->Integral());
hist_new->Scale(1/hist_new->Integral());
hs->SetMaximum(0.050);
hs->Draw();
hist_new->Draw("same");

for (int j = 1; j<nbins; j++)
{
VecA[j]=hs->Integral(j,nbins);
VecB[j]=sqrt(hist_new->Integral(j,nbins));

VecC[j]=VecA[j]/(VecB[j]);
cout<<VecA[j]<<"\t"<<sqrt(VecB[j])<<"\t"<<VecB[j]<<endl;
}			
	gr = new TGraph(nbins,VecE,VecA);
	gr2 = new TGraph(nbins,VecE,VecB);
	gr3 = new TGraph(nbins,VecE,VecB);
	gr->Draw("A*");
	gr2->Draw("same");

		if (GetFOMCut)
		{
	//cout<<"Sb = "<<VecA[0]/sqrt(VecB[0])<<endl;
	//cout<<"signal = "<<VecA[0]<<"\tbkg = "<<VecB[0]<<endl;
	}


}
