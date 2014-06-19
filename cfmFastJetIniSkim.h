//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// FastJet IniSkim Class (MC)                                                    
//                                                                              
//=============================================  
#ifndef cfmFastJetIniSkim_h
#define cfmFastJetIniSkim_h

#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "/net/hisrv0001/home/cfmcginn/emDiJet/CMSSW_5_3_12_patch3/tempHIFA/HiForestAnalysis/commonSetup.h"

enum sampleType{
  kHIDATA, //0
  kHIMC,   //1
  kPPDATA, //2
  kPPMC,   //3
  kPADATA, //4
  kPAMC    //5
};

enum AlgoType_PbPb{
  PuCalo,  //0
  VsCalo,  //1
  T        //2
};


TString getSampleName ( sampleType colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}
TString getSampleName ( int colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}

TTree* rechitTreeIni_p = 0;

TTree* pfcandTreeIni_p = 0;

TTree* jetTreeIni_p = 0;

//rechit Tree Variables

Int_t nRechits_;
Float_t rechitPt_[maxHits];
Float_t rechitPhi_[maxHits];
Float_t rechitEta_[maxHits];

//pfcand Tree Variables

Int_t nPF_;
Float_t pfPt_[maxPF];
Float_t pfPhi_[maxPF];
Float_t pfEta_[maxPF];

//Jet Tree Variables

Int_t run_;
Int_t evt_;
Int_t lumi_;
Int_t hiBin_;

Float_t pthat_;

Float_t hiEvtPlane_;
Float_t psin_;

Float_t AlgJtPt_[3][2];
Float_t AlgJtPhi_[3][2];
Float_t AlgJtEta_[3][2];
Float_t AlgJtRawPt_[3][2];
Float_t AlgRefPt_[3][2];
Float_t AlgRefPhi_[3][2];
Float_t AlgRefEta_[3][2];


void SetIniBranches(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  //Rechit Tree Branches

  rechitTreeIni_p->Branch("nRechits", &nRechits_, "nRechits/I");
  rechitTreeIni_p->Branch("rechitPt", &rechitPt_, "rechitPt[nRechits]/F");
  rechitTreeIni_p->Branch("rechitPhi", &rechitPhi_, "rechitPhi[nRechits]/F");
  rechitTreeIni_p->Branch("rechitEta", &rechitEta_, "rechitEta[nRechits]/F");

  //PF Tree Branches

  pfcandTreeIni_p->Branch("nPF", &nPF_, "nPF/I");
  pfcandTreeIni_p->Branch("pfPt", &pfPt_, "pfPt[nPF]/F");
  pfcandTreeIni_p->Branch("pfPhi", &pfPhi_, "pfPhi[nPF]/F");
  pfcandTreeIni_p->Branch("pfEta", &pfEta_, "pfEta[nPF]/F");

  //Jet Tree Branches

  jetTreeIni_p->Branch("run", &run_, "run/I");
  jetTreeIni_p->Branch("evt", &evt_, "evt/I");
  jetTreeIni_p->Branch("lumi", &lumi_, "lumi/I");

  if(sType == kHIDATA || sType == kHIMC)
    jetTreeIni_p->Branch("hiBin", &hiBin_, "hiBin/I");

   
  if(montecarlo)
    jetTreeIni_p->Branch("pthat", &pthat_, "pthat/F");

  if(sType == kHIDATA || sType == kHIMC){
    jetTreeIni_p->Branch("hiEvtPlane", &hiEvtPlane_, "hiEvtPlane/F");
    jetTreeIni_p->Branch("psin", &psin_, "psin/F");
  }    

  jetTreeIni_p->Branch("AlgJtPt", &AlgJtPt_, "AlgJtPt[3][2]/F");
  jetTreeIni_p->Branch("AlgJtPhi", &AlgJtPhi_, "AlgJtPhi[3][2]/F");
  jetTreeIni_p->Branch("AlgJtEta", &AlgJtEta_, "AlgJtEta[3][2]/F");
  jetTreeIni_p->Branch("AlgJtRawPt", &AlgJtRawPt_, "AlgJtRawPt[3][2]/F");

  if(montecarlo){
    jetTreeIni_p->Branch("AlgRefPt", &AlgRefPt_, "AlgRefPt[3][2]/F");
    jetTreeIni_p->Branch("AlgRefPhi", &AlgRefPhi_, "AlgRefPhi[3][2]/F");
    jetTreeIni_p->Branch("AlgRefEta", &AlgRefEta_, "AlgRefEta[3][2]/F");
  }    
}


