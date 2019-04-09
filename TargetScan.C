#include "Utils.C"
#include "/home/ebusato/Travail/AVIRM/avirmStyle/avirmStyle.C"


void TargetScan()
{
  SetAvirmStyle();
  /*
	TFile* f0 = new TFile("analysis_v3.2-calibG2/run110LOR.root", "read"); // z = 13.5 cm
// 	TFile* f1 = new TFile("analysis_v3.2-calibG2/run91LOR.root", "read"); // z = 14 cm
	TFile* f1 = new TFile("analysis_v3.3-calibK1/run118LOR.root", "read"); // z = 14 cm // <- default
// 	TFile* f1 = new TFile("analysis_v3.3-calibK1/run166LOR.root", "read"); 
	TFile* f2 = new TFile("analysis_v3.3-calibK1/run136LOR.root", "read"); // z = 14.5 cm
	TFile* f3 = new TFile("analysis_v3.3-calibK1/run140LOR.root", "read"); // z = 15 cm
	TFile* f4 = new TFile("analysis_v3.3-calibK1/run143LOR.root", "read"); // z = 15.5 cm
	TFile* f5 = new TFile("analysis_v3.3-calibK1/run147LOR.root", "read"); // z = 16.5 cm
	TFile* f6 = new TFile("analysis_v3.3-calibK1/run149LOR.root", "read"); // z = 17.5 cm
	TFile* f7 = new TFile("analysis_v3.3-calibK1/run151LOR.root", "read"); // z = 18.5 cm
	TFile* f8 = new TFile("analysis_v3.3-calibK1/run153LOR.root", "read"); // z = 19.5 cm
	TFile* f9 = new TFile("analysis_v3.3-calibK1/run156LOR.root", "read"); // z = 20.5 cm
	TFile* f10 = new TFile("analysis_v3.3-calibK1/run170LOR.root", "read"); // z = 22.5 cm
  */
  TFile* f0 = new TFile("~/godaq/analysis_v3.3-calibG2/run110LOR.root", "read"); // z = 13.5 cm
  TFile* f1 = new TFile("~/godaq/analysis_v3.3-calibK1/run118LOR.root", "read"); // z = 14 cm // <- default
  TFile* f2 = new TFile("~/godaq/analysis_v3.3-calibK1/run136LOR.root", "read"); // z = 14.5 cm
  TFile* f3 = new TFile("~/godaq/analysis_v3.3-calibK1/run140LOR.root", "read"); // z = 15 cm
  TFile* f4 = new TFile("~/godaq/analysis_v3.3-calibK1/run143LOR.root", "read"); // z = 15.5 cm
  TFile* f5 = new TFile("~/godaq/analysis_v3.3-calibK1/run147LOR.root", "read"); // z = 16.5 cm
  TFile* f6 = new TFile("~/godaq/analysis_v3.3-calibK1/run149LOR.root", "read"); // z = 17.5 cm
  TFile* f7 = new TFile("~/godaq/analysis_v3.3-calibK1/run151LOR.root", "read"); // z = 18.5 cm
  TFile* f8 = new TFile("~/godaq/analysis_v3.3-calibK1/run153LOR.root", "read"); // z = 19.5 cm
  TFile* f9 = new TFile("~/godaq/analysis_v3.3-calibK1/run156LOR.root", "read"); // z = 20.5 cm
  TFile* f10 = new TFile("~/godaq/analysis_v3.3-calibK1/run170LOR.root", "read"); // z = 22.5 cm
  
  
	TTree* t0 = (TTree*) f0->Get("tree");
	TTree* t1 = (TTree*) f1->Get("tree");
	TTree* t2 = (TTree*) f2->Get("tree");
	TTree* t3 = (TTree*) f3->Get("tree");
	TTree* t4 = (TTree*) f4->Get("tree");
	TTree* t5 = (TTree*) f5->Get("tree");
	TTree* t6 = (TTree*) f6->Get("tree");
	TTree* t7 = (TTree*) f7->Get("tree");
	TTree* t8 = (TTree*) f8->Get("tree");
	TTree* t9 = (TTree*) f9->Get("tree");
	TTree* t10 = (TTree*) f10->Get("tree");
	
	/*
	int evtMax = 40000;
	TreeAnalysis* tAna_0 = new TreeAnalysis(t0, Form("Evt > 2500 && Evt < %d", evtMax), "E[LORIdx1] > 400 && E[LORIdx1] < 650 && E[LORIdx2] > 400 && E[LORIdx2] < 650", kRed, 135);
	// run118 has for an unknown reason a downward gain drift (511 keV peak at around 400 keV, hence the fancy energy cuts below
	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, Form("Evt > 3500 && Evt < %d", evtMax), "E[LORIdx1] > 300 && E[LORIdx1] < 570 && E[LORIdx2] > 300 && E[LORIdx2] < 570", kGreen+2, 140); //<-default
// 	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, Form("Evt > 900 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kGreen+2, 140);
	TreeAnalysis* tAna_2 = new TreeAnalysis(t2, Form("Evt > 1500 && Evt < %d", evtMax), "E[LORIdx1] > 400 && E[LORIdx1] < 700 && E[LORIdx2] > 400 && E[LORIdx2] < 700", kBlue, 145);
	TreeAnalysis* tAna_3 = new TreeAnalysis(t3, Form("Evt > 1000 && Evt < %d", evtMax), "E[LORIdx1] > 400 && E[LORIdx1] < 700 && E[LORIdx2] > 400 && E[LORIdx2] < 700", kMagenta, 150);
	TreeAnalysis* tAna_4 = new TreeAnalysis(t4, Form("Evt > 1000 && Evt < %d", evtMax), "E[LORIdx1] > 380 && E[LORIdx1] < 700 && E[LORIdx2] > 380 && E[LORIdx2] < 700", kYellow+1, 155);
	TreeAnalysis* tAna_5 = new TreeAnalysis(t5, Form("Evt > 2600 && Evt < %d", evtMax), "E[LORIdx1] > 450 && E[LORIdx1] < 700 && E[LORIdx2] > 450 && E[LORIdx2] < 700", kOrange, 165);
	TreeAnalysis* tAna_6 = new TreeAnalysis(t6, Form("Evt > 2000 && Evt < %d", evtMax), "E[LORIdx1] > 450 && E[LORIdx1] < 700 && E[LORIdx2] > 450 && E[LORIdx2] < 700", kBlack, 175);
	TreeAnalysis* tAna_7 = new TreeAnalysis(t7, Form("Evt > 600 && Evt < %d", evtMax), "E[LORIdx1] > 450 && E[LORIdx1] < 700 && E[LORIdx2] > 450 && E[LORIdx2] < 700", kRed+1, 185);
	TreeAnalysis* tAna_8 = new TreeAnalysis(t8, Form("Evt > 1000 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 700 && E[LORIdx2] > 420 && E[LORIdx2] < 700", kGreen+3, 195);
	TreeAnalysis* tAna_9 = new TreeAnalysis(t9, Form("Evt > 1000 && Evt < %d", evtMax), "E[LORIdx1] > 350 && E[LORIdx1] < 700 && E[LORIdx2] > 350 && E[LORIdx2] < 700", kBlue+1, 205);
	TreeAnalysis* tAna_10 = new TreeAnalysis(t10, Form("Evt > 3800 && Evt < %d", evtMax), "E[LORIdx1] > 0 && E[LORIdx1] < 1000 && E[LORIdx2] > 0 && E[LORIdx2] < 1000", kMagenta+1, 225);
	*/
	
// 	double time = 28.*60.; // time in seconds
	double time = 15.*60.; // time in seconds
	//double time = 0.5*60.; // time in seconds
	TreeAnalysis* tAna_0 = new TreeAnalysis(t0, 2500, time, "E[LORIdx1] > 400 && E[LORIdx1] < 650 && E[LORIdx2] > 400 && E[LORIdx2] < 650", kRed, 135);
	// run118 has for an unknown reason a downward gain drift (511 keV peak at around 400 keV, hence the fancy energy cuts below
	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, 3500, time, "E[LORIdx1] > 300 && E[LORIdx1] < 570 && E[LORIdx2] > 300 && E[LORIdx2] < 570", kGreen+2, 140); //<-default
