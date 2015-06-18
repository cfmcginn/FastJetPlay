//=============================================
// Author: Chris McGinn
//
// Jet Substructure Class
// 
//=============================================

#ifndef __JETSUPERSUBSTRUCT__
#define __JETSUPERSUBSTRUCT__

#include "jetSubstruct.h"
#include "commonSetup.h"
#include <string>
#include "sType.h"
#include "qGType.h"

class JetSuperSubstruct{
public:
  JetSuperSubstruct(){};
  ~JetSuperSubstruct(){};

  //declare arrays much yolo
  JetSubstruct* pbpbStruct_p;

  JetSubstruct* ppStruct_p;

  JetSubstruct* hiMCTotStruct_p;
  JetSubstruct* hiMCQStruct_p;
  JetSubstruct* hiMCGStruct_p;

  JetSubstruct* ppMCTotStruct_p;
  JetSubstruct* ppMCQStruct_p;
  JetSubstruct* ppMCGStruct_p;
};

class JetSuperSubstructHist{
public:
  JetSuperSubstructHist(){};
  ~JetSuperSubstructHist(){};

  //declare arrays much yolo
  Bool_t isPP_;
  Bool_t isPbPb_;
  Bool_t isHIMC_;
  Bool_t isPPMC_;

  Bool_t isGenPP_;
  Bool_t isGenHI_;

  JetSubstructHist* pbpbStruct_p;

  JetSubstructHist* ppStruct_p;

  JetSubstructHist* hiMCTotStruct_p;
  JetSubstructHist* hiMCQStruct_p;
  JetSubstructHist* hiMCGStruct_p;

  JetSubstructHist* ppMCTotStruct_p;
  JetSubstructHist* ppMCQStruct_p;
  JetSubstructHist* ppMCGStruct_p;

  JetSubstructHist* genPPStruct_p;
  JetSubstructHist* genHIStruct_p;

  Bool_t GetTH1ErrorCheck(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum);
  Float_t GetNewMax(Float_t oldMax, Float_t newMax);
  Float_t GetNewMin(Float_t oldMin, Float_t newMin);
  Int_t GetRangeLow(TH1F* inHist_p, Int_t oldLow);
  Int_t GetRangeHi(TH1F* inHist_p, Int_t oldHi);
  void handsomeTH1(TH1* a, Int_t markCol, Int_t fillCol, Float_t size, Int_t markerstyle);
  void niceTH1(TH1F* uglyTH1, float max , float min, float ndivX, float ndivY, Int_t markCol, Int_t fillCol, Float_t size, Int_t style);
  void SetTitle(TH1F* inHist_p, const std::string xTitle, const std::string yTitle, const Float_t xOffset, const Float_t yOffset);
  void SetTitleSize(TH1F* inHist_p, const Int_t titleSize, const Int_t labelSize);
  void SetSuperActiveTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum);
  std::string GetSubTitle(const Int_t histNum, const Int_t subNum);
  void StandardizeTH1(const Int_t histNum);
  void StandardizeMeanTH1(const Int_t histNum);
};


Bool_t JetSuperSubstructHist::GetTH1ErrorCheck(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum)
{
  if(histNum < 0 || histNum > nTH1_){
    std::cout << "Error setting active histogram; outside of nTH1 range" << std::endl;
    return false;
  }

  if(centNum < 0 || centNum > centHIMax){
    std::cout << "Error setting active histogram; outside of centHIMax range" << std::endl;
    return false;
  }

  if(jtNum < 0 || jtNum > histJtMax){
    std::cout << "Error setting active histogram; outside of histJtMax range" << std::endl;
    return false;
  }

  if(histNum == 4 || histNum == 5){
    if(subNum < 0 || subNum > nSDBeta){
      std::cout << "Error setting active histogram; outside of nSDBeta range" << std::endl;
      return false;
    }
  }
  else if(histNum == 7){
    if(subNum < 0 || subNum > nChgBeta){
      std::cout << "Error setting active histogram; outside of nChgBeta range" << std::endl;
      return false;
    }
  }
  else if(histNum == 9){
    if(subNum < 0 || subNum > nSigma){
      std::cout << "Error setting active histogram; outside of nSigma range" << std::endl;
      return false;
    }
  }
  else if(histNum == 10 || histNum == 11 || histNum == 12){
    if(subNum < 0 || subNum > nFFM){
      std::cout << "Error setting active histogram; outside of nFFM range" << std::endl;
      return false;
    }
  }
  else if(histNum == 13 || histNum == 14){
    if(subNum < 0 || subNum > nSubjet){
      std::cout << "Error setting active histogram; outside of nSubjet range" << std::endl;
      return false;
    }
  }

  return true;
}



