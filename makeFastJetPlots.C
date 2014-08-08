#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TString.h"

#include <iostream>
#include <fstream>
#include <string>

#include "TLatex.h"
#include "TLine.h"

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};


void handsomeTH1( TH1 *a=0, Int_t col =1, Float_t size=1, Int_t markerstyle=20)
{
  a->SetMarkerColor(col);
  a->SetMarkerSize(size);
  a->SetMarkerStyle(markerstyle);
  a->SetLineColor(col);
  a->GetXaxis()->SetTitleOffset(1.6);
  a->GetYaxis()->SetTitleOffset(2.5);
  a->GetXaxis()->CenterTitle();
  a->GetYaxis()->CenterTitle();
}


void niceTH1(TH1F* uglyTH1, float max , float min, float ndivX, float ndivY)
{
  handsomeTH1(uglyTH1);
  uglyTH1->SetMaximum(max);
  uglyTH1->SetMinimum(min);
  uglyTH1->GetXaxis()->SetNdivisions(ndivX, false);
  uglyTH1->GetYaxis()->SetNdivisions(ndivY, false);
  return;
}

void claverCanvasSaving(TCanvas* c, TString s,TString format="gif") {
  TDatime* date = new TDatime();
  c->SaveAs(Form("%s_%d.%s",s.Data(),date->GetDate(), format.Data()));
}


void drawMeanLine(Float_t histMean)
{
  TLine* oneLine_p = new TLine(histMean, 0.0, histMean, 0.20);
  oneLine_p->SetLineColor(1);
  oneLine_p->SetLineStyle(2);

  oneLine_p->Draw("Same");
}


void plotFastJetPTD(const std::string histFileName, const std::string alg)
{
  TFile *f = new TFile(histFileName.c_str(), "UPDATE");

  TH1F* getHist_p[4];

  const std::string centString[4] = {"50100", "3050", "1030", "010"};
  const std::string centString2[4] = {"50-100%", "30-50%", "10-30%", "0-10%"};

  for(Int_t iter = 0; iter < 4; iter++){
    getHist_p[iter] = (TH1F*)f->Get(Form("%sPFVsPTDHist_%s_h", alg.c_str(), centString[iter].c_str()));
    niceTH1(getHist_p[iter], .16, 0.0, 505, 402);
  }

  TCanvas* plotCanvas_p = new TCanvas(Form("%sPFVsPTDCanv_c", alg.c_str()), Form("%sPFVsPTDCanv_c", alg.c_str()), 4*300, 2*350);
  plotCanvas_p->Divide(4, 2, 0.0, 0.0);

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(23);

  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p->cd(iter+1);
    getHist_p[iter]->SetXTitle("PTD_{1}");
    getHist_p[iter]->SetYTitle("Event Fraction");
    getHist_p[iter]->SetAxisRange(.001, .999);
    getHist_p[iter]->DrawCopy("Hist");
    drawMeanLine(getHist_p[iter]->GetMean());

    label_p->DrawLatex(.7, .8, alg.c_str());
    label_p->DrawLatex(.7, .7, centString2[iter].c_str());
  }

  TLine* oneLine_p = new TLine(0.0, 1.0, 1.0, 1.0);
  oneLine_p->SetLineColor(1);
  oneLine_p->SetLineStyle(2);

  plotCanvas_p->cd(6);
  niceTH1(getHist_p[1], 1.5, .5, 505, 402);
  getHist_p[1]->Divide(getHist_p[0]);
  getHist_p[1]->DrawCopy();
  oneLine_p->Draw("SAME");

  plotCanvas_p->cd(7);
  niceTH1(getHist_p[2], 1.5, .5, 505, 402);
  getHist_p[2]->Divide(getHist_p[0]);
  getHist_p[2]->DrawCopy();
  oneLine_p->Draw("SAME");

  plotCanvas_p->cd(8);
  niceTH1(getHist_p[3], 1.5, .5, 505, 402);
  getHist_p[3]->Divide(getHist_p[0]);
  getHist_p[3]->DrawCopy();
  oneLine_p->Draw("SAME");

  plotCanvas_p->cd(5);
  niceTH1(getHist_p[0], 1.5, .5, 505, 402);
  getHist_p[0]->Divide(getHist_p[0]);
  getHist_p[0]->SetYTitle("Ratio w/ Peripheral");
  getHist_p[0]->DrawCopy();
  oneLine_p->Draw("SAME");

  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%sPFVsPTDCanv", alg.c_str()), "pdf");

  delete label_p;
  delete plotCanvas_p;
  f->Close();
  delete f;
  return;
}


void makeFastJetPlots(const std::string histFileName, Bool_t isMonteCarlo = false)
{
  TH1::SetDefaultSumw2();

  for(Int_t iter = 0; iter < 5; iter++){
    if(iter == 2) continue;
    
    plotFastJetPTD(histFileName, algType[iter]);
  }
  return;
}
