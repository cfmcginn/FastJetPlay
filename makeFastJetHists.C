//Placeholder for FastJetHistMaker

#include <string>
#include "VectFunc.h"
#include "FastJetAnaSkim.h"

TFile* inFile_p = 0;
TFile* outFile_p = 0;

const Float_t leadJtCut = 120.;
const Float_t subLeadJtCut = 50.;

const Float_t totJtPtCut = 50.;
const Float_t totJtEtaCut = 2.0;
const Float_t totJtAjCut = 0.22;

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};

Int_t ptHatCuts_PYTHHYD[4] = {80, 100, 120, 1000000};
Float_t ptHatWeights_PYTHHYD[3] = {.342827, .106555, .0279868};


Float_t getHatWeight(Float_t inHat)
{
  for(Int_t iter = 0; iter < 3; iter++){
    if(inHat > ptHatCuts_PYTHHYD[iter] && inHat < ptHatCuts_PYTHHYD[iter + 1]){
      return ptHatWeights_PYTHHYD[iter];
    }
  }

  std::cout << inHat << std::endl;
  std::cout << "No weight assigned; check for error." << std::endl;
  return 0;
}


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


void makeJetSubStructHist(TTree* anaTree_p, const std::string outName, Int_t setNum, sampleType sType = kHIDATA)
{
  const Bool_t montecarlo = isMonteCarlo(sType);                                                         
  const Bool_t hi = isHI(sType);                                                                       
                                                                                               
  Int_t centMax = 1;                                                                             
  if(hi) centMax = 4;
  
  const Int_t nPTDBins  = 20;                                                                            
  const Float_t ptdLow = 0.0001;                                                                                
  const Float_t ptdHigh = 0.9999;

  const Int_t nSubBins  = 25;                                                                            
  const Int_t subLow = 0;                                                                                
  const Int_t subHigh = 1;

  const Int_t nTauBins = 10;
  const Float_t TauLow = 0.0001;
  const Float_t TauHigh = 0.9999;

  const Int_t centLow[4] = {0, 20, 60, 100};
  const Int_t centHi[4] = {19, 59, 99, 199};

  const Float_t bLow[4] = {0.00000, 8.48859, 11.6098, 13.9928};
  const Float_t bHi[4] = {8.48859, 11.6098, 13.9928, 20.0000};

  std::string centString[4];
  const std::string LeadSubLead[2] = {"Leading", "Subleading"};

  TH1F* pfRawPTDHist_Tot_p[4][2];                                                                
  TH1F* pfRawPTDHist_Q_p[4][2];                                                                        
  TH1F* pfRawPTDHist_G_p[4][2];                                                              
  TH1F* pfRawPTDHist_Else_p[4][2];                                                 

  TH1F* pfVsPTDHist_Tot_p[4][2];                                                                
  TH1F* pfVsPTDHist_Q_p[4][2];                                                                        
  TH1F* pfVsPTDHist_G_p[4][2];                                                              
  TH1F* pfVsPTDHist_Else_p[4][2];                                                 

  TH1F* pfVsTauHist_Tot_p[4][2];                                                                
  TH1F* pfVsTauHist_Q_p[4][2];                                                                        
  TH1F* pfVsTauHist_G_p[4][2];                                                              
  TH1F* pfVsTauHist_Else_p[4][2];                                                 

  TH1F* pfRawSubRatHist_Tot_p[4][2][2];
  TH1F* pfVsSubRatHist_Tot_p[4][2][2];


  TH1F* genRawPTDHist_Tot_p[4][2];                                                                
  TH1F* genRawPTDHist_Q_p[4][2];                                                                        
  TH1F* genRawPTDHist_G_p[4][2];                                                              
  TH1F* genRawPTDHist_Else_p[4][2];                                                 

  TH1F* genSUBEPTDHist_Tot_p[4][2];                                                                
  TH1F* genSUBEPTDHist_Q_p[4][2];                                                                        
  TH1F* genSUBEPTDHist_G_p[4][2];                                                              
  TH1F* genSUBEPTDHist_Else_p[4][2];                                                 

  TH1F* genRawTauHist_Tot_p[4][2];                                                                
  TH1F* genRawTauHist_Q_p[4][2];                                                                        
  TH1F* genRawTauHist_G_p[4][2];                                                              
  TH1F* genRawTauHist_Else_p[4][2];                                                 

  TH1F* genSUBETauHist_Tot_p[4][2];                                                                
  TH1F* genSUBETauHist_Q_p[4][2];                                                                        
  TH1F* genSUBETauHist_G_p[4][2];                                                              
  TH1F* genSUBETauHist_Else_p[4][2];                                                 

  for(Int_t iter = 0; iter < centMax; iter++){                                           
    centString[iter] = getCentString(sType, centLow[iter], centHi[iter]);

   for(Int_t subIter = 0; subIter < 2; subIter++){
      //Raw
      pfRawPTDHist_Tot_p[iter][subIter] = new TH1F(Form("%sPFRawPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFRawPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      pfRawPTDHist_Tot_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      pfRawPTDHist_Q_p[iter][subIter] = new TH1F(Form("%sPFRawPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFRawPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      pfRawPTDHist_Q_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      pfRawPTDHist_G_p[iter][subIter] = new TH1F(Form("%sPFRawPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFRawPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      pfRawPTDHist_G_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      pfRawPTDHist_Else_p[iter][subIter] = new TH1F(Form("%sPFRawPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFRawPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      pfRawPTDHist_Else_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);         
      
      //Vs
      
      pfVsPTDHist_Tot_p[iter][subIter] = new TH1F(Form("%sPFVsPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      pfVsPTDHist_Tot_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);                    
      
      pfVsPTDHist_Q_p[iter][subIter] = new TH1F(Form("%sPFVsPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      pfVsPTDHist_Q_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      pfVsPTDHist_G_p[iter][subIter] = new TH1F(Form("%sPFVsPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      pfVsPTDHist_G_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);   
      
      pfVsPTDHist_Else_p[iter][subIter] = new TH1F(Form("%sPFVsPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      pfVsPTDHist_Else_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);                            

      //Nsubjettiness beta = 0.5

      pfVsTauHist_Tot_p[iter][subIter] = new TH1F(Form("%sPFVsTau21%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsTau21%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      pfVsTauHist_Tot_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);                    
      
      pfVsTauHist_Q_p[iter][subIter] = new TH1F(Form("%sPFVsTau21%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsTau21%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      pfVsTauHist_Q_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);
      
      pfVsTauHist_G_p[iter][subIter] = new TH1F(Form("%sPFVsTau21%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsTau21%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      pfVsTauHist_G_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);   
      
      pfVsTauHist_Else_p[iter][subIter] = new TH1F(Form("%sPFVsTau21%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsTau21%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      pfVsTauHist_Else_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);                           
              

      //RatHist

      for(Int_t subIter2 = 0; subIter2 < 2; subIter2++){
	pfRawSubRatHist_Tot_p[iter][subIter][subIter2] = new TH1F(Form("%sPFRawSub%dRat%s_%s_h", algType[setNum].c_str(), subIter2 + 1, LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFRawSub%dRat%s_%s_h", algType[setNum].c_str(), subIter2 + 1, LeadSubLead[subIter].c_str(), centString[iter].c_str()), nSubBins, subLow, subHigh);
	pfRawSubRatHist_Tot_p[iter][subIter][subIter2]->GetXaxis()->SetLimits(subLow, subHigh);
	
	pfVsSubRatHist_Tot_p[iter][subIter][subIter2] = new TH1F(Form("%sPFVsSub%dRat%s_%s_h", algType[setNum].c_str(), subIter2 + 1, LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sPFVsSub%dRat%s_%s_h", algType[setNum].c_str(), subIter2 + 1, LeadSubLead[subIter].c_str(), centString[iter].c_str()), nSubBins, subLow, subHigh);
	pfVsSubRatHist_Tot_p[iter][subIter][subIter2]->GetXaxis()->SetLimits(subLow, subHigh);
      }
	//Gen PTD

      genRawPTDHist_Tot_p[iter][subIter] = new TH1F(Form("%sGENRawPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      genRawPTDHist_Tot_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      genRawPTDHist_Q_p[iter][subIter] = new TH1F(Form("%sGENRawPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      genRawPTDHist_Q_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      genRawPTDHist_G_p[iter][subIter] = new TH1F(Form("%sGENRawPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      genRawPTDHist_G_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      genRawPTDHist_Else_p[iter][subIter] = new TH1F(Form("%sGENRawPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
      genRawPTDHist_Else_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);         
      
      //SK PTD
      
      genSUBEPTDHist_Tot_p[iter][subIter] = new TH1F(Form("%sGENSUBEPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBEPTD%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      genSUBEPTDHist_Tot_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);                    
      
      genSUBEPTDHist_Q_p[iter][subIter] = new TH1F(Form("%sGENSUBEPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBEPTD%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      genSUBEPTDHist_Q_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);
      
      genSUBEPTDHist_G_p[iter][subIter] = new TH1F(Form("%sGENSUBEPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBEPTD%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      genSUBEPTDHist_G_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);   
      
      genSUBEPTDHist_Else_p[iter][subIter] = new TH1F(Form("%sGENSUBEPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBEPTD%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
      genSUBEPTDHist_Else_p[iter][subIter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);                        


      //GEN Nsubjettiness beta = 0.5 RAW

      genRawTauHist_Tot_p[iter][subIter] = new TH1F(Form("%sGENRawTau21%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawTau21%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genRawTauHist_Tot_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);                    
      
      genRawTauHist_Q_p[iter][subIter] = new TH1F(Form("%sGENRawTau21%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawTau21%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genRawTauHist_Q_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);
      
      genRawTauHist_G_p[iter][subIter] = new TH1F(Form("%sGENRawTau21%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawTau21%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genRawTauHist_G_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);   
      
      genRawTauHist_Else_p[iter][subIter] = new TH1F(Form("%sGENRawTau21%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENRawTau21%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genRawTauHist_Else_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);                      

      //GEN Nsubjettiness beta = 0.5 SK

      genSUBETauHist_Tot_p[iter][subIter] = new TH1F(Form("%sGENSUBETau21%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBETau21%s_Tot_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genSUBETauHist_Tot_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);                    
      
      genSUBETauHist_Q_p[iter][subIter] = new TH1F(Form("%sGENSUBETau21%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBETau21%s_Q_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genSUBETauHist_Q_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);
      
      genSUBETauHist_G_p[iter][subIter] = new TH1F(Form("%sGENSUBETau21%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBETau21%s_G_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genSUBETauHist_G_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);   
      
      genSUBETauHist_Else_p[iter][subIter] = new TH1F(Form("%sGENSUBETau21%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), Form("%sGENSUBETau21%s_Else_%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), centString[iter].c_str()), nTauBins, TauLow, TauHigh);   
      genSUBETauHist_Else_p[iter][subIter]->GetXaxis()->SetLimits(TauLow, TauHigh);                         
   }
  }

  Int_t nCentBins = 10;

  TH1F* pfRawPTDHiBinHist_p[2];      
  TH1F* pfVsPTDHiBinHist_p[2]; 
  TH1F* pfRawPTDHiBinMean_p[nCentBins][2];
  TH1F* pfVsPTDHiBinMean_p[nCentBins][2];

  if(hi){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      pfRawPTDHiBinHist_p[subIter] = new TH1F(Form("%sPFRawPTDHiBin%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str()), Form("%sPFRawPTDHiBin%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str()), nCentBins, -0.5, 199.5);
      pfVsPTDHiBinHist_p[subIter] = new TH1F(Form("%sPFVsPTDHiBin%s_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str()), Form("%sPFVsPTDHiBin%s_h",algType[setNum].c_str(), LeadSubLead[subIter].c_str()), nCentBins, -0.5, 199.5);

      for(Int_t iter = 0; iter < nCentBins; iter++){
	pfRawPTDHiBinMean_p[iter][subIter] = new TH1F(Form("%sPFRawPTDHiBinMean%s_%d_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), iter), Form("%sPFRawPTDHiBinMean%s_%d_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), iter), 100, 0, 1);
	pfVsPTDHiBinMean_p[iter][subIter] = new TH1F(Form("%sPFVsPTDHiBinMean%s_%d_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), iter), Form("%sPFVsPTDHiBinMean%s_%d_h", algType[setNum].c_str(), LeadSubLead[subIter].c_str(), iter), 100, 0, 1);
      }
    }
  }

  for(Int_t jEntry = 0; jEntry < (Int_t)anaTree_p->GetEntries(); jEntry++){
    anaTree_p->GetEntry(jEntry);
    if(jEntry%10000 == 0) std::cout << jEntry << std::endl;
    if(isEventCut(setNum, sType)) continue;

    Float_t hatWeight = 1;

    if(montecarlo) hatWeight = pthatWeight_;

    //    if(AlgJtAsymm_[setNum] < totJtAjCut) continue;

    if(!hi){

      for(Int_t subIter = 0; subIter < 2; subIter++){
	if(TMath::Abs(pfJtVsEta_[subIter]) < totJtEtaCut && pfJtVsPt_[subIter] > totJtPtCut){

	  pfVsPTDHist_Tot_p[0][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);                             
 
	  if(TMath::Abs(pfJtVsRefPart_[subIter]) < 9) pfVsPTDHist_Q_p[0][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);         
	  else if(pfJtVsRefPart_[subIter] == 21) pfVsPTDHist_G_p[0][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);   
	  else pfVsPTDHist_Else_p[0][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);  
	}
      
	if(TMath::Abs(pfJtRawEta_[subIter]) < totJtEtaCut && pfJtRawPt_[subIter] > totJtPtCut){

	  pfRawPTDHist_Tot_p[0][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);                                                      
	  if(TMath::Abs(pfJtRawRefPart_[subIter]) < 9) pfRawPTDHist_Q_p[0][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);           
	  else if(pfJtRawRefPart_[subIter] == 21) pfRawPTDHist_G_p[0][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight); 
	  else pfRawPTDHist_Else_p[0][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);	
	}
      }
    }
    else{
      for(Int_t centIter = 0; centIter < centMax; centIter++){
	if(b_ >= bLow[centIter] && b_ <= bHi[centIter]){

	  for(Int_t subIter = 0; subIter < 2; subIter++){
	    if(TMath::Abs(pfJtVsEta_[subIter]) < totJtEtaCut && pfJtVsPt_[subIter] > totJtPtCut){
	      
	      pfVsPTDHist_Tot_p[centIter][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);
	      pfVsTauHist_Tot_p[centIter][subIter]->Fill(pfVsTau_[subIter][1][4]/pfVsTau_[subIter][0][4], hatWeight);

	      for(Int_t subIter2 = 0; subIter2 < 2; subIter2++){
		if(pfJtVsPt_[subIter] > 100 && pfSubJtVsPt_[subIter][subIter2] > 50) pfVsSubRatHist_Tot_p[centIter][subIter][subIter2]->Fill(pfSubJtVsPt_[subIter][subIter2]/pfJtVsPt_[subIter], hatWeight);
	      }      

	      if(TMath::Abs(pfJtVsRefPart_[subIter]) < 9){
		pfVsPTDHist_Q_p[centIter][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);
		pfVsTauHist_Q_p[centIter][subIter]->Fill(pfVsTau_[subIter][1][4]/pfVsTau_[subIter][0][4], hatWeight);
	      }
	      else if(pfJtVsRefPart_[subIter] == 21){
		pfVsPTDHist_G_p[centIter][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);
		pfVsTauHist_G_p[centIter][subIter]->Fill(pfVsTau_[subIter][1][4]/pfVsTau_[subIter][0][4], hatWeight);
	      }
	      else{
		pfVsPTDHist_Else_p[centIter][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight); 
		pfVsTauHist_Else_p[centIter][subIter]->Fill(pfVsTau_[subIter][1][4]/pfVsTau_[subIter][0][4], hatWeight);
	      }
	    }

	    if(TMath::Abs(genJtSUBEEta_[subIter]) < totJtEtaCut && genJtSUBEPt_[subIter] > totJtPtCut){
	     
	      genSUBEPTDHist_Tot_p[centIter][subIter]->Fill(genJtSUBEPTD_[subIter], hatWeight);
	      genSUBETauHist_Tot_p[centIter][subIter]->Fill(genSUBETau_[subIter][1][2]/genSUBETau_[subIter][0][2], hatWeight);


	      if(TMath::Abs(genJtSUBERefPart_[subIter]) < 9){
		genSUBEPTDHist_Q_p[centIter][subIter]->Fill(genJtSUBEPTD_[subIter], hatWeight);
		genSUBETauHist_Q_p[centIter][subIter]->Fill(genSUBETau_[subIter][1][2]/genSUBETau_[subIter][0][2], hatWeight);
	      }
	      else if(genJtSUBERefPart_[subIter] == 21){
		genSUBEPTDHist_G_p[centIter][subIter]->Fill(genJtSUBEPTD_[subIter], hatWeight);
		genSUBETauHist_G_p[centIter][subIter]->Fill(genSUBETau_[subIter][1][2]/genSUBETau_[subIter][0][2], hatWeight);
	      }
	      else{
		genSUBEPTDHist_Else_p[centIter][subIter]->Fill(genJtSUBEPTD_[subIter], hatWeight); 
		genSUBETauHist_Else_p[centIter][subIter]->Fill(genSUBETau_[subIter][1][2]/genSUBETau_[subIter][0][2], hatWeight);
	      }
	    }
	  
	    if(TMath::Abs(pfJtRawEta_[subIter]) < totJtEtaCut && pfJtRawPt_[subIter] > totJtPtCut){
	      
	      pfRawPTDHist_Tot_p[centIter][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);

	      for(Int_t subIter2 = 0; subIter2 < 2; subIter2++){
		if(pfJtRawPt_[subIter] > 50) pfRawSubRatHist_Tot_p[centIter][subIter][subIter2]->Fill(pfSubJtRawPt_[subIter][subIter2]/pfJtRawPt_[subIter], hatWeight);
	      }	      

	      if(TMath::Abs(pfJtRawRefPart_[subIter]) < 9) pfRawPTDHist_Q_p[centIter][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);
	      else if(pfJtRawRefPart_[subIter] == 21) pfRawPTDHist_G_p[centIter][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);
	      else pfRawPTDHist_Else_p[centIter][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);
	    }

	    if(TMath::Abs(genJtRawEta_[subIter]) < totJtEtaCut && genJtRawPt_[subIter] > totJtPtCut){
	      
	      genRawPTDHist_Tot_p[centIter][subIter]->Fill(genJtRawPTD_[subIter], hatWeight);
	      genRawTauHist_Tot_p[centIter][subIter]->Fill(genRawTau_[subIter][1][2]/genRawTau_[subIter][0][2], hatWeight);

	      if(TMath::Abs(genJtRawRefPart_[subIter]) < 9) genRawPTDHist_Q_p[centIter][subIter]->Fill(genJtRawPTD_[subIter], hatWeight);
	      else if(genJtRawRefPart_[subIter] == 21) genRawPTDHist_G_p[centIter][subIter]->Fill(genJtRawPTD_[subIter], hatWeight);
	      else genRawPTDHist_Else_p[centIter][subIter]->Fill(genJtRawPTD_[subIter], hatWeight);
	    }
	  }	
	  
	  break; 
	}
      }
    
      for(Int_t centIter = 0; centIter < nCentBins; centIter++){
	if(hiBin_ < (centIter+1)*200./nCentBins){

	  for(Int_t subIter = 0; subIter < 2; subIter++){

	    if(TMath::Abs(pfJtRawEta_[subIter]) < totJtEtaCut && pfJtRawPt_[subIter] > totJtPtCut)
	      pfRawPTDHiBinMean_p[centIter][subIter]->Fill(pfJtRawPTD_[subIter], hatWeight);
	    
	    if(TMath::Abs(pfJtVsEta_[subIter]) < totJtEtaCut && pfJtVsPt_[subIter] > totJtPtCut)
	      pfVsPTDHiBinMean_p[centIter][subIter]->Fill(pfJtVsPTD_[subIter], hatWeight);
	  }

	  break;
	}
      }
    }
  }


  if(hi){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      for(Int_t centIter = 0; centIter < nCentBins; centIter++){
	pfVsPTDHiBinHist_p[subIter]->SetBinContent(centIter + 1, pfVsPTDHiBinMean_p[centIter][subIter]->GetMean());
	pfVsPTDHiBinHist_p[subIter]->SetBinError(centIter + 1, pfVsPTDHiBinMean_p[centIter][subIter]->GetMeanError());
	
	pfRawPTDHiBinHist_p[subIter]->SetBinContent(centIter + 1, pfRawPTDHiBinMean_p[centIter][subIter]->GetMean());
	pfRawPTDHiBinHist_p[subIter]->SetBinError(centIter + 1, pfRawPTDHiBinMean_p[centIter][subIter]->GetMeanError());
      }
    }
  }

  outFile_p = new TFile(outName.c_str(), "UPDATE");
  for(Int_t iter = 0; iter < centMax; iter++){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      /*
      pfVsPTDHist_Q_p[iter][subIter]->Scale(1./pfVsPTDHist_Tot_p[iter][subIter]->Integral());
      pfVsPTDHist_Q_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      pfVsPTDHist_G_p[iter][subIter]->Scale(1./pfVsPTDHist_Tot_p[iter][subIter]->Integral());
      pfVsPTDHist_G_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      pfVsPTDHist_Else_p[iter][subIter]->Scale(1./pfVsPTDHist_Tot_p[iter][subIter]->Integral());
      pfVsPTDHist_Else_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      pfVsPTDHist_Tot_p[iter][subIter]->Scale(1./pfVsPTDHist_Tot_p[iter][subIter]->Integral());
      pfVsPTDHist_Tot_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      pfRawPTDHist_Q_p[iter][subIter]->Scale(1./pfRawPTDHist_Tot_p[iter][subIter]->Integral());
      pfRawPTDHist_Q_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      pfRawPTDHist_G_p[iter][subIter]->Scale(1./pfRawPTDHist_Tot_p[iter][subIter]->Integral());
      pfRawPTDHist_G_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      pfRawPTDHist_Else_p[iter][subIter]->Scale(1./pfRawPTDHist_Tot_p[iter][subIter]->Integral());
      pfRawPTDHist_Else_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      pfRawPTDHist_Tot_p[iter][subIter]->Scale(1./pfRawPTDHist_Tot_p[iter][subIter]->Integral());
      pfRawPTDHist_Tot_p[iter][subIter]->Write("", TObject::kOverwrite);
      */
      genSUBEPTDHist_Q_p[iter][subIter]->Scale(1./genSUBEPTDHist_Tot_p[iter][subIter]->Integral());
      genSUBEPTDHist_Q_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      genSUBEPTDHist_G_p[iter][subIter]->Scale(1./genSUBEPTDHist_Tot_p[iter][subIter]->Integral());
      genSUBEPTDHist_G_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      genSUBEPTDHist_Else_p[iter][subIter]->Scale(1./genSUBEPTDHist_Tot_p[iter][subIter]->Integral());
      genSUBEPTDHist_Else_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      genSUBEPTDHist_Tot_p[iter][subIter]->Scale(1./genSUBEPTDHist_Tot_p[iter][subIter]->Integral());
      genSUBEPTDHist_Tot_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      genRawPTDHist_Q_p[iter][subIter]->Scale(1./genRawPTDHist_Tot_p[iter][subIter]->Integral());
      genRawPTDHist_Q_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      genRawPTDHist_G_p[iter][subIter]->Scale(1./genRawPTDHist_Tot_p[iter][subIter]->Integral());
      genRawPTDHist_G_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      genRawPTDHist_Else_p[iter][subIter]->Scale(1./genRawPTDHist_Tot_p[iter][subIter]->Integral());
      genRawPTDHist_Else_p[iter][subIter]->Write("", TObject::kOverwrite);
      
      genRawPTDHist_Tot_p[iter][subIter]->Scale(1./genRawPTDHist_Tot_p[iter][subIter]->Integral());
      genRawPTDHist_Tot_p[iter][subIter]->Write("", TObject::kOverwrite);


      //Tau
      /*
      pfVsTauHist_Q_p[iter][subIter]->Scale(1./pfVsTauHist_Tot_p[iter][subIter]->Integral());
      pfVsTauHist_Q_p[iter][subIter]->Write("", TObject::kOverwrite);

      pfVsTauHist_G_p[iter][subIter]->Scale(1./pfVsTauHist_Tot_p[iter][subIter]->Integral());
      pfVsTauHist_G_p[iter][subIter]->Write("", TObject::kOverwrite);

      pfVsTauHist_Else_p[iter][subIter]->Scale(1./pfVsTauHist_Tot_p[iter][subIter]->Integral());
      pfVsTauHist_Else_p[iter][subIter]->Write("", TObject::kOverwrite);

      pfVsTauHist_Tot_p[iter][subIter]->Scale(1./pfVsTauHist_Tot_p[iter][subIter]->Integral());
      pfVsTauHist_Tot_p[iter][subIter]->Write("", TObject::kOverwrite);
      */
      genSUBETauHist_Q_p[iter][subIter]->Scale(1./genSUBETauHist_Tot_p[iter][subIter]->Integral());
      genSUBETauHist_Q_p[iter][subIter]->Write("", TObject::kOverwrite);

      genSUBETauHist_G_p[iter][subIter]->Scale(1./genSUBETauHist_Tot_p[iter][subIter]->Integral());
      genSUBETauHist_G_p[iter][subIter]->Write("", TObject::kOverwrite);

      genSUBETauHist_Else_p[iter][subIter]->Scale(1./genSUBETauHist_Tot_p[iter][subIter]->Integral());
      genSUBETauHist_Else_p[iter][subIter]->Write("", TObject::kOverwrite);

      genSUBETauHist_Tot_p[iter][subIter]->Scale(1./genSUBETauHist_Tot_p[iter][subIter]->Integral());
      genSUBETauHist_Tot_p[iter][subIter]->Write("", TObject::kOverwrite);

      genRawTauHist_Q_p[iter][subIter]->Scale(1./genRawTauHist_Tot_p[iter][subIter]->Integral());
      genRawTauHist_Q_p[iter][subIter]->Write("", TObject::kOverwrite);

      genRawTauHist_G_p[iter][subIter]->Scale(1./genRawTauHist_Tot_p[iter][subIter]->Integral());
      genRawTauHist_G_p[iter][subIter]->Write("", TObject::kOverwrite);

      genRawTauHist_Else_p[iter][subIter]->Scale(1./genRawTauHist_Tot_p[iter][subIter]->Integral());
      genRawTauHist_Else_p[iter][subIter]->Write("", TObject::kOverwrite);

      genRawTauHist_Tot_p[iter][subIter]->Scale(1./genRawTauHist_Tot_p[iter][subIter]->Integral());
      genRawTauHist_Tot_p[iter][subIter]->Write("", TObject::kOverwrite);

      
      //Sub Rat
      for(Int_t subIter2 = 0; subIter2 < 2; subIter2++){
	/*
	pfRawSubRatHist_Tot_p[iter][subIter][subIter2]->Scale(1./pfRawSubRatHist_Tot_p[iter][subIter][subIter2]->Integral());
	pfRawSubRatHist_Tot_p[iter][subIter][subIter2]->Write("", TObject::kOverwrite);
	
	pfVsSubRatHist_Tot_p[iter][subIter][subIter2]->Scale(1./pfVsSubRatHist_Tot_p[iter][subIter][subIter2]->Integral());
	pfVsSubRatHist_Tot_p[iter][subIter][subIter2]->Write("", TObject::kOverwrite);
	*/
      }
    }
  }

  if(hi){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      /*
      pfRawPTDHiBinHist_p[subIter]->Write("", TObject::kOverwrite);
      pfVsPTDHiBinHist_p[subIter]->Write("", TObject::kOverwrite);
      */
    }
  }

  outFile_p->Close();
  delete outFile_p;
  outFile_p = 0;
  
  for(Int_t iter = 0; iter < centMax; iter++){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      delete pfVsPTDHist_Tot_p[iter][subIter];
      pfVsPTDHist_Tot_p[iter][subIter] = 0;
      
      delete pfVsPTDHist_Q_p[iter][subIter];
      pfVsPTDHist_Q_p[iter][subIter] = 0;
      
      delete pfVsPTDHist_G_p[iter][subIter];
      pfVsPTDHist_G_p[iter][subIter] = 0;
      
      delete pfVsPTDHist_Else_p[iter][subIter];
      pfVsPTDHist_Else_p[iter][subIter] = 0;
      
      delete pfRawPTDHist_Tot_p[iter][subIter];
      pfRawPTDHist_Tot_p[iter][subIter] = 0;
      
      delete pfRawPTDHist_Q_p[iter][subIter];
      pfRawPTDHist_Q_p[iter][subIter] = 0;
      
      delete pfRawPTDHist_G_p[iter][subIter];
      pfRawPTDHist_G_p[iter][subIter] = 0;
      
      delete pfRawPTDHist_Else_p[iter][subIter];
      pfRawPTDHist_Else_p[iter][subIter] = 0;


      delete genSUBEPTDHist_Tot_p[iter][subIter];
      genSUBEPTDHist_Tot_p[iter][subIter] = 0;
      
      delete genSUBEPTDHist_Q_p[iter][subIter];
      genSUBEPTDHist_Q_p[iter][subIter] = 0;
      
      delete genSUBEPTDHist_G_p[iter][subIter];
      genSUBEPTDHist_G_p[iter][subIter] = 0;
      
      delete genSUBEPTDHist_Else_p[iter][subIter];
      genSUBEPTDHist_Else_p[iter][subIter] = 0;
      
      delete genRawPTDHist_Tot_p[iter][subIter];
      genRawPTDHist_Tot_p[iter][subIter] = 0;
      
      delete genRawPTDHist_Q_p[iter][subIter];
      genRawPTDHist_Q_p[iter][subIter] = 0;
      
      delete genRawPTDHist_G_p[iter][subIter];
      genRawPTDHist_G_p[iter][subIter] = 0;
      
      delete genRawPTDHist_Else_p[iter][subIter];
      genRawPTDHist_Else_p[iter][subIter] = 0;



      //Tau

      delete pfVsTauHist_Tot_p[iter][subIter];
      pfVsTauHist_Tot_p[iter][subIter] = 0;

      delete pfVsTauHist_Q_p[iter][subIter];
      pfVsTauHist_Q_p[iter][subIter] = 0;

      delete pfVsTauHist_G_p[iter][subIter];
      pfVsTauHist_G_p[iter][subIter] = 0;

      delete pfVsTauHist_Else_p[iter][subIter];
      pfVsTauHist_Else_p[iter][subIter] = 0;

      delete genSUBETauHist_Tot_p[iter][subIter];
      genSUBETauHist_Tot_p[iter][subIter] = 0;

      delete genSUBETauHist_Q_p[iter][subIter];
      genSUBETauHist_Q_p[iter][subIter] = 0;

      delete genSUBETauHist_G_p[iter][subIter];
      genSUBETauHist_G_p[iter][subIter] = 0;

      delete genSUBETauHist_Else_p[iter][subIter];
      genSUBETauHist_Else_p[iter][subIter] = 0;

      delete genRawTauHist_Tot_p[iter][subIter];
      genRawTauHist_Tot_p[iter][subIter] = 0;

      delete genRawTauHist_Q_p[iter][subIter];
      genRawTauHist_Q_p[iter][subIter] = 0;

      delete genRawTauHist_G_p[iter][subIter];
      genRawTauHist_G_p[iter][subIter] = 0;

      delete genRawTauHist_Else_p[iter][subIter];
      genRawTauHist_Else_p[iter][subIter] = 0;

      //SubRat

      for(Int_t subIter2 = 0; subIter2 < 2; subIter2++){
	delete pfRawSubRatHist_Tot_p[iter][subIter][subIter2];
	pfRawSubRatHist_Tot_p[iter][subIter][subIter2] = 0;
	
	delete pfVsSubRatHist_Tot_p[iter][subIter][subIter2];
	pfVsSubRatHist_Tot_p[iter][subIter][subIter2] = 0;
      }
    }
  }
    
  for(Int_t iter = 0; iter < nCentBins; iter++){
    for(Int_t subIter = 0; subIter < 2; subIter++){
      delete pfRawPTDHiBinMean_p[iter][subIter];
      pfRawPTDHiBinMean_p[iter][subIter] = 0;
      
      delete pfVsPTDHiBinMean_p[iter][subIter];
      pfVsPTDHiBinMean_p[iter][subIter] = 0;
    }
  }


  for(Int_t iter = 0; iter < 2; iter++){
    delete pfRawPTDHiBinHist_p[iter];
    pfRawPTDHiBinHist_p[iter] = 0;

    delete pfVsPTDHiBinHist_p[iter];
    pfVsPTDHiBinHist_p[iter] = 0;
  }

  return;
}


void makeFastJetHists(const std::string inName, const std::string outName, sampleType sType = kHIDATA)
{
  TH1::SetDefaultSumw2();

  outFile_p = new TFile(outName.c_str(), "RECREATE");
  outFile_p->Close();
  delete outFile_p;

  inFile_p = new TFile(inName.c_str(), "READ");
  GetFastJetAnaSkim(inFile_p, sType);

  std::cout << "AnaSkim Loaded" << std::endl;

  pfcandTreeAna_p->AddFriend(genTreeAna_p);
  jetTreeAna_p->AddFriend(pfcandTreeAna_p);
  Int_t algMax = 5;

  for(Int_t setIter = 2; setIter < 3; setIter++){
    
    makeJetSubStructHist(jetTreeAna_p, outName, setIter, sType);
  }

  return;
}

