#include "TH1F.h"
#include "TH2F.h"
#include "TH1I.h"
#include "TFile.h"
#include "TDatime.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

const std::string bBins[5] = {"0.0", "8.5", "11.6", "14.0", "20.0"};

void handsomeTH1( TH1 *a=0, Int_t col =1, Float_t size=1, Int_t markerstyle=20)
{
  a->SetMarkerColor(col);
  a->SetMarkerSize(size);
  a->SetMarkerStyle(markerstyle);
  a->SetLineColor(col);
}


void niceTH1(TH1* uglyTH1, float max , float min, float ndivX, float ndivY)
{
  handsomeTH1(uglyTH1);
  uglyTH1->SetMaximum(max);
  uglyTH1->SetMinimum(min);
  uglyTH1->GetXaxis()->SetNdivisions(ndivX);
  uglyTH1->GetYaxis()->SetNdivisions(ndivY);
  return;
}

void handsomeTH2( TH2 *a=0)
{
  a->GetYaxis()->SetTitleOffset(1.25);
  a->GetXaxis()->CenterTitle();
  a->GetYaxis()->CenterTitle();
}


void makeFastJetPlots_Jet(const std::string inName, const std::string outName)
{
  TFile* inFile_p = new TFile(inName.c_str(), "READ");

  TH2F* getImpact_p = (TH2F*)inFile_p->Get("impactCut_h");
  handsomeTH2(getImpact_p);
  getImpact_p->SetXTitle("b (fm)");
  getImpact_p->SetYTitle("p_{T}^{SK} Cut (GeV/c)");

  TH1F* getGenSubeRaw[4];
  TH1F* getGenSubeSK[4];
  for(Int_t iter = 0; iter < 4; iter++){
    getGenSubeRaw[iter] = (TH1F*)inFile_p->Get(Form("genSubeRaw_b%d_h", iter));
    niceTH1(getGenSubeRaw[iter], 1.1999, 0.0001, 505, 505);

    getGenSubeSK[iter] = (TH1F*)inFile_p->Get(Form("genSubeSK_b%d_h", iter));
    getGenSubeSK[iter]->SetXTitle("Signal == 0/Bkgd == 1");
    getGenSubeSK[iter]->SetYTitle("Momentum Fraction");
    niceTH1(getGenSubeSK[iter], 1.1999, 0.0001, 505, 505);

    getGenSubeSK[iter]->GetYaxis()->SetTitleOffset(1.25);

    getGenSubeSK[iter]->GetXaxis()->SetTitleFont(43);
    getGenSubeSK[iter]->GetYaxis()->SetTitleFont(43);

    getGenSubeSK[iter]->GetXaxis()->SetTitleSize(22);
    getGenSubeSK[iter]->GetYaxis()->SetTitleSize(22);

    getGenSubeSK[iter]->SetMarkerColor(kRed);
    getGenSubeRaw[iter]->SetLineColor(kBlue);
  }

  TCanvas* c1 = new TCanvas("impactCanv", "impactCanv", 2*300, 2*350);
  c1->SetLogz();
  getImpact_p->DrawCopy("COL");

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(23);

  label_p->DrawLatex(.4, .9, "PYTHIA+HYDJET, Gen. Level");

  TCanvas *c2 = new TCanvas("genSubeCanv", "genSubeCanv", 4*300, 1*350);
  c2->Divide(4, 1, 0, 0);

  const Float_t xPos[4] = {.3, .15, .15, .15};

  for(Int_t iter = 0; iter < 4; iter++){
    c2->cd(iter+1);
    getGenSubeSK[3-iter]->DrawCopy("P");
    getGenSubeRaw[3-iter]->DrawCopy("HIST SAME");
    label_p->DrawLatex(xPos[iter], .9, "PYTHIA+HYDJET (Gen)");
    label_p->DrawLatex(xPos[iter], .82, Form("%s < b < %s", bBins[3-iter].c_str(), bBins[3-iter+1].c_str()));
  }

  c2->cd(1);

  TLegend* leg_p = new TLegend(0.70, 0.45, 0.95, 0.75);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSizePixels(16);
  leg_p->SetBorderSize(0);

  leg_p->AddEntry(getGenSubeRaw[0], "Uncut", "L");
  leg_p->AddEntry(getGenSubeSK[0], "SK Cut", "P");

  leg_p->Draw();

  TFile* outFile_p = new TFile(outName.c_str(), "UPDATE");
  c1->Write("", TObject::kOverwrite);
  c2->Write("", TObject::kOverwrite);
  outFile_p->Close();
  delete outFile_p;
  delete c1;
  delete inFile_p;

  return;
}
