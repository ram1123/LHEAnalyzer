/*
this program plots one branch of different trees on the same histogram 

var1 is the variable that we want to plot

var2 is the xtitle

n is the number of input rootfiles 

format to enter

	$root -l
	root[].L CompareAdvanced.C
	root[]compareQuantities("branch_name","x-axis Title",10,0,200,Cut,2,"abc.root","abc","xyz.root","xyz");

abc.root is the name of root file  --->>> abc is the legend of abc.root;   similarly others.
*/
void compareQuantities(string var1, string var2, int nbins, float min, float max, string cut="",int n,...){
	
	float a1=0.29;
	float a2=0.42;
	int color[9] = {2,3,4,1,5,1,7,8,9};
	int style[9] = {1,2,3,4,1,4};
	float yMax = 0.1;

	cmsprem = new TLatex(0,0.45,"CMS Preliminary");
	cmsprem->SetTextSize(0.04);

	if (var2 == "") var2 = var1;
	
	cout<<var1<<"\t"<<var2<<endl;

	gStyle->SetOptStat(0);
	gROOT->ForceStyle(kTRUE);

	va_list list;
	va_start(list, n);
	char** fname=new char*[n];
	TFile** tf = new TFile*[n];
	TTree** tt = new TTree*[n];
	TH1F** th = new TH1F*[n];
	TPaveStats** tp = new TPaveStats*[n];
	TLegend** leg = new TLegend*[n];

	for (int i=0;i<n;i++)
	{


		fname[i]=va_arg(list, char*);
		tf[i] = new TFile(fname[i]);
		//tt[i] = (TTree*) tf[i]->Get("demo/tree");
		tt[i] = (TTree*) tf[i]->Get("tree");
		th[i] = new TH1F(Form("th%i",i),"",nbins,min,max);
		tt[i]->Draw(Form("%s>>th%i",var1.c_str(),i), cut.c_str(), "goff");
		
		th[i]->SetStats(0);
		th[i]->SetLineWidth(2);
		th[i]->SetLineStyle(style[i]);
		th[i]->SetLineColor(color[i]);
		
		th[i]->GetYaxis()->SetTitle("Fraction of Events");
		th[i]->GetYaxis()->CenterTitle();
		th[i]->GetYaxis()->SetTitleOffset(1.30);
		th[i]->GetXaxis()->SetTitle(var2.c_str());
		th[i]->GetXaxis()->SetTitle(var2.c_str());
		th[i]->GetXaxis()->CenterTitle();

		if (i==0) th[i]->Scale(3/th[i]->Integral());
		th[i]->Scale(1/th[i]->Integral());
		
		//th[0]->SetMaximum(0.45);
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.10,yMax));
		yMax = TMath::Max(th[i]->GetMaximum()*1.10,yMax);
		if (i==0) th[i]->Draw(); else th[i]->Draw("sames");

		leg[i] = new TLegend(a1,0.85,a2,0.99);
		leg[i]->AddEntry(th[i],va_arg(list, char*),"l");

		int entries = th[i]->GetEntries();
		char c[20];
		sprintf(c,"%d",entries);

		leg[i]->AddEntry(th[i],TString(c),"l");
		leg[i]->Draw("sames");
		//cmsprem->Draw();

		a1 = a2;
		a2 = a2+0.16;
		cout<<"histogram  "<<Form("th%i",i)<<"  entries = "<<th[i]->GetEntries()<<endl;

	}
	va_end(list);


}
