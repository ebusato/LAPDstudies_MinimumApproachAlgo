
#include "Utils.C"

std::pair<TH1F*, TH1F*> GetZDistr(TString fileName, TString histoName, int color, double xmin=-100, double xmax=100)
{
  TFile* f = new TFile(fileName.Data(), "read");
  TTree* t = (TTree*) f->Get("tree");
  TH1F* h = new TH1F(histoName.Data(), histoName.Data(), 2000, -100, 100);
  TString toPlot("LORZmar");
  toPlot += ">>";
  toPlot += histoName;
//   t->Draw(toPlot, "NoLORs == 1", "", 3000);
   t->Draw(toPlot, "NoLORs == 1 && LORRmar < 25");
  h->SetLineColor(color);
  h->SetFillColor(color);
  h->SetFillStyle(3004);
//   h->SetMaximum(2000);
  //h->Fit("gaus");
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetXaxis()->SetTitleOffset(1.25);
  h->GetYaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetLabelSize(0.05);
  //h->GetXaxis()->SetRangeUser(xmin,xmax);
  h->GetXaxis()->SetRangeUser(-42,42);
  h->GetYaxis()->SetRangeUser(0, h->GetMaximum());
  
  h->GetXaxis()->SetTitle("z [cm]");
  h->GetYaxis()->SetTitle("Entries [a.u.]");

  TH1F* hKeys = MakeKernelPDFFromTH1(h, color, 1.2);
  
//   h->Scale(1/h->Integral());
  hKeys->Scale(h->GetMaximum()/hKeys->GetMaximum());
  
  
  return std::make_pair(h, hKeys);
}

class Data {
public:
	Data(TH1F* h, TH1F* h0, double z);
	
	TH1F* m_h;
	TH1F* m_h0;
	double m_z;
};

Data::Data(TH1F* h, TH1F* h0, double z) : m_h(h), m_h0(h0), m_z(z)
{}

void MakePlotMaxVsRun(std::vector<Data*> data)
{
	TGraph* g = new TGraph(data.size());
	for(int i=0; i<data.size(); i++)
	{
		TH1F* h = data[i]->m_h;
		TH1F* h0 = data[i]->m_h0;
		g->SetPoint(i, data[i]->m_z, h->GetBinCenter(h->GetMaximumBin()) - h0->GetBinCenter(h0->GetMaximumBin()));
	}
	g->SetMarkerSize(1.5);
	//g->SetMarkerStyle(4);
	g->Draw("ap");
	g->GetYaxis()->SetRangeUser(0,60);
	//g->GetXaxis()->SetRangeUser(0,50);
	g->GetXaxis()->SetTitle("z_{ source} - z_{ source}^{0} [mm]");
	g->GetYaxis()->SetTitle("mode[z] - mode[z^{0}] [mm]");
	g->GetXaxis()->SetTitleSize(0.05);
	g->GetYaxis()->SetTitleSize(0.05);
	g->GetXaxis()->SetTitleOffset(1.25);
	g->GetYaxis()->SetTitleOffset(1.5);
	g->GetXaxis()->SetLabelSize(0.05);
	g->GetYaxis()->SetLabelSize(0.05);
	g->GetXaxis()->SetNdivisions(10);
	g->GetYaxis()->SetNdivisions(10);
	g->GetXaxis()->SetTickLength(0.02);
	g->GetYaxis()->SetTickLength(0.02);
	TF1* f = new TF1("f", "x", -20, 40);
	//f->Draw("same");
// 	g->Draw("apsame");
	const Int_t n = 5;
	double err = 1;
	Double_t x[n]  = {0, 5, 10, 20, 38};
	Double_t y[n]  = {0, 5, 10, 20, 38};
// 	Double_t y[n]  = {0, 0, 0, 0, 0};
	Double_t ex[n] = {0, 0, 0, 0, 0};
	Double_t ey[n] = {err, err, err, err, err};
	TGraphErrors* gr = new TGraphErrors(n,x,y,ex,ey);	
	gr->SetFillStyle(3001);
	//gr->SetLineStyle(2);
	gr->SetFillColor(15);
	gr->SetLineColor(kBlack);
	gr->Draw("C3");
	g->Draw("p");
	//PutText(0.27, 0.75, kBlack, "LAPD");
	//PutText(0.27, 0.67, kBlack, "^{22}Na (14.4 kBq)");
	PutText(0.6160458,0.7813163, kBlack, "LAPD");
	PutText(0.6174785,0.7048832, kBlack, "^{22}Na (14.4 kBq)");

	//TLegend* leg2 = new TLegend(0.5,0.2908705,0.8508772,0.4097665);
	TLegend* leg2 = new TLegend(0.5630372,0.2292994,0.9126074,0.3481953);
	leg2->SetBorderSize(0);
	leg2->SetFillStyle(0);
	leg2->AddEntry(g, "Data", "p");
	leg2->AddEntry(gr, "Expectation #pm 1 mm", "lf");
	leg2->Draw("same");
}

