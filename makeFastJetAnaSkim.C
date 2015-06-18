#include <vector>
#include <string>
#include <fstream>

#include "FastJetAnaSkim.h"
#include "TLorentzVector.h"

//Substructure headers

#include "getPTD.h"
#include "getJtCharge.h"
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


#include "fastjet/contrib/SoftDrop.hh"

//Dijet cuts

const Float_t lJtPtCut = 120.;
const Float_t sLJtPtCut = 50.;
const Float_t jtEtaCut = 2.0; 

const Float_t pPbEtaBoost = 0.4654094531;

const Float_t clustPtCut = 30.;

//Nsubjettiness var, taus and betas

/*
const Int_t tauArr[nTau] = {1, 2, 3};
const Double_t betaArr[nBeta] = {0.2, 0.5, 1.0, 1.5, 2.0, 3.0};
const Double_t betaSDArr[nSDBeta] = {-0.5, -0.1, 0.0, 0.1, 0.5};
const Double_t betaChgArr[nChgBeta] = {0.3, 0.5, 1.0, 1.5, 2.0};
*/
//Def. set for jet clustering

const Double_t jtR = 0.4;
fastjet::JetAlgorithm jtAlg = fastjet::antikt_algorithm;
fastjet::JetDefinition jtDef(jtAlg, jtR, fastjet::E_scheme, fastjet::Best);
fastjet::AreaDefinition jtAreaDef(fastjet::active_area, fastjet::GhostedAreaSpec(fastjet::SelectorAbsRapMax(5.0)));

//Def. set for rho correction (Jet FFM)

const Double_t rhoJtR = 0.4;
fastjet::JetAlgorithm rhoJtAlg = fastjet::kt_algorithm;

//Def. set for subjet clustering

const Double_t subJtR = 0.1;
fastjet::JetAlgorithm subJtAlg = fastjet::antikt_algorithm;

const Int_t pthatCuts_PYTH_HYD[11] = {15, 30, 50, 80, 100, 120, 170, 220, 280, 370, 10000000};
const Float_t pthatWeights_PYTH_HYD[10] = {.611066, .0374106, .00232016, .00014917, .0000822379, .0000142819, .00000296162, .00000102099, .000000522123, .000000232907};


const Int_t pthatCuts_PYTH_HIJ[10] = {15, 30, 50, 80, 120, 170, 220, 280, 370, 1000000000};
const Float_t pthatWeights_PYTH_HIJ[9] = {.803486, .800737, .0115077, .0012741, .000235174, .0000321983, .00000629003, .00000202126, .000000573347};

const Int_t pthatCuts_PYTH_PPTrk[7] = {15, 30, 50, 80, 120, 170, 1000000};
const Float_t pthatWeights_PYTH_PPTrk[6] = {.161482, .00749461, .000752396, .0000837038, .0000101988, .00000175206};


void getJtSubstrct(fastjet::PseudoJet* inJt, JetSubstruct* outJet_p, std::vector<fastjet::PseudoJet>* inBG)
{
  outJet_p->jtConstN_[outJet_p->nJt_] = (Int_t)(inJt->constituents().size());
  outJet_p->jtPTD_[outJet_p->nJt_] = getPTD(inJt);

  for(Int_t iter = 0; iter < nChgBeta; iter++){
    outJet_p->jtChg_[outJet_p->nJt_][iter] = getJtCharge(inJt, betaChgArr[iter]);
  }

  outJet_p->jtR2_[outJet_p->nJt_] = getAvgDelR(inJt, 2.0);

  calcSigma(inJt);
  for(Int_t sigIter = 0; sigIter < nSigma; sigIter++){
    outJet_p->jtSigma_[outJet_p->nJt_][sigIter] = getSigma(sigIter);
  }

  getJtFFMoments(inJt, rhoJtR, rhoJtAlg, jtAreaDef, inBG, 14, -0.5, 6.0, outJet_p->jtFFMUnsub_[outJet_p->nJt_], outJet_p->jtFFMSub_[outJet_p->nJt_], outJet_p->jtFFMSubBetter_[outJet_p->nJt_]);
  getSubJt(inJt, subJtR, subJtAlg, nSubjet, outJet_p->subJtPt_[outJet_p->nJt_], outJet_p->subJtPhi_[outJet_p->nJt_], outJet_p->subJtEta_[outJet_p->nJt_]);
  
  for(Int_t tauIter = 0; tauIter < nTau; tauIter++){
    for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
      outJet_p->jtTau_[outJet_p->nJt_][tauIter][betaIter] = getTau(inJt, 0.0, tauArr[tauIter], betaArr[betaIter]);
    }
  }
    
  return;
}


