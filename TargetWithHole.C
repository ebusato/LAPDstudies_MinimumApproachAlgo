#include "Utils.C"

void TargetWithHole()
{
	TFile* f0 = new TFile("analysis_v3.2-calibG2/run91LOR.root", "read"); // z = 14 cm
// 	TFile* f0 = new TFile("analysis_v3.3-calibK1/run118LOR.root", "read"); // z = 14 cm
	TFile* f1 = new TFile("analysis_v3.3-calibK1/run158LOR.root", "read"); // z = 14 cm
	
	TTree* t0 = (TTree*) f0->Get("tree");
	TTree* t1 = (TTree*) f1->Get("tree");
	
	int evtMax = 40000;
	// run118 has for an unknown reason a downward gain drift (511 keV peak at around 400 keV, hence the fancy energy cuts below
	TreeAnalysis* tAna_0 = new TreeAnalysis(t0, Form("Evt > 3500 && Evt < %d", evtMax), "E[LORIdx1] > 300 && E[LORIdx1] < 570 && E[LORIdx2] > 300 && E[LORIdx2] < 570", kRed, 140);
// 	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, Form("Evt > 3500 && Evt < %d", evtMax), "E[LORIdx1] > 300 && E[LORIdx1] < 570 && E[LORIdx2] > 300 && E[LORIdx2] < 570", kGreen+2, 140);  
	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, Form("Evt > 1200 && Evt < %d", evtMax), "E[LORIdx1] > 0 && E[LORIdx1] < 1000 && E[LORIdx2] > 0 && E[LORIdx2] < 1000", kGreen+2, 140);
	
	std::vector<TreeAnalysis*> vec;
	vec.push_back(tAna_0);
	vec.push_back(tAna_1);
	
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
		TH1F* hKeys = MakeKernelPDFFromTH1(hZmar, vec[i]->m_color, 1.8);
		hZmar->Scale(1/hZmar->Integral());
		hZmar->Draw();
		hKeys->Scale(hZmar->GetMaximum()/hKeys->GetMaximum());
// 		hKeys->GetYaxis()->SetRangeUser(0, hKeys->GetMaximum()*1.25);
		hKeys->GetYaxis()->SetRangeUser(0, hKeys->GetMaximum()*1.8);
		hKeys->GetXaxis()->SetRangeUser(-40, 80);
		hKeys->Draw("same");
		TF1* hFit = FitKeysSideBand(hKeys, hKeys->GetName(), -90,-40,20,90);
		hFit->Draw("same");
		TH1F* hKeys_woBkg = Subtract(hKeys, hFit);
		vec[i]->m_hKeys = hKeys;			
		//vec[i]->m_hKeys = hKeys_woBkg;	
	}
	
	TCanvas* c4 = new TCanvas("c4", "c4", 800, 500);
	gPad->SetGridx(1);
	gPad->SetGridy(1);
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
			TLine* line = new TLine(vec[i]->m_coords->m_Xhigh, max0/2., vec[i]->m_coords->m_Xhigh, yStart);
			line->SetLineStyle(kDashed);
			line->Draw();
			TEllipse* ell = new TEllipse(vec[i]->m_coords->m_Xhigh, max0/2., 1.5, 0.005);
			ell->SetFillStyle(0);
			ell->Draw();
		} else {
			vec[i]->m_hKeys->Scale(max0/max);
			vec[i]->m_hKeys->Draw("same");
			
			HalfMaxCoords* coords = FindHalfMaxCoords(vec[i]->m_hKeys);
			coords->Print();
			vec[i]->m_coords = coords;
			cout << "maximum = " << Maximum(vec[i]->m_hKeys) << endl;
			
			double locY = yStart - i*yShift;
			if(i >= 5) {
				locY = yStart - 5*yShift;
			}
			
			TArrow* arr = new TArrow(vec[i]->m_coords->m_Xhigh, locY, vec[i-1]->m_coords->m_Xhigh, locY, 0.015, "<->");
// 			TArrow* arr = new TArrow(vec[i]->m_coords->m_Xhigh, vec[i]->m_coords->m_Yhigh, vec[i-1]->m_coords->m_Xhigh, vec[i-1]->m_coords->m_Yhigh, 0.015, "<|-|>");
			arr->SetLineColor(kBlack);
			arr->SetFillColor(kBlack);
			arr->SetAngle(120);
			arr->SetArrowSize(0.007);
			arr->Draw();
			TLatex l;
			l.SetTextColor(kBlack);
			l.SetTextSize(0.045);
// 			l.DrawLatex((vec[i]->m_coords->m_Xhigh + vec[i-1]->m_coords->m_Xhigh)/2.+7, max0/2.+0.02-i*0.009, Form("#Delta z_{MAR} = %.1f mm", -1*(vec[i]->m_coords->m_Xhigh - 
//vec[i-1]->m_coords->m_Xhigh)));
			l.DrawLatex(vec[i-1]->m_coords->m_Xhigh+1.4, locY+0.007, Form("%.1f", (vec[i]->m_coords->m_Xhigh-vec[i-1]->m_coords->m_Xhigh)));
			TLine* line = new TLine(vec[i]->m_coords->m_Xhigh, max0/2., vec[i]->m_coords->m_Xhigh, locY);
			line->SetLineStyle(kDashed);
			line->Draw();
			TEllipse* ell = new TEllipse(vec[i]->m_coords->m_Xhigh, max0/2., 1.5, 0.005);
			ell->SetFillStyle(0);
			ell->Draw();
		}
	}
	PutText(0.57, 0.81, kBlack, "LAPD");
	PutText(0.57, 0.75, kBlack, "Protons 65 MeV, I = 5 nA ");
	PutText(0.57, 0.69, kBlack, "Targets: PMMA 5 #times 5 cm");
	
	c4->SaveAs("TargetScan_c4.png");
}
