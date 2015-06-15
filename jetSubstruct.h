//=============================================
// Author: Chris McGinn
//
// Jet Substructure Class
// 
//=============================================

#ifndef __JETSUBSTRUCT__
#define __JETSUBSTRUCT__

#include "commonSetup.h"
#include <string>
#include <vector>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "sType.h"
#include "qGType.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TMath.h"
#include "etaPhiFunc.h"
#include "getLogBins.h"

const Int_t nSigma = 3;
const Int_t nTau = 3;
const Int_t nBeta = 6;
const Int_t nFFM = 14;
const Int_t nSubjet = 5;
const Int_t nSDBeta = 5;
const Int_t nChgBeta = 5;

const Int_t tauArr[nTau] = {1, 2, 3};
const Double_t betaArr[nBeta] = {0.2, 0.5, 1.0, 1.5, 2.0, 3.0};
const Double_t betaSDArr[nSDBeta] = {-0.5, -0.1, 0.0, 0.1, 0.5};
const Double_t betaChgArr[nChgBeta] = {0.3, 0.5, 1.0, 1.5, 2.0};

const std::string betaArrStr[nBeta] = {"0.2", "0.5", "1.0", "1.5", "2.0", "3.0"};
const std::string betaSDArrStr[nSDBeta] = {"-0.5", "-0.1", "0.0", "0.1", "0.5"};
const std::string betaChgArrStr[nChgBeta] = {"0.3", "0.5", "1.0", "1.5", "2.0"};
const std::string ffmArrStr[nFFM] = {"-0.5", "0.0", "0.5", "1.0", "1.5", "2.0", "2.5", "3.0", "3.5", "4.0", "4.5", "5.0", "5.5", "6.0"};

//const Int_t centHIMax = 4;
//const Int_t centArr[centHIMax] = {20, 60, 100, 200};
const Int_t centHIMax = 2;
const Int_t centArr[centHIMax] = {60, 200};
const Int_t histJtMax = 2;
const std::string jtStr[histJtMax] = {"Lead", "Sublead"};

const Int_t nPtBins = 100;
const Float_t ptLow = -0.5;
const Float_t ptHi = 199.5;

const Int_t nEtaBins = 20;
const Float_t etaLow = -2.0;
const Float_t etaHi = 2.0;

const Int_t nPhiBins = 20;
const Float_t phiLow = -TMath::Pi();
const Float_t phiHi = TMath::Pi();

const Int_t nConstBins = 50;
const Float_t constLow = -0.001;
const Float_t constHi = 99.999;

const Int_t nSDSymmZBins = 10;
const Float_t sdSymmZLow = 0.05;
const Float_t sdSymmZHi = 0.5000;

const Int_t nPTDBins = 20;
const Float_t ptdLow = -0.0001;
const Float_t ptdHi = 1.0001;

const Int_t nChgBins = 20;
const Float_t chgLow = 0.0001;
const Float_t chgHi = 1.4999;

const Int_t nR2Bins = 20;
const Float_t r2Low = 0.0001;
const Float_t r2Hi = .1999;

const Int_t nSigmaBins = 20;
const Float_t sigmaLow = 0.0001;
const Float_t sigmaHi = .1999;

const Int_t nFFMBins = 50;
Float_t ffmBins[nFFMBins+1];
const Float_t ffmLow = 0.0001;
const Float_t ffmHi = 99.9999;

const Int_t nSubJtRatBins = 20;
const Float_t subJtRatLow = -0.0001;
const Float_t subJtRatHi = 1.0001;

const Int_t nSubJtDRBins = 10;
const Float_t subJtDRLow = 0.0001;
const Float_t subJtDRHi = .4999;

const Int_t nSubJtEtaBins = 10;
const Float_t subJtEtaLow = -0.5;
const Float_t subJtEtaHi = 0.5;

const Int_t nSubJtPhiBins = 10;
const Float_t subJtPhiLow = -0.5;
const Float_t subJtPhiHi = 0.5;

class JetSubstruct{
public:
  JetSubstruct(){};
  ~JetSubstruct(){};

  //declare arrays much yolo
  Int_t nJt_;
  Float_t jtPt_[maxJets];
  Float_t jtPhi_[maxJets];
  Float_t jtEta_[maxJets];
  Int_t jtMatchIndex_[maxJets];
  Float_t jtMatchPt_[maxJets];
  Float_t jtMatchPhi_[maxJets];
  Float_t jtMatchEta_[maxJets];
  Int_t jtConstN_[maxJets];
  Float_t jtSoftPt_[maxJets][nSDBeta];
  Float_t jtSoftSymmZ_[maxJets][nSDBeta];
  Float_t jtPTD_[maxJets];
  Float_t jtChg_[maxJets][nChgBeta];
  Float_t jtR2_[maxJets];
  Float_t jtSigma_[maxJets][nSigma];
  Int_t jtRefPart_[maxJets];
  Float_t jtFFMUnsub_[maxJets][nFFM];
  Float_t jtFFMSub_[maxJets][nFFM];
  Float_t jtFFMSubBetter_[maxJets][nFFM];
  Float_t jtTau_[maxJets][nTau][nBeta];
  Float_t subJtPt_[maxJets][nSubjet];
  Float_t subJtPhi_[maxJets][nSubjet];
  Float_t subJtEta_[maxJets][nSubjet];
  Float_t subJtScalePt_[maxJets][nSubjet];
};

