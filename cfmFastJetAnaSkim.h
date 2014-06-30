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

enum betaType{
  betaHalf, //0
  betaOne,  //1
  betaTwo   //2
};

TTree* rechitTreeAna_p = 0;
TTree* pfcandTreeAna_p = 0;
TTree* trkTreeAna_p = 0;
TTree* jetTreeAna_p = 0;

//rechit TreeAna Variables

Float_t rechitJtRawPt_[5];
Float_t rechitJtRawPhi_[5];
Float_t rechitJtRawEta_[5];
Float_t rechitRawTau1_[5][3];
Float_t rechitRawTau2_[5][3];
Float_t rechitRawTau3_[5][3];
Float_t rechitRawTau21_[5][3];
Float_t rechitRawTau32_[5][3];

Float_t rechitJtVsPt_[5];
Float_t rechitJtVsPhi_[5];
Float_t rechitJtVsEta_[5];
Float_t rechitVsTau1_[5][3];
Float_t rechitVsTau2_[5][3];
Float_t rechitVsTau3_[5][3];
Float_t rechitVsTau21_[5][3];
Float_t rechitVsTau32_[5][3];

//pfcand TreeAna Variables

Float_t pfJtRawPt_[5];
Float_t pfJtRawPhi_[5];
Float_t pfJtRawEta_[5];
Float_t pfRawTau1_[5][3];
Float_t pfRawTau2_[5][3];
Float_t pfRawTau3_[5][3];
Float_t pfRawTau21_[5][3];
Float_t pfRawTau32_[5][3];

Float_t pfJtVsPt_[5];
Float_t pfJtVsPhi_[5];
Float_t pfJtVsEta_[5];
Float_t pfVsTau1_[5][3];
Float_t pfVsTau2_[5][3];
Float_t pfVsTau3_[5][3];
Float_t pfVsTau21_[5][3];
Float_t pfVsTau32_[5][3];

//track TreeAna Variables

