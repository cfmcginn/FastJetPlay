#include <vector>
#include <string>
#include <fstream>

#include "FastJetAnaSkim.h"
#include "TLorentzVector.h"

//Substructure headers

#include "getPTD.h"
#include "getTau.h"
#include "getAvgDelR.h"
#include "getSigma.h"
#include "getSubJt.h"
#include "getJtFFMoments.h"
#include "getGenAngularity.h"

//Fastjet headers

#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"
#include "fastjet/PseudoJet.hh"

//Dijet cuts

const Float_t lJtPtCut = 120.;
const Float_t sLJtPtCut = 50.;
const Float_t jtEtaCut = 2.0; 

const Float_t clustPtCut = 30.;

//Nsubjettiness var, taus and betas

const Int_t tauArr[nTau] = {1, 2, 3};
const Double_t betaArr[nBeta] = {0.2, 0.5, 1.0, 1.5, 2.0, 3.0};

//Def. set for jet clustering

const Double_t jtR = 0.4;
fastjet::JetAlgorithm jtAlg = fastjet::antikt_algorithm;
fastjet::JetDefinition jtDef(jtAlg, jtR, fastjet::E_scheme, fastjet::Best);
fastjet::AreaDefinition jtAreaDef(fastjet::active_area, fastjet::GhostedAreaSpec(fastjet::SelectorAbsRapMax(2.3)));

//Def. set for rho correction (Jet FFM)

const Double_t rhoJtR = 0.4;
fastjet::JetAlgorithm rhoJtAlg = fastjet::kt_algorithm;

//Def. set for subjet clustering

const Int_t nSubJt = 2;
const Double_t subJtR = 0.1;
fastjet::JetAlgorithm subJtAlg = fastjet::antikt_algorithm;

const Int_t pthatCuts_PYTH_HYD[10] = {15, 30, 50, 80, 120, 170, 220, 280, 370, 10000000};
const Float_t pthatWeights_PYTH_HYD[9] = {.611066, .0399951, .00243874, .000241009, .0000273235, .00000328804, .00000105782, .000000531469, .000000234991};


void getJtSubstrct(fastjet::PseudoJet* inJt, Int_t& outConstN, Float_t& outPTD, Float_t& outR2, Float_t outSigma[nSigma], std::vector<fastjet::PseudoJet>* inBG, Float_t outFFMUnsub[nFFM], Float_t outFFMSub[nFFM], Float_t outFFMSubBetter[nFFM], Float_t tau[nTau][nBeta], Float_t subPt[nSubjet], Float_t subPhi[nSubjet], Float_t subEta[nSubjet])
{
  outConstN = (Int_t)(inJt->constituents().size());
  outPTD = getPTD(inJt);
  outR2 = getAvgDelR(inJt, 2.0);

  calcSigma(inJt);
  for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
    outSigma[sigIter] = getSigma(sigIter);
  }

  getJtFFMoments(inJt, rhoJtR, rhoJtAlg, jtAreaDef, inBG, 14, -0.5, 6.0, outFFMUnsub, outFFMSub, outFFMSubBetter);
  getSubJt(inJt, subJtR, subJtAlg, nSubJt, subPt, subPhi, subEta);
  
  for(Int_t tauIter = 0; tauIter < nTau; tauIter++){
    for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
      tau[tauIter][betaIter] = getTau(inJt, 0.0, tauArr[tauIter], betaArr[betaIter]);
    }
  }
    
  return;
}


void getJt(Int_t nMax, Float_t pt[], Float_t phi[], Float_t eta[], Int_t& nOut, Float_t outPt[maxJets], Float_t outPhi[maxJets], Float_t outEta[maxJets], Int_t outConstN[maxJets], Float_t outPTD[maxJets], Float_t outR2[maxJets], Float_t outSigma[maxJets][nSigma], Float_t outFFMUnsub[maxJets][nFFM], Float_t outFFMSub[maxJets][nFFM], Float_t outFFMSubBetter[maxJets][nFFM], Float_t tau[maxJets][nTau][nBeta], Float_t subPt[maxJets][nSubjet], Float_t subPhi[maxJets][nSubjet], Float_t subEta[maxJets][nSubjet], Float_t ptCut, Int_t inID[], Bool_t IDBool = false)
{
  std::vector<fastjet::PseudoJet>* algVect_p = new std::vector<fastjet::PseudoJet>;
  TLorentzVector tempTL;

  for(Int_t iter = 0; iter < nMax; iter++){
    if(IDBool && inID[iter] != 0) continue;

    if(pt[iter] > ptCut){
       tempTL.SetPtEtaPhiM(pt[iter], eta[iter], phi[iter], 0);
       algVect_p->push_back(tempTL);
    }       
  }

  fastjet::ClusterSequenceArea cs(*algVect_p, jtDef, jtAreaDef);
  std::vector<fastjet::PseudoJet> algSortVect = fastjet::sorted_by_pt(cs.inclusive_jets());

  nOut = 0;

  for(Int_t iter = 0; iter < (Int_t)algSortVect.size(); iter++){
    if(algSortVect[iter].perp() < clustPtCut) break; 
    
    if(TMath::Abs(algSortVect[iter].eta()) < 2.0){
      outPt[nOut] = algSortVect[iter].perp();
      outPhi[nOut] = algSortVect[iter].phi_std();
      outEta[nOut] = algSortVect[iter].eta();

      getJtSubstrct(&algSortVect[iter], outConstN[nOut], outPTD[nOut], outR2[nOut], outSigma[nOut], algVect_p, outFFMUnsub[nOut], outFFMSub[nOut], outFFMSubBetter[nOut], tau[nOut], subPt[nOut], subPhi[nOut], subEta[nOut]);
      nOut++;
      if(nOut == 5) break;
    }
  }

  algSortVect.clear();
  algVect_p->clear();
  delete algVect_p;

  return;
}


