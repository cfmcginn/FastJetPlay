//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// FastJet AnaSkim Class (MC)                                                    
//                                                                              
//=============================================  
#ifndef cfmFastJetAnaSkim_h
#define cfmFastJetAnaSkim_h

#include "/net/hisrv0001/home/cfmcginn/FastJet/CMSSW_5_3_12_patch3/src/FastJetIniSkim/cfmFastJetIniSkim.h"

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

TTree* rechitTreeAna_p = 0;
TTree* pfcandTreeAna_p = 0;
TTree* trkTreeAna_p = 0;
TTree* genTreeAna_p = 0;
TTree* jetTreeAna_p = 0;

//rechit TreeAna Variables, [alg][tau][beta]

Float_t rechitJtRawPt_[5];
Float_t rechitJtRawPhi_[5];
Float_t rechitJtRawEta_[5];
Float_t rechitJtRawPTD_[5];
Float_t rechitRawTau_[5][3][3];
Float_t rechitSubJtRawPt_[5];
Float_t rechitSubJtRawPhi_[5];
Float_t rechitSubJtRawEta_[5];

Float_t rechitJtVsPt_[5];
Float_t rechitJtVsPhi_[5];
Float_t rechitJtVsEta_[5];
Float_t rechitJtVsPTD_[5];
Float_t rechitVsTau_[5][3][3];
Float_t rechitSubJtVsPt_[5];
Float_t rechitSubJtVsPhi_[5];
Float_t rechitSubJtVsEta_[5];

//pfcand TreeAna Variables

Float_t pfJtRawPt_[5];
Float_t pfJtRawPhi_[5];
Float_t pfJtRawEta_[5];
Float_t pfJtRawPTD_[5];
Float_t pfRawTau_[5][3][3];
Float_t pfSubJtRawPt_[5];
Float_t pfSubJtRawPhi_[5];
Float_t pfSubJtRawEta_[5];

Float_t pfJtVsPt_[5];
Float_t pfJtVsPhi_[5];
Float_t pfJtVsEta_[5];
Float_t pfJtVsPTD_[5];
Float_t pfVsTau_[5][3][3];
Float_t pfSubJtVsPt_[5];
Float_t pfSubJtVsPhi_[5];
Float_t pfSubJtVsEta_[5];

Float_t pfJtSKPt_[5];
Float_t pfJtSKPhi_[5];
Float_t pfJtSKEta_[5];
Float_t pfJtSKPTD_[5];
Float_t pfSKTau_[5][3][3];
Float_t pfSubJtSKPt_[5];
Float_t pfSubJtSKPhi_[5];
Float_t pfSubJtSKEta_[5];


//track TreeAna Variables

Float_t trkJtRawPt_[5];
Float_t trkJtRawPhi_[5];
Float_t trkJtRawEta_[5];
Float_t trkJtRawPTD_[5];
Float_t trkRawTau_[5][3][3];
Float_t trkSubJtRawPt_[5];
Float_t trkSubJtRawPhi_[5];
Float_t trkSubJtRawEta_[5];

Float_t trkJtSKPt_[5];
Float_t trkJtSKPhi_[5];
Float_t trkJtSKEta_[5];
Float_t trkJtSKPTD_[5];
Float_t trkSKTau_[5][3][3];
Float_t trkSubJtSKPt_[5];
Float_t trkSubJtSKPhi_[5];
Float_t trkSubJtSKEta_[5];

//Gen TreeAna Variables

Float_t genJtRawPt_[5];
Float_t genJtRawPhi_[5];
Float_t genJtRawEta_[5];
Float_t genJtRawPTD_[5];
Float_t genRawTau_[5][3][3];
Float_t genSubJtRawPt_[5];
Float_t genSubJtRawPhi_[5];
Float_t genSubJtRawEta_[5];

Float_t genJtSKPt_[5];
Float_t genJtSKPhi_[5];
Float_t genJtSKEta_[5];
Float_t genJtSKPTD_[5];
Float_t genSKTau_[5][3][3];
Float_t genSubJtSKPt_[5];
Float_t genSubJtSKPhi_[5];
Float_t genSubJtSKEta_[5];

//Jet TreeAna Variables

Int_t run_;
Int_t evt_;
Int_t lumi_;
Int_t hiBin_;

