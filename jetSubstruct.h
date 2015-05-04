//=============================================
// Author: Chris McGinn
//
// Jet Substructure Class
// 
//=============================================

#ifndef __JETSUBSTRUCT__
#define __JETSUBSTRUCT__

#include "commonSetup.h"

const Int_t nSigma = 3;
const Int_t nTau = 3;
const Int_t nBeta = 6;
const Int_t nFFM = 14;
const Int_t nSubjet = 5;
const Int_t nSDBeta = 5;

class JetSubstruct{
public:
  JetSubstruct(){};
  ~JetSubstruct(){};

  //declare arrays much yolo
  Int_t nJt_;
  Float_t jtPt_[maxJets];
  Float_t jtPhi_[maxJets];
  Float_t jtEta_[maxJets];
  Float_t jtMatchPt_[maxJets];
  Float_t jtMatchPhi_[maxJets];
  Float_t jtMatchEta_[maxJets];
  Int_t jtConstN_[maxJets];
  Float_t jtSoftPt_[maxJets][nSDBeta];
  Float_t jtSoftSymmZ_[maxJets][nSDBeta];
  Float_t jtPTD_[maxJets];
  Float_t jtChg_[maxJets];
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
};

void SetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName)
{
  inTree_p->Branch(Form("%s_nJt", fillName.c_str()), &inJt_p->nJt_, Form("%s_nJt/I", fillName.c_str()));
  inTree_p->Branch(Form("%s_jtPt", fillName.c_str()), inJt_p->jtPt_, Form("%s_jtPt[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtPhi", fillName.c_str()), inJt_p->jtPhi_, Form("%s_jtPhi[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtEta", fillName.c_str()), inJt_p->jtEta_, Form("%s_jtEta[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtMatchPt", fillName.c_str()), inJt_p->jtMatchPt_, Form("%s_jtMatchPt[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtMatchPhi", fillName.c_str()), inJt_p->jtMatchPhi_, Form("%s_jtMatchPhi[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtMatchEta", fillName.c_str()), inJt_p->jtMatchEta_, Form("%s_jtMatchEta[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtConstN", fillName.c_str()), inJt_p->jtConstN_, Form("%s_jtConstN[%s_nJt]/I", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtSoftPt", fillName.c_str()), inJt_p->jtSoftPt_, Form("%s_jtSoftPt[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSDBeta));
  inTree_p->Branch(Form("%s_jtSoftSymmZ", fillName.c_str()), inJt_p->jtSoftSymmZ_, Form("%s_jtSoftSymmZ[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSDBeta));
  inTree_p->Branch(Form("%s_jtPTD", fillName.c_str()), inJt_p->jtPTD_, Form("%s_jtPTD[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtChg", fillName.c_str()), inJt_p->jtChg_, Form("%s_jtChg[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtR2", fillName.c_str()), inJt_p->jtR2_, Form("%s_jtR2[%s_nJt]/F", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtSigma", fillName.c_str()), inJt_p->jtSigma_, Form("%s_jtSigma[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSigma));
  inTree_p->Branch(Form("%s_jtRefPart", fillName.c_str()), inJt_p->jtRefPart_, Form("%s_jtRefPart[%s_nJt]/I", fillName.c_str(), fillName.c_str()));
  inTree_p->Branch(Form("%s_jtFFMUnsub", fillName.c_str()), inJt_p->jtFFMUnsub_, Form("%s_jtFFMUnsub[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nFFM));
  inTree_p->Branch(Form("%s_jtFFMSub", fillName.c_str()), inJt_p->jtFFMSub_, Form("%s_jtFFMSub[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nFFM));
  inTree_p->Branch(Form("%s_jtFFMSubBetter", fillName.c_str()), inJt_p->jtFFMSubBetter_, Form("%s_jtFFMSubBetter[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nFFM));
  inTree_p->Branch(Form("%s_jtTau", fillName.c_str()), inJt_p->jtTau_, Form("%s_jtTau[%s_nJt][%d][%d]/F", fillName.c_str(), fillName.c_str(), nTau, nBeta));
  inTree_p->Branch(Form("%s_subJtPt", fillName.c_str()), inJt_p->subJtPt_, Form("%s_subJtPt[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSubjet));
  inTree_p->Branch(Form("%s_subJtPhi", fillName.c_str()), inJt_p->subJtPhi_, Form("%s_subJtPhi[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSubjet));
  inTree_p->Branch(Form("%s_subJtEta", fillName.c_str()), inJt_p->subJtEta_, Form("%s_subJtEta[%s_nJt][%d]/F", fillName.c_str(), fillName.c_str(), nSubjet));

  return;
}


void GetJetSubstructBranches(TTree* inTree_p, JetSubstruct* inJt_p, const std::string fillName)
{
  inTree_p->SetBranchAddress(Form("%s_nJt", fillName.c_str()), &inJt_p->nJt_);
  inTree_p->SetBranchAddress(Form("%s_jtPt", fillName.c_str()), inJt_p->jtPt_);
  inTree_p->SetBranchAddress(Form("%s_jtPhi", fillName.c_str()), inJt_p->jtPhi_);
  inTree_p->SetBranchAddress(Form("%s_jtEta", fillName.c_str()), inJt_p->jtEta_);
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

  return;
}


#endif // __JETSUB__