const Int_t nTH1_ = 15;
const Int_t nTH1Sub_[nTH1_] = {1, 1, 1, 1, nSDBeta, nSDBeta, 1, nChgBeta, 1, nSigma, nFFM, nFFM, nFFM, nSubjet, nSubjet};
const std::string th1Str_[nTH1_] = {"pt", "phi", "eta", "constN", "sdPt", "sdSymmZ", "ptd", "chg", "r2", "sigma", "ffmUnsub", "ffmSub", "ffmSubBetter", "subJetRat", "subJtDR"};
const std::string xTit_[nTH1_] = {"p_{T}", "#phi", "#eta", "N_{Const}", "p_{T}; SD #beta=", "z_{symm}; #beta=", "p_{T}D", "Jet Charge; #kappa=", "R_{2}", "#sigma", "ffmUnsub; N=", "ffmSub; N=", "ffmSubBetter; N=", "p_{T} Ratio; Subjet=", "#DeltaR; Subjet="};

class JetSubstructHist{
public:
  JetSubstructHist(){};
  ~JetSubstructHist(){};

  //declare arrays much yolo                                                                                 

  TH1F* ptHist_p[centHIMax][histJtMax]; //0
  TH1F* phiHist_p[centHIMax][histJtMax]; //1
  TH1F* etaHist_p[centHIMax][histJtMax]; //2
  TH1F* constNHist_p[centHIMax][histJtMax]; //3
  TH1F* softPtHist_p[centHIMax][histJtMax][nSDBeta]; //4
  TH1F* softSymmZHist_p[centHIMax][histJtMax][nSDBeta]; //5
  TH1F* ptdHist_p[centHIMax][histJtMax]; //6
  TH1F* chgHist_p[centHIMax][histJtMax][nChgBeta]; //7
  TH1F* r2Hist_p[centHIMax][histJtMax]; //8
  TH1F* sigmaHist_p[centHIMax][histJtMax][nSigma]; //9
  TH1F* ffmUnsubHist_p[centHIMax][histJtMax][nFFM]; //10
  TH1F* ffmSubHist_p[centHIMax][histJtMax][nFFM]; //11
  TH1F* ffmSubBetterHist_p[centHIMax][histJtMax][nFFM]; //12
  TH1F* subJtRatHist_p[centHIMax][histJtMax][nSubjet]; //13
  TH1F* subJtDRHist_p[centHIMax][histJtMax][nSubjet]; //14
  TH2F* subJtCorrHist_p[centHIMax][histJtMax][nSubjet];

  TH1F* softPtHist_Mean_p[centHIMax][histJtMax];
  TH1F* softSymmZHist_Mean_p[centHIMax][histJtMax];
  
  TH1F* ffmUnsubHist_Mean_p[centHIMax][histJtMax];
  TH1F* ffmSubHist_Mean_p[centHIMax][histJtMax];
  TH1F* ffmSubBetterHist_Mean_p[centHIMax][histJtMax];

  TH1F* activeTH1_p;

  Bool_t GetTH1ErrorCheck(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum);
  void SetActiveTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum);
  void SetActiveMeanTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum);
  TH1F GetActiveTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum);
  TH1F GetActiveMeanTH1(const Int_t hisNum, const Int_t centNum, const Int_t jtNum);
};


Bool_t JetSubstructHist::GetTH1ErrorCheck(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum)
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

void JetSubstructHist::SetActiveTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum)
{
  if(!GetTH1ErrorCheck(histNum, centNum, jtNum, subNum)) return;
  
  if(histNum == 0) activeTH1_p = (TH1F*)(ptHist_p[centNum][jtNum]);
  else if(histNum == 1) activeTH1_p = (TH1F*)(phiHist_p[centNum][jtNum]);
  else if(histNum == 2) activeTH1_p = (TH1F*)(etaHist_p[centNum][jtNum]);
  else if(histNum == 3) activeTH1_p = (TH1F*)(constNHist_p[centNum][jtNum]);
  else if(histNum == 4) activeTH1_p = (TH1F*)(softPtHist_p[centNum][jtNum][subNum]);
  else if(histNum == 5) activeTH1_p = (TH1F*)(softSymmZHist_p[centNum][jtNum][subNum]);
  else if(histNum == 6) activeTH1_p = (TH1F*)(ptdHist_p[centNum][jtNum]);
  else if(histNum == 7) activeTH1_p = (TH1F*)(chgHist_p[centNum][jtNum][subNum]);
  else if(histNum == 8) activeTH1_p = (TH1F*)(r2Hist_p[centNum][jtNum]);
  else if(histNum == 9) activeTH1_p = (TH1F*)(sigmaHist_p[centNum][jtNum][subNum]);
  else if(histNum == 10) activeTH1_p = (TH1F*)(ffmUnsubHist_p[centNum][jtNum][subNum]);
  else if(histNum == 11) activeTH1_p = (TH1F*)(ffmSubHist_p[centNum][jtNum][subNum]);
  else if(histNum == 12) activeTH1_p = (TH1F*)(ffmSubBetterHist_p[centNum][jtNum][subNum]);
  else if(histNum == 13) activeTH1_p = (TH1F*)(subJtRatHist_p[centNum][jtNum][subNum]);
  else if(histNum == 14) activeTH1_p = (TH1F*)(subJtDRHist_p[centNum][jtNum][subNum]);
  
  return;
}


void JetSubstructHist::SetActiveMeanTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum)
{
  if(histNum == 5) activeTH1_p = (TH1F*)(softSymmZHist_Mean_p[centNum][jtNum]);
  else if(histNum == 10) activeTH1_p = (TH1F*)(ffmUnsubHist_Mean_p[centNum][jtNum]);
  else if(histNum == 11) activeTH1_p = (TH1F*)(ffmSubHist_Mean_p[centNum][jtNum]);
  else if(histNum == 12) activeTH1_p = (TH1F*)(ffmSubBetterHist_Mean_p[centNum][jtNum]);
  
  return;
}


