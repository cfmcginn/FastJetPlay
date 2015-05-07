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
#include "TH1F.h"
#include "TTree.h"
#include "sType.h"
#include "qGType.h"
#include "TFile.h"
#include "TMath.h"

const Int_t nSigma = 3;
const Int_t nTau = 3;
const Int_t nBeta = 6;
const Int_t nFFM = 14;
const Int_t nSubjet = 5;
const Int_t nSDBeta = 5;
const Int_t nChgBeta = 5;

const Int_t centHIMax = 4;
const Int_t centArr[centHIMax] = {20, 60, 100, 200};
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

const Int_t nSDSymmZBins = 15;
const Float_t sdSymmZLow = 0.0001;
const Float_t sdSymmZHi = 0.5999;

const Int_t nPTDBins = 20;
const Float_t ptdLow = 0.0001;
const Float_t ptdHi = 0.9999;

const Int_t nChgBins = 20;
const Float_t chgLow = 0.0001;
const Float_t chgHi = 1.4999;

const Int_t nR2Bins = 20;
const Float_t r2Low = 0.0001;
const Float_t r2Hi = 99.9999;

const Int_t nSigma = 20;
const Float_t sigmaLow = 0.0001;
const Float_t sigmaHi = 99.9999;

const Int_t nSubJtRat = 20;
const Float_t subJtRatLow = -0.0001;
const Float_t subJtRatHi = 0.9999;

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

class JetSubstructHist{
public:
  JetSubstructHist(){};
  ~JetSubstructHist(){};

  //declare arrays much yolo                                                                                       
  TH1F* ptHist_p[centHIMax][histJtMax];
  TH1F* phiHist_p[centHIMax][histJtMax];
  TH1F* etaHist_p[centHIMax][histJtMax];
  TH1F* constNHist_p[centHIMax][histJtMax];
  TH1F* softPtHist_p[centHIMax][histJtMax][nSDBeta];
  TH1F* softSymmZHist_p[centHIMax][histJtMax][nSDBeta];
  TH1F* ptdHist_p[centHIMax][histJtMax];
  TH1F* chgHist_p[centHIMax][histJtMax][nChgBeta];
  TH1F* r2Hist_p[centHIMax][histJtMax];
  TH1F* sigmaHist_p[centHIMax][histJtMax][nSigma];
  TH1F* ffmUnsubHist_p[centHIMax][histJtMax][nFFM];
  TH1F* ffmSubHist_p[centHIMax][histJtMax][nFFM];
  TH1F* ffmSubBetterHist_p[centHIMax][histJtMax][nFFM];
  TH1F* subJtRat_p[centHIMax][histJtMax][nSubjet];
};




//Forward declaration of relevant functions
void SetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName);
void GetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName);
void InitJetSubstructHist(JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName);
void GetJetSubstructHist(TFile* histFile_p, JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName);
void FillJetSubstructHist(JetSubstruct* inJt_p, JetSubstructHist* inJtHist_p, sampleType sType, Int_t hiBin, Float_t weight, qGType qG);
void ScaleJetSubstructHist(JetSubstructHist* num_p, JetSubstructHist* denom_p, sampleType sType);
void WriteJetSubstructHist(TFile* outFile_p, JetSubstructHist* inJtHist_p, sampleType sType);
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


void InitJetSubstructHist(JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName)
{
  std::string hiBinOrPPPA[4] = {"010", "1030", "3050", "50100"};
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

      inJtHist_p->ptdHist_p[centIter][jtIter] = new TH1F(Form("%s_PTD_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_PTD_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nPTDBins, ptdLow, ptdHi);  

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	inJtHist_p->chgHist_p[centIter][jtIter][chgIter] = new TH1F(Form("%s_chgBeta%d_%s_%s_h", fillName.c_str(), chgIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), Form("%s_chgBeta%d_%s_%s_h", fillName.c_str(), chgIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()), nChgBins, chgLow, chgHi);
      }
    }
  }

  return;
}


