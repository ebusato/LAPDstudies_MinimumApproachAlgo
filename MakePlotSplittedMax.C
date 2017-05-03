void MakePlotSplittedMax()
{
  TCanvas* cMaxSplitted = new TCanvas("cMaxSplitted","cMaxSplitted");
  cMaxSplitted->SetGridx(1);
  cMaxSplitted->SetGridy(1);

  TNtuple* nt = new TNtuple("nt","nt","x:y");
  nt->ReadFile("SplittedTargetMaxFromWebPlotDigitizer2.dat");
  int n = nt->Draw("x+81.2:Entry$*19.5","","goff");
  TGraph *g = new TGraph(n,nt->GetV1(),nt->GetV2());
  g->Draw("ap");
  g->GetXaxis()->SetRangeUser(0,150);
  g->GetYaxis()->SetRangeUser(0,150);
  g->GetXaxis()->SetTitle("z_{ slab} - z_{ slab}^{0} [mm]");
  g->GetYaxis()->SetTitle("mode[z_{ reco}] - mode[z_{ reco}^{0}] [mm]");
  g->GetXaxis()->SetTitleSize(0.06);
  g->GetYaxis()->SetTitleSize(0.06);
  g->GetXaxis()->SetTitleOffset(1.3);
  g->GetYaxis()->SetTitleOffset(1.3);
  g->GetXaxis()->SetLabelSize(0.06);
  g->GetYaxis()->SetLabelSize(0.06);
  g->GetXaxis()->SetNdivisions(10);
  g->GetYaxis()->SetNdivisions(10);
	g->SetMarkerSize(1.5);
  TF1* f = new TF1("f","x",0,150);
  f->Draw("same");

  PutText(0.25, 0.8, kBlack, "LAPD", 0.05);
  PutText(0.25, 0.72, kBlack, "Protons 65 MeV, I = 5 nA ", 0.05);
  PutText(0.25, 0.64, kBlack, "Target PMMA slabs", 0.05);

  cMaxSplitted->SaveAs("cMaxSplitted.png");

  TCanvas* cMaxSplitted2 = new TCanvas("cMaxSplitted2","cMaxSplitted2");
  nt->Draw("x+81.2:Entry$","","goff");
  TGraph *g2 = new TGraph(n,nt->GetV2(),nt->GetV1());
  g2->Draw("ap");
  TF1* fitFunc = new TF1("fitFunc","[0]*x");
  g2->Fit("fitFunc");
}