Float_t pthat_;

Float_t hiEvtPlane_;
Float_t psin_;

Bool_t eventSet_[5];

Float_t AlgJtPt_[5][5];
Float_t AlgJtPhi_[5][5];
Float_t AlgJtEta_[5][5];
Float_t AlgJtRawPt_[5][5];

Float_t AlgJtDelPhi_[5];
Float_t AlgJtAsymm_[5];

Float_t AlgRefPartFlav_[5][5];
Float_t AlgRefPt_[5][5];
Float_t AlgRefPhi_[5][5];
Float_t AlgRefEta_[5][5];


void SetAnaBranches(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);
  //Rechit TreeAna Branches

  if(!isGen){
    rechitTreeAna_p->Branch("rechitJtRawPt", rechitJtRawPt_, "rechitJtRawPt[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawPhi", rechitJtRawPhi_, "rechitJtRawPhi[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawEta", rechitJtRawEta_, "rechitJtRawEta[5]/F");
    rechitTreeAna_p->Branch("rechitJtRawPTD", rechitJtRawPTD_, "rechitJtRawPTD[5]/F");
    rechitTreeAna_p->Branch("rechitRawTau", rechitRawTau_, "rechitRawTau[5][3][3]/F");
    rechitTreeAna_p->Branch("rechitSubJtRawPt", rechitSubJtRawPt_, "rechitSubJtRawPt[5]/F");
    rechitTreeAna_p->Branch("rechitSubJtRawPhi", rechitSubJtRawPhi_, "rechitSubJtRawPhi[5]/F");
    rechitTreeAna_p->Branch("rechitSubJtRawEta", rechitSubJtRawEta_, "rechitSubJtRawEta[5]/F");
    
    rechitTreeAna_p->Branch("rechitJtVsPt", rechitJtVsPt_, "rechitJtVsPt[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsPhi", rechitJtVsPhi_, "rechitJtVsPhi[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsEta", rechitJtVsEta_, "rechitJtVsEta[5]/F");
    rechitTreeAna_p->Branch("rechitJtVsPTD", rechitJtVsPTD_, "rechitJtVsPTD[5]/F");
    rechitTreeAna_p->Branch("rechitVsTau", rechitVsTau_, "rechitVsTau[5][3][3]/F");
    rechitTreeAna_p->Branch("rechitSubJtVsPt", rechitSubJtVsPt_, "rechitSubJtVsPt[5]/F");
    rechitTreeAna_p->Branch("rechitSubJtVsPhi", rechitSubJtVsPhi_, "rechitSubJtVsPhi[5]/F");
    rechitTreeAna_p->Branch("rechitSubJtVsEta", rechitSubJtVsEta_, "rechitSubJtVsEta[5]/F");
    
    //PF TreeAna Branches
    
    pfcandTreeAna_p->Branch("pfJtRawPt", pfJtRawPt_, "pfJtRawPt[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawPhi", pfJtRawPhi_, "pfJtRawPhi[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawEta", pfJtRawEta_, "pfJtRawEta[5]/F");
    pfcandTreeAna_p->Branch("pfJtRawPTD", pfJtRawPTD_, "pfJtRawPTD[5]/F");
    pfcandTreeAna_p->Branch("pfRawTau", pfRawTau_, "pfRawTau[5][3][3]/F");
    pfcandTreeAna_p->Branch("pfSubJtRawPt", pfSubJtRawPt_, "pfSubJtRawPt[5]/F");
    pfcandTreeAna_p->Branch("pfSubJtRawPhi", pfSubJtRawPhi_, "pfSubJtRawPhi[5]/F");
    pfcandTreeAna_p->Branch("pfSubJtRawEta", pfSubJtRawEta_, "pfSubJtRawEta[5]/F");
    
    pfcandTreeAna_p->Branch("pfJtVsPt", pfJtVsPt_, "pfJtVsPt[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsPhi", pfJtVsPhi_, "pfJtVsPhi[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsEta", pfJtVsEta_, "pfJtVsEta[5]/F");
    pfcandTreeAna_p->Branch("pfJtVsPTD", pfJtVsPTD_, "pfJtVsPTD[5]/F");
    pfcandTreeAna_p->Branch("pfVsTau", pfVsTau_, "pfVsTau[5][3][3]/F");
    pfcandTreeAna_p->Branch("pfSubJtVsPt", pfSubJtVsPt_, "pfSubJtVsPt[5]/F");
    pfcandTreeAna_p->Branch("pfSubJtVsPhi", pfSubJtVsPhi_, "pfSubJtVsPhi[5]/F");
    pfcandTreeAna_p->Branch("pfSubJtVsEta", pfSubJtVsEta_, "pfSubJtVsEta[5]/F");
    
    pfcandTreeAna_p->Branch("pfJtSKPt", pfJtSKPt_, "pfJtSKPt[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKPhi", pfJtSKPhi_, "pfJtSKPhi[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKEta", pfJtSKEta_, "pfJtSKEta[5]/F");
    pfcandTreeAna_p->Branch("pfJtSKPTD", pfJtSKPTD_, "pfJtSKPTD[5]/F");
    pfcandTreeAna_p->Branch("pfSKTau", pfSKTau_, "pfSKTau[5][3][3]/F");
    pfcandTreeAna_p->Branch("pfSubJtSKPt", pfSubJtSKPt_, "pfSubJtSKPt[5]/F");
    pfcandTreeAna_p->Branch("pfSubJtSKPhi", pfSubJtSKPhi_, "pfSubJtSKPhi[5]/F");
    pfcandTreeAna_p->Branch("pfSubJtSKEta", pfSubJtSKEta_, "pfSubJtSKEta[5]/F");
    
    //Trk TreeAna Branches
    
    trkTreeAna_p->Branch("trkJtRawPt", trkJtRawPt_, "trkJtRawPt[5]/F");
    trkTreeAna_p->Branch("trkJtRawPhi", trkJtRawPhi_, "trkJtRawPhi[5]/F");
    trkTreeAna_p->Branch("trkJtRawEta", trkJtRawEta_, "trkJtRawEta[5]/F");
    trkTreeAna_p->Branch("trkJtRawPTD", trkJtRawPTD_, "trkJtRawPTD[5]/F");
    trkTreeAna_p->Branch("trkRawTau", trkRawTau_, "trkRawTau[5][3][3]/F");
    trkTreeAna_p->Branch("trkSubJtRawPt", trkSubJtRawPt_, "trkSubJtRawPt[5]/F");
    trkTreeAna_p->Branch("trkSubJtRawPhi", trkSubJtRawPhi_, "trkSubJtRawPhi[5]/F");
    trkTreeAna_p->Branch("trkSubJtRawEta", trkSubJtRawEta_, "trkSubJtRawEta[5]/F");
    
    trkTreeAna_p->Branch("trkJtSKPt", trkJtSKPt_, "trkJtSKPt[5]/F");
    trkTreeAna_p->Branch("trkJtSKPhi", trkJtSKPhi_, "trkJtSKPhi[5]/F");
    trkTreeAna_p->Branch("trkJtSKEta", trkJtSKEta_, "trkJtSKEta[5]/F");
    trkTreeAna_p->Branch("trkJtSKPTD", trkJtSKPTD_, "trkJtSKPTD[5]/F");
    trkTreeAna_p->Branch("trkSKTau", trkSKTau_, "trkSKTau[5][3][3]/F");
    trkTreeAna_p->Branch("trkSubJtSKPt", trkSubJtSKPt_, "trkSubJtSKPt[5]/F");
    trkTreeAna_p->Branch("trkSubJtSKPhi", trkSubJtSKPhi_, "trkSubJtSKPhi[5]/F");
    trkTreeAna_p->Branch("trkSubJtSKEta", trkSubJtSKEta_, "trkSubJtSKEta[5]/F");
  }    

  //Gen TreeAna Branches
  if(montecarlo){
    genTreeAna_p->Branch("genJtRawPt", genJtRawPt_, "genJtRawPt[5]/F");
    genTreeAna_p->Branch("genJtRawPhi", genJtRawPhi_, "genJtRawPhi[5]/F");
    genTreeAna_p->Branch("genJtRawEta", genJtRawEta_, "genJtRawEta[5]/F");
    genTreeAna_p->Branch("genJtRawPTD", genJtRawPTD_, "genJtRawPTD[5]/F");
    genTreeAna_p->Branch("genRawTau", genRawTau_, "genRawTau[5][3][3]/F");
    genTreeAna_p->Branch("genSubJtRawPt", genSubJtRawPt_, "genSubJtRawPt[5]/F");
    genTreeAna_p->Branch("genSubJtRawPhi", genSubJtRawPhi_, "genSubJtRawPhi[5]/F");
    genTreeAna_p->Branch("genSubJtRawEta", genSubJtRawEta_, "genSubJtRawEta[5]/F");

    genTreeAna_p->Branch("genJtSKPt", genJtSKPt_, "genJtSKPt[5]/F");
    genTreeAna_p->Branch("genJtSKPhi", genJtSKPhi_, "genJtSKPhi[5]/F");
    genTreeAna_p->Branch("genJtSKEta", genJtSKEta_, "genJtSKEta[5]/F");
    genTreeAna_p->Branch("genJtSKPTD", genJtSKPTD_, "genJtSKPTD[5]/F");
    genTreeAna_p->Branch("genSKTau", genSKTau_, "genSKTau[5][3][3]/F");
    genTreeAna_p->Branch("genSubJtSKPt", genSubJtSKPt_, "genSubJtSKPt[5]/F");
    genTreeAna_p->Branch("genSubJtSKPhi", genSubJtSKPhi_, "genSubJtSKPhi[5]/F");
    genTreeAna_p->Branch("genSubJtSKEta", genSubJtSKEta_, "genSubJtSKEta[5]/F");
  }

  //Jet TreeAna Branches

  jetTreeAna_p->Branch("run", &run_, "run/I");
  jetTreeAna_p->Branch("evt", &evt_, "evt/I");
  jetTreeAna_p->Branch("lumi", &lumi_, "lumi/I");

  if(hi)
    jetTreeAna_p->Branch("hiBin", &hiBin_, "hiBin/I");

   
  if(montecarlo)
    jetTreeAna_p->Branch("pthat", &pthat_, "pthat/F");

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
    jetTreeAna_p->Branch("AlgRefPartFlav", AlgRefPartFlav_, "AlgRefPartFlav[5][5]/F");
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
    rechitTreeAna_p->SetBranchAddress("rechitJtRawPt", rechitJtRawPt_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawPhi", rechitJtRawPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawEta", rechitJtRawEta_);
    rechitTreeAna_p->SetBranchAddress("rechitJtRawPTD", rechitJtRawPTD_);
    rechitTreeAna_p->SetBranchAddress("rechitRawTau", rechitRawTau_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtRawPt", rechitSubJtRawPt_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtRawPhi", rechitSubJtRawPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtRawEta", rechitSubJtRawEta_);
    
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPt", rechitJtVsPt_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPhi", rechitJtVsPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsEta", rechitJtVsEta_);
    rechitTreeAna_p->SetBranchAddress("rechitJtVsPTD", rechitJtVsPTD_);
    rechitTreeAna_p->SetBranchAddress("rechitVsTau", rechitVsTau_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtVsPt", rechitSubJtVsPt_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtVsPhi", rechitSubJtVsPhi_);
    rechitTreeAna_p->SetBranchAddress("rechitSubJtVsEta", rechitSubJtVsEta_);
    
    //PF TreeAna Branches
    
    pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawPhi", pfJtRawPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawEta", pfJtRawEta_);
    pfcandTreeAna_p->SetBranchAddress("pfJtRawPTD", pfJtRawPTD_);
    pfcandTreeAna_p->SetBranchAddress("pfRawTau", pfRawTau_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtRawPt", pfSubJtRawPt_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtRawPhi", pfSubJtRawPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtRawEta", pfSubJtRawEta_);
    
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPt", pfJtVsPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPhi", pfJtVsPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsEta", pfJtVsEta_);
    pfcandTreeAna_p->SetBranchAddress("pfJtVsPTD", pfJtVsPTD_);
    pfcandTreeAna_p->SetBranchAddress("pfVsTau", pfVsTau_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtVsPt", pfSubJtVsPt_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtVsPhi", pfSubJtVsPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtVsEta", pfSubJtVsEta_);
    
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPt", pfJtSKPt_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPhi", pfJtSKPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKEta", pfJtSKEta_);
    pfcandTreeAna_p->SetBranchAddress("pfJtSKPTD", pfJtSKPTD_);
    pfcandTreeAna_p->SetBranchAddress("pfSKTau", pfSKTau_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtSKPt", pfSubJtSKPt_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtSKPhi", pfSubJtSKPhi_);
    pfcandTreeAna_p->SetBranchAddress("pfSubJtSKEta", pfSubJtSKEta_);
    
    //Trk TreeAna Branches
    
    trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPt_);
    trkTreeAna_p->SetBranchAddress("trkJtRawPhi", trkJtRawPhi_);
    trkTreeAna_p->SetBranchAddress("trkJtRawEta", trkJtRawEta_);
    trkTreeAna_p->SetBranchAddress("trkJtRawPTD", trkJtRawPTD_);
    trkTreeAna_p->SetBranchAddress("trkRawTau", trkRawTau_);
    trkTreeAna_p->SetBranchAddress("trkSubJtRawPt", trkSubJtRawPt_);
    trkTreeAna_p->SetBranchAddress("trkSubJtRawPhi", trkSubJtRawPhi_);
    trkTreeAna_p->SetBranchAddress("trkSubJtRawEta", trkSubJtRawEta_);
    
    trkTreeAna_p->SetBranchAddress("trkJtSKPt", trkJtSKPt_);
    trkTreeAna_p->SetBranchAddress("trkJtSKPhi", trkJtSKPhi_);
    trkTreeAna_p->SetBranchAddress("trkJtSKEta", trkJtSKEta_);
    trkTreeAna_p->SetBranchAddress("trkJtSKPTD", trkJtSKPTD_);
    trkTreeAna_p->SetBranchAddress("trkSKTau", trkSKTau_);
    trkTreeAna_p->SetBranchAddress("trkSubJtSKPt", trkSubJtSKPt_);
    trkTreeAna_p->SetBranchAddress("trkSubJtSKPhi", trkSubJtSKPhi_);
    trkTreeAna_p->SetBranchAddress("trkSubJtSKEta", trkSubJtSKEta_);
  }
  //Gen TreeAna Branches

  if(montecarlo){
    genTreeAna_p->SetBranchAddress("genJtRawPt", genJtRawPt_);
    genTreeAna_p->SetBranchAddress("genJtRawPhi", genJtRawPhi_);
    genTreeAna_p->SetBranchAddress("genJtRawEta", genJtRawEta_);
    genTreeAna_p->SetBranchAddress("genJtRawPTD", genJtRawPTD_);
    genTreeAna_p->SetBranchAddress("genRawTau", genRawTau_);
    genTreeAna_p->SetBranchAddress("genSubJtRawPt", genSubJtRawPt_);
    genTreeAna_p->SetBranchAddress("genSubJtRawPhi", genSubJtRawPhi_);
    genTreeAna_p->SetBranchAddress("genSubJtRawEta", genSubJtRawEta_);

    genTreeAna_p->SetBranchAddress("genJtSKPt", genJtSKPt_);
    genTreeAna_p->SetBranchAddress("genJtSKPhi", genJtSKPhi_);
    genTreeAna_p->SetBranchAddress("genJtSKEta", genJtSKEta_);
    genTreeAna_p->SetBranchAddress("genJtSKPTD", genJtSKPTD_);
    genTreeAna_p->SetBranchAddress("genSKTau", genSKTau_);
    genTreeAna_p->SetBranchAddress("genSubJtSKPt", genSubJtSKPt_);
    genTreeAna_p->SetBranchAddress("genSubJtSKPhi", genSubJtSKPhi_);
    genTreeAna_p->SetBranchAddress("genSubJtSKEta", genSubJtSKEta_);
  }
  //Jet TreeAna Branches

  jetTreeAna_p->SetBranchAddress("run", &run_);
  jetTreeAna_p->SetBranchAddress("evt", &evt_);
  jetTreeAna_p->SetBranchAddress("lumi", &lumi_);

  if(hi)
    jetTreeAna_p->SetBranchAddress("hiBin", &hiBin_);

  if(montecarlo)
    jetTreeAna_p->SetBranchAddress("pthat", &pthat_);

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
  if(isMonteCarlo(sType)) genTreeAna_p = (TTree*)iniSkimFile_p->Get("genTreeAna");
  jetTreeAna_p = (TTree*)iniSkimFile_p->Get("jetTreeAna");

  GetAnaBranches(sType);
}


