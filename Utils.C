
using namespace RooFit;

TH1F* MakeKernelPDFFromTH1(TH1F* h, int color, double rho)
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
  RooKeysPdf kest1("kest1","kest1",*z,*ds,RooKeysPdf::NoMirror, rho) ;
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
  hKeys->GetXaxis()->SetTitle("z_{MAR} [mm]");
  hKeys->GetXaxis()->SetTitleSize(0.06);
  hKeys->GetXaxis()->SetLabelSize(0.055);
  hKeys->GetXaxis()->SetTitleOffset(1.3);
  hKeys->SetLineWidth(2);
  for(int i=0; i<hKeys->GetNbinsX(); i++) {
	  hKeys->SetBinError(i, 0);
// 	cout << "i, Err: " << i << "  " << hKeys->GetXaxis()->GetBinCenter(i) << "  " << hKeys->GetBinError(i) << endl;  
  }
//   hKeys->Draw("histsame");
  return hKeys;
}


TF1* FitKeysSideBand(TH1F* h, string histName, double Lmin, double Lmax, double Rmin, double Rmax)
{
  RooRealVar* Z = new RooRealVar("Z", "Z", -70, 70, "mm");
  Z->setRange("R1",Lmin,Lmax);
  Z->setRange("R2",Rmin,Rmax);
  //Z->setRange("R1",-30,0);
  RooRealVar* mean = new RooRealVar("mean", "mean", -5);
  RooRealVar* sigma = new RooRealVar("sigma", "width", 45);

  RooGaussian* gaussian = new RooGaussian("gaussian", "gaussian", *Z, *mean, *sigma);

  RooDataHist* dh = new RooDataHist(histName.c_str(), histName.c_str(), *Z, Import(*h));

  gaussian->fitTo(*dh, Extended(),Range("R1", "R2"), SumW2Error(kTRUE));

  TF1* gaussianTF = gaussian->asTF(RooArgList(*Z), RooArgList(*mean,*sigma), RooArgSet(*Z));

  return gaussianTF;
}

TH1F* Subtract(TH1F* h, TF1* f) 
{
  TString name(h->GetName());
  name+="_clone";
  TH1F* h1 = (TH1F*) h->Clone(name);
  h1->Reset();
  h1->Sumw2();
  for(int i=0; i<h->GetNbinsX(); i++)
    {
      double content = h->GetBinContent(i);
      double val = h->GetBinCenter(i);
      double funcval = f->Eval(val);
      //cout << i << "  " << val << "  " << content << "  " << funcval<< endl;
      h1->SetBinContent(i, content-funcval);
      //h1->Set
    }
  return h1;
}

TH1F* Draw(TTree* t, TString var, TCut cut, TString hName, int Nbins, double xmin, double xmax, int color, int linesize)
{
	TH1F* h = new TH1F(hName.Data(), hName.Data(), Nbins, xmin, xmax);
	TString temp(var);
	temp+=">>";
	temp+=hName;
	t->Draw(temp.Data(), cut);
	h->SetLineColor(color);
	h->SetMarkerColor(color);
	h->SetLineWidth(linesize);
	return h;
}

  //RooDataSet* data = new RooDataSet("data","data",RooArgSet(x));
  //x=4;
  //data->add(RooArgSet(x));


class HalfMaxCoords {
public:
	void Print();
	
	double m_Xlow;
	double m_Xhigh;
	double m_Ylow;
	double m_Yhigh;
};
 
void HalfMaxCoords::Print()
{
	cout << "m_Xlow = " << m_Xlow << endl;
	cout << "m_Xhigh = " << m_Xhigh << endl;
	cout << "m_Ylow = " << m_Ylow << endl;
	cout << "m_Yhigh = " << m_Yhigh << endl;
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

HalfMaxCoords* FindHalfMaxCoords(TH1F* h)
{
   double max = Maximum(h);
   int bin1 = h->FindFirstBinAbove(max/2.);
   int bin2 = h->FindLastBinAbove(max/2.);
   // 0.018 is the background estimated by eye !
   //int bin1 = h->FindFirstBinAbove((max-0.018)/2.+0.018);
   //int bin2 = h->FindLastBinAbove((max-0.018)/2.+0.018);
   HalfMaxCoords* coords = new HalfMaxCoords();
   coords->m_Xlow = h->GetBinCenter(bin1);
   coords->m_Xhigh = h->GetBinCenter(bin2);
   coords->m_Ylow = h->GetBinContent(bin1);
   coords->m_Yhigh = h->GetBinContent(bin2);
   return coords;
}

class TreeAnalysis {
public:
	// zTargetSupport is in mm
	TreeAnalysis(TTree* t, TCut cutEvents, TCut cutEnergy, int color, double zTargetSupport);
	TTree* m_tree;
	TCut m_cutTimes;
	TCut m_cutLOR;
	TCut m_cutBeamPause;
	TCut m_cutEvents;
	TCut m_cutEnergy;
	int m_color;	
	double m_zTargetSupport;
	
	TH1F* m_hKeys;
	HalfMaxCoords* m_coords;
};

TreeAnalysis::TreeAnalysis(TTree* t, TCut cutEvents, TCut cutEnergy, int color, double zTargetSupport) : m_tree(t),
							    m_cutEvents(cutEvents),
							    m_cutEnergy(cutEnergy),
							    m_color(color),
							    m_zTargetSupport(zTargetSupport)
{
	m_cutTimes = "T30[LORIdx1] > 20 && T30[LORIdx1] < 50 && T30[LORIdx2] > 20 && T30[LORIdx2] < 50";
	m_cutLOR = "NoLORs == 1 && LORRmar < 15";
	m_cutBeamPause = "abs(LORTMean - LORTRF - 7) > 5";
// 	m_cutBeamPause = "";
}