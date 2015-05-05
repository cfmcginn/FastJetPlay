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

#include "FastJetPlot.h"

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};

const Int_t totJtPtCut = 50;

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


void drawMeanLine(Float_t histMean, Int_t lineStyle = 2, Int_t lineColor = 1)
{
  TLine* oneLine_p = new TLine(histMean, 0.0, histMean, 0.30);
  oneLine_p->SetLineColor(lineColor);
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


void plotFastJetPTDTauPanel(const std::string pbpbFileName, const std::string alg, const std::string ppFileName, const std::string hiMCFileName, const std::string ppMCFileName)
{
  TH1::SetDefaultSumw2();

  TFile* pbpbFile_p = new TFile(pbpbFileName.c_str(), "READ");

  rechitRawJt_HistPbPbTot_p = new JetSubstructHist();
  rechitVsJt_HistPbPbTot_p = new JetSubstructHist();

  pfRawJt_HistPbPbTot_p = new JetSubstructHist();
  pfVsJt_HistPbPbTot_p = new JetSubstructHist();
  pfSKJt_HistPbPbTot_p = new JetSubstructHist();

  trkRawJt_HistPbPbTot_p = new JetSubstructHist();
  trkSKJt_HistPbPbTot_p = new JetSubstructHist();

  TFile *ppFile_p = new TFile(ppFileName.c_str(), "UPDATE");

  rechitRawJt_HistPPTot_p = new JetSubstructHist();
  rechitVsJt_HistPPTot_p = new JetSubstructHist();

  pfRawJt_HistPPTot_p = new JetSubstructHist();
  pfVsJt_HistPPTot_p = new JetSubstructHist();
  pfSKJt_HistPPTot_p = new JetSubstructHist();

  trkRawJt_HistPPTot_p = new JetSubstructHist();
  trkSKJt_HistPPTot_p = new JetSubstructHist();

  TFile *ppMCFile_p = new TFile(ppMCFileName.c_str(), "UPDATE");

  rechitRawJt_HistPPMCTot_p = new JetSubstructHist();
  rechitVsJt_HistPPMCTot_p = new JetSubstructHist();

  rechitRawJt_HistPPMCQ_p = new JetSubstructHist();
  rechitVsJt_HistPPMCQ_p = new JetSubstructHist();

  rechitRawJt_HistPPMCG_p = new JetSubstructHist();
  rechitVsJt_HistPPMCG_p = new JetSubstructHist();

  pfRawJt_HistPPMCTot_p = new JetSubstructHist();
  pfVsJt_HistPPMCTot_p = new JetSubstructHist();
  pfSKJt_HistPPMCTot_p = new JetSubstructHist();

  pfRawJt_HistPPMCQ_p = new JetSubstructHist();
  pfVsJt_HistPPMCQ_p = new JetSubstructHist();
  pfSKJt_HistPPMCQ_p = new JetSubstructHist();

  pfRawJt_HistPPMCG_p = new JetSubstructHist();
  pfVsJt_HistPPMCG_p = new JetSubstructHist();
  pfSKJt_HistPPMCG_p = new JetSubstructHist();

  trkRawJt_HistPPMCTot_p = new JetSubstructHist();
  trkSKJt_HistPPMCTot_p = new JetSubstructHist();

  trkRawJt_HistPPMCQ_p = new JetSubstructHist();
  trkSKJt_HistPPMCQ_p = new JetSubstructHist();

  trkRawJt_HistPPMCG_p = new JetSubstructHist();
  trkSKJt_HistPPMCG_p = new JetSubstructHist();

  genRawJt_HistPPMCTot_p = new JetSubstructHist();
  genSKJt_HistPPMCTot_p = new JetSubstructHist();
  genSUBEJt_HistPPMCTot_p = new JetSubstructHist();

  genRawJt_HistPPMCQ_p = new JetSubstructHist();
  genSKJt_HistPPMCQ_p = new JetSubstructHist();
  genSUBEJt_HistPPMCQ_p = new JetSubstructHist();

  genRawJt_HistPPMCG_p = new JetSubstructHist();
  genSKJt_HistPPMCG_p = new JetSubstructHist();
  genSUBEJt_HistPPMCG_p = new JetSubstructHist();

  TFile *hiMCFile_p = new TFile(hiMCFileName.c_str(), "UPDATE");

  rechitRawJt_HistHIMCTot_p = new JetSubstructHist();
  rechitVsJt_HistHIMCTot_p = new JetSubstructHist();

  rechitRawJt_HistHIMCQ_p = new JetSubstructHist();
  rechitVsJt_HistHIMCQ_p = new JetSubstructHist();

  rechitRawJt_HistHIMCG_p = new JetSubstructHist();
  rechitVsJt_HistHIMCG_p = new JetSubstructHist();

  pfRawJt_HistHIMCTot_p = new JetSubstructHist();
  pfVsJt_HistHIMCTot_p = new JetSubstructHist();
  pfSKJt_HistHIMCTot_p = new JetSubstructHist();

  pfRawJt_HistHIMCQ_p = new JetSubstructHist();
  pfVsJt_HistHIMCQ_p = new JetSubstructHist();
  pfSKJt_HistHIMCQ_p = new JetSubstructHist();

  pfRawJt_HistHIMCG_p = new JetSubstructHist();
  pfVsJt_HistHIMCG_p = new JetSubstructHist();
  pfSKJt_HistHIMCG_p = new JetSubstructHist();

  trkRawJt_HistHIMCTot_p = new JetSubstructHist();
  trkSKJt_HistHIMCTot_p = new JetSubstructHist();

  trkRawJt_HistHIMCQ_p = new JetSubstructHist();
  trkSKJt_HistHIMCQ_p = new JetSubstructHist();

  trkRawJt_HistHIMCG_p = new JetSubstructHist();
  trkSKJt_HistHIMCG_p = new JetSubstructHist();

  genRawJt_HistHIMCTot_p = new JetSubstructHist();
  genSKJt_HistHIMCTot_p = new JetSubstructHist();
  genSUBEJt_HistHIMCTot_p = new JetSubstructHist();

  genRawJt_HistHIMCQ_p = new JetSubstructHist();
  genSKJt_HistHIMCQ_p = new JetSubstructHist();
  genSUBEJt_HistHIMCQ_p = new JetSubstructHist();

  genRawJt_HistHIMCG_p = new JetSubstructHist();
  genSKJt_HistHIMCG_p = new JetSubstructHist();
  genSUBEJt_HistHIMCG_p = new JetSubstructHist();

  TFile* dumFile_p[2] = {0, 0};

  GetHistForPlot(pbpbFile_p, ppFile_p, hiMCFile_p, ppMCFile_p, "VsCalo");

  TCanvas* plotCanvas_p[2];
  const Int_t nPanel = 5;
  const std::string panelLab[nPanel] = {"pp", "50-100%", "30-50%", "10-30%", "0-10%"};
  const std::string lead[2] = {"Lead", "Sublead"};

  for(Int_t iter = 0; iter < 2; iter++){
    plotCanvas_p[iter] = new TCanvas(Form("%s_pfVsTot_%s_c", alg.c_str(), lead[iter].c_str()), Form("%s_pfVsTot_%s_c", alg.c_str(), lead[iter].c_str()), nPanel*300, 2*350);
    plotCanvas_p[iter]->Divide(nPanel, 2, 0.0, 0.0);
  }

  TLine* oneLine_p;
  oneLine_p = new TLine(0., 1., .6, 1.);

  oneLine_p->SetLineColor(1);
  oneLine_p->SetLineStyle(2);

  Int_t error = 0;
  std::cout << error << std::endl;
  error++;

  plotCanvas_p[0]->cd(1);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->SetMaximum(.299);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->SetMinimum(.001);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->GetXaxis()->CenterTitle();
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->GetXaxis()->SetTitleOffset(1.5);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->GetYaxis()->CenterTitle();
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->GetYaxis()->SetTitleOffset(2.5);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->SetXTitle("z_{symm}; #beta=0");
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->SetYTitle("Event Fraction");
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->DrawCopy("E1 P");

  trkSKJt_HistPPMCTot_p->chgHist_p[0][0][0]->SetMarkerStyle(25);
  trkSKJt_HistPPMCTot_p->chgHist_p[0][0][0]->SetFillColor(18);
  trkSKJt_HistPPMCTot_p->chgHist_p[0][0][0]->DrawCopy("E1 HIST SAME");
  trkSKJt_HistPPMCTot_p->chgHist_p[0][0][0]->DrawCopy("E1 SAME");

  trkSKJt_HistPPMCQ_p->chgHist_p[0][0][0]->SetMarkerSize(0);
  trkSKJt_HistPPMCQ_p->chgHist_p[0][0][0]->SetFillColor(kBlue);
  trkSKJt_HistPPMCQ_p->chgHist_p[0][0][0]->Add(trkSKJt_HistPPMCG_p->chgHist_p[0][0][0]);
  trkSKJt_HistPPMCQ_p->chgHist_p[0][0][0]->DrawCopy("E1 HIST SAME");

  trkSKJt_HistPPMCG_p->chgHist_p[0][0][0]->SetMarkerSize(0);
  trkSKJt_HistPPMCG_p->chgHist_p[0][0][0]->SetFillColor(kRed);
  trkSKJt_HistPPMCG_p->chgHist_p[0][0][0]->DrawCopy("E1 HIST SAME");

  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->DrawCopy("E1 P SAME");

  std::cout << error << std::endl;
  error++;

  plotCanvas_p[1]->cd(1);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->SetMaximum(.299);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->SetMinimum(.001);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->GetXaxis()->CenterTitle();
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->GetXaxis()->SetTitleOffset(1.5);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->GetYaxis()->CenterTitle();
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->GetYaxis()->SetTitleOffset(2.5);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->SetXTitle("z_{symm}; #beta=0");
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->SetYTitle("Event Fraction");
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->DrawCopy("E1 P");

  trkSKJt_HistPPMCTot_p->chgHist_p[0][1][0]->SetMarkerStyle(25);
  trkSKJt_HistPPMCTot_p->chgHist_p[0][1][0]->SetFillColor(18);
  trkSKJt_HistPPMCTot_p->chgHist_p[0][1][0]->DrawCopy("E1 HIST SAME");
  trkSKJt_HistPPMCTot_p->chgHist_p[0][1][0]->DrawCopy("E1 SAME");

  trkSKJt_HistPPMCQ_p->chgHist_p[0][1][0]->SetMarkerSize(0);
  trkSKJt_HistPPMCQ_p->chgHist_p[0][1][0]->SetFillColor(kBlue);
  trkSKJt_HistPPMCQ_p->chgHist_p[0][1][0]->Add(trkSKJt_HistPPMCG_p->chgHist_p[0][1][0]);
  trkSKJt_HistPPMCQ_p->chgHist_p[0][1][0]->DrawCopy("E1 HIST SAME");

  trkSKJt_HistPPMCG_p->chgHist_p[0][1][0]->SetMarkerSize(0);
  trkSKJt_HistPPMCG_p->chgHist_p[0][1][0]->SetFillColor(kRed);
  trkSKJt_HistPPMCG_p->chgHist_p[0][1][0]->DrawCopy("E1 HIST SAME");

  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->DrawCopy("E1 P SAME");

  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p[0]->cd(iter+2);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->SetMaximum(.299);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->SetMinimum(.001);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->GetXaxis()->CenterTitle();
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->GetXaxis()->SetTitleOffset(1.5);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->SetXTitle("z_{symm}; #beta=0");
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->DrawCopy("E1 P");

    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][0][0]->SetMarkerStyle(25);
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][0][0]->SetFillColor(18);
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][0][0]->DrawCopy("E1 HIST SAME");
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][0][0]->DrawCopy("E1 SAME");

    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->DrawCopy("E1 P SAME");

    plotCanvas_p[0]->cd(iter+7);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->Divide(trkSKJt_HistPPTot_p->chgHist_p[0][0][2]);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->SetMaximum(1.499);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->SetMinimum(.501);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->DrawCopy("E1 P");

    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][0][0]->Divide(trkSKJt_HistPPMCTot_p->chgHist_p[0][0][2]);
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][0][0]->DrawCopy("E1 P SAME");

    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][0][0]->DrawCopy("E1 P SAME");

    oneLine_p->DrawClone();


    plotCanvas_p[1]->cd(iter+2);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->SetMaximum(.299);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->SetMinimum(.001);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->GetXaxis()->CenterTitle();
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->GetXaxis()->SetTitleOffset(1.5);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->SetXTitle("z_{symm}; #beta=0");
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->DrawCopy("E1 P");

    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][1][0]->SetMarkerStyle(25);
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][1][0]->SetFillColor(18);
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][1][0]->DrawCopy("E1 HIST SAME");
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][1][0]->DrawCopy("E1 SAME");

    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->DrawCopy("E1 P SAME");

    plotCanvas_p[1]->cd(iter+7);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->Divide(trkSKJt_HistPPTot_p->chgHist_p[0][1][2]);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->SetMaximum(1.499);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->SetMinimum(0.501);
    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->DrawCopy("E1 P");

    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][1][0]->Divide(trkSKJt_HistPPMCTot_p->chgHist_p[0][0][2]);
    trkSKJt_HistHIMCTot_p->chgHist_p[3-iter][1][0]->DrawCopy("E1 P SAME");

    trkSKJt_HistPbPbTot_p->chgHist_p[3-iter][1][0]->DrawCopy("E1 P SAME");
    oneLine_p->DrawClone();
  }

  plotCanvas_p[0]->cd(6);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->Divide(trkSKJt_HistPPTot_p->chgHist_p[0][0][2]);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->SetMaximum(1.499);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->SetMinimum(.501);
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->SetYTitle("Ratio");
  trkSKJt_HistPPTot_p->chgHist_p[0][0][0]->DrawCopy("E1 P");
  oneLine_p->DrawClone();

  plotCanvas_p[1]->cd(6);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->Divide(trkSKJt_HistPPTot_p->chgHist_p[0][1][2]);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->SetMaximum(1.499);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->SetMinimum(.501);
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->SetYTitle("Ratio");
  trkSKJt_HistPPTot_p->chgHist_p[0][1][0]->DrawCopy("E1 P");
  oneLine_p->DrawClone();

  TLatex* label1_p = new TLatex();
  label1_p->SetNDC();
  label1_p->SetTextFont(43);
  label1_p->SetTextSizePixels(28);

  for(Int_t iter = 0; iter < nPanel; iter++){
    for(Int_t iter2 = 0; iter2 < 2; iter2++){
      plotCanvas_p[iter2]->cd(iter+1);
      label1_p->DrawLatex(.58, .7, Form("%s", panelLab[iter].c_str()));
      if(iter == 0) label1_p->DrawLatex(.58, .6, Form("%s", lead[iter2].c_str()));
    }
  }


  TFile* outFile_p = new TFile("testPlot.root", "RECREATE");
  plotCanvas_p[0]->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p[0], Form("../FastJetHists/pdfDir/%s_trkSKTot_Lead", alg.c_str()), "pdf");
  plotCanvas_p[1]->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p[1], Form("../FastJetHists/pdfDir/%s_trkSKTot_Sublead", alg.c_str()), "pdf");
  outFile_p->Close();
  delete outFile_p;

  delete plotCanvas_p[0];
  delete plotCanvas_p[1];

  ppFile_p->Close();
  delete ppFile_p;

  pbpbFile_p->Close();
  delete pbpbFile_p;

  return;
}


void makeFastJetPlots(const std::string pbpbFileName, const std::string ppFileName, const std::string hiMCFileName, const std::string ppMCFileName)
{
  TH1::SetDefaultSumw2();

  plotFastJetPTDTauPanel(pbpbFileName, "VsCalo", ppFileName, hiMCFileName, ppMCFileName);

  
  return;
}
