//=============================================
// Author: Chris McGinn
//
// FastJet AnaSkim Class (MC)
//
//=============================================
#ifndef FastJetHist_h
#define FastJetHist_h

#include <string>

#include "FastJetAnaSkim.h"

#include "TH1F.h"

const Int_t jtMax = 8;
const std::string jtOrder[jtMax] = {"Lead", "Sublead", "Inc", "6080", "80100", "100120", "120140", "140200"};

const Int_t centHIMax = 4;

TH1F* ptdHist_Tot_p[centHIMax][jtMax];
TH1F* ptdHist_Q_p[centHIMax][jtMax];
TH1F* ptdHist_G_p[centHIMax][jtMax];
TH1F* ptdHist_Else_p[centHIMax][jtMax];

TH1F* sigHist_Tot_p[centHIMax][jtMax][nSigma];
TH1F* sigHist_Q_p[centHIMax][jtMax][nSigma];
TH1F* sigHist_G_p[centHIMax][jtMax][nSigma];
TH1F* sigHist_Else_p[centHIMax][jtMax][nSigma];

TH1F* multHist_Tot_p[centHIMax][jtMax];
TH1F* multHist_Q_p[centHIMax][jtMax];
TH1F* multHist_G_p[centHIMax][jtMax];
TH1F* multHist_Else_p[centHIMax][jtMax];

TH1F* ptdHiBinHist_p[jtMax];

TH1F* tau21Hist_Tot_p[centHIMax][jtMax][nBeta];
TH1F* tau21Hist_Q_p[centHIMax][jtMax][nBeta];
TH1F* tau21Hist_G_p[centHIMax][jtMax][nBeta];
TH1F* tau21Hist_Else_p[centHIMax][jtMax][nBeta];

TH1F* tau32Hist_Tot_p[centHIMax][jtMax][nBeta];
TH1F* tau32Hist_Q_p[centHIMax][jtMax][nBeta];
TH1F* tau32Hist_G_p[centHIMax][jtMax][nBeta];
TH1F* tau32Hist_Else_p[centHIMax][jtMax][nBeta];

TH1F* subRatHist_Tot_p[centHIMax][jtMax][nSubjet];
TH1F* subRatHist_Q_p[centHIMax][jtMax][nSubjet];
TH1F* subRatHist_G_p[centHIMax][jtMax][nSubjet];
TH1F* subRatHist_Else_p[centHIMax][jtMax][nSubjet];

TH1F* ffmUnsubHist_Tot_p[centHIMax][jtMax][nFFM];
TH1F* ffmUnsubHist_Q_p[centHIMax][jtMax][nFFM];
TH1F* ffmUnsubHist_G_p[centHIMax][jtMax][nFFM];
TH1F* ffmUnsubHist_Else_p[centHIMax][jtMax][nFFM];

std::string getCentString(sampleType sType, Int_t centLow, Int_t centHi);
void BookHist(sampleType sType, const std::string evtSelAlg, const std::string clustAlg);
void CleanHist(TH1F* cleanHist_p);
void CleanHistAll(sampleType sType);
void WriteHistAll(TFile* outFile_p, sampleType sType);
void ScaleHistAll(sampleType sType);

std::string getCentString(sampleType sType, Int_t centLow, Int_t centHi)
{
  if(isHI(sType)) return Form("%d%d", (Int_t)(centLow*.5), (Int_t)((centHi+1)*.5));
  else if(isPA(sType)) return "PA";
  else return "PP";
}

