//Placeholder for FastJetHistMaker

#include <string>
#include "/net/hisrv0001/home/cfmcginn/DijetMPt/CMSSW_5_3_12_patch3/src/DijetInitialSkim/cfmVectFunc.h"
#include "/net/hisrv0001/home/cfmcginn/FastJet/CMSSW_5_3_12_patch3/src/FastJetAnaSkim/cfmFastJetAnaSkim.h"

TFile* inFile_p = 0;
TFile* outFile_p = 0;

const Float_t leadJtCut = 120.;
const Float_t subLeadJtCut = 50.;

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};

std::string getCentString(sampleType sType, Int_t centLow, Int_t centHi)
{
  if(isHI(sType)) return Form("%d%d", (Int_t)(centLow*.5), (Int_t)((centHi+1)*.5));
  else return "PP";
}


Bool_t isEventCut(Int_t setNum, sampleType sType)
{
  if(!eventSet_[setNum]) return true;

  if(AlgJtPt_[setNum][0] < leadJtCut || AlgJtPt_[setNum][1] < subLeadJtCut) return true;

  if(TMath::Abs(AlgJtEta_[setNum][0]) > 1.6 || TMath::Abs(AlgJtEta_[setNum][1]) > 1.6) return true;

  if(AlgJtDelPhi_[setNum] < 5.0*TMath::Pi()/6.0) return true;

  if(isMonteCarlo(sType) && pthat_ < 80) return true;

  return false;
}

/*
void makeTauHist(TTree* anaTree_p, const char* outName, Int_t setNum, sampleType sType = kHIDATA)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);

  Int_t centMax = 1;
  if(hi) centMax = 4;

  const Int_t nTauBins  = 25;
  const Int_t tauLow = 0;
  const Int_t tauHigh = 25000;
  const Int_t centLow[4] = {0, 20, 60, 100};
  const Int_t centHi[4] = {19, 59, 99, 199};

  TH1F* trkTauHist_p[4];
  for(Int_t iter = 0; iter < centMax; iter++){
    trkTauHist_p[iter] = new TH1F(Form("trkTauHist_%d_p", iter), Form("trkTauHist_%d_p", iter), nTauBins, tauLow, tauHi);
    trkTauHist_p[iter]->GetXaxis()->SetLimits(0.00, 25.00);
  }

  for(Int_t jEntry = 0; jEntry < (Int_t)anaTree_p->GetEntries(); jEntry++){
    anaTree_p->GetEntry(jEntry);

    if(jEntry%10000 == 0) std::cout << jEntry << std::endl;

    if(isEventCut(setNum, sType)) continue;

    if(!hi)
      trkTauHist_p[0]->Fill(trkJtRawPt_[0]);
    else{
      for(Int_t centIter = 0; centIter < centMax; centIter++){
	if(hiBin_ >= centLow[centIter] && hiBin_ <= centHi[centIter]){
	  trkTauHist_p[centIter]->Fill(trkRawTau_[setNum][0][1]);
	  break;
	}
      }
    }

  }

  //continue editing

  outFile_p = new TFile(outName, "UPDATE");
  for(Int_t iter = 0; iter < centMax; iter++){
    trkTauHist_p[iter]->Write(Form("%sTrkTauHist_%s_h", algType[setNum], getCentString(sType, centLow[iter], centHi[iter])));
  }
  outFile_p->Close();
  delete outFile_p;
  outFile_p = 0;

  for(Int_t iter = 0; iter < centMax; iter++){
    delete trkTauHist_p[iter];
    trkTauHist_p[iter] = 0;
  }
  return;
}
*/


void makeJetSubStructHist(TTree* anaTree_p, const std::string outName, Int_t setNum, sampleType sType = kHIDATA)
{
  //  const Bool_t montecarlo = isMonteCarlo(sType);                                                         
  const Bool_t hi = isHI(sType);                                                                       
                                                                                               
  Int_t centMax = 1;                                                                             
  if(hi) centMax = 4;
  
  const Int_t nPTDBins  = 100;                                                                            
  const Int_t ptdLow = 0;                                                                                
  const Int_t ptdHigh = 1;
  const Int_t centLow[4] = {0, 20, 60, 100};
  const Int_t centHi[4] = {19, 59, 99, 199};

  TH1F* pfVsPTDHist_p[4];                                                                               
  for(Int_t iter = 0; iter < centMax; iter++){                                           
    pfVsPTDHist_p[iter] = new TH1F(Form("pfVsPTDHist_%d_p", iter), Form("pfVsPTDHist_%d_p", iter), nPTDBins, ptdLow, ptdHigh);   
    pfVsPTDHist_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);                                          
  }

  for(Int_t jEntry = 0; jEntry < (Int_t)anaTree_p->GetEntries(); jEntry++){
    anaTree_p->GetEntry(jEntry);
    if(jEntry%10000 == 0) std::cout << jEntry << std::endl;
    if(isEventCut(setNum, sType)) continue;
    if(!hi)
      pfVsPTDHist_p[0]->Fill(pfJtVsPTD_[0]);                                                                         
    else{
      for(Int_t centIter = 0; centIter < centMax; centIter++){
	if(hiBin_ >= centLow[centIter] && hiBin_ <= centHi[centIter]){
	  pfVsPTDHist_p[centIter]->Fill(pfJtVsPTD_[0]);
	  break; 
	}
      }
    }
  }

  outFile_p = new TFile(outName.c_str(), "UPDATE");
  for(Int_t iter = 0; iter < centMax; iter++){

    const std::string centString = getCentString(sType, centLow[iter], centHi[iter]);
    pfVsPTDHist_p[iter]->Write(Form("%sPFVsPTDHist_%s_h", algType[setNum].c_str(), centString.c_str()));
  }
  outFile_p->Close();
  delete outFile_p;
  outFile_p = 0;
  
  for(Int_t iter = 0; iter < centMax; iter++){
    delete pfVsPTDHist_p[iter];
    pfVsPTDHist_p[iter] = 0;
  }

  return;
}


void makeFastJetHists(const std::string inName, const std::string outName, sampleType sType = kHIDATA)
{
  TH1::SetDefaultSumw2();

  inFile_p = new TFile(inName.c_str(), "READ");
  GetFastJetAnaSkim(inFile_p, sType);

  std::cout << "AnaSkim Loaded" << std::endl;

  jetTreeAna_p->AddFriend(pfcandTreeAna_p);
  Int_t algMax = 2;
  if(isMonteCarlo(sType)) algMax = 3;

  for(Int_t setIter = 0; setIter < algMax; setIter++){
    makeJetSubStructHist(jetTreeAna_p, outName, setIter, sType);
  }

  return;
}

