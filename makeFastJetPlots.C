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


void plotFastJetPTDTau(const std::string histFileName, const std::string alg, const std::string constAlg, const std::string LeadSubLead, const std::string ptdTau, const std::string dataFileName = "")
{
  const Int_t titleSize = 24;
  const Int_t labelSize = 20;

  const std::string centString[4] = {"50100", "3050", "1030", "010"};
  const std::string centString2[4] = {"50-100%", "30-50%", "10-30%", "0-10%"};
  const std::string bBins[4] = {"b=0.0-8.5", "b=8.5-11.6", "b=11.6-14.0", "b=14.0-20.0"};


  TFile* dataFile;
  TH1F* getHist_Data_p[4];

  if(strcmp("", dataFileName.c_str()) != 0){
    dataFile = new TFile(dataFileName.c_str(), "READ");

    for(Int_t iter = 0; iter < 4; iter++){
      getHist_Data_p[iter] = (TH1F*)dataFile->Get(Form("%s%s%s%s_Tot_%s_h", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str(), centString[iter].c_str()));
      niceTH1(getHist_Data_p[iter], 0.5, 0.000, 505, 505);  
    }
  }


  TFile *f = new TFile(histFileName.c_str(), "UPDATE");

  TH1F* getHist_Tot_p[4];
  TH1F* getHist_Q_p[4];
  TH1F* getHist_G_p[4];

  for(Int_t iter = 0; iter < 4; iter++){
    std::cout << Form("%s%s%s%s_Tot_%s_h", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str(), centString[iter].c_str()) << std::endl;
    getHist_Tot_p[iter] = (TH1F*)f->Get(Form("%s%s%s%s_Tot_%s_h", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str(), centString[iter].c_str()));
    niceTH1(getHist_Tot_p[iter], 0.4999, 0.0001, 505, 505);

    getHist_Q_p[iter] = (TH1F*)f->Get(Form("%s%s%s%s_Q_%s_h", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str(), centString[iter].c_str()));
    niceTH1(getHist_Q_p[iter], 0.50, 0.00, 505, 505);

    getHist_G_p[iter] = (TH1F*)f->Get(Form("%s%s%s%s_G_%s_h", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str(), centString[iter].c_str()));
    niceTH1(getHist_G_p[iter], 0.50, 0.00, 505, 505);
  }

  TCanvas* plotCanvas_p = new TCanvas(Form("%s%s%s%s_c", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str()), Form("%s%s%s%s_c", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str()), 4*300, 1*350);
  plotCanvas_p->Divide(4, 1, 0.0, 0.0);

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(23);

  const std::string jetLabels[4] = {Form("Dijet selection w/ ak%s", alg.c_str()), Form("Recluster w/ %s", constAlg.c_str()), "anti-k_{t} Algorithm", "R = 0.4"};
  const std::string cutLabels[4] = {Form("p_{T}>%d GeV/c", totJtPtCut), "|#eta| < 2.0", "A_{J} Inclusive", Form("%s Jet", LeadSubLead.c_str())};

  const Float_t xPos[4] = {0.3, 0.2, 0.2, 0.2};

  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p->cd(iter+1); 
    SetTitleLabel(getHist_Tot_p[iter], titleSize, labelSize, ptdTau, 1.0, "EventFraction", 1.5);
    getHist_Tot_p[iter]->DrawCopy("HIST");

    getHist_Q_p[iter]->SetFillColor(kBlue-7);
    getHist_G_p[iter]->SetFillColor(kRed);

    SetTitleLabel(getHist_Q_p[iter], titleSize, labelSize, ptdTau, 1.5, "EventFraction", 2.0);
    SetTitleLabel(getHist_G_p[iter], titleSize, labelSize, ptdTau, 1.5, "EventFraction", 2.0);

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
    label_p->DrawLatex(xPos[iter], .92, jetLabels[iter].c_str());
    label_p->DrawLatex(xPos[iter], .84, centString2[3-iter].c_str());
    label_p->DrawLatex(xPos[iter], .76, cutLabels[iter].c_str());
  }

  TLegend* leg_p = new TLegend(0.50, 0.55, 0.75, 0.75);
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

  /*  
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

    getHist_Q_p[iter]->SetMarkerColor(kBlue-7);
    getHist_G_p[iter]->SetMarkerColor(kRed);

    SetTitleLabel(getHist_Q_p[iter], titleSize, labelSize, ptdTau, 1.5, "Fraction of Total", 2.0);
    SetTitleLabel(getHist_G_p[iter], titleSize, labelSize, ptdTau, 1.5, "Fraction of Total", 2.0);

    getHist_Q_p[iter]->DrawCopy();
    getHist_G_p[iter]->DrawCopy("SAME");
  }
  */

  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%s%s%s%s", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str()), "pdf");

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


