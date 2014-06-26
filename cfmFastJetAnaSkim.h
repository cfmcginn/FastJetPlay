//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// FastJet AnaSkim Class (MC)                                                    
//                                                                              
//=============================================  
#ifndef cfmFastJetAnaSkim_h
#define cfmFastJetAnaSkim_h

#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"

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
  T,       //2
  PuPF,    //3
  VsPF     //4
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

TTree* rechitTreeAna_p = 0;
TTree* pfcandTreeAna_p = 0;
TTree* trkTreeAna_p = 0;
TTree* jetTreeAna_p = 0;

//rechit TreeAna Variables

Float_t rechitJtRawPt_[5];
Float_t rechitJtRawPhi_[5];
Float_t rechitJtRawEta_[5];

//pfcand TreeAna Variables

Float_t pfJtRawPt_[5];
Float_t pfJtRawPhi_[5];
Float_t pfJtRawEta_[5];

//track TreeAna Variables

Float_t trkJtRawPt_[5];
Float_t trkJtRawPhi_[5];
Float_t trkJtRawEta_[5];

//Jet TreeAna Variables

Int_t run_;
Int_t evt_;
Int_t lumi_;
Int_t hiBin_;

Float_t pthat_;

Float_t hiEvtPlane_;
Float_t psin_;

Float_t AlgJtPt_[5][2];
Float_t AlgJtPhi_[5][2];
Float_t AlgJtEta_[5][2];
Float_t AlgJtRawPt_[5][2];
Float_t AlgRefPt_[5][2];
Float_t AlgRefPhi_[5][2];
Float_t AlgRefEta_[5][2];


void SetAnaBranches(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  //Rechit TreeAna Branches

  rechitTreeAna_p->Branch("rechitJtRawPt", &rechitJtRawPt_, "rechitJtRawPt[5]/F");
  rechitTreeAna_p->Branch("rechitJtRawPhi", &rechitJtRawPhi_, "rechitJtRawPhi[5]/F");
  rechitTreeAna_p->Branch("rechitJtRawEta", &rechitJtRawEta_, "rechitJtRawEta[5]/F");

  //PF TreeAna Branches

  pfcandTreeAna_p->Branch("pfJtRawPt", &pfJtRawPt_, "pfJtRawPt[5]/F");
  pfcandTreeAna_p->Branch("pfJtRawPhi", &pfJtRawPhi_, "pfJtRawPhi[5]/F");
  pfcandTreeAna_p->Branch("pfJtRawEta", &pfJtRawEta_, "pfJtRawEta[5]/F");

  //Trk TreeAna Branches

  trkTreeAna_p->Branch("trkJtRawPt", &trkJtRawPt_, "trkJtRawPt[5]/F");
  trkTreeAna_p->Branch("trkJtRawPhi", &trkJtRawPhi_, "trkJtRawPhi[5]/F");
  trkTreeAna_p->Branch("trkJtRawEta", &trkJtRawEta_, "trkJtRawEta[5]/F");

  //Jet TreeAna Branches

  jetTreeAna_p->Branch("run", &run_, "run/I");
  jetTreeAna_p->Branch("evt", &evt_, "evt/I");
  jetTreeAna_p->Branch("lumi", &lumi_, "lumi/I");

  if(sType == kHIDATA || sType == kHIMC)
    jetTreeAna_p->Branch("hiBin", &hiBin_, "hiBin/I");

   
  if(montecarlo)
    jetTreeAna_p->Branch("pthat", &pthat_, "pthat/F");

  if(sType == kHIDATA || sType == kHIMC){
    jetTreeAna_p->Branch("hiEvtPlane", &hiEvtPlane_, "hiEvtPlane/F");
    jetTreeAna_p->Branch("psin", &psin_, "psin/F");
  }    

  jetTreeAna_p->Branch("AlgJtPt", &AlgJtPt_, "AlgJtPt[5][2]/F");
  jetTreeAna_p->Branch("AlgJtPhi", &AlgJtPhi_, "AlgJtPhi[5][2]/F");
  jetTreeAna_p->Branch("AlgJtEta", &AlgJtEta_, "AlgJtEta[5][2]/F");
  jetTreeAna_p->Branch("AlgJtRawPt", &AlgJtRawPt_, "AlgJtRawPt[5][2]/F");

  if(montecarlo){
    jetTreeAna_p->Branch("AlgRefPt", &AlgRefPt_, "AlgRefPt[5][2]/F");
    jetTreeAna_p->Branch("AlgRefPhi", &AlgRefPhi_, "AlgRefPhi[5][2]/F");
    jetTreeAna_p->Branch("AlgRefEta", &AlgRefEta_, "AlgRefEta[5][2]/F");
  }    
}


