//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// FastJet AnaSkim Class (MC)                                                    
//                                                                              
//=============================================  
#ifndef FastJetAnaSkim_h
#define FastJetAnaSkim_h

#include "FastJetIniSkim.h"

#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"

enum Taus{
  tau1, //0
  tau2, //1
  tau3  //2
};

enum betaType{
  betaHalf, //0
  betaOne,  //1
  betaTwo   //2
};

const Int_t nSigma = 3;
const Int_t nTau = 3;
const Int_t nBeta = 6;
const Int_t nFFM = 14;
const Int_t nSubjet = 2;

TTree* rechitTreeAna_p = 0;
TTree* pfcandTreeAna_p = 0;
TTree* trkTreeAna_p = 0;
TTree* genTreeAna_p = 0;
TTree* jetTreeAna_p = 0;

//rechit TreeAna Variables, [alg][tau][beta]

Float_t rechitSKPtCut_;

Int_t nRechitJtRaw_;
Float_t rechitJtRawPt_[maxJets];
Float_t rechitJtRawPhi_[maxJets];
Float_t rechitJtRawEta_[maxJets];
Int_t rechitJtRawConstN_[maxJets];
Float_t rechitJtRawPTD_[maxJets];
Float_t rechitJtRawR2_[maxJets];
Float_t rechitJtRawSigma_[maxJets][nSigma];
Int_t rechitJtRawRefPart_[maxJets];
Float_t rechitJtRawFFMUnsub_[maxJets][nFFM];
Float_t rechitJtRawFFMSub_[maxJets][nFFM];
Float_t rechitJtRawFFMSubBetter_[maxJets][nFFM];
Float_t rechitRawTau_[maxJets][nTau][nBeta];
Float_t rechitSubJtRawPt_[maxJets][nSubjet];
Float_t rechitSubJtRawPhi_[maxJets][nSubjet];
Float_t rechitSubJtRawEta_[maxJets][nSubjet];

Int_t nRechitJtVs_;
Float_t rechitJtVsPt_[maxJets];
Float_t rechitJtVsPhi_[maxJets];
Float_t rechitJtVsEta_[maxJets];
Int_t rechitJtVsConstN_[maxJets];
Float_t rechitJtVsPTD_[maxJets];
Float_t rechitJtVsR2_[maxJets];
Float_t rechitJtVsSigma_[maxJets][nSigma];
Int_t rechitJtVsRefPart_[maxJets];
Float_t rechitJtVsFFMUnsub_[maxJets][nFFM];
Float_t rechitJtVsFFMSub_[maxJets][nFFM];
Float_t rechitJtVsFFMSubBetter_[maxJets][nFFM];
Float_t rechitVsTau_[maxJets][nTau][nBeta];
Float_t rechitSubJtVsPt_[maxJets][nSubjet];
Float_t rechitSubJtVsPhi_[maxJets][nSubjet];
Float_t rechitSubJtVsEta_[maxJets][nSubjet];

//pfcand TreeAna Variables

Float_t pfSKPtCut_;

Int_t nPFJtRaw_;
Float_t pfJtRawPt_[maxJets];
Float_t pfJtRawPhi_[maxJets];
Float_t pfJtRawEta_[maxJets];
Int_t pfJtRawConstN_[maxJets];
Float_t pfJtRawPTD_[maxJets];
Float_t pfJtRawR2_[maxJets];
Float_t pfJtRawSigma_[maxJets][nSigma];
Int_t pfJtRawRefPart_[maxJets];
Float_t pfJtRawFFMUnsub_[maxJets][nFFM];
Float_t pfJtRawFFMSub_[maxJets][nFFM];
Float_t pfJtRawFFMSubBetter_[maxJets][nFFM];
Float_t pfRawTau_[maxJets][nTau][nBeta];
Float_t pfSubJtRawPt_[maxJets][nSubjet];
Float_t pfSubJtRawPhi_[maxJets][nSubjet];
Float_t pfSubJtRawEta_[maxJets][nSubjet];

Int_t nPFJtVs_;
Float_t pfJtVsPt_[maxJets];
Float_t pfJtVsPhi_[maxJets];
Float_t pfJtVsEta_[maxJets];
Int_t pfJtVsConstN_[maxJets];
Float_t pfJtVsPTD_[maxJets];
Float_t pfJtVsR2_[maxJets];
Float_t pfJtVsSigma_[maxJets][nSigma];
Int_t pfJtVsRefPart_[maxJets];
Float_t pfJtVsFFMUnsub_[maxJets][nFFM];
Float_t pfJtVsFFMSub_[maxJets][nFFM];
Float_t pfJtVsFFMSubBetter_[maxJets][nFFM];
Float_t pfVsTau_[maxJets][nTau][nBeta];
Float_t pfSubJtVsPt_[maxJets][nSubjet];
Float_t pfSubJtVsPhi_[maxJets][nSubjet];
Float_t pfSubJtVsEta_[maxJets][nSubjet];

Int_t nPFJtSK_;
Float_t pfJtSKPt_[maxJets];
Float_t pfJtSKPhi_[maxJets];
Float_t pfJtSKEta_[maxJets];
Int_t pfJtSKConstN_[maxJets];
Float_t pfJtSKPTD_[maxJets];
Float_t pfJtSKR2_[maxJets];
Float_t pfJtSKSigma_[maxJets][nSigma];
Int_t pfJtSKRefPart_[maxJets];
Float_t pfJtSKFFMUnsub_[maxJets][nFFM];
Float_t pfJtSKFFMSub_[maxJets][nFFM];
Float_t pfJtSKFFMSubBetter_[maxJets][nFFM];
Float_t pfSKTau_[maxJets][nTau][nBeta];
Float_t pfSubJtSKPt_[maxJets][nSubjet];
Float_t pfSubJtSKPhi_[maxJets][nSubjet];
Float_t pfSubJtSKEta_[maxJets][nSubjet];


//track TreeAna Variables

Float_t trkSKPtCut_;

Int_t nTrkJtRaw_;
Float_t trkJtRawPt_[maxJets];
Float_t trkJtRawPhi_[maxJets];
Float_t trkJtRawEta_[maxJets];
Int_t trkJtRawConstN_[maxJets];
Float_t trkJtRawPTD_[maxJets];
Float_t trkJtRawR2_[maxJets];
Float_t trkJtRawSigma_[maxJets][nSigma];
Int_t trkJtRawRefPart_[maxJets];
Float_t trkJtRawFFMUnsub_[maxJets][nFFM];
Float_t trkJtRawFFMSub_[maxJets][nFFM];
Float_t trkJtRawFFMSubBetter_[maxJets][nFFM];
Float_t trkRawTau_[maxJets][nTau][nBeta];
Float_t trkSubJtRawPt_[maxJets][nSubjet];
Float_t trkSubJtRawPhi_[maxJets][nSubjet];
Float_t trkSubJtRawEta_[maxJets][nSubjet];

Int_t nTrkJtSK_;
Float_t trkJtSKPt_[maxJets];
Float_t trkJtSKPhi_[maxJets];
Float_t trkJtSKEta_[maxJets];
Int_t trkJtSKConstN_[maxJets];
Float_t trkJtSKPTD_[maxJets];
Float_t trkJtSKR2_[maxJets];
Float_t trkJtSKSigma_[maxJets][nSigma];
Int_t trkJtSKRefPart_[maxJets];
Float_t trkJtSKFFMUnsub_[maxJets][nFFM];
Float_t trkJtSKFFMSub_[maxJets][nFFM];
Float_t trkJtSKFFMSubBetter_[maxJets][nFFM];
Float_t trkSKTau_[maxJets][nTau][nBeta];
Float_t trkSubJtSKPt_[maxJets][nSubjet];
Float_t trkSubJtSKPhi_[maxJets][nSubjet];
Float_t trkSubJtSKEta_[maxJets][nSubjet];

