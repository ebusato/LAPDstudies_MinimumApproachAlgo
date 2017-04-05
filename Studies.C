
#include "../RFPlotALaArnaud/RFPlotALaArnaud.C"

std::pair<TH1F*, TH1F*> GetZDistr(TString fileName, TString histoName, int color, double xmin=-100, double xmax=100)
{
  TFile* f = new TFile(fileName.Data(), "read");
  TTree* t = (TTree*) f->Get("tree");
  TH1F* h = new TH1F(histoName.Data(), histoName.Data(), 2000, -100, 100);
  TString toPlot("LORZmar");
  toPlot += ">>";
  toPlot += histoName;
//   t->Draw(toPlot, "", "", 1000);
   t->Draw(toPlot);
  h->SetLineColor(color);
  h->SetFillColor(color);
  h->SetFillStyle(3002);
  h->SetMaximum(2000);
  //h->Fit("gaus");
  h->GetXaxis()->SetRangeUser(xmin,xmax);
  h->GetXaxis()->SetTitle("z_{MAR} [cm]");
  h->GetYaxis()->SetTitle("Entries (a.u.)");
  
  	
  TH1F* hKeys = MakeKernelPDFFromTH1(h);
  hKeys->SetLineColor(color);
  
  h->Scale(1/h->Integral());
  hKeys->Scale(20*h->Integral()/hKeys->Integral());
  
  
  return std::make_pair(h, hKeys);
}

void MakePlotMaxVsRun(std::vector<std::pair<TH1F*, double> > data)
{
	TGraph* g = new TGraph(data.size());
	for(int i=0; i<data.size(); i++)
	{
		TH1F* h = data[i].first;
		g->SetPoint(i, data[i].second, h->GetBinCenter(h->GetMaximumBin()));
	}
	TCanvas* c = new TCanvas("c", "c");
	g->Draw("ap");
	g->GetXaxis()->SetTitle("z_{target} [mm]");
	g->GetYaxis()->SetTitle("z_{reconstructed} [mm]");
	g->GetXaxis()->SetNdivisions(20);
	g->GetYaxis()->SetNdivisions(20);
	TF1* f = new TF1("f", "x", -20, 40);
	f->Draw("same");
}

void Studies() 
{
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	TCanvas* c1 = new TCanvas("c1", "c1");
	std::pair<TH1F*, TH1F*> h1 = GetZDistr("analysis_v2.18-calibG2/run98LOR.root", "h1", kBlack);
	std::pair<TH1F*, TH1F*> h2 = GetZDistr("analysis_v2.18-calibG2/run99LOR.root", "h2", kRed);
	std::pair<TH1F*, TH1F*> h3 = GetZDistr("analysis_v2.18-calibG2/run100LOR.root", "h3", kBlue);
	std::pair<TH1F*, TH1F*> h4 = GetZDistr("analysis_v2.18-calibG2/run101LOR.root", "h4", kGreen+3);
	std::pair<TH1F*, TH1F*> h5 = GetZDistr("analysis_v2.18-calibG2/run102LOR.root", "h5", kYellow);
	std::pair<TH1F*, TH1F*> h6 = GetZDistr("analysis_v2.18-calibG2/run103LOR.root", "h6", kOrange);
	std::pair<TH1F*, TH1F*> h7 = GetZDistr("analysis_v2.18-calibG2/run104LOR.root", "h7", kMagenta);
	std::pair<TH1F*, TH1F*> h8 = GetZDistr("analysis_v2.18-calibG2/run105LOR.root", "h8", kBlue+2);
	h1.first->Draw();
	h2.first->Draw("same");
	h3.first->Draw("same");
	h4.first->Draw("same");
	h5.first->Draw("same");
	h6.first->Draw("same");
	h7.first->Draw("same");
	h8.first->Draw("same");

	h1.second->Draw("same");
	h2.second->Draw("same");
	h3.second->Draw("same");
	h4.second->Draw("same");
	h5.second->Draw("same");
	h6.second->Draw("same");
	h7.second->Draw("same");
	h8.second->Draw("same");
	
	gPad->SetGridx();
	gPad->SetGridy();
	PutText(0.5, 0.89, kBlack, "LAPD");
	PutText(0.5, 0.82, kBlack, "^{22}Na (16 kBq) - 5mm scan");
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
	c1->SaveAs("c1.png");
	
	std::vector<std::pair<TH1F*, double> > data;
	data.push_back(std::make_pair(h1.second, (13-14)*10));
	data.push_back(std::make_pair(h2.second, (13.5-14)*10));
	data.push_back(std::make_pair(h3.second, (14-14)*10));
	data.push_back(std::make_pair(h4.second, (14.5-14)*10));
	data.push_back(std::make_pair(h5.second, (15-14)*10));
	data.push_back(std::make_pair(h6.second, (15.5-14)*10));
	data.push_back(std::make_pair(h7.second, (16-14)*10));
	data.push_back(std::make_pair(h8.second, (16.5-14)*10));
	MakePlotMaxVsRun(data);
}