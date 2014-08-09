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


void plotFastJetPTD(const std::string histFileName, const std::string alg, const std::string constAlg)
{
  TFile *f = new TFile(histFileName.c_str(), "UPDATE");

  TH1F* getHist_Tot_p[4];
  TH1F* getHist_Q_p[4];
  TH1F* getHist_G_p[4];

  const std::string centString[4] = {"50100", "3050", "1030", "010"};
  const std::string centString2[4] = {"50-100%", "30-50%", "10-30%", "0-10%"};

  for(Int_t iter = 0; iter < 4; iter++){
    getHist_Tot_p[iter] = (TH1F*)f->Get(Form("%s%sPTDHist_Tot_%s_h", alg.c_str(), constAlg.c_str(), centString[iter].c_str()));
    niceTH1(getHist_Tot_p[iter], .20, 0.0, 505, 402);

    getHist_Q_p[iter] = (TH1F*)f->Get(Form("%s%sPTDHist_Q_%s_h", alg.c_str(), constAlg.c_str(), centString[iter].c_str()));
    niceTH1(getHist_Q_p[iter], .20, 0.0, 505, 402);

    getHist_G_p[iter] = (TH1F*)f->Get(Form("%s%sPTDHist_G_%s_h", alg.c_str(), constAlg.c_str(), centString[iter].c_str()));
    niceTH1(getHist_G_p[iter], .20, 0.0, 505, 402);
  }

  TCanvas* plotCanvas_p = new TCanvas(Form("%s%sPTDCanv_c", alg.c_str(), constAlg.c_str()), Form("%s%sPTDCanv_c", alg.c_str(), constAlg.c_str()), 4*300, 2*350);
  plotCanvas_p->Divide(4, 2, 0.0, 0.0);

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(23);

  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p->cd(iter+1);
    getHist_Tot_p[iter]->SetXTitle("PTD_{1}");
    getHist_Tot_p[iter]->SetYTitle("Event Fraction");
    getHist_Tot_p[iter]->SetAxisRange(.001, .999);
    getHist_Tot_p[iter]->DrawCopy("Hist");

    getHist_Q_p[iter]->SetFillColor(kBlue);
    getHist_G_p[iter]->SetFillColor(kRed);

    for(Int_t histIter = 0; histIter < getHist_Q_p[iter]->GetNbinsX(); histIter++){
      Float_t tempContent = getHist_Q_p[iter]->GetBinContent(histIter+1) + getHist_G_p[iter]->GetBinContent(histIter+1);
      getHist_Q_p[iter]->SetBinContent(histIter+1, tempContent);
    }

    getHist_Q_p[iter]->DrawCopy("SAME HIST");
    getHist_G_p[iter]->DrawCopy("SAME HIST");

    drawMeanLine(getHist_Tot_p[iter]->GetMean());
    label_p->DrawLatex(.7, .8, alg.c_str());
    label_p->DrawLatex(.7, .7, centString2[iter].c_str());
  }

  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p->cd(iter+5);

    for(Int_t histIter = 0; histIter < getHist_Q_p[iter]->GetNbinsX(); histIter++){
      Float_t tempContent = getHist_Q_p[iter]->GetBinContent(histIter+1) - getHist_G_p[iter]->GetBinContent(histIter+1);
      getHist_Q_p[iter]->SetBinContent(histIter+1, tempContent);
    }

    getHist_Q_p[iter]->Divide(getHist_Tot_p[iter]);
    getHist_G_p[iter]->Divide(getHist_Tot_p[iter]);

    niceTH1(getHist_Q_p[iter], 1.0, 0.0, 505, 505);
    niceTH1(getHist_G_p[iter], 1.0, 0.0, 505, 505);
    getHist_Q_p[iter]->SetYTitle("Ratio");
    getHist_G_p[iter]->SetYTitle("Ratio");

    getHist_Q_p[iter]->SetMarkerColor(kBlue);
    getHist_G_p[iter]->SetMarkerColor(kRed);

    getHist_Q_p[iter]->DrawCopy();
    getHist_G_p[iter]->DrawCopy("SAME");
  }

  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%s%sPTDCanv", alg.c_str(), constAlg.c_str()), "pdf");

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
    
    plotFastJetPTD(histFileName, algType[iter], "PFVs");
    plotFastJetPTD(histFileName, algType[iter], "PFRaw");
  }
  return;
}
