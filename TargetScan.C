#include "Utils.C"

TH1F* Draw(TTree* t, TString var, TCut cut, TString hName, int Nbins, double xmin, double xmax, int color, int linesize, bool normalize=false)
{
	TH1F* h = new TH1F(hName.Data(), hName.Data(), Nbins, xmin, xmax);
	TString temp(var);
	temp+=">>";
	temp+=hName;
	t->Draw(temp.Data(), cut);
	h->SetLineColor(color);
	h->SetLineWidth(linesize);
	if(normalize) {
		h->Scale(1/h->Integral());
	}
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

HalfMaxCoords FindHalfMaxCoords(TH1F* h)
{
   double max = Maximum(h);
   int bin1 = h->FindFirstBinAbove(max/2.);
   int bin2 = h->FindLastBinAbove(max/2.);
   HalfMaxCoords coords;
   coords.m_low = h->GetBinCenter(bin1);
   coords.m_high = h->GetBinCenter(bin2);
   return coords;
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
	
	TCut cutTimes("T30[LORIdx1] > 20 && T30[LORIdx1] < 50 && T30[LORIdx2] > 20 && T30[LORIdx2] < 50 && LORRmar < 25");
	TCut cutSpillOut("abs(LORTMean - LORTRF - 7) > 5");
	TCut cut = cutTimes && cutSpillOut;
	
// 	TCut cut0 = "Evt > 2000 && Evt < 60000";
// 	TCut cut1 = "Evt > 2000 && Evt < 60000";
	
	TCut cut0 = "NoLORs == 1 && Evt > 2000 && Evt < 60000";
	TCut cut1 = "NoLORs == 1 && Evt > 2000 && Evt < 60000";
	
	TCanvas* c0 = new TCanvas("c0", "c0");
	c0->Divide(2,2);
	c0->cd(1);
	t0->Draw("RateLvsL3 : Evt");
	c0->cd(2);
	t1->Draw("RateLvsL3 : Evt");
	c0->cd(3);
	t0->Draw("RateLvsL3 : Evt", cut0);
	c0->cd(4);
	t1->Draw("RateLvsL3 : Evt", cut1);
	
	
	TCanvas* c1 = new TCanvas("c1", "c1");
	c1->Divide(2,1);
	c1->cd(1);
	TH2F* hArnaud_0 = new TH2F("hArnaud_0", "hArnaud_0", 100, 0, 40, 200, 0, 1000);
	t0->Draw("E[LORIdx1] : LORTMean - LORTRF>>hArnaud_0",  cut0 && cutTimes, "colz");
	t0->Draw("E[LORIdx2] : LORTMean - LORTRF>>+hArnaud_0",  cut0 && cutTimes, "colz");
	hArnaud_0->Draw("colz");
	c1->cd(2);
	TH2F* hArnaud_1 = new TH2F("hArnaud_1", "hArnaud_1", 100, 0, 40, 200, 0, 1000);
	t1->Draw("E[LORIdx1] : LORTMean - LORTRF>>hArnaud_1",  cut1 && cutTimes, "colz");
	t1->Draw("E[LORIdx2] : LORTMean - LORTRF>>+hArnaud_1",  cut1 && cutTimes, "colz");
	hArnaud_1->Draw("colz");
	
	TCanvas* c2 = new TCanvas("c2", "c2");
	TH1F* hETemp_0 = Draw(t0, "E[LORIdx1]", cut0 && cut, "hE_01", 100, 0, 1000, kRed, 1);
	TH1F* hE_0 = Draw(t0, "E[LORIdx2]", cut0 && cut, "hE_02", 100, 0, 1000, kRed, 1);
	hE_0->Add(hETemp_0);
	TH1F* hETemp_1 = Draw(t1, "E[LORIdx1]", cut1 && cut, "hE_11", 100, 0, 1000, kBlue, 1);
	TH1F* hE_1 = Draw(t1, "E[LORIdx2]", cut1 && cut, "hE_12", 100, 0, 1000, kBlue, 1);
	hE_1->Add(hETemp_1);
	hE_0->Draw();
	hE_1->Draw("same");
	
	TCanvas* c3 = new TCanvas("c3", "c3");
	TH1F* hZmar_0 = Draw(t0, "LORZmar", cut0 && cut, "hZmar", 2000, -100, 100, kRed, 4);
	TH1F* hZmar_1 = Draw(t1, "LORZmar", cut1 && cut, "hZmar", 2000, -100, 100, kGreen+2, 1);
	TH1F* hKeys_0 = MakeKernelPDFFromTH1(hZmar_0, kMagenta);
	TH1F* hKeys_1 = MakeKernelPDFFromTH1(hZmar_1, kBlue);
	hZmar_0->Scale(1/hZmar_0->Integral());
	hZmar_0->Draw();
	hZmar_1->Scale(1/hZmar_1->Integral());
	hZmar_1->Draw("same");
	
	hKeys_0->Scale(hZmar_0->GetMaximum()/hKeys_0->GetMaximum());
	hKeys_0->GetYaxis()->SetRangeUser(0, hKeys_0->GetMaximum()*1.2);
	hKeys_0->GetXaxis()->SetRangeUser(-50, 30);
	hKeys_0->Draw("same");
	hKeys_1->Scale(Maximum(hKeys_0)/Maximum(hKeys_1));
	hKeys_1->GetXaxis()->SetRangeUser(-50, 30);
	hKeys_1->Draw("same");
	
	
	TCanvas* c4 = new TCanvas("c4", "c4");
	gPad->SetGridx(1);
	gPad->SetGridy(1);
	hKeys_0->Draw();
	hKeys_1->Draw("same");
	HalfMaxCoords coords_0 = FindHalfMaxCoords(hKeys_0);
	coords_0.Print();
	HalfMaxCoords coords_1 = FindHalfMaxCoords(hKeys_1);
	coords_1.Print();
	cout << "Delta z = " << coords_0.m_high - coords_1.m_high << " mm " << endl;
	
	cout << "maximum = " << Maximum(hKeys_0) << "  " << Maximum(hKeys_1) << endl;
	
	TArrow* arr = new TArrow(coords_1.m_high, Maximum(hKeys_1)/2., coords_0.m_high, Maximum(hKeys_0)/2., 0.015, "<|-|>");
	arr->SetLineColor(kBlack);
	arr->SetFillColor(kBlack);
	arr->SetAngle(48);
	arr->Draw();
	TLatex l;
	l.SetTextColor(kBlack);
	l.SetTextSize(0.05);
	l.DrawLatex((coords_0.m_high + coords_1.m_high)/2.+5, Maximum(hKeys_1)/2.+0., Form("#Delta z = %.1f mm", coords_0.m_high - coords_1.m_high));
}