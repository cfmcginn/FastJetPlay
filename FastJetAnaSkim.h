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

Float_t rechitJtRawPt_[5];
Float_t rechitJtRawPhi_[5];
Float_t rechitJtRawEta_[5];
Float_t rechitJtRawPTD_[5];
Float_t rechitJtRawR2_[5];
Float_t rechitJtRawSigma_[5][nSigma];
Int_t rechitJtRawRefPart_[5];
Float_t rechitJtRawFFMUnsub_[5][nFFM];
Float_t rechitJtRawFFMSub_[5][nFFM];
Float_t rechitJtRawFFMSubBetter_[5][nFFM];
Float_t rechitRawTau_[5][nTau][nBeta];
Float_t rechitSubJtRawPt_[5][nSubjet];
Float_t rechitSubJtRawPhi_[5][nSubjet];
Float_t rechitSubJtRawEta_[5][nSubjet];

Float_t rechitJtVsPt_[5];
Float_t rechitJtVsPhi_[5];
Float_t rechitJtVsEta_[5];
Float_t rechitJtVsPTD_[5];
Float_t rechitJtVsR2_[5];
Float_t rechitJtVsSigma_[5][nSigma];
Int_t rechitJtVsRefPart_[5];
Float_t rechitJtVsFFMUnsub_[5][nFFM];
Float_t rechitJtVsFFMSub_[5][nFFM];
Float_t rechitJtVsFFMSubBetter_[5][nFFM];
Float_t rechitVsTau_[5][nTau][nBeta];
Float_t rechitSubJtVsPt_[5][nSubjet];
Float_t rechitSubJtVsPhi_[5][nSubjet];
Float_t rechitSubJtVsEta_[5][nSubjet];

//pfcand TreeAna Variables

Float_t pfSKPtCut_;

Float_t pfJtRawPt_[5];
Float_t pfJtRawPhi_[5];
Float_t pfJtRawEta_[5];
Float_t pfJtRawPTD_[5];
Float_t pfJtRawR2_[5];
Float_t pfJtRawSigma_[5][nSigma];
Int_t pfJtRawRefPart_[5];
Float_t pfJtRawFFMUnsub_[5][nFFM];
Float_t pfJtRawFFMSub_[5][nFFM];
Float_t pfJtRawFFMSubBetter_[5][nFFM];
Float_t pfRawTau_[5][nTau][nBeta];
Float_t pfSubJtRawPt_[5][nSubjet];
Float_t pfSubJtRawPhi_[5][nSubjet];
Float_t pfSubJtRawEta_[5][nSubjet];

Float_t pfJtVsPt_[5];
Float_t pfJtVsPhi_[5];
Float_t pfJtVsEta_[5];
Float_t pfJtVsPTD_[5];
Float_t pfJtVsR2_[5];
Float_t pfJtVsSigma_[5][nSigma];
Int_t pfJtVsRefPart_[5];
Float_t pfJtVsFFMUnsub_[5][nFFM];
Float_t pfJtVsFFMSub_[5][nFFM];
Float_t pfJtVsFFMSubBetter_[5][nFFM];
Float_t pfVsTau_[5][nTau][nBeta];
Float_t pfSubJtVsPt_[5][nSubjet];
Float_t pfSubJtVsPhi_[5][nSubjet];
Float_t pfSubJtVsEta_[5][nSubjet];

Float_t pfJtSKPt_[5];
Float_t pfJtSKPhi_[5];
Float_t pfJtSKEta_[5];
Float_t pfJtSKPTD_[5];
Float_t pfJtSKR2_[5];
Float_t pfJtSKSigma_[5][nSigma];
Int_t pfJtSKRefPart_[5];
Float_t pfJtSKFFMUnsub_[5][nFFM];
Float_t pfJtSKFFMSub_[5][nFFM];
Float_t pfJtSKFFMSubBetter_[5][nFFM];
Float_t pfSKTau_[5][nTau][nBeta];
Float_t pfSubJtSKPt_[5][nSubjet];
Float_t pfSubJtSKPhi_[5][nSubjet];
Float_t pfSubJtSKEta_[5][nSubjet];


//track TreeAna Variables

Float_t trkSKPtCut_;

Float_t trkJtRawPt_[5];
Float_t trkJtRawPhi_[5];
Float_t trkJtRawEta_[5];
Float_t trkJtRawPTD_[5];
Float_t trkJtRawR2_[5];
Float_t trkJtRawSigma_[5][nSigma];
Int_t trkJtRawRefPart_[5];
Float_t trkJtRawFFMUnsub_[5][nFFM];
Float_t trkJtRawFFMSub_[5][nFFM];
Float_t trkJtRawFFMSubBetter_[5][nFFM];
Float_t trkRawTau_[5][nTau][nBeta];
Float_t trkSubJtRawPt_[5][nSubjet];
Float_t trkSubJtRawPhi_[5][nSubjet];
Float_t trkSubJtRawEta_[5][nSubjet];