Float_t JetSuperSubstructHist::GetNewMax(Float_t oldMax, Float_t newMax)
{
  if(oldMax < newMax) oldMax = newMax;

  return oldMax;
}

Float_t JetSuperSubstructHist::GetNewMin(Float_t oldMin, Float_t newMin)
{
  if(oldMin > newMin) oldMin = newMin;

  return oldMin;
}

Int_t JetSuperSubstructHist::GetRangeLow(TH1F* inHist_p, Int_t oldLow)
{
  for(Int_t iter = 0; iter < inHist_p->GetNbinsX(); iter++){
    if(iter > oldLow) break;

    if(inHist_p->GetBinContent(iter+1) != 0){
      oldLow = iter+1;
      break;
    }
  }

  return oldLow;
}


Int_t JetSuperSubstructHist::GetRangeHi(TH1F* inHist_p, Int_t oldHi)
{
  for(Int_t iter = inHist_p->GetNbinsX(); iter > 0; iter--){
    if(iter < oldHi) break;

    if(inHist_p->GetBinContent(iter) != 0){
      oldHi = iter;
      break;
    }
  }

  return oldHi;
}


void JetSuperSubstructHist::handsomeTH1(TH1* a, Int_t markCol, Int_t fillCol, Float_t size, Int_t markerstyle)
{
  a->SetMarkerColor(markCol);
  a->SetFillColor(fillCol);
  a->SetMarkerSize(size);
  a->SetMarkerStyle(markerstyle);
  a->SetLineColor(markCol);

  return;
}


void JetSuperSubstructHist::niceTH1(TH1F* uglyTH1, float max , float min, float ndivX, float ndivY, Int_t markCol, Int_t fillCol, Float_t size, Int_t style)
{
  handsomeTH1(uglyTH1, markCol, fillCol, size, style);
  uglyTH1->SetMaximum(max);
  uglyTH1->SetMinimum(min);
  uglyTH1->GetXaxis()->SetNdivisions(ndivX);
  uglyTH1->GetYaxis()->SetNdivisions(ndivY);

  return;
}


void JetSuperSubstructHist::SetTitle(TH1F* inHist_p, const std::string xTitle, const std::string yTitle, const Float_t xOffset, const Float_t yOffset)
{
  inHist_p->GetXaxis()->CenterTitle();
  inHist_p->GetYaxis()->CenterTitle();

  inHist_p->SetXTitle(xTitle.c_str());
  inHist_p->SetYTitle(yTitle.c_str());

  inHist_p->GetXaxis()->SetTitleOffset(xOffset);
  inHist_p->GetYaxis()->SetTitleOffset(yOffset);

  return;
}


void JetSuperSubstructHist::SetTitleSize(TH1F* inHist_p, const Int_t titleSize, const Int_t labelSize)
{
  inHist_p->GetXaxis()->SetTitleSize(titleSize);
  inHist_p->GetXaxis()->SetLabelSize(labelSize);

  inHist_p->GetYaxis()->SetTitleSize(titleSize);
  inHist_p->GetYaxis()->SetLabelSize(labelSize);

  return;
}


