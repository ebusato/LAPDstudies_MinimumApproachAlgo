
TH1F* GetZDistr(TString fileName, TString histoName, int color, double xmin=-30, double xmax=60)
{
  TFile* f = new TFile(fileName.Data(), "read");
  TTree* t = (TTree*) f->Get("tree");
  TH1F* h = new TH1F(histoName.Data(), histoName.Data(), 300, -100, 100);
  TString toPlot("Zmaa");
  toPlot += ">>";
  toPlot += histoName;
  t->Draw(toPlot);
  h->SetLineColor(color);
  h->SetFillColor(color);
  h->SetFillStyle(3002);
  h->Scale(1/h->Integral());
  h->SetMaximum(0.4);
  //h->Fit("gaus");
  h->GetXaxis()->SetRangeUser(xmin,xmax);
  h->GetXaxis()->SetTitle("z_{MA} [cm]");
  h->GetXaxis()->SetTitle("Entries (a.u.)");
  return h;
}

void Studies() 
{
	TCanvas* c1 = new TCanvas("c1", "c1");
	TH1F* h1 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run98Mult2.root", "h1", kBlack);
	TH1F* h2 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run99Mult2.root", "h2", kRed);
	TH1F* h3 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run100Mult2.root", "h3", kBlue);
	TH1F* h4 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run101Mult2.root", "h4", kGreen+3);
	TH1F* h5 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run102Mult2.root", "h5", kYellow);
	TH1F* h6 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run103Mult2.root", "h6", kOrange);
	TH1F* h7 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run104Mult2.root", "h7", kMagenta);
	TH1F* h8 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run105Mult2.root", "h8", kBlue+2);
	h1->Draw();
	h2->Draw("same");
	h3->Draw("same");
	h4->Draw("same");
	h5->Draw("same");
	h6->Draw("same");
	h7->Draw("same");
	h8->Draw("same");
	gPad->SetGridx();
	gPad->SetGridy();
	PutText(0.5, 0.89, kBlack, "LAPD");
	PutText(0.5, 0.82, kBlack, "^{22}Na (16 kBq) - 5mm scan");
	TLegend* leg = new TLegend(0.7,0.3,0.9,0.75);
	leg->SetBorderSize(0);
	leg->AddEntry(h1, "z = 13 cm", "l");
	leg->AddEntry(h2, "z = 13.5 cm", "l");
	leg->AddEntry(h3, "z = 14 cm", "l");
	leg->AddEntry(h4, "z = 14.5 cm", "l");
	leg->AddEntry(h5, "z = 15 cm", "l");
	leg->AddEntry(h6, "z = 15.5 cm", "l");
	leg->AddEntry(h7, "z = 16 cm", "l");
	leg->AddEntry(h8, "z = 16.5 cm", "l");
	leg->Draw();
	c1->SaveAs("c1.png");
	
	TCanvas* c2 = new TCanvas("c2", "c2");
	TH1F* h9 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run92Mult2.root", "h9", kBlack, -100, 100);
	TH1F* h10 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run112Mult2.root", "h10", kRed, -100, 100);
	h9->Draw();
	h10->Draw("same");
	gPad->SetGridx();
	gPad->SetGridy();
	PutText(0.5, 0.89, kBlack, "LAPD");
	PutText(0.5, 0.82, kBlack, "PMMA 5#times5 cm");
	TLegend* leg2 = new TLegend(0.7,0.3,0.9,0.75);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h1, "z = 13 cm", "l");
	leg2->AddEntry(h2, "z = 13.5 cm", "l");
	leg2->Draw();
	c2->SaveAs("c2.png");
	
	TCanvas* c3 = new TCanvas("c3", "c3");
	TH1F* h11 = GetZDistr("~/godaq_rootfiles/analysis_v2.11-calibG2/run112Mult2.root", "h10", kRed, -100, 100);
	h11->Draw();
	gPad->SetGridx();
	gPad->SetGridy();
	PutText(0.5, 0.89, kBlack, "LAPD");
	PutText(0.5, 0.82, kBlack, "Target PMMA (splitted)");
	c3->SaveAs("c3.png");
}