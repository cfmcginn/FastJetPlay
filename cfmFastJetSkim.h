//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// FastJet Skim Class (MC)                                                    
//                                                                              
//=============================================  
#ifndef cfmFastJetSkim_h
#define cfmFastJetSkim_h

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

TTree* rechitTree_p = 0;

TTree* pfcandTree_p = 0;

TTree* jetTree_p = 0;

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
Float_t AlgRefPt_[3][2];
Float_t AlgRefPhi_[3][2];
Float_t AlgRefEta_[3][2];


void SetBranches(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  //Rechit Tree Branches

  rechitTree_p->Branch("nRechits", &nRechits_, "nRechits/I");
  rechitTree_p->Branch("rechitPt", &rechitPt_, "rechitPt[nRechits]/F");
  rechitTree_p->Branch("rechitPhi", &rechitPhi_, "rechitPhi[nRechits]/F");
  rechitTree_p->Branch("rechitEta", &rechitEta_, "rechitEta[nRechits]/F");

  //PF Tree Branches

  pfcandTree_p->Branch("nPF", &nPF_, "nPF/I");
  pfcandTree_p->Branch("pfPt", &pfPt_, "pfPt[nPF]/F");
  pfcandTree_p->Branch("pfPhi", &pfPhi_, "pfPhi[nPF]/F");
  pfcandTree_p->Branch("pfEta", &pfEta_, "pfEta[nPF]/F");

  //Jet Tree Branches

  jetTree_p->Branch("run", &run_, "run/I");
  jetTree_p->Branch("evt", &evt_, "evt/I");
  jetTree_p->Branch("lumi", &lumi_, "lumi/I");

  if(sType == kHIDATA || sType == kHIMC)
    jetTree_p->Branch("hiBin", &hiBin_, "hiBin/I");

   
  if(montecarlo)
    jetTree_p->Branch("pthat", &pthat_, "pthat/F");

  if(sType == kHIDATA || sType == kHIMC){
    jetTree_p->Branch("hiEvtPlane", &hiEvtPlane_, "hiEvtPlane/F");
    jetTree_p->Branch("psin", &psin_, "psin/F");
  }    

  jetTree_p->Branch("AlgJtPt", &AlgJtPt_, "AlgJtPt[3][2]/F");
  jetTree_p->Branch("AlgJtPhi", &AlgJtPhi_, "AlgJtPhi[3][2]/F");
  jetTree_p->Branch("AlgJtEta", &AlgJtEta_, "AlgJtEta[3][2]/F");

  if(montecarlo){
    jetTree_p->Branch("AlgRefPt", &AlgRefPt_, "AlgRefPt[3][2]/F");
    jetTree_p->Branch("AlgRefPhi", &AlgRefPhi_, "AlgRefPhi[3][2]/F");
    jetTree_p->Branch("AlgRefEta", &AlgRefEta_, "AlgRefEta[3][2]/F");
  }    
}


void GetBranches(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  //Rechit Tree Branches

  rechitTree_p->SetBranchAddress("nRechits", &nRechits_);
  rechitTree_p->SetBranchAddress("rechitPt", &rechitPt_);
  rechitTree_p->SetBranchAddress("rechitPhi", &rechitPhi_);
  rechitTree_p->SetBranchAddress("rechitEta", &rechitEta_);

  //PF Tree Branches

  pfcandTree_p->SetBranchAddress("nPF", &nPF_);
  pfcandTree_p->SetBranchAddress("pfPt", &pfPt_);
  pfcandTree_p->SetBranchAddress("pfPhi", &pfPhi_);
  pfcandTree_p->SetBranchAddress("pfEta", &pfEta_);

  //Jet Tree Branches

  jetTree_p->SetBranchAddress("run", &run_);
  jetTree_p->SetBranchAddress("evt", &evt_);
  jetTree_p->SetBranchAddress("lumi", &lumi_);

  if(sType == kHIDATA || sType == kHIMC)
    jetTree_p->SetBranchAddress("hiBin", &hiBin_);

  if(montecarlo)
    jetTree_p->SetBranchAddress("pthat", &pthat_);

  if(sType == kHIDATA || sType == kHIMC){
    jetTree_p->SetBranchAddress("hiEvtPlane", &hiEvtPlane_);
    jetTree_p->SetBranchAddress("psin", &psin_);
  }  

  jetTree_p->SetBranchAddress("AlgJtPt", AlgJtPt_);
  jetTree_p->SetBranchAddress("AlgJtPhi", AlgJtPhi_);
  jetTree_p->SetBranchAddress("AlgJtEta", AlgJtEta_);

  if(montecarlo){
    jetTree_p->SetBranchAddress("AlgRefPt", AlgRefPt_);
    jetTree_p->SetBranchAddress("AlgRefPhi", AlgRefPhi_);
    jetTree_p->SetBranchAddress("AlgRefEta", AlgRefEta_);
  }
}


void InitFastJetSkim(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  std::cout << "Init FastJet Skim" << std::endl;

  rechitTree_p = new TTree("rechitTree", "rechitTree");
  pfcandTree_p = new TTree("pfcandTree", "pfcandTree");
  jetTree_p = new TTree("jetTree", "jetTree");

  SetBranches(montecarlo, sType);
}


void CleanupFastJetSkim()
{
  if(rechitTree_p == 0) delete rechitTree_p;
  if(pfcandTree_p == 0) delete pfcandTree_p;
  if(jetTree_p == 0) delete jetTree_p;
}


void GetFastJetSkim(TFile* skimFile_p, Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  std::cout << "Get FastJet Skim" << std::endl;

  rechitTree_p = (TTree*)skimFile_p->Get("rechitTree");
  pfcandTree_p = (TTree*)skimFile_p->Get("pfcandTree");
  jetTree_p = (TTree*)skimFile_p->Get("jetTree");

  GetBranches(montecarlo, sType);
}


#endif
