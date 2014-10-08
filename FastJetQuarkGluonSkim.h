//=============================================
// Author: Chris McGinn
//
// FastJet AnaSkim Class (MC)
//
//=============================================
#ifndef FastJetQuarkGluonSkim_h
#define FastJetQuarkGluonSkim_h

#include "FastJetAnaSkim.h"

TTree* outTree_p = 0;

Int_t nJt;
Float_t jtPt_[maxJets];
Float_t jtPhi_[maxJets];
Float_t jtEta_[maxJets];
Float_t jtPTD_[maxJets];
Float_t jtR2_[maxJets];
Float_t jtSigma_[maxJets][nSigma];
Int_t jtRefPart_[maxJets];
Float_t jtFFMUnsub_[maxJets][nFFM];
Float_t jtFFMSub_[maxJets][nFFM];
Float_t jtFFMSubBetter_[maxJets][nFFM];
Float_t jtTau_[maxJets][nTau][nBeta];
Float_t jtSubPt_[maxJets][nSubjet];
Float_t jtSubPhi_[maxJets][nSubjet];
Float_t jtSubEta_[maxJets][nSubjet];


void SetQuarkGluonBranches()
{
  outTree_p->Branch("nJt", &nJt_, "nJt/I");
  outTree_p->Branch("jtPt", jtPt_, "jtPt/F");
  outTree_p->Branch("jtPhi", jtPhi_, "jtPhi/F");
  outTree_p->Branch("jtEta", jtEta_, "jtEta/F");

  return;
}

#endif