// 	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, 900, time, "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kGreen+2, 140);
	TreeAnalysis* tAna_2 = new TreeAnalysis(t2, 1500, time, "E[LORIdx1] > 400 && E[LORIdx1] < 700 && E[LORIdx2] > 400 && E[LORIdx2] < 700", kBlue, 145);
	TreeAnalysis* tAna_3 = new TreeAnalysis(t3, 1000, time, "E[LORIdx1] > 400 && E[LORIdx1] < 700 && E[LORIdx2] > 400 && E[LORIdx2] < 700", kMagenta, 150);
	TreeAnalysis* tAna_4 = new TreeAnalysis(t4, 1000, time, "E[LORIdx1] > 380 && E[LORIdx1] < 700 && E[LORIdx2] > 380 && E[LORIdx2] < 700", kYellow+1, 155);
	TreeAnalysis* tAna_5 = new TreeAnalysis(t5, 2600, time, "E[LORIdx1] > 450 && E[LORIdx1] < 700 && E[LORIdx2] > 450 && E[LORIdx2] < 700", kOrange, 165);
	TreeAnalysis* tAna_6 = new TreeAnalysis(t6, 2000, time, "E[LORIdx1] > 450 && E[LORIdx1] < 700 && E[LORIdx2] > 450 && E[LORIdx2] < 700", kBlack, 175);
	TreeAnalysis* tAna_7 = new TreeAnalysis(t7, 600, time, "E[LORIdx1] > 450 && E[LORIdx1] < 700 && E[LORIdx2] > 450 && E[LORIdx2] < 700", kRed+1, 185);
	TreeAnalysis* tAna_8 = new TreeAnalysis(t8, 1000, time, "E[LORIdx1] > 420 && E[LORIdx1] < 700 && E[LORIdx2] > 420 && E[LORIdx2] < 700", kGreen+3, 195);
	TreeAnalysis* tAna_9 = new TreeAnalysis(t9, 1000, time, "E[LORIdx1] > 350 && E[LORIdx1] < 700 && E[LORIdx2] > 350 && E[LORIdx2] < 700", kBlue+1, 205);
	TreeAnalysis* tAna_10 = new TreeAnalysis(t10, 3800, time, "E[LORIdx1] > 0 && E[LORIdx1] < 1000 && E[LORIdx2] > 0 && E[LORIdx2] < 1000", kMagenta+1, 225);
	
	std::vector<TreeAnalysis*> vec;
	vec.push_back(tAna_0);
	vec.push_back(tAna_1);
	vec.push_back(tAna_2);
	vec.push_back(tAna_3);
	vec.push_back(tAna_4);
	vec.push_back(tAna_5);
	vec.push_back(tAna_6);
	vec.push_back(tAna_7);
	vec.push_back(tAna_8);
	vec.push_back(tAna_9);
