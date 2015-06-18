#include <string>
#include "VectFunc.h"
#include "FastJetHist.h"

TFile* inFile_p = 0;
TFile* outFile_p = 0;

const Float_t leadJtCut = 120.;
const Float_t subLeadJtCut = 50.;

const Float_t totJtPtCut = 50.;
const Float_t totJtEtaCut = 2.0;
const Float_t totJtAjCut = 0.33;

const Float_t pPbEtaBoost = 0.4654094531;

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};

const Int_t ptCuts[6] = {60, 80, 100, 120, 140, 200};
const Int_t ptPosArr[5] = {3, 4, 5, 6, 7};

Bool_t isEventCut(Int_t setNum, sampleType sType)
{
  if(isPA(sType)) return false;

  if(!eventSet_[setNum]) return true;

  if(AlgJtPt_[setNum][0] < leadJtCut || AlgJtPt_[setNum][1] < subLeadJtCut) return true;

  if(TMath::Abs(AlgJtEta_[setNum][0]) > 1.6 || TMath::Abs(AlgJtEta_[setNum][1]) > 1.6) return true;

  if(AlgJtDelPhi_[setNum] < 5.0*TMath::Pi()/6.0) return true;

  if(isMonteCarlo(sType) && pthat_ < 80) return true;

  return false;
}