//Gen TreeAna Variables

Float_t genSKPtCut_;

Int_t nGenJtRaw_;
Float_t genJtRawPt_[maxJets];
Float_t genJtRawPhi_[maxJets];
Float_t genJtRawEta_[maxJets];
Int_t genJtRawConstN_[maxJets];
Float_t genJtRawPTD_[maxJets];
Float_t genJtRawR2_[maxJets];
Float_t genJtRawSigma_[maxJets][nSigma];
Int_t genJtRawRefPart_[maxJets];
Float_t genJtRawFFMUnsub_[maxJets][nFFM];
Float_t genJtRawFFMSub_[maxJets][nFFM];
Float_t genJtRawFFMSubBetter_[maxJets][nFFM];
Float_t genRawTau_[maxJets][nTau][nBeta];
Float_t genSubJtRawPt_[maxJets][nSubjet];
Float_t genSubJtRawPhi_[maxJets][nSubjet];
Float_t genSubJtRawEta_[maxJets][nSubjet];

Int_t nGenJtSK_;
Float_t genJtSKPt_[maxJets];
Float_t genJtSKPhi_[maxJets];
Float_t genJtSKEta_[maxJets];
Int_t genJtSKConstN_[maxJets];
Float_t genJtSKPTD_[maxJets];
Float_t genJtSKR2_[maxJets];
Float_t genJtSKSigma_[maxJets][nSigma];
Int_t genJtSKRefPart_[maxJets];
Float_t genJtSKFFMUnsub_[maxJets][nFFM];
Float_t genJtSKFFMSub_[maxJets][nFFM];
Float_t genJtSKFFMSubBetter_[maxJets][nFFM];
Float_t genSKTau_[maxJets][nTau][nBeta];
Float_t genSubJtSKPt_[maxJets][nSubjet];
Float_t genSubJtSKPhi_[maxJets][nSubjet];
Float_t genSubJtSKEta_[maxJets][nSubjet];

Int_t nGenJtSUBE_;
Float_t genJtSUBEPt_[maxJets];
Float_t genJtSUBEPhi_[maxJets];
Float_t genJtSUBEEta_[maxJets];
Int_t genJtSUBEConstN_[maxJets];
Float_t genJtSUBEPTD_[maxJets];
Float_t genJtSUBER2_[maxJets];
Float_t genJtSUBESigma_[maxJets][nSigma];
Int_t genJtSUBERefPart_[maxJets];
Float_t genJtSUBEFFMUnsub_[maxJets][nFFM];
Float_t genJtSUBEFFMSub_[maxJets][nFFM];
Float_t genJtSUBEFFMSubBetter_[maxJets][nFFM];
Float_t genSUBETau_[maxJets][nTau][nBeta];
Float_t genSubJtSUBEPt_[maxJets][nSubjet];
Float_t genSubJtSUBEPhi_[maxJets][nSubjet];
Float_t genSubJtSUBEEta_[maxJets][nSubjet];

//Jet TreeAna Variables

Int_t run_;
Int_t evt_;
Int_t lumi_;
Int_t hiBin_;
Float_t b_;

Float_t pthat_;
Float_t pthatWeight_;

Float_t hiEvtPlane_;
Float_t psin_;

Bool_t eventSet_[5];

Float_t AlgJtPt_[5][5];
Float_t AlgJtPhi_[5][5];
Float_t AlgJtEta_[5][5];
Float_t AlgJtRawPt_[5][5];
Int_t AlgRefPartFlav_[5][5];

Float_t AlgJtDelPhi_[5];
Float_t AlgJtAsymm_[5];

Float_t AlgRefPt_[5][5];
Float_t AlgRefPhi_[5][5];
Float_t AlgRefEta_[5][5];


