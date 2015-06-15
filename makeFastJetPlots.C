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
#include "jetSuperSubstruct.h"

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};

const Int_t totJtPtCut = 50;

void handsomeTH1( TH1 *a=0, Int_t col =1, Float_t size=1, Int_t markerstyle=20)
{
  a->SetMarkerColor(col);
  a->SetMarkerSize(size);
  a->SetMarkerStyle(markerstyle);
  a->SetLineColor(col);

  return;
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

  return;
}


void drawMeanLine(Float_t histMean, Int_t lineStyle = 2, Int_t lineColor = 1)
{
  TLine* oneLine_p = new TLine(histMean, 0.0, histMean, 0.30);
  oneLine_p->SetLineColor(lineColor);
  oneLine_p->SetLineStyle(lineStyle);

  oneLine_p->Draw("Same");

  return;
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

  return;
}


Float_t GetRangeLow(TH1F* inHist_p)
{
  return inHist_p->GetXaxis()->GetBinLowEdge(inHist_p->GetXaxis()->GetFirst());
}



Float_t GetRangeHi(TH1F* inHist_p)
{
  return inHist_p->GetXaxis()->GetBinUpEdge(inHist_p->GetXaxis()->GetLast());
}


void plotFastJetPTDTauPanel(JetSuperSubstructHist* inStruct_p, const std::string alg, const std::string alg2, const Int_t histNum, const Bool_t isPbPb, const Bool_t isPP, const Bool_t isHIMC, const Bool_t isPPMC)
{
  TH1::SetDefaultSumw2();

  const Int_t nSub = nTH1Sub_[histNum];
  const std::string plotStr = th1Str_[histNum];
  std::cout << "A" << std::endl;
  inStruct_p->StandardizeTH1(histNum);
  inStruct_p->StandardizeMeanTH1(histNum);
  std::cout << "B" << std::endl;

  TFile* outFile_p = new TFile("testPlot.root", "UPDATE");
  TCanvas* plotCanvas_p[histJtMax][nSub];
  TCanvas* plotCanvasMean_p[histJtMax];
  Int_t nPanel_Temp = 1;
  Int_t nPanel_Temp2 = 1;
  if(isPbPb || isHIMC){
    nPanel_Temp += centHIMax;
    nPanel_Temp2 = 2;
  }
  
  const Int_t nPanel = nPanel_Temp;
  const Int_t nPanel2 = nPanel_Temp2;
  const std::string panelLab[3] = {"pp", "30-100%", "0-30%"};
  //  const Int_t nPanel = 5;
  //  const std::string panelLab[nPanel] = {"pp", "50-100%", "30-50%", "10-30%", "0-10%"};
  std::string lead[histJtMax];
  lead[0] = "Lead"; 
  if(histJtMax > 1) lead[1] = "Sublead";
  
  for(Int_t iter = 2; iter < histJtMax; iter++){
    lead[iter] = Form("%d", iter);
  }
  
  for(Int_t iter = 0; iter < histJtMax; iter++){
    plotCanvasMean_p[iter] = new TCanvas(Form("%s_%s_%s_%s_Mean_c", alg.c_str(), alg2.c_str(), lead[iter].c_str(), plotStr.c_str()), Form("%s_%s_%s_%s_Mean_c", alg.c_str(), alg2.c_str(), lead[iter].c_str(), plotStr.c_str()), nPanel*300, nPanel2*350);
    plotCanvasMean_p[iter]->Divide(nPanel, nPanel2, 0.0, 0.0);

    for(Int_t iter2 = 0; iter2 < nSub; iter2++){
      plotCanvas_p[iter][iter2] = new TCanvas(Form("%s_%s_%s_%s%d_c", alg.c_str(), alg2.c_str(), lead[iter].c_str(), plotStr.c_str(), iter2), Form("%s_%s_%s_%s%d_c", alg.c_str(), alg2.c_str(), lead[iter].c_str(), plotStr.c_str(), iter2), nPanel*300, nPanel2*350);
      plotCanvas_p[iter][iter2]->Divide(nPanel, nPanel2, 0.0, 0.0);
      //      std::cout << "Plot Canv: " << plotCanvas_p[iter][iter2]->GetName() << std::endl;
    }
  }

  TLine* oneLine_p;
  Float_t oneLineXLow = 0;
  Float_t oneLineXHi = 0;
  
  inStruct_p->SetSuperActiveTH1(histNum, 0, 0, 0);
  if(isPP){
    oneLineXLow = GetRangeLow(inStruct_p->ppStruct_p->activeTH1_p);
    oneLineXHi = GetRangeHi(inStruct_p->ppStruct_p->activeTH1_p);
  }
  else if(isPPMC){
    oneLineXLow = GetRangeLow(inStruct_p->ppMCTotStruct_p->activeTH1_p);
    oneLineXHi = GetRangeHi(inStruct_p->ppMCTotStruct_p->activeTH1_p);
  }
  else if(isPbPb){
    oneLineXLow = GetRangeLow(inStruct_p->pbpbStruct_p->activeTH1_p);
    oneLineXHi = GetRangeHi(inStruct_p->pbpbStruct_p->activeTH1_p);
  }
  else if(isHIMC){
    oneLineXLow = GetRangeLow(inStruct_p->hiMCTotStruct_p->activeTH1_p);
    oneLineXHi = GetRangeHi(inStruct_p->hiMCTotStruct_p->activeTH1_p);
  }  

  oneLine_p = new TLine(oneLineXLow, 1, oneLineXHi, 1);
  
  oneLine_p->SetLineColor(1);
  oneLine_p->SetLineStyle(2);
      
  std::cout << "A" << std::endl;

  Float_t ratMax = 0;
  Float_t ratMin = 1000000;

  const Int_t nLeg1 = 10;
  TH1F* legHist1_p[nLeg1];
  const Bool_t legBool1[nLeg1] = {isPP, isPbPb, isPP && isPbPb, isPPMC, isHIMC, isPPMC && isHIMC, isPPMC || isHIMC, isPPMC || isHIMC, inStruct_p->isGenPP_, inStruct_p->isGenHI_};
  const std::string legStr1[nLeg1] = {"pp", "PbPb", "PbPb/pp", "PYT.", "PYT.+HYD.", "PYT.+HYD./PYT", "QUARKS!", "gluons?", "Gen. PYT.", "Gen. PYT.+HYD."};


  for(Int_t plotIter = 0; plotIter < histJtMax; plotIter++){
    TH1F ppTotMean_h;
    TH1F ppMCTotMean_h;

    if(isPP) ppTotMean_h = inStruct_p->ppStruct_p->GetActiveMeanTH1(histNum, 0, plotIter);
    if(isPPMC) ppMCTotMean_h = inStruct_p->ppMCTotStruct_p->GetActiveMeanTH1(histNum, 0, plotIter);

    plotCanvasMean_p[plotIter]->cd(1);

    if(isPP) ppTotMean_h.DrawCopy("E1 P");
    if(isPPMC){
      if(!isPP) ppMCTotMean_h.DrawCopy("E1 P");
      else ppMCTotMean_h.DrawCopy("E1 SAME P");
      ppMCTotMean_h.DrawCopy("E1 SAME P");
    }
    if(isPP) ppTotMean_h.DrawCopy("E1 P SAME");

    for(Int_t iter = 0; iter < nPanel-1; iter++){
      TH1F pbpbTotMean_h;
      TH1F hiMCTotMean_h;
      if(isPbPb) pbpbTotMean_h = inStruct_p->pbpbStruct_p->GetActiveMeanTH1(histNum, nPanel - 2 - iter, plotIter);
      if(isHIMC) hiMCTotMean_h = inStruct_p->hiMCTotStruct_p->GetActiveMeanTH1(histNum, nPanel - 2 - iter, plotIter);
      //EDIT HERE
      plotCanvasMean_p[plotIter]->cd(iter+2);

      if(isPbPb) pbpbTotMean_h.DrawCopy("E1 P");
      if(isHIMC){
	if(!isPbPb) hiMCTotMean_h.DrawCopy("E1 P");
	else hiMCTotMean_h.DrawCopy("E1 SAME P");
	hiMCTotMean_h.DrawCopy("E1 SAME");
      }
      if(isPbPb) pbpbTotMean_h.DrawCopy("E1 P SAME");
    }


    for(Int_t subIter = 0; subIter < nSub; subIter++){
      TH1F ppTot_h;
      TH1F ppMCTot_h;
      TH1F ppMCQ_h;
      TH1F ppMCG_h;
      //Edit

      TH1F genPP_h;

      if(isPP) ppTot_h = inStruct_p->ppStruct_p->GetActiveTH1(histNum, 0, plotIter, subIter);
      if(isPPMC){
	ppMCTot_h = inStruct_p->ppMCTotStruct_p->GetActiveTH1(histNum, 0, plotIter, subIter);
	ppMCQ_h = inStruct_p->ppMCQStruct_p->GetActiveTH1(histNum, 0, plotIter, subIter);
	ppMCG_h = inStruct_p->ppMCGStruct_p->GetActiveTH1(histNum, 0, plotIter, subIter);

	std::cout << "YOLO" << std::endl;
	std::cout << ppMCTot_h.GetName() << std::endl;
      }
      if(inStruct_p->isGenPP_) genPP_h = inStruct_p->genPPStruct_p->GetActiveTH1(histNum, 0, plotIter, subIter);

      legHist1_p[0] = (TH1F*)ppTot_h.Clone();
      legHist1_p[3] = (TH1F*)ppMCTot_h.Clone();
      legHist1_p[6] = (TH1F*)ppMCQ_h.Clone();
      legHist1_p[7] = (TH1F*)ppMCG_h.Clone();

      legHist1_p[8] = (TH1F*)genPP_h.Clone();

      plotCanvas_p[plotIter][subIter]->cd(1);
      if(histNum == 10 || histNum == 11 || histNum == 12) gPad->SetLogx();

      if(isPP) ppTot_h.DrawCopy("E1 P");
      if(isPPMC){
	if(!isPP) ppMCTot_h.DrawCopy("E1 HIST");
	else ppMCTot_h.DrawCopy("E1 SAME HIST");
	ppMCTot_h.DrawCopy("E1 SAME");
		
	ppMCQ_h.Add(&ppMCG_h);
	ppMCQ_h.DrawCopy("E1 HIST SAME");
		
	ppMCG_h.DrawCopy("E1 HIST SAME");
      }
      
      if(isPP) ppTot_h.DrawCopy("E1 P SAME");

      if(inStruct_p->isGenPP_) genPP_h.DrawCopy("E1 P SAME");

      for(Int_t iter = 0; iter < nPanel-1; iter++){
	TH1F pbpbTot_h;
	TH1F hiMCTot_h;
	TH1F hiMCQ_h;
	TH1F hiMCG_h;

	TH1F genHI_h;
	
	if(isPbPb) pbpbTot_h = inStruct_p->pbpbStruct_p->GetActiveTH1(histNum, nPanel - 2 -iter, plotIter, subIter);
	if(isHIMC){
	  hiMCTot_h = inStruct_p->hiMCTotStruct_p->GetActiveTH1(histNum, nPanel - 2 - iter, plotIter, subIter);
	  hiMCQ_h = inStruct_p->hiMCQStruct_p->GetActiveTH1(histNum, nPanel - 2 - iter, plotIter, subIter);
	  hiMCG_h = inStruct_p->hiMCGStruct_p->GetActiveTH1(histNum, nPanel - 2 - iter, plotIter, subIter);
	}
	if(inStruct_p->isGenHI_) genHI_h = inStruct_p->genHIStruct_p->GetActiveTH1(histNum, nPanel - 2 - iter, plotIter, subIter);


	if(iter == 0){
	  legHist1_p[1] = (TH1F*)pbpbTot_h.Clone();
	  legHist1_p[4] = (TH1F*)hiMCTot_h.Clone();
	  legHist1_p[9] = (TH1F*)genHI_h.Clone();
	}

	plotCanvas_p[plotIter][subIter]->cd(iter+2);
	if(histNum == 10 || histNum == 11 || histNum == 12) gPad->SetLogx();

	if(isPbPb) pbpbTot_h.DrawCopy("E1 P");
	if(isHIMC){
	  if(!isPbPb) hiMCTot_h.DrawCopy("E1 HIST");
	  else hiMCTot_h.DrawCopy("E1 SAME HIST");
	  hiMCTot_h.DrawCopy("E1 SAME");
	  
	  hiMCQ_h.Add(&hiMCG_h);
	  hiMCQ_h.DrawCopy("E1 HIST SAME");
	  
	  hiMCG_h.DrawCopy("E1 HIST SAME");
	}
	
	if(isPbPb) pbpbTot_h.DrawCopy("E1 P SAME");
	
	if(inStruct_p->isGenHI_) genHI_h.DrawCopy("E1 P SAME");

	plotCanvas_p[plotIter][subIter]->cd(iter+2+nPanel);
	if(histNum == 10 || histNum == 11 || histNum == 12) gPad->SetLogx();
	
	if(isPbPb && isPP){
	  pbpbTot_h.Divide(&ppTot_h);
	  for(Int_t valIter = 0; valIter < pbpbTot_h.GetNbinsX(); valIter++){
	    if(pbpbTot_h.GetBinContent(valIter+1) == 0) continue;
	    if(pbpbTot_h.GetBinContent(valIter+1) + pbpbTot_h.GetBinError(valIter+1) > ratMax) ratMax = pbpbTot_h.GetBinContent(valIter+1) + pbpbTot_h.GetBinError(valIter+1);
	    if(pbpbTot_h.GetBinContent(valIter+1) - pbpbTot_h.GetBinError(valIter+1) < ratMin) ratMin = pbpbTot_h.GetBinContent(valIter+1) - pbpbTot_h.GetBinError(valIter+1);
	  }
	}
	if(isHIMC && isPPMC){
	  hiMCTot_h.Divide(&ppMCTot_h);
	  for(Int_t valIter = 0; valIter < hiMCTot_h.GetNbinsX(); valIter++){
	    if(hiMCTot_h.GetBinContent(valIter+1) == 0) continue;
	    if(hiMCTot_h.GetBinContent(valIter+1) + hiMCTot_h.GetBinError(valIter+1) > ratMax) ratMax = hiMCTot_h.GetBinContent(valIter+1) + hiMCTot_h.GetBinError(valIter+1);
	    if(hiMCTot_h.GetBinContent(valIter+1) - hiMCTot_h.GetBinError(valIter+1) < ratMin) ratMin = hiMCTot_h.GetBinContent(valIter+1) - hiMCTot_h.GetBinError(valIter+1);
	  }
	}
      }
    }
  }

  if(ratMax > 2) ratMax = 2;
  if(ratMin < 0) ratMin = 0.0001;

  for(Int_t plotIter = 0; plotIter < histJtMax; plotIter++){
    for(Int_t subIter = 0; subIter < nSub; subIter++){
      TH1F ppTot_h;
      TH1F ppMCTot_h;
      TH1F ppMCQ_h;
      TH1F ppMCG_h;
      //Edit
      
      if(isPP) ppTot_h = inStruct_p->ppStruct_p->GetActiveTH1(histNum, 0, plotIter, subIter);
      if(isPPMC) ppMCTot_h = inStruct_p->ppMCTotStruct_p->GetActiveTH1(histNum, 0, plotIter, subIter);

      for(Int_t iter = 0; iter < nPanel-1; iter++){
	TH1F pbpbTot_h;
	TH1F hiMCTot_h;
	TH1F hiMCQ_h;
	TH1F hiMCG_h;
	
	if(isPbPb) pbpbTot_h = inStruct_p->pbpbStruct_p->GetActiveTH1(histNum, nPanel - 2 -iter, plotIter, subIter);
	if(isHIMC) hiMCTot_h = inStruct_p->hiMCTotStruct_p->GetActiveTH1(histNum, nPanel - 2 - iter, plotIter, subIter);
	
	plotCanvas_p[plotIter][subIter]->cd(iter+2+nPanel);
	if(histNum == 10 || histNum == 11 || histNum == 12) gPad->SetLogx();
       	
	if(isPbPb && isPP){
	  pbpbTot_h.Divide(&ppTot_h);
	  pbpbTot_h.SetMaximum(ratMax);
	  pbpbTot_h.SetMinimum(ratMin);
	  pbpbTot_h.SetMarkerStyle(34);
	  pbpbTot_h.DrawCopy("E1 P");
	}
	if(isHIMC && isPPMC){
	  hiMCTot_h.Divide(&ppMCTot_h);
	  hiMCTot_h.SetMaximum(ratMax);
	  hiMCTot_h.SetMinimum(ratMin);
	  hiMCTot_h.SetMarkerStyle(28);
	  if(!isPbPb && ! isPP) hiMCTot_h.DrawCopy("E1 P");
	  else hiMCTot_h.DrawCopy("E1 P SAME");
	}
	if(isPbPb && isPP) pbpbTot_h.DrawCopy("E1 P SAME");
	
	if(isHIMC || isPbPb) oneLine_p->DrawClone();

	if(iter == 0){
	  legHist1_p[2] = (TH1F*)pbpbTot_h.Clone();
	  legHist1_p[5] = (TH1F*)hiMCTot_h.Clone();
	}
      }
      
      if(isPP){
	plotCanvas_p[plotIter][subIter]->cd(nPanel+1);
	if(histNum == 10 || histNum == 11 || histNum == 12) gPad->SetLogx();
	ppTot_h.Divide(&ppTot_h);
	ppTot_h.SetMaximum(ratMax);
	ppTot_h.SetMinimum(ratMin);
	ppTot_h.SetYTitle("Ratio");
	ppTot_h.SetMarkerColor(0);
	ppTot_h.SetLineColor(0);
	ppTot_h.DrawCopy("E1 P");
	//	oneLine_p->DrawClone();
      }
      if(isPPMC){
	plotCanvas_p[plotIter][subIter]->cd(nPanel+1);
	if(histNum == 10 || histNum == 11 || histNum == 12) gPad->SetLogx();
        ppMCTot_h.Divide(&ppMCTot_h);
        ppMCTot_h.SetMaximum(ratMax);
        ppMCTot_h.SetMinimum(ratMin);
        ppMCTot_h.SetYTitle("Ratio");
	ppMCTot_h.SetMarkerColor(0);
	ppMCTot_h.SetLineColor(0);
        if(!isPP) ppMCTot_h.DrawCopy("E1 P");
	else ppMCTot_h.DrawCopy("E1 P SAME");
	//       oneLine_p->DrawClone();
      }  
    }
  }


  TLatex* label1_p = new TLatex();
  label1_p->SetNDC();
  label1_p->SetTextFont(43);
  label1_p->SetTextSizePixels(28);


  TLegend* leg1_p = new TLegend(0.25, 0.55, 0.55, 0.95);
  leg1_p->SetFillColor(0);
  leg1_p->SetFillStyle(0);
  leg1_p->SetTextFont(43);
  leg1_p->SetTextSizePixels(28);
  leg1_p->SetBorderSize(0);

  TLegend* leg2_p = new TLegend(0.25, 0.25, 0.75, 0.45);
  leg2_p->SetFillColor(0);
  leg2_p->SetFillStyle(0);
  leg2_p->SetTextFont(43);
  leg2_p->SetTextSizePixels(28);
  leg2_p->SetBorderSize(0);

  for(Int_t iter = 0; iter < nLeg1; iter++){
    if(iter == nLeg1 - 4 || iter == nLeg1 - 3) continue;
    if(legBool1[iter]) leg1_p->AddEntry(legHist1_p[iter], Form("%s", legStr1[iter].c_str()), "P L");
  }

  for(Int_t iter = nLeg1-4; iter < nLeg1-2; iter++){
    if(legBool1[iter]) leg2_p->AddEntry(legHist1_p[iter], Form("%s", legStr1[iter].c_str()), "F");
  }

  for(Int_t iter = 0; iter < nPanel; iter++){
    for(Int_t plotIter = 0; plotIter < histJtMax; plotIter++){
      plotCanvasMean_p[plotIter]->cd(iter+1);
      label1_p->DrawLatex(.58, .7, Form("%s", panelLab[iter].c_str()));
      if(iter == 0) label1_p->DrawLatex(.58, .6, Form("%s", lead[plotIter].c_str()));

      for(Int_t subIter = 0; subIter < nSub; subIter++){
	plotCanvas_p[plotIter][subIter]->cd(iter+1);

	label1_p->DrawLatex(.58, .7, Form("%s", panelLab[iter].c_str()));
	if(iter == 0) label1_p->DrawLatex(.58, .6, Form("%s", lead[plotIter].c_str()));

	if(iter == 0){
	  plotCanvas_p[plotIter][subIter]->cd(nPanel+1);
	  leg1_p->Draw("SAME");
	  leg2_p->Draw("SAME");
	}
      }
    }  
  }

  outFile_p->cd();
  for(Int_t plotIter = 0; plotIter < histJtMax; plotIter++){
    plotCanvasMean_p[plotIter]->Write("", TObject::kOverwrite);
    claverCanvasSaving(plotCanvasMean_p[plotIter], Form("../FastJetHists/pdfDir/%s_%s_%s_%s_Mean", alg.c_str(), alg2.c_str(), lead[plotIter].c_str(), plotStr.c_str()), "pdf");

    for(Int_t subIter = 0; subIter < nSub; subIter++){      
      plotCanvas_p[plotIter][subIter]->Write("", TObject::kOverwrite);
      claverCanvasSaving(plotCanvas_p[plotIter][subIter], Form("../FastJetHists/pdfDir/%s_%s_%s_%s%d", alg.c_str(), alg2.c_str(), lead[plotIter].c_str(), plotStr.c_str(), subIter), "pdf");
    }
  }
  outFile_p->Close();
  delete outFile_p;

  //  delete leg1_p;

  for(Int_t plotIter = 0; plotIter < histJtMax; plotIter++){
    delete plotCanvasMean_p[plotIter];

    for(Int_t subIter = 0; subIter < nSub; subIter++){
      delete plotCanvas_p[plotIter][subIter];
    }
  }

  return;
}