// 	vec.push_back(tAna_10);
	
	TCanvas* c0 = new TCanvas("c0", "c0", 1800, 300);
	c0->Divide(vec.size(), 2);
	for(int i=0; i<vec.size(); i++) {
		c0->cd(i+1);
		vec[i]->m_tree->Draw("RateLvsL3 : Evt");
		c0->cd(i+1+vec.size());
		vec[i]->m_tree->Draw("RateLvsL3 : Evt", vec[i]->m_cutEvents);
	}
	
	TCanvas* c1 = new TCanvas("c1", "c1", 1800, 300);
	c1->Divide(vec.size(),1);
	for(int i=0; i<vec.size(); i++) {
		c1->cd(i+1);
		TString hName("hArnaud");
		hName+=i;
		TH2F* hArnaud = new TH2F(hName.Data(), hName.Data(), 100, 0, 40, 200, 0, 1000);
		TString cmd1("E[LORIdx1] : LORTMean - LORTRF>>");
		TString cmd2(cmd1);
		cmd1+=hName;
		cmd2+="+";
		cmd2+=hName;
		vec[i]->m_tree->Draw(cmd1.Data(), vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutLOR, "colz");
		vec[i]->m_tree->Draw(cmd2.Data(), vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutLOR, "colz");
		hArnaud->Draw("colz");
	}
	
	TCanvas* c2 = new TCanvas("c2", "c2", 1800, 300);
	c2->Divide(vec.size(),1);
	for(int i=0; i<vec.size(); i++) {
		c2->cd(i+1);
		TString hNameTemp("hETemp");
		hNameTemp+=i;
		TString hName("hE");
		hName+=i;
		TH1F* hETemp = Draw(vec[i]->m_tree, "E[LORIdx1]", vec[i]->m_cutEnergy && vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutBeamPause, hNameTemp.Data(), 100, 0, 1000, 
vec[i]->m_color, 1);
		TH1F* hE = Draw(vec[i]->m_tree, "E[LORIdx2]", vec[i]->m_cutEnergy && vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutBeamPause, hName.Data(), 100, 0, 1000, vec[i]->m_color, 
1);
		hE->Add(hETemp);
		cout << "name = " << hE->GetName() << " " << hE->GetEntries() << endl;
		hE->Draw("");
	}
	
	TCanvas* c3 = new TCanvas("c3", "c3", 1800, 300);
	c3->Divide(vec.size(),1);
	for(int i=0; i<vec.size(); i++) {
		c3->cd(i+1);
		TString hName("hZmar");
		hName+=i;
		TH1F* hZmar = Draw(vec[i]->m_tree, "LORZmar", vec[i]->m_cutEnergy && vec[i]->m_cutLOR && vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutBeamPause, hName.Data(), 2000, -100, 100, vec[i]->m_color, 3);
		// 		TH1F* hKeys = MakeKernelPDFFromTH1(hZmar, vec[i]->m_color, 2.4);
		TH1F* hKeys = MakeKernelPDFFromTH1(hZmar, vec[i]->m_color, 1.8);
		hZmar->Scale(1/hZmar->Integral());
		hZmar->Draw("hist");
		hKeys->Scale(hZmar->GetMaximum()/hKeys->GetMaximum());
// 		hKeys->GetYaxis()->SetRangeUser(0, hKeys->GetMaximum()*1.25);
		hKeys->GetYaxis()->SetRangeUser(0, hKeys->GetMaximum()*1.95);
		hKeys->GetXaxis()->SetRangeUser(-70, 90);
		hKeys->Draw("same");
		TF1* hFit = FitKeysSideBand(hKeys, hKeys->GetName(), -90,-50,20,90);
		hFit->Draw("same");
		TH1F* hKeys_woBkg = Subtract(hKeys, hFit);
		vec[i]->m_hKeys = hKeys;			
		//vec[i]->m_hKeys = hKeys_woBkg;	
	}
	
	TCanvas* c4 = new TCanvas("c4", "c4");
