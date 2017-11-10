#include "Utils.C"

void TargetWithHole()
{
// 	TFile* f00 = new TFile("analysis_v3.2-calibG2/run91LOR.root", "read"); // z = 14 cm, no holes
// 	TFile* f00 = new TFile("analysis_v3.3-calibK1/run118LOR.root", "read"); // z = 14 cm, no holes  <- default
	TFile* f0 = new TFile("analysis_v3.3-calibK1/run166LOR.root", "read"); // z = 14 cm, no holes
	
	TFile* f1 = new TFile("analysis_v3.3-calibK1/run164LOR.root", "read"); // z = 14 cm, hole depth = 1 mm
	TFile* f2 = new TFile("analysis_v3.3-calibK1/run162LOR.root", "read"); // z = 14 cm, hole depth = 3 mm
	TFile* f3 = new TFile("analysis_v3.3-calibK1/run158LOR.root", "read"); // z = 14 cm, hole depth = 5 mm
	TFile* f4 = new TFile("analysis_v3.3-calibK1/run168LOR.root", "read"); // z = 14 cm, hole depth = 11 mm
	
// 	TTree* t00 = (TTree*) f00->Get("tree");
	TTree* t0 = (TTree*) f0->Get("tree");
	TTree* t1 = (TTree*) f1->Get("tree");
	TTree* t2 = (TTree*) f2->Get("tree");
	TTree* t3 = (TTree*) f3->Get("tree");
	TTree* t4 = (TTree*) f4->Get("tree");
	
	/*
	int evtMax = 40000;
// 	TreeAnalysis* tAna_00 = new TreeAnalysis(t00, Form("Evt > 1700 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kBlack, 140);
	// run118 has for an unknown reason a downward gain drift (511 keV peak at around 400 keV, hence the fancy energy cuts below
// 	TreeAnalysis* tAna_00 = new TreeAnalysis(t00, Form("Evt > 3500 && Evt < %d", evtMax), "E[LORIdx1] > 300 && E[LORIdx1] < 500 && E[LORIdx2] > 300 && E[LORIdx2] < 500", kBlack, 140); // <-default
	TreeAnalysis* tAna_0 = new TreeAnalysis(t0, Form("Evt > 900 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kRed, 140);
	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, Form("Evt > 900 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kGreen+2, 140);
	TreeAnalysis* tAna_2 = new TreeAnalysis(t2, Form("Evt > 1400 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kBlue, 140);
	TreeAnalysis* tAna_3 = new TreeAnalysis(t3, Form("Evt > 1200 && Evt < %d", evtMax), "E[LORIdx1] > 400 && E[LORIdx1] < 550 && E[LORIdx2] > 400 && E[LORIdx2] < 550", kMagenta, 140);  
	TreeAnalysis* tAna_4 = new TreeAnalysis(t4, Form("Evt > 1000 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kYellow+1, 140);
	*/
	double time = 29.*60.; // time in seconds
// 	TreeAnalysis* tAna_00 = new TreeAnalysis(t00, Form("Evt > 1700 && Evt < %d", evtMax), "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kBlack, 140);
	// run118 has for an unknown reason a downward gain drift (511 keV peak at around 400 keV, hence the fancy energy cuts below
// 	TreeAnalysis* tAna_00 = new TreeAnalysis(t00, Form("Evt > 3500 && Evt < %d", evtMax), "E[LORIdx1] > 300 && E[LORIdx1] < 500 && E[LORIdx2] > 300 && E[LORIdx2] < 500", kBlack, 140); // <-default
	TreeAnalysis* tAna_0 = new TreeAnalysis(t0, 900, time, "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kRed, 140);
	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, 900, time, "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kGreen+2, 140);
	TreeAnalysis* tAna_2 = new TreeAnalysis(t2, 1400, time, "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kYellow+1, 140);
	TreeAnalysis* tAna_3 = new TreeAnalysis(t3, 1200, time, "E[LORIdx1] > 400 && E[LORIdx1] < 550 && E[LORIdx2] > 400 && E[LORIdx2] < 550", kBlue, 140);  
	TreeAnalysis* tAna_4 = new TreeAnalysis(t4, 1000, time, "E[LORIdx1] > 420 && E[LORIdx1] < 600 && E[LORIdx2] > 420 && E[LORIdx2] < 600", kMagenta, 140);
	
	
	std::vector<TreeAnalysis*> vec;
	
// 	vec.push_back(tAna_00);
	vec.push_back(tAna_0);
	vec.push_back(tAna_1);
	vec.push_back(tAna_2);
	vec.push_back(tAna_3);
	vec.push_back(tAna_4);
	
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
		TH1F* hZmar = Draw(vec[i]->m_tree, "LORZmar", vec[i]->m_cutEnergy && vec[i]->m_cutLOR && vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutBeamPause, hName.Data(), 2000, -100, 
100, vec[i]->m_color, 3);
// 		TH1F* hKeys = MakeKernelPDFFromTH1(hZmar, vec[i]->m_color, 2.4);
		TH1F* hKeys = MakeKernelPDFFromTH1(hZmar, vec[i]->m_color, 2);
		hZmar->Scale(1/hZmar->Integral());
		hZmar->Draw();
		hKeys->Scale(hZmar->GetMaximum()/hKeys->GetMaximum());
// 		hKeys->GetYaxis()->SetRangeUser(0, hKeys->GetMaximum()*1.25);
		hKeys->GetYaxis()->SetRangeUser(0, hKeys->GetMaximum()*1.6);
		hKeys->GetXaxis()->SetRangeUser(-45, 45);
		hKeys->Draw("same");
		TF1* hFit = FitKeysSideBand(hKeys, hKeys->GetName(), -90,-40,20,90);
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
	double yShift = 0.017;
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
		if(i == 0) {
			locY = yStart - yShift;
		}
	  

	  //	  double locY = yStart - (5-i)*yShift;
		TLine* line = new TLine(vec[i]->m_coords->m_Xhigh, max0/2., vec[i]->m_coords->m_Xhigh, locY);
		//line->SetLineStyle(kDashed);
		line->SetLineStyle(kDotted);
		line->SetLineColor(12);
		line->Draw();
		TEllipse* ell = new TEllipse(vec[i]->m_coords->m_Xhigh, max0/2., 0.5, 0.002);
		ell->SetFillStyle(1);
		//ell->SetFillColor(12);
		//ell->SetLineColor(12);
		ell->SetFillColor(kBlack);
		ell->SetLineColor(kBlack);
		ell->Draw();
		if(i>0) {
			TArrow* arr = new TArrow(vec[i]->m_coords->m_Xhigh, locY, vec[0]->m_coords->m_Xhigh, locY, 0.015, "<->");
// 			TArrow* arr = new TArrow(vec[i]->m_coords->m_Xhigh, vec[i]->m_coords->m_Yhigh, vec[i-1]->m_coords->m_Xhigh, vec[i-1]->m_coords->m_Yhigh, 0.015, "<|-|>");
			arr->SetLineColor(12);
			arr->SetLineColor(kBlack);
			arr->SetFillColor(12);
			arr->SetAngle(170);
			arr->SetArrowSize(0.0008);
			arr->Draw();
			TLatex l;
			//l.SetTextColor(12);
			l.SetTextColor(kBlack);
			l.SetTextSize(0.045);
// 			l.DrawLatex((vec[i]->m_coords->m_Xhigh + vec[i-1]->m_coords->m_Xhigh)/2.+7, max0/2.+0.02-i*0.009, Form("#Delta z_{MAR} = %.1f mm", -1*(vec[i]->m_coords->m_Xhigh - 
//vec[i-1]->m_coords->m_Xhigh)));
			l.DrawLatex(vec[i]->m_coords->m_Xhigh+0.5, locY-0.004, Form("%.1f mm", (vec[i]->m_coords->m_Xhigh-vec[0]->m_coords->m_Xhigh)));
		}
	}
	PutText(0.2, 0.81, kBlack, "LAPD", 0.046);
	PutText(0.2, 0.75, kBlack, "Protons 65 MeV, I = 5 nA ", 0.046);
	PutText(0.2, 0.69, kBlack, "PMMA targets (5#times5#times5 cm^{3})", 0.046);
	gPad->SetGridx(1);
	gPad->SetGridy(1);
	TLegend* leg = new TLegend(0.6618911,0.3269639,0.9183381,0.5923567);
	leg->SetBorderSize(0);
	leg->AddEntry(vec[0]->m_hKeys, "homogeneous", "l");
	leg->AddEntry(vec[1]->m_hKeys, "1 mm air cavity", "l");
	leg->AddEntry(vec[2]->m_hKeys, "3 mm air cavity", "l");
	leg->AddEntry(vec[3]->m_hKeys, "5 mm air cavity", "l");
	leg->AddEntry(vec[4]->m_hKeys, "11 mm air cavity", "l");
	leg->Draw();
	
	c4->SaveAs("TargetWithHole_c4.png");

	TCanvas* c5 = new TCanvas("c5", "c5");
	vec[0]->m_hKeys->Draw();
	vec[3]->m_hKeys->Draw("same");
	PutText(0.2, 0.81, kBlack, "LAPD", 0.046);
	PutText(0.2, 0.75, kBlack, "Protons 65 MeV, I = 5 nA ", 0.046);
	PutText(0.2, 0.69, kBlack, "Targets: PMMA 5 #times 5 cm", 0.046);
	TLegend* leg2 = new TLegend(0.5662651,0.4883227,0.9036145,0.6178344);
	leg2->SetBorderSize(0);
	leg2->AddEntry(vec[0]->m_hKeys, "homogeneous", "l");
	leg2->AddEntry(vec[3]->m_hKeys, "5 mm air cavity", "l");
	leg2->Draw();
	c5->SaveAs("TargetWithHole_c5.png");
}
