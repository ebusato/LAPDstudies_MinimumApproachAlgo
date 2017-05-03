void MakePlotSplittedMax()
{
  TCanvas* cMaxSplitted = new TCanvas("cMaxSplitted","cMaxSplitted");
  cMaxSplitted->SetGridx(1);
  cMaxSplitted->SetGridy(1);

  TNtuple* nt = new TNtuple("nt","nt","x:y");
  nt->ReadFile("SplittedTargetMaxFromWebPlotDigitizer.dat");
  int n = nt->Draw("x+81.2:Entry$*19.5","","goff");
  TGraph *g = new TGraph(n,nt->GetV1(),nt->GetV2());
  g->Draw("ap");
  g->GetXaxis()->SetRangeUser(0,150);
  g->GetYaxis()->SetRangeUser(0,150);
  TF1* f = new TF1("f","x",0,150);
  f->Draw("same");

}