TH2F* MakeTH2FromTH1s(std::vector<Data*> data)
{
	int nBinsExcess = 3;
	TH2F* h = new TH2F("h", "h", data[0]->m_h->GetNbinsX(), data[0]->m_h->GetXaxis()->GetXmin(), data[0]->m_h->GetXaxis()->GetXmax(), data.size()+nBinsExcess, data[0]->m_z-2.5, 
data[data.size()-1]->m_z+2.5+5*nBinsExcess);
// 	TH2F* h = new TH2F("h", "h", data[0]->m_h->GetNbinsX(), data[0]->m_h->GetXaxis()->GetXmin(), data[0]->m_h->GetXaxis()->GetXmax(), 8, -2.5, 37.5);
	for(int i=0; i<data.size(); i++)
	{
		for(int j=0; j<data[0]->m_h->GetNbinsX(); j++) {
			h->Fill(data[i]->m_h->GetXaxis()->GetBinCenter(j), data[i]->m_z, data[i]->m_h->GetBinContent(j));
// 			for(int k=0; k<data[i]->m_h->GetBinContent(j); k++) {
// 				h->Fill(data[i]->m_h->GetXaxis()->GetBinCenter(j), data[i]->m_z);
// 			}
		}
	}
	h->GetXaxis()->SetTitleSize(0.08);
	h->GetYaxis()->SetTitleSize(0.09);
	h->GetXaxis()->SetTitleOffset(0.93);
	h->GetYaxis()->SetTitleOffset(0.82);
	h->GetXaxis()->SetLabelSize(0.07);
	h->GetYaxis()->SetLabelSize(0.07);
	return h;
}