Float_t trkJtSKPt_[5];
Float_t trkJtSKPhi_[5];
Float_t trkJtSKEta_[5];
Float_t trkJtSKPTD_[5];
Float_t trkJtSKR2_[5];
Float_t trkJtSKSigma_[5][nSigma];
Int_t trkJtSKRefPart_[5];
Float_t trkJtSKFFMUnsub_[5][nFFM];
Float_t trkJtSKFFMSub_[5][nFFM];
Float_t trkJtSKFFMSubBetter_[5][nFFM];
Float_t trkSKTau_[5][nTau][nBeta];
Float_t trkSubJtSKPt_[5][nSubjet];
Float_t trkSubJtSKPhi_[5][nSubjet];
Float_t trkSubJtSKEta_[5][nSubjet];

//Gen TreeAna Variables

Float_t genSKPtCut_;

Float_t genJtRawPt_[5];
Float_t genJtRawPhi_[5];
Float_t genJtRawEta_[5];
Float_t genJtRawPTD_[5];
Float_t genJtRawR2_[5];
Float_t genJtRawSigma_[5][nSigma];
Int_t genJtRawRefPart_[5];
Float_t genJtRawFFMUnsub_[5][nFFM];
Float_t genJtRawFFMSub_[5][nFFM];
Float_t genJtRawFFMSubBetter_[5][nFFM];
Float_t genRawTau_[5][nTau][nBeta];
Float_t genSubJtRawPt_[5][nSubjet];
Float_t genSubJtRawPhi_[5][nSubjet];
Float_t genSubJtRawEta_[5][nSubjet];

Float_t genJtSKPt_[5];
Float_t genJtSKPhi_[5];
Float_t genJtSKEta_[5];
Float_t genJtSKPTD_[5];
Float_t genJtSKR2_[5];
Float_t genJtSKSigma_[5][nSigma];
Int_t genJtSKRefPart_[5];
Float_t genJtSKFFMUnsub_[5][nFFM];
Float_t genJtSKFFMSub_[5][nFFM];
Float_t genJtSKFFMSubBetter_[5][nFFM];
Float_t genSKTau_[5][nTau][nBeta];
Float_t genSubJtSKPt_[5][nSubjet];
Float_t genSubJtSKPhi_[5][nSubjet];
Float_t genSubJtSKEta_[5][nSubjet];