Float_t trkJtRawPt_[5];
Float_t trkJtRawPhi_[5];
Float_t trkJtRawEta_[5];
Float_t trkRawTau1_[5][3];
Float_t trkRawTau2_[5][3];
Float_t trkRawTau3_[5][3];
Float_t trkRawTau21_[5][3];
Float_t trkRawTau32_[5][3];

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
  rechitTreeAna_p->Branch("rechitRawTau1", &rechitRawTau1_, "rechitRawTau1[5][3]/F");
  rechitTreeAna_p->Branch("rechitRawTau2", &rechitRawTau2_, "rechitRawTau2[5][3]/F");
  rechitTreeAna_p->Branch("rechitRawTau3", &rechitRawTau3_, "rechitRawTau3[5][3]/F");
  rechitTreeAna_p->Branch("rechitRawTau21", &rechitRawTau21_, "rechitRawTau21[5][3]/F");
  rechitTreeAna_p->Branch("rechitRawTau32", &rechitRawTau32_, "rechitRawTau32[5][3]/F");

  rechitTreeAna_p->Branch("rechitJtVsPt", &rechitJtVsPt_, "rechitJtVsPt[5]/F");
  rechitTreeAna_p->Branch("rechitJtVsPhi", &rechitJtVsPhi_, "rechitJtVsPhi[5]/F");
  rechitTreeAna_p->Branch("rechitJtVsEta", &rechitJtVsEta_, "rechitJtVsEta[5]/F");
  rechitTreeAna_p->Branch("rechitVsTau1", &rechitVsTau1_, "rechitVsTau1[5][3]/F");
  rechitTreeAna_p->Branch("rechitVsTau2", &rechitVsTau2_, "rechitVsTau2[5][3]/F");
  rechitTreeAna_p->Branch("rechitVsTau3", &rechitVsTau3_, "rechitVsTau3[5][3]/F");
  rechitTreeAna_p->Branch("rechitVsTau21", &rechitVsTau21_, "rechitVsTau21[5][3]/F");
  rechitTreeAna_p->Branch("rechitVsTau32", &rechitVsTau32_, "rechitVsTau32[5][3]/F");

  //PF TreeAna Branches

  pfcandTreeAna_p->Branch("pfJtRawPt", &pfJtRawPt_, "pfJtRawPt[5]/F");
  pfcandTreeAna_p->Branch("pfJtRawPhi", &pfJtRawPhi_, "pfJtRawPhi[5]/F");
  pfcandTreeAna_p->Branch("pfJtRawEta", &pfJtRawEta_, "pfJtRawEta[5]/F");
  pfcandTreeAna_p->Branch("pfRawTau1", &pfRawTau1_, "pfRawTau1[5][3]/F");
  pfcandTreeAna_p->Branch("pfRawTau2", &pfRawTau2_, "pfRawTau2[5][3]/F");
  pfcandTreeAna_p->Branch("pfRawTau3", &pfRawTau3_, "pfRawTau3[5][3]/F");
  pfcandTreeAna_p->Branch("pfRawTau21", &pfRawTau21_, "pfRawTau21[5][3]/F");
  pfcandTreeAna_p->Branch("pfRawTau32", &pfRawTau32_, "pfRawTau32[5][3]/F");

  pfcandTreeAna_p->Branch("pfJtVsPt", &pfJtVsPt_, "pfJtVsPt[5]/F");
  pfcandTreeAna_p->Branch("pfJtVsPhi", &pfJtVsPhi_, "pfJtVsPhi[5]/F");
  pfcandTreeAna_p->Branch("pfJtVsEta", &pfJtVsEta_, "pfJtVsEta[5]/F");
  pfcandTreeAna_p->Branch("pfVsTau1", &pfVsTau1_, "pfVsTau1[5][3]/F");
  pfcandTreeAna_p->Branch("pfVsTau2", &pfVsTau2_, "pfVsTau2[5][3]/F");
  pfcandTreeAna_p->Branch("pfVsTau3", &pfVsTau3_, "pfVsTau3[5][3]/F");
  pfcandTreeAna_p->Branch("pfVsTau21", &pfVsTau21_, "pfVsTau21[5][3]/F");
  pfcandTreeAna_p->Branch("pfVsTau32", &pfVsTau32_, "pfVsTau32[5][3]/F");

  //Trk TreeAna Branches

  trkTreeAna_p->Branch("trkJtRawPt", &trkJtRawPt_, "trkJtRawPt[5]/F");
  trkTreeAna_p->Branch("trkJtRawPhi", &trkJtRawPhi_, "trkJtRawPhi[5]/F");
  trkTreeAna_p->Branch("trkJtRawEta", &trkJtRawEta_, "trkJtRawEta[5]/F");
  trkTreeAna_p->Branch("trkRawTau1", &trkRawTau1_, "trkRawTau1[5][3]/F");
  trkTreeAna_p->Branch("trkRawTau2", &trkRawTau2_, "trkRawTau2[5][3]/F");
  trkTreeAna_p->Branch("trkRawTau3", &trkRawTau3_, "trkRawTau3[5][3]/F");
  trkTreeAna_p->Branch("trkRawTau21", &trkRawTau21_, "trkRawTau21[5][3]/F");
  trkTreeAna_p->Branch("trkRawTau32", &trkRawTau32_, "trkRawTau32[5][3]/F");

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
  rechitTreeAna_p->SetBranchAddress("rechitRawTau1", rechitRawTau1_);
  rechitTreeAna_p->SetBranchAddress("rechitRawTau2", rechitRawTau2_);
  rechitTreeAna_p->SetBranchAddress("rechitRawTau3", rechitRawTau3_);
  rechitTreeAna_p->SetBranchAddress("rechitRawTau21", rechitRawTau21_);
  rechitTreeAna_p->SetBranchAddress("rechitRawTau32", rechitRawTau32_);

  rechitTreeAna_p->SetBranchAddress("rechitJtVsPt", rechitJtVsPt_);
  rechitTreeAna_p->SetBranchAddress("rechitJtVsPhi", rechitJtVsPhi_);
  rechitTreeAna_p->SetBranchAddress("rechitJtVsEta", rechitJtVsEta_);
  rechitTreeAna_p->SetBranchAddress("rechitVsTau1", rechitVsTau1_);
  rechitTreeAna_p->SetBranchAddress("rechitVsTau2", rechitVsTau2_);
  rechitTreeAna_p->SetBranchAddress("rechitVsTau3", rechitVsTau3_);
  rechitTreeAna_p->SetBranchAddress("rechitVsTau21", rechitVsTau21_);
  rechitTreeAna_p->SetBranchAddress("rechitVsTau32", rechitVsTau32_);

  //PF TreeAna Branches

  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPt_);
  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPhi_);
  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawEta_);
  pfcandTreeAna_p->SetBranchAddress("pfRawTau1", pfRawTau1_);
  pfcandTreeAna_p->SetBranchAddress("pfRawTau2", pfRawTau2_);
  pfcandTreeAna_p->SetBranchAddress("pfRawTau3", pfRawTau3_);
  pfcandTreeAna_p->SetBranchAddress("pfRawTau21", pfRawTau21_);
  pfcandTreeAna_p->SetBranchAddress("pfRawTau32", pfRawTau32_);

  pfcandTreeAna_p->SetBranchAddress("pfJtVsPt", pfJtVsPt_);
  pfcandTreeAna_p->SetBranchAddress("pfJtVsPhi", pfJtVsPhi_);
  pfcandTreeAna_p->SetBranchAddress("pfJtVsEta", pfJtVsEta_);
  pfcandTreeAna_p->SetBranchAddress("pfVsTau1", pfVsTau1_);
  pfcandTreeAna_p->SetBranchAddress("pfVsTau2", pfVsTau2_);
  pfcandTreeAna_p->SetBranchAddress("pfVsTau3", pfVsTau3_);
  pfcandTreeAna_p->SetBranchAddress("pfVsTau21", pfVsTau21_);
  pfcandTreeAna_p->SetBranchAddress("pfVsTau32", pfVsTau32_);

  //Trk TreeAna Branches

  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPt_);
  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPhi_);
  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawEta_);
  trkTreeAna_p->SetBranchAddress("trkRawTau1", trkRawTau1_);
  trkTreeAna_p->SetBranchAddress("trkRawTau2", trkRawTau2_);
  trkTreeAna_p->SetBranchAddress("trkRawTau3", trkRawTau3_);
  trkTreeAna_p->SetBranchAddress("trkRawTau21", trkRawTau21_);
  trkTreeAna_p->SetBranchAddress("trkRawTau32", trkRawTau32_);

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
    rechitJtRawPt_[iter] = -10;
    rechitJtRawPhi_[iter] = -10;
    rechitJtRawEta_[iter] = -10;

    rechitJtVsPt_[iter] = -10;
    rechitJtVsPhi_[iter] = -10;
    rechitJtVsEta_[iter] = -10;

    pfJtRawPt_[iter] = -10;
    pfJtRawPhi_[iter] = -10;
    pfJtRawEta_[iter] = -10;

    pfJtVsPt_[iter] = -10;
    pfJtVsPhi_[iter] = -10;
    pfJtVsEta_[iter] = -10;

    trkJtRawPt_[iter] = -10;
    trkJtRawPhi_[iter] = -10;
    trkJtRawEta_[iter] = -10;

    for(Int_t iter2 = 0; iter2 < 3; iter2++){
      rechitRawTau1_[iter][iter2] = -10;
      rechitRawTau2_[iter][iter2] = -10;
      rechitRawTau3_[iter][iter2] = -10;
      rechitRawTau21_[iter][iter2] = -10;
      rechitRawTau32_[iter][iter2] = -10;

      rechitVsTau1_[iter][iter2] = -10;
      rechitVsTau2_[iter][iter2] = -10;
      rechitVsTau3_[iter][iter2] = -10;
      rechitVsTau21_[iter][iter2] = -10;
      rechitVsTau32_[iter][iter2] = -10;

      pfRawTau1_[iter][iter2] = -10;
      pfRawTau2_[iter][iter2] = -10;
      pfRawTau3_[iter][iter2] = -10;
      pfRawTau21_[iter][iter2] = -10;
      pfRawTau32_[iter][iter2] = -10;      

      pfVsTau1_[iter][iter2] = -10;
      pfVsTau2_[iter][iter2] = -10;
      pfVsTau3_[iter][iter2] = -10;
      pfVsTau21_[iter][iter2] = -10;
      pfVsTau32_[iter][iter2] = -10;      

      trkRawTau1_[iter][iter2] = -10;
      trkRawTau2_[iter][iter2] = -10;
      trkRawTau3_[iter][iter2] = -10;
      trkRawTau21_[iter][iter2] = -10;
      trkRawTau32_[iter][iter2] = -10;      

    }

  }
}


#endif