void JetSuperSubstructHist::SetSuperActiveTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum){
  if(isPbPb_) pbpbStruct_p->SetActiveTH1(histNum, centNum, jtNum, subNum);
  if(isPP_) ppStruct_p->SetActiveTH1(histNum, 0, jtNum, subNum);
  
  if(isHIMC_) hiMCTotStruct_p->SetActiveTH1(histNum, centNum, jtNum, subNum);
  if(isHIMC_) hiMCQStruct_p->SetActiveTH1(histNum, centNum, jtNum, subNum);
  if(isHIMC_) hiMCGStruct_p->SetActiveTH1(histNum, centNum, jtNum, subNum);
  
  if(isPPMC_) ppMCTotStruct_p->SetActiveTH1(histNum, 0, jtNum, subNum);
  if(isPPMC_) ppMCQStruct_p->SetActiveTH1(histNum, 0, jtNum, subNum);
  if(isPPMC_) ppMCGStruct_p->SetActiveTH1(histNum, 0, jtNum, subNum);

  if(isGenPP_) genPPStruct_p->SetActiveTH1(histNum, 0, jtNum, subNum);
  if(isGenHI_) genHIStruct_p->SetActiveTH1(histNum, 0, jtNum, subNum);

  return;
}

std::string JetSuperSubstructHist::GetSubTitle(const Int_t histNum, const Int_t subNum)
{
  std::string subStr = "";

  if(!GetTH1ErrorCheck(histNum, 0, 0, subNum)) return subStr;

  if(histNum == 4) subStr = betaSDArrStr[subNum];
  else if(histNum == 5) subStr = betaSDArrStr[subNum];
  else if(histNum == 7) subStr = betaChgArrStr[subNum];
  else if(histNum == 10 || histNum == 11 || histNum == 12) subStr = ffmArrStr[subNum];

  return subStr;
}