void SetAnaBranches(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);
  //Rechit TreeAna Branches

  if(!isGen){
    rechitTreeAna_p->Branch("rechitSKPtCut", &rechitSKPtCut_, Form("rechitSKPtCut/F"));

    rechitTreeAna_p->Branch("nRechitJtRaw", &nRechitJtRaw_, Form("nRechitJtRaw/I"));
    rechitTreeAna_p->Branch("rechitJtRawPt", rechitJtRawPt_, Form("rechitJtRawPt[nRechitJtRaw]/F"));
    rechitTreeAna_p->Branch("rechitJtRawPhi", rechitJtRawPhi_, Form("rechitJtRawPhi[nRechitJtRaw]/F"));
    rechitTreeAna_p->Branch("rechitJtRawEta", rechitJtRawEta_, Form("rechitJtRawEta[nRechitJtRaw]/F"));
    rechitTreeAna_p->Branch("rechitJtRawConstN", rechitJtRawConstN_, Form("rechitJtRawConstN[nRechitJtRaw]/I"));
    rechitTreeAna_p->Branch("rechitJtRawPTD", rechitJtRawPTD_, Form("rechitJtRawPTD[nRechitJtRaw]/F"));
    rechitTreeAna_p->Branch("rechitJtRawR2", rechitJtRawR2_, Form("rechitJtRawR2[nRechitJtRaw]/F"));
    rechitTreeAna_p->Branch("rechitJtRawSigma", rechitJtRawSigma_, Form("rechitJtRawSigma[nRechitJtRaw][%d]/F", nSigma));
    rechitTreeAna_p->Branch("rechitJtRawRefPart", rechitJtRawRefPart_, Form("rechitJtRawRefPart[nRechitJtRaw]/I"));
    rechitTreeAna_p->Branch("rechitJtRawFFMUnsub", rechitJtRawFFMUnsub_, Form("rechitJtRawFFMUnsub[nRechitJtRaw][%d]/F", nFFM));
    rechitTreeAna_p->Branch("rechitJtRawFFMSub", rechitJtRawFFMSub_, Form("rechitJtRawFFMSub[nRechitJtRaw][%d]/F", nFFM));
    rechitTreeAna_p->Branch("rechitJtRawFFMSubBetter", rechitJtRawFFMSubBetter_, Form("rechitJtRawFFMSubBetter[nRechitJtRaw][%d]/F", nFFM));
    rechitTreeAna_p->Branch("rechitRawTau", rechitRawTau_, Form("rechitRawTau[nRechitJtRaw][%d][%d]/F", nTau, nBeta));
    rechitTreeAna_p->Branch("rechitSubJtRawPt", rechitSubJtRawPt_, Form("rechitSubJtRawPt[nRechitJtRaw][%d]/F", nSubjet));
    rechitTreeAna_p->Branch("rechitSubJtRawPhi", rechitSubJtRawPhi_, Form("rechitSubJtRawPhi[nRechitJtRaw][%d]/F", nSubjet));
    rechitTreeAna_p->Branch("rechitSubJtRawEta", rechitSubJtRawEta_, Form("rechitSubJtRawEta[nRechitJtRaw][%d]/F", nSubjet));
    
    rechitTreeAna_p->Branch("nRechitJtVs", &nRechitJtVs_, Form("nRechitJtVs/I"));
    rechitTreeAna_p->Branch("rechitJtVsPt", rechitJtVsPt_, Form("rechitJtVsPt[nRechitJtVs]/F"));
    rechitTreeAna_p->Branch("rechitJtVsPhi", rechitJtVsPhi_, Form("rechitJtVsPhi[nRechitJtVs]/F"));
    rechitTreeAna_p->Branch("rechitJtVsEta", rechitJtVsEta_, Form("rechitJtVsEta[nRechitJtVs]/F"));
    rechitTreeAna_p->Branch("rechitJtVsConstN", rechitJtVsConstN_, Form("rechitJtVsConstN[nRechitJtVs]/I"));
    rechitTreeAna_p->Branch("rechitJtVsPTD", rechitJtVsPTD_, Form("rechitJtVsPTD[nRechitJtVs]/F"));
    rechitTreeAna_p->Branch("rechitJtVsR2", rechitJtVsR2_, Form("rechitJtVsR2[nRechitJtVs]/F"));
    rechitTreeAna_p->Branch("rechitJtVsSigma", rechitJtVsSigma_, Form("rechitJtVsSigma[nRechitJtVs][%d]/F", nSigma));
    rechitTreeAna_p->Branch("rechitJtVsRefPart", rechitJtVsRefPart_, Form("rechitJtVsRefPart[nRechitJtVs]/I"));
    rechitTreeAna_p->Branch("rechitJtVsFFMUnsub", rechitJtVsFFMUnsub_, Form("rechitJtVsFFMUnsub[nRechitJtVs][%d]/F", nFFM));
    rechitTreeAna_p->Branch("rechitJtVsFFMSub", rechitJtVsFFMSub_, Form("rechitJtVsFFMSub[nRechitJtVs][%d]/F", nFFM));
    rechitTreeAna_p->Branch("rechitJtVsFFMSubBetter", rechitJtVsFFMSubBetter_, Form("rechitJtVsFFMSubBetter[nRechitJtVs][%d]/F", nFFM));
    rechitTreeAna_p->Branch("rechitVsTau", rechitVsTau_, Form("rechitVsTau[nRechitJtVs][%d][%d]/F", nTau, nBeta));
    rechitTreeAna_p->Branch("rechitSubJtVsPt", rechitSubJtVsPt_, Form("rechitSubJtVsPt[nRechitJtVs][%d]/F", nSubjet));
    rechitTreeAna_p->Branch("rechitSubJtVsPhi", rechitSubJtVsPhi_, Form("rechitSubJtVsPhi[nRechitJtVs][%d]/F", nSubjet));
    rechitTreeAna_p->Branch("rechitSubJtVsEta", rechitSubJtVsEta_, Form("rechitSubJtVsEta[nRechitJtVs][%d]/F", nSubjet));
    
    //PF TreeAna Branches

    pfcandTreeAna_p->Branch("pfSKPtCut", &pfSKPtCut_, Form("pfSKPtCut/F")); 

    pfcandTreeAna_p->Branch("nPFJtRaw", &nPFJtRaw_, Form("nPFJtRaw/I"));
    pfcandTreeAna_p->Branch("pfJtRawPt", pfJtRawPt_, Form("pfJtRawPt[nPFJtRaw]/F"));
    pfcandTreeAna_p->Branch("pfJtRawPhi", pfJtRawPhi_, Form("pfJtRawPhi[nPFJtRaw]/F"));
    pfcandTreeAna_p->Branch("pfJtRawEta", pfJtRawEta_, Form("pfJtRawEta[nPFJtRaw]/F"));
    pfcandTreeAna_p->Branch("pfJtRawConstN", pfJtRawConstN_, Form("pfJtRawConstN[nPfJtRaw]/I"));
    pfcandTreeAna_p->Branch("pfJtRawR2", pfJtRawR2_, Form("pfJtRawR2[nPFJtRaw]/F"));
    pfcandTreeAna_p->Branch("pfJtRawSigma", pfJtRawSigma_, Form("pfJtRawSigma[nPFJtRaw][%d]/F", nSigma));
    pfcandTreeAna_p->Branch("pfJtRawRefPart", pfJtRawRefPart_, Form("pfJtRawRefPart[nPFJtRaw]/I"));
    pfcandTreeAna_p->Branch("pfJtRawFFMUnsub", pfJtRawFFMUnsub_, Form("pfJtRawFFMUnsub[nPFJtRaw][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfJtRawFFMSub", pfJtRawFFMSub_, Form("pfJtRawFFMSub[nPFJtRaw][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfJtRawFFMSubBetter", pfJtRawFFMSubBetter_, Form("pfJtRawFFMSubBetter[nPFJtRaw][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfRawTau", pfRawTau_, Form("pfRawTau[nPFJtRaw][%d][%d]/F", nTau, nBeta));
    pfcandTreeAna_p->Branch("pfSubJtRawPt", pfSubJtRawPt_, Form("pfSubJtRawPt[nPFJtRaw][%d]/F", nSubjet));
    pfcandTreeAna_p->Branch("pfSubJtRawPhi", pfSubJtRawPhi_, Form("pfSubJtRawPhi[nPFJtRaw][%d]/F", nSubjet));
    pfcandTreeAna_p->Branch("pfSubJtRawEta", pfSubJtRawEta_, Form("pfSubJtRawEta[nPFJtRaw][%d]/F", nSubjet));

    pfcandTreeAna_p->Branch("nPFJtVs", &nPFJtVs_, Form("nPFJtVs/I"));    
    pfcandTreeAna_p->Branch("pfJtVsPt", pfJtVsPt_, Form("pfJtVsPt[nPFJtVs]/F"));
    pfcandTreeAna_p->Branch("pfJtVsPhi", pfJtVsPhi_, Form("pfJtVsPhi[nPFJtVs]/F"));
    pfcandTreeAna_p->Branch("pfJtVsEta", pfJtVsEta_, Form("pfJtVsEta[nPFJtVs]/F"));
    pfcandTreeAna_p->Branch("pfJtVsConstN", pfJtVsConstN_, Form("pfJtVsConstN[nPfJtVs]/I"));
    pfcandTreeAna_p->Branch("pfJtVsPTD", pfJtVsPTD_, Form("pfJtVsPTD[nPFJtVs]/F"));
    pfcandTreeAna_p->Branch("pfJtVsR2", pfJtVsR2_, Form("pfJtVsR2[nPFJtVs]/F"));
    pfcandTreeAna_p->Branch("pfJtVsSigma", pfJtVsSigma_, Form("pfJtVsSigma[nPFJtVs][%d]/F", nSigma));
    pfcandTreeAna_p->Branch("pfJtVsRefPart", pfJtVsRefPart_, Form("pfJtVsRefPart[nPFJtVs]/I"));
    pfcandTreeAna_p->Branch("pfJtVsFFMUnsub", pfJtVsFFMUnsub_, Form("pfJtVsFFMUnsub[nPFJtVs][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfJtVsFFMSub", pfJtVsFFMSub_, Form("pfJtVsFFMSub[nPFJtVs][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfJtVsFFMSubBetter", pfJtVsFFMSubBetter_, Form("pfJtVsFFMSubBetter[nPFJtVs][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfVsTau", pfVsTau_, Form("pfVsTau[nPFJtVs][%d][%d]/F", nTau, nBeta));
    pfcandTreeAna_p->Branch("pfSubJtVsPt", pfSubJtVsPt_, Form("pfSubJtVsPt[nPFJtVs][%d]/F", nSubjet));
    pfcandTreeAna_p->Branch("pfSubJtVsPhi", pfSubJtVsPhi_, Form("pfSubJtVsPhi[nPFJtVs][%d]/F", nSubjet));
    pfcandTreeAna_p->Branch("pfSubJtVsEta", pfSubJtVsEta_, Form("pfSubJtVsEta[nPFJtVs][%d]/F", nSubjet));

    pfcandTreeAna_p->Branch("nPFJtSK", &nPFJtSK_, Form("nPFJtSK/I"));
    pfcandTreeAna_p->Branch("pfJtSKPt", pfJtSKPt_, Form("pfJtSKPt[nPFJtSK]/F"));
    pfcandTreeAna_p->Branch("pfJtSKPhi", pfJtSKPhi_, Form("pfJtSKPhi[nPFJtSK]/F"));
    pfcandTreeAna_p->Branch("pfJtSKEta", pfJtSKEta_, Form("pfJtSKEta[nPFJtSK]/F"));
    pfcandTreeAna_p->Branch("pfJtSKConstN", pfJtSKConstN_, Form("pfJtSKConstN[nPfJtSK]/I"));
    pfcandTreeAna_p->Branch("pfJtSKPTD", pfJtSKPTD_, Form("pfJtSKPTD[nPFJtSK]/F"));
    pfcandTreeAna_p->Branch("pfJtSKR2", pfJtSKR2_, Form("pfJtSKR2[nPFJtSK]/F"));
    pfcandTreeAna_p->Branch("pfJtSKSigma", pfJtSKSigma_, Form("pfJtSKSigma[nPFJtSK][%d]/F", nSigma));
    pfcandTreeAna_p->Branch("pfJtSKRefPart", pfJtSKRefPart_, Form("pfJtSKRefPart[nPFJtSK]/I"));
    pfcandTreeAna_p->Branch("pfJtSKFFMUnsub", pfJtSKFFMUnsub_, Form("pfJtSKFFMUnsub[nPFJtSK][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfJtSKFFMSub", pfJtSKFFMSub_, Form("pfJtSKFFMSub[nPFJtSK][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfJtSKFFMSubBetter", pfJtSKFFMSubBetter_, Form("pfJtSKFFMSubBetter[nPFJtSK][%d]/F", nFFM));
    pfcandTreeAna_p->Branch("pfSKTau", pfSKTau_, Form("pfSKTau[nPFJtSK][%d][%d]/F", nTau, nBeta));
    pfcandTreeAna_p->Branch("pfSubJtSKPt", pfSubJtSKPt_, Form("pfSubJtSKPt[nPFJtSK][%d]/F", nSubjet));
    pfcandTreeAna_p->Branch("pfSubJtSKPhi", pfSubJtSKPhi_, Form("pfSubJtSKPhi[nPFJtSK][%d]/F", nSubjet));
    pfcandTreeAna_p->Branch("pfSubJtSKEta", pfSubJtSKEta_, Form("pfSubJtSKEta[nPFJtSK][%d]/F", nSubjet));
    
    //Trk TreeAna Branches
    trkTreeAna_p->Branch("trkSKPtCut", &trkSKPtCut_, Form("trkSKPtCut/F"));    

    trkTreeAna_p->Branch("nTrkJtRaw", &nTrkJtRaw_, Form("nTrkJtRaw/I"));
    trkTreeAna_p->Branch("trkJtRawPt", trkJtRawPt_, Form("trkJtRawPt[nTrkJtRaw]/F"));
    trkTreeAna_p->Branch("trkJtRawPhi", trkJtRawPhi_, Form("trkJtRawPhi[nTrkJtRaw]/F"));
    trkTreeAna_p->Branch("trkJtRawEta", trkJtRawEta_, Form("trkJtRawEta[nTrkJtRaw]/F"));
    trkTreeAna_p->Branch("trkJtRawConstN", trkJtRawConstN_, Form("trkJtRawConstN[nTrkJtRaw]/I"));
    trkTreeAna_p->Branch("trkJtRawPTD", trkJtRawPTD_, Form("trkJtRawPTD[nTrkJtRaw]/F"));
    trkTreeAna_p->Branch("trkJtRawR2", trkJtRawR2_, Form("trkJtRawR2[nTrkJtRaw]/F"));
    trkTreeAna_p->Branch("trkJtRawSigma", trkJtRawSigma_, Form("trkJtRawSigma[nTrkJtRaw][%d]/F", nSigma));
    trkTreeAna_p->Branch("trkJtRawRefPart", trkJtRawRefPart_, Form("trkJtRawRefPart[nTrkJtRaw]/I"));
    trkTreeAna_p->Branch("trkJtRawFFMUnsub", trkJtRawFFMUnsub_, Form("trkJtRawFFMUnsub[nTrkJtRaw][%d]/F", nFFM));
    trkTreeAna_p->Branch("trkJtRawFFMSub", trkJtRawFFMSub_, Form("trkJtRawFFMSub[nTrkJtRaw][%d]/F", nFFM));
    trkTreeAna_p->Branch("trkJtRawFFMSubBetter", trkJtRawFFMSubBetter_, Form("trkJtRawFFMSubBetter[nTrkJtRaw][%d]/F", nFFM));
    trkTreeAna_p->Branch("trkRawTau", trkRawTau_, Form("trkRawTau[nTrkJtRaw][%d][%d]/F", nTau, nBeta));
    trkTreeAna_p->Branch("trkSubJtRawPt", trkSubJtRawPt_, Form("trkSubJtRawPt[nTrkJtRaw][%d]/F", nSubjet));
    trkTreeAna_p->Branch("trkSubJtRawPhi", trkSubJtRawPhi_, Form("trkSubJtRawPhi[nTrkJtRaw][%d]/F", nSubjet));
    trkTreeAna_p->Branch("trkSubJtRawEta", trkSubJtRawEta_, Form("trkSubJtRawEta[nTrkJtRaw][%d]/F", nSubjet));
    
    trkTreeAna_p->Branch("nTrkJtSK", &nTrkJtSK_, Form("nTrkJtSK/I"));
    trkTreeAna_p->Branch("trkJtSKPt", trkJtSKPt_, Form("trkJtSKPt[nTrkJtSK]/F"));
    trkTreeAna_p->Branch("trkJtSKPhi", trkJtSKPhi_, Form("trkJtSKPhi[nTrkJtSK]/F"));
    trkTreeAna_p->Branch("trkJtSKEta", trkJtSKEta_, Form("trkJtSKEta[nTrkJtSK]/F"));
    trkTreeAna_p->Branch("trkJtSKConstN", trkJtSKConstN_, Form("trkJtSKConstN[nTrkJtSK]/I"));
    trkTreeAna_p->Branch("trkJtSKPTD", trkJtSKPTD_, Form("trkJtSKPTD[nTrkJtSK]/F"));
    trkTreeAna_p->Branch("trkJtSKR2", trkJtSKR2_, Form("trkJtSKR2[nTrkJtSK]/F"));
    trkTreeAna_p->Branch("trkJtSKSigma", trkJtSKSigma_, Form("trkJtSKSigma[nTrkJtSK][%d]/F", nSigma));
    trkTreeAna_p->Branch("trkJtSKRefPart", trkJtSKRefPart_, Form("trkJtSKRefPart[nTrkJtSK]/I"));
    trkTreeAna_p->Branch("trkJtSKFFMUnsub", trkJtSKFFMUnsub_, Form("trkJtSKFFMUnsub[nTrkJtSK][%d]/F", nFFM));
    trkTreeAna_p->Branch("trkJtSKFFMSub", trkJtSKFFMSub_, Form("trkJtSKFFMSub[nTrkJtSK][%d]/F", nFFM));
    trkTreeAna_p->Branch("trkJtSKFFMSubBetter", trkJtSKFFMSubBetter_, Form("trkJtSKFFMSubBetter[nTrkJtSK][%d]/F", nFFM));
    trkTreeAna_p->Branch("trkSKTau", trkSKTau_, Form("trkSKTau[nTrkJtSK][%d][%d]/F", nTau, nBeta));
    trkTreeAna_p->Branch("trkSubJtSKPt", trkSubJtSKPt_, Form("trkSubJtSKPt[nTrkJtSK][%d]/F", nSubjet));
    trkTreeAna_p->Branch("trkSubJtSKPhi", trkSubJtSKPhi_, Form("trkSubJtSKPhi[nTrkJtSK][%d]/F", nSubjet));
    trkTreeAna_p->Branch("trkSubJtSKEta", trkSubJtSKEta_, Form("trkSubJtSKEta[nTrkJtSK][%d]/F", nSubjet));
  }    

  //Gen TreeAna Branches
  if(montecarlo){
    genTreeAna_p->Branch("genSKPtCut", &genSKPtCut_, Form("genSKPtCut/F"));

    genTreeAna_p->Branch("nGenJtRaw", &nGenJtRaw_, Form("nGenJtRaw/I"));
    genTreeAna_p->Branch("genJtRawPt", genJtRawPt_, Form("genJtRawPt[nGenJtRaw]/F"));
    genTreeAna_p->Branch("genJtRawPhi", genJtRawPhi_, Form("genJtRawPhi[nGenJtRaw]/F"));
    genTreeAna_p->Branch("genJtRawEta", genJtRawEta_, Form("genJtRawEta[nGenJtRaw]/F"));
    genTreeAna_p->Branch("genJtRawConstN", genJtRawConstN_, Form("genJtRawConstN[nGenJtRaw]/I"));
    genTreeAna_p->Branch("genJtRawPTD", genJtRawPTD_, Form("genJtRawPTD[nGenJtRaw]/F"));
    genTreeAna_p->Branch("genJtRawR2", genJtRawR2_, Form("genJtRawR2[nGenJtRaw]/F"));
    genTreeAna_p->Branch("genJtRawSigma", genJtRawSigma_, Form("genJtRawSigma[nGenJtRaw][%d]/F", nSigma));
    genTreeAna_p->Branch("genJtRawRefPart", genJtRawRefPart_, Form("genJtRawRefPart[nGenJtRaw]/I"));
    genTreeAna_p->Branch("genJtRawFFMUnsub", genJtRawFFMUnsub_, Form("genJtRawFFMUnsub[nGenJtRaw][%d]/F", nFFM));
    genTreeAna_p->Branch("genJtRawFFMSub", genJtRawFFMSub_, Form("genJtRawFFMSub[nGenJtRaw][%d]/F", nFFM));
    genTreeAna_p->Branch("genJtRawFFMSubBetter", genJtRawFFMSubBetter_, Form("genJtRawFFMSubBetter[nGenJtRaw][%d]/F", nFFM));
    genTreeAna_p->Branch("genRawTau", genRawTau_, Form("genRawTau[nGenJtRaw][%d][%d]/F", nTau, nBeta));
    genTreeAna_p->Branch("genSubJtRawPt", genSubJtRawPt_, Form("genSubJtRawPt[nGenJtRaw][%d]/F", nSubjet));
    genTreeAna_p->Branch("genSubJtRawPhi", genSubJtRawPhi_, Form("genSubJtRawPhi[nGenJtRaw][%d]/F", nSubjet));
    genTreeAna_p->Branch("genSubJtRawEta", genSubJtRawEta_, Form("genSubJtRawEta[nGenJtRaw][%d]/F", nSubjet));

    genTreeAna_p->Branch("nGenJtSK", &nGenJtSK_, Form("nGenJtSK/I"));
    genTreeAna_p->Branch("genJtSKPt", genJtSKPt_, Form("genJtSKPt[nGenJtSK]/F"));
    genTreeAna_p->Branch("genJtSKPhi", genJtSKPhi_, Form("genJtSKPhi[nGenJtSK]/F"));
    genTreeAna_p->Branch("genJtSKEta", genJtSKEta_, Form("genJtSKEta[nGenJtSK]/F"));
    genTreeAna_p->Branch("genJtSKConstN", genJtSKConstN_, Form("genJtSKConstN[nGenJtSK]/I"));
    genTreeAna_p->Branch("genJtSKPTD", genJtSKPTD_, Form("genJtSKPTD[nGenJtSK]/F"));
    genTreeAna_p->Branch("genJtSKR2", genJtSKR2_, Form("genJtSKR2[nGenJtSK]/F"));
    genTreeAna_p->Branch("genJtSKSigma", genJtSKSigma_, Form("genJtSKSigma[nGenJtSK][%d]/F", nSigma));
    genTreeAna_p->Branch("genJtSKRefPart", genJtSKRefPart_, Form("genJtSKRefPart[nGenJtSK]/I"));
    genTreeAna_p->Branch("genJtSKFFMUnsub", genJtSKFFMUnsub_, Form("genJtSKFFMUnsub[nGenJtSK][%d]/F", nFFM));
    genTreeAna_p->Branch("genJtSKFFMSub", genJtSKFFMSub_, Form("genJtSKFFMSub[nGenJtSK][%d]/F", nFFM));
    genTreeAna_p->Branch("genJtSKFFMSubBetter", genJtSKFFMSubBetter_, Form("genJtSKFFMSubBetter[nGenJtSK][%d]/F", nFFM));
    genTreeAna_p->Branch("genSKTau", genSKTau_, Form("genSKTau[nGenJtSK][%d][%d]/F", nTau, nBeta));
    genTreeAna_p->Branch("genSubJtSKPt", genSubJtSKPt_, Form("genSubJtSKPt[nGenJtSK][%d]/F", nSubjet));
    genTreeAna_p->Branch("genSubJtSKPhi", genSubJtSKPhi_, Form("genSubJtSKPhi[nGenJtSK][%d]/F", nSubjet));
    genTreeAna_p->Branch("genSubJtSKEta", genSubJtSKEta_, Form("genSubJtSKEta[nGenJtSK][%d]/F", nSubjet));

    genTreeAna_p->Branch("nGenJtSUBE", &nGenJtSUBE_, Form("nGenJtSUBE/I"));
    genTreeAna_p->Branch("genJtSUBEPt", genJtSUBEPt_, Form("genJtSUBEPt[nGenJtSUBE]/F"));
    genTreeAna_p->Branch("genJtSUBEPhi", genJtSUBEPhi_, Form("genJtSUBEPhi[nGenJtSUBE]/F"));
    genTreeAna_p->Branch("genJtSUBEEta", genJtSUBEEta_, Form("genJtSUBEEta[nGenJtSUBE]/F"));
    genTreeAna_p->Branch("genJtSUBEConstN", genJtSUBEConstN_, Form("genJtSUBEConstN[nGenJtSUBE]/I"));
    genTreeAna_p->Branch("genJtSUBEPTD", genJtSUBEPTD_, Form("genJtSUBEPTD[nGenJtSUBE]/F"));
    genTreeAna_p->Branch("genJtSUBER2", genJtSUBER2_, Form("genJtSUBER2[nGenJtSUBE]/F"));
    genTreeAna_p->Branch("genJtSUBESigma", genJtSUBESigma_, Form("genJtSUBESigma[nGenJtSUBE][%d]/F", nSigma));
    genTreeAna_p->Branch("genJtSUBERefPart", genJtSUBERefPart_, Form("genJtSUBERefPart[nGenJtSUBE]/I"));
    genTreeAna_p->Branch("genJtSUBEFFMUnsub", genJtSUBEFFMUnsub_, Form("genJtSUBEFFMUnsub[nGenJtSUBE][%d]/F", nFFM));
    genTreeAna_p->Branch("genJtSUBEFFMSub", genJtSUBEFFMSub_, Form("genJtSUBEFFMSub[nGenJtSUBE][%d]/F", nFFM));
    genTreeAna_p->Branch("genJtSUBEFFMSubBetter", genJtSUBEFFMSubBetter_, Form("genJtSUBEFFMSubBetter[nGenJtSUBE][%d]/F", nFFM));
    genTreeAna_p->Branch("genSUBETau", genSUBETau_, Form("genSUBETau[nGenJtSUBE][%d][%d]/F", nTau, nBeta));
    genTreeAna_p->Branch("genSubJtSUBEPt", genSubJtSUBEPt_, Form("genSubJtSUBEPt[nGenJtSUBE][%d]/F", nSubjet));
    genTreeAna_p->Branch("genSubJtSUBEPhi", genSubJtSUBEPhi_, Form("genSubJtSUBEPhi[nGenJtSUBE][%d]/F", nSubjet));
    genTreeAna_p->Branch("genSubJtSUBEEta", genSubJtSUBEEta_, Form("genSubJtSUBEEta[nGenJtSUBE][%d]/F", nSubjet));
  }

  //Jet TreeAna Branches

  jetTreeAna_p->Branch("run", &run_, Form("run/I"));
  jetTreeAna_p->Branch("evt", &evt_, Form("evt/I"));
  jetTreeAna_p->Branch("lumi", &lumi_, Form("lumi/I"));

  if(hi){
    jetTreeAna_p->Branch("hiBin", &hiBin_, Form("hiBin/I"));
    if(montecarlo) jetTreeAna_p->Branch("b", &b_, Form("b/F"));
  }
   
  if(montecarlo){
    jetTreeAna_p->Branch("pthat", &pthat_, Form("pthat/F"));
    jetTreeAna_p->Branch("pthatWeight", &pthatWeight_, Form("pthatWeight/F"));
  }

  if(hi){
    jetTreeAna_p->Branch("hiEvtPlane", &hiEvtPlane_, Form("hiEvtPlane/F"));
    jetTreeAna_p->Branch("psin", &psin_, Form("psin/F"));
  }    

  jetTreeAna_p->Branch("eventSet", eventSet_, Form("eventSet[5]/O"));

  jetTreeAna_p->Branch("AlgJtPt", AlgJtPt_, Form("AlgJtPt[5][5]/F"));
  jetTreeAna_p->Branch("AlgJtPhi", AlgJtPhi_, Form("AlgJtPhi[5][5]/F"));
  jetTreeAna_p->Branch("AlgJtEta", AlgJtEta_, Form("AlgJtEta[5][5]/F"));
  jetTreeAna_p->Branch("AlgJtRawPt", AlgJtRawPt_, Form("AlgJtRawPt[5][5]/F"));

  jetTreeAna_p->Branch("AlgJtDelPhi", AlgJtDelPhi_, Form("AlgJtDelPhi[5]/F"));
  jetTreeAna_p->Branch("AlgJtAsymm", AlgJtAsymm_, Form("AlgJtAsymm[5]/F"));

  if(montecarlo){
    jetTreeAna_p->Branch("AlgRefPartFlav", AlgRefPartFlav_, Form("AlgRefPartFlav[5][5]/I"));
    jetTreeAna_p->Branch("AlgRefPt", AlgRefPt_, Form("AlgRefPt[5][5]/F"));
    jetTreeAna_p->Branch("AlgRefPhi", AlgRefPhi_, Form("AlgRefPhi[5][5]/F"));
    jetTreeAna_p->Branch("AlgRefEta", AlgRefEta_, Form("AlgRefEta[5][5]/F"));
  }    

  return;
}


void GetAnaBranches(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);
  //Rechit TreeAna Branches

  if(!isGen){
    rechitTreeAna_p->SetBranchAddress("rechitSKPtCut", &rechitSKPtCut_);

    rechitTreeAna_p->SetBranchAddress("nRechitJtRaw", &nRechitJtRaw_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawPt", rechitJtRawPt_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawPhi", rechitJtRawPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawEta", rechitJtRawEta_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawConstN", rechitJtRawConstN_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawPTD", rechitJtRawPTD_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawR2", rechitJtRawR2_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawSigma", rechitJtRawSigma_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawRefPart", rechitJtRawRefPart_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawFFMUnsub", rechitJtRawFFMUnsub_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawFFMSub", rechitJtRawFFMSub_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawFFMSubBetter", rechitJtRawFFMSubBetter_);
    rechitTreeAna_p->SetBranchAddress("rechitRawTau", rechitRawTau_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtRawPt", rechitSubJtRawPt_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtRawPhi", rechitSubJtRawPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtRawEta", rechitSubJtRawEta_);
    
    rechitTreeAna_p->SetBranchAddress("nRechitJtVs", &nRechitJtVs_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPt", rechitJtVsPt_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPhi", rechitJtVsPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsEta", rechitJtVsEta_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsConstN", rechitJtVsConstN_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPTD", rechitJtVsPTD_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsR2", rechitJtVsR2_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsSigma", rechitJtVsSigma_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsRefPart", rechitJtVsRefPart_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsFFMUnsub", rechitJtVsFFMUnsub_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsFFMSub", rechitJtVsFFMSub_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsFFMSubBetter", rechitJtVsFFMSubBetter_);
    rechitTreeAna_p->SetBranchAddress("rechitVsTau", rechitVsTau_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtVsPt", rechitSubJtVsPt_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtVsPhi", rechitSubJtVsPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtVsEta", rechitSubJtVsEta_);
    
    //PF TreeAna Branches
    pfcandTreeAna_p->SetBranchAddress("pfSKPtCut", &pfSKPtCut_);    

    pfcandTreeAna_p->SetBranchAddress("nPFJtRaw", &nPFJtRaw_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawPhi", pfJtRawPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawEta", pfJtRawEta_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawConstN", pfJtRawConstN_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawPTD", pfJtRawPTD_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawR2", pfJtRawR2_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawSigma", pfJtRawSigma_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawRefPart", pfJtRawRefPart_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawFFMUnsub", pfJtRawFFMUnsub_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawFFMSub", pfJtRawFFMSub_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawFFMSubBetter", pfJtRawFFMSubBetter_);
    pfcandTreeAna_p->SetBranchAddress("pfRawTau", pfRawTau_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtRawPt", pfSubJtRawPt_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtRawPhi", pfSubJtRawPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtRawEta", pfSubJtRawEta_);

    pfcandTreeAna_p->SetBranchAddress("nPFJtVs", &nPFJtVs_);    
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPt", pfJtVsPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPhi", pfJtVsPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsEta", pfJtVsEta_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsConstN", pfJtVsConstN_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPTD", pfJtVsPTD_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsR2", pfJtVsR2_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsSigma", pfJtVsSigma_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsRefPart", pfJtVsRefPart_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsFFMUnsub", pfJtVsFFMUnsub_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsFFMSub", pfJtVsFFMSub_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsFFMSubBetter", pfJtVsFFMSubBetter_);
    pfcandTreeAna_p->SetBranchAddress("pfVsTau", pfVsTau_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtVsPt", pfSubJtVsPt_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtVsPhi", pfSubJtVsPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtVsEta", pfSubJtVsEta_);
    
    pfcandTreeAna_p->SetBranchAddress("nPFJtSK", &nPFJtSK_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPt", pfJtSKPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPhi", pfJtSKPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKEta", pfJtSKEta_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKConstN", pfJtSKConstN_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPTD", pfJtSKPTD_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKR2", pfJtSKR2_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKSigma", pfJtSKSigma_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKRefPart", pfJtSKRefPart_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKFFMUnsub", pfJtSKFFMUnsub_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKFFMSub", pfJtSKFFMSub_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKFFMSubBetter", pfJtSKFFMSubBetter_);
    pfcandTreeAna_p->SetBranchAddress("pfSKTau", pfSKTau_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtSKPt", pfSubJtSKPt_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtSKPhi", pfSubJtSKPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtSKEta", pfSubJtSKEta_);
    
    //Trk TreeAna Branches
    trkTreeAna_p->SetBranchAddress("trkSKPtCut", &trkSKPtCut_);    

    trkTreeAna_p->SetBranchAddress("nTrkJtRaw", &nTrkJtRaw_);
    trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPt_);
    trkTreeAna_p->SetBranchAddress("trkJtRawPhi", trkJtRawPhi_);
    trkTreeAna_p->SetBranchAddress("trkJtRawEta", trkJtRawEta_);
    trkTreeAna_p->SetBranchAddress("trkJtRawConstN", trkJtRawConstN_);
    trkTreeAna_p->SetBranchAddress("trkJtRawPTD", trkJtRawPTD_);
    trkTreeAna_p->SetBranchAddress("trkJtRawR2", trkJtRawR2_);
    trkTreeAna_p->SetBranchAddress("trkJtRawSigma", trkJtRawSigma_);
    trkTreeAna_p->SetBranchAddress("trkJtRawRefPart", trkJtRawRefPart_);
    trkTreeAna_p->SetBranchAddress("trkJtRawFFMUnsub", trkJtRawFFMUnsub_);
    trkTreeAna_p->SetBranchAddress("trkJtRawFFMSub", trkJtRawFFMSub_);
    trkTreeAna_p->SetBranchAddress("trkJtRawFFMSubBetter", trkJtRawFFMSubBetter_);
    trkTreeAna_p->SetBranchAddress("trkRawTau", trkRawTau_);
    trkTreeAna_p->SetBranchAddress("trkSubJtRawPt", trkSubJtRawPt_);
    trkTreeAna_p->SetBranchAddress("trkSubJtRawPhi", trkSubJtRawPhi_);
    trkTreeAna_p->SetBranchAddress("trkSubJtRawEta", trkSubJtRawEta_);
    
    trkTreeAna_p->SetBranchAddress("nTrkJtSK", &nTrkJtSK_);
    trkTreeAna_p->SetBranchAddress("trkJtSKPt", trkJtSKPt_);
    trkTreeAna_p->SetBranchAddress("trkJtSKPhi", trkJtSKPhi_);
    trkTreeAna_p->SetBranchAddress("trkJtSKEta", trkJtSKEta_);
    trkTreeAna_p->SetBranchAddress("trkJtSKConstN", trkJtSKConstN_);
    trkTreeAna_p->SetBranchAddress("trkJtSKPTD", trkJtSKPTD_);
    trkTreeAna_p->SetBranchAddress("trkJtSKR2", trkJtSKR2_);
    trkTreeAna_p->SetBranchAddress("trkJtSKSigma", trkJtSKSigma_);
    trkTreeAna_p->SetBranchAddress("trkJtSKRefPart", trkJtSKRefPart_);
    trkTreeAna_p->SetBranchAddress("trkJtSKFFMUnsub", trkJtSKFFMUnsub_);
    trkTreeAna_p->SetBranchAddress("trkJtSKFFMSub", trkJtSKFFMSub_);
    trkTreeAna_p->SetBranchAddress("trkJtSKFFMSubBetter", trkJtSKFFMSubBetter_);
    trkTreeAna_p->SetBranchAddress("trkSKTau", trkSKTau_);
    trkTreeAna_p->SetBranchAddress("trkSubJtSKPt", trkSubJtSKPt_);
    trkTreeAna_p->SetBranchAddress("trkSubJtSKPhi", trkSubJtSKPhi_);
    trkTreeAna_p->SetBranchAddress("trkSubJtSKEta", trkSubJtSKEta_);
  }
  //Gen TreeAna Branches

  if(montecarlo){
    genTreeAna_p->SetBranchAddress("genSKPtCut", &genSKPtCut_);

    genTreeAna_p->SetBranchAddress("nGenJtRaw", &nGenJtRaw_);
    genTreeAna_p->SetBranchAddress("genJtRawPt", genJtRawPt_);
    genTreeAna_p->SetBranchAddress("genJtRawPhi", genJtRawPhi_);
    genTreeAna_p->SetBranchAddress("genJtRawEta", genJtRawEta_);
    genTreeAna_p->SetBranchAddress("genJtRawConstN", genJtRawConstN_);
    genTreeAna_p->SetBranchAddress("genJtRawPTD", genJtRawPTD_);
    genTreeAna_p->SetBranchAddress("genJtRawR2", genJtRawR2_);
    genTreeAna_p->SetBranchAddress("genJtRawSigma", genJtRawSigma_);
    genTreeAna_p->SetBranchAddress("genJtRawRefPart", genJtRawRefPart_);
    genTreeAna_p->SetBranchAddress("genJtRawFFMUnsub", genJtRawFFMUnsub_);
    genTreeAna_p->SetBranchAddress("genJtRawFFMSub", genJtRawFFMSub_);
    genTreeAna_p->SetBranchAddress("genJtRawFFMSubBetter", genJtRawFFMSubBetter_);
    genTreeAna_p->SetBranchAddress("genRawTau", genRawTau_);
    genTreeAna_p->SetBranchAddress("genSubJtRawPt", genSubJtRawPt_);
    genTreeAna_p->SetBranchAddress("genSubJtRawPhi", genSubJtRawPhi_);
    genTreeAna_p->SetBranchAddress("genSubJtRawEta", genSubJtRawEta_);

    genTreeAna_p->SetBranchAddress("nGenJtSK", &nGenJtSK_);
    genTreeAna_p->SetBranchAddress("genJtSKPt", genJtSKPt_);
    genTreeAna_p->SetBranchAddress("genJtSKPhi", genJtSKPhi_);
    genTreeAna_p->SetBranchAddress("genJtSKEta", genJtSKEta_);
    genTreeAna_p->SetBranchAddress("genJtSKConstN", genJtSKConstN_);
    genTreeAna_p->SetBranchAddress("genJtSKPTD", genJtSKPTD_);
    genTreeAna_p->SetBranchAddress("genJtSKR2", genJtSKR2_);
    genTreeAna_p->SetBranchAddress("genJtSKSigma", genJtSKSigma_);
    genTreeAna_p->SetBranchAddress("genJtSKRefPart", genJtSKRefPart_);
    genTreeAna_p->SetBranchAddress("genJtSKFFMUnsub", genJtSKFFMUnsub_);
    genTreeAna_p->SetBranchAddress("genJtSKFFMSub", genJtSKFFMSub_);
    genTreeAna_p->SetBranchAddress("genJtSKFFMSubBetter", genJtSKFFMSubBetter_);
    genTreeAna_p->SetBranchAddress("genSKTau", genSKTau_);
    genTreeAna_p->SetBranchAddress("genSubJtSKPt", genSubJtSKPt_);
    genTreeAna_p->SetBranchAddress("genSubJtSKPhi", genSubJtSKPhi_);
    genTreeAna_p->SetBranchAddress("genSubJtSKEta", genSubJtSKEta_);

    genTreeAna_p->SetBranchAddress("nGenJtSUBE", &nGenJtSUBE_);
    genTreeAna_p->SetBranchAddress("genJtSUBEPt", genJtSUBEPt_);
    genTreeAna_p->SetBranchAddress("genJtSUBEPhi", genJtSUBEPhi_);
    genTreeAna_p->SetBranchAddress("genJtSUBEEta", genJtSUBEEta_);
    genTreeAna_p->SetBranchAddress("genJtSUBEConstN", genJtSUBEConstN_);
    genTreeAna_p->SetBranchAddress("genJtSUBEPTD", genJtSUBEPTD_);
    genTreeAna_p->SetBranchAddress("genJtSUBER2", genJtSUBER2_);
    genTreeAna_p->SetBranchAddress("genJtSUBESigma", genJtSUBESigma_);
    genTreeAna_p->SetBranchAddress("genJtSUBERefPart", genJtSUBERefPart_);
    genTreeAna_p->SetBranchAddress("genJtSUBEFFMUnsub", genJtSUBEFFMUnsub_);
    genTreeAna_p->SetBranchAddress("genJtSUBEFFMSub", genJtSUBEFFMSub_);
    genTreeAna_p->SetBranchAddress("genJtSUBEFFMSubBetter", genJtSUBEFFMSubBetter_);
    genTreeAna_p->SetBranchAddress("genSUBETau", genSUBETau_);
    genTreeAna_p->SetBranchAddress("genSubJtSUBEPt", genSubJtSUBEPt_);
    genTreeAna_p->SetBranchAddress("genSubJtSUBEPhi", genSubJtSUBEPhi_);
    genTreeAna_p->SetBranchAddress("genSubJtSUBEEta", genSubJtSUBEEta_);

    std::cout << "Added Branches" << std::endl;
  }
  //Jet TreeAna Branches

  jetTreeAna_p->SetBranchAddress("run", &run_);
  jetTreeAna_p->SetBranchAddress("evt", &evt_);
  jetTreeAna_p->SetBranchAddress("lumi", &lumi_);

  if(hi){
    jetTreeAna_p->SetBranchAddress("hiBin", &hiBin_);
    if(montecarlo) jetTreeAna_p->SetBranchAddress("b", &b_);
  }

  if(montecarlo){
    jetTreeAna_p->SetBranchAddress("pthat", &pthat_);
    jetTreeAna_p->SetBranchAddress("pthatWeight", &pthatWeight_);
  }

  if(hi){
    jetTreeAna_p->SetBranchAddress("hiEvtPlane", &hiEvtPlane_);
    jetTreeAna_p->SetBranchAddress("psin", &psin_);
  }  

  jetTreeAna_p->SetBranchAddress("eventSet", eventSet_);

  jetTreeAna_p->SetBranchAddress("AlgJtPt", AlgJtPt_);
  jetTreeAna_p->SetBranchAddress("AlgJtPhi", AlgJtPhi_);
  jetTreeAna_p->SetBranchAddress("AlgJtEta", AlgJtEta_);
  jetTreeAna_p->SetBranchAddress("AlgJtRawPt", AlgJtRawPt_);

  jetTreeAna_p->SetBranchAddress("AlgJtDelPhi", AlgJtDelPhi_);
  jetTreeAna_p->SetBranchAddress("AlgJtAsymm", AlgJtAsymm_);

  if(montecarlo){
    jetTreeAna_p->SetBranchAddress("AlgRefPartFlav", AlgRefPartFlav_);
    jetTreeAna_p->SetBranchAddress("AlgRefPt", AlgRefPt_);
    jetTreeAna_p->SetBranchAddress("AlgRefPhi", AlgRefPhi_);
    jetTreeAna_p->SetBranchAddress("AlgRefEta", AlgRefEta_);
  }

  return;
}


void InitFastJetAnaSkim(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  std::cout << "Init FastJet AnaSkim" << std::endl;

  if(!isGen){
    rechitTreeAna_p = new TTree("rechitTreeAna", "rechitTreeAna");
    pfcandTreeAna_p = new TTree("pfcandTreeAna", "pfcandTreeAna");
    trkTreeAna_p = new TTree("trkTreeAna", "trkTreeAna");
  }
  if(isMonteCarlo(sType)) genTreeAna_p = new TTree("genTreeAna", "genTreeAna");
  jetTreeAna_p = new TTree("jetTreeAna", "jetTreeAna");

  SetAnaBranches(sType);

  return;
}


void CleanupFastJetAnaSkim()
{
  if(rechitTreeAna_p != 0) delete rechitTreeAna_p;
  if(pfcandTreeAna_p != 0) delete pfcandTreeAna_p;
  if(trkTreeAna_p != 0) delete trkTreeAna_p;
  if(genTreeAna_p != 0) delete genTreeAna_p;
  if(jetTreeAna_p != 0) delete jetTreeAna_p;

  return;
}


void GetFastJetAnaSkim(TFile* iniSkimFile_p, sampleType sType = kHIDATA, Bool_t isGen = false)
{
  std::cout << "Get FastJet AnaSkim" << std::endl;

  if(!isGen){
    rechitTreeAna_p = (TTree*)iniSkimFile_p->Get("rechitTreeAna");
    pfcandTreeAna_p = (TTree*)iniSkimFile_p->Get("pfcandTreeAna");
    trkTreeAna_p = (TTree*)iniSkimFile_p->Get("trkTreeAna");
  }
  if(isMonteCarlo(sType)){
    genTreeAna_p = (TTree*)iniSkimFile_p->Get("genTreeAna");
    std::cout << "Added gen Tree" << std::endl;
  }
  jetTreeAna_p = (TTree*)iniSkimFile_p->Get("jetTreeAna");

  GetAnaBranches(sType);

  return;
}


void InitJtVar(){
  rechitSKPtCut_ = 0.010;
  pfSKPtCut_ = 0.010;
  trkSKPtCut_ = 0.010;
  genSKPtCut_ = 0.010;

  nRechitJtRaw_ = 0;
  nRechitJtVs_ = 0;

  nPFJtRaw_ = 0;
  nPFJtVs_ = 0;
  nPFJtSK_ = 0;

  nTrkJtRaw_ = 0;
  nTrkJtSK_ = 0;

  nGenJtRaw_ = 0;
  nGenJtSK_ = 0;
  nGenJtSUBE_ = 0;

  return;
}


#endif
