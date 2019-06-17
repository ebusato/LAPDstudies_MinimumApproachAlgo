#include "Utils.C"
#include "/home/ebusato/Travail/AVIRM/avirmStyle/avirmStyle.C"

void HDPEProfile(TTree* t, TCut cut, int color)
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

void HDPEProfile()
{	
  TFile* f = new TFile("~/godaq/analysis_v3.3-calibK1/run83LOR.root", "read");
  
  TTree* t = (TTree*) f->Get("tree");

  double time = 15*60.; // time in seconds
  TreeAnalysis* tAna_0 = new TreeAnalysis(t, 950, time, "E[LORIdx1] > 450 && E[LORIdx1] < 700 && E[LORIdx2] > 450 && E[LORIdx2] < 700", kRed, 135);
  
  TCanvas* c0 = new TCanvas("c0", "c0", 1200, 600);
  c0->Divide(2, 1);
  c0->cd(1);
  tAna_0->m_tree->Draw("RateLvsL3 : Evt");
  c0->cd(2);
  tAna_0->m_tree->Draw("RateLvsL3 : Evt", tAna_0->m_cutEvents);
  
  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TString hName("hArnaud");
  hName+=0;
  TH2F* hArnaud = new TH2F(hName.Data(), hName.Data(), 100, 0, 40, 200, 0, 1000);
  TString cmd1("E[LORIdx1] : LORTMean - LORTRF>>");
  TString cmd2(cmd1);
  cmd1+=hName;
  cmd2+="+";
  cmd2+=hName;
  tAna_0->m_tree->Draw(cmd1.Data(), tAna_0->m_cutEvents && tAna_0->m_cutTimes && tAna_0->m_cutLOR, "colz");
  tAna_0->m_tree->Draw(cmd2.Data(), tAna_0->m_cutEvents && tAna_0->m_cutTimes && tAna_0->m_cutLOR, "colz");
  hArnaud->Draw("colz");

  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);
  TString hNameTemp("hETemp");
  hNameTemp+=0;
  hName = "hE";
  hName+=0;
  TH1F* hETemp = Draw(tAna_0->m_tree, "E[LORIdx1]", tAna_0->m_cutEnergy && tAna_0->m_cutEvents && tAna_0->m_cutTimes && tAna_0->m_cutBeamPause, hNameTemp.Data(), 100, 0, 1000, tAna_0->m_color, 1);
  TH1F* hE = Draw(tAna_0->m_tree, "E[LORIdx2]", tAna_0->m_cutEnergy && tAna_0->m_cutEvents && tAna_0->m_cutTimes && tAna_0->m_cutBeamPause, hName.Data(), 100, 0, 1000, tAna_0->m_color, 1);
  hE->Add(hETemp);
  cout << "name = " << hE->GetName() << " " << hE->GetEntries() << endl;
  hE->Draw("");

  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);
  hName = "hZmar";
  hName+=0;
  TH1F* hZmar = Draw(tAna_0->m_tree, "LORZmar", tAna_0->m_cutEnergy && tAna_0->m_cutLOR && tAna_0->m_cutEvents && tAna_0->m_cutTimes && tAna_0->m_cutBeamPause, hName.Data(), 2000, -100, 100, tAna_0->m_color, 3);
  TFile* fOut = new TFile("hZ_HDPE.root","recreate");
  hZmar->Write();
  fOut->Write();
  fOut->Close();
  //hZmar->Sumw2();
  //cout << "hZmar integral " << hZmar->Integral() << endl;
}