Float_t genJtSUBEPt_[5];
Float_t genJtSUBEPhi_[5];
Float_t genJtSUBEEta_[5];
Float_t genJtSUBEPTD_[5];
Float_t genJtSUBER2_[5];
Float_t genJtSUBESigma_[5][nSigma];
Int_t genJtSUBERefPart_[5];
Float_t genJtSUBEFFMUnsub_[5][nFFM];
Float_t genJtSUBEFFMSub_[5][nFFM];
Float_t genJtSUBEFFMSubBetter_[5][nFFM];
Float_t genSUBETau_[5][nTau][nBeta];
Float_t genSubJtSUBEPt_[5][nSubjet];
Float_t genSubJtSUBEPhi_[5][nSubjet];
Float_t genSubJtSUBEEta_[5][nSubjet];

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
    rechitTreeAna_p->Branch("rechitSKPtCut", &rechitSKPtCut_, "rechitSKPtCut/F");

    rechitTreeAna_p->Branch("rechitJtRawPt", rechitJtRawPt_, "rechitJtRawPt[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawPhi", rechitJtRawPhi_, "rechitJtRawPhi[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawEta", rechitJtRawEta_, "rechitJtRawEta[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawPTD", rechitJtRawPTD_, "rechitJtRawPTD[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawR2", rechitJtRawR2_, "rechitJtRawR2[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawSigma", rechitJtRawSigma_, "rechitJtRawSigma[5][nSigma]/F");
    rechitTreeAna_p->Branch("rechitJtRawRefPart", rechitJtRawRefPart_, "rechitJtRawRefPart[5]/I");
    rechitTreeAna_p->Branch("rechitJtRawFFMUnsub", rechitJtRawFFMUnsub_, "rechitJtRawFFMUnsub[5][nFFM]/F");
    rechitTreeAna_p->Branch("rechitJtRawFFMUnsub", rechitJtRawFFMUnsub_, "rechitJtRawFFMUnsub[5][nFFM]/F");
    rechitTreeAna_p->Branch("rechitJtRawFFMUnsub", rechitJtRawFFMUnsub_, "rechitJtRawFFMUnsub[5][nFFM]/F");
    rechitTreeAna_p->Branch("rechitRawTau", rechitRawTau_, "rechitRawTau[5][nTau][nBeta]/F");
    rechitTreeAna_p->Branch("rechitSubJtRawPt", rechitSubJtRawPt_, "rechitSubJtRawPt[5][nSubjet]/F");
    rechitTreeAna_p->Branch("rechitSubJtRawPhi", rechitSubJtRawPhi_, "rechitSubJtRawPhi[5][nSubjet]/F");
    rechitTreeAna_p->Branch("rechitSubJtRawEta", rechitSubJtRawEta_, "rechitSubJtRawEta[5][nSubjet]/F");
    
    rechitTreeAna_p->Branch("rechitJtVsPt", rechitJtVsPt_, "rechitJtVsPt[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsPhi", rechitJtVsPhi_, "rechitJtVsPhi[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsEta", rechitJtVsEta_, "rechitJtVsEta[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsPTD", rechitJtVsPTD_, "rechitJtVsPTD[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsR2", rechitJtVsR2_, "rechitJtVsR2[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsSigma", rechitJtVsSigma_, "rechitJtVsSigma[5][nSigma]/F");
    rechitTreeAna_p->Branch("rechitJtVsRefPart", rechitJtVsRefPart_, "rechitJtVsRefPart[5]/I");
    rechitTreeAna_p->Branch("rechitJtVsFFMUnsub", rechitJtVsFFMUnsub_, "rechitJtVsFFMUnsub[5][nFFM]/F");
    rechitTreeAna_p->Branch("rechitJtVsFFMUnsub", rechitJtVsFFMUnsub_, "rechitJtVsFFMUnsub[5][nFFM]/F");
    rechitTreeAna_p->Branch("rechitJtVsFFMUnsub", rechitJtVsFFMUnsub_, "rechitJtVsFFMUnsub[5][nFFM]/F");
    rechitTreeAna_p->Branch("rechitVsTau", rechitVsTau_, "rechitVsTau[5][nTau][nBeta]/F");
    rechitTreeAna_p->Branch("rechitSubJtVsPt", rechitSubJtVsPt_, "rechitSubJtVsPt[5][nSubjet]/F");
    rechitTreeAna_p->Branch("rechitSubJtVsPhi", rechitSubJtVsPhi_, "rechitSubJtVsPhi[5][nSubjet]/F");
    rechitTreeAna_p->Branch("rechitSubJtVsEta", rechitSubJtVsEta_, "rechitSubJtVsEta[5][nSubjet]/F");
    
    //PF TreeAna Branches
    pfcandTreeAna_p->Branch("pfSKPtCut", &pfSKPtCut_, "pfSKPtCut/F");    

    pfcandTreeAna_p->Branch("pfJtRawPt", pfJtRawPt_, "pfJtRawPt[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawPhi", pfJtRawPhi_, "pfJtRawPhi[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawEta", pfJtRawEta_, "pfJtRawEta[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawPTD", pfJtRawPTD_, "pfJtRawPTD[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawR2", pfJtRawR2_, "pfJtRawR2[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawSigma", pfJtRawSigma_, "pfJtRawSigma[5][nSigma]/F");
    pfcandTreeAna_p->Branch("pfJtRawRefPart", pfJtRawRefPart_, "pfJtRawRefPart[5]/I");
    pfcandTreeAna_p->Branch("pfJtRawFFMUnsub", pfJtRawFFMUnsub_, "pfJtRawFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfJtRawFFMUnsub", pfJtRawFFMUnsub_, "pfJtRawFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfJtRawFFMUnsub", pfJtRawFFMUnsub_, "pfJtRawFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfRawTau", pfRawTau_, "pfRawTau[5][nTau][nBeta]/F");
    pfcandTreeAna_p->Branch("pfSubJtRawPt", pfSubJtRawPt_, "pfSubJtRawPt[5][nSubjet]/F");
    pfcandTreeAna_p->Branch("pfSubJtRawPhi", pfSubJtRawPhi_, "pfSubJtRawPhi[5][nSubjet]/F");
    pfcandTreeAna_p->Branch("pfSubJtRawEta", pfSubJtRawEta_, "pfSubJtRawEta[5][nSubjet]/F");
    
    pfcandTreeAna_p->Branch("pfJtVsPt", pfJtVsPt_, "pfJtVsPt[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsPhi", pfJtVsPhi_, "pfJtVsPhi[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsEta", pfJtVsEta_, "pfJtVsEta[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsPTD", pfJtVsPTD_, "pfJtVsPTD[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsR2", pfJtVsR2_, "pfJtVsR2[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsSigma", pfJtVsSigma_, "pfJtVsSigma[5][nSigma]/F");
    pfcandTreeAna_p->Branch("pfJtVsRefPart", pfJtVsRefPart_, "pfJtVsRefPart[5]/I");
    pfcandTreeAna_p->Branch("pfJtVsFFMUnsub", pfJtVsFFMUnsub_, "pfJtVsFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfJtVsFFMUnsub", pfJtVsFFMUnsub_, "pfJtVsFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfJtVsFFMUnsub", pfJtVsFFMUnsub_, "pfJtVsFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfVsTau", pfVsTau_, "pfVsTau[5][nTau][nBeta]/F");
    pfcandTreeAna_p->Branch("pfSubJtVsPt", pfSubJtVsPt_, "pfSubJtVsPt[5][nSubjet]/F");
    pfcandTreeAna_p->Branch("pfSubJtVsPhi", pfSubJtVsPhi_, "pfSubJtVsPhi[5][nSubjet]/F");
    pfcandTreeAna_p->Branch("pfSubJtVsEta", pfSubJtVsEta_, "pfSubJtVsEta[5][nSubjet]/F");
    
    pfcandTreeAna_p->Branch("pfJtSKPt", pfJtSKPt_, "pfJtSKPt[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKPhi", pfJtSKPhi_, "pfJtSKPhi[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKEta", pfJtSKEta_, "pfJtSKEta[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKPTD", pfJtSKPTD_, "pfJtSKPTD[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKR2", pfJtSKR2_, "pfJtSKR2[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKSigma", pfJtSKSigma_, "pfJtSKSigma[5][nSigma]/F");
    pfcandTreeAna_p->Branch("pfJtSKFFMUnsub", pfJtSKFFMUnsub_, "pfJtSKFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfJtSKFFMUnsub", pfJtSKFFMUnsub_, "pfJtSKFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfJtSKFFMUnsub", pfJtSKFFMUnsub_, "pfJtSKFFMUnsub[5][nFFM]/F");
    pfcandTreeAna_p->Branch("pfJtSKRefPart", pfJtSKRefPart_, "pfJtSKRefPart[5]/I");
    pfcandTreeAna_p->Branch("pfSKTau", pfSKTau_, "pfSKTau[5][nTau][nBeta]/F");
    pfcandTreeAna_p->Branch("pfSubJtSKPt", pfSubJtSKPt_, "pfSubJtSKPt[5][nSubjet]/F");
    pfcandTreeAna_p->Branch("pfSubJtSKPhi", pfSubJtSKPhi_, "pfSubJtSKPhi[5][nSubjet]/F");
    pfcandTreeAna_p->Branch("pfSubJtSKEta", pfSubJtSKEta_, "pfSubJtSKEta[5][nSubjet]/F");
    
    //Trk TreeAna Branches
    trkTreeAna_p->Branch("trkSKPtCut", &trkSKPtCut_, "trkSKPtCut/F");    

    trkTreeAna_p->Branch("trkJtRawPt", trkJtRawPt_, "trkJtRawPt[5]/F");
    trkTreeAna_p->Branch("trkJtRawPhi", trkJtRawPhi_, "trkJtRawPhi[5]/F");
    trkTreeAna_p->Branch("trkJtRawEta", trkJtRawEta_, "trkJtRawEta[5]/F");
    trkTreeAna_p->Branch("trkJtRawPTD", trkJtRawPTD_, "trkJtRawPTD[5]/F");
    trkTreeAna_p->Branch("trkJtRawR2", trkJtRawR2_, "trkJtRawR2[5]/F");
    trkTreeAna_p->Branch("trkJtRawSigma", trkJtRawSigma_, "trkJtRawSigma[5][nSigma]/F");
    trkTreeAna_p->Branch("trkJtRawRefPart", trkJtRawRefPart_, "trkJtRawRefPart[5]/I");
    trkTreeAna_p->Branch("trkJtRawFFMUnsub", trkJtRawFFMUnsub_, "trkJtRawFFMUnsub[5][nFFM]/F");
    trkTreeAna_p->Branch("trkJtRawFFMUnsub", trkJtRawFFMUnsub_, "trkJtRawFFMUnsub[5][nFFM]/F");
    trkTreeAna_p->Branch("trkJtRawFFMUnsub", trkJtRawFFMUnsub_, "trkJtRawFFMUnsub[5][nFFM]/F");
    trkTreeAna_p->Branch("trkRawTau", trkRawTau_, "trkRawTau[5][nTau][nBeta]/F");
    trkTreeAna_p->Branch("trkSubJtRawPt", trkSubJtRawPt_, "trkSubJtRawPt[5][nSubjet]/F");
    trkTreeAna_p->Branch("trkSubJtRawPhi", trkSubJtRawPhi_, "trkSubJtRawPhi[5][nSubjet]/F");
    trkTreeAna_p->Branch("trkSubJtRawEta", trkSubJtRawEta_, "trkSubJtRawEta[5][nSubjet]/F");
    
    trkTreeAna_p->Branch("trkJtSKPt", trkJtSKPt_, "trkJtSKPt[5]/F");
    trkTreeAna_p->Branch("trkJtSKPhi", trkJtSKPhi_, "trkJtSKPhi[5]/F");
    trkTreeAna_p->Branch("trkJtSKEta", trkJtSKEta_, "trkJtSKEta[5]/F");
    trkTreeAna_p->Branch("trkJtSKPTD", trkJtSKPTD_, "trkJtSKPTD[5]/F");
    trkTreeAna_p->Branch("trkJtSKR2", trkJtSKR2_, "trkJtSKR2[5]/F");
    trkTreeAna_p->Branch("trkJtSKSigma", trkJtSKSigma_, "trkJtSKSigma[5][nSigma]/F");
    trkTreeAna_p->Branch("trkJtSKRefPart", trkJtSKRefPart_, "trkJtSKRefPart[5]/I");
    trkTreeAna_p->Branch("trkJtSKFFMUnsub", trkJtSKFFMUnsub_, "trkJtSKFFMUnsub[5][nFFM]/F");
    trkTreeAna_p->Branch("trkJtSKFFMUnsub", trkJtSKFFMUnsub_, "trkJtSKFFMUnsub[5][nFFM]/F");
    trkTreeAna_p->Branch("trkJtSKFFMUnsub", trkJtSKFFMUnsub_, "trkJtSKFFMUnsub[5][nFFM]/F");
    trkTreeAna_p->Branch("trkSKTau", trkSKTau_, "trkSKTau[5][nTau][nBeta]/F");
    trkTreeAna_p->Branch("trkSubJtSKPt", trkSubJtSKPt_, "trkSubJtSKPt[5][nSubjet]/F");
    trkTreeAna_p->Branch("trkSubJtSKPhi", trkSubJtSKPhi_, "trkSubJtSKPhi[5][nSubjet]/F");
    trkTreeAna_p->Branch("trkSubJtSKEta", trkSubJtSKEta_, "trkSubJtSKEta[5][nSubjet]/F");
  }    

  //Gen TreeAna Branches
  if(montecarlo){
    genTreeAna_p->Branch("genSKPtCut", &genSKPtCut_, "genSKPtCut/F");

    genTreeAna_p->Branch("genJtRawPt", genJtRawPt_, "genJtRawPt[5]/F");
    genTreeAna_p->Branch("genJtRawPhi", genJtRawPhi_, "genJtRawPhi[5]/F");
    genTreeAna_p->Branch("genJtRawEta", genJtRawEta_, "genJtRawEta[5]/F");
    genTreeAna_p->Branch("genJtRawPTD", genJtRawPTD_, "genJtRawPTD[5]/F");
    genTreeAna_p->Branch("genJtRawR2", genJtRawR2_, "genJtRawR2[5]/F");
    genTreeAna_p->Branch("genJtRawSigma", genJtRawSigma_, "genJtRawSigma[5][nSigma]/F");
    genTreeAna_p->Branch("genJtRawRefPart", genJtRawRefPart_, "genJtRawRefPart[5]/I");
    genTreeAna_p->Branch("genJtRawFFMUnsub", genJtRawFFMUnsub_, "genJtRawFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genJtRawFFMUnsub", genJtRawFFMUnsub_, "genJtRawFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genJtRawFFMUnsub", genJtRawFFMUnsub_, "genJtRawFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genRawTau", genRawTau_, "genRawTau[5][nTau][nBeta]/F");
    genTreeAna_p->Branch("genSubJtRawPt", genSubJtRawPt_, "genSubJtRawPt[5][nSubjet]/F");
    genTreeAna_p->Branch("genSubJtRawPhi", genSubJtRawPhi_, "genSubJtRawPhi[5][nSubjet]/F");
    genTreeAna_p->Branch("genSubJtRawEta", genSubJtRawEta_, "genSubJtRawEta[5][nSubjet]/F");

    genTreeAna_p->Branch("genJtSKPt", genJtSKPt_, "genJtSKPt[5]/F");
    genTreeAna_p->Branch("genJtSKPhi", genJtSKPhi_, "genJtSKPhi[5]/F");
    genTreeAna_p->Branch("genJtSKEta", genJtSKEta_, "genJtSKEta[5]/F");
    genTreeAna_p->Branch("genJtSKPTD", genJtSKPTD_, "genJtSKPTD[5]/F");
    genTreeAna_p->Branch("genJtSKR2", genJtSKR2_, "genJtSKR2[5]/F");
    genTreeAna_p->Branch("genJtSKSigma", genJtSKSigma_, "genJtSKSigma[5][nSigma]/F");
    genTreeAna_p->Branch("genJtSKRefPart", genJtSKRefPart_, "genJtSKRefPart[5]/I");
    genTreeAna_p->Branch("genJtSKFFMUnsub", genJtSKFFMUnsub_, "genJtSKFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genJtSKFFMUnsub", genJtSKFFMUnsub_, "genJtSKFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genJtSKFFMUnsub", genJtSKFFMUnsub_, "genJtSKFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genSKTau", genSKTau_, "genSKTau[5][nTau][nBeta]/F");
    genTreeAna_p->Branch("genSubJtSKPt", genSubJtSKPt_, "genSubJtSKPt[5][nSubjet]/F");
    genTreeAna_p->Branch("genSubJtSKPhi", genSubJtSKPhi_, "genSubJtSKPhi[5][nSubjet]/F");
    genTreeAna_p->Branch("genSubJtSKEta", genSubJtSKEta_, "genSubJtSKEta[5][nSubjet]/F");

    genTreeAna_p->Branch("genJtSUBEPt", genJtSUBEPt_, "genJtSUBEPt[5]/F");
    genTreeAna_p->Branch("genJtSUBEPhi", genJtSUBEPhi_, "genJtSUBEPhi[5]/F");
    genTreeAna_p->Branch("genJtSUBEEta", genJtSUBEEta_, "genJtSUBEEta[5]/F");
    genTreeAna_p->Branch("genJtSUBEPTD", genJtSUBEPTD_, "genJtSUBEPTD[5]/F");
    genTreeAna_p->Branch("genJtSUBER2", genJtSUBER2_, "genJtSUBER2[5]/F");
    genTreeAna_p->Branch("genJtSUBESigma", genJtSUBESigma_, "genJtSUBESigma[5][nSigma]/F");
    genTreeAna_p->Branch("genJtSUBERefPart", genJtSUBERefPart_, "genJtSUBERefPart[5]/I");
    genTreeAna_p->Branch("genJtSUBEFFMUnsub", genJtSUBEFFMUnsub_, "genJtSUBEFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genJtSUBEFFMUnsub", genJtSUBEFFMUnsub_, "genJtSUBEFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genJtSUBEFFMUnsub", genJtSUBEFFMUnsub_, "genJtSUBEFFMUnsub[5][nFFM]/F");
    genTreeAna_p->Branch("genSUBETau", genSUBETau_, "genSUBETau[5][nTau][nBeta]/F");
    genTreeAna_p->Branch("genSubJtSUBEPt", genSubJtSUBEPt_, "genSubJtSUBEPt[5][nSubjet]/F");
    genTreeAna_p->Branch("genSubJtSUBEPhi", genSubJtSUBEPhi_, "genSubJtSUBEPhi[5][nSubjet]/F");
    genTreeAna_p->Branch("genSubJtSUBEEta", genSubJtSUBEEta_, "genSubJtSUBEEta[5][nSubjet]/F");
  }

  //Jet TreeAna Branches

  jetTreeAna_p->Branch("run", &run_, "run/I");
  jetTreeAna_p->Branch("evt", &evt_, "evt/I");
  jetTreeAna_p->Branch("lumi", &lumi_, "lumi/I");

  if(hi){
    jetTreeAna_p->Branch("hiBin", &hiBin_, "hiBin/I");
    if(montecarlo) jetTreeAna_p->Branch("b", &b_, "b/F");
  }
   
  if(montecarlo){
    jetTreeAna_p->Branch("pthat", &pthat_, "pthat/F");
    jetTreeAna_p->Branch("pthatWeight", &pthatWeight_, "pthatWeight/F");
  }

  if(hi){
    jetTreeAna_p->Branch("hiEvtPlane", &hiEvtPlane_, "hiEvtPlane/F");
    jetTreeAna_p->Branch("psin", &psin_, "psin/F");
  }    

  jetTreeAna_p->Branch("eventSet", eventSet_, "eventSet[5]/O");

  jetTreeAna_p->Branch("AlgJtPt", AlgJtPt_, "AlgJtPt[5][5]/F");
  jetTreeAna_p->Branch("AlgJtPhi", AlgJtPhi_, "AlgJtPhi[5][5]/F");
  jetTreeAna_p->Branch("AlgJtEta", AlgJtEta_, "AlgJtEta[5][5]/F");
  jetTreeAna_p->Branch("AlgJtRawPt", AlgJtRawPt_, "AlgJtRawPt[5][5]/F");

  jetTreeAna_p->Branch("AlgJtDelPhi", AlgJtDelPhi_, "AlgJtDelPhi[5]/F");
  jetTreeAna_p->Branch("AlgJtAsymm", AlgJtAsymm_, "AlgJtAsymm[5]/F");

  if(montecarlo){
    jetTreeAna_p->Branch("AlgRefPartFlav", AlgRefPartFlav_, "AlgRefPartFlav[5][5]/I");
    jetTreeAna_p->Branch("AlgRefPt", AlgRefPt_, "AlgRefPt[5][5]/F");
    jetTreeAna_p->Branch("AlgRefPhi", AlgRefPhi_, "AlgRefPhi[5][5]/F");
    jetTreeAna_p->Branch("AlgRefEta", AlgRefEta_, "AlgRefEta[5][5]/F");
  }    
}


