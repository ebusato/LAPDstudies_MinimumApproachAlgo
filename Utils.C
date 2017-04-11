
using namespace RooFit;

TH1F* MakeKernelPDFFromTH1(TH1F* h, int color)
{
  RooRealVar* z = new RooRealVar("z", "z", -100, 100);
  z->setBins(10000);
  RooDataSet* ds = new RooDataSet("ds","ds",RooArgSet(*z)) ;
  for(int i=0; i<h->GetNbinsX(); i++) {
	double binContent = h->GetBinContent(i);
	if(binContent!=0) {
	  double binCenter = h->GetBinCenter(i);
	  z->setVal(binCenter);
	  for(int j=0; j<binContent; j++) {
	  	ds->add(RooArgSet(*z));
	  }
	}
  }
  RooDataHist* dh = new RooDataHist("dh", "dh", *z, Import(*h));
  
//   RooKeysPdf kest1("kest1","kest1",*z,*ds,RooKeysPdf::MirrorBoth, 2) ;
  RooKeysPdf kest1("kest1","kest1",*z,*ds,RooKeysPdf::NoMirror, 2) ;
//   RooPlot* frame = z->frame() ;
// //   ds->plotOn(frame);
//   dh->plotOn(frame);
//   kest1.plotOn(frame);
//   frame->Draw();
//   
  TH1F* hKeys = (TH1F*) kest1.createHistogram("hKeys", *z);
  hKeys->SetLineColor(color);
  hKeys->SetFillColor(color);
  hKeys->SetFillStyle(3002);
  hKeys->GetYaxis()->SetTitle("Probability density [a. u.]");
  hKeys->GetYaxis()->SetTitleSize(0.06);
  hKeys->GetYaxis()->SetLabelSize(0.055);
  hKeys->GetYaxis()->SetTitleOffset(1.39);
  hKeys->GetXaxis()->SetTitle("z [mm]");
  hKeys->GetXaxis()->SetTitleSize(0.06);
  hKeys->GetXaxis()->SetLabelSize(0.055);
  hKeys->GetXaxis()->SetTitleOffset(1.37);
  for(int i=0; i<hKeys->GetNbinsX(); i++) {
	  hKeys->SetBinError(i, 0);
// 	cout << "i, Err: " << i << "  " << hKeys->GetXaxis()->GetBinCenter(i) << "  " << hKeys->GetBinError(i) << endl;  
  }
//   hKeys->Draw("histsame");
  return hKeys;
}