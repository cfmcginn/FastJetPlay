//Placeholder for FastJetHistMaker

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


void makeJetSubStructHist(TTree* anaTree_p, const std::string outName, Int_t setNum, sampleType sType = kHIDATA, const std::string constJtStr, Float_t nConstJt, Float_t constJtPt[], Float_t constJtEta[])
{
  const Bool_t montecarlo = isMonteCarlo(sType);                                                         
  const Bool_t hi = isHI(sType);                                                                       
                                                                                               
  Int_t centMax = 1;                                                                             
  if(hi) centMax = centHIMax;

  const Float_t jtCuts[2] = {100.0, 40.0};

  BookHist(sType, algType[setNum], "PFVs");

  for(Int_t jEntry = 0; jEntry < (Int_t)anaTree_p->GetEntries(); jEntry++){
    anaTree_p->GetEntry(jEntry);
    if(jEntry%10000 == 0) std::cout << jEntry << std::endl;
    if(isEventCut(setNum, sType)) continue;
    if(pthat_ < 50 && montecarlo) continue;

    Float_t hatWeight = 1;
    if(montecarlo) hatWeight = pthatWeight_;

    if(!hi){
      for(Int_t jtIter = 0; jtIter < nPFJtRaw_; jtIter++){
	if(pfJtRawPt_[jtIter] < 60.0) continue;
	if(TMath::Abs(pfJtRawEta_[jtIter] + pPbEtaBoost) > 1.5) continue;

	Bool_t isQuark = TMath::Abs(pfJtRawRefPart_[jtIter]) < 9;
	Bool_t isGluon = TMath::Abs(pfJtRawRefPart_[jtIter]) == 21;

	if(jtIter < 2){
	  ptdHist_Tot_p[0][jtIter]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  if(isQuark) ptdHist_Q_p[0][jtIter]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  else if(isGluon) ptdHist_G_p[0][jtIter]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  else ptdHist_Else_p[0][jtIter]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  
	  for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	    Float_t sig = pfJtRawSigma_[jtIter][sigIter];

	    sigHist_Tot_p[0][jtIter][sigIter]->Fill(sig, hatWeight);
	    if(isQuark) sigHist_Q_p[0][jtIter][sigIter]->Fill(sig, hatWeight);
	    else if(isGluon) sigHist_G_p[0][jtIter][sigIter]->Fill(sig, hatWeight);
	    else sigHist_Else_p[0][jtIter][sigIter]->Fill(sig, hatWeight);
	  }

	  multHist_Tot_p[0][jtIter]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	  if(isQuark) multHist_Q_p[0][jtIter]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	  else if(isGluon) multHist_G_p[0][jtIter]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	  else multHist_Else_p[0][jtIter]->Fill(pfJtRawConstN_[jtIter], hatWeight);

          for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
	    Float_t subRat = pfSubJtRawPt_[jtIter][subJtIter]/pfJtRawPt_[jtIter];

            subRatHist_Tot_p[0][jtIter][subJtIter]->Fill(subRat, hatWeight);
            if(isQuark) subRatHist_Q_p[0][jtIter][subJtIter]->Fill(subRat, hatWeight);
            else if(isGluon) subRatHist_G_p[0][jtIter][subJtIter]->Fill(subRat, hatWeight);
            else subRatHist_Else_p[0][jtIter][subJtIter]->Fill(subRat, hatWeight);
          }

          for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	    Float_t rat21 = pfRawTau_[jtIter][1][betaIter]/pfRawTau_[jtIter][0][betaIter];
	    Float_t rat32 = pfRawTau_[jtIter][2][betaIter]/pfRawTau_[jtIter][1][betaIter];

            tau21Hist_Tot_p[0][jtIter][betaIter]->Fill(rat21, hatWeight);
            if(isQuark) tau21Hist_Q_p[0][jtIter][betaIter]->Fill(rat21, hatWeight);
            else if(isGluon) tau21Hist_G_p[0][jtIter][betaIter]->Fill(rat21, hatWeight);
            else tau21Hist_Else_p[0][jtIter][betaIter]->Fill(rat21, hatWeight);

            tau32Hist_Tot_p[0][jtIter][betaIter]->Fill(rat32, hatWeight);
            if(isQuark) tau32Hist_Q_p[0][jtIter][betaIter]->Fill(rat32, hatWeight);
            else if(isGluon) tau32Hist_G_p[0][jtIter][betaIter]->Fill(rat32, hatWeight);
            else tau32Hist_Else_p[0][jtIter][betaIter]->Fill(rat32, hatWeight);
          }
	}


	//inclusive jet

 	ptdHist_Tot_p[0][2]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	if(isQuark) ptdHist_Q_p[0][2]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	else if(isGluon) ptdHist_G_p[0][2]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	else ptdHist_Else_p[0][2]->Fill(pfJtRawPTD_[jtIter], hatWeight);

	for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	  Float_t sig = pfJtRawSigma_[jtIter][sigIter];

	  sigHist_Tot_p[0][2][sigIter]->Fill(sig, hatWeight);
	  if(isQuark) sigHist_Q_p[0][2][sigIter]->Fill(sig, hatWeight);
	  else if(isGluon) sigHist_G_p[0][2][sigIter]->Fill(sig, hatWeight);
	  else sigHist_Else_p[0][2][sigIter]->Fill(sig, hatWeight);
	}

	multHist_Tot_p[0][2]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	if(isQuark) multHist_Q_p[0][2]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	else if(isGluon) multHist_G_p[0][2]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	else multHist_Else_p[0][2]->Fill(pfJtRawConstN_[jtIter], hatWeight);

	for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
	  Float_t subRat = pfSubJtRawPt_[jtIter][subJtIter]/pfJtRawPt_[jtIter];

	  subRatHist_Tot_p[0][2][subJtIter]->Fill(subRat, hatWeight);
	  if(isQuark) subRatHist_Q_p[0][2][subJtIter]->Fill(subRat, hatWeight);
	  else if(isGluon) subRatHist_G_p[0][2][subJtIter]->Fill(subRat, hatWeight);
	  else subRatHist_Else_p[0][2][subJtIter]->Fill(subRat, hatWeight);
	}
	

	for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	  Float_t rat21 = pfRawTau_[jtIter][1][betaIter]/pfRawTau_[jtIter][0][betaIter];
	  Float_t rat32 = pfRawTau_[jtIter][2][betaIter]/pfRawTau_[jtIter][1][betaIter];
	  
	  tau21Hist_Tot_p[0][2][betaIter]->Fill(rat21, hatWeight);
	  if(isQuark) tau21Hist_Q_p[0][2][betaIter]->Fill(rat21, hatWeight);
	  else if(isGluon) tau21Hist_G_p[0][2][betaIter]->Fill(rat21, hatWeight);
	  else tau21Hist_Else_p[0][2][betaIter]->Fill(rat21, hatWeight);
	  
	  tau32Hist_Tot_p[0][2][betaIter]->Fill(rat32, hatWeight);
	  if(isQuark) tau32Hist_Q_p[0][2][betaIter]->Fill(rat32, hatWeight);
	  else if(isGluon) tau32Hist_G_p[0][2][betaIter]->Fill(rat32, hatWeight);
	  else tau32Hist_Else_p[0][2][betaIter]->Fill(rat32, hatWeight);
	}
	

	//Binned by jet pt

	Int_t ptPos = -1;
	for(Int_t ptIter = 0; ptIter < 5; ptIter++){
	  if(pfJtRawPt_[jtIter] > ptCuts[ptIter] && pfJtRawPt_[jtIter] < ptCuts[ptIter+1]){
	    ptPos = ptPosArr[ptIter];
	    break;
	  }
	}

	if(ptPos >= 0){
	  ptdHist_Tot_p[0][ptPos]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  if(isQuark) ptdHist_Q_p[0][ptPos]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  else if(isGluon) ptdHist_G_p[0][ptPos]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  else ptdHist_Else_p[0][ptPos]->Fill(pfJtRawPTD_[jtIter], hatWeight);
	  
	  for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
	    Float_t sig = pfJtRawSigma_[jtIter][sigIter];

	    sigHist_Tot_p[0][ptPos][sigIter]->Fill(sig, hatWeight);
	    if(isQuark) sigHist_Q_p[0][ptPos][sigIter]->Fill(sig, hatWeight);
	    else if(isGluon) sigHist_G_p[0][ptPos][sigIter]->Fill(sig, hatWeight);
	    else sigHist_Else_p[0][ptPos][sigIter]->Fill(sig, hatWeight);
	  }

	  multHist_Tot_p[0][ptPos]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	  if(isQuark) multHist_Q_p[0][ptPos]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	  else if(isGluon) multHist_G_p[0][ptPos]->Fill(pfJtRawConstN_[jtIter], hatWeight);
	  else multHist_Else_p[0][ptPos]->Fill(pfJtRawConstN_[jtIter], hatWeight);

          for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
            Float_t subRat = pfSubJtRawPt_[jtIter][subJtIter]/pfJtRawPt_[jtIter];

            subRatHist_Tot_p[0][ptPos][subJtIter]->Fill(subRat, hatWeight);
            if(isQuark) subRatHist_Q_p[0][ptPos][subJtIter]->Fill(subRat, hatWeight);
            else if(isGluon) subRatHist_G_p[0][ptPos][subJtIter]->Fill(subRat, hatWeight);
            else subRatHist_Else_p[0][ptPos][subJtIter]->Fill(subRat, hatWeight);
          }

          for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	    Float_t rat21 = pfRawTau_[jtIter][1][betaIter]/pfRawTau_[jtIter][0][betaIter];
	    Float_t rat32 = pfRawTau_[jtIter][2][betaIter]/pfRawTau_[jtIter][1][betaIter];

            tau21Hist_Tot_p[0][ptPos][betaIter]->Fill(rat21, hatWeight);
            if(isQuark) tau21Hist_Q_p[0][ptPos][betaIter]->Fill(rat21, hatWeight);
            else if(isGluon) tau21Hist_G_p[0][ptPos][betaIter]->Fill(rat21, hatWeight);
            else tau21Hist_Else_p[0][ptPos][betaIter]->Fill(rat21, hatWeight);

            tau32Hist_Tot_p[0][ptPos][betaIter]->Fill(rat32, hatWeight);
            if(isQuark) tau32Hist_Q_p[0][ptPos][betaIter]->Fill(rat32, hatWeight);
            else if(isGluon) tau32Hist_G_p[0][ptPos][betaIter]->Fill(rat32, hatWeight);
            else tau32Hist_Else_p[0][ptPos][betaIter]->Fill(rat32, hatWeight);
          }
	}
      }
    }
    else{
      std::cout << "Temp. Placeholder" << std::endl;
    }
  }


  outFile_p = new TFile(Form("%s.root", outName.c_str()), "UPDATE");

  ScaleHistAll(sType);
  WriteHistAll(outFile_p, sType);

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
  GetFastJetAnaSkim(inFile_p, sType);

  std::cout << "AnaSkim Loaded" << std::endl;

  pfcandTreeAna_p->AddFriend(genTreeAna_p);
  jetTreeAna_p->AddFriend(pfcandTreeAna_p);
  Int_t algMax = 5;

  for(Int_t setIter = 4; setIter < 5; setIter++){
    if(setIter == 2 && !isMonteCarlo(sType)) continue;
    if(setIter == 3) continue;    

    makeJetSubStructHist(jetTreeAna_p, outName, setIter, sType);
  }

  return;
}