void makeFastJetPlots(const std::string pbpbFileName, const std::string ppFileName, const std::string hiMCFileName, const std::string ppMCFileName)
{
  TH1::SetDefaultSumw2();

  Bool_t isPbPb = strcmp(pbpbFileName.c_str(), "") != 0;
  Bool_t isPP = strcmp(ppFileName.c_str(), "") != 0;
  Bool_t isHIMC = strcmp(hiMCFileName.c_str(), "") != 0;
  Bool_t isPPMC = strcmp(ppMCFileName.c_str(), "") != 0;

  TFile* pbpbFile_p = 0;
  TFile *ppFile_p = 0;
  TFile *ppMCFile_p = 0;
  TFile *hiMCFile_p = 0;

  if(isPbPb){
    pbpbFile_p = new TFile(pbpbFileName.c_str(), "READ");

    rechitRawJt_HistPbPbTot_p = new JetSubstructHist();
    rechitVsJt_HistPbPbTot_p = new JetSubstructHist();

    pfRawJt_HistPbPbTot_p = new JetSubstructHist();
    pfVsJt_HistPbPbTot_p = new JetSubstructHist();
    pfSKJt_HistPbPbTot_p = new JetSubstructHist();

    trkRawJt_HistPbPbTot_p = new JetSubstructHist();
    trkSKJt_HistPbPbTot_p = new JetSubstructHist();
    trk3CutJt_HistPbPbTot_p = new JetSubstructHist();
  }
  if(isPP){
    ppFile_p = new TFile(ppFileName.c_str(), "UPDATE");

    rechitRawJt_HistPPTot_p = new JetSubstructHist();
    rechitVsJt_HistPPTot_p = new JetSubstructHist();

    pfRawJt_HistPPTot_p = new JetSubstructHist();
    pfVsJt_HistPPTot_p = new JetSubstructHist();
    pfSKJt_HistPPTot_p = new JetSubstructHist();

    trkRawJt_HistPPTot_p = new JetSubstructHist();
    trkSKJt_HistPPTot_p = new JetSubstructHist();
    trk3CutJt_HistPPTot_p = new JetSubstructHist();
  }
  if(isPPMC){
    ppMCFile_p = new TFile(ppMCFileName.c_str(), "UPDATE");
  
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
    trk3CutJt_HistPPMCTot_p = new JetSubstructHist();

    trkRawJt_HistPPMCQ_p = new JetSubstructHist();
    trkSKJt_HistPPMCQ_p = new JetSubstructHist();
    trk3CutJt_HistPPMCQ_p = new JetSubstructHist();

    trkRawJt_HistPPMCG_p = new JetSubstructHist();
    trkSKJt_HistPPMCG_p = new JetSubstructHist();
    trk3CutJt_HistPPMCG_p = new JetSubstructHist();

    genRawJt_HistPPMCTot_p = new JetSubstructHist();
    genSKJt_HistPPMCTot_p = new JetSubstructHist();
    genSUBEJt_HistPPMCTot_p = new JetSubstructHist();

    genRawJt_HistPPMCQ_p = new JetSubstructHist();
    genSKJt_HistPPMCQ_p = new JetSubstructHist();
    genSUBEJt_HistPPMCQ_p = new JetSubstructHist();

    genRawJt_HistPPMCG_p = new JetSubstructHist();
    genSKJt_HistPPMCG_p = new JetSubstructHist();
    genSUBEJt_HistPPMCG_p = new JetSubstructHist();

    T_genSUBEJt_HistPPMCTot_p = new JetSubstructHist();
  }
  if(isHIMC){
    hiMCFile_p = new TFile(hiMCFileName.c_str(), "UPDATE");
  
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
    trk3CutJt_HistHIMCTot_p = new JetSubstructHist();

    trkRawJt_HistHIMCQ_p = new JetSubstructHist();
    trkSKJt_HistHIMCQ_p = new JetSubstructHist();
    trk3CutJt_HistHIMCQ_p = new JetSubstructHist();

    trkRawJt_HistHIMCG_p = new JetSubstructHist();
    trkSKJt_HistHIMCG_p = new JetSubstructHist();
    trk3CutJt_HistHIMCG_p = new JetSubstructHist();

    genRawJt_HistHIMCTot_p = new JetSubstructHist();
    genSKJt_HistHIMCTot_p = new JetSubstructHist();
    genSUBEJt_HistHIMCTot_p = new JetSubstructHist();

    genRawJt_HistHIMCQ_p = new JetSubstructHist();
    genSKJt_HistHIMCQ_p = new JetSubstructHist();
    genSUBEJt_HistHIMCQ_p = new JetSubstructHist();

    genRawJt_HistHIMCG_p = new JetSubstructHist();
    genSKJt_HistHIMCG_p = new JetSubstructHist();
    genSUBEJt_HistHIMCG_p = new JetSubstructHist();

    T_genSUBEJt_HistHIMCTot_p = new JetSubstructHist();
  }

  JetSuperSubstructHist* genSUBE_p = new JetSuperSubstructHist();
  genSUBE_p->isPP_ = false;
  genSUBE_p->isPPMC_ = isPPMC;
  genSUBE_p->isPbPb_ = false;
  genSUBE_p->isHIMC_ = isHIMC;
  genSUBE_p->isGenPP_ = false;
  genSUBE_p->isGenHI_ = false;

  genSUBE_p->hiMCTotStruct_p = genSUBEJt_HistHIMCTot_p;
  genSUBE_p->hiMCQStruct_p = genSUBEJt_HistHIMCQ_p;
  genSUBE_p->hiMCGStruct_p = genSUBEJt_HistHIMCG_p;

  genSUBE_p->ppMCTotStruct_p = genSUBEJt_HistPPMCTot_p;
  genSUBE_p->ppMCQStruct_p = genSUBEJt_HistPPMCQ_p;
  genSUBE_p->ppMCGStruct_p = genSUBEJt_HistPPMCG_p;

  JetSuperSubstructHist* genRaw_p = new JetSuperSubstructHist();
  genRaw_p->isPP_ = false;
  genRaw_p->isPPMC_ = isPPMC;
  genRaw_p->isPbPb_ = false;
  genRaw_p->isHIMC_ = isHIMC;
  genRaw_p->isGenPP_ = true;
  genRaw_p->isGenHI_ = true;

  genRaw_p->hiMCTotStruct_p = genRawJt_HistHIMCTot_p;
  genRaw_p->hiMCQStruct_p = genRawJt_HistHIMCQ_p;
  genRaw_p->hiMCGStruct_p = genRawJt_HistHIMCG_p;

  genRaw_p->ppMCTotStruct_p = genRawJt_HistPPMCTot_p;
  genRaw_p->ppMCQStruct_p = genRawJt_HistPPMCQ_p;
  genRaw_p->ppMCGStruct_p = genRawJt_HistPPMCG_p;

  genRaw_p->genPPStruct_p = T_genSUBEJt_HistPPMCTot_p;
  genRaw_p->genHIStruct_p = T_genSUBEJt_HistHIMCTot_p;

  JetSuperSubstructHist* genSK_p = new JetSuperSubstructHist();
  genSK_p->isPP_ = false;
  genSK_p->isPPMC_ = isPPMC;
  genSK_p->isPbPb_ = false;
  genSK_p->isHIMC_ = isHIMC;
  genSK_p->isGenPP_ = true;
  genSK_p->isGenHI_ = true;

  genSK_p->hiMCTotStruct_p = genSKJt_HistHIMCTot_p;
  genSK_p->hiMCQStruct_p = genSKJt_HistHIMCQ_p;
  genSK_p->hiMCGStruct_p = genSKJt_HistHIMCG_p;

  genSK_p->ppMCTotStruct_p = genSKJt_HistPPMCTot_p;
  genSK_p->ppMCQStruct_p = genSKJt_HistPPMCQ_p;
  genSK_p->ppMCGStruct_p = genSKJt_HistPPMCG_p;

  genSK_p->genPPStruct_p = T_genSUBEJt_HistPPMCTot_p;
  genSK_p->genHIStruct_p = T_genSUBEJt_HistHIMCTot_p;


  JetSuperSubstructHist* pfRaw_p = new JetSuperSubstructHist();
  pfRaw_p->isPP_ = isPP;
  pfRaw_p->isPPMC_ = isPPMC;
  pfRaw_p->isPbPb_ = isPbPb;
  pfRaw_p->isHIMC_ = isHIMC;
  pfRaw_p->isGenPP_ = true;
  pfRaw_p->isGenHI_ = true;

  pfRaw_p->ppMCTotStruct_p = pfRawJt_HistPPMCTot_p;
  pfRaw_p->ppMCQStruct_p = pfRawJt_HistPPMCQ_p;
  pfRaw_p->ppMCGStruct_p = pfRawJt_HistPPMCG_p;

  pfRaw_p->hiMCTotStruct_p = pfRawJt_HistHIMCTot_p;
  pfRaw_p->hiMCQStruct_p = pfRawJt_HistHIMCQ_p;
  pfRaw_p->hiMCGStruct_p = pfRawJt_HistHIMCG_p;

  pfRaw_p->ppStruct_p = pfRawJt_HistPPTot_p;
  pfRaw_p->pbpbStruct_p = pfRawJt_HistPbPbTot_p;

  pfRaw_p->genPPStruct_p = T_genSUBEJt_HistPPMCTot_p;
  pfRaw_p->genHIStruct_p = T_genSUBEJt_HistHIMCTot_p;

  JetSuperSubstructHist* pfVs_p = new JetSuperSubstructHist();
  pfVs_p->isPP_ = isPP;
  pfVs_p->isPPMC_ = isPPMC;
  pfVs_p->isPbPb_ = isPbPb;
  pfVs_p->isHIMC_ = isHIMC;
  pfVs_p->isGenPP_ = true;
  pfVs_p->isGenHI_ = true;

  pfVs_p->ppMCTotStruct_p = pfRawJt_HistPPMCTot_p;
  pfVs_p->ppMCQStruct_p = pfRawJt_HistPPMCQ_p;
  pfVs_p->ppMCGStruct_p = pfRawJt_HistPPMCG_p;

  pfVs_p->hiMCTotStruct_p = pfVsJt_HistHIMCTot_p;
  pfVs_p->hiMCQStruct_p = pfVsJt_HistHIMCQ_p;
  pfVs_p->hiMCGStruct_p = pfVsJt_HistHIMCG_p;

  pfVs_p->ppStruct_p = pfRawJt_HistPPTot_p;
  pfVs_p->pbpbStruct_p = pfVsJt_HistPbPbTot_p;

  pfVs_p->genPPStruct_p = T_genSUBEJt_HistPPMCTot_p;
  pfVs_p->genHIStruct_p = T_genSUBEJt_HistHIMCTot_p;

  JetSuperSubstructHist* pfSK_p = new JetSuperSubstructHist();
  pfSK_p->isPP_ = isPP;
  pfSK_p->isPPMC_ = isPPMC;
  pfSK_p->isPbPb_ = isPbPb;
  pfSK_p->isHIMC_ = isHIMC;
  pfSK_p->isGenPP_ = true;
  pfSK_p->isGenHI_ = true;

  pfSK_p->ppMCTotStruct_p = pfSKJt_HistPPMCTot_p;
  pfSK_p->ppMCQStruct_p = pfSKJt_HistPPMCQ_p;
  pfSK_p->ppMCGStruct_p = pfSKJt_HistPPMCG_p;

  pfSK_p->hiMCTotStruct_p = pfSKJt_HistHIMCTot_p;
  pfSK_p->hiMCQStruct_p = pfSKJt_HistHIMCQ_p;
  pfSK_p->hiMCGStruct_p = pfSKJt_HistHIMCG_p;

  pfSK_p->ppStruct_p = pfSKJt_HistPPTot_p;
  pfSK_p->pbpbStruct_p = pfSKJt_HistPbPbTot_p;

  pfSK_p->genPPStruct_p = T_genSUBEJt_HistPPMCTot_p;
  pfSK_p->genHIStruct_p = T_genSUBEJt_HistHIMCTot_p;
  GetHistForPlot(pbpbFile_p, ppFile_p, hiMCFile_p, ppMCFile_p, "T", true, true);

  for(Int_t iter = 0; iter < 15; iter++){
    std::cout << "iter: " << iter << std::endl;

    if(iter == 4) continue;
    //    if(iter < 4) continue;
    //    if(iter > 5) continue;
    plotFastJetPTDTauPanel(genSUBE_p, "T", "genSUBETot", iter, genSUBE_p->isPbPb_, genSUBE_p->isPP_, isHIMC, isPPMC);
    plotFastJetPTDTauPanel(genRaw_p, "T", "genRawTot", iter, genRaw_p->isPbPb_, genRaw_p->isPP_, isHIMC, isPPMC);
    plotFastJetPTDTauPanel(genSK_p, "T", "genSKTot", iter, genSK_p->isPbPb_, genSK_p->isPP_, isHIMC, isPPMC);
  }
  GetHistForPlot(pbpbFile_p, ppFile_p, hiMCFile_p, ppMCFile_p, "VsPF", true, true);

  for(Int_t iter = 0; iter < 15; iter++){
    if(iter == 4 || iter == 7) continue;

    plotFastJetPTDTauPanel(pfSK_p, "VsPF", "pfSKTot", iter, pfSK_p->isPbPb_, pfSK_p->isPP_, isHIMC, isPPMC);
    plotFastJetPTDTauPanel(pfRaw_p, "VsPF", "pfRawTot", iter, pfRaw_p->isPbPb_, pfRaw_p->isPP_, isHIMC, isPPMC);
    plotFastJetPTDTauPanel(pfVs_p, "VsPF", "pfVsTot", iter, pfVs_p->isPbPb_, pfVs_p->isPP_, isHIMC, isPPMC);
  }

  //  GetHistForPlot(pbpbFile_p, ppFile_p, hiMCFile_p, ppMCFile_p, "VsPF");
  //  plotFastJetPTDTauPanel(pfRaw_p, "VsPF", "pfRawTot", isPbPb, isPP, isHIMC, isPPMC);

  delete genSUBE_p;
  delete genRaw_p;
  delete genSK_p;
  delete pfRaw_p;
  delete pfVs_p;
  delete pfSK_p;


  if(isPP){
    ppFile_p->Close();
    delete ppFile_p;
  }
  if(isPbPb){
    pbpbFile_p->Close();
    delete pbpbFile_p;
  }
  if(isHIMC){
    hiMCFile_p->Close();
    delete hiMCFile_p;
  }
  if(isPPMC){
    ppMCFile_p->Close();
    delete ppMCFile_p;
  }
  
  return;
}