void getJt(Int_t nMax, Float_t pt[], Float_t phi[], Float_t eta[], Int_t chg[], Bool_t isChg, JetSubstruct* outJet_p, Float_t ptCut, Int_t inID[], Bool_t IDBool, Bool_t chgJet)
{
  Int_t nAlgVect = 0;
  std::vector<fastjet::PseudoJet>* algVect_p = new std::vector<fastjet::PseudoJet>;
  TLorentzVector tempTL;

  for(Int_t iter = 0; iter < nMax; iter++){
    if(IDBool && inID[iter] != 0) continue;

    if(chgJet && chg[iter] == 0) continue;

    if(pt[iter] > ptCut){
       tempTL.SetPtEtaPhiM(pt[iter], eta[iter], phi[iter], 0);
       algVect_p->push_back(tempTL);
       if(isChg) algVect_p->at(nAlgVect).set_user_index(chg[iter]);
       else algVect_p->at(nAlgVect).set_user_index(0);
       nAlgVect++;
    }       
  }

  // fastjet::ClusterSequence cs(*algVect_p, jtDef);
  fastjet::ClusterSequenceArea cs(*algVect_p, jtDef, jtAreaDef);
  //  fastjet::ClusterSequence csNoArea = fastjet::ClusterSequence(cs);
  std::vector<fastjet::PseudoJet> algSortVect = fastjet::sorted_by_pt(cs.inclusive_jets());

  outJet_p->nJt_ = 0;

  const Double_t zCut = 0.10;
  fastjet::contrib::SoftDrop* sd[nSDBeta];
  for(Int_t iter = 0; iter < nSDBeta; iter++){
    sd[iter] = new fastjet::contrib::SoftDrop(betaSDArr[iter], zCut);
    if(betaSDArr[iter] < 0) sd[iter]->set_tagging_mode();
    sd[iter]->set_verbose_structure();
  }

  for(Int_t iter = 0; iter < (Int_t)algSortVect.size(); iter++){
    if(algSortVect[iter].perp() < clustPtCut) break; 
    
    if(TMath::Abs(algSortVect[iter].eta()) < 2.0){
      outJet_p->jtPt_[outJet_p->nJt_] = algSortVect[iter].perp();
      outJet_p->jtPhi_[outJet_p->nJt_] = algSortVect[iter].phi_std();
      outJet_p->jtEta_[outJet_p->nJt_] = algSortVect[iter].eta();

      for(Int_t iter2 = 0; iter2 < nSDBeta; iter2++){
	fastjet::PseudoJet tempSDJt = (*sd[iter2])(algSortVect[iter]);
	if(tempSDJt == 0.0) continue;
	outJet_p->jtSoftPt_[outJet_p->nJt_][iter2] = tempSDJt.perp();
	outJet_p->jtSoftSymmZ_[outJet_p->nJt_][iter2] = tempSDJt.structure_of<fastjet::contrib::SoftDrop>().symmetry();
      }

      getJtSubstrct(&algSortVect[iter], outJet_p, algVect_p);

      outJet_p->nJt_++;
      if(outJet_p->nJt_ == 5) break;
    }
  }

  for(Int_t iter = 0; iter < nSDBeta; iter++){
    delete sd[iter];
  }

  algSortVect.clear();
  algVect_p->clear();
  delete algVect_p;

  return;
}


