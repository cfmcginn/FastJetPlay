//=============================================                                 
// Author: Chris McGinn                                                         
//                                                                              
// FastJet IniSkim Class (MC)                                                    
//                                                                              
//=============================================  
#ifndef FastJetIniSkim_h
#define FastJetIniSkim_h

#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "commonSetup.h"

#include "sType.h"

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


Bool_t isPA(sampleType sType = kHIDATA){
  if(sType == kPADATA || sType == kPAMC) return true;
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
Float_t rechitIniSKPtCut_;
Float_t rechitPt_[maxHits];
Float_t rechitVsPt_[maxHits];
Float_t rechitPhi_[maxHits];
Float_t rechitEta_[maxHits];

//pfcand TreeIni Variables

Int_t nPF_;
Float_t pfIniSKPtCut_;
Float_t pfPt_[maxPF];
Float_t pfVsPt_[maxPF];
Float_t pfPhi_[maxPF];
Float_t pfEta_[maxPF];

//trk TreeIni Variables

Int_t nTrk_;
Float_t trkIniSKPtCut_;
Float_t trkPt_[maxTracks];
Float_t trkPhi_[maxTracks];
Float_t trkEta_[maxTracks];
Int_t trkChg_[maxTracks];

//gen TreeIni Variables

Int_t nGen_;
Float_t genIniSKPtCut_;
Float_t genIniSKChgPtCut_;
Float_t genPt_[maxEntrySim];
Float_t genPhi_[maxEntrySim];
Float_t genEta_[maxEntrySim];
Int_t genSube_[maxEntrySim];
Int_t genChg_[maxEntrySim];

Int_t nGen_TEMP_;
Float_t genPt_TEMP_[maxEntrySim];
Float_t genPhi_TEMP_[maxEntrySim];
Float_t genEta_TEMP_[maxEntrySim];

//Jet TreeIni Variables

Int_t runIni_;
Int_t evtIni_;
Int_t lumiIni_;
Int_t hiBinIni_;
Float_t bIni_;

Float_t pthatIni_;

Float_t hiEvtPlaneIni_;
Float_t psinIni_;

Float_t AlgIniJtPt_[5][5];
Float_t AlgIniJtPhi_[5][5];
Float_t AlgIniJtEta_[5][5];
Float_t AlgIniJtRawPt_[5][5];
Int_t AlgIniRefPartFlav_[5][5];
Float_t AlgIniRefPt_[5][5];
Float_t AlgIniRefPhi_[5][5];
Float_t AlgIniRefEta_[5][5];


void SetIniBranches(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);

  //Rechit TreeIni Branches

  if(!isGen){
    rechitTreeIni_p->Branch("nRechits", &nRechits_, "nRechits/I");
    rechitTreeIni_p->Branch("rechitIniSKPtCut", &rechitIniSKPtCut_, "rechitIniSKPtCut/F");
    rechitTreeIni_p->Branch("rechitPt", rechitPt_, "rechitPt[nRechits]/F");
    rechitTreeIni_p->Branch("rechitVsPt", rechitVsPt_, "rechitVsPt[nRechits]/F");
    rechitTreeIni_p->Branch("rechitPhi", rechitPhi_, "rechitPhi[nRechits]/F");
    rechitTreeIni_p->Branch("rechitEta", rechitEta_, "rechitEta[nRechits]/F");
    
    //PF TreeIni Branches
    
    pfcandTreeIni_p->Branch("nPF", &nPF_, "nPF/I");
    pfcandTreeIni_p->Branch("pfIniSKPtCut", &pfIniSKPtCut_, "pfIniSKPtCut/F");
    pfcandTreeIni_p->Branch("pfPt", pfPt_, "pfPt[nPF]/F");
    pfcandTreeIni_p->Branch("pfVsPt", pfVsPt_, "pfVsPt[nPF]/F");
    pfcandTreeIni_p->Branch("pfPhi", pfPhi_, "pfPhi[nPF]/F");
    pfcandTreeIni_p->Branch("pfEta", pfEta_, "pfEta[nPF]/F");
    
    //Trk TreeIni Branches
    
    trkTreeIni_p->Branch("nTrk", &nTrk_, "nTrk/I");
    trkTreeIni_p->Branch("trkIniSKPtCut", &trkIniSKPtCut_, "trkIniSKPtCut/F");
    trkTreeIni_p->Branch("trkPt", trkPt_, "trkPt[nTrk]/F");
    trkTreeIni_p->Branch("trkPhi", trkPhi_, "trkPhi[nTrk]/F");
    trkTreeIni_p->Branch("trkEta", trkEta_, "trkEta[nTrk]/F");
    trkTreeIni_p->Branch("trkChg", trkChg_, "trkChg[nTrk]/I");
  }
  //Gen TreeIni Branches

  if(montecarlo){
    genTreeIni_p->Branch("nGen", &nGen_, "nGen/I");
    genTreeIni_p->Branch("genIniSKPtCut", &genIniSKPtCut_, "genIniSKPtCut/F");
    genTreeIni_p->Branch("genIniSKChgPtCut", &genIniSKChgPtCut_, "genIniSKChgPtCut/F");
    genTreeIni_p->Branch("genPt", genPt_, "genPt[nGen]/F");
    genTreeIni_p->Branch("genPhi", genPhi_, "genPhi[nGen]/F");
    genTreeIni_p->Branch("genEta", genEta_, "genEta[nGen]/F");
    genTreeIni_p->Branch("genSube", genSube_, "genSube[nGen]/I");
    genTreeIni_p->Branch("genChg", genChg_, "genChg[nGen]/I");
  }    

  //Jet TreeIni Branches

  jetTreeIni_p->Branch("runIni", &runIni_, "runIni/I");
  jetTreeIni_p->Branch("evtIni", &evtIni_, "evtIni/I");
  jetTreeIni_p->Branch("lumiIni", &lumiIni_, "lumiIni/I");

  if(hi){
    jetTreeIni_p->Branch("hiBinIni", &hiBinIni_, "hiBinIni/I");
    if(montecarlo) jetTreeIni_p->Branch("bIni", &bIni_, "bIni/F");
  }
   
  if(montecarlo)
    jetTreeIni_p->Branch("pthatIni", &pthatIni_, "pthatIni/F");

  if(hi){
    jetTreeIni_p->Branch("hiEvtPlaneIni", &hiEvtPlaneIni_, "hiEvtPlaneIni/F");
    jetTreeIni_p->Branch("psinIni", &psinIni_, "psinIni/F");
  }    

  jetTreeIni_p->Branch("AlgIniJtPt", AlgIniJtPt_, "AlgIniJtPt[5][5]/F");
  jetTreeIni_p->Branch("AlgIniJtPhi", AlgIniJtPhi_, "AlgIniJtPhi[5][5]/F");
  jetTreeIni_p->Branch("AlgIniJtEta", AlgIniJtEta_, "AlgIniJtEta[5][5]/F");
  jetTreeIni_p->Branch("AlgIniJtRawPt", AlgIniJtRawPt_, "AlgIniJtRawPt[5][5]/F");

  if(montecarlo){
    jetTreeIni_p->Branch("AlgIniRefPartFlav", AlgIniRefPartFlav_, "AlgIniRefPartFlav[5][5]/I");
    jetTreeIni_p->Branch("AlgIniRefPt", AlgIniRefPt_, "AlgIniRefPt[5][5]/F");
    jetTreeIni_p->Branch("AlgIniRefPhi", AlgIniRefPhi_, "AlgIniRefPhi[5][5]/F");
    jetTreeIni_p->Branch("AlgIniRefEta", AlgIniRefEta_, "AlgIniRefEta[5][5]/F");
  }    

  return;
}