void plotFastJetMeanPTDHiBin(const std::string histFileName, const std::string alg, const std::string LeadSubLead, const std::string dataFileName = "")
{
  const Int_t titleSize = 20;
  const Int_t labelSize = 20;

  TFile* dataFile;
  TH1F* getHist_p[4];

  if(strcmp(dataFileName.c_str(), "") != 0){
    dataFile = new TFile(dataFileName.c_str(), "READ");
    getHist_p[2] = (TH1F*)dataFile->Get(Form("%sPFVsPTDHiBin%s_h", alg.c_str(), LeadSubLead.c_str()));
    getHist_p[3] = (TH1F*)dataFile->Get(Form("%sPFRawPTDHiBin%s_h", alg.c_str(), LeadSubLead.c_str()));

    niceTH1(getHist_p[2], 0.4999, 0.0001, 505, 505);
    niceTH1(getHist_p[3], 0.4999, 0.0001, 505, 505);

    getHist_p[2]->SetMarkerColor(kYellow-3);
    getHist_p[3]->SetMarkerColor(kMagenta+3);

    SetTitleLabel(getHist_p[2], titleSize, labelSize, "hiBin", 1.0, "<p_{T}D>", 1.5);
    SetTitleLabel(getHist_p[3], titleSize, labelSize, "hiBin", 1.0, "<p_{T}D>", 1.5);
  }


  TFile *f = new TFile(histFileName.c_str(), "UPDATE");
  getHist_p[0] = (TH1F*)f->Get(Form("%sPFVsPTDHiBin%s_h", alg.c_str(), LeadSubLead.c_str()));
  getHist_p[1] = (TH1F*)f->Get(Form("%sPFRawPTDHiBin%s_h", alg.c_str(), LeadSubLead.c_str()));


  TCanvas* plotCanvas_p = new TCanvas(Form("%sMeanPTDHiBin%s_c", alg.c_str(), LeadSubLead.c_str()), Form("%sMeanPTDHiBin%s_c", alg.c_str(), LeadSubLead.c_str()), 1*300, 1*350);

  niceTH1(getHist_p[0], 0.4999, 0.0001, 505, 505);
  niceTH1(getHist_p[1], 0.4999, 0.0001, 505, 505);

  getHist_p[0]->SetMarkerColor(kBlue-7);
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

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(20);

  label_p->DrawLatex(.30, .60, Form("%s A_{J} Inclusive", LeadSubLead.c_str()));


  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%sMeanPTDHiBin%s", alg.c_str(), LeadSubLead.c_str()), "pdf");

  delete plotCanvas_p;

  if(strcmp(dataFileName.c_str(), "") != 0){
    dataFile->Close();
    delete dataFile;
  }

  f->Close();
  delete f;
  return;
}