void makeJetSubStructHist(TTree* anaTree_p, const std::string outName, Int_t setNum, sampleType sType)
{
  const Bool_t isMC = isMonteCarlo(sType);
  
  rechitRawJt_HistTot_p = new JetSubstructHist();
  rechitVsJt_HistTot_p = new JetSubstructHist();

  pfRawJt_HistTot_p = new JetSubstructHist();
  pfVsJt_HistTot_p = new JetSubstructHist();
  pfSKJt_HistTot_p = new JetSubstructHist();

  trkRawJt_HistTot_p = new JetSubstructHist();
  trkSKJt_HistTot_p = new JetSubstructHist();
  trk3CutJt_HistTot_p = new JetSubstructHist();

  if(isMC){
    genRawJt_HistTot_p = new JetSubstructHist();
    genSKJt_HistTot_p = new JetSubstructHist();
    genSUBEJt_HistTot_p = new JetSubstructHist();
    genChgJt_HistTot_p = new JetSubstructHist();
    genSKChgJt_HistTot_p = new JetSubstructHist();
  }  

  if(isMC){
    rechitRawJt_HistQ_p = new JetSubstructHist();
    rechitVsJt_HistQ_p = new JetSubstructHist();
    
    pfRawJt_HistQ_p = new JetSubstructHist();
    pfVsJt_HistQ_p = new JetSubstructHist();
    pfSKJt_HistQ_p = new JetSubstructHist();
    
    trkRawJt_HistQ_p = new JetSubstructHist();
    trkSKJt_HistQ_p = new JetSubstructHist();
    trk3CutJt_HistQ_p = new JetSubstructHist();
    
    genRawJt_HistQ_p = new JetSubstructHist();
    genSKJt_HistQ_p = new JetSubstructHist();
    genSUBEJt_HistQ_p = new JetSubstructHist();
    genChgJt_HistQ_p = new JetSubstructHist();
    genSKChgJt_HistQ_p = new JetSubstructHist();
    
    rechitRawJt_HistG_p = new JetSubstructHist();
    rechitVsJt_HistG_p = new JetSubstructHist();
    
    pfRawJt_HistG_p = new JetSubstructHist();
    pfVsJt_HistG_p = new JetSubstructHist();
    pfSKJt_HistG_p = new JetSubstructHist();
    
    trkRawJt_HistG_p = new JetSubstructHist();
    trkSKJt_HistG_p = new JetSubstructHist();
    trk3CutJt_HistG_p = new JetSubstructHist();
    
    genRawJt_HistG_p = new JetSubstructHist();
    genSKJt_HistG_p = new JetSubstructHist();
    genSUBEJt_HistG_p = new JetSubstructHist();
    genChgJt_HistG_p = new JetSubstructHist();
    genSKChgJt_HistG_p = new JetSubstructHist();
  }  

  BookHist(sType, algType[setNum]);


  for(Int_t jEntry = 0; jEntry < (Int_t)anaTree_p->GetEntries(); jEntry++){
    anaTree_p->GetEntry(jEntry);
    if(jEntry%10000 == 0) std::cout << jEntry << std::endl;
    if(isEventCut(setNum, sType)) continue;
    if(isMC)
      if(pthat_ < 50) continue;

    Float_t hatWeight = 1;
    if(isMC) hatWeight = pthatWeight_;

    FillJetSubstructHist(rechitRawJt_p, rechitRawJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
    FillJetSubstructHist(rechitVsJt_p, rechitVsJt_HistTot_p, sType, hiBin_, hatWeight, Tot);

    FillJetSubstructHist(pfRawJt_p, pfRawJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
    FillJetSubstructHist(pfVsJt_p, pfVsJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
    FillJetSubstructHist(pfSKJt_p, pfSKJt_HistTot_p, sType, hiBin_, hatWeight, Tot);

    FillJetSubstructHist(trkRawJt_p, trkRawJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
    FillJetSubstructHist(trkSKJt_p, trkSKJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
    FillJetSubstructHist(trk3CutJt_p, trk3CutJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
    if(isMC){
      FillJetSubstructHist(genRawJt_p, genRawJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
      FillJetSubstructHist(genSKJt_p, genSKJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
      FillJetSubstructHist(genSUBEJt_p, genSUBEJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
      FillJetSubstructHist(genChgJt_p, genChgJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
      FillJetSubstructHist(genSKChgJt_p, genSKChgJt_HistTot_p, sType, hiBin_, hatWeight, Tot);
    }

    if(isMC){
      // QUARKS!

      FillJetSubstructHist(rechitRawJt_p, rechitRawJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(rechitVsJt_p, rechitVsJt_HistQ_p, sType, hiBin_, hatWeight, Qua);

      FillJetSubstructHist(pfRawJt_p, pfRawJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(pfVsJt_p, pfVsJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(pfSKJt_p, pfSKJt_HistQ_p, sType, hiBin_, hatWeight, Qua);

      FillJetSubstructHist(trkRawJt_p, trkRawJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(trkSKJt_p, trkSKJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(trk3CutJt_p, trk3CutJt_HistQ_p, sType, hiBin_, hatWeight, Qua);

      FillJetSubstructHist(genRawJt_p, genRawJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(genSKJt_p, genSKJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(genSUBEJt_p, genSUBEJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(genChgJt_p, genChgJt_HistQ_p, sType, hiBin_, hatWeight, Qua);
      FillJetSubstructHist(genSKChgJt_p, genSKChgJt_HistQ_p, sType, hiBin_, hatWeight, Qua);

      //gluons?
      FillJetSubstructHist(rechitRawJt_p, rechitRawJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(rechitVsJt_p, rechitVsJt_HistG_p, sType, hiBin_, hatWeight, Glu);

      FillJetSubstructHist(pfRawJt_p, pfRawJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(pfVsJt_p, pfVsJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(pfSKJt_p, pfSKJt_HistG_p, sType, hiBin_, hatWeight, Glu);

      FillJetSubstructHist(trkRawJt_p, trkRawJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(trkSKJt_p, trkSKJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(trk3CutJt_p, trk3CutJt_HistG_p, sType, hiBin_, hatWeight, Glu);

      FillJetSubstructHist(genRawJt_p, genRawJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(genSKJt_p, genSKJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(genSUBEJt_p, genSUBEJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(genChgJt_p, genChgJt_HistG_p, sType, hiBin_, hatWeight, Glu);
      FillJetSubstructHist(genSKChgJt_p, genSKChgJt_HistG_p, sType, hiBin_, hatWeight, Glu);
    }
  }

  outFile_p = new TFile(Form("%s.root", outName.c_str()), "UPDATE");
  ScaleHistAll(sType);
  WriteHistAll(outFile_p, sType, algType[setNum]);
  outFile_p->Close();
  delete outFile_p;
  outFile_p = 0;
    
  CleanHistAll(sType);

  return;
}


void makeFastJetHists(const std::string inName, sampleType sType = kHIDATA)
{
  TH1::SetDefaultSumw2();

  std::string outName = inName;
  const std::string cutString[2] = {"AnaSkim", ".root"};
  const std::string repString[2] = {"Hist", ""};
  std::cout << "Replace string" << std::endl;
  for(Int_t iter = 0; iter < 2; iter++){
    std::size_t strIndex = outName.find(cutString[iter]);
    if(!(strIndex == std::string::npos)){
      outName.replace(strIndex, cutString[iter].length(), repString[iter]);
    }
  }

  outFile_p = new TFile(Form("%s.root", outName.c_str()), "RECREATE");
  outFile_p->Close();
  delete outFile_p;

  inFile_p = new TFile(inName.c_str(), "READ");
  InitJtSubstruct();
  GetFastJetAnaSkim(inFile_p, sType);

  std::cout << "AnaSkim Loaded" << std::endl;

  if(isMonteCarlo(sType)) trkTreeAna_p->AddFriend(genTreeAna_p);
  rechitTreeAna_p->AddFriend(trkTreeAna_p);
  pfcandTreeAna_p->AddFriend(rechitTreeAna_p);
  jetTreeAna_p->AddFriend(pfcandTreeAna_p);
  const Int_t algMax = 5;

  std::cout << "Begin the loop" << std::endl;
  
  for(Int_t setIter = 2; setIter < 5; setIter++){
    if(setIter == 2 && !isMonteCarlo(sType)) continue;
    if(setIter == 3) continue;    

    makeJetSubStructHist(jetTreeAna_p, outName, setIter, sType);
  }

  CleanupFastJetAnaSkim();
  CleanupJtSubstruct();

  return;
}

