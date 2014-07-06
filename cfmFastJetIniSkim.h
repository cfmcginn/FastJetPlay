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
  T,       //2
  PuPF,    //3
  VsPF   //4
};


Bool_t isMonteCarlo(sampleType sType = kHIDATA){
  if(sType == kHIMC || sType == kPPMC || sType == kPAMC) return true;
  else return false;
}


Bool_t isHI(sampleType sType = kHIDATA){
  if(sType == kHIDATA || sType == kHIMC) return true;
  else return false;
}


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
TTree* trkTreeIni_p = 0;
TTree* genTreeIni_p = 0;
TTree* jetTreeIni_p = 0;

//rechit TreeIni Variables

Int_t nRechits_;
Float_t rechitSKPtCut_;
Float_t rechitPt_[maxHits];
Float_t rechitVsPt_[maxHits];
Float_t rechitPhi_[maxHits];
Float_t rechitEta_[maxHits];

//pfcand TreeIni Variables

Int_t nPF_;
Float_t pfSKPtCut_;
Float_t pfPt_[maxPF];
Float_t pfVsPt_[maxPF];
Float_t pfPhi_[maxPF];
Float_t pfEta_[maxPF];

//trk TreeIni Variables

Int_t nTrk_;
Float_t trkSKPtCut_;
Float_t trkPt_[maxTracks];
Float_t trkPhi_[maxTracks];
Float_t trkEta_[maxTracks];

//gen TreeIni Variables

Int_t nGen_;
Float_t genPt_[maxEntrySim];
Float_t genPhi_[maxEntrySim];
Float_t genEta_[maxEntrySim];

//Jet TreeIni Variables

Int_t runIni_;
Int_t evtIni_;
Int_t lumiIni_;
Int_t hiBinIni_;

Float_t pthatIni_;

Float_t hiEvtPlaneIni_;
Float_t psinIni_;

Float_t AlgIniJtPt_[5][2];
Float_t AlgIniJtPhi_[5][2];
Float_t AlgIniJtEta_[5][2];
Float_t AlgIniJtRawPt_[5][2];
Float_t AlgIniRefPt_[5][2];
Float_t AlgIniRefPhi_[5][2];
Float_t AlgIniRefEta_[5][2];