void plotFastJetPTDTauHiBin(const std::string histFileName, const std::string alg, const std::string constAlg, const std::string LeadSubLead, const std::string ptdTau, const std::string dataFileName = "")
{
  const Int_t titleSize = 20;
  const Int_t labelSize = 20;

  const std::string centString[4] = {"50100", "3050", "1030", "010"};
  const std::string centString2[4] = {"50-100%", "30-50%", "10-30%", "0-10%"};

  std::string drawOpt[4] = {"E1" , "E1 SAME", "E1 SAME", "E1 SAME"};
  const Int_t colors[4] = {kBlue-7, kYellow+1, kOrange+7, kRed};

  TFile* dataFile;
  TH1F* getHist_Data_p[4];

  if(strcmp(dataFileName.c_str(), "") !=  0){
    dataFile = new TFile(dataFileName.c_str(), "READ");
    for(Int_t iter = 0; iter < 4; iter++){
      getHist_Data_p[iter] = (TH1F*)dataFile->Get(Form("%s%s%s%s_Tot_%s_h", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str(), centString[iter].c_str()));
      niceTH1(getHist_Data_p[iter], 0.50, 0.00, 505, 505);
      
      getHist_Data_p[iter]->SetMarkerColor(colors[iter]);
      SetTitleLabel(getHist_Data_p[iter], titleSize, labelSize, ptdTau.c_str(), 2.0, "EventFraction", 2.5);
    }
  }


  TFile* f = new TFile(histFileName.c_str(), "UPDATE");
  TH1F* getHist_MC_p[4];

  for(Int_t iter = 0; iter < 4; iter++){
    getHist_MC_p[iter] = (TH1F*)f->Get(Form("%s%s%s%s_Tot_%s_h", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str(), centString[iter].c_str()));
    niceTH1(getHist_MC_p[iter], 0.50, 0.00, 505, 505);

    getHist_MC_p[iter]->SetMarkerColor(colors[iter]);
    SetTitleLabel(getHist_MC_p[iter], titleSize, labelSize, ptdTau.c_str(), 2.0, "Event Fraction", 2.5);
  }

  TCanvas* plotCanvas_p = new TCanvas(Form("%s%s%sHiBin%s_c", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str()), Form("%s%s%sHiBin%s_c", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str()), 2*300, 2*350);
  plotCanvas_p->Divide(2, 2, 0.0, 0.0);

  plotCanvas_p->cd(1);

  TLegend* leg_p = new TLegend(0.60, 0.75, 0.95, 0.95);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSizePixels(12);
  leg_p->SetBorderSize(0);

  for(Int_t iter = 0; iter < 4; iter++){
    leg_p->AddEntry(getHist_MC_p[iter], Form("%s %s", constAlg.c_str(), centString2[iter].c_str()), "P");
    getHist_MC_p[iter]->DrawCopy(drawOpt[iter].c_str());
  }

  leg_p->Draw("SAME");

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(20);

  label_p->DrawLatex(.65, .65, "P+H");

  plotCanvas_p->cd(2);

  if(strcmp(dataFileName.c_str(),"") != 0){
    for(Int_t iter = 0; iter < 4; iter++){
      getHist_Data_p[iter]->DrawCopy(drawOpt[iter].c_str());
    }
  }

  label_p->DrawLatex(.50, .93, LeadSubLead.c_str());
  label_p->DrawLatex(.50, .85, "A_{J} Inclusive");
  label_p->DrawLatex(.50, .77, Form("p_{T}>%d; |#eta| < 2", totJtPtCut));
  label_p->DrawLatex(.50, .69, "PbPb");

  plotCanvas_p->cd(3);

  drawOpt[3] = "SAME HIST P";

  for(Int_t iter = 0; iter < 4; iter++){
    getHist_MC_p[3 - iter]->Divide(getHist_MC_p[0]);
    niceTH1(getHist_MC_p[3-iter], 2.999, 0.001, 504, 505);
    getHist_MC_p[3-iter]->SetMarkerColor(colors[3-iter]);
    SetTitleLabel(getHist_MC_p[3-iter], titleSize, labelSize, ptdTau.c_str(), 2.0, "Ratio w/ Peripheral", 2.5);
    getHist_MC_p[3-iter]->DrawCopy(drawOpt[iter].c_str());
  }

  plotCanvas_p->cd(4);

  if(strcmp(dataFileName.c_str(), "") != 0){
    for(Int_t iter = 0; iter < 4; iter++){
      getHist_Data_p[3 - iter]->Divide(getHist_Data_p[0]);
      niceTH1(getHist_Data_p[3-iter], 2.999, 0.001, 504, 505);
      getHist_Data_p[3-iter]->SetMarkerColor(colors[3-iter]);
      SetTitleLabel(getHist_Data_p[3-iter], titleSize, labelSize, ptdTau.c_str(), 2.0, "Ratio w/ Peripheral", 2.5);
      getHist_Data_p[3-iter]->DrawCopy(drawOpt[iter].c_str());
    }
  }

  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%s%s%sHiBin%s", alg.c_str(), constAlg.c_str(), ptdTau.c_str(), LeadSubLead.c_str()), "pdf");

  delete leg_p;
  delete plotCanvas_p;

  f->Close();
  delete f;

  if(strcmp(dataFileName.c_str(), "") != 0){
    dataFile->Close();
    delete dataFile;
  }

  return;
}


