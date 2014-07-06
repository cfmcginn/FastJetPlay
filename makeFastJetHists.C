//Placeholder for FastJetHistMaker

#include "/net/hisrv0001/home/cfmcginn/DijetMPt/CMSSW_5_3_12_patch3/src/DijetInitialSkim/cfmVectFunc.h"
#include "/net/hisrv0001/home/cfmcginn/FastJet/CMSSW_5_3_12_patch3/src/FastJetAnaSkim/cfmFastJetAnaSkim.h"

TFile* inFile_p = 0;
TFile* outFile_p = 0;

const Float_t leadJtCut = 120.;
const Float_t subLeadJtCut = 50.;


const char* getCentString(sampleType sType, Int_t centLow, Int_t centHi)
{
  if(isHI(sType)) return Form("%d%d", (Int_t)(centLow*.5), (Int_t)((centHi+1)*.5));
  else return "PP";
}


Bool_t isEventCut(Int_t setNum, sampleType sType, Int_t centLow, Int_t centHi)
{
  if(!eventSet_[setNum]) return true;

  if(AlgJtPt_[setNum][0] < leadJtCut || AlgJtPt_[setNum][1] < subLeadJtCut) return true;

  if(isHI(sType)){
    if(hiBin_ < centLow || hiBin_ > centHi) return true;
  }

  if(TMath::Abs(AlgJtEta_[setNum][0]) > 1.6 || TMath::Abs(AlgJtEta_[setNum][1]) > 1.6) return true;

  if(AlgJtDelPhi_[setNum] < 5.0*TMath::Pi()/6.0) return true;

  if(isMonteCarlo(sType) && pthat_ < 80) return true;

  return false;
}


void makeTauHist(TTree* anaTree_p, const char* outName, Int_t setNum, sampleType sType = kHIDATA)
{
  Bool_t montecarlo = isMonteCarlo(sType);

  const Int_t nBins  = 25;
  const Int_t tauLow = 0;
  const Int_t tauHigh = 25000

  const char* centString = getCentString(sType, centLow, centHi);
  TH1F* tauHist_p[4];
  for(Int_t iter = 0; iter < 4; iter++){

  }

  //continue editing

}