void SetIniBranches(sampleType sType = kHIDATA)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);

  //Rechit TreeIni Branches

  rechitTreeIni_p->Branch("nRechits", &nRechits_, "nRechits/I");
  rechitTreeIni_p->Branch("rechitSKPtCut", &rechitSKPtCut_, "rechitSKPtCut/F");
  rechitTreeIni_p->Branch("rechitPt", &rechitPt_, "rechitPt[nRechits]/F");
  rechitTreeIni_p->Branch("rechitVsPt", &rechitVsPt_, "rechitVsPt[nRechits]/F");
  rechitTreeIni_p->Branch("rechitPhi", &rechitPhi_, "rechitPhi[nRechits]/F");
  rechitTreeIni_p->Branch("rechitEta", &rechitEta_, "rechitEta[nRechits]/F");

  //PF TreeIni Branches

  pfcandTreeIni_p->Branch("nPF", &nPF_, "nPF/I");
  pfcandTreeIni_p->Branch("pfSKPtCut", &pfSKPtCut_, "pfSKPtCut/F");
  pfcandTreeIni_p->Branch("pfPt", &pfPt_, "pfPt[nPF]/F");
  pfcandTreeIni_p->Branch("pfVsPt", &pfVsPt_, "pfVsPt[nPF]/F");
  pfcandTreeIni_p->Branch("pfPhi", &pfPhi_, "pfPhi[nPF]/F");
  pfcandTreeIni_p->Branch("pfEta", &pfEta_, "pfEta[nPF]/F");

  //Trk TreeIni Branches

  trkTreeIni_p->Branch("nTrk", &nTrk_, "nTrk/I");
  trkTreeIni_p->Branch("trkSKPtCut", &trkSKPtCut_, "trkSKPtCut/F");
  trkTreeIni_p->Branch("trkPt", &trkPt_, "trkPt[nTrk]/F");
  trkTreeIni_p->Branch("trkPhi", &trkPhi_, "trkPhi[nTrk]/F");
  trkTreeIni_p->Branch("trkEta", &trkEta_, "trkEta[nTrk]/F");

  //Gen TreeIni Branches

  if(montecarlo){
    genTreeIni_p->Branch("nGen", &nGen_, "nGen/I");
    genTreeIni_p->Branch("genPt", &genPt_, "genPt[nGen]/F");
    genTreeIni_p->Branch("genPhi", &genPhi_, "genPhi[nGen]/F");
    genTreeIni_p->Branch("genEta", &genEta_, "genEta[nGen]/F");
  }    

  //Jet TreeIni Branches

  jetTreeIni_p->Branch("runIni", &runIni_, "runIni/I");
  jetTreeIni_p->Branch("evtIni", &evtIni_, "evtIni/I");
  jetTreeIni_p->Branch("lumiIni", &lumiIni_, "lumiIni/I");

  if(hi)
    jetTreeIni_p->Branch("hiBinIni", &hiBinIni_, "hiBinIni/I");

   
  if(montecarlo)
    jetTreeIni_p->Branch("pthatIni", &pthatIni_, "pthatIni/F");

  if(hi){
    jetTreeIni_p->Branch("hiEvtPlaneIni", &hiEvtPlaneIni_, "hiEvtPlaneIni/F");
    jetTreeIni_p->Branch("psinIni", &psinIni_, "psinIni/F");
  }    

  jetTreeIni_p->Branch("AlgIniJtPt", &AlgIniJtPt_, "AlgIniJtPt[5][2]/F");
  jetTreeIni_p->Branch("AlgIniJtPhi", &AlgIniJtPhi_, "AlgIniJtPhi[5][2]/F");
  jetTreeIni_p->Branch("AlgIniJtEta", &AlgIniJtEta_, "AlgIniJtEta[5][2]/F");
  jetTreeIni_p->Branch("AlgIniJtRawPt", &AlgIniJtRawPt_, "AlgIniJtRawPt[5][2]/F");

  if(montecarlo){
    jetTreeIni_p->Branch("AlgIniRefPt", &AlgIniRefPt_, "AlgIniRefPt[5][2]/F");
    jetTreeIni_p->Branch("AlgIniRefPhi", &AlgIniRefPhi_, "AlgIniRefPhi[5][2]/F");
    jetTreeIni_p->Branch("AlgIniRefEta", &AlgIniRefEta_, "AlgIniRefEta[5][2]/F");
  }    
}