void plotFastJetSubRat(const std::string histFileName, const std::string alg, const std::string constAlg, const Int_t subRatNum, const std::string dataMC)
{
  const Int_t titleSize = 24;
  const Int_t labelSize = 20;

  const std::string centString[4] = {"50100", "3050", "1030", "010"};
  const std::string centString2[4] = {"50-100%", "30-50%", "10-30%", "0-10%"};
  const std::string LeadSubLead[2] = {"Leading", "Subleading"};
  const std::string drawOpt[2] = {"", "SAME"};

  const Int_t color[2] = {kRed, kBlue-7};


  TFile *f = new TFile(histFileName.c_str(), "UPDATE");

  TH1F* getHist_p[4][2];

  for(Int_t iter = 0; iter < 4; iter++){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      getHist_p[iter][subIter] = (TH1F*)f->Get(Form("%s%sSub%dRat%s_%s_h", alg.c_str(), constAlg.c_str(), subRatNum, LeadSubLead[subIter].c_str(), centString[iter].c_str()));
      niceTH1(getHist_p[iter][subIter], 0.40, 0.00, 505, 504);
      getHist_p[iter][subIter]->SetMarkerColor(color[subIter]);
    }
  }

  TCanvas* plotCanvas_p = new TCanvas(Form("%s%sSub%dRat_c", alg.c_str(), constAlg.c_str(), subRatNum), Form("%s%sSub%dRat_c", alg.c_str(), constAlg.c_str(), subRatNum), 4*300, 1*350);
  plotCanvas_p->Divide(4, 1, 0.0, 0.0);

  TLatex* label_p = new TLatex();
  label_p->SetNDC();
  label_p->SetTextFont(43);
  label_p->SetTextSizePixels(23);

  const std::string jetLabels[4] = {Form("Dijet selection w/ ak%s", alg.c_str()), Form("Recluster w/ %s", constAlg.c_str()), "CA Algorithm", "R = 0.3"};
  const std::string cutLabels[4] = {Form("p_{T}^{tot}>%d GeV/c", totJtPtCut), "p_{T}^{sub}>20 GeV/c", "|#eta| < 2.0", "A_{J} Inclusive"};

  for(Int_t iter = 0; iter < 4; iter++){
    plotCanvas_p->cd(iter+1);

    for(Int_t subIter = 0; subIter < 2; subIter++){
      SetTitleLabel(getHist_p[iter][subIter], titleSize, labelSize, "p_{T}^{sub}/p_{T,Tot}", 1.0, "EventFraction", 1.5);
      getHist_p[iter][subIter]->DrawCopy(drawOpt[subIter].c_str());
      //      drawMeanLine(getHist_p[iter][subIter]->GetMean());
    }

    label_p->DrawLatex(.3, .92, jetLabels[iter].c_str());
    label_p->DrawLatex(.3, .84, centString2[iter].c_str());
    label_p->DrawLatex(.3, .76, cutLabels[iter].c_str());
  }

  TLegend* leg_p = new TLegend(0.30, 0.45, 0.55, 0.75);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSizePixels(22);
  leg_p->SetBorderSize(0);

  leg_p->AddEntry(getHist_p[0][0], Form("p_{T,sub%d}/p_{T,1}", subRatNum), "P");
  leg_p->AddEntry(getHist_p[0][1], Form("p_{T,sub%d}/p_{T,2}", subRatNum), "P");

  plotCanvas_p->cd(1);
  leg_p->Draw("SAME");

  plotCanvas_p->Write("", TObject::kOverwrite);
  claverCanvasSaving(plotCanvas_p, Form("../FastJetHists/pdfDir/%s%sSub%dRat_%s", alg.c_str(), constAlg.c_str(), subRatNum, dataMC.c_str()), "pdf");

  delete label_p;
  delete plotCanvas_p;

  for(Int_t iter = 0; iter < 4; iter++){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      delete getHist_p[iter][subIter];
    }
  }

  f->Close();
  delete f;
  return;
}


void makeFastJetPlots(const std::string histFileName, Bool_t isMonteCarlo = false, const std::string dataFileName = "")
{
  TH1::SetDefaultSumw2();

  const std::string LeadSubLead[2] = {"Leading", "Subleading"};
  const std::string ptdTau[2] = {"PTD", "Tau21"};

  for(Int_t iter = 1; iter < 2; iter++){
    
    for(Int_t subIter = 0; subIter < 2; subIter++){

      for(Int_t ptdTauIter = 0; ptdTauIter < 2; ptdTauIter++){
	plotFastJetPTDTau(histFileName, algType[iter], "PFVs", LeadSubLead[subIter], ptdTau[ptdTauIter], dataFileName);
	plotFastJetPTDTau(histFileName, algType[iter], "PFRaw", LeadSubLead[subIter], ptdTau[ptdTauIter], dataFileName);
	//	plotFastJetPTDTauHiBin(histFileName, algType[iter], "GENRaw", LeadSubLead[subIter], ptdTau[ptdTauIter], dataFileName);
	//	plotFastJetPTDTauHiBin(histFileName, algType[iter], "PFRaw", LeadSubLead[subIter], ptdTau[ptdTauIter], dataFileName);
      }      

      //      plotFastJetMeanPTDHiBin(histFileName, algType[iter], LeadSubLead[subIter], dataFileName);
    }

    for(Int_t subRatIter = 0; subRatIter < 2; subRatIter++){    
      //      plotFastJetSubRat(histFileName, algType[iter], "PFVs", subRatIter+1, "MC");
      //      plotFastJetSubRat(dataFileName, algType[iter], "PFVs", subRatIter+1, "Data");
    }
  }

  return;
}