void GetAnaBranches(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  //Rechit TreeAna Branches

  rechitTreeAna_p->SetBranchAddress("rechitJtRawPt", rechitJtRawPt_);
  rechitTreeAna_p->SetBranchAddress("rechitJtRawPt", rechitJtRawPhi_);
  rechitTreeAna_p->SetBranchAddress("rechitJtRawPt", rechitJtRawEta_);

  //PF TreeAna Branches

  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPt_);
  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPhi_);
  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawEta_);

  //Trk TreeAna Branches

  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPt_);
  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPhi_);
  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawEta_);

  //Jet TreeAna Branches

  jetTreeAna_p->SetBranchAddress("run", &run_);
  jetTreeAna_p->SetBranchAddress("evt", &evt_);
  jetTreeAna_p->SetBranchAddress("lumi", &lumi_);

  if(sType == kHIDATA || sType == kHIMC)
    jetTreeAna_p->SetBranchAddress("hiBin", &hiBin_);

  if(montecarlo)
    jetTreeAna_p->SetBranchAddress("pthat", &pthat_);

  if(sType == kHIDATA || sType == kHIMC){
    jetTreeAna_p->SetBranchAddress("hiEvtPlane", &hiEvtPlane_);
    jetTreeAna_p->SetBranchAddress("psin", &psin_);
  }  

  jetTreeAna_p->SetBranchAddress("AlgJtPt", AlgJtPt_);
  jetTreeAna_p->SetBranchAddress("AlgJtPhi", AlgJtPhi_);
  jetTreeAna_p->SetBranchAddress("AlgJtEta", AlgJtEta_);
  jetTreeAna_p->SetBranchAddress("AlgJtRawPt", AlgJtRawPt_);

  if(montecarlo){
    jetTreeAna_p->SetBranchAddress("AlgRefPt", AlgRefPt_);
    jetTreeAna_p->SetBranchAddress("AlgRefPhi", AlgRefPhi_);
    jetTreeAna_p->SetBranchAddress("AlgRefEta", AlgRefEta_);
  }
}


void InitFastJetAnaSkim(Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  std::cout << "Init FastJet AnaSkim" << std::endl;

  rechitTreeAna_p = new TTree("rechitTreeAna", "rechitTreeAna");
  pfcandTreeAna_p = new TTree("pfcandTreeAna", "pfcandTreeAna");
  trkTreeAna_p = new TTree("trkTreeAna", "trkTreeAna");
  jetTreeAna_p = new TTree("jetTreeAna", "jetTreeAna");

  SetAnaBranches(montecarlo, sType);
}


void CleanupFastJetAnaSkim()
{
  if(rechitTreeAna_p == 0) delete rechitTreeAna_p;
  if(pfcandTreeAna_p == 0) delete pfcandTreeAna_p;
  if(trkTreeAna_p == 0) delete trkTreeAna_p;
  if(jetTreeAna_p == 0) delete jetTreeAna_p;
}


void GetFastJetAnaSkim(TFile* iniSkimFile_p, Bool_t montecarlo = false, sampleType sType = kHIDATA)
{
  std::cout << "Get FastJet AnaSkim" << std::endl;

  rechitTreeAna_p = (TTree*)iniSkimFile_p->Get("rechitTreeAna");
  pfcandTreeAna_p = (TTree*)iniSkimFile_p->Get("pfcandTreeAna");
  trkTreeAna_p = (TTree*)iniSkimFile_p->Get("trkTreeAna");
  jetTreeAna_p = (TTree*)iniSkimFile_p->Get("jetTreeAna");

  GetAnaBranches(montecarlo, sType);
}


void InitJtVar(){
  for(Int_t iter = 0; iter < 5; iter++){
    rechitRawJtPt[iter] = -10;
    rechitRawJtPhi[iter] = -10;
    rechitRawJtEta[iter] = -10;

    pfcandRawJtPt[iter] = -10;
    pfcandRawJtPhi[iter] = -10;
    pfcandRawJtEta[iter] = -10;

    trkRawJtPt[iter] = -10;
    trkRawJtPhi[iter] = -10;
    trkRawJtEta[iter] = -10;
  }
}


#endif