void JetSuperSubstructHist::StandardizeTH1(const Int_t histNum)
{
  const Int_t nSub = nTH1Sub_[histNum];

  Float_t max = 0;
  Float_t min = 100000;

  Int_t rangeLow = 100000;
  Int_t rangeHi = 0;

  std::cout << "MAX START: " << max << std::endl;

  for(Int_t iter = 0; iter < histJtMax; iter++){
    for(Int_t subIter = 0; subIter < nSub; subIter++){
      if(histNum == 10 || histNum == 11 || histNum == 12){
	if(subIter == 3) continue;
      }
      if(isPP_){
	ppStruct_p->SetActiveTH1(histNum, 0, iter, subIter);	
	max = GetNewMax(max, ppStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, ppStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(ppStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(ppStruct_p->activeTH1_p, rangeHi);
      }

      std::cout << "pp max: " << iter <<  ", " << subIter << ", " << max << std::endl;
      if(isPPMC_){
	ppMCTotStruct_p->SetActiveTH1(histNum, 0, iter, subIter);	
	max = GetNewMax(max, ppMCTotStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, ppMCTotStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(ppMCTotStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(ppMCTotStruct_p->activeTH1_p, rangeHi);

	std::cout << "ppmc max: " << iter <<  ", " << subIter << ", " << max << std::endl;

	ppMCQStruct_p->SetActiveTH1(histNum, 0, iter, subIter);	
	max = GetNewMax(max, ppMCQStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, ppMCQStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(ppMCQStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(ppMCQStruct_p->activeTH1_p, rangeHi);

	std::cout << "ppq max: " << iter <<  ", " << subIter << ", " << max << std::endl;

	ppMCGStruct_p->SetActiveTH1(histNum, 0, iter, subIter);	
	max = GetNewMax(max, ppMCGStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, ppMCGStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(ppMCGStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(ppMCGStruct_p->activeTH1_p, rangeHi);

	std::cout << "ppg max: " << iter <<  ", " << subIter << ", " << max << std::endl;
      }

      if(isGenPP_){
        genPPStruct_p->SetActiveTH1(histNum, 0, iter, subIter);
        max = GetNewMax(max, genPPStruct_p->activeTH1_p->GetMaximum());
        min = GetNewMin(min, genPPStruct_p->activeTH1_p->GetMinimum());
        rangeLow = GetRangeLow(genPPStruct_p->activeTH1_p, rangeLow);
        rangeHi = GetRangeHi(genPPStruct_p->activeTH1_p, rangeHi);

	std::cout << "ppgen max: " << iter <<  ", " << subIter << ", " << max << std::endl;
      }
      
      for(Int_t centIter = 0; centIter < centHIMax; centIter++){
	if(isPbPb_){
	  pbpbStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);	
	  max = GetNewMax(max, pbpbStruct_p->activeTH1_p->GetMaximum());
	  min = GetNewMin(min, pbpbStruct_p->activeTH1_p->GetMinimum());
	  rangeLow = GetRangeLow(pbpbStruct_p->activeTH1_p, rangeLow);
	  rangeHi = GetRangeHi(pbpbStruct_p->activeTH1_p, rangeHi);
	  
	  std::cout << "pbpb  max: " << iter <<  ", " << subIter << ", " << centIter << ", " << max << std::endl;
	}
	
	if(isHIMC_){
	  hiMCTotStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);	
	  max = GetNewMax(max, hiMCTotStruct_p->activeTH1_p->GetMaximum());
	  min = GetNewMin(min, hiMCTotStruct_p->activeTH1_p->GetMinimum());
	  rangeLow = GetRangeLow(hiMCTotStruct_p->activeTH1_p, rangeLow);
	  rangeHi = GetRangeHi(hiMCTotStruct_p->activeTH1_p, rangeHi);
	  
	  std::cout << "himc  max: " << iter <<  ", " << subIter << ", " << centIter << ", " << max << std::endl;

	  hiMCQStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);	
	  max = GetNewMax(max, hiMCQStruct_p->activeTH1_p->GetMaximum());
	  min = GetNewMin(min, hiMCQStruct_p->activeTH1_p->GetMinimum());
	  rangeLow = GetRangeLow(hiMCQStruct_p->activeTH1_p, rangeLow);
	  rangeHi = GetRangeHi(hiMCQStruct_p->activeTH1_p, rangeHi);

	  std::cout << "hiq  max: " << iter <<  ", " << subIter << ", " << centIter << ", " << max << std::endl;

	  hiMCGStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);	
	  max = GetNewMax(max, hiMCGStruct_p->activeTH1_p->GetMaximum());
	  min = GetNewMin(min, hiMCGStruct_p->activeTH1_p->GetMinimum());
	  rangeLow = GetRangeLow(hiMCGStruct_p->activeTH1_p, rangeLow);
	  rangeHi = GetRangeHi(hiMCGStruct_p->activeTH1_p, rangeHi);

	  std::cout << "hig  max: " << iter <<  ", " << subIter << ", " << centIter << ", " << max << std::endl;
	}

	if(isGenHI_){
	  genHIStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);
	  max = GetNewMax(max, genHIStruct_p->activeTH1_p->GetMaximum());
	  min = GetNewMin(min, genHIStruct_p->activeTH1_p->GetMinimum());
	  rangeLow = GetRangeLow(genHIStruct_p->activeTH1_p, rangeLow);
	  rangeHi = GetRangeHi(genHIStruct_p->activeTH1_p, rangeHi);

	  std::cout << "higen  max: " << iter <<  ", " << subIter << ", " << centIter << ", " << max << std::endl;
	}

      }
    }
  }

  std::cout << "MAX A: " << max << std::endl;

  if(max >= 1) 
    std::cout << "MAX PROBLEM: " << max << ", " << hiMCTotStruct_p->activeTH1_p->GetName() << std::endl;
 
  //  if(max <= 1) max += *max;
  //  if(max > 1) max = 1;

  if(min < 1) min = 0;

  std::cout << "MAX B: " << max << std::endl;
  
  Float_t xOffset = 0.8;
  Float_t yOffset = 1.3;
  if(isPbPb_ || isHIMC_){
    xOffset = 1.6;
    yOffset = 2.2;
  }

  for(Int_t iter = 0; iter < histJtMax; iter++){
    for(Int_t subIter = 0; subIter < nSub; subIter++){
      std::string xTit2 = Form("%s%d", xTit_[histNum].c_str(), subIter);
      if(nSub == 1) xTit2 = Form("%s", xTit_[histNum].c_str());
      else if(0 != strcmp(GetSubTitle(histNum, subIter).c_str(), "")) xTit2 = Form("%s%s", xTit_[histNum].c_str(), GetSubTitle(histNum, subIter).c_str());

      if(isPP_){
	ppStruct_p->SetActiveTH1(histNum, 0, iter, subIter);
	niceTH1(ppStruct_p->activeTH1_p, max, min, 505, 505, ppStruct_p->activeTH1_p->GetMarkerColor(), ppStruct_p->activeTH1_p->GetFillColor(), ppStruct_p->activeTH1_p->GetMarkerSize(), 21);
	SetTitle(ppStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	ppStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      }


      if(isPPMC_){
	ppMCTotStruct_p->SetActiveTH1(histNum, 0, iter, subIter);
        niceTH1(ppMCTotStruct_p->activeTH1_p, max, min, 505, 505, ppMCTotStruct_p->activeTH1_p->GetMarkerColor(), 18, ppMCTotStruct_p->activeTH1_p->GetMarkerSize(), 25);
	SetTitle(ppMCTotStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	ppMCTotStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);

	ppMCQStruct_p->SetActiveTH1(histNum, 0, iter, subIter);
        niceTH1(ppMCQStruct_p->activeTH1_p, max, min, 505, 505, ppMCQStruct_p->activeTH1_p->GetMarkerColor(), kBlue, 0, 25);
	SetTitle(ppMCQStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	ppMCQStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);

	ppMCGStruct_p->SetActiveTH1(histNum, 0, iter, subIter);
	niceTH1(ppMCGStruct_p->activeTH1_p, max, min, 505, 505, ppMCGStruct_p->activeTH1_p->GetMarkerColor(), kRed, 0, 25);
	SetTitle(ppMCGStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	ppMCGStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      }

      if(isGenPP_){
	genPPStruct_p->SetActiveTH1(histNum, 0, iter, subIter);
	niceTH1(genPPStruct_p->activeTH1_p, max, min, 505, 505, genPPStruct_p->activeTH1_p->GetMarkerColor(), genPPStruct_p->activeTH1_p->GetFillColor(), genPPStruct_p->activeTH1_p->GetMarkerSize(), 26);
	SetTitle(genPPStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	genPPStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      }

      for(Int_t centIter = 0; centIter < centHIMax; centIter++){
        if(isPbPb_){
          pbpbStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);
	  niceTH1(pbpbStruct_p->activeTH1_p, max, min, 505, 505, pbpbStruct_p->activeTH1_p->GetMarkerColor(), pbpbStruct_p->activeTH1_p->GetFillColor(), pbpbStruct_p->activeTH1_p->GetMarkerSize(), 20);
	  SetTitle(pbpbStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	  pbpbStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
        }

        if(isHIMC_){
          hiMCTotStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);
	  niceTH1(hiMCTotStruct_p->activeTH1_p, max, min, 505, 505, hiMCTotStruct_p->activeTH1_p->GetMarkerColor(), 18, hiMCTotStruct_p->activeTH1_p->GetMarkerSize(), 24);
	  SetTitle(hiMCTotStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	  hiMCTotStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);

          hiMCQStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);
	  niceTH1(hiMCQStruct_p->activeTH1_p, max, min, 505, 505, hiMCQStruct_p->activeTH1_p->GetMarkerColor(), kBlue, 0, 24);
	  SetTitle(hiMCQStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	  hiMCQStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);

          hiMCGStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);
	  niceTH1(hiMCGStruct_p->activeTH1_p, max, min, 505, 505, hiMCGStruct_p->activeTH1_p->GetMarkerColor(), kRed, 0, 24);
	  SetTitle(hiMCGStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	  hiMCGStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
        }

        if(isGenHI_){
          genHIStruct_p->SetActiveTH1(histNum, centIter, iter, subIter);
	  niceTH1(genHIStruct_p->activeTH1_p, max, min, 505, 505, genHIStruct_p->activeTH1_p->GetMarkerColor(), genHIStruct_p->activeTH1_p->GetFillColor(), genHIStruct_p->activeTH1_p->GetMarkerSize(), 27);
	  SetTitle(genHIStruct_p->activeTH1_p, xTit2, "Event Fraction", xOffset, yOffset);
	  genHIStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
        }
      }
    }
  }

  return;
}



void JetSuperSubstructHist::StandardizeMeanTH1(const Int_t histNum)
{
  Float_t max = 0;
  Float_t min = 100000;

  Int_t rangeLow = 100000;
  Int_t rangeHi = 0;

  for(Int_t iter = 0; iter < histJtMax; iter++){
    if(isPP_){
      ppStruct_p->SetActiveMeanTH1(histNum, 0, iter);	
      max = GetNewMax(max, ppStruct_p->activeTH1_p->GetMaximum());
      min = GetNewMin(min, ppStruct_p->activeTH1_p->GetMinimum());
      rangeLow = GetRangeLow(ppStruct_p->activeTH1_p, rangeLow);
      rangeHi = GetRangeHi(ppStruct_p->activeTH1_p, rangeHi);
    }

    std::cout << "isPPMC_" << isPPMC_ << std::endl;

    if(isPPMC_){
      ppMCTotStruct_p->SetActiveMeanTH1(histNum, 0, iter);	
      max = GetNewMax(max, ppMCTotStruct_p->activeTH1_p->GetMaximum());
      min = GetNewMin(min, ppMCTotStruct_p->activeTH1_p->GetMinimum());
      rangeLow = GetRangeLow(ppMCTotStruct_p->activeTH1_p, rangeLow);
      rangeHi = GetRangeHi(ppMCTotStruct_p->activeTH1_p, rangeHi);
      
      ppMCQStruct_p->SetActiveMeanTH1(histNum, 0, iter);	
      max = GetNewMax(max, ppMCQStruct_p->activeTH1_p->GetMaximum());
      min = GetNewMin(min, ppMCQStruct_p->activeTH1_p->GetMinimum());
      rangeLow = GetRangeLow(ppMCQStruct_p->activeTH1_p, rangeLow);
      rangeHi = GetRangeHi(ppMCQStruct_p->activeTH1_p, rangeHi);
      
      ppMCGStruct_p->SetActiveMeanTH1(histNum, 0, iter);	
      max = GetNewMax(max, ppMCGStruct_p->activeTH1_p->GetMaximum());
      min = GetNewMin(min, ppMCGStruct_p->activeTH1_p->GetMinimum());
      rangeLow = GetRangeLow(ppMCGStruct_p->activeTH1_p, rangeLow);
      rangeHi = GetRangeHi(ppMCGStruct_p->activeTH1_p, rangeHi);
    }
    
    std::cout << "Gets to gen" << std::endl;
    std::cout << isGenPP_ << std::endl;
    
    if(isGenPP_){
      genPPStruct_p->SetActiveMeanTH1(histNum, 0, iter);
      max = GetNewMax(max, genPPStruct_p->activeTH1_p->GetMaximum());
      min = GetNewMin(min, genPPStruct_p->activeTH1_p->GetMinimum());
      rangeLow = GetRangeLow(genPPStruct_p->activeTH1_p, rangeLow);
      rangeHi = GetRangeHi(genPPStruct_p->activeTH1_p, rangeHi);
    }
    
    for(Int_t centIter = 0; centIter < centHIMax; centIter++){
      std::cout << "  centIter: " << centIter << std::endl;
      
      std::cout << "isPbPb_" << isPbPb_ << std::endl;
      if(isPbPb_){
	pbpbStruct_p->SetActiveMeanTH1(histNum, centIter, iter);	
	max = GetNewMax(max, pbpbStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, pbpbStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(pbpbStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(pbpbStruct_p->activeTH1_p, rangeHi);
      }
      std::cout << "isHIMC_" << isHIMC_ << std::endl;
      
      if(isHIMC_){
	hiMCTotStruct_p->SetActiveMeanTH1(histNum, centIter, iter);	
	max = GetNewMax(max, hiMCTotStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, hiMCTotStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(hiMCTotStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(hiMCTotStruct_p->activeTH1_p, rangeHi);
	
	hiMCQStruct_p->SetActiveMeanTH1(histNum, centIter, iter);	
	max = GetNewMax(max, hiMCQStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, hiMCQStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(hiMCQStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(hiMCQStruct_p->activeTH1_p, rangeHi);
	
	hiMCGStruct_p->SetActiveMeanTH1(histNum, centIter, iter);	
	max = GetNewMax(max, hiMCGStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, hiMCGStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(hiMCGStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(hiMCGStruct_p->activeTH1_p, rangeHi);
      }
      
      if(isGenHI_){
	genHIStruct_p->SetActiveMeanTH1(histNum, centIter, iter);
	max = GetNewMax(max, genHIStruct_p->activeTH1_p->GetMaximum());
	min = GetNewMin(min, genHIStruct_p->activeTH1_p->GetMinimum());
	rangeLow = GetRangeLow(genHIStruct_p->activeTH1_p, rangeLow);
	rangeHi = GetRangeHi(genHIStruct_p->activeTH1_p, rangeHi);
      }

    }
  }

  //  if(max <= 1) max += .25*max;
  //  if(max > 2) max = 2;
  
  Float_t xOffset = 0.7;
  Float_t yOffset = 1.1;

  for(Int_t iter = 0; iter < histJtMax; iter++){    
    if(isPP_){
      ppStruct_p->SetActiveMeanTH1(histNum, 0, iter);
      niceTH1(ppStruct_p->activeTH1_p, max, min, 505, 505, ppStruct_p->activeTH1_p->GetMarkerColor(), ppStruct_p->activeTH1_p->GetFillColor(), ppStruct_p->activeTH1_p->GetMarkerSize(), 21);
      SetTitle(ppStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
      SetTitleSize(ppStruct_p->activeTH1_p, ppStruct_p->activeTH1_p->GetTitleSize()-6, ppStruct_p->activeTH1_p->GetLabelSize()-6);
      ppStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
    }
    
    if(isPPMC_){
      ppMCTotStruct_p->SetActiveMeanTH1(histNum, 0, iter);
      niceTH1(ppMCTotStruct_p->activeTH1_p, max, min, 505, 505, ppMCTotStruct_p->activeTH1_p->GetMarkerColor(), 18, ppMCTotStruct_p->activeTH1_p->GetMarkerSize(), 25);
      SetTitle(ppMCTotStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
      SetTitleSize(ppMCTotStruct_p->activeTH1_p, ppMCTotStruct_p->activeTH1_p->GetTitleSize()-6, ppMCTotStruct_p->activeTH1_p->GetLabelSize()-6);
      ppMCTotStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      
      ppMCQStruct_p->SetActiveMeanTH1(histNum, 0, iter);
      niceTH1(ppMCQStruct_p->activeTH1_p, max, min, 505, 505, kBlue, kBlue, ppMCQStruct_p->activeTH1_p->GetMarkerSize(), 25);
      SetTitle(ppMCQStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
      SetTitleSize(ppMCQStruct_p->activeTH1_p, ppMCQStruct_p->activeTH1_p->GetTitleSize()-6, ppMCQStruct_p->activeTH1_p->GetLabelSize()-6);
      ppMCQStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      
      ppMCGStruct_p->SetActiveMeanTH1(histNum, 0, iter);
      niceTH1(ppMCGStruct_p->activeTH1_p, max, min, 505, 505, kRed, kRed, ppMCGStruct_p->activeTH1_p->GetMarkerSize(), 25);
      SetTitle(ppMCGStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
      SetTitleSize(ppMCGStruct_p->activeTH1_p, ppMCGStruct_p->activeTH1_p->GetTitleSize()-6, ppMCGStruct_p->activeTH1_p->GetLabelSize()-6);
      ppMCGStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
    }
    
    if(isGenPP_){
      genPPStruct_p->SetActiveMeanTH1(histNum, 0, iter);
      niceTH1(genPPStruct_p->activeTH1_p, max, min, 505, 505, genPPStruct_p->activeTH1_p->GetMarkerColor(), genPPStruct_p->activeTH1_p->GetFillColor(), genPPStruct_p->activeTH1_p->GetMarkerSize(), 26);
      SetTitle(genPPStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
	SetTitleSize(genPPStruct_p->activeTH1_p, genPPStruct_p->activeTH1_p->GetTitleSize()-6, genPPStruct_p->activeTH1_p->GetLabelSize()-6);
      genPPStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
    }
    
    const Int_t markStylePbPb[2] = {20, 34};
    const Int_t markStyleMC[2] = {24, 28};

    for(Int_t centIter = 0; centIter < centHIMax; centIter++){
      if(isPbPb_){
	pbpbStruct_p->SetActiveMeanTH1(histNum, centIter, iter);
	niceTH1(pbpbStruct_p->activeTH1_p, max, min, 505, 505, 1, pbpbStruct_p->activeTH1_p->GetFillColor(), pbpbStruct_p->activeTH1_p->GetMarkerSize(), markStylePbPb[centIter]);
	SetTitle(pbpbStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
	SetTitleSize(pbpbStruct_p->activeTH1_p, pbpbStruct_p->activeTH1_p->GetTitleSize()-6, pbpbStruct_p->activeTH1_p->GetLabelSize()-6);
	pbpbStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      }
      
      if(isHIMC_){
	hiMCTotStruct_p->SetActiveMeanTH1(histNum, centIter, iter);
	niceTH1(hiMCTotStruct_p->activeTH1_p, max, min, 505, 505, 1, 18, hiMCTotStruct_p->activeTH1_p->GetMarkerSize(), markStyleMC[centIter]);
	SetTitle(hiMCTotStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
	SetTitleSize(hiMCTotStruct_p->activeTH1_p, hiMCTotStruct_p->activeTH1_p->GetTitleSize()-6, hiMCTotStruct_p->activeTH1_p->GetLabelSize()-6);
	hiMCTotStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
	
	hiMCQStruct_p->SetActiveMeanTH1(histNum, centIter, iter);
	niceTH1(hiMCQStruct_p->activeTH1_p, max, min, 505, 505, kBlue, kBlue, hiMCQStruct_p->activeTH1_p->GetMarkerSize(), markStyleMC[centIter]);
	SetTitle(hiMCQStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
	SetTitleSize(hiMCQStruct_p->activeTH1_p, hiMCQStruct_p->activeTH1_p->GetTitleSize()-6, hiMCQStruct_p->activeTH1_p->GetLabelSize()-6);
	hiMCQStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
	
	hiMCGStruct_p->SetActiveMeanTH1(histNum, centIter, iter);
	niceTH1(hiMCGStruct_p->activeTH1_p, max, min, 505, 505, kRed, kRed, hiMCGStruct_p->activeTH1_p->GetMarkerSize(), markStyleMC[centIter]);
	SetTitle(hiMCGStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
	SetTitleSize(hiMCGStruct_p->activeTH1_p, hiMCGStruct_p->activeTH1_p->GetTitleSize()-6, hiMCGStruct_p->activeTH1_p->GetLabelSize()-6);
	hiMCGStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      }
      
      if(isGenHI_){
	genHIStruct_p->SetActiveMeanTH1(histNum, centIter, iter);
	niceTH1(genHIStruct_p->activeTH1_p, max, min, 505, 505, 1, genHIStruct_p->activeTH1_p->GetFillColor(), genHIStruct_p->activeTH1_p->GetMarkerSize(), 27);
	SetTitle(genHIStruct_p->activeTH1_p, xMeanTit_[histNum], yMeanTit_[histNum], xOffset, yOffset);
	SetTitleSize(genHIStruct_p->activeTH1_p, genHIStruct_p->activeTH1_p->GetTitleSize()-6, genHIStruct_p->activeTH1_p->GetLabelSize()-6);
	genHIStruct_p->activeTH1_p->GetXaxis()->SetRange(rangeLow, rangeHi);
      }
    }
  }

  return;
}




#endif // __JETSUPERSUBSTRUCT__