void getJtFlavor(Float_t realJtPhi[5], Float_t realJtEta[5], Int_t realJtRefPart[5], Float_t constJtPhi[5], Float_t constJtEta[5], Int_t constJtRefPart[5])
{
  for(Int_t realIter = 0; realIter < 5; realIter++){
    if(realJtPhi[realIter] < -9 || realJtRefPart[realIter] < -900) continue;

    for(Int_t constIter = 0; constIter < 5; constIter++){
      if(constJtRefPart[constIter] > -900 || constJtPhi[constIter] < -9) continue;

      if(getDR(realJtEta[realIter], realJtPhi[realIter], constJtEta[constIter], constJtPhi[constIter]) < 0.3){
	constJtRefPart[constIter] = realJtRefPart[realIter];
	break;
      }
    }

  }

  return;
}

 
int makeFastJetAnaSkim(std::string fList = "", sampleType sType = kHIDATA, Int_t num = 0, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);

  std::cout << sType << std::endl;
  std::cout << montecarlo << std::endl;
  
  std::string buffer;
  std::vector<std::string> listOfFiles;
  Int_t nLines = 0;
  ifstream inFile(fList.data());
  
  std::cout << fList << std::endl;
  std::cout << inFile.is_open() << std::endl;
  
  if(!inFile.is_open()){
    std::cout << "Error opening file. Exiting." << std::endl;
    return 1;
  }
  else{
    while(true){
      inFile >> buffer;
      if(inFile.eof()) break;
      listOfFiles.push_back(buffer);
      nLines++;
    }
  }
  
  std::cout << "FileList Loaded" << std::endl;

  for(Int_t iter = 0; iter < (Int_t)listOfFiles.size(); iter++){
    std::cout << listOfFiles.at(iter) << std::endl;
  }

  TFile* iniSkim_p = new TFile(listOfFiles[num].data(), "READ");
  GetFastJetIniSkim(iniSkim_p, sType, isGen);

  std::cout << "FastJet Skim Loaded" << std::endl;

  std::string outName = listOfFiles[num];
  const std::string cutString = "/";
  const std::string iniString = "Ini";
  std::size_t strIndex = 0;

  std::cout << "Cull string" << std::endl;

  while(true){
    strIndex = outName.find(cutString);

    if(strIndex == std::string::npos) break;

    outName.replace(0, strIndex + 1, "");
  }

  std::cout << "Replace string" << std::endl;

  strIndex = outName.find(iniString);
  if(!(strIndex == std::string::npos)){
    outName.replace(strIndex, iniString.length(), "Ana");
  }

  std::cout << "Output name: " << outName.c_str() << std::endl;

  TFile *outFile_p = new TFile(outName.c_str(), "RECREATE");
  InitFastJetAnaSkim(sType, isGen);

  Long64_t nentries = jetTreeIni_p->GetEntries();

  std::cout << nentries << std::endl;

  Int_t dummyArr[2] = {0,0};

  for(Long64_t jentry = 0; jentry < nentries; jentry++){
    if(jentry%1000 == 0) std::cout << "Entry: " << jentry << std::endl;
    //    std::cout << "Entry: " << jentry << std::endl;

    if(!isGen){
      rechitTreeIni_p->GetEntry(jentry);
      pfcandTreeIni_p->GetEntry(jentry);
      trkTreeIni_p->GetEntry(jentry);
    }
    if(montecarlo) genTreeIni_p->GetEntry(jentry);
    jetTreeIni_p->GetEntry(jentry);

    InitJtVar();

    if(!isGen){
      getJt(nRechits_, rechitPt_, rechitPhi_, rechitEta_, nRechitJtRaw_, rechitJtRawPt_, rechitJtRawPhi_, rechitJtRawEta_, rechitJtRawConstN_, rechitJtRawPTD_ , rechitJtRawR2_, rechitJtRawSigma_, rechitJtRawFFMUnsub_, rechitJtRawFFMSub_, rechitJtRawFFMSubBetter_, rechitRawTau_, rechitSubJtRawPt_, rechitSubJtRawPhi_, rechitSubJtRawEta_, 0.010, dummyArr);
      getJt(nRechits_, rechitVsPt_, rechitPhi_, rechitEta_, nRechitJtVs_, rechitJtVsPt_, rechitJtVsPhi_, rechitJtVsEta_, rechitJtVsConstN_, rechitJtVsPTD_, rechitJtVsR2_, rechitJtVsSigma_, rechitJtVsFFMUnsub_, rechitJtVsFFMSub_, rechitJtVsFFMSubBetter_, rechitVsTau_, rechitSubJtVsPt_, rechitSubJtVsPhi_, rechitSubJtVsEta_, 0.010, dummyArr); 
 
      getJt(nPF_, pfPt_, pfPhi_, pfEta_, nPFJtRaw_, pfJtRawPt_, pfJtRawPhi_, pfJtRawEta_, pfJtRawConstN_, pfJtRawPTD_, pfJtRawR2_, pfJtRawSigma_, pfJtRawFFMUnsub_, pfJtRawFFMSub_, pfJtRawFFMSubBetter_, pfRawTau_, pfSubJtRawPt_, pfSubJtRawPhi_, pfSubJtRawEta_, 0.010, dummyArr);
      getJt(nPF_, pfVsPt_, pfPhi_, pfEta_, nPFJtVs_, pfJtVsPt_, pfJtVsPhi_, pfJtVsEta_, pfJtVsConstN_, pfJtVsPTD_, pfJtVsR2_, pfJtVsSigma_, pfJtVsFFMUnsub_, pfJtVsFFMSub_, pfJtVsFFMSubBetter_, pfVsTau_, pfSubJtVsPt_, pfSubJtVsPhi_, pfSubJtVsEta_, 0.010, dummyArr);
      getJt(nPF_, pfPt_, pfPhi_, pfEta_, nPFJtSK_, pfJtSKPt_, pfJtSKPhi_, pfJtSKEta_, pfJtSKConstN_, pfJtSKPTD_, pfJtSKR2_, pfJtSKSigma_, pfJtSKFFMUnsub_, pfJtSKFFMSub_, pfJtSKFFMSubBetter_, pfSKTau_, pfSubJtSKPt_, pfSubJtSKPhi_, pfSubJtSKEta_, pfIniSKPtCut_, dummyArr);

      getJt(nTrk_, trkPt_, trkPhi_, trkEta_, nTrkJtRaw_, trkJtRawPt_, trkJtRawPhi_, trkJtRawEta_, trkJtRawConstN_, trkJtRawPTD_, trkJtRawR2_, trkJtRawSigma_, trkJtRawFFMUnsub_, trkJtRawFFMSub_, trkJtRawFFMSubBetter_, trkRawTau_, trkSubJtRawPt_, trkSubJtRawPhi_, trkSubJtRawEta_, 0.010, dummyArr);
      getJt(nTrk_, trkPt_, trkPhi_, trkEta_, nTrkJtSK_, trkJtSKPt_, trkJtSKPhi_, trkJtSKEta_, trkJtSKConstN_, trkJtSKPTD_, trkJtSKR2_, trkJtSKSigma_, trkJtSKFFMUnsub_, trkJtSKFFMSub_, trkJtSKFFMSubBetter_, trkSKTau_, trkSubJtSKPt_, trkSubJtSKPhi_, trkSubJtSKEta_, trkIniSKPtCut_, dummyArr);

    }
    if(montecarlo){
      getJt(nGen_, genPt_, genPhi_, genEta_, nGenJtRaw_, genJtRawPt_, genJtRawPhi_, genJtRawEta_, genJtRawConstN_, genJtRawPTD_, genJtRawR2_, genJtRawSigma_, genJtRawFFMUnsub_, genJtRawFFMSub_, genJtRawFFMSubBetter_, genRawTau_, genSubJtRawPt_, genSubJtRawPhi_, genSubJtRawEta_, 0.010, dummyArr);
      getJt(nGen_, genPt_, genPhi_, genEta_, nGenJtSK_, genJtSKPt_, genJtSKPhi_, genJtSKEta_, genJtSKConstN_, genJtSKPTD_, genJtSKR2_, genJtSKSigma_, genJtSKFFMUnsub_, genJtSKFFMSub_, genJtSKFFMSubBetter_, genSKTau_, genSubJtSKPt_, genSubJtSKPhi_, genSubJtSKEta_, genIniSKPtCut_, dummyArr);
      getJt(nGen_, genPt_, genPhi_, genEta_, nGenJtSUBE_, genJtSUBEPt_, genJtSUBEPhi_, genJtSUBEEta_, genJtSUBEConstN_, genJtSUBEPTD_, genJtSUBER2_, genJtSUBESigma_, genJtSUBEFFMUnsub_, genJtSUBEFFMSub_, genJtSUBEFFMSubBetter_, genSUBETau_, genSubJtSUBEPt_, genSubJtSUBEPhi_, genSubJtSUBEEta_, 0.010, genSube_, true);
    }

    run_ = runIni_;
    evt_ = evtIni_;
    lumi_ = lumiIni_;

    if(hi){
      hiBin_ = hiBinIni_;
      if(montecarlo) b_ = bIni_;
    }

    if(montecarlo){
      pthat_ = pthatIni_;
      if(hi){
        for(Int_t hatIter = 0; hatIter < 9; hatIter++){
          if(pthat_ >= pthatCuts_PYTH_HYD[hatIter] && pthat_ < pthatCuts_PYTH_HYD[hatIter + 1]){
            pthatWeight_ = pthatWeights_PYTH_HYD[hatIter];
            break;
          }
        }
      }
    }

    if(hi){
      hiEvtPlane_ = hiEvtPlaneIni_;
      psin_ = psinIni_;
    }

    rechitSKPtCut_ = rechitIniSKPtCut_;
    pfSKPtCut_ = pfIniSKPtCut_;
    trkSKPtCut_ = trkIniSKPtCut_;
    genSKPtCut_ = genIniSKPtCut_;


    for(Int_t algIter = 0; algIter < 5; algIter++){
      if(!montecarlo && algIter == 2) continue;

      for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	AlgJtPt_[algIter][jtIter] = AlgIniJtPt_[algIter][jtIter];
	AlgJtPhi_[algIter][jtIter] = AlgIniJtPhi_[algIter][jtIter];
	AlgJtEta_[algIter][jtIter] = AlgIniJtEta_[algIter][jtIter];
	AlgJtRawPt_[algIter][jtIter] = AlgIniJtRawPt_[algIter][jtIter];

	if(montecarlo){
	  AlgRefPartFlav_[algIter][jtIter] = AlgIniRefPartFlav_[algIter][jtIter];
	  AlgRefPt_[algIter][jtIter] = AlgIniRefPt_[algIter][jtIter];
	  AlgRefPhi_[algIter][jtIter] = AlgIniRefPhi_[algIter][jtIter];
	  AlgRefEta_[algIter][jtIter] = AlgIniRefEta_[algIter][jtIter];
	}
      }

      if(AlgJtPt_[algIter][0] > lJtPtCut && AlgJtPt_[algIter][1] > sLJtPtCut && TMath::Abs(AlgJtEta_[algIter][0]) < jtEtaCut && TMath::Abs(AlgJtEta_[algIter][1]) < jtEtaCut){
	AlgJtDelPhi_[algIter] = TMath::Abs(getDPHI(AlgJtPhi_[algIter][0], AlgJtPhi_[algIter][1]));
	AlgJtAsymm_[algIter] = (AlgJtPt_[algIter][0] - AlgJtPt_[algIter][1])/(AlgJtPt_[algIter][0] + AlgJtPt_[algIter][1]);
	
	if(AlgJtDelPhi_[algIter] > 5*TMath::Pi()/6) eventSet_[algIter] = true;
	else eventSet_[algIter] = false;
      }
      else{
	AlgJtDelPhi_[algIter]  = -10;
	AlgJtAsymm_[algIter] = -10;
	eventSet_[algIter] = false;
      }
    }

    getJtFlavor(AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], pfJtVsPhi_, pfJtVsEta_, pfJtVsRefPart_);
    getJtFlavor(AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], pfJtRawPhi_, pfJtRawEta_, pfJtRawRefPart_);

    if(montecarlo){
      getJtFlavor(AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genJtSUBEPhi_, genJtSUBEEta_, genJtSUBERefPart_);
      getJtFlavor(AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genJtSKPhi_, genJtSKEta_, genJtSKRefPart_);
      getJtFlavor(AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genJtRawPhi_, genJtRawEta_, genJtRawRefPart_);
    }

    if(!isGen){
      rechitTreeAna_p->Fill();
      pfcandTreeAna_p->Fill();
      trkTreeAna_p->Fill();
    }
    if(montecarlo) genTreeAna_p->Fill();
    jetTreeAna_p->Fill();
  }

  if(!isGen){
    rechitTreeAna_p->Write("", TObject::kOverwrite);
    pfcandTreeAna_p->Write("", TObject::kOverwrite);
    trkTreeAna_p->Write("", TObject::kOverwrite);
  }
  if(montecarlo) genTreeAna_p->Write("", TObject::kOverwrite);
  jetTreeAna_p->Write("", TObject::kOverwrite);

  CleanupFastJetAnaSkim();
  outFile_p->Close();
  delete outFile_p;

  iniSkim_p->Close();
  delete iniSkim_p;

  return 0;
}


int main(int argc, char* argv[])
{
  if(argc!=5){
    std::cout << "Usage: jetTestScript <inputFile> <sType> <#> <isGenBool>" << std::endl;
    return 1;
  }

  int rStatus = -1;

  rStatus = makeFastJetAnaSkim(argv[1], sampleType(atoi(argv[2])), atoi(argv[3]), Bool_t(atoi(argv[4])));

  return rStatus;
}