void GetIniBranches(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);

  //Rechit TreeIni Branches

  std::cout << "A" << std::endl;

  if(!isGen){
    std::cout << "A1" << std::endl;
    rechitTreeIni_p->SetBranchAddress("nRechits", &nRechits_);
    rechitTreeIni_p->SetBranchAddress("rechitIniSKPtCut", &rechitIniSKPtCut_);
    rechitTreeIni_p->SetBranchAddress("rechitPt", rechitPt_);
    rechitTreeIni_p->SetBranchAddress("rechitVsPt", rechitVsPt_);
    rechitTreeIni_p->SetBranchAddress("rechitPhi", rechitPhi_);
    rechitTreeIni_p->SetBranchAddress("rechitEta", rechitEta_);
    
    //PF TreeIni Branches

    std::cout << "A2" << std::endl;
    pfcandTreeIni_p->SetBranchAddress("nPF", &nPF_);
    pfcandTreeIni_p->SetBranchAddress("pfIniSKPtCut", &pfIniSKPtCut_);
    pfcandTreeIni_p->SetBranchAddress("pfPt", pfPt_);
    pfcandTreeIni_p->SetBranchAddress("pfVsPt", pfVsPt_);
    pfcandTreeIni_p->SetBranchAddress("pfPhi", pfPhi_);
    pfcandTreeIni_p->SetBranchAddress("pfEta", pfEta_);
    
    //Track TreeIni Branches
    std::cout << "A3" << std::endl;
    trkTreeIni_p->SetBranchAddress("nTrk", &nTrk_);
    trkTreeIni_p->SetBranchAddress("trkIniSKPtCut", &trkIniSKPtCut_);
    trkTreeIni_p->SetBranchAddress("trkPt", trkPt_);
    trkTreeIni_p->SetBranchAddress("trkPhi", trkPhi_);
    trkTreeIni_p->SetBranchAddress("trkEta", trkEta_);
    trkTreeIni_p->SetBranchAddress("trkChg", trkChg_);
  }
    //Gen TreeIni Branches

  std::cout << "B" << std::endl;

  if(montecarlo){
    genTreeIni_p->SetBranchAddress("nGen", &nGen_);
    genTreeIni_p->SetBranchAddress("genIniSKPtCut", &genIniSKPtCut_);
    genTreeIni_p->SetBranchAddress("genIniSKChgPtCut", &genIniSKChgPtCut_);
    genTreeIni_p->SetBranchAddress("genPt", genPt_);
    genTreeIni_p->SetBranchAddress("genPhi", genPhi_);
    genTreeIni_p->SetBranchAddress("genEta", genEta_);
    genTreeIni_p->SetBranchAddress("genSube", genSube_);
    genTreeIni_p->SetBranchAddress("genChg", genChg_);
  }    

  std::cout << "C" << std::endl;

  //Jet TreeIni Branches

  jetTreeIni_p->SetBranchAddress("runIni", &runIni_);
  jetTreeIni_p->SetBranchAddress("evtIni", &evtIni_);
  jetTreeIni_p->SetBranchAddress("lumiIni", &lumiIni_);

  if(hi){
    jetTreeIni_p->SetBranchAddress("hiBinIni", &hiBinIni_);
    if(montecarlo) jetTreeIni_p->SetBranchAddress("bIni", &bIni_);
  }

  if(montecarlo)
    jetTreeIni_p->SetBranchAddress("pthatIni", &pthatIni_);

  if(hi){
    jetTreeIni_p->SetBranchAddress("hiEvtPlaneIni", &hiEvtPlaneIni_);
    jetTreeIni_p->SetBranchAddress("psinIni", &psinIni_);
  }  

  std::cout << "D" << std::endl;

  jetTreeIni_p->SetBranchAddress("AlgIniJtPt", AlgIniJtPt_);
  jetTreeIni_p->SetBranchAddress("AlgIniJtPhi", AlgIniJtPhi_);
  jetTreeIni_p->SetBranchAddress("AlgIniJtEta", AlgIniJtEta_);
  jetTreeIni_p->SetBranchAddress("AlgIniJtRawPt", AlgIniJtRawPt_);

  if(montecarlo){
    jetTreeIni_p->SetBranchAddress("AlgIniRefPartFlav", AlgIniRefPartFlav_);
    jetTreeIni_p->SetBranchAddress("AlgIniRefPt", AlgIniRefPt_);
    jetTreeIni_p->SetBranchAddress("AlgIniRefPhi", AlgIniRefPhi_);
    jetTreeIni_p->SetBranchAddress("AlgIniRefEta", AlgIniRefEta_);
  }

  std::cout << "E" << std::endl;

  return;
}


