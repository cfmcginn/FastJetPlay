//Placeholder for FastJetHistMaker

#include <string>
#include "VectFunc.h"
#include "FastJetAnaSkim.h"

TFile* inFile_p = 0;
TFile* outFile_p = 0;

const Float_t leadJtCut = 120.;
const Float_t subLeadJtCut = 50.;

const Float_t totJtPtCut = 80.;
const Float_t totJtEtaCut = 2.0;

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
  
  const Int_t nPTDBins  = 25;                                                                            
  const Int_t ptdLow = 0;                                                                                
  const Int_t ptdHigh = 1;
  const Int_t centLow[4] = {0, 20, 60, 100};
  const Int_t centHi[4] = {19, 59, 99, 199};

  std::string centString[4];

  TH1F* pfRawPTDHist_Tot_p[4];                                                                
  TH1F* pfRawPTDHist_Q_p[4];                                                                        
  TH1F* pfRawPTDHist_G_p[4];                                                              
  TH1F* pfRawPTDHist_Else_p[4];                                                 

  TH1F* pfVsPTDHist_Tot_p[4];                                                                
  TH1F* pfVsPTDHist_Q_p[4];                                                                        
  TH1F* pfVsPTDHist_G_p[4];                                                              
  TH1F* pfVsPTDHist_Else_p[4];                                                 

  for(Int_t iter = 0; iter < centMax; iter++){                                           
    centString[iter] = getCentString(sType, centLow[iter], centHi[iter]);

    //Raw
    pfRawPTDHist_Tot_p[iter] = new TH1F(Form("%sPFRawPTDHist_Tot_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFRawPTDHist_Tot_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
    pfRawPTDHist_Tot_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);

    pfRawPTDHist_Q_p[iter] = new TH1F(Form("%sPFRawPTDHist_Q_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFRawPTDHist_Q_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
    pfRawPTDHist_Q_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);

    pfRawPTDHist_G_p[iter] = new TH1F(Form("%sPFRawPTDHist_G_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFRawPTDHist_G_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
    pfRawPTDHist_G_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);

    pfRawPTDHist_Else_p[iter] = new TH1F(Form("%sPFRawPTDHist_Else_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFRawPTDHist_Else_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);
    pfRawPTDHist_Else_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);         

    //Vs

    pfVsPTDHist_Tot_p[iter] = new TH1F(Form("%sPFVsPTDHist_Tot_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFVsPTDHist_Tot_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
    pfVsPTDHist_Tot_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);                    

    pfVsPTDHist_Q_p[iter] = new TH1F(Form("%sPFVsPTDHist_Q_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFVsPTDHist_Q_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
    pfVsPTDHist_Q_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);

    pfVsPTDHist_G_p[iter] = new TH1F(Form("%sPFVsPTDHist_G_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFVsPTDHist_G_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
    pfVsPTDHist_G_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);   

    pfVsPTDHist_Else_p[iter] = new TH1F(Form("%sPFVsPTDHist_Else_%s_p", algType[setNum].c_str(), centString[iter].c_str()), Form("%sPFVsPTDHist_Else_%s_p", algType[setNum].c_str(), centString[iter].c_str()), nPTDBins, ptdLow, ptdHigh);   
    pfVsPTDHist_Else_p[iter]->GetXaxis()->SetLimits(ptdLow, ptdHigh);                                          
  }

  Int_t nCentBins = 20;

  TH1F* pfRawPTDHiBinHist_p = new TH1F(Form("%sPFRawPTDHiBinHist_p", algType[setNum].c_str()), Form("%sPFRawPTDHiBinHist_p", algType[setNum].c_str()), nCentBins, -0.5, 199.5);      
  TH1F* pfVsPTDHiBinHist_p = new TH1F(Form("%sPFVsPTDHiBinHist_p", algType[setNum].c_str()), Form("%sPFVsPTDHiBinHist_p",algType[setNum].c_str()), nCentBins, -0.5, 199.5); 

  std::vector<Float_t>* pfRawPTDHiBinVect_p[nCentBins];
  std::vector<Float_t>* pfVsPTDHiBinVect_p[nCentBins];

  if(hi){
    for(Int_t iter = 0; iter < nCentBins; iter++){
      pfRawPTDHiBinVect_p[iter] = new std::vector<Float_t>;
      pfVsPTDHiBinVect_p[iter] = new std::vector<Float_t>;
    }
  }

  for(Int_t jEntry = 0; jEntry < (Int_t)anaTree_p->GetEntries(); jEntry++){
    anaTree_p->GetEntry(jEntry);
    if(jEntry%10000 == 0) std::cout << jEntry << std::endl;
    if(isEventCut(setNum, sType)) continue;
    if(!hi){
      for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	if(pfJtVsPt_[jtIter] < totJtPtCut) break;

	if(TMath::Abs(pfJtVsEta_[jtIter]) > totJtEtaCut) continue;

	pfVsPTDHist_Tot_p[0]->Fill(pfJtVsPTD_[jtIter]);                                                                         

	if(TMath::Abs(pfJtVsRefPart_[jtIter]) < 9) pfVsPTDHist_Q_p[0]->Fill(pfJtVsPTD_[jtIter]);                                                     
	else if(pfJtVsRefPart_[jtIter] == 21) pfVsPTDHist_G_p[0]->Fill(pfJtVsPTD_[jtIter]);                                                       
	else pfVsPTDHist_Else_p[0]->Fill(pfJtVsPTD_[jtIter]);
	  
      }

      for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	if(pfJtRawPt_[jtIter] < totJtPtCut) break;

	if(TMath::Abs(pfJtRawEta_[jtIter]) > totJtEtaCut) continue;

	pfRawPTDHist_Tot_p[0]->Fill(pfJtRawPTD_[jtIter]);                                                                         

	if(TMath::Abs(pfJtRawRefPart_[jtIter]) < 9) pfRawPTDHist_Q_p[0]->Fill(pfJtRawPTD_[jtIter]);                                                     
	else if(pfJtRawRefPart_[jtIter] == 21) pfRawPTDHist_G_p[0]->Fill(pfJtRawPTD_[jtIter]);                                                       
	else pfRawPTDHist_Else_p[0]->Fill(pfJtRawPTD_[jtIter]);
	  
      }
    }
    else{
      for(Int_t centIter = 0; centIter < centMax; centIter++){
	if(hiBin_ >= centLow[centIter] && hiBin_ <= centHi[centIter]){

	  for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	    if(pfJtVsPt_[jtIter] < totJtPtCut) break;

	    if(TMath::Abs(pfJtVsEta_[jtIter]) > totJtEtaCut) continue;

	    pfVsPTDHist_Tot_p[centIter]->Fill(pfJtVsPTD_[jtIter]);

	    if(TMath::Abs(pfJtVsRefPart_[jtIter]) < 9) pfVsPTDHist_Q_p[centIter]->Fill(pfJtVsPTD_[jtIter]);
	    else if(pfJtVsRefPart_[jtIter] == 21) pfVsPTDHist_G_p[centIter]->Fill(pfJtVsPTD_[jtIter]);
	    else pfVsPTDHist_Else_p[centIter]->Fill(pfJtVsPTD_[jtIter]);

	  }

	  for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	    if(pfJtRawPt_[jtIter] < totJtPtCut) break;

	    if(TMath::Abs(pfJtRawEta_[jtIter]) > totJtEtaCut) continue;

	    pfRawPTDHist_Tot_p[centIter]->Fill(pfJtRawPTD_[jtIter]);

	    if(TMath::Abs(pfJtRawRefPart_[jtIter]) < 9) pfRawPTDHist_Q_p[centIter]->Fill(pfJtRawPTD_[jtIter]);
	    else if(pfJtRawRefPart_[jtIter] == 21) pfRawPTDHist_G_p[centIter]->Fill(pfJtRawPTD_[jtIter]);
	    else pfRawPTDHist_Else_p[centIter]->Fill(pfJtRawPTD_[jtIter]);

	  }
	  break; 
	}
      }
    
      for(Int_t centIter = 0; centIter < nCentBins; centIter++){
	if(hiBin_ < centIter*200./nCentBins){

	  for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	    if(pfJtRawPt_[jtIter] < totJtPtCut) break;

            if(TMath::Abs(pfJtRawEta_[jtIter]) > totJtEtaCut) continue;

	    pfRawPTDHiBinVect_p[centIter]->push_back(pfJtRawPTD_[jtIter]);
	  }

	  for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	    if(pfJtVsPt_[jtIter] < totJtPtCut) break;

            if(TMath::Abs(pfJtVsEta_[jtIter]) > totJtEtaCut) continue;

	    pfVsPTDHiBinVect_p[centIter]->push_back(pfJtVsPTD_[jtIter]);
	  }

	  break;
	}
      } 
    }
  }

  if(hi){
    for(Int_t centIter = 0; centIter < nCentBins; centIter++){
      Float_t mean = getMean(pfVsPTDHiBinVect_p[centIter]);
      pfVsPTDHiBinHist_p->SetBinContent(centIter + 1, mean);
      pfVsPTDHiBinHist_p->SetBinError(centIter + 1, getError(pfVsPTDHiBinVect_p[centIter], mean));

      mean = getMean(pfRawPTDHiBinVect_p[centIter]);
      pfRawPTDHiBinHist_p->SetBinContent(centIter + 1, mean);
      pfRawPTDHiBinHist_p->SetBinError(centIter + 1, getError(pfRawPTDHiBinVect_p[centIter], mean));
    }
  }

  outFile_p = new TFile(outName.c_str(), "UPDATE");
  for(Int_t iter = 0; iter < centMax; iter++){
    pfVsPTDHist_Q_p[iter]->Scale(1./pfVsPTDHist_Tot_p[iter]->Integral());
    pfVsPTDHist_Q_p[iter]->Write(Form("%sPFVsPTDHist_Q_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);

    pfVsPTDHist_G_p[iter]->Scale(1./pfVsPTDHist_Tot_p[iter]->Integral());
    pfVsPTDHist_G_p[iter]->Write(Form("%sPFVsPTDHist_G_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);

    pfVsPTDHist_Else_p[iter]->Scale(1./pfVsPTDHist_Tot_p[iter]->Integral());
    pfVsPTDHist_Else_p[iter]->Write(Form("%sPFVsPTDHist_Else_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);

    pfVsPTDHist_Tot_p[iter]->Scale(1./pfVsPTDHist_Tot_p[iter]->Integral());
    pfVsPTDHist_Tot_p[iter]->Write(Form("%sPFVsPTDHist_Tot_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);

    pfRawPTDHist_Q_p[iter]->Scale(1./pfRawPTDHist_Tot_p[iter]->Integral());
    pfRawPTDHist_Q_p[iter]->Write(Form("%sPFRawPTDHist_Q_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);

    pfRawPTDHist_G_p[iter]->Scale(1./pfRawPTDHist_Tot_p[iter]->Integral());
    pfRawPTDHist_G_p[iter]->Write(Form("%sPFRawPTDHist_G_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);

    pfRawPTDHist_Else_p[iter]->Scale(1./pfRawPTDHist_Tot_p[iter]->Integral());
    pfRawPTDHist_Else_p[iter]->Write(Form("%sPFRawPTDHist_Else_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);

    pfRawPTDHist_Tot_p[iter]->Scale(1./pfRawPTDHist_Tot_p[iter]->Integral());
    pfRawPTDHist_Tot_p[iter]->Write(Form("%sPFRawPTDHist_Tot_%s_h", algType[setNum].c_str(), centString[iter].c_str()), TObject::kOverwrite);
  }

  if(hi){
    pfRawPTDHiBinHist_p->Write("", TObject::kOverwrite);
    pfVsPTDHiBinHist_p->Write("", TObject::kOverwrite);
  }

  outFile_p->Close();
  delete outFile_p;
  outFile_p = 0;
  
  for(Int_t iter = 0; iter < centMax; iter++){
    delete pfVsPTDHist_Tot_p[iter];
    pfVsPTDHist_Tot_p[iter] = 0;

    delete pfVsPTDHist_Q_p[iter];
    pfVsPTDHist_Q_p[iter] = 0;

    delete pfVsPTDHist_G_p[iter];
    pfVsPTDHist_G_p[iter] = 0;

    delete pfVsPTDHist_Else_p[iter];
    pfVsPTDHist_Else_p[iter] = 0;

    delete pfRawPTDHist_Tot_p[iter];
    pfRawPTDHist_Tot_p[iter] = 0;

    delete pfRawPTDHist_Q_p[iter];
    pfRawPTDHist_Q_p[iter] = 0;

    delete pfRawPTDHist_G_p[iter];
    pfRawPTDHist_G_p[iter] = 0;

    delete pfRawPTDHist_Else_p[iter];
    pfRawPTDHist_Else_p[iter] = 0;
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

  jetTreeAna_p->AddFriend(pfcandTreeAna_p);
  Int_t algMax = 5;

  for(Int_t setIter = 0; setIter < algMax; setIter++){
    if(!isMonteCarlo(sType) && setIter == 2) continue;
    
    makeJetSubStructHist(jetTreeAna_p, outName, setIter, sType);
  }

  return;
}

