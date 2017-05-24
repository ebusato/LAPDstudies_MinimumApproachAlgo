
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
   t->Draw(toPlot, "NoLORs == 1");
  h->SetLineColor(color);
  h->SetFillColor(color);
  h->SetFillStyle(3002);
//   h->SetMaximum(2000);
  //h->Fit("gaus");
  h->GetXaxis()->SetRangeUser(xmin,xmax);
  h->GetYaxis()->SetRangeUser(0, h->GetMaximum());
  h->GetXaxis()->SetTitle("z_{MAR} [cm]");
  h->GetYaxis()->SetTitle("Entries (a.u.)");

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
	g->Draw("ap");
	g->GetXaxis()->SetTitle("z_{ source} - z_{ source}^{0} [mm]");
	g->GetYaxis()->SetTitle("mode[z_{ reco}] - mode[z_{ reco}^{0}] [mm]");
	g->GetXaxis()->SetTitleSize(0.06);
	g->GetYaxis()->SetTitleSize(0.06);
	g->GetXaxis()->SetTitleOffset(1.25);
	g->GetYaxis()->SetTitleOffset(1.1);
	g->GetXaxis()->SetLabelSize(0.06);
	g->GetYaxis()->SetLabelSize(0.06);
	g->GetXaxis()->SetNdivisions(10);
	g->GetYaxis()->SetNdivisions(10);
	TF1* f = new TF1("f", "x", -20, 40);
	f->Draw("same");
// 	g->Draw("apsame");
	
	
	PutText(0.27, 0.75, kBlack, "LAPD");
	PutText(0.27, 0.67, kBlack, "^{22}Na (14.4 kBq)");
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
	h->GetXaxis()->SetTitleSize(0.06);
	h->GetYaxis()->SetTitleSize(0.06);
	h->GetXaxis()->SetTitleOffset(1.25);
	h->GetYaxis()->SetTitleOffset(1.1);
	h->GetXaxis()->SetLabelSize(0.06);
	h->GetYaxis()->SetLabelSize(0.06);
	return h;
}

void Na22Scan() 
{
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	double xmin = -50;
	double xmax = 50;
	/*
	std::pair<TH1F*, TH1F*> h1 = GetZDistr("analysis_v2.18-calibG2/run98LOR.root", "h1", kBlack, xmin, xmax);
	std::pair<TH1F*, TH1F*> h2 = GetZDistr("analysis_v2.18-calibG2/run99LOR.root", "h2", kRed, xmin, xmax);
	std::pair<TH1F*, TH1F*> h3 = GetZDistr("analysis_v2.18-calibG2/run100LOR.root", "h3", kBlue, xmin, xmax);
	std::pair<TH1F*, TH1F*> h4 = GetZDistr("analysis_v2.18-calibG2/run101LOR.root", "h4", kGreen+3, xmin, xmax);
	std::pair<TH1F*, TH1F*> h5 = GetZDistr("analysis_v2.18-calibG2/run102LOR.root", "h5", kYellow, xmin, xmax);
	std::pair<TH1F*, TH1F*> h6 = GetZDistr("analysis_v2.18-calibG2/run103LOR.root", "h6", kOrange, xmin, xmax);
	std::pair<TH1F*, TH1F*> h7 = GetZDistr("analysis_v2.18-calibG2/run104LOR.root", "h7", kMagenta, xmin, xmax);
	std::pair<TH1F*, TH1F*> h8 = GetZDistr("analysis_v2.18-calibG2/run105LOR.root", "h8", kBlue+2, xmin, xmax);
	*/
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
	
	TCanvas* c0_ForPresentation = new TCanvas("c0_ForPresentation", "c0_ForPresentation");
	h4.first->GetYaxis()->SetRangeUser(0, h4.first->GetMaximum()*1.2);
	h4.first->Draw();
	h4.second->Draw("same");
	h4.second->Fit("gaus", "", "", -7, 7);
	gPad->SetGridx();
	gPad->SetGridy();
	PutText(0.25, 0.8, kBlack, "LAPD");
	PutText(0.25, 0.73, kBlack, "^{22}Na (14 kBq)");
	gPad->Update();
	HalfMaxCoords* hmc = FindHalfMaxCoords(h4.second);
	cout << "HalfMaxCoords= " << endl;
	hmc->Print();
		
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
	c1->SaveAs("Na22Scan_c1.png");
	
	std::vector<Data*> data;
	data.push_back(new Data(h1.second, h1.second, (13-14)*10 + 10));
	data.push_back(new Data(h2.second, h2.second, (13.5-14)*10 + 10));
	data.push_back(new Data(h3.second, h3.second, (14-14)*10 + 10));
	data.push_back(new Data(h4.second, h4.second, (14.5-14)*10 + 10));
	data.push_back(new Data(h5.second, h5.second, (15-14)*10 + 10));
	data.push_back(new Data(h6.second, h6.second, (15.5-14)*10 + 10));
	data.push_back(new Data(h7.second, h7.second, (16-14)*10 + 10));
	data.push_back(new Data(h8.second, h8.second, (16.5-14)*10 + 10));
	
	TCanvas* c2 = new TCanvas("c2", "c2");
	TH2F* h2D = MakeTH2FromTH1s(data);
	h2D->SetBarWidth(4);
	h2D->SetFillStyle(3004);
	h2D->SetFillColor(kBlue);
	h2D->SetLineColor(kBlue);
	h2D->GetYaxis()->SetTitle("z_{ target} - z_{ target}^{0} [mm]");
	h2D->GetXaxis()->SetTitle("z_{ reco} [mm]");
	h2D->GetXaxis()->SetRangeUser(-70,70);
	h2D->Draw("violiny(12000000)");
	PutText(0.22, 0.8, kBlack, "LAPD");
	PutText(0.22, 0.73, kBlack, "^{22}Na (14 kBq)");
//    h2D->Draw("colz");
	c2->SaveAs("Na22Scan_c2.png");
}