void InitFastJetIniSkim(sampleType sType = kHIDATA, Bool_t isGen = false)
{
  std::cout << "Init FastJet IniSkim" << std::endl;

  if(!isGen){
    rechitTreeIni_p = new TTree("rechitTreeIni", "rechitTreeIni");
    pfcandTreeIni_p = new TTree("pfcandTreeIni", "pfcandTreeIni");
    trkTreeIni_p = new TTree("trkTreeIni", "trkTreeIni");
  }
  jetTreeIni_p = new TTree("jetTreeIni", "jetTreeIni");

  if(isMonteCarlo(sType)) genTreeIni_p = new TTree("genTreeIni", "genTreeIni");

  SetIniBranches(sType, isGen);

  return;
}


void CleanupFastJetIniSkim()
{
  if(rechitTreeIni_p != 0) delete rechitTreeIni_p;
  if(pfcandTreeIni_p != 0) delete pfcandTreeIni_p;
  if(trkTreeIni_p != 0) delete trkTreeIni_p;
  if(jetTreeIni_p != 0) delete jetTreeIni_p;
  if(genTreeIni_p != 0) delete genTreeIni_p;

  return;
}


void GetFastJetIniSkim(TFile* iniSkimFile_p, sampleType sType = kHIDATA, Bool_t isGen = false)
{
  std::cout << "Get FastJet IniSkim" << std::endl;

  if(!isGen){
    rechitTreeIni_p = (TTree*)iniSkimFile_p->Get("rechitTreeIni");
    pfcandTreeIni_p = (TTree*)iniSkimFile_p->Get("pfcandTreeIni");				  
    trkTreeIni_p = (TTree*)iniSkimFile_p->Get("trkTreeIni");
  }
  jetTreeIni_p = (TTree*)iniSkimFile_p->Get("jetTreeIni");

  if(isMonteCarlo(sType)) genTreeIni_p = (TTree*)iniSkimFile_p->Get("genTreeIni");

  GetIniBranches(sType);

  return;
}


void InitIniJtVar()
{
  for(Int_t iter = 0; iter < 5; iter++){
    for(Int_t iter2 = 0; iter2 < 5; iter2++){
      AlgIniJtPt_[iter][iter2] = -999;
      AlgIniJtPhi_[iter][iter2] = -999;
      AlgIniJtEta_[iter][iter2] = -999;
      AlgIniJtRawPt_[iter][iter2] = -999;

      AlgIniRefPartFlav_[iter][iter2] = -999;

      AlgIniRefPt_[iter][iter2] = -999;
      AlgIniRefPhi_[iter][iter2] = -999;
      AlgIniRefEta_[iter][iter2] = -999;
    }
  }

  return;
}


#endif