void Na22Scan() 
{
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	double xmin = -50;
	double xmax = 50;
	
	std::pair<TH1F*, TH1F*> h1 = GetZDistr("analysis_v3.2-calibG2/run98LOR.root", "h1", kBlack, xmin, xmax);
	std::pair<TH1F*, TH1F*> h2 = GetZDistr("analysis_v3.2-calibG2/run99LOR.root", "h2", kRed, xmin, xmax);
	std::pair<TH1F*, TH1F*> h3 = GetZDistr("analysis_v3.2-calibG2/run100LOR.root", "h3", kBlue, xmin, xmax);
	std::pair<TH1F*, TH1F*> h4 = GetZDistr("analysis_v3.2-calibG2/run101LOR.root", "h4", kGreen+3, xmin, xmax);
	std::pair<TH1F*, TH1F*> h5 = GetZDistr("analysis_v3.2-calibG2/run102LOR.root", "h5", kYellow, xmin, xmax);
	std::pair<TH1F*, TH1F*> h6 = GetZDistr("analysis_v3.2-calibG2/run103LOR.root", "h6", kOrange, xmin, xmax);
	std::pair<TH1F*, TH1F*> h7 = GetZDistr("analysis_v3.2-calibG2/run104LOR.root", "h7", kMagenta, xmin, xmax);
	std::pair<TH1F*, TH1F*> h8 = GetZDistr("analysis_v3.2-calibG2/run105LOR.root", "h8", kBlue+2, xmin, xmax);
		
	TCanvas* c0 = new TCanvas("c0", "c0");
	c0->Divide(4,2);
	c0->cd(1);
	h1.first->Draw();
	h1.second->Draw("same");
	c0->cd(2);
	h2.first->Draw();
	h2.second->Draw("same");
	c0->cd(3);
	h3.first->Draw();
	h3.second->Draw("same");
	c0->cd(4);
	h4.first->Draw();
	h4.second->Draw("same");
	c0->cd(5);
	h5.first->Draw();
	h5.second->Draw("same");
	c0->cd(6);
	h6.first->Draw();
	h6.second->Draw("same");
	c0->cd(7);
	h7.first->Draw();
	h7.second->Draw("same");
	c0->cd(8);
	h8.first->Draw();
	h8.second->Draw("same");
		
	/*
	TLegend* leg = new TLegend(0.7,0.3,0.9,0.75);
	leg->SetBorderSize(0);
	leg->AddEntry(h1.first, "z = 13 cm", "l");
	leg->AddEntry(h2.first, "z = 13.5 cm", "l");
	leg->AddEntry(h3.first, "z = 14 cm", "l");
	leg->AddEntry(h4.first, "z = 14.5 cm", "l");
	leg->AddEntry(h5.first, "z = 15 cm", "l");
	leg->AddEntry(h6.first, "z = 15.5 cm", "l");
	leg->AddEntry(h7.first, "z = 16 cm", "l");
	leg->AddEntry(h8.first, "z = 16.5 cm", "l");
	leg->Draw();
	*/
	c0->SaveAs("Na22Scan_c0.png");
	

	TCanvas* c0_ForPresentation = new TCanvas("c0_ForPresentation", "c0_ForPresentation");
	h4.first->GetYaxis()->SetRangeUser(0, h4.first->GetMaximum()*1.1);
	h4.first->SetLineColor(kBlack);
	h4.first->SetFillColor(kBlack);
	h4.first->SetLineWidth(2);
	h4.first->Draw();
	h4.second->SetLineColor(15);
	h4.second->SetFillColor(15);
	h4.second->Draw("same");
	h4.first->Draw("same");
	//h4.second->Fit("gaus", "", "", -7, 7);
	gPad->SetGridx();
	gPad->SetGridy();
	PutText(0.21,0.71, kBlack, "LAPD");
	PutText(0.21,0.64, kBlack, "^{22}Na (14.4 kBq)");
	gPad->Update();
	HalfMaxCoords* hmc = FindHalfMaxCoords(h4.second);
	cout << "HalfMaxCoords= " << endl;
	hmc->Print();
	h4.first->GetXaxis()->SetRangeUser(-45,60);
	TLegend* leg2 = new TLegend(0.5515759,0.6231423,0.8825215,0.7526539);
	leg2->SetBorderSize(1);
	leg2->AddEntry(h4.first, "MA algorithm profile", "l");
	leg2->AddEntry(h4.second, "Kernel profile", "f");
	leg2->Draw();
	c0_ForPresentation->Update();
	c0_ForPresentation->SaveAs("Na22Scan_c0_ForPresentation.png");
	
	// Make this calculation here

	std::vector<Data*> data;
	data.push_back(new Data(h1.second, h1.second, (13-14)*10 + 10));
	data.push_back(new Data(h2.second, h2.second, (13.5-14)*10 + 10));
	data.push_back(new Data(h3.second, h3.second, (14-14)*10 + 10));
	data.push_back(new Data(h4.second, h4.second, (14.5-14)*10 + 10));
	data.push_back(new Data(h5.second, h5.second, (15-14)*10 + 10));
	data.push_back(new Data(h6.second, h6.second, (15.5-14)*10 + 10));
	data.push_back(new Data(h7.second, h7.second, (16-14)*10 + 10));
	data.push_back(new Data(h8.second, h8.second, (16.5-14)*10 + 10));

	TH2F* h2D = MakeTH2FromTH1s(data);
	h2D->SetBarWidth(5.5);
	//h2D->SetFillStyle(3004);
	h2D->SetFillStyle(3002);
	h2D->SetLineColor(kBlack);
	h2D->SetFillColor(kBlack);
	h2D->GetYaxis()->SetTitle("z_{ source} - z_{ source}^{0} [mm]");
	h2D->GetXaxis()->SetTitle("z [mm]");
	h2D->GetXaxis()->SetRangeUser(-70,70);

	TCanvas* c1 = new TCanvas("c1", "c1");
	std::vector<Data*> dataKeys;
	dataKeys.push_back(new Data(h1.second, h1.second, (13-14)*10 + 10));
	dataKeys.push_back(new Data(h2.second, h1.second, (13.5-14)*10 + 10));
	dataKeys.push_back(new Data(h3.second, h1.second, (14-14)*10 + 10));
	dataKeys.push_back(new Data(h4.second, h1.second, (14.5-14)*10 + 10));
	dataKeys.push_back(new Data(h5.second, h1.second, (15-14)*10 + 10));
	dataKeys.push_back(new Data(h6.second, h1.second, (15.5-14)*10 + 10));
	dataKeys.push_back(new Data(h7.second, h1.second, (16-14)*10 + 10));
	dataKeys.push_back(new Data(h8.second, h1.second, (16.5-14)*10 + 10));
	MakePlotMaxVsRun(dataKeys);

	TPad* subpad = new TPad("subpad", "", 0.18,0.45,0.62,0.9);
	subpad->SetFillStyle(4000); 
	subpad->Draw();
	subpad->cd();
	h2D->GetXaxis()->SetRangeUser(-40, 40);
	h2D->GetYaxis()->SetRangeUser(0,200);
	h2D->GetXaxis()->SetTickLength(0.02);
	h2D->GetYaxis()->SetTickLength(0.02);
	h2D->Draw("violiny(12000000)");

	c1->SaveAs("Na22Scan_c1.png");
	c1->SaveAs("Na22Scan_c1.pdf");
	

	TCanvas* c2 = new TCanvas("c2", "c2");
	h2D->Draw("violiny(12000000)");
	PutText(0.22, 0.8, kBlack, "LAPD");
	PutText(0.22, 0.73, kBlack, "^{22}Na (14 kBq)");
//    h2D->Draw("colz");
	c2->SaveAs("Na22Scan_c2.png");
	
}