void GetIniBranches(sampleType sType = kHIDATA)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);

  //Rechit TreeIni Branches

  rechitTreeIni_p->SetBranchAddress("nRechits", &nRechits_);
  rechitTreeIni_p->SetBranchAddress("rechitSKPtCut", &rechitSKPtCut_);
  rechitTreeIni_p->SetBranchAddress("rechitPt", rechitPt_);
  rechitTreeIni_p->SetBranchAddress("rechitVsPt", rechitVsPt_);
  rechitTreeIni_p->SetBranchAddress("rechitPhi", rechitPhi_);
  rechitTreeIni_p->SetBranchAddress("rechitEta", rechitEta_);

  //PF TreeIni Branches

  pfcandTreeIni_p->SetBranchAddress("nPF", &nPF_);
  pfcandTreeIni_p->SetBranchAddress("pfSKPtCut", &pfSKPtCut_);
  pfcandTreeIni_p->SetBranchAddress("pfPt", pfPt_);
  pfcandTreeIni_p->SetBranchAddress("pfVsPt", pfVsPt_);
  pfcandTreeIni_p->SetBranchAddress("pfPhi", pfPhi_);
  pfcandTreeIni_p->SetBranchAddress("pfEta", pfEta_);

  //Track TreeIni Branches

  trkTreeIni_p->SetBranchAddress("nTrk", &nTrk_);
  trkTreeIni_p->SetBranchAddress("trkSKPtCut", &trkSKPtCut_);
  trkTreeIni_p->SetBranchAddress("trkPt", trkPt_);
  trkTreeIni_p->SetBranchAddress("trkPhi", trkPhi_);
  trkTreeIni_p->SetBranchAddress("trkEta", trkEta_);

  //Gen TreeIni Branches

  if(montecarlo){
    genTreeIni_p->SetBranchAddress("nGen", &nGen_);
    genTreeIni_p->SetBranchAddress("genPt", genPt_);
    genTreeIni_p->SetBranchAddress("genPhi", genPhi_);
    genTreeIni_p->SetBranchAddress("genEta", genEta_);
  }    

  //Jet TreeIni Branches

  jetTreeIni_p->SetBranchAddress("runIni", &runIni_);
  jetTreeIni_p->SetBranchAddress("evtIni", &evtIni_);
  jetTreeIni_p->SetBranchAddress("lumiIni", &lumiIni_);

  if(hi)
    jetTreeIni_p->SetBranchAddress("hiBinIni", &hiBinIni_);

  if(montecarlo)
    jetTreeIni_p->SetBranchAddress("pthatIni", &pthatIni_);

  if(hi){
    jetTreeIni_p->SetBranchAddress("hiEvtPlaneIni", &hiEvtPlaneIni_);
    jetTreeIni_p->SetBranchAddress("psinIni", &psinIni_);
  }  

  jetTreeIni_p->SetBranchAddress("AlgIniJtPt", AlgIniJtPt_);
  jetTreeIni_p->SetBranchAddress("AlgIniJtPhi", AlgIniJtPhi_);
  jetTreeIni_p->SetBranchAddress("AlgIniJtEta", AlgIniJtEta_);
  jetTreeIni_p->SetBranchAddress("AlgIniJtRawPt", AlgIniJtRawPt_);

  if(montecarlo){
    jetTreeIni_p->SetBranchAddress("AlgIniRefPt", AlgIniRefPt_);
    jetTreeIni_p->SetBranchAddress("AlgIniRefPhi", AlgIniRefPhi_);
    jetTreeIni_p->SetBranchAddress("AlgIniRefEta", AlgIniRefEta_);
  }
}


void InitFastJetIniSkim(sampleType sType = kHIDATA)
{
  std::cout << "Init FastJet IniSkim" << std::endl;

  rechitTreeIni_p = new TTree("rechitTreeIni", "rechitTreeIni");
  pfcandTreeIni_p = new TTree("pfcandTreeIni", "pfcandTreeIni");
  trkTreeIni_p = new TTree("trkTreeIni", "trkTreeIni");
  jetTreeIni_p = new TTree("jetTreeIni", "jetTreeIni");

  if(isMonteCarlo(sType)) genTreeIni_p = new TTree("genTreeIni", "genTreeIni");

  SetIniBranches(sType);
}


void CleanupFastJetIniSkim(sampleType sType)
{
  delete rechitTreeIni_p;
  delete pfcandTreeIni_p;
  delete trkTreeIni_p;
  delete jetTreeIni_p;
  if(isMonteCarlo(sType)) delete genTreeIni_p;
}


void GetFastJetIniSkim(TFile* iniSkimFile_p, sampleType sType = kHIDATA)
{
  std::cout << "Get FastJet IniSkim" << std::endl;

  rechitTreeIni_p = (TTree*)iniSkimFile_p->Get("rechitTreeIni");
  pfcandTreeIni_p = (TTree*)iniSkimFile_p->Get("pfcandTreeIni");				  
  trkTreeIni_p = (TTree*)iniSkimFile_p->Get("trkTreeIni");
  jetTreeIni_p = (TTree*)iniSkimFile_p->Get("jetTreeIni");

  if(isMonteCarlo(sType)) genTreeIni_p = (TTree*)iniSkimFile_p->Get("genTreeIni");

  GetIniBranches(sType);
}


#endif