void BookHist(sampleType sType, const std::string evtSelAlg, const std::string clustAlg)
{
  const Bool_t hi = isHI(sType);

  const Int_t centLow[centHIMax] = {0, 20, 60, 100};
  const Int_t centHi[centHIMax] = {19, 59, 99, 199};

  Int_t centBin = 1;
  if(hi) centBin = centHIMax;

  std::string centString[4];
  for(Int_t centIter = 0; centIter < centBin; centIter++){
    centString[centIter] = getCentString(sType, centLow[centIter], centHi[centIter]);
  }

  const Int_t nPTDHiBins = 10;

  const Int_t nPTDBins = 20;
  const Float_t ptdLow = 0.0001;
  const Float_t ptdHi = 0.9999;

  const Int_t nSigBins[nSigma] = {20, 20, 20};
  const Float_t sigLow = 0.0001;
  const Float_t sigHi[nSigma] = {0.1999, 0.1999, 0.1999};

  const Int_t nMultBins = 50;
  const Float_t multLow = -.0001;
  const Float_t multHi = 49.9999;

  const Int_t nTauBins = 20;
  const Float_t tauLow = 0.0001;
  const Float_t tauHi = 0.9999;

  const Int_t nSubBins  = 40;
  const Int_t subLow = 0;
  const Int_t subHi = 1;

  const Int_t nFFMBins[nFFM] = {50, 40, 40, 5, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40};
  const Float_t ffmLow = 0;
  const Float_t ffmHi[nFFM] = {200, 40, 6, 5, 1, 1, 1, 1, 1, 0.1, 0.05, 0.05, 0.05, 0.05};

  for(Int_t jtIter = 0; jtIter < jtMax; jtIter++){
    const std::string ptdStr = Form("%s%sPTD_%s_", evtSelAlg.c_str(), clustAlg.c_str(), jtOrder[jtIter].c_str());

    std::string sigStr[nSigma];
    for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
      sigStr[sigIter] = Form("%s%sSig%d_%s_", evtSelAlg.c_str(), clustAlg.c_str(), sigIter, jtOrder[jtIter].c_str());
    }
    const std::string multStr = Form("%s%sMult_%s_", evtSelAlg.c_str(), clustAlg.c_str(), jtOrder[jtIter].c_str());

    std::string tau21Str[nBeta];
    std::string tau32Str[nBeta];

    for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
      tau21Str[betaIter] = Form("%s%sTau21Beta%d_%s_", evtSelAlg.c_str(), clustAlg.c_str(), betaIter, jtOrder[jtIter].c_str());
      tau32Str[betaIter] = Form("%s%sTau32Beta%d_%s_", evtSelAlg.c_str(), clustAlg.c_str(), betaIter, jtOrder[jtIter].c_str());
    }

    std::string ratStr[nSubjet];
    for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
      ratStr[subJtIter] = Form("%s%sRatSub%d_%s_", evtSelAlg.c_str(), clustAlg.c_str(), subJtIter, jtOrder[jtIter].c_str());
    }

    std::string ffmUnsubStr[nFFM];
    for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
      ffmUnsubStr[ffmIter] = Form("%s%sffmUnsub%d_%s_", evtSelAlg.c_str(), clustAlg.c_str(), ffmIter, jtOrder[jtIter].c_str());
    }

    if(hi) ptdHiBinHist_p[jtIter] = new TH1F(Form("%s_HiBin_h", ptdStr.c_str()), Form("%s_HiBin_h", ptdStr.c_str()), nPTDHiBins, -0.5, 199.5);
    
    for(Int_t centIter = 0; centIter < centBin; centIter++){
      const std::string backStr = Form("_%s_h", centString[centIter].c_str());
      
      ptdHist_Tot_p[centIter][jtIter] = new TH1F(Form("%sTot%s", ptdStr.c_str(), backStr.c_str()), Form("%sTot%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);
      ptdHist_Q_p[centIter][jtIter] = new TH1F(Form("%sQ%s", ptdStr.c_str(), backStr.c_str()), Form("%sQ%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);
      ptdHist_G_p[centIter][jtIter] = new TH1F(Form("%sG%s", ptdStr.c_str(), backStr.c_str()), Form("%sG%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);
      ptdHist_Else_p[centIter][jtIter] = new TH1F(Form("%sElse%s", ptdStr.c_str(), backStr.c_str()), Form("%sElse%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);


      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	sigHist_Tot_p[centIter][jtIter][sigIter] = new TH1F(Form("%sTot%s", sigStr[sigIter].c_str(), backStr.c_str()), Form("%sTot%s", sigStr[sigIter].c_str(), backStr.c_str()), nSigBins[sigIter], sigLow, sigHi[sigIter]);
	sigHist_Q_p[centIter][jtIter][sigIter] = new TH1F(Form("%sQ%s", sigStr[sigIter].c_str(), backStr.c_str()), Form("%sQ%s", sigStr[sigIter].c_str(), backStr.c_str()), nSigBins[sigIter], sigLow, sigHi[sigIter]);
	sigHist_G_p[centIter][jtIter][sigIter] = new TH1F(Form("%sG%s", sigStr[sigIter].c_str(), backStr.c_str()), Form("%sG%s", sigStr[sigIter].c_str(), backStr.c_str()), nSigBins[sigIter], sigLow, sigHi[sigIter]);
	sigHist_Else_p[centIter][jtIter][sigIter] = new TH1F(Form("%sElse%s", sigStr[sigIter].c_str(), backStr.c_str()), Form("%sElse%s", sigStr[sigIter].c_str(), backStr.c_str()), nSigBins[sigIter], sigLow, sigHi[sigIter]);
      }

      multHist_Tot_p[centIter][jtIter] = new TH1F(Form("%sTot%s", multStr.c_str(), backStr.c_str()), Form("%sTot%s", multStr.c_str(), backStr.c_str()), nMultBins, multLow, multHi);
      multHist_Q_p[centIter][jtIter] = new TH1F(Form("%sQ%s", multStr.c_str(), backStr.c_str()), Form("%sQ%s", multStr.c_str(), backStr.c_str()), nMultBins, multLow, multHi);
      multHist_G_p[centIter][jtIter] = new TH1F(Form("%sG%s", multStr.c_str(), backStr.c_str()), Form("%sG%s", multStr.c_str(), backStr.c_str()), nMultBins, multLow, multHi);
      multHist_Else_p[centIter][jtIter] = new TH1F(Form("%sElse%s", multStr.c_str(), backStr.c_str()), Form("%sElse%s", multStr.c_str(), backStr.c_str()), nMultBins, multLow, multHi);


      for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	tau21Hist_Tot_p[centIter][jtIter][betaIter] = new TH1F(Form("%sTot%s", tau21Str[betaIter].c_str(), backStr.c_str()), Form("%sTot%s", tau21Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau21Hist_Q_p[centIter][jtIter][betaIter] = new TH1F(Form("%sQ%s", tau21Str[betaIter].c_str(), backStr.c_str()), Form("%sQ%s", tau21Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau21Hist_G_p[centIter][jtIter][betaIter] = new TH1F(Form("%sG%s", tau21Str[betaIter].c_str(), backStr.c_str()), Form("%sG%s", tau21Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau21Hist_Else_p[centIter][jtIter][betaIter] = new TH1F(Form("%sElse%s", tau21Str[betaIter].c_str(), backStr.c_str()), Form("%sElse%s", tau21Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);

	tau32Hist_Tot_p[centIter][jtIter][betaIter] = new TH1F(Form("%sTot%s", tau32Str[betaIter].c_str(), backStr.c_str()), Form("%sTot%s", tau32Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau32Hist_Q_p[centIter][jtIter][betaIter] = new TH1F(Form("%sQ%s", tau32Str[betaIter].c_str(), backStr.c_str()), Form("%sQ%s", tau32Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau32Hist_G_p[centIter][jtIter][betaIter] = new TH1F(Form("%sG%s", tau32Str[betaIter].c_str(), backStr.c_str()), Form("%sG%s", tau32Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau32Hist_Else_p[centIter][jtIter][betaIter] = new TH1F(Form("%sElse%s", tau32Str[betaIter].c_str(), backStr.c_str()), Form("%sElse%s", tau32Str[betaIter].c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
      }

      for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
	subRatHist_Tot_p[centIter][jtIter][subJtIter] = new TH1F(Form("%sTot%s", ratStr[subJtIter].c_str(), backStr.c_str()), Form("%sTot%s", ratStr[subJtIter].c_str(), backStr.c_str()), nSubBins, subLow, subHi);
	subRatHist_Q_p[centIter][jtIter][subJtIter] = new TH1F(Form("%sQ%s", ratStr[subJtIter].c_str(), backStr.c_str()), Form("%sQ%s", ratStr[subJtIter].c_str(), backStr.c_str()), nSubBins, subLow, subHi);
	subRatHist_G_p[centIter][jtIter][subJtIter] = new TH1F(Form("%sG%s", ratStr[subJtIter].c_str(), backStr.c_str()), Form("%sG%s", ratStr[subJtIter].c_str(), backStr.c_str()), nSubBins, subLow, subHi);
	subRatHist_Else_p[centIter][jtIter][subJtIter] = new TH1F(Form("%sElse%s", ratStr[subJtIter].c_str(), backStr.c_str()), Form("%sElse%s", ratStr[subJtIter].c_str(), backStr.c_str()), nSubBins, subLow, subHi);
      }

      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
	ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter] = new TH1F(Form("%sTot%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), Form("%sTot%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), nFFMBins[ffmIter], ffmLow, ffmHi[ffmIter]);
	ffmUnsubHist_Q_p[centIter][jtIter][ffmIter] = new TH1F(Form("%sQ%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), Form("%sQ%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), nFFMBins[ffmIter], ffmLow, ffmHi[ffmIter]);
	ffmUnsubHist_G_p[centIter][jtIter][ffmIter] = new TH1F(Form("%sG%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), Form("%sG%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), nFFMBins[ffmIter], ffmLow, ffmHi[ffmIter]);
	ffmUnsubHist_Else_p[centIter][jtIter][ffmIter] = new TH1F(Form("%sElse%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), Form("%sElse%s", ffmUnsubStr[ffmIter].c_str(), backStr.c_str()), nFFMBins[ffmIter], ffmLow, ffmHi[ffmIter]);
      }
    }
  }

  return;
}

void CleanHist(TH1F* cleanHist_p)
{
  if(cleanHist_p!=0){
    delete cleanHist_p;
    cleanHist_p = 0;
  }
  return;
}

void CleanHistAll(sampleType sType)
{
  const Bool_t hi = isHI(sType);

  Int_t centBin = 1;
  if(hi) centBin = centHIMax;

  for(Int_t jtIter = 0; jtIter < jtMax; jtIter++){
    if(hi) CleanHist(ptdHiBinHist_p[jtIter]);

    for(Int_t centIter = 0; centIter < centBin; centIter++){
      CleanHist(ptdHist_Tot_p[centIter][jtIter]);
      CleanHist(ptdHist_Q_p[centIter][jtIter]);
      CleanHist(ptdHist_G_p[centIter][jtIter]);
      CleanHist(ptdHist_Else_p[centIter][jtIter]);

      for(Int_t sigmaIter = 0; sigmaIter < nSigma; sigmaIter++){
	CleanHist(sigHist_Tot_p[centIter][jtIter][sigmaIter]);
	CleanHist(sigHist_Q_p[centIter][jtIter][sigmaIter]);
	CleanHist(sigHist_G_p[centIter][jtIter][sigmaIter]);
	CleanHist(sigHist_Else_p[centIter][jtIter][sigmaIter]);
      }

      CleanHist(multHist_Tot_p[centIter][jtIter]);
      CleanHist(multHist_Q_p[centIter][jtIter]);
      CleanHist(multHist_G_p[centIter][jtIter]);
      CleanHist(multHist_Else_p[centIter][jtIter]);

      for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	CleanHist(tau21Hist_Tot_p[centIter][jtIter][betaIter]);
	CleanHist(tau21Hist_Q_p[centIter][jtIter][betaIter]);
	CleanHist(tau21Hist_G_p[centIter][jtIter][betaIter]);
	CleanHist(tau21Hist_Else_p[centIter][jtIter][betaIter]);

	CleanHist(tau32Hist_Tot_p[centIter][jtIter][betaIter]);
	CleanHist(tau32Hist_Q_p[centIter][jtIter][betaIter]);
	CleanHist(tau32Hist_G_p[centIter][jtIter][betaIter]);
	CleanHist(tau32Hist_Else_p[centIter][jtIter][betaIter]);
      }

      for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
	CleanHist(subRatHist_Tot_p[centIter][jtIter][subJtIter]);
	CleanHist(subRatHist_Q_p[centIter][jtIter][subJtIter]);
	CleanHist(subRatHist_G_p[centIter][jtIter][subJtIter]);
	CleanHist(subRatHist_Else_p[centIter][jtIter][subJtIter]);
      }

      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
	CleanHist(ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter]);
	CleanHist(ffmUnsubHist_Q_p[centIter][jtIter][ffmIter]);
	CleanHist(ffmUnsubHist_G_p[centIter][jtIter][ffmIter]);
	CleanHist(ffmUnsubHist_Else_p[centIter][jtIter][ffmIter]);
      }

    }
  }

  return;
}


void ScaleHistAll(sampleType sType)
{
  const Bool_t hi = isHI(sType);

  Int_t centBin = 1;
  if(hi) centBin = centHIMax;

  for(Int_t jtIter = 0; jtIter < jtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centBin; centIter++){
      ptdHist_Q_p[centIter][jtIter]->Scale(1./ptdHist_Tot_p[centIter][jtIter]->Integral());
      ptdHist_G_p[centIter][jtIter]->Scale(1./ptdHist_Tot_p[centIter][jtIter]->Integral());
      ptdHist_Else_p[centIter][jtIter]->Scale(1./ptdHist_Tot_p[centIter][jtIter]->Integral());
      ptdHist_Tot_p[centIter][jtIter]->Scale(1./ptdHist_Tot_p[centIter][jtIter]->Integral());

      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	sigHist_Q_p[centIter][jtIter][sigIter]->Scale(1./sigHist_Tot_p[centIter][jtIter][sigIter]->Integral());
	sigHist_G_p[centIter][jtIter][sigIter]->Scale(1./sigHist_Tot_p[centIter][jtIter][sigIter]->Integral());
	sigHist_Else_p[centIter][jtIter][sigIter]->Scale(1./sigHist_Tot_p[centIter][jtIter][sigIter]->Integral());
	sigHist_Tot_p[centIter][jtIter][sigIter]->Scale(1./sigHist_Tot_p[centIter][jtIter][sigIter]->Integral());
      }

      multHist_Q_p[centIter][jtIter]->Scale(1./multHist_Tot_p[centIter][jtIter]->Integral());
      multHist_G_p[centIter][jtIter]->Scale(1./multHist_Tot_p[centIter][jtIter]->Integral());
      multHist_Else_p[centIter][jtIter]->Scale(1./multHist_Tot_p[centIter][jtIter]->Integral());
      multHist_Tot_p[centIter][jtIter]->Scale(1./multHist_Tot_p[centIter][jtIter]->Integral());

      
      for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	tau21Hist_Q_p[centIter][jtIter][betaIter]->Scale(1./tau21Hist_Tot_p[centIter][jtIter][betaIter]->Integral());
	tau21Hist_G_p[centIter][jtIter][betaIter]->Scale(1./tau21Hist_Tot_p[centIter][jtIter][betaIter]->Integral());
	tau21Hist_Else_p[centIter][jtIter][betaIter]->Scale(1./tau21Hist_Tot_p[centIter][jtIter][betaIter]->Integral());
	tau21Hist_Tot_p[centIter][jtIter][betaIter]->Scale(1./tau21Hist_Tot_p[centIter][jtIter][betaIter]->Integral());

	tau32Hist_Q_p[centIter][jtIter][betaIter]->Scale(1./tau32Hist_Tot_p[centIter][jtIter][betaIter]->Integral());
	tau32Hist_G_p[centIter][jtIter][betaIter]->Scale(1./tau32Hist_Tot_p[centIter][jtIter][betaIter]->Integral());
	tau32Hist_Else_p[centIter][jtIter][betaIter]->Scale(1./tau32Hist_Tot_p[centIter][jtIter][betaIter]->Integral());
	tau32Hist_Tot_p[centIter][jtIter][betaIter]->Scale(1./tau32Hist_Tot_p[centIter][jtIter][betaIter]->Integral());
      }
      

      for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
        subRatHist_Q_p[centIter][jtIter][subJtIter]->Scale(1./subRatHist_Tot_p[centIter][jtIter][subJtIter]->Integral());
        subRatHist_G_p[centIter][jtIter][subJtIter]->Scale(1./subRatHist_Tot_p[centIter][jtIter][subJtIter]->Integral());
        subRatHist_Else_p[centIter][jtIter][subJtIter]->Scale(1./subRatHist_Tot_p[centIter][jtIter][subJtIter]->Integral());
	subRatHist_Tot_p[centIter][jtIter][subJtIter]->Scale(1./subRatHist_Tot_p[centIter][jtIter][subJtIter]->Integral());
      }

      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
        ffmUnsubHist_Q_p[centIter][jtIter][ffmIter]->Scale(1./ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter]->Integral());
        ffmUnsubHist_G_p[centIter][jtIter][ffmIter]->Scale(1./ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter]->Integral());
        ffmUnsubHist_Else_p[centIter][jtIter][ffmIter]->Scale(1./ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter]->Integral());
	ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter]->Scale(1./ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter]->Integral());
      }
    }
  }
  return;
}


void WriteHistAll(TFile* outFile_p, sampleType sType)
{
  outFile_p->cd();

  const Bool_t hi = isHI(sType);

  Int_t centBin = 1;
  if(hi) centBin = centHIMax;

  for(Int_t jtIter = 0; jtIter < jtMax; jtIter++){
    if(hi) ptdHiBinHist_p[jtIter]->Write("", TObject::kOverwrite);

    for(Int_t centIter = 0; centIter < centBin; centIter++){
      ptdHist_Q_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      ptdHist_G_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      ptdHist_Else_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      ptdHist_Tot_p[centIter][jtIter]->Write("", TObject::kOverwrite);

      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	sigHist_Q_p[centIter][jtIter][sigIter]->Write("", TObject::kOverwrite);
	sigHist_G_p[centIter][jtIter][sigIter]->Write("", TObject::kOverwrite);
	sigHist_Else_p[centIter][jtIter][sigIter]->Write("", TObject::kOverwrite);
	sigHist_Tot_p[centIter][jtIter][sigIter]->Write("", TObject::kOverwrite);
      }

      multHist_Q_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      multHist_G_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      multHist_Else_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      multHist_Tot_p[centIter][jtIter]->Write("", TObject::kOverwrite);

      for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	tau21Hist_Q_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
	tau21Hist_G_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
	tau21Hist_Else_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
	tau21Hist_Tot_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
	
	tau32Hist_Q_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
	tau32Hist_G_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
	tau32Hist_Else_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
	tau32Hist_Tot_p[centIter][jtIter][betaIter]->Write("", TObject::kOverwrite);
      }
      

      for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
        subRatHist_Tot_p[centIter][jtIter][subJtIter]->Write("", TObject::kOverwrite);
        subRatHist_Q_p[centIter][jtIter][subJtIter]->Write("", TObject::kOverwrite);
        subRatHist_G_p[centIter][jtIter][subJtIter]->Write("", TObject::kOverwrite);
        subRatHist_Else_p[centIter][jtIter][subJtIter]->Write("", TObject::kOverwrite);
      }

      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
        ffmUnsubHist_Tot_p[centIter][jtIter][ffmIter]->Write("", TObject::kOverwrite);
        ffmUnsubHist_Q_p[centIter][jtIter][ffmIter]->Write("", TObject::kOverwrite);
        ffmUnsubHist_G_p[centIter][jtIter][ffmIter]->Write("", TObject::kOverwrite);
        ffmUnsubHist_Else_p[centIter][jtIter][ffmIter]->Write("", TObject::kOverwrite);
      }
      
    }
  }
  return;
}


#endif