TH1F JetSubstructHist::GetActiveTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum, const Int_t subNum)
{
  TH1F histRet_h;

  if(!GetTH1ErrorCheck(histNum, centNum, jtNum, subNum)) return histRet_h;

  if(histNum == 0) return *(ptHist_p[centNum][jtNum]);
  else if(histNum == 1) return *(phiHist_p[centNum][jtNum]);
  else if(histNum == 2) return *(etaHist_p[centNum][jtNum]);
  else if(histNum == 3) return *(constNHist_p[centNum][jtNum]);
  else if(histNum == 4) return *(softPtHist_p[centNum][jtNum][subNum]);
  else if(histNum == 5) return *(softSymmZHist_p[centNum][jtNum][subNum]);
  else if(histNum == 6) return *(ptdHist_p[centNum][jtNum]);
  else if(histNum == 7) return *(chgHist_p[centNum][jtNum][subNum]);
  else if(histNum == 8) return *(r2Hist_p[centNum][jtNum]);
  else if(histNum == 9) return *(sigmaHist_p[centNum][jtNum][subNum]);
  else if(histNum == 10) return *(ffmUnsubHist_p[centNum][jtNum][subNum]);
  else if(histNum == 11) return *(ffmSubHist_p[centNum][jtNum][subNum]);
  else if(histNum == 12) return *(ffmSubBetterHist_p[centNum][jtNum][subNum]);
  else if(histNum == 13) return *(subJtRatHist_p[centNum][jtNum][subNum]);
  else if(histNum == 14) return *(subJtDRHist_p[centNum][jtNum][subNum]);

  return histRet_h;
}

TH1F JetSubstructHist::GetActiveMeanTH1(const Int_t histNum, const Int_t centNum, const Int_t jtNum)
{
  TH1F histRet_h;

  if(histNum == 5) return *(softSymmZHist_Mean_p[centNum][jtNum]);
  else if(histNum == 10) return *(ffmUnsubHist_Mean_p[centNum][jtNum]);
  else if(histNum == 11) return *(ffmSubHist_Mean_p[centNum][jtNum]);
  else if(histNum == 12) return *(ffmSubBetterHist_Mean_p[centNum][jtNum]);

  return histRet_h;
}


//Forward declaration of relevant functions
void SetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName);
void GetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName);
void InitJetSubstructHist(JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName);
void GetJetSubstructHist(TFile* histFile_p, JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName);
void FillJetSubstructHist(JetSubstruct* inJt_p, JetSubstructHist* inJtHist_p, sampleType sType, Int_t hiBin, Float_t weight, qGType qG);
void ScaleJetSubstructHist(JetSubstructHist* num_p, JetSubstructHist* denom_p, sampleType sType);
void WriteJetSubstructHist(TFile* outFile_p, JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName, const std::string fillName2);
void CleanupJetSubstructHist(JetSubstructHist* inJtHist_p, sampleType sType);


void SetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName)
{
  inTree_p->Branch(Form("%s_nJt", fillName.c_str()), &inJt_p->nJt_, Form("%s_nJt/I", fillName.c_str()));
  inTree_p->Branch(Form("%s_jtPt", fillName.c_str()), inJt_p->jtPt_, Form("%s_jtPt[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtPhi", fillName.c_str()), inJt_p->jtPhi_, Form("%s_jtPhi[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtEta", fillName.c_str()), inJt_p->jtEta_, Form("%s_jtEta[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtMatchIndex", fillName.c_str()), inJt_p->jtMatchIndex_, Form("%s_jtMatchIndex[%s_nJt]/I", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtMatchPt", fillName.c_str()), inJt_p->jtMatchPt_, Form("%s_jtMatchPt[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtMatchPhi", fillName.c_str()), inJt_p->jtMatchPhi_, Form("%s_jtMatchPhi[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtMatchEta", fillName.c_str()), inJt_p->jtMatchEta_, Form("%s_jtMatchEta[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtConstN", fillName.c_str()), inJt_p->jtConstN_, Form("%s_jtConstN[%s_nJt]/I", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtSoftPt", fillName.c_str()), inJt_p->jtSoftPt_, Form("%s_jtSoftPt[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSDBeta));
  inTree_p->Branch(Form("%s_jtSoftSymmZ", fillName.c_str()), inJt_p->jtSoftSymmZ_, Form("%s_jtSoftSymmZ[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSDBeta));
  inTree_p->Branch(Form("%s_jtPTD", fillName.c_str()), inJt_p->jtPTD_, Form("%s_jtPTD[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtChg", fillName.c_str()), inJt_p->jtChg_, Form("%s_jtChg[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nChgBeta));
  inTree_p->Branch(Form("%s_jtR2", fillName.c_str()), inJt_p->jtR2_, Form("%s_jtR2[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtSigma", fillName.c_str()), inJt_p->jtSigma_, Form("%s_jtSigma[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSigma));
  inTree_p->Branch(Form("%s_jtRefPart", fillName.c_str()), inJt_p->jtRefPart_, Form("%s_jtRefPart[%s_nJt]/I", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtFFMUnsub", fillName.c_str()), inJt_p->jtFFMUnsub_, Form("%s_jtFFMUnsub[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nFFM));
  inTree_p->Branch(Form("%s_jtFFMSub", fillName.c_str()), inJt_p->jtFFMSub_, Form("%s_jtFFMSub[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nFFM));
  inTree_p->Branch(Form("%s_jtFFMSubBetter", fillName.c_str()), inJt_p->jtFFMSubBetter_, Form("%s_jtFFMSubBetter[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nFFM));
  inTree_p->Branch(Form("%s_jtTau", fillName.c_str()), inJt_p->jtTau_, Form("%s_jtTau[%s_nJt][%d][%d]/F", fillName.c_str(), fillName.c_str(), nTau, nBeta));
  inTree_p->Branch(Form("%s_subJtPt", fillName.c_str()), inJt_p->subJtPt_, Form("%s_subJtPt[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSubjet));
  inTree_p->Branch(Form("%s_subJtPhi", fillName.c_str()), inJt_p->subJtPhi_, Form("%s_subJtPhi[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSubjet));
  inTree_p->Branch(Form("%s_subJtEta", fillName.c_str()), inJt_p->subJtEta_, Form("%s_subJtEta[%s_nJt][%d]/F", fillName.c_str(),fillName.c_str(), nSubjet));
  inTree_p->Branch(Form("%s_subJtScalePt", fillName.c_str()), inJt_p->subJtScalePt_, Form("%s_subJtScalePt[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSubjet));

  return;
}


void GetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName)
{
  inTree_p->SetBranchAddress(Form("%s_nJt", fillName.c_str()), &inJt_p->nJt_);
  inTree_p->SetBranchAddress(Form("%s_jtPt", fillName.c_str()), inJt_p->jtPt_);
  inTree_p->SetBranchAddress(Form("%s_jtPhi", fillName.c_str()), inJt_p->jtPhi_);
  inTree_p->SetBranchAddress(Form("%s_jtEta", fillName.c_str()), inJt_p->jtEta_);
  inTree_p->SetBranchAddress(Form("%s_jtMatchIndex", fillName.c_str()), inJt_p->jtMatchIndex_);
  inTree_p->SetBranchAddress(Form("%s_jtMatchPt", fillName.c_str()), inJt_p->jtMatchPt_);
  inTree_p->SetBranchAddress(Form("%s_jtMatchPhi", fillName.c_str()), inJt_p->jtMatchPhi_);
  inTree_p->SetBranchAddress(Form("%s_jtMatchEta", fillName.c_str()), inJt_p->jtMatchEta_);
  inTree_p->SetBranchAddress(Form("%s_jtConstN", fillName.c_str()), inJt_p->jtConstN_);
  inTree_p->SetBranchAddress(Form("%s_jtSoftPt", fillName.c_str()), inJt_p->jtSoftPt_);
  inTree_p->SetBranchAddress(Form("%s_jtSoftSymmZ", fillName.c_str()), inJt_p->jtSoftSymmZ_);
  inTree_p->SetBranchAddress(Form("%s_jtPTD", fillName.c_str()), inJt_p->jtPTD_);
  inTree_p->SetBranchAddress(Form("%s_jtChg", fillName.c_str()), inJt_p->jtChg_);
  inTree_p->SetBranchAddress(Form("%s_jtR2", fillName.c_str()), inJt_p->jtR2_);
  inTree_p->SetBranchAddress(Form("%s_jtSigma", fillName.c_str()), inJt_p->jtSigma_);
  inTree_p->SetBranchAddress(Form("%s_jtRefPart", fillName.c_str()), inJt_p->jtRefPart_);
  inTree_p->SetBranchAddress(Form("%s_jtFFMUnsub", fillName.c_str()), inJt_p->jtFFMUnsub_);
  inTree_p->SetBranchAddress(Form("%s_jtFFMSub", fillName.c_str()), inJt_p->jtFFMSub_);
  inTree_p->SetBranchAddress(Form("%s_jtFFMSubBetter", fillName.c_str()), inJt_p->jtFFMSubBetter_);
  inTree_p->SetBranchAddress(Form("%s_jtTau", fillName.c_str()), inJt_p->jtTau_);
  inTree_p->SetBranchAddress(Form("%s_subJtPt", fillName.c_str()), inJt_p->subJtPt_);
  inTree_p->SetBranchAddress(Form("%s_subJtPhi", fillName.c_str()), inJt_p->subJtPhi_);
  inTree_p->SetBranchAddress(Form("%s_subJtEta", fillName.c_str()), inJt_p->subJtEta_);
  inTree_p->SetBranchAddress(Form("%s_subJtScalePt", fillName.c_str()), inJt_p->subJtScalePt_);

  return;
}


void GetMeanBinning(const Int_t nArr, const Double_t arr[], Int_t &outNBins, Float_t &outMin, Float_t &outMax)
{
  Float_t max = arr[nArr-1];
  Float_t min = arr[0];

  Float_t minDiff = arr[1] - arr[0];

  for(Int_t iter = 1; iter < nArr-1; iter++){
    if(arr[iter+1] - arr[iter] < minDiff) minDiff = arr[iter+1] - arr[iter];
  }

  outMin = min - minDiff/2;
  outMax = max + minDiff/2;
  outNBins = (outMax-outMin)/minDiff;

  return;
}


void InitJetSubstructHist(JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName)
{
  std::string hiBinOrPPPA[centHIMax] = {"030", "30100"};
//  std::string hiBinOrPPPA[centHIMax] = {"010", "1030", "3050", "50100"};
  if(sType == kPPDATA || sType == kPPMC) hiBinOrPPPA[0] = "PP";
  else if(sType == kPADATA || sType == kPAMC) hiBinOrPPPA[0] = "PA";

  Int_t centMax = 1;
  if(isHI(sType)) centMax = centHIMax;

  for(Int_t jtIter = 0; jtIter < histJtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centMax; centIter++){
      inJtHist_p->ptHist_p[centIter][jtIter] = new TH1F(Form("%s_pt_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_pt_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nPtBins, ptLow, ptHi);

      inJtHist_p->etaHist_p[centIter][jtIter] = new TH1F(Form("%s_eta_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_eta_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nEtaBins, etaLow, etaHi);

      inJtHist_p->phiHist_p[centIter][jtIter] = new TH1F(Form("%s_phi_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_phi_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nPhiBins, phiLow, phiHi);

      inJtHist_p->constNHist_p[centIter][jtIter] = new TH1F(Form("%s_constN_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_constN_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nConstBins, constLow, constHi);

      inJtHist_p->r2Hist_p[centIter][jtIter] = new TH1F(Form("%s_r2_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_r2_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nR2Bins, r2Low, r2Hi);

      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter] = new TH1F(Form("%s_softSymmZBeta%d_%s_%s_h", fillName.c_str(), sdIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_softSymmZBeta%d_%s_%s_h", fillName.c_str(), sdIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nSDSymmZBins, sdSymmZLow, sdSymmZHi);
      }

      Int_t nBinZSymmMean;
      Float_t binZSymmMeanLow, binZSymmMeanHi;
      GetMeanBinning(nSDBeta, betaSDArr, nBinZSymmMean, binZSymmMeanLow, binZSymmMeanHi);
      inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter] = new TH1F(Form("%s_softSymmZ_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_softSymmZ_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nBinZSymmMean, binZSymmMeanLow, binZSymmMeanHi);

      inJtHist_p->ptdHist_p[centIter][jtIter] = new TH1F(Form("%s_PTD_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_PTD_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nPTDBins, ptdLow, ptdHi);  

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	inJtHist_p->chgHist_p[centIter][jtIter][chgIter] = new TH1F(Form("%s_chgBeta%d_%s_%s_h", fillName.c_str(), chgIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_chgBeta%d_%s_%s_h", fillName.c_str(), chgIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nChgBins, chgLow, chgHi);
      }

      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	inJtHist_p->sigmaHist_p[centIter][jtIter][sigIter] = new TH1F(Form("%s_sigma%d_%s_%s_h", fillName.c_str(), sigIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_sigma%d_%s_%s_h", fillName.c_str(), sigIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nSigmaBins, sigmaLow, sigmaHi);
      }

      getLogBins(ffmLow, ffmHi, nFFMBins, ffmBins);
      Double_t ffmArr[nFFM];
      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
	ffmArr[ffmIter] = ffmIter;
	ffmArr[ffmIter] /= 2;
	ffmArr[ffmIter] -= 0.5;

	inJtHist_p->ffmUnsubHist_p[centIter][jtIter][ffmIter] = new TH1F(Form("%s_ffmUnsub%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_ffmUnsub%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nFFMBins, ffmBins);

	inJtHist_p->ffmSubHist_p[centIter][jtIter][ffmIter] = new TH1F(Form("%s_ffmSub%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_ffmSub%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nFFMBins, ffmBins);

	inJtHist_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter] = new TH1F(Form("%s_ffmSubBetter%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_ffmSubBetter%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nFFMBins, ffmBins);
      }   

      Int_t nBinFFMMean;
      Float_t binFFMMeanLow, binFFMMeanHi;
      GetMeanBinning(nFFM, ffmArr, nBinFFMMean, binFFMMeanLow, binFFMMeanHi);

      inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter] = new TH1F(Form("%s_ffmUnsub_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_ffmUnsub_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nBinFFMMean, binFFMMeanLow, binFFMMeanHi);

      inJtHist_p->ffmSubHist_Mean_p[centIter][jtIter] = new TH1F(Form("%s_ffmSub_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_ffmSub_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nBinFFMMean, binFFMMeanLow, binFFMMeanHi);

      inJtHist_p->ffmSubBetterHist_Mean_p[centIter][jtIter] = new TH1F(Form("%s_ffmSubBetter_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_ffmSubBetter_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nBinFFMMean, binFFMMeanLow, binFFMMeanHi);

      for(Int_t subIter = 0; subIter < nSubjet; subIter++){
	inJtHist_p->subJtRatHist_p[centIter][jtIter][subIter] = new TH1F(Form("%s_subJtRat%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_subJtRat%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nSubJtRatBins, subJtRatLow, subJtRatHi);

	inJtHist_p->subJtDRHist_p[centIter][jtIter][subIter] = new TH1F(Form("%s_subJtDR%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_subJtDR%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nSubJtDRBins, subJtDRLow, subJtDRHi);

	inJtHist_p->subJtCorrHist_p[centIter][jtIter][subIter] = new TH2F(Form("%s_subJtCorr%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_subJtCorr%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nSubJtEtaBins, subJtEtaLow, subJtEtaHi, nSubJtPhiBins, subJtPhiLow, subJtPhiHi);
      }
    }
  }

  return;
}


void GetJetSubstructHist(TFile* histFile_p, JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName)
{
  std::string hiBinOrPPPA[2] = {"030", "30100"};
  //  std::string hiBinOrPPPA[centHIMax] = {"010", "1030", "3050", "50100"};
  if(sType == kPPDATA || sType == kPPMC) hiBinOrPPPA[0] = "PP";
  else if(sType == kPADATA || sType == kPAMC) hiBinOrPPPA[0] = "PA";

  Int_t centMax = 1;
  if(isHI(sType)) centMax = centHIMax;

  for(Int_t jtIter = 0; jtIter < histJtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centMax; centIter++){
      inJtHist_p->ptHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_pt_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->etaHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_eta_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->phiHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_phi_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->constNHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_constN_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));


      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter] = (TH1F*)histFile_p->Get(Form("%s_softSymmZBeta%d_%s_%s_h", fillName.c_str(), sdIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));
      }

	inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_softSymmZ_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->ptdHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_PTD_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      if(!strcmp("T", fillName.substr(0, 1).c_str())){
	for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	  inJtHist_p->chgHist_p[centIter][jtIter][chgIter] = (TH1F*)histFile_p->Get(Form("%s_chgBeta%d_%s_%s_h", fillName.c_str(), chgIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));
	}
      }

      inJtHist_p->r2Hist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_r2_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
        inJtHist_p->sigmaHist_p[centIter][jtIter][sigIter] = (TH1F*)histFile_p->Get(Form("%s_sigma%d_%s_%s_h", fillName.c_str(), sigIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));
      }

      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
        inJtHist_p->ffmUnsubHist_p[centIter][jtIter][ffmIter] = (TH1F*)histFile_p->Get(Form("%s_ffmUnsub%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

        inJtHist_p->ffmSubHist_p[centIter][jtIter][ffmIter] = (TH1F*)histFile_p->Get(Form("%s_ffmSub%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

        inJtHist_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter] = (TH1F*)histFile_p->Get(Form("%s_ffmSubBetter%d_%s_%s_h", fillName.c_str(), ffmIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));
      }

      inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_ffmUnsub_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->ffmSubHist_Mean_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_ffmSub_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->ffmSubBetterHist_Mean_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_ffmSubBetter_Mean_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      for(Int_t subIter = 0; subIter < nSubjet; subIter++){
        inJtHist_p->subJtRatHist_p[centIter][jtIter][subIter] = (TH1F*)histFile_p->Get(Form("%s_subJtRat%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

        inJtHist_p->subJtDRHist_p[centIter][jtIter][subIter] = (TH1F*)histFile_p->Get(Form("%s_subJtDR%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

	inJtHist_p->subJtCorrHist_p[centIter][jtIter][subIter] = (TH2F*)histFile_p->Get(Form("%s_subJtCorr%d_%s_%s_h", fillName.c_str(), subIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));
      }
    }
  }

  return;
}


void FillJetSubstructHist(JetSubstruct* inJt_p, JetSubstructHist* inJtHist_p, sampleType sType, Int_t hiBin, Float_t weight, qGType qG)
{
  Int_t centPos = 0;
  if(isHI(sType)){
    for(Int_t iter = 0; iter < centHIMax; iter++){
      if(hiBin < centArr[iter]){
	centPos = iter;
	break;
      }
    }
  }

  Bool_t isMC = isMonteCarlo(sType);

  if(qG != Tot && !isMC) return;

  Int_t jtMax = inJt_p->nJt_;
  if(jtMax > histJtMax) jtMax = histJtMax;

  for(Int_t jtIter = 0; jtIter < jtMax; jtIter++){
    if(qG != Tot){
      if(qG == Qua && TMath::Abs(inJt_p->jtRefPart_[jtIter]) > 8) continue;
      else if(qG == Glu && TMath::Abs(inJt_p->jtRefPart_[jtIter]) != 21) continue;
    }
    //    if(qG == Qua) std::cout << "QUARKS! " << jtIter << ", " << inJt_p->jtPt_[jtIter] << ", " << inJt_p->jtRefPart_[jtIter] << ", " << inJt_p->jtChg_[jtIter][0] << std::endl;

    //    if(isMC && TMath::Abs(inJt_p->jtRefPart_[jtIter]) > 900) continue;

    inJtHist_p->ptHist_p[centPos][jtIter]->Fill(inJt_p->jtPt_[jtIter], weight);
    inJtHist_p->etaHist_p[centPos][jtIter]->Fill(inJt_p->jtEta_[jtIter], weight);
    inJtHist_p->phiHist_p[centPos][jtIter]->Fill(inJt_p->jtPhi_[jtIter], weight);
    inJtHist_p->constNHist_p[centPos][jtIter]->Fill(inJt_p->jtConstN_[jtIter], weight);

    for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
      inJtHist_p->softSymmZHist_p[centPos][jtIter][sdIter]->Fill(inJt_p->jtSoftSymmZ_[jtIter][sdIter], weight);
    }

    inJtHist_p->ptdHist_p[centPos][jtIter]->Fill(inJt_p->jtPTD_[jtIter], weight);

    for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
      inJtHist_p->chgHist_p[centPos][jtIter][chgIter]->Fill(TMath::Abs(inJt_p->jtChg_[jtIter][chgIter]), weight);
    }

    inJtHist_p->r2Hist_p[centPos][jtIter]->Fill(inJt_p->jtR2_[jtIter], weight);

    for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
      inJtHist_p->sigmaHist_p[centPos][jtIter][sigIter]->Fill(TMath::Abs(inJt_p->jtSigma_[jtIter][sigIter]), weight);
    }

    for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
      Float_t ffmVal = ffmIter*0.5 - 0.5;
      ffmVal = TMath::Power((ffmVal + 1)/2, 4);

      inJtHist_p->ffmUnsubHist_p[centPos][jtIter][ffmIter]->Fill(TMath::Abs(ffmVal*inJt_p->jtFFMUnsub_[jtIter][ffmIter]), weight);

      inJtHist_p->ffmSubHist_p[centPos][jtIter][ffmIter]->Fill(TMath::Abs(ffmVal*inJt_p->jtFFMSub_[jtIter][ffmIter]), weight);

      inJtHist_p->ffmSubBetterHist_p[centPos][jtIter][ffmIter]->Fill(TMath::Abs(ffmVal*inJt_p->jtFFMSubBetter_[jtIter][ffmIter]), weight);
    }

    for(Int_t subIter = 0; subIter < nSubjet; subIter++){
      inJtHist_p->subJtRatHist_p[centPos][jtIter][subIter]->Fill(inJt_p->subJtPt_[jtIter][subIter]/inJt_p->jtPt_[jtIter], weight);

      Float_t dEta = inJt_p->subJtEta_[jtIter][subIter] - inJt_p->jtEta_[jtIter];
      Float_t dPhi = getDPHI(inJt_p->subJtPhi_[jtIter][subIter], inJt_p->jtPhi_[jtIter]);

      inJtHist_p->subJtDRHist_p[centPos][jtIter][subIter]->Fill(TMath::Sqrt(dEta*dEta + dPhi*dPhi), weight);

      inJtHist_p->subJtCorrHist_p[centPos][jtIter][subIter]->Fill(dEta, dPhi, weight);
    }
  }

  return;
}


void ScaleJetSubstructHist(JetSubstructHist* num_p, JetSubstructHist* denom_p, sampleType sType)
{
  TH1::SetDefaultSumw2();

  Int_t centMax = 1;
  if(isHI(sType)) centMax = centHIMax;

  for(Int_t jtIter = 0; jtIter < histJtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centMax; centIter++){
      num_p->ptHist_p[centIter][jtIter]->Scale(1./denom_p->ptHist_p[centIter][jtIter]->Integral());
      num_p->etaHist_p[centIter][jtIter]->Scale(1./denom_p->etaHist_p[centIter][jtIter]->Integral());
      num_p->phiHist_p[centIter][jtIter]->Scale(1./denom_p->phiHist_p[centIter][jtIter]->Integral());
      num_p->constNHist_p[centIter][jtIter]->Scale(1./denom_p->constNHist_p[centIter][jtIter]->Integral());

      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	num_p->softSymmZHist_p[centIter][jtIter][sdIter]->Scale(1./denom_p->softSymmZHist_p[centIter][jtIter][sdIter]->Integral());
      }

      num_p->ptdHist_p[centIter][jtIter]->Scale(1./denom_p->ptdHist_p[centIter][jtIter]->Integral());

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	num_p->chgHist_p[centIter][jtIter][chgIter]->Scale(1./denom_p->chgHist_p[centIter][jtIter][chgIter]->Integral());
      }

      num_p->r2Hist_p[centIter][jtIter]->Scale(1./denom_p->r2Hist_p[centIter][jtIter]->Integral());

      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	num_p->sigmaHist_p[centIter][jtIter][sigIter]->Scale(1./denom_p->sigmaHist_p[centIter][jtIter][sigIter]->Integral());
      }

      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
	num_p->ffmUnsubHist_p[centIter][jtIter][ffmIter]->Scale(1./denom_p->ffmUnsubHist_p[centIter][jtIter][ffmIter]->Integral());

	num_p->ffmSubHist_p[centIter][jtIter][ffmIter]->Scale(1./denom_p->ffmSubHist_p[centIter][jtIter][ffmIter]->Integral());

	num_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter]->Scale(1./denom_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter]->Integral());
      }

      for(Int_t subIter = 0; subIter < nSubjet; subIter++){
	num_p->subJtRatHist_p[centIter][jtIter][subIter]->Scale(1./denom_p->subJtRatHist_p[centIter][jtIter][subIter]->Integral());

	num_p->subJtDRHist_p[centIter][jtIter][subIter]->Scale(1./denom_p->subJtDRHist_p[centIter][jtIter][subIter]->Integral());

	num_p->subJtCorrHist_p[centIter][jtIter][subIter]->Scale(1./denom_p->subJtCorrHist_p[centIter][jtIter][subIter]->Integral());
      }
    }
  }

  return;
}


void WriteJetSubstructHist(TFile* outFile_p, JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName, const std::string fillName2)
{
  outFile_p->cd();
  const std::string dirName = Form("%s%sDir", fillName.c_str(), fillName2.c_str());

  TDirectory* dir_p = outFile_p->GetDirectory(Form("%s", dirName.c_str()));
  if(dir_p){
    dir_p->cd();
  }
  else{
    dir_p = outFile_p->mkdir(Form("%s", dirName.c_str()));
    dir_p->cd();
  }

  Int_t centMax = 1;
  if(isHI(sType)) centMax = centHIMax;

  for(Int_t jtIter = 0; jtIter < histJtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centMax; centIter++){
      inJtHist_p->ptHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      inJtHist_p->etaHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      inJtHist_p->phiHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      inJtHist_p->constNHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      
      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter]->Write("", TObject::kOverwrite);

	Int_t bin = inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter]->FindBin(betaSDArr[sdIter]);
	Float_t val = inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter]->GetMean();
	Float_t err = inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter]->GetMeanError();
	inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter]->SetBinContent(bin, val);
	inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter]->SetBinError(bin, err);
      }
      inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter]->Write("", TObject::kOverwrite);

      inJtHist_p->ptdHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	inJtHist_p->chgHist_p[centIter][jtIter][chgIter]->Write("", TObject::kOverwrite);
      }

      inJtHist_p->r2Hist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      

      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	inJtHist_p->sigmaHist_p[centIter][jtIter][sigIter]->Write("", TObject::kOverwrite);
      }

      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
	inJtHist_p->ffmUnsubHist_p[centIter][jtIter][ffmIter]->Write("", TObject::kOverwrite);
 	inJtHist_p->ffmSubHist_p[centIter][jtIter][ffmIter]->Write("", TObject::kOverwrite);
	inJtHist_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter]->Write("", TObject::kOverwrite);

	Float_t ffmVal = ffmIter;
	ffmVal /= 2;
	ffmVal -= 0.5;
	Int_t bin = inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter]->FindBin(ffmVal);
	Float_t valUnsub = inJtHist_p->ffmUnsubHist_p[centIter][jtIter][ffmIter]->GetMean();
	Float_t errUnsub = inJtHist_p->ffmUnsubHist_p[centIter][jtIter][ffmIter]->GetMeanError();

	Float_t valSub = inJtHist_p->ffmSubHist_p[centIter][jtIter][ffmIter]->GetMean();
	Float_t errSub = inJtHist_p->ffmSubHist_p[centIter][jtIter][ffmIter]->GetMeanError();

	Float_t valSubBetter = inJtHist_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter]->GetMean();
	Float_t errSubBetter = inJtHist_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter]->GetMeanError();

	inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter]->SetBinContent(bin, valUnsub);
	inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter]->SetBinError(bin, errUnsub);

	inJtHist_p->ffmSubHist_Mean_p[centIter][jtIter]->SetBinContent(bin, valSub);
	inJtHist_p->ffmSubHist_Mean_p[centIter][jtIter]->SetBinError(bin, errSub);

	inJtHist_p->ffmSubBetterHist_Mean_p[centIter][jtIter]->SetBinContent(bin, valSubBetter);
	inJtHist_p->ffmSubBetterHist_Mean_p[centIter][jtIter]->SetBinError(bin, errSubBetter);
      }

      inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      inJtHist_p->ffmSubHist_Mean_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      inJtHist_p->ffmSubBetterHist_Mean_p[centIter][jtIter]->Write("", TObject::kOverwrite);

      for(Int_t subIter = 0; subIter < nSubjet; subIter++){
	inJtHist_p->subJtRatHist_p[centIter][jtIter][subIter]->Write("", TObject::kOverwrite);

	inJtHist_p->subJtDRHist_p[centIter][jtIter][subIter]->Write("", TObject::kOverwrite);

	inJtHist_p->subJtCorrHist_p[centIter][jtIter][subIter]->Write("", TObject::kOverwrite);
      }
    }
  }

  dir_p->Close();

  return;
}


void CleanupJetSubstructHist(JetSubstructHist* inJtHist_p, sampleType sType)
{
  Int_t centMax = 1;
  if(isHI(sType)) centMax = centHIMax;

  for(Int_t jtIter = 0; jtIter < histJtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centMax; centIter++){
      delete inJtHist_p->ptHist_p[centIter][jtIter];
      inJtHist_p->ptHist_p[centIter][jtIter] = 0;
      delete inJtHist_p->etaHist_p[centIter][jtIter];
      inJtHist_p->etaHist_p[centIter][jtIter] = 0;
      delete inJtHist_p->phiHist_p[centIter][jtIter];
      inJtHist_p->phiHist_p[centIter][jtIter] = 0;
      delete inJtHist_p->constNHist_p[centIter][jtIter];
      inJtHist_p->constNHist_p[centIter][jtIter] = 0;

      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	delete inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter];
	inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter] = 0;
      }
      delete inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter];
      inJtHist_p->softSymmZHist_Mean_p[centIter][jtIter] = 0;

      delete inJtHist_p->ptdHist_p[centIter][jtIter];
      inJtHist_p->ptdHist_p[centIter][jtIter] = 0;

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	delete inJtHist_p->chgHist_p[centIter][jtIter][chgIter];
	inJtHist_p->chgHist_p[centIter][jtIter][chgIter] = 0;
      }

      delete inJtHist_p->r2Hist_p[centIter][jtIter];
      inJtHist_p->r2Hist_p[centIter][jtIter] = 0;

      for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	delete inJtHist_p->sigmaHist_p[centIter][jtIter][sigIter];
	inJtHist_p->sigmaHist_p[centIter][jtIter][sigIter] = 0;
      }


      for(Int_t ffmIter = 0; ffmIter < nFFM; ffmIter++){
	delete inJtHist_p->ffmUnsubHist_p[centIter][jtIter][ffmIter];
	inJtHist_p->ffmUnsubHist_p[centIter][jtIter][ffmIter] = 0;

	delete inJtHist_p->ffmSubHist_p[centIter][jtIter][ffmIter];
	inJtHist_p->ffmSubHist_p[centIter][jtIter][ffmIter] = 0;

	delete inJtHist_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter];
	inJtHist_p->ffmSubBetterHist_p[centIter][jtIter][ffmIter] = 0;
      }

      delete inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter];
      inJtHist_p->ffmUnsubHist_Mean_p[centIter][jtIter] = 0;
      
      delete inJtHist_p->ffmSubHist_Mean_p[centIter][jtIter];
      inJtHist_p->ffmSubHist_Mean_p[centIter][jtIter] = 0;
      
      delete inJtHist_p->ffmSubBetterHist_Mean_p[centIter][jtIter];
      inJtHist_p->ffmSubBetterHist_Mean_p[centIter][jtIter] = 0;
      

      for(Int_t subIter = 0; subIter < nSubjet; subIter++){
	delete inJtHist_p->subJtRatHist_p[centIter][jtIter][subIter];
	inJtHist_p->subJtRatHist_p[centIter][jtIter][subIter] = 0;

	delete inJtHist_p->subJtDRHist_p[centIter][jtIter][subIter];
	inJtHist_p->subJtDRHist_p[centIter][jtIter][subIter] = 0;

	delete inJtHist_p->subJtCorrHist_p[centIter][jtIter][subIter];
	inJtHist_p->subJtCorrHist_p[centIter][jtIter][subIter] = 0;
      }
    }
  }

  delete inJtHist_p;
  inJtHist_p = 0;

  return;
}


#endif // __JETSUB__