void InitJtVar(){
  for(Int_t iter = 0; iter < 5; iter++){
    rechitJtRawPt_[iter] = -10;
    rechitJtRawPhi_[iter] = -10;
    rechitJtRawEta_[iter] = -10;
    rechitJtRawPTD_[iter] = -10;
    rechitSubJtRawPt_[iter] = -10;
    rechitSubJtRawPhi_[iter] = -10;
    rechitSubJtRawEta_[iter] = -10;

    rechitJtVsPt_[iter] = -10;
    rechitJtVsPhi_[iter] = -10;
    rechitJtVsEta_[iter] = -10;
    rechitJtVsPTD_[iter] = -10;
    rechitSubJtVsPt_[iter] = -10;
    rechitSubJtVsPhi_[iter] = -10;
    rechitSubJtVsEta_[iter] = -10;

    pfJtRawPt_[iter] = -10;
    pfJtRawPhi_[iter] = -10;
    pfJtRawEta_[iter] = -10;
    pfJtRawPTD_[iter] = -10;
    pfSubJtRawPt_[iter] = -10;
    pfSubJtRawPhi_[iter] = -10;
    pfSubJtRawEta_[iter] = -10;

    pfJtVsPt_[iter] = -10;
    pfJtVsPhi_[iter] = -10;
    pfJtVsEta_[iter] = -10;
    pfJtVsPTD_[iter] = -10;
    pfSubJtVsPt_[iter] = -10;
    pfSubJtVsPhi_[iter] = -10;
    pfSubJtVsEta_[iter] = -10;

    pfJtSKPt_[iter] = -10;
    pfJtSKPhi_[iter] = -10;
    pfJtSKEta_[iter] = -10;
    pfJtSKPTD_[iter] = -10;
    pfSubJtSKPt_[iter] = -10;
    pfSubJtSKPhi_[iter] = -10;
    pfSubJtSKEta_[iter] = -10;

    trkJtRawPt_[iter] = -10;
    trkJtRawPhi_[iter] = -10;
    trkJtRawEta_[iter] = -10;
    trkJtRawPTD_[iter] = -10;
    trkSubJtRawPt_[iter] = -10;
    trkSubJtRawPhi_[iter] = -10;
    trkSubJtRawEta_[iter] = -10;

    trkJtSKPt_[iter] = -10;
    trkJtSKPhi_[iter] = -10;
    trkJtSKEta_[iter] = -10;
    trkJtSKPTD_[iter] = -10;
    trkSubJtSKPt_[iter] = -10;
    trkSubJtSKPhi_[iter] = -10;
    trkSubJtSKEta_[iter] = -10;

    genJtRawPt_[iter] = -10;
    genJtRawPhi_[iter] = -10;
    genJtRawEta_[iter] = -10;
    genJtRawPTD_[iter] = -10;
    genSubJtRawPt_[iter] = -10;
    genSubJtRawPhi_[iter] = -10;
    genSubJtRawEta_[iter] = -10;

    genJtSKPt_[iter] = -10;
    genJtSKPhi_[iter] = -10;
    genJtSKEta_[iter] = -10;
    genJtSKPTD_[iter] = -10;
    genSubJtSKPt_[iter] = -10;
    genSubJtSKPhi_[iter] = -10;
    genSubJtSKEta_[iter] = -10;

    for(Int_t iter2 = 0; iter2 < 3; iter2++){
      for(Int_t iter3 = 0; iter3 < 3; iter3++){
	rechitRawTau_[iter][iter2][iter3] = -10;
	rechitVsTau_[iter][iter2][iter3] = -10;
	pfRawTau_[iter][iter2][iter3] = -10;
	pfVsTau_[iter][iter2][iter3] = -10;
	pfSKTau_[iter][iter2][iter3] = -10;
	trkRawTau_[iter][iter2][iter3] = -10;
	trkSKTau_[iter][iter2][iter3] = -10;
	genRawTau_[iter][iter2][iter3] = -10;
	genSKTau_[iter][iter2][iter3] = -10;
      }
    }

  }
}


#endif
