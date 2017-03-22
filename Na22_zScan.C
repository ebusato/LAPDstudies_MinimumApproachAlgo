
TH1F* GetZDistr(TString fileName, TString histoName, int color)
{
  TFile* f = new TFile(fileName.Data(), "read");
  TTree* t = (TTree*) f->Get("tree");
  TH1F* h = new TH1F(histoName.Data(), histoName.Data(), 300, -100, 100);
  TString toPlot("Zmaa");
  toPlot += ">>";
  toPlot += histoName;
  t->Draw(toPlot);
  h->SetLineColor(color);
  h->Scale(1/h->Integral());
  h->SetMaximum(0.4);
  //h->Fit("gaus");
  return h;
}

void Na22_zScan() 
{
	TH1F* h1 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run98Mult2.root", "h1", kBlack);
	TH1F* h2 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run99Mult2.root", "h2", kRed);
	TH1F* h3 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run100Mult2.root", "h3", kBlue);
	TH1F* h4 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run101Mult2.root", "h4", kGreen+3);
	TH1F* h5 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run102Mult2.root", "h5", kYellow);
	TH1F* h6 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run103Mult2.root", "h6", kOrange);
	TH1F* h7 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run104Mult2.root", "h7", kMagenta);
	TH1F* h8 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run105Mult2.root", "h8", kBlue);
	h1->Draw();
	h2->Draw("same");
	h3->Draw("same");
	h4->Draw("same");
	h5->Draw("same");
	h6->Draw("same");
	h7->Draw("same");
	h8->Draw("same");
}