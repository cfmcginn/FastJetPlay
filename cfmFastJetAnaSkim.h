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
TTree* jetTreeAna_p = 0;

//rechit TreeAna Variables

Float_t rechitJtRawPt_[5];
Float_t rechitJtRawPhi_[5];
Float_t rechitJtRawEta_[5];
Float_t rechitRawTau_[5][3][3];
Float_t rechitSubJtRawPt_[5][3][3];
Float_t rechitSubJtRawPhi_[5][3][3];
Float_t rechitSubJtRawEta_[5][3][3];

Float_t rechitJtVsPt_[5];
Float_t rechitJtVsPhi_[5];
Float_t rechitJtVsEta_[5];
Float_t rechitVsTau_[5][3][3];
Float_t rechitSubJtVsPt_[5][3][3];
Float_t rechitSubJtVsPhi_[5][3][3];
Float_t rechitSubJtVsEta_[5][3][3];

//pfcand TreeAna Variables

Float_t pfJtRawPt_[5];
Float_t pfJtRawPhi_[5];
Float_t pfJtRawEta_[5];
Float_t pfRawTau_[5][3][3];
Float_t pfSubJtRawPt_[5][3][3];
Float_t pfSubJtRawPhi_[5][3][3];
Float_t pfSubJtRawEta_[5][3][3];

Float_t pfJtVsPt_[5];
Float_t pfJtVsPhi_[5];
Float_t pfJtVsEta_[5];
Float_t pfVsTau_[5][3][3];
Float_t pfSubJtVsPt_[5][3][3];
Float_t pfSubJtVsPhi_[5][3][3];
Float_t pfSubJtVsEta_[5][3][3];

//track TreeAna Variables

Float_t trkJtRawPt_[5];
Float_t trkJtRawPhi_[5];
Float_t trkJtRawEta_[5];
Float_t trkRawTau_[5][3][3];
Float_t trkSubJtRawPt_[5][3][3];
Float_t trkSubJtRawPhi_[5][3][3];
Float_t trkSubJtRawEta_[5][3][3];

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
  rechitTreeAna_p->Branch("rechitRawTau", &rechitRawTau_, "rechitRawTau[5][3][3]/F");
  rechitTreeAna_p->Branch("rechitSubJtRawPt", &rechitSubJtRawPt_, "rechitSubJtRawPt[5][3][3]/F");
  rechitTreeAna_p->Branch("rechitSubJtRawPhi", &rechitSubJtRawPhi_, "rechitSubJtRawPhi[5][3][3]/F");
  rechitTreeAna_p->Branch("rechitSubJtRawEta", &rechitSubJtRawEta_, "rechitSubJtRawEta[5][3][3]/F");

  rechitTreeAna_p->Branch("rechitJtVsPt", &rechitJtVsPt_, "rechitJtVsPt[5]/F");
  rechitTreeAna_p->Branch("rechitJtVsPhi", &rechitJtVsPhi_, "rechitJtVsPhi[5]/F");
  rechitTreeAna_p->Branch("rechitJtVsEta", &rechitJtVsEta_, "rechitJtVsEta[5]/F");
  rechitTreeAna_p->Branch("rechitVsTau", &rechitVsTau_, "rechitVsTau[5][3][3]/F");
  rechitTreeAna_p->Branch("rechitSubJtVsPt", &rechitSubJtVsPt_, "rechitSubJtVsPt[5][3][3]/F");
  rechitTreeAna_p->Branch("rechitSubJtVsPhi", &rechitSubJtVsPhi_, "rechitSubJtVsPhi[5][3][3]/F");
  rechitTreeAna_p->Branch("rechitSubJtVsEta", &rechitSubJtVsEta_, "rechitSubJtVsEta[5][3][3]/F");

  //PF TreeAna Branches

  pfcandTreeAna_p->Branch("pfJtRawPt", &pfJtRawPt_, "pfJtRawPt[5]/F");
  pfcandTreeAna_p->Branch("pfJtRawPhi", &pfJtRawPhi_, "pfJtRawPhi[5]/F");
  pfcandTreeAna_p->Branch("pfJtRawEta", &pfJtRawEta_, "pfJtRawEta[5]/F");
  pfcandTreeAna_p->Branch("pfRawTau", &pfRawTau_, "pfRawTau[5][3][3]/F");
  pfcandTreeAna_p->Branch("pfSubJtRawPt", &pfSubJtRawPt_, "pfSubJtRawPt[5][3][3]/F");
  pfcandTreeAna_p->Branch("pfSubJtRawPhi", &pfSubJtRawPhi_, "pfSubJtRawPhi[5][3][3]/F");
  pfcandTreeAna_p->Branch("pfSubJtRawEta", &pfSubJtRawEta_, "pfSubJtRawEta[5][3][3]/F");

  pfcandTreeAna_p->Branch("pfJtVsPt", &pfJtVsPt_, "pfJtVsPt[5]/F");
  pfcandTreeAna_p->Branch("pfJtVsPhi", &pfJtVsPhi_, "pfJtVsPhi[5]/F");
  pfcandTreeAna_p->Branch("pfJtVsEta", &pfJtVsEta_, "pfJtVsEta[5]/F");
  pfcandTreeAna_p->Branch("pfVsTau", &pfVsTau_, "pfVsTau[5][3][3]/F");
  pfcandTreeAna_p->Branch("pfSubJtVsPt", &pfSubJtVsPt_, "pfSubJtVsPt[5][3][3]/F");
  pfcandTreeAna_p->Branch("pfSubJtVsPhi", &pfSubJtVsPhi_, "pfSubJtVsPhi[5][3][3]/F");
  pfcandTreeAna_p->Branch("pfSubJtVsEta", &pfSubJtVsEta_, "pfSubJtVsEta[5][3][3]/F");

  //Trk TreeAna Branches

  trkTreeAna_p->Branch("trkJtRawPt", &trkJtRawPt_, "trkJtRawPt[5]/F");
  trkTreeAna_p->Branch("trkJtRawPhi", &trkJtRawPhi_, "trkJtRawPhi[5]/F");
  trkTreeAna_p->Branch("trkJtRawEta", &trkJtRawEta_, "trkJtRawEta[5]/F");
  trkTreeAna_p->Branch("trkRawTau", &trkRawTau_, "trkRawTau[5][3][3]/F");
  trkTreeAna_p->Branch("trkSubJtRawPt", &trkSubJtRawPt_, "trkSubJtRawPt[5][3][3]/F");
  trkTreeAna_p->Branch("trkSubJtRawPhi", &trkSubJtRawPhi_, "trkSubJtRawPhi[5][3][3]/F");
  trkTreeAna_p->Branch("trkSubJtRawEta", &trkSubJtRawEta_, "trkSubJtRawEta[5][3][3]/F");

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
  rechitTreeAna_p->SetBranchAddress("rechitRawTau", rechitRawTau_);
  rechitTreeAna_p->SetBranchAddress("rechitSubJtRawPt", rechitSubJtRawPt_);
  rechitTreeAna_p->SetBranchAddress("rechitSubJtRawPhi", rechitSubJtRawPhi_);
  rechitTreeAna_p->SetBranchAddress("rechitSubJtRawEta", rechitSubJtRawEta_);

  rechitTreeAna_p->SetBranchAddress("rechitJtVsPt", rechitJtVsPt_);
  rechitTreeAna_p->SetBranchAddress("rechitJtVsPhi", rechitJtVsPhi_);
  rechitTreeAna_p->SetBranchAddress("rechitJtVsEta", rechitJtVsEta_);
  rechitTreeAna_p->SetBranchAddress("rechitVsTau", rechitVsTau_);
  rechitTreeAna_p->SetBranchAddress("rechitSubJtVsPt", rechitSubJtVsPt_);
  rechitTreeAna_p->SetBranchAddress("rechitSubJtVsPhi", rechitSubJtVsPhi_);
  rechitTreeAna_p->SetBranchAddress("rechitSubJtVsEta", rechitSubJtVsEta_);

  //PF TreeAna Branches

  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPt_);
  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawPhi_);
  pfcandTreeAna_p->SetBranchAddress("pfJtRawPt", pfJtRawEta_);
  pfcandTreeAna_p->SetBranchAddress("pfRawTau", pfRawTau_);
  pfcandTreeAna_p->SetBranchAddress("pfSubJtRawPt", pfSubJtRawPt_);
  pfcandTreeAna_p->SetBranchAddress("pfSubJtRawPhi", pfSubJtRawPhi_);
  pfcandTreeAna_p->SetBranchAddress("pfSubJtRawEta", pfSubJtRawEta_);

  pfcandTreeAna_p->SetBranchAddress("pfJtVsPt", pfJtVsPt_);
  pfcandTreeAna_p->SetBranchAddress("pfJtVsPhi", pfJtVsPhi_);
  pfcandTreeAna_p->SetBranchAddress("pfJtVsEta", pfJtVsEta_);
  pfcandTreeAna_p->SetBranchAddress("pfVsTau", pfVsTau_);
  pfcandTreeAna_p->SetBranchAddress("pfSubJtVsPt", pfSubJtVsPt_);
  pfcandTreeAna_p->SetBranchAddress("pfSubJtVsPhi", pfSubJtVsPhi_);
  pfcandTreeAna_p->SetBranchAddress("pfSubJtVsEta", pfSubJtVsEta_);

  //Trk TreeAna Branches

  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPt_);
  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawPhi_);
  trkTreeAna_p->SetBranchAddress("trkJtRawPt", trkJtRawEta_);
  trkTreeAna_p->SetBranchAddress("trkRawTau", trkRawTau_);
  trkTreeAna_p->SetBranchAddress("trkSubJtRawPt", trkSubJtRawPt_);
  trkTreeAna_p->SetBranchAddress("trkSubJtRawPhi", trkSubJtRawPhi_);
  trkTreeAna_p->SetBranchAddress("trkSubJtRawEta", trkSubJtRawEta_);

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
      for(Int_t iter3 = 0; iter3 < 3; iter3++){
	rechitRawTau_[iter][iter2][iter3] = -10;
	rechitSubJtRawPt_[iter][iter2][iter3] = -10;
	rechitSubJtRawPhi_[iter][iter2][iter3] = -10;
	rechitSubJtRawEta_[iter][iter2][iter3] = -10;
	
	rechitVsTau_[iter][iter2][iter3] = -10;
	rechitSubJtVsPt_[iter][iter2][iter3] = -10;
	rechitSubJtVsPhi_[iter][iter2][iter3] = -10;
	rechitSubJtVsEta_[iter][iter2][iter3] = -10;
	
	pfRawTau_[iter][iter2][iter3] = -10;
	pfSubJtRawPt_[iter][iter2][iter3] = -10;
	pfSubJtRawPhi_[iter][iter2][iter3] = -10;
	pfSubJtRawEta_[iter][iter2][iter3] = -10;
	
	pfVsTau_[iter][iter2][iter3] = -10;
	pfSubJtVsPt_[iter][iter2][iter3] = -10;
	pfSubJtVsPhi_[iter][iter2][iter3] = -10;
	pfSubJtVsEta_[iter][iter2][iter3] = -10;
	
	trkRawTau_[iter][iter2][iter3] = -10;
	trkSubJtRawPt_[iter][iter2][iter3] = -10;
	trkSubJtRawPhi_[iter][iter2][iter3] = -10;
	trkSubJtRawEta_[iter][iter2][iter3] = -10;
      }
    }

  }
}


#endif
