void MakePlotSplittedMax()
{
  TNtuple* nt = new TNtuple("nt","nt","x:y");
  nt->ReadFile("SplittedTargetMaxFromWebPlotDigitizer.dat");
  nt->Draw("x+81.2:Entry$*19.5");
  TF1* f = new TF1("f","x",0,150);
  f->Draw("same");

}