// 	gPad->SetGridx(1);
// 	gPad->SetGridy(1);
	double max0 = Maximum(vec[0]->m_hKeys);
	HalfMaxCoords* coords0 = FindHalfMaxCoords(vec[0]->m_hKeys);
	vec[0]->m_coords = coords0;
	coords0->Print();
	cout << "max0 = " << max0 << endl;
	double yShift = 0.015;
	double yStart = max0*1.65;
	for(int i=0; i<vec.size(); i++) {
		double max = Maximum(vec[i]->m_hKeys);
		if(i == 0) {
			vec[i]->m_hKeys->Draw();
		} else {
			vec[i]->m_hKeys->Scale(max0/max);
			vec[i]->m_hKeys->Draw("same");
			
			HalfMaxCoords* coords = FindHalfMaxCoords(vec[i]->m_hKeys);
			coords->Print();
			vec[i]->m_coords = coords;
			cout << "maximum = " << Maximum(vec[i]->m_hKeys) << endl;
		}
	}
	for(int i=0; i<vec.size(); i++) {
		double locY = yStart - i*yShift;
		if(i==0) {
			locY = yStart - yShift;
		}
		if(i >= 5) {
			locY = yStart - 5*yShift;
		}
		/*
		TLine* line = new TLine(vec[i]->m_coords->m_Xhigh, max0/2., vec[i]->m_coords->m_Xhigh, locY);
		line->SetLineStyle(kDashed);
		line->SetLineColor(12);
		line->Draw();
		*/
		TEllipse* ell = new TEllipse(vec[i]->m_coords->m_Xhigh, max0/2., 1, 0.002);
		ell->SetFillStyle(1);
		ell->SetLineColor(12);
		ell->SetFillColor(12);
		ell->Draw();
		/*
		if(i>=1) {
			TArrow* arr = new TArrow(vec[i]->m_coords->m_Xhigh, locY, vec[i-1]->m_coords->m_Xhigh, locY, 0.015, "|-|");
// 			TArrow* arr = new TArrow(vec[i]->m_coords->m_Xhigh, vec[i]->m_coords->m_Yhigh, vec[i-1]->m_coords->m_Xhigh, vec[i-1]->m_coords->m_Yhigh, 0.015, "<|-|>");
			arr->SetLineColor(12);
			arr->SetFillColor(12);
// 			arr->SetAngle(180);
// 			arr->SetArrowSize(0.0001);
			arr->Draw();
			TLatex l;
			l.SetTextColor(12);
			l.SetTextSize(0.035);
// 			l.DrawLatex((vec[i]->m_coords->m_Xhigh + vec[i-1]->m_coords->m_Xhigh)/2.+7, max0/2.+0.02-i*0.009, Form("#Delta z_{MAR} = %.1f mm", -1*(vec[i]->m_coords->m_Xhigh - 
// vec[i-1]->m_coords->m_Xhigh)));
			l.DrawLatex(vec[i-1]->m_coords->m_Xhigh+(i>0?1:0)*1.4, locY+0.007, Form("%.1f", (vec[i]->m_coords->m_Xhigh-vec[i-1]->m_coords->m_Xhigh)));
		}
		*/
	}
	
	PutText(0.51, 0.78, kBlack, "LAPD");
	PutText(0.51, 0.72, kBlack, "Protons 65 MeV, I = 5 nA ");
	PutText(0.51, 0.66, kBlack, "PMMA targets (5#times5#times5 cm^{3})");
	gPad->SetGridx(1);
	gPad->SetGridy(1);
	/*
	TLegend* leg = new TLegend(0.1929825,0.4288747,0.3709273,0.8619958);
	leg->SetBorderSize(0);
	leg->AddEntry(vec[0]->m_hKeys, "initial position", "l");
	leg->AddEntry(vec[1]->m_hKeys, "5 mm shift", "l");
	leg->AddEntry(vec[2]->m_hKeys, "5 mm shift", "l");
	leg->AddEntry(vec[3]->m_hKeys, "5 mm shift", "l");
	leg->AddEntry(vec[4]->m_hKeys, "5 mm shift", "l");
	leg->AddEntry(vec[5]->m_hKeys, "10 mm shift", "l");
	leg->AddEntry(vec[6]->m_hKeys, "10 mm shift", "l");
	leg->AddEntry(vec[7]->m_hKeys, "10 mm shift", "l");
	leg->AddEntry(vec[8]->m_hKeys, "10 mm shift", "l");
	leg->AddEntry(vec[9]->m_hKeys, "10 mm shift", "l");
// 	leg->AddEntry(vec[10]->m_hKeys, "20 mm shift", "l");
*/
	TLegend* leg = new TLegend(0.1991404,0.4819533,0.260745,0.8407643);
	leg->SetBorderSize(0);
	leg->SetMargin(1);
	leg->SetEntrySeparation(0.01);
	leg->AddEntry(vec[0]->m_hKeys, " ", "l");
	leg->AddEntry(vec[1]->m_hKeys, " ", "l");
	leg->AddEntry(vec[2]->m_hKeys, " ", "l");
	leg->AddEntry(vec[3]->m_hKeys, " ", "l");
	leg->AddEntry(vec[4]->m_hKeys, " ", "l");
	leg->AddEntry(vec[5]->m_hKeys, " ", "l");
	leg->AddEntry(vec[6]->m_hKeys, " ", "l");
	leg->AddEntry(vec[7]->m_hKeys, " ", "l");
	leg->AddEntry(vec[8]->m_hKeys, " ", "l");
	leg->AddEntry(vec[9]->m_hKeys, " ", "l");
	leg->Draw();

	PutText(0.268, 0.81, kBlack, "initial position", 0.045);
	PutText(0.29, 0.719, kBlack, "5 mm shifts", 0.045);
	PutText(0.29, 0.56, kBlack, "10 mm shifts", 0.045);

	Double_t Graph0_fx1[4] = {
	  -50,
	  -47.13,
	  -47.13,
	  -50};
	Double_t Graph0_fy1[4] = {
	  0.225,
	  0.215,
	  0.19,
	  0.18};
	TGraph *graph = new TGraph(4,Graph0_fx1,Graph0_fy1);
	graph->SetName("Graph0");
	graph->SetTitle("Graph");
	graph->SetFillColor(1);
	graph->SetLineColor(1);
	graph->SetLineWidth(2);
	graph->SetMarkerStyle(8);
	TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,-51.19121,-44.58949);
	Graph_Graph1->SetMinimum(0.2825257);
	Graph_Graph1->SetMaximum(0.3783401);
	Graph_Graph1->SetDirectory(0);
	Graph_Graph1->SetStats(0);
	Graph_Graph1->SetLineWidth(2);
	Graph_Graph1->SetMarkerStyle(8);
	Graph_Graph1->GetXaxis()->SetNdivisions(506);
	Graph_Graph1->GetXaxis()->SetLabelFont(42);
	Graph_Graph1->GetXaxis()->SetLabelOffset(0.015);
	Graph_Graph1->GetXaxis()->SetLabelSize(0.06);
	Graph_Graph1->GetXaxis()->SetTitleSize(0.07);
	Graph_Graph1->GetXaxis()->SetTitleFont(42);
	Graph_Graph1->GetYaxis()->SetNdivisions(506);
	Graph_Graph1->GetYaxis()->SetLabelFont(42);
	Graph_Graph1->GetYaxis()->SetLabelOffset(0.015);
	Graph_Graph1->GetYaxis()->SetLabelSize(0.06);
	Graph_Graph1->GetYaxis()->SetTitleSize(0.07);
	Graph_Graph1->GetYaxis()->SetTitleOffset(1.1);
	Graph_Graph1->GetYaxis()->SetTitleFont(42);
	Graph_Graph1->GetZaxis()->SetLabelFont(42);
	Graph_Graph1->GetZaxis()->SetLabelOffset(0.015);
	Graph_Graph1->GetZaxis()->SetLabelSize(0.06);
	Graph_Graph1->GetZaxis()->SetTitleSize(0.07);
	Graph_Graph1->GetZaxis()->SetTitleOffset(1.1);
	Graph_Graph1->GetZaxis()->SetTitleFont(42);
	graph->SetHistogram(Graph_Graph1);
	graph->Draw("L");

	Double_t Graph1_fx1[4] = {
	  -50,
	  -47.13,
	  -47.13,
	  -50};
	Double_t Graph1_fy1[4] = {
	  0.175,
	  0.165,
	  0.125,
	  0.115};
	TGraph *graph1 = new TGraph(4,Graph1_fx1,Graph1_fy1);
	graph1->SetName("Graph0");
	graph1->SetTitle("Graph");
	graph1->SetFillColor(1);
	graph1->SetLineColor(1);
	graph1->SetLineWidth(2);
	graph1->SetMarkerStyle(8);

	TH1F *Graph_Graph_Graph11 = new TH1F("Graph_Graph_Graph11","Graph",100,-51.19121,-44.58949);
	Graph_Graph_Graph11->SetMinimum(0.2825257);
	Graph_Graph_Graph11->SetMaximum(0.3783401);
	Graph_Graph_Graph11->SetDirectory(0);
	Graph_Graph_Graph11->SetStats(0);
	Graph_Graph_Graph11->SetLineWidth(2);
	Graph_Graph_Graph11->SetMarkerStyle(8);
	Graph_Graph_Graph11->GetXaxis()->SetNdivisions(506);
	Graph_Graph_Graph11->GetXaxis()->SetLabelFont(42);
	Graph_Graph_Graph11->GetXaxis()->SetLabelOffset(0.015);
	Graph_Graph_Graph11->GetXaxis()->SetLabelSize(0.06);
	Graph_Graph_Graph11->GetXaxis()->SetTitleSize(0.07);
	Graph_Graph_Graph11->GetXaxis()->SetTitleFont(42);
	Graph_Graph_Graph11->GetYaxis()->SetNdivisions(506);
	Graph_Graph_Graph11->GetYaxis()->SetLabelFont(42);
	Graph_Graph_Graph11->GetYaxis()->SetLabelOffset(0.015);
	Graph_Graph_Graph11->GetYaxis()->SetLabelSize(0.06);
	Graph_Graph_Graph11->GetYaxis()->SetTitleSize(0.07);
	Graph_Graph_Graph11->GetYaxis()->SetTitleOffset(1.1);
	Graph_Graph_Graph11->GetYaxis()->SetTitleFont(42);
	Graph_Graph_Graph11->GetZaxis()->SetLabelFont(42);
	Graph_Graph_Graph11->GetZaxis()->SetLabelOffset(0.015);
	Graph_Graph_Graph11->GetZaxis()->SetLabelSize(0.06);
	Graph_Graph_Graph11->GetZaxis()->SetTitleSize(0.07);
	Graph_Graph_Graph11->GetZaxis()->SetTitleOffset(1.1);
	Graph_Graph_Graph11->GetZaxis()->SetTitleFont(42);
	graph1->SetHistogram(Graph_Graph_Graph11);
	
	graph1->Draw("l");

	TLine *line1 = new TLine(-47.58472,0.201,-45.13964,0.201);
	line1->SetLineWidth(2);
	line1->Draw();
	TLine* line2 = new TLine(-47.58472,0.145,-45.13964,0.145);
	line2->SetLineWidth(2);
	line2->Draw();

	c4->SaveAs("TargetScan_c4.png");
	c4->SaveAs("TargetScan_c4.pdf");
	
	TCanvas* c5 = new TCanvas("c5", "c5");
	gPad->SetGridx(1);
	gPad->SetGridy(1);
	TGraph* g = new TGraph(vec.size());
	for(int i=0; i<vec.size(); i++) {
		cout << vec[i]->m_coords->m_Xhigh << endl;
// 		g->SetPoint(i, vec[i]->m_zTargetSupport - vec[0]->m_zTargetSupport, vec[i]->m_coords->m_Xhigh - vec[0]->m_coords->m_Xhigh - (vec[i]->m_zTargetSupport - vec[0]->m_zTargetSupport));
		g->SetPoint(i, vec[i]->m_zTargetSupport - vec[0]->m_zTargetSupport, vec[i]->m_coords->m_Xhigh - vec[0]->m_coords->m_Xhigh);
	}
	g->SetMarkerSize(1.5);
	g->GetXaxis()->SetRangeUser(0, 80);
	g->GetYaxis()->SetRangeUser(0, 72);
	g->Draw("ap");
	g->GetXaxis()->SetTitle("z_{ target} - z_{ target}^{0} [mm]");
	g->GetYaxis()->SetTitle("z_{ fall-off} - z_{ fall-off}^{0} [mm]");
	g->GetXaxis()->SetTitleSize(0.05);
	g->GetYaxis()->SetTitleSize(0.05);
	g->GetXaxis()->SetTitleOffset(1.25);
	g->GetYaxis()->SetTitleOffset(1.5);
	g->GetXaxis()->SetLabelSize(0.05);
	g->GetYaxis()->SetLabelSize(0.05);
	g->GetXaxis()->SetNdivisions(512);
	g->GetYaxis()->SetNdivisions(512);
