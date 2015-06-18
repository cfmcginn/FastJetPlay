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
#include "jetSubstruct.h"

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

Float_t rechitSKPtCut_;

JetSubstruct* rechitRawJt_p;
JetSubstruct* rechitVsJt_p;

//pfcand TreeAna Variables

Float_t pfSKPtCut_;

JetSubstruct* pfRawJt_p;
JetSubstruct* pfVsJt_p;
JetSubstruct* pfSKJt_p;

//track TreeAna Variables

Float_t trkSKPtCut_;

JetSubstruct* trkRawJt_p;
JetSubstruct* trkSKJt_p;
JetSubstruct* trk3CutJt_p;

//Gen TreeAna Variables

Float_t genSKPtCut_;
Float_t genSKChgPtCut_;

JetSubstruct* genRawJt_p;
JetSubstruct* genSKJt_p;
JetSubstruct* genSUBEJt_p;
JetSubstruct* genRawChgJt_p;
JetSubstruct* genSKChgJt_p;
JetSubstruct* genSUBEChgJt_p;

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
    
    SetJetSubstructBranches(rechitTreeAna_p, rechitRawJt_p, "rechitRaw");
    SetJetSubstructBranches(rechitTreeAna_p, rechitVsJt_p, "rechitVs");
    
    //PF TreeAna Branches
    
    pfcandTreeAna_p->Branch("pfSKPtCut", &pfSKPtCut_, Form("pfSKPtCut/F")); 
    
    SetJetSubstructBranches(pfcandTreeAna_p, pfRawJt_p, "pfRaw");
    SetJetSubstructBranches(pfcandTreeAna_p, pfVsJt_p, "pfVs");
    SetJetSubstructBranches(pfcandTreeAna_p, pfSKJt_p, "pfSK");
    
    //Trk TreeAna Branches
    trkTreeAna_p->Branch("trkSKPtCut", &trkSKPtCut_, Form("trkSKPtCut/F"));    
    
    SetJetSubstructBranches(trkTreeAna_p, trkRawJt_p, "trkRaw");
    SetJetSubstructBranches(trkTreeAna_p, trkSKJt_p, "trkSK");
    SetJetSubstructBranches(trkTreeAna_p, trk3CutJt_p, "trk3Cut");
  }    

  //Gen TreeAna Branches
  if(montecarlo){
    genTreeAna_p->Branch("genSKPtCut", &genSKPtCut_, Form("genSKPtCut/F"));
    genTreeAna_p->Branch("genSKChgPtCut", &genSKChgPtCut_, Form("genSKChgPtCut/F"));

    SetJetSubstructBranches(genTreeAna_p, genRawJt_p, "genRaw");
    SetJetSubstructBranches(genTreeAna_p, genSKJt_p, "genSK");
    SetJetSubstructBranches(genTreeAna_p, genSUBEJt_p, "genSUBE");
    SetJetSubstructBranches(genTreeAna_p, genRawChgJt_p, "genRawChg");
    SetJetSubstructBranches(genTreeAna_p, genSKChgJt_p, "genSKChg");
    SetJetSubstructBranches(genTreeAna_p, genSUBEChgJt_p, "genSUBEChg");
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

    GetJetSubstructBranches(rechitTreeAna_p, rechitRawJt_p, "rechitRaw");
    GetJetSubstructBranches(rechitTreeAna_p, rechitVsJt_p, "rechitVs");

    //PF TreeAna Branches

    pfcandTreeAna_p->SetBranchAddress("pfSKPtCut", &pfSKPtCut_);    

    GetJetSubstructBranches(pfcandTreeAna_p, pfRawJt_p, "pfRaw");
    GetJetSubstructBranches(pfcandTreeAna_p, pfVsJt_p, "pfVs");
    GetJetSubstructBranches(pfcandTreeAna_p, pfSKJt_p, "pfSK");
    
    //Trk TreeAna Branches
    trkTreeAna_p->SetBranchAddress("trkSKPtCut", &trkSKPtCut_);    

    GetJetSubstructBranches(trkTreeAna_p, trkRawJt_p, "trkRaw");
    GetJetSubstructBranches(trkTreeAna_p, trkSKJt_p, "trkSK");
    GetJetSubstructBranches(trkTreeAna_p, trk3CutJt_p, "trk3Cut");
  }
  //Gen TreeAna Branches

  if(montecarlo){
    genTreeAna_p->SetBranchAddress("genSKPtCut", &genSKPtCut_);
    genTreeAna_p->SetBranchAddress("genSKChgPtCut", &genSKChgPtCut_);

    GetJetSubstructBranches(genTreeAna_p, genRawJt_p, "genRaw");
    GetJetSubstructBranches(genTreeAna_p, genSKJt_p, "genSK");
    GetJetSubstructBranches(genTreeAna_p, genSUBEJt_p, "genSUBE");
    GetJetSubstructBranches(genTreeAna_p, genRawChgJt_p, "genRawChg");
    GetJetSubstructBranches(genTreeAna_p, genSKChgJt_p, "genSKChg");
    GetJetSubstructBranches(genTreeAna_p, genSUBEChgJt_p, "genSUBEChg");

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


void InitJtVar()
{
  rechitSKPtCut_ = 0.010;
  pfSKPtCut_ = 0.010;
  trkSKPtCut_ = 0.010;
  genSKPtCut_ = 0.010;
  genSKChgPtCut_ = 0.010;

  return;
}


void InitJtSubstruct()
{
  rechitRawJt_p = new JetSubstruct();
  rechitVsJt_p = new JetSubstruct();

  pfRawJt_p = new JetSubstruct();
  pfVsJt_p = new JetSubstruct();
  pfSKJt_p = new JetSubstruct();


  trkRawJt_p = new JetSubstruct();
  trkSKJt_p = new JetSubstruct();
  trk3CutJt_p = new JetSubstruct();

  genRawJt_p = new JetSubstruct();
  genSKJt_p = new JetSubstruct();
  genSUBEJt_p = new JetSubstruct();
  genRawChgJt_p = new JetSubstruct();
  genSKChgJt_p = new JetSubstruct();
  genSUBEChgJt_p = new JetSubstruct();

  return;
}

void CleanupJtSubstruct()
{
  delete rechitRawJt_p;
  delete rechitVsJt_p;

  delete pfRawJt_p;
  delete pfVsJt_p;
  delete pfSKJt_p;


  delete trkRawJt_p;
  delete trkSKJt_p;
  delete trk3CutJt_p;

  delete genRawJt_p;
  delete genSKJt_p;
  delete genSUBEJt_p;
  delete genRawChgJt_p;
  delete genSKChgJt_p;
  delete genSUBEChgJt_p;

  rechitRawJt_p = 0;
  rechitVsJt_p = 0;

  pfRawJt_p = 0;
  pfVsJt_p = 0;
  pfSKJt_p = 0;


  trkRawJt_p = 0;
  trkSKJt_p = 0;
  trk3CutJt_p = 0;

  genRawJt_p = 0;
  genSKJt_p = 0;
  genSUBEJt_p = 0;
  genRawChgJt_p = 0;
  genSKChgJt_p = 0;
  genSUBEChgJt_p = 0;

  return;
}

#endif
