#include "Utils.C"

void SplittedTarget(TTree* t, TCut cut, int color)
{
	TH1F* h = new TH1F("h", "h", 2000, -100, 100);
	t->Draw("LORZmar>>h", cut, "goff");
	
	h->SetLineColor(color);
        h->SetFillColor(color);
        h->SetFillStyle(3002);
	h->GetYaxis()->SetRangeUser(0, h->GetMaximum());
	
	h->GetXaxis()->SetTitle("z_{MAR} [mm]");
	h->GetYaxis()->SetTitle("Entries");

	TH1F* hKeys = MakeKernelPDFFromTH1(h, kRed, 1);
	hKeys->Scale(h->GetMaximum()*1.2/hKeys->GetMaximum());
	hKeys->GetXaxis()->SetTitle("z [mm]");
	hKeys->GetYaxis()->SetTitle("Entries [a.u]");
	
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	double xmin = -50;
	double xmax = 50;
	
	hKeys->SetFillColor(kBlack);
	hKeys->SetLineColor(kBlack);

	//h->Draw();
	//hKeys->Draw("same");
	hKeys->Draw();
	
	PutText(0.2, 0.8, kBlack, "LAPD", 0.05);
	PutText(0.2, 0.74, kBlack, "Protons 65 MeV, I = 5 nA ", 0.05);
	PutText(0.2, 0.68, kBlack, "Splitted PMMA target", 0.05);
}

void SplittedTarget()
{	
  TFile* f = new TFile("analysis_v2.18-calibG2/run112LOR_80kevts.root", "read");
  //TFile* f = new TFile("analysis_v3.2-calibG2/run112LOR_80kevts.root", "read");
	TTree* t = (TTree*) f->Get("tree");
	
	TCanvas* c0 = new TCanvas("c0", "c0");
	t->Draw("RateLvsL3:Evt");
	
	TCut cutTimes = "T30[LORIdx1] > 20 && T30[LORIdx1] < 50 && T30[LORIdx2] > 20 && T30[LORIdx2] < 50";
	TCut cutLOR = "NoLORs == 1 && LORRmar < 25";
	
	TCut cutEventsDesact = "Evt > 45000"; 
	TCut cutDesactivation = cutTimes && cutLOR && cutEventsDesact;
	
	TCanvas* c1 = new TCanvas("c1", "c1");
	SplittedTarget(t, cutDesactivation, kRed);
	
	/*
	TCut cutBeamPause = "abs(LORTMean - LORTRF - 7) > 5";
	TCut cutEventsInBeam = "Evt > 2000 && Evt < 42000"; 
	TCut cutInBeam = cutTimes && cutLOR && cutBeamPause && cutEventsInBeam;
	
	TCanvas* c2 = new TCanvas("c2", "c2");
	SplittedTarget(t, cutInBeam, kGreen+2);
	*/
	
}