// 	TF1* f = new TF1("f", "x", -20, 100);
// 	f->Draw("same");
	
	const Int_t n = 5;
	double err = 2;
	Double_t x[n]  = {0, 20, 60, 70, 80};
	Double_t y[n]  = {0, 20, 60, 70, 80};
// 	Double_t y[n]  = {0, 0, 0, 0, 0};
	Double_t ex[n] = {0, 0, 0, 0, 0};
	Double_t ey[n] = {err, err, err, err, err};
	TGraphErrors* gr = new TGraphErrors(n,x,y,ex,ey);	
	gr->SetFillStyle(3001);
	gr->SetFillColor(15);
	gr->SetLineColor(kBlack);
	gr->Draw("C3");
	
	g->Draw("p");
	PutText(0.2, 0.81, kBlack, "LAPD");
	PutText(0.2, 0.75, kBlack, "Protons 65 MeV, I = 5 nA ");
	PutText(0.2, 0.69, kBlack, "PMMA targets (5#times5#times5 cm^{3})");
	
	TLegend* leg2 = new TLegend(0.5,0.2908705,0.8508772,0.4097665);
	leg2->SetBorderSize(0);
	leg2->AddEntry(g, "Data", "p");
	leg2->AddEntry(gr, "Expectation #pm 2 mm", "lf");
	leg2->Draw("same");
	
	c5->SaveAs("TargetScan_c5.png");
	c5->SaveAs("TargetScan_c5.pdf");
}