void GetJetSubstructHist(TFile* histFile_p, JetSubstructHist* inJtHist_p, sampleType sType, const std::string fillName)
{
  std::string hiBinOrPPPA[4] = {"010", "1030", "3050", "50100"};
  if(sType == kPPDATA || sType == kPPMC) hiBinOrPPPA[0] = "PP";
  else if(sType == kPADATA || sType == kPAMC) hiBinOrPPPA[0] = "PA";

  Int_t centMax = 1;
  if(isHI(sType)) centMax = centHIMax;

  for(Int_t jtIter = 0; jtIter < histJtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centMax; centIter++){
      inJtHist_p->ptHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_pt_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->etaHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_eta_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      inJtHist_p->phiHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_phi_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter] = (TH1F*)histFile_p->Get(Form("%s_softSymmZBeta%d_%s_%s_h", fillName.c_str(), sdIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));
      }

      inJtHist_p->ptdHist_p[centIter][jtIter] = (TH1F*)histFile_p->Get(Form("%s_PTD_%s_%s_h", fillName.c_str(), jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	inJtHist_p->chgHist_p[centIter][jtIter][chgIter] = (TH1F*)histFile_p->Get(Form("%s_chgBeta%d_%s_%s_h", fillName.c_str(), chgIter, jtStr[jtIter].c_str(), hiBinOrPPPA[centIter].c_str()));
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

    for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
      inJtHist_p->softSymmZHist_p[centPos][jtIter][sdIter]->Fill(inJt_p->jtSoftSymmZ_[jtIter][sdIter], weight);
    }

    inJtHist_p->ptdHist_p[centPos][jtIter]->Fill(inJt_p->jtPTD_[jtIter], weight);

    for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
      inJtHist_p->chgHist_p[centPos][jtIter][chgIter]->Fill(TMath::Abs(inJt_p->jtChg_[jtIter][chgIter]), weight);
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

      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	num_p->softSymmZHist_p[centIter][jtIter][sdIter]->Scale(1./denom_p->softSymmZHist_p[centIter][jtIter][sdIter]->Integral());
      }

      num_p->ptdHist_p[centIter][jtIter]->Scale(1./denom_p->ptdHist_p[centIter][jtIter]->Integral());

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	num_p->chgHist_p[centIter][jtIter][chgIter]->Scale(1./denom_p->chgHist_p[centIter][jtIter][chgIter]->Integral());
      }
    }
  }

  return;
}


void WriteJetSubstructHist(TFile* outFile_p, JetSubstructHist* inJtHist_p, sampleType sType)
{
  outFile_p->cd();

  Int_t centMax = 1;
  if(isHI(sType)) centMax = centHIMax;

  for(Int_t jtIter = 0; jtIter < histJtMax; jtIter++){
    for(Int_t centIter = 0; centIter < centMax; centIter++){
      inJtHist_p->ptHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      inJtHist_p->etaHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      inJtHist_p->phiHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);
      
      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter]->Write("", TObject::kOverwrite);
      }

      inJtHist_p->ptdHist_p[centIter][jtIter]->Write("", TObject::kOverwrite);

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	inJtHist_p->chgHist_p[centIter][jtIter][chgIter]->Write("", TObject::kOverwrite);
      }
      
    }
  }

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

      for(Int_t sdIter = 0; sdIter < nSDBeta; sdIter++){
	delete inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter];
	inJtHist_p->softSymmZHist_p[centIter][jtIter][sdIter] = 0;
      }

      delete inJtHist_p->ptdHist_p[centIter][jtIter];
      inJtHist_p->ptdHist_p[centIter][jtIter] = 0;

      for(Int_t chgIter = 0; chgIter < nChgBeta; chgIter++){
	delete inJtHist_p->chgHist_p[centIter][jtIter][chgIter];
	inJtHist_p->chgHist_p[centIter][jtIter][chgIter] = 0;
      }
    }
  }

  delete inJtHist_p;
  inJtHist_p = 0;

  return;
}


#endif // __JETSUB__
