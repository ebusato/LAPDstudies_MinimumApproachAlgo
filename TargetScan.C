#include "Utils.C"

TH1F* Draw(TTree* t, TString var, TCut cut, TString hName, int Nbins, double xmin, double xmax, int color, int linesize)
{
	TH1F* h = new TH1F(hName.Data(), hName.Data(), Nbins, xmin, xmax);
	TString temp(var);
	temp+=">>";
	temp+=hName;
	t->Draw(temp.Data(), cut);
	h->SetLineColor(color);
	h->SetMarkerColor(color);
	h->SetLineWidth(linesize);
	return h;
}

  //RooDataSet* data = new RooDataSet("data","data",RooArgSet(x));
  //x=4;
  //data->add(RooArgSet(x));


class HalfMaxCoords {
public:
	void Print();
	
	double m_low;
	double m_high;
};
  
void HalfMaxCoords::Print()
{
	cout << "m_low = " << m_low << endl;
	cout << "m_high = " << m_high << endl;
}

double Maximum(TH1F* h)
{
	double max = -1;
	for(int i=0; i<h->GetNbinsX(); i++)
	{
		if(h->GetBinContent(i) > max) {
			max = h->GetBinContent(i);
		}
	}
	return max;
}

HalfMaxCoords* FindHalfMaxCoords(TH1F* h)
{
   double max = Maximum(h);
   int bin1 = h->FindFirstBinAbove(max/2.);
   int bin2 = h->FindLastBinAbove(max/2.);
   HalfMaxCoords* coords = new HalfMaxCoords();
   coords->m_low = h->GetBinCenter(bin1);
   coords->m_high = h->GetBinCenter(bin2);
   return coords;
}

class TreeAnalysis {
public:
	TreeAnalysis(TTree* t, TCut cut, int color);
	TTree* m_tree;
	TCut m_cutTimes;
	TCut m_cutLOR;
	TCut m_cutBeamPause;
	TCut m_cutEvents;
	int m_color;	
	
	TH1F* m_hKeys;
	HalfMaxCoords* m_coords;
};

TreeAnalysis::TreeAnalysis(TTree* t, TCut cutEvents, int color) : m_tree(t),
							    m_cutEvents(cutEvents),
							    m_color(color)
{
	m_cutTimes = "T30[LORIdx1] > 20 && T30[LORIdx1] < 50 && T30[LORIdx2] > 20 && T30[LORIdx2] < 50";
	m_cutLOR = "NoLORs == 1 && LORRmar < 25";
	m_cutBeamPause = "abs(LORTMean - LORTRF - 7) > 5";
}


void TargetScan()
{
	TFile* f0 = new TFile("analysis_v2.18-calibG2/run91LOR.root", "read");
	TFile* f1 = new TFile("analysis_v2.18-calibG2/run110LOR.root", "read");
// 	TFile* f1 = new TFile("analysis_v2.18-calibG2/run91LOR.root", "read");
	
// 	TFile* f0 = new TFile("analysis_v2.18-calibG2/run98LOR.root", "read");
// 	TFile* f1 = new TFile("analysis_v2.18-calibG2/run99LOR.root", "read");
	
	TTree* t0 = (TTree*) f0->Get("tree");
	TTree* t1 = (TTree*) f1->Get("tree");
	
	TreeAnalysis* tAna_0 = new TreeAnalysis(t0, "Evt > 2000 && Evt < 60000", kBlue);
	TreeAnalysis* tAna_1 = new TreeAnalysis(t1, "Evt > 2000 && Evt < 60000", kRed);
	
	std::vector<TreeAnalysis*> vec;
	vec.push_back(tAna_0);
	vec.push_back(tAna_1);
	
	TCanvas* c0 = new TCanvas("c0", "c0");
	c0->Divide(vec.size(), 2);
	for(int i=0; i<vec.size(); i++) {
		c0->cd(i+1);
		vec[i]->m_tree->Draw("RateLvsL3 : Evt");
		c0->cd(i+1+vec.size());
		vec[i]->m_tree->Draw("RateLvsL3 : Evt", vec[i]->m_cutEvents);
	}
	
	TCanvas* c1 = new TCanvas("c1", "c1");
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
	
	TCanvas* c2 = new TCanvas("c2", "c2");
	c2->Divide(vec.size(),1);
	for(int i=0; i<vec.size(); i++) {
		c2->cd(i+1);
		TString hNameTemp("hETemp");
		hNameTemp+=i;
		TString hName("hE");
		hName+=i;
		TH1F* hETemp = Draw(vec[i]->m_tree, "E[LORIdx1]", vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutBeamPause, hNameTemp.Data(), 100, 0, 1000, vec[i]->m_color, 1);
		TH1F* hE = Draw(vec[i]->m_tree, "E[LORIdx2]", vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutBeamPause, hName.Data(), 100, 0, 1000, vec[i]->m_color, 1);
		hE->Add(hETemp);
		cout << "name = " << hE->GetName() << " " << hE->GetEntries() << endl;
		hE->Draw("");
	}
	
	TCanvas* c3 = new TCanvas("c3", "c3");
	c3->Divide(vec.size(),1);
	for(int i=0; i<vec.size(); i++) {
		c3->cd(i+1);
		TString hName("hZmar");
		hName+=i;
		TH1F* hZmar = Draw(vec[i]->m_tree, "LORZmar", vec[i]->m_cutEvents && vec[i]->m_cutTimes && vec[i]->m_cutBeamPause, hName.Data(), 2000, -100, 100, vec[i]->m_color, 3);
		TH1F* hKeys = MakeKernelPDFFromTH1(hZmar, vec[i]->m_color);
		hZmar->Scale(1/hZmar->Integral());
		hZmar->Draw();
		hKeys->Scale(hZmar->GetMaximum()/hKeys->GetMaximum());
		hKeys->GetYaxis()->SetRangeUser(0, hKeys->GetMaximum()*1.25);
		hKeys->GetXaxis()->SetRangeUser(-50, 50);
		hKeys->Draw("same");
		vec[i]->m_hKeys = hKeys;
	}
	
	TCanvas* c4 = new TCanvas("c4", "c4");
	gPad->SetGridx(1);
	gPad->SetGridy(1);
	double max0 = Maximum(vec[0]->m_hKeys);
	HalfMaxCoords* coords0 = FindHalfMaxCoords(vec[0]->m_hKeys);
	vec[0]->m_coords = coords0;
	coords0->Print();
	cout << "max0 = " << max0 << endl;
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
			TArrow* arr = new TArrow(vec[i]->m_coords->m_high, max0/2., vec[i-1]->m_coords->m_high, max0/2., 0.015, "<|-|>");
			arr->SetLineColor(kBlack);
			arr->SetFillColor(kBlack);
			arr->SetAngle(48);
			arr->Draw();
			TLatex l;
			l.SetTextColor(kBlack);
			l.SetTextSize(0.05);
			l.DrawLatex((vec[i]->m_coords->m_high + vec[i-1]->m_coords->m_high)/2.+5, max0/2.+0., Form("#Delta z_{MAR} = %.1f mm", -1*(vec[i]->m_coords->m_high - 
vec[i-1]->m_coords->m_high)));
		}
	}
	PutText(0.54, 0.81, kBlack, "LAPD");
	PutText(0.54, 0.75, kBlack, "Targets: PMMA 5 #times 5 cm");
}