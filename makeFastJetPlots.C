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
#include "TLegend.h"

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};


void handsomeTH1( TH1 *a=0, Int_t col =1, Float_t size=1, Int_t markerstyle=20)
{
  a->SetMarkerColor(col);
  a->SetMarkerSize(size);
  a->SetMarkerStyle(markerstyle);
  a->SetLineColor(col);
}


void niceTH1(TH1F* uglyTH1, float max , float min, float ndivX, float ndivY)
{
  handsomeTH1(uglyTH1);
  uglyTH1->SetMaximum(max);
  uglyTH1->SetMinimum(min);
  uglyTH1->GetXaxis()->SetNdivisions(ndivX);
  uglyTH1->GetYaxis()->SetNdivisions(ndivY);
  return;
}

void claverCanvasSaving(TCanvas* c, TString s,TString format="gif") {
  TDatime* date = new TDatime();
  c->SaveAs(Form("%s_%d.%s",s.Data(),date->GetDate(), format.Data()));
}


void drawMeanLine(Float_t histMean, Int_t lineStyle = 2)
{
  TLine* oneLine_p = new TLine(histMean, 0.0, histMean, 0.10);
  oneLine_p->SetLineColor(1);
  oneLine_p->SetLineStyle(lineStyle);

  oneLine_p->Draw("Same");
}


void SetTitleLabel(TH1F* inHist_p, Int_t titleSize, Int_t labelSize, std::string xTitle, Float_t xOff, std::string yTitle, Float_t yOff)
{
  inHist_p->GetXaxis()->SetTitleOffset(xOff);
  inHist_p->GetYaxis()->SetTitleOffset(yOff);
  inHist_p->GetXaxis()->CenterTitle();
  inHist_p->GetYaxis()->CenterTitle();

  inHist_p->GetXaxis()->SetTitleSize(titleSize);
  inHist_p->GetYaxis()->SetTitleSize(titleSize);
  inHist_p->GetXaxis()->SetLabelSize(labelSize);
  inHist_p->GetYaxis()->SetLabelSize(labelSize);

  inHist_p->SetXTitle(xTitle.c_str());
  inHist_p->SetYTitle(yTitle.c_str());
}


void plotFastJetPTD(const std::string histFileName, const std::string alg, const std::string constAlg, const std::string dataFileName = "")
{
  const Int_t titleSize = 24;
  const Int_t labelSize = 20;

  const std::string centString[4] = {"50100", "3050", "1030", "010"};
  const std::string centString2[4] = {"50-100%", "30-50%", "10-30%", "0-10%"};

  TFile* dataFile;
  TH1F* getHist_Data_p[4];

  if(strcmp("", dataFileName.c_str()) != 0){
    dataFile = new TFile(dataFileName.c_str(), "READ");

    for(Int_t iter = 0; iter < 4; iter++){
      getHist_Data_p[iter] = (TH1F*)dataFile->Get(Form("%s%sPTDHist_Tot_%s_h", alg.c_str(), constAlg.c_str(), centString[iter].c_str()));
      niceTH1(getHist_Data_p[iter], 0.20, 0.00, 505, 202);  
    }
  }


  TFile *f = new TFile(histFileName.c_str(), "UPDATE");

  TH1F* getHist_Tot_p[4];
  TH1F* getHist_Q_p[4];
  TH1F* getHist_G_p[4];

  for(Int_t iter = 0; iter < 4; iter++){
    getHist_Tot_p[iter] = (TH1F*)f->Get(Form("%s%sPTDHist_Tot_%s_h", alg.c_str(), constAlg.c_str(), centString[iter].c_str()));
    niceTH1(getHist_Tot_p[iter], 0.20, 0.00, 505, 202);

    getHist_Q_p[iter] = (TH1F*)f->Get(Form("%s%sPTDHist_Q_%s_h", alg.c_str(), constAlg.c_str(), centString[iter].c_str()));
    niceTH1(getHist_Q_p[iter], 0.20, 0.00, 505, 202);

    getHist_G_p[iter] = (TH1F*)f->Get(Form("%s%sPTDHist_G_%s_h", alg.c_str(), constAlg.c_str(), centString[iter].c_str()));
    niceTH1(getHist_G_p[iter], 0.20, 0.00, 505, 202);
  }

  TCanvas* plotCanvas_p = new TCanvas(Form("%s%sPTDCanv_c", alg.c_str(), constAlg.c_str()), Form("%s%sPTDCanv_c", alg.c_str(), constAlg.c_str()), 4*300, 2*350);
  plotCanvas_p->Divide(4, 2, 0.0, 0.0);

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(23);

  const std::string jetLabels[4] = {Form("Dijet selection w/ ak%s", alg.c_str()), Form("Recluster w/ %s", constAlg.c_str()), "CA Algorithm", "R = 0.3"};
  const std::string cutLabels[4] = {"p_{T} > 80 GeV/c", "|#eta| < 2.0", "", ""};

  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p->cd(iter+1); 
    SetTitleLabel(getHist_Tot_p[iter], titleSize, labelSize, "p_{T}D", 1.5, "EventFraction", 2.0);
    getHist_Tot_p[iter]->DrawCopy("Hist");

    getHist_Q_p[iter]->SetFillColor(kBlue);
    getHist_G_p[iter]->SetFillColor(kRed);

    SetTitleLabel(getHist_Q_p[iter], titleSize, labelSize, "p_{T}D", 1.5, "EventFraction", 2.0);
    SetTitleLabel(getHist_G_p[iter], titleSize, labelSize, "p_{T}D", 1.5, "EventFraction", 2.0);

    for(Int_t histIter = 0; histIter < getHist_Q_p[iter]->GetNbinsX(); histIter++){
      Float_t tempContent = getHist_Q_p[iter]->GetBinContent(histIter+1) + getHist_G_p[iter]->GetBinContent(histIter+1);
      getHist_Q_p[iter]->SetBinContent(histIter+1, tempContent);
    }

    getHist_Q_p[iter]->DrawCopy("SAME HIST");
    getHist_G_p[iter]->DrawCopy("SAME HIST");
    if(strcmp("", dataFileName.c_str()) != 0){
      getHist_Data_p[iter]->DrawCopy("SAME");
      drawMeanLine(getHist_Data_p[iter]->GetMean(), 1);
    }

    drawMeanLine(getHist_Tot_p[iter]->GetMean());
    label_p->DrawLatex(.3, .92, jetLabels[iter].c_str());
    label_p->DrawLatex(.3, .84, centString2[iter].c_str());
    label_p->DrawLatex(.3, .76, cutLabels[iter].c_str());
  }

  TLegend* leg_p = new TLegend(0.70, 0.45, 0.95, 0.75);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSizePixels(16);
  leg_p->SetBorderSize(0);

  leg_p->AddEntry(getHist_Q_p[0], "Quark", "F");
  leg_p->AddEntry(getHist_G_p[0], "Gluon", "F");
  leg_p->AddEntry(getHist_Tot_p[0], "Untagged", "F");
  if(strcmp("", dataFileName.c_str()) != 0) leg_p->AddEntry(getHist_Data_p[0], "Data", "P");

  plotCanvas_p->cd(1);
  leg_p->Draw("SAME");


  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p->cd(iter+5);

    for(Int_t histIter = 0; histIter < getHist_Q_p[iter]->GetNbinsX(); histIter++){
      Float_t tempContent = getHist_Q_p[iter]->GetBinContent(histIter+1) - getHist_G_p[iter]->GetBinContent(histIter+1);
      getHist_Q_p[iter]->SetBinContent(histIter+1, tempContent);
    }

    getHist_Q_p[iter]->Divide(getHist_Tot_p[iter]);
    getHist_G_p[iter]->Divide(getHist_Tot_p[iter]);

    niceTH1(getHist_Q_p[iter], 0.9999, 0.0001, 505, 505);
    niceTH1(getHist_G_p[iter], 0.9999, 0.0001, 505, 505);

    getHist_Q_p[iter]->SetMarkerColor(kBlue);
    getHist_G_p[iter]->SetMarkerColor(kRed);

    SetTitleLabel(getHist_Q_p[iter], titleSize, labelSize, "p_{T}D", 1.5, "Fraction of Total", 2.0);
    SetTitleLabel(getHist_G_p[iter], titleSize, labelSize, "p_{T}D", 1.5, "Fraction of Total", 2.0);

    getHist_Q_p[iter]->DrawCopy();
    getHist_G_p[iter]->DrawCopy("SAME");
  }

  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%s%sPTDCanv", alg.c_str(), constAlg.c_str()), "pdf");

  delete label_p;
  delete plotCanvas_p;

  if(strcmp("", dataFileName.c_str()) != 0){
    for(Int_t iter = 0; iter < 4; iter++){
      delete getHist_Data_p[iter];
    }

    dataFile->Close();
    delete dataFile;
  }

  for(Int_t iter = 0; iter < 4; iter++){
    delete getHist_Tot_p[iter];
    delete getHist_Q_p[iter];
    delete getHist_G_p[iter];
  }

  f->Close();
  delete f;
  return;
}


void plotFastJetPTDHiBin(const std::string histFileName, const std::string alg, const std::string dataFileName = "")
{
  const Int_t titleSize = 20;
  const Int_t labelSize = 20;

  TFile* dataFile;
  TH1F* getHist_p[4];

  if(strcmp(dataFileName.c_str(), "") != 0){
    dataFile = new TFile(dataFileName.c_str(), "READ");
    getHist_p[2] = (TH1F*)dataFile->Get(Form("%sPFVsPTDHiBinHist_p", alg.c_str()));
    getHist_p[3] = (TH1F*)dataFile->Get(Form("%sPFRawPTDHiBinHist_p", alg.c_str()));

    niceTH1(getHist_p[2], 0.4999, 0.0001, 505, 505);
    niceTH1(getHist_p[3], 0.4999, 0.0001, 505, 505);

    getHist_p[2]->SetMarkerColor(kYellow-3);
    getHist_p[3]->SetMarkerColor(kMagenta+3);

    SetTitleLabel(getHist_p[2], titleSize, labelSize, "hiBin", 1.0, "<p_{T}D>", 1.5);
    SetTitleLabel(getHist_p[3], titleSize, labelSize, "hiBin", 1.0, "<p_{T}D>", 1.5);
  }


  TFile *f = new TFile(histFileName.c_str(), "UPDATE");
  getHist_p[0] = (TH1F*)f->Get(Form("%sPFVsPTDHiBinHist_p", alg.c_str()));
  getHist_p[1] = (TH1F*)f->Get(Form("%sPFRawPTDHiBinHist_p", alg.c_str()));


  TCanvas* plotCanvas_p = new TCanvas(Form("%sPTDHiBinCanv_c", alg.c_str()), Form("%sPTDHiBinCanv_c", alg.c_str()), 1*300, 1*350);

  niceTH1(getHist_p[0], 0.4999, 0.0001, 505, 505);
  niceTH1(getHist_p[1], 0.4999, 0.0001, 505, 505);

  getHist_p[0]->SetMarkerColor(kBlue);
  getHist_p[1]->SetMarkerColor(kRed);

  SetTitleLabel(getHist_p[0], titleSize, labelSize, "hiBin", 1.0, "<p_{T}D>", 1.5);
  SetTitleLabel(getHist_p[1], titleSize, labelSize, "hiBin", 1.0, "<p_{T}D>", 1.5);

  getHist_p[0]->DrawCopy("E1");
  getHist_p[1]->DrawCopy("E1 SAME");

  TLegend* leg_p = new TLegend(0.25, 0.35, 0.65, 0.55);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSizePixels(16);
  leg_p->SetBorderSize(0);

  leg_p->AddEntry(getHist_p[0], "Voronoi PF, P+H", "P");
  leg_p->AddEntry(getHist_p[1], "Unsubtracted PF, P+H", "P");

  if(strcmp(dataFileName.c_str(), "") != 0){
    getHist_p[2]->DrawCopy("E1 SAME");
    getHist_p[3]->DrawCopy("E1 SAME");

    leg_p->AddEntry(getHist_p[2], "Voronoi PF, Data", "P");
    leg_p->AddEntry(getHist_p[3], "Unsubtracted PF, Data", "P");
  }

  leg_p->Draw("SAME");

  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%sPTDHiBinCanv", alg.c_str()), "pdf");

  delete plotCanvas_p;

  if(strcmp(dataFileName.c_str(), "") != 0){
    dataFile->Close();
    delete dataFile;
  }

  f->Close();
  delete f;
  return;
}



void makeFastJetPlots(const std::string histFileName, Bool_t isMonteCarlo = false, const std::string dataFileName = "")
{
  TH1::SetDefaultSumw2();

  for(Int_t iter = 0; iter < 5; iter++){
    if(iter == 2) continue;
    
    plotFastJetPTD(histFileName, algType[iter], "PFVs", dataFileName);
    plotFastJetPTD(histFileName, algType[iter], "PFRaw", dataFileName);

    plotFastJetPTDHiBin(histFileName, algType[iter], dataFileName);
    plotFastJetPTDHiBin(histFileName, algType[iter], dataFileName);
  }
  return;
}
