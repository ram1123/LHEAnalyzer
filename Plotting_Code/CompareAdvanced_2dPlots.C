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
void compareQuantities(string var1, string var2, int xbins,  float minx, float maxx, int ybins, float miny, float maxy, string cut="",int n,...){
	
	float a1=0.47;
	float a2=0.55;
	int color[9] = {2,3,4,1,5,1,7,8,9};
	int style[9] = {1,2,3,4,1,4};
	float yMax = 0.1;

	cmsprem = new TLatex(0,0.45,"CMS Preliminary");
	cmsprem->SetTextSize(0.04);

	if (var2 == "") var2 = var1;
	
	cout<<var1<<"\t"<<var2<<endl;

	gStyle->SetOptStat(0);
	gStyle->SetPalette(1); 
	gROOT->ForceStyle(kTRUE);

	TGaxis::SetMaxDigits(3);

	const Int_t NRGBs = 5;
	const Int_t NCont = 255;
	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);

	va_list list;
	va_start(list, n);
	char** fname=new char*[n];
	TFile** tf = new TFile*[n];
	TTree** tt = new TTree*[n];
	TH2F** th = new TH2F*[n];
	TPaveStats** tp = new TPaveStats*[n];
	TLegend** leg = new TLegend*[n];
	TLatex** lxt = new TLatex*[n];

	for (int i=0;i<n;i++)
	{


		fname[i]=va_arg(list, char*);
		tf[i] = new TFile(fname[i]);
		//tt[i] = (TTree*) tf[i]->Get("demo/tree");
		tt[i] = (TTree*) tf[i]->Get("tree");
		th[i] = new TH2F(Form("th%i",i),"",xbins,minx,maxx,ybins,miny,maxy);
		tt[i]->Draw(Form("%s:%s>>th%i",var2.c_str(),var1.c_str(),i), cut.c_str(), "colz");
		cout<<"Correlation factor = "<<th[i]->GetCorrelationFactor()<<endl;
		
		th[i]->SetStats(0);
		th[i]->SetLineWidth(2);
		th[i]->SetLineStyle(style[i]);
		th[i]->SetLineColor(color[i]);
		
		th[i]->GetYaxis()->SetTitle(var2.c_str());
		th[i]->GetYaxis()->CenterTitle();
		th[i]->GetYaxis()->SetTitleOffset(1.00);
		th[i]->GetXaxis()->SetTitle(var1.c_str());
		th[i]->GetXaxis()->CenterTitle();

		//if (i==0) th[i]->Scale(3/th[i]->Integral());
		//th[i]->Scale(1/th[i]->Integral());
		
		//th[0]->SetMaximum(0.45);
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.10,yMax));
		yMax = TMath::Max(th[i]->GetMaximum()*1.10,yMax);
		if (i==0) th[i]->Draw("colz"); else th[i]->Draw("sames");

	//	leg[i] = new TLegend(a1,0.90,a2,0.95);
	//	leg[i]->AddEntry(th[i],va_arg(list, char*),"l");
	//	leg[i]->SetTextSize(0.05);
	//	leg[i]->Draw("sames");

		int entries = th[i]->GetEntries();
		char c[20];
		sprintf(c,"Entries = %d",entries);

/*
 *
		leg1[i] = new TLegend(a2,0.90,a2+0.35,0.95);
		leg1[i]->AddEntry(th[i],TString(c),"l");
		leg1[i]->SetTextSize(0.05);
		leg1[i]->SetMarkerColor(0);
		leg1[i]->Draw("sames");
		//cmsprem->Draw();
*
*/

		lxt[i] = new TLatex();
		lxt[i]->SetTextSize(0.05);
		lxt[i]->DrawLatex(maxx-10.00,maxy,TString("Sample : ")+TString(va_arg(list, char*)));
		lxt[i]->DrawLatex(maxx-5.00,maxy,TString(c));

		a1 = a2;
		a2 = a2+0.16;
		cout<<"histogram  "<<Form("th%i",i)<<"  entries = "<<th[i]->GetEntries()<<endl;

	}
	va_end(list);


}