void GetAnaBranches(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);
  //Rechit TreeAna Branches

  if(!isGen){
    rechitTreeAna_p->SetBranchAddress("rechitSKPtCut", &rechitSKPtCut_);

    rechitTreeAna_p->SetBranchAddress("rechitJtRawPt", rechitJtRawPt_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawPhi", rechitJtRawPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawEta", rechitJtRawEta_);
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
    
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPt", rechitJtVsPt_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPhi", rechitJtVsPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsEta", rechitJtVsEta_);
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

    pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawPhi", pfJtRawPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawEta", pfJtRawEta_);
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
    
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPt", pfJtVsPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPhi", pfJtVsPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsEta", pfJtVsEta_);
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
    
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPt", pfJtSKPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPhi", pfJtSKPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKEta", pfJtSKEta_);
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

    trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPt_);
    trkTreeAna_p->SetBranchAddress("trkJtRawPhi", trkJtRawPhi_);
    trkTreeAna_p->SetBranchAddress("trkJtRawEta", trkJtRawEta_);
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
    
    trkTreeAna_p->SetBranchAddress("trkJtSKPt", trkJtSKPt_);
    trkTreeAna_p->SetBranchAddress("trkJtSKPhi", trkJtSKPhi_);
    trkTreeAna_p->SetBranchAddress("trkJtSKEta", trkJtSKEta_);
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

    genTreeAna_p->SetBranchAddress("genJtRawPt", genJtRawPt_);
    genTreeAna_p->SetBranchAddress("genJtRawPhi", genJtRawPhi_);
    genTreeAna_p->SetBranchAddress("genJtRawEta", genJtRawEta_);
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

    genTreeAna_p->SetBranchAddress("genJtSKPt", genJtSKPt_);
    genTreeAna_p->SetBranchAddress("genJtSKPhi", genJtSKPhi_);
    genTreeAna_p->SetBranchAddress("genJtSKEta", genJtSKEta_);
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

    genTreeAna_p->SetBranchAddress("genJtSUBEPt", genJtSUBEPt_);
    genTreeAna_p->SetBranchAddress("genJtSUBEPhi", genJtSUBEPhi_);
    genTreeAna_p->SetBranchAddress("genJtSUBEEta", genJtSUBEEta_);
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
}