void getJtMatch(Float_t realJtPt[5], Float_t realJtPhi[5], Float_t realJtEta[5], Int_t realJtRefPart[5], JetSubstruct* outJet_p, Bool_t isMC)
{
  for(Int_t constIter = 0; constIter < outJet_p->nJt_; constIter++){
    outJet_p->jtMatchIndex_[constIter] = -1;
    if(isMC) outJet_p->jtRefPart_[constIter] = -990;
  }    

  for(Int_t realIter = 0; realIter < 5; realIter++){
    if(realJtPhi[realIter] < -9) continue;

    for(Int_t constIter = 0; constIter < outJet_p->nJt_; constIter++){
      if(outJet_p->jtMatchIndex_[constIter] != -1 || outJet_p->jtPhi_[constIter] < -9) continue;

      if(getDR(realJtEta[realIter], realJtPhi[realIter], outJet_p->jtEta_[constIter], outJet_p->jtPhi_[constIter]) < 0.4){
	outJet_p->jtMatchIndex_[constIter] = realIter;
	outJet_p->jtMatchPt_[constIter] = realJtPt[realIter];
	outJet_p->jtMatchPhi_[constIter] = realJtPhi[realIter];
	outJet_p->jtMatchEta_[constIter] = realJtEta[realIter];
	if(isMC) outJet_p->jtRefPart_[constIter] = realJtRefPart[realIter];
	break;
      }
    }
  }

  return;
}