void GetIniBranches(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  //Rechit Tree Branches

  rechitTreeIni_p->SetBranchAddress("nRechits", &nRechits_);
  rechitTreeIni_p->SetBranchAddress("rechitPt", &rechitPt_);
  rechitTreeIni_p->SetBranchAddress("rechitPhi", &rechitPhi_);
  rechitTreeIni_p->SetBranchAddress("rechitEta", &rechitEta_);

  //PF Tree Branches

  pfcandTreeIni_p->SetBranchAddress("nPF", &nPF_);
  pfcandTreeIni_p->SetBranchAddress("pfPt", &pfPt_);
  pfcandTreeIni_p->SetBranchAddress("pfPhi", &pfPhi_);
  pfcandTreeIni_p->SetBranchAddress("pfEta", &pfEta_);

  //Jet Tree Branches

  jetTreeIni_p->SetBranchAddress("run", &run_);
  jetTreeIni_p->SetBranchAddress("evt", &evt_);
  jetTreeIni_p->SetBranchAddress("lumi", &lumi_);

  if(sType == kHIDATA || sType == kHIMC)
    jetTreeIni_p->SetBranchAddress("hiBin", &hiBin_);

  if(montecarlo)
    jetTreeIni_p->SetBranchAddress("pthat", &pthat_);

  if(sType == kHIDATA || sType == kHIMC){
    jetTreeIni_p->SetBranchAddress("hiEvtPlane", &hiEvtPlane_);
    jetTreeIni_p->SetBranchAddress("psin", &psin_);
  }  

  jetTreeIni_p->SetBranchAddress("AlgJtPt", AlgJtPt_);
  jetTreeIni_p->SetBranchAddress("AlgJtPhi", AlgJtPhi_);
  jetTreeIni_p->SetBranchAddress("AlgJtEta", AlgJtEta_);
  jetTreeIni_p->SetBranchAddress("AlgJtRawPt", AlgJtRawPt_);

  if(montecarlo){
    jetTreeIni_p->SetBranchAddress("AlgRefPt", AlgRefPt_);
    jetTreeIni_p->SetBranchAddress("AlgRefPhi", AlgRefPhi_);
    jetTreeIni_p->SetBranchAddress("AlgRefEta", AlgRefEta_);
  }
}


void InitFastJetIniSkim(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  std::cout << "Init FastJet IniSkim" << std::endl;

  rechitTreeIni_p = new TTree("rechitTreeIni", "rechitTreeIni");
  pfcandTreeIni_p = new TTree("pfcandTreeIni", "pfcandTreeIni");
  jetTreeIni_p = new TTree("jetTreeIni", "jetTreeIni");

  SetIniBranches(montecarlo, sType);
}


void CleanupFastJetIniSkim()
{
  if(rechitTreeIni_p == 0) delete rechitTreeIni_p;
  if(pfcandTreeIni_p == 0) delete pfcandTreeIni_p;
  if(jetTreeIni_p == 0) delete jetTreeIni_p;
}


void GetFastJetIniSkim(TFile* iniSkimFile_p, Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  std::cout << "Get FastJet IniSkim" << std::endl;

  rechitTreeIni_p = (TTree*)iniSkimFile_p->Get("rechitTreeIni");
  pfcandTreeIni_p = (TTree*)iniSkimFile_p->Get("pfcandTreeIni");
  jetTreeIni_p = (TTree*)iniSkimFile_p->Get("jetTreeIni");

  GetIniBranches(montecarlo, sType);
}


#endif