void CleanupFastJetAnaSkim()
{
  if(rechitTreeAna_p != 0) delete rechitTreeAna_p;
  if(pfcandTreeAna_p != 0) delete pfcandTreeAna_p;
  if(trkTreeAna_p != 0) delete trkTreeAna_p;
  if(genTreeAna_p != 0) delete genTreeAna_p;
  if(jetTreeAna_p != 0) delete jetTreeAna_p;
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
}


void InitJtVar(){
  rechitSKPtCut_ = -10;
  pfSKPtCut_ = -10;
  trkSKPtCut_ = -10;
  genSKPtCut_ = -10;

  for(Int_t iter = 0; iter < 5; iter++){
    rechitJtRawPt_[iter] = -10;
    rechitJtRawPhi_[iter] = -10;
    rechitJtRawEta_[iter] = -10;
    rechitJtRawPTD_[iter] = -10;
    rechitJtRawR2_[iter] = -10;
    rechitJtRawRefPart_[iter] = -999;

    rechitJtVsPt_[iter] = -10;
    rechitJtVsPhi_[iter] = -10;
    rechitJtVsEta_[iter] = -10;
    rechitJtVsPTD_[iter] = -10;
    rechitJtVsR2_[iter] = -10;
    rechitJtVsRefPart_[iter] = -999;

    pfJtRawPt_[iter] = -10;
    pfJtRawPhi_[iter] = -10;
    pfJtRawEta_[iter] = -10;
    pfJtRawPTD_[iter] = -10;
    pfJtRawR2_[iter] = -10;
    pfJtRawRefPart_[iter] = -999;

    pfJtVsPt_[iter] = -10;
    pfJtVsPhi_[iter] = -10;
    pfJtVsEta_[iter] = -10;
    pfJtVsPTD_[iter] = -10;
    pfJtVsR2_[iter] = -10;
    pfJtVsRefPart_[iter] = -999;

    pfJtSKPt_[iter] = -10;
    pfJtSKPhi_[iter] = -10;
    pfJtSKEta_[iter] = -10;
    pfJtSKPTD_[iter] = -10;
    pfJtSKR2_[iter] = -10;
    pfJtSKRefPart_[iter] = -999;

    trkJtRawPt_[iter] = -10;
    trkJtRawPhi_[iter] = -10;
    trkJtRawEta_[iter] = -10;
    trkJtRawPTD_[iter] = -10;
    trkJtRawR2_[iter] = -10;
    trkJtRawRefPart_[iter] = -999;

    trkJtSKPt_[iter] = -10;
    trkJtSKPhi_[iter] = -10;
    trkJtSKEta_[iter] = -10;
    trkJtSKPTD_[iter] = -10;
    trkJtSKR2_[iter] = -10;
    trkJtSKRefPart_[iter] = -999;

    genJtRawPt_[iter] = -10;
    genJtRawPhi_[iter] = -10;
    genJtRawEta_[iter] = -10;
    genJtRawPTD_[iter] = -10;
    genJtRawR2_[iter] = -10;
    genJtRawRefPart_[iter] = -999;

    genJtSKPt_[iter] = -10;
    genJtSKPhi_[iter] = -10;
    genJtSKEta_[iter] = -10;
    genJtSKPTD_[iter] = -10;
    genJtSKR2_[iter] = -10;
    genJtSKRefPart_[iter] = -999;

    genJtSUBEPt_[iter] = -10;
    genJtSUBEPhi_[iter] = -10;
    genJtSUBEEta_[iter] = -10;
    genJtSUBEPTD_[iter] = -10;
    genJtSUBER2_[iter] = -10;
    genJtSUBERefPart_[iter] = -999;

    for(Int_t iter2 = 0; iter2 < nSubjet; iter2++){
      rechitSubJtRawPt_[iter][iter2] = -10;
      rechitSubJtRawPhi_[iter][iter2] = -10;
      rechitSubJtRawEta_[iter][iter2] = -10;

      rechitSubJtVsPt_[iter][iter2] = -10;
      rechitSubJtVsPhi_[iter][iter2] = -10;
      rechitSubJtVsEta_[iter][iter2] = -10;

      pfSubJtRawPt_[iter][iter2] = -10;
      pfSubJtRawPhi_[iter][iter2] = -10;
      pfSubJtRawEta_[iter][iter2] = -10;

      pfSubJtVsPt_[iter][iter2] = -10;
      pfSubJtVsPhi_[iter][iter2] = -10;
      pfSubJtVsEta_[iter][iter2] = -10;

      pfSubJtSKPt_[iter][iter2] = -10;
      pfSubJtSKPhi_[iter][iter2] = -10;
      pfSubJtSKEta_[iter][iter2] = -10;

      trkSubJtRawPt_[iter][iter2] = -10;
      trkSubJtRawPhi_[iter][iter2] = -10;
      trkSubJtRawEta_[iter][iter2] = -10;

      trkSubJtSKPt_[iter][iter2] = -10;
      trkSubJtSKPhi_[iter][iter2] = -10;
      trkSubJtSKEta_[iter][iter2] = -10;

      genSubJtRawPt_[iter][iter2] = -10;
      genSubJtRawPhi_[iter][iter2] = -10;
      genSubJtRawEta_[iter][iter2] = -10;

      genSubJtSKPt_[iter][iter2] = -10;
      genSubJtSKPhi_[iter][iter2] = -10;
      genSubJtSKEta_[iter][iter2] = -10;

      genSubJtSUBEPt_[iter][iter2] = -10;
      genSubJtSUBEPhi_[iter][iter2] = -10;
      genSubJtSUBEEta_[iter][iter2] = -10;
    }

    for(Int_t iter2 = 0; iter2 < nSigma; iter2++){
      rechitJtRawSigma_[iter][iter2] = -10;
      rechitJtVsSigma_[iter][iter2] = -10;
      pfJtRawSigma_[iter][iter2] = -10;
      pfJtVsSigma_[iter][iter2] = -10;
      pfJtSKSigma_[iter][iter2] = -10;
      trkJtRawSigma_[iter][iter2] = -10;
      trkJtSKSigma_[iter][iter2] = -10;
      genJtRawSigma_[iter][iter2] = -10;
      genJtSKSigma_[iter][iter2] = -10;
      genJtSUBESigma_[iter][iter2] = -10;
    }

    for(Int_t iter2 = 0; iter2 < nFFM; iter2++){

    }

    for(Int_t iter2 = 0; iter2 < nTau; iter2++){
      for(Int_t iter3 = 0; iter3 < nBeta; iter3++){
	rechitRawTau_[iter][iter2][iter3] = -10;
	rechitVsTau_[iter][iter2][iter3] = -10;
	pfRawTau_[iter][iter2][iter3] = -10;
	pfVsTau_[iter][iter2][iter3] = -10;
	pfSKTau_[iter][iter2][iter3] = -10;
	trkRawTau_[iter][iter2][iter3] = -10;
	trkSKTau_[iter][iter2][iter3] = -10;
	genRawTau_[iter][iter2][iter3] = -10;
	genSKTau_[iter][iter2][iter3] = -10;
	genSUBETau_[iter][iter2][iter3] = -10;
      }
    }

  }
}


#endif