void getSubJtScalePt(JetSubstruct* outJet_p)
{
  for(Int_t iter = 0; iter < outJet_p->nJt_; iter++){
    if(outJet_p->jtMatchIndex_[iter] == -1) continue;
    for(Int_t subIter = 0; subIter < nSubjet; subIter++){
      outJet_p->subJtScalePt_[iter][subIter] = outJet_p->subJtPt_[iter][subIter]*(outJet_p->jtMatchPt_[iter]/outJet_p->jtPt_[iter]);
    }
  }

  return;
}

 
int makeFastJetAnaSkim(std::string fList = "", sampleType sType = kHIDATA, Int_t num = 0, Bool_t isGen = false)
{
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);
  Bool_t pa = isPA(sType);

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
  InitJtSubstruct();
  InitFastJetAnaSkim(sType, isGen);

  Long64_t nentries = jetTreeIni_p->GetEntries();

  std::cout << nentries << std::endl;

  Int_t dummyArr[2] = {0,0};

  for(Long64_t jentry = 0; jentry < nentries; jentry++){
    if(jentry%10 == 0) std::cout << "Entry: " << jentry << std::endl;
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
      getJt(nRechits_, rechitPt_, rechitPhi_, rechitEta_, dummyArr, false, rechitRawJt_p, 0.010, dummyArr, false, false);
      if(hi) getJt(nRechits_, rechitVsPt_, rechitPhi_, rechitEta_, dummyArr, false, rechitVsJt_p, 0.010, dummyArr, false, false); 
 
      getJt(nPF_, pfPt_, pfPhi_, pfEta_, dummyArr, false, pfRawJt_p, 0.010, dummyArr, false, false);
      if(hi) getJt(nPF_, pfVsPt_, pfPhi_, pfEta_, dummyArr, false, pfVsJt_p, 0.010, dummyArr, false, false);
      getJt(nPF_, pfPt_, pfPhi_, pfEta_, dummyArr, false, pfSKJt_p, pfIniSKPtCut_, dummyArr, false, false);

      getJt(nTrk_, trkPt_, trkPhi_, trkEta_, trkChg_, true, trkRawJt_p, 0.010, dummyArr, false, false);
      getJt(nTrk_, trkPt_, trkPhi_, trkEta_, trkChg_, true, trkSKJt_p, trkIniSKPtCut_, dummyArr, false, false);
      getJt(nTrk_, trkPt_, trkPhi_, trkEta_, trkChg_, true, trk3CutJt_p, 3.0, dummyArr, false, false);
    }
    if(montecarlo){
      getJt(nGen_, genPt_, genPhi_, genEta_, genChg_, true, genRawJt_p, 0.010, dummyArr, false, false);
      getJt(nGen_, genPt_, genPhi_, genEta_, genChg_, true, genSKJt_p, genIniSKPtCut_, dummyArr, false, false);
      getJt(nGen_, genPt_, genPhi_, genEta_, genChg_, true, genSUBEJt_p, 0.010, genSube_, true, false);
      getJt(nGen_, genPt_, genPhi_, genEta_, genChg_, true, genRawChgJt_p, 0.010, dummyArr, false, true);
      getJt(nGen_, genPt_, genPhi_, genEta_, genChg_, true, genSKChgJt_p, genIniSKChgPtCut_, dummyArr, false, true);
      getJt(nGen_, genPt_, genPhi_, genEta_, genChg_, true, genSUBEChgJt_p, 0.010, genSube_, true, true);
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
        for(Int_t hatIter = 0; hatIter < 10; hatIter++){
          if(pthat_ >= pthatCuts_PYTH_HYD[hatIter] && pthat_ < pthatCuts_PYTH_HYD[hatIter + 1]){
            pthatWeight_ = pthatWeights_PYTH_HYD[hatIter];
            break;
          }
        }
      }
      else if(pa){
	for(Int_t hatIter = 0; hatIter < 9; hatIter++){
	  if(pthat_ >= pthatCuts_PYTH_HIJ[hatIter] && pthat_ < pthatCuts_PYTH_HIJ[hatIter + 1]){
	    pthatWeight_ = pthatWeights_PYTH_HIJ[hatIter];
	    break;
	  }
	}
      }
      else{
	for(Int_t hatIter = 0; hatIter < 6; hatIter++){
          if(pthat_ >= pthatCuts_PYTH_PPTrk[hatIter] && pthat_ < pthatCuts_PYTH_PPTrk[hatIter + 1]){
            pthatWeight_ = pthatWeights_PYTH_PPTrk[hatIter];
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
    genSKChgPtCut_ = genIniSKChgPtCut_;


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

      if(!pa && AlgJtPt_[algIter][0] > lJtPtCut && AlgJtPt_[algIter][1] > sLJtPtCut && TMath::Abs(AlgJtEta_[algIter][0]) < jtEtaCut && TMath::Abs(AlgJtEta_[algIter][1]) < jtEtaCut){
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

    getJtMatch(AlgJtPt_[VsCalo], AlgJtPhi_[VsCalo], AlgJtEta_[VsCalo], AlgRefPartFlav_[VsCalo], rechitRawJt_p, montecarlo);
    if(hi) getJtMatch(AlgJtPt_[VsCalo], AlgJtPhi_[VsCalo], AlgJtEta_[VsCalo], AlgRefPartFlav_[VsCalo], rechitVsJt_p, montecarlo);
    
    getJtMatch(AlgJtPt_[VsPF], AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], pfRawJt_p, montecarlo);
    if(hi) getJtMatch(AlgJtPt_[VsPF], AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], pfVsJt_p, montecarlo);
    getJtMatch(AlgJtPt_[VsPF], AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], pfSKJt_p, montecarlo);
    
    getJtMatch(AlgJtPt_[VsPF], AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], trkRawJt_p, montecarlo);
    getJtMatch(AlgJtPt_[VsPF], AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], trkSKJt_p, montecarlo);
    getJtMatch(AlgJtPt_[VsPF], AlgJtPhi_[VsPF], AlgJtEta_[VsPF], AlgRefPartFlav_[VsPF], trk3CutJt_p, montecarlo);

    if(montecarlo){
      getJtMatch(AlgJtPt_[T], AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genSUBEJt_p, montecarlo);
      getJtMatch(AlgJtPt_[T], AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genSKJt_p, montecarlo);
      getJtMatch(AlgJtPt_[T], AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genRawJt_p, montecarlo);
      getJtMatch(AlgJtPt_[T], AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genRawChgJt_p, montecarlo);
      getJtMatch(AlgJtPt_[T], AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genSKChgJt_p, montecarlo);
      getJtMatch(AlgJtPt_[T], AlgJtPhi_[T], AlgJtEta_[T], AlgRefPartFlav_[T], genSUBEChgJt_p, montecarlo);
    }

    getSubJtScalePt(rechitRawJt_p);
    if(hi) getSubJtScalePt(rechitVsJt_p);

    getSubJtScalePt(pfRawJt_p);
    if(hi) getSubJtScalePt(pfVsJt_p);
    getSubJtScalePt(pfSKJt_p);

    getSubJtScalePt(trkRawJt_p);
    getSubJtScalePt(trkSKJt_p);
    getSubJtScalePt(trk3CutJt_p);

    if(montecarlo){
      getSubJtScalePt(genRawJt_p);
      getSubJtScalePt(genSKJt_p);
      getSubJtScalePt(genSUBEJt_p);
      getSubJtScalePt(genRawChgJt_p);
      getSubJtScalePt(genSKChgJt_p);
      getSubJtScalePt(genSUBEChgJt_p);
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
  CleanupJtSubstruct();

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
