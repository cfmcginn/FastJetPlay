#include "FastJetAnaSkim.h"
#include <fstream>
#include "TLorentzVector.h"
#include <vector>
#include <string>

#include "etaPhiFunc.h"
#include "getPTD.h"
#include "getTau.h"
#include "getAvgDelR.h"
#include "getSigma.h"

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"

const Float_t lJtPtCut = 120.;
const Float_t sLJtPtCut = 50.;
const Float_t jtEtaCut = 2.0; 

const Int_t tauArr[nTau] = {1, 2, 3};
const Double_t betaArr[nBeta] = {0.2, 0.5, 1.0, 1.5, 2.0, 3.0};

const Double_t jtR = 0.4;
fastjet::JetAlgorithm jtAlg = fastjet::antikt_algorithm;
fastjet::JetDefinition jtDef(jtAlg, jtR, fastjet::E_scheme, fastjet::Best);

const Double_t subJtR = 0.1;
fastjet::JetAlgorithm subJtAlg = fastjet::antikt_algorithm;
fastjet::JetDefinition subJtDef(subJtAlg, subJtR, fastjet::E_scheme, fastjet::Best);

void getSubJt(fastjet::PseudoJet inJt, Float_t subPt[2], Float_t subPhi[2], Float_t subEta[2])
{
  fastjet::ClusterSequence subCS(inJt.constituents(), subJtDef);
  std::vector<fastjet::PseudoJet> subJets = subCS.inclusive_jets();

  if(subJets.size() != 0){
    subPt[0] = subJets[0].perp();
    subPhi[0] = subJets[0].phi_std();
    subEta[0] = subJets[0].eta();

    if(subJets.size() != 1){
      subPt[1] = subJets[1].perp();
      subPhi[1] = subJets[1].phi_std();
      subEta[1] = subJets[1].eta();
    }
  }    

  subJets.clear();
  return;
}


void getJt(Int_t nMax, Float_t pt[], Float_t phi[], Float_t eta[], Float_t outPt[5], Float_t outPhi[5], Float_t outEta[5], Float_t outPTD[5], Float_t outR2[5], Float_t outSigma[5][3], Float_t tau[5][nTau][nBeta], Float_t subPt[5][nSubjet], Float_t subPhi[5][nSubjet], Float_t subEta[5][nSubjet], Float_t ptCut)
{
  std::vector<fastjet::PseudoJet>* algVect_p = new std::vector<fastjet::PseudoJet>;
  TLorentzVector tempTL;

  for(Int_t iter = 0; iter < nMax; iter++){
    if(pt[iter] > ptCut){
       tempTL.SetPtEtaPhiM(pt[iter], eta[iter], phi[iter], 0);
       algVect_p->push_back(tempTL);
    }       
  }

  fastjet::ClusterSequence cs(*algVect_p, jtDef);
  std::vector<fastjet::PseudoJet> algSortVect = sorted_by_pt(cs.inclusive_jets());

  Int_t breakIter = 0;

  for(Int_t iter = 0; iter < (Int_t)algSortVect.size(); iter++){
    if(TMath::Abs(algSortVect[iter].eta()) < 2.0){
      outPt[breakIter] = algSortVect[iter].perp();
      outPhi[breakIter] = algSortVect[iter].phi_std();
      outEta[breakIter] = algSortVect[iter].eta();

      outPTD[breakIter] = getPTD(algSortVect[iter]);
      outR2[breakIter] = getAvgDelR(algSortVect[iter], 30.0, 2.0);
      calcSigma(algSortVect[iter]);
      for(Int_t sigIter = 0; sigIter < 3; sigIter++){
	outSig[breakIter][sigIter] = getSigma(sigIter);
      }

      getSubJt(algSortVect[iter], subPt[breakIter], subPhi[breakIter], subEta[breakIter]);

      for(Int_t tauIter = 0; tauIter < nTau; tauIter++){
	for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	  tau[breakIter][tauIter][betaIter] = getTau(algSortVect[iter], 0.0, tauArr[tauIter], betaArr[betaIter]);
	}
      }

      if(breakIter == 4) break;

      breakIter++;
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

 
int makeFastJetAnaSkim(std::string fList = "", sampleType sType = kHIDATA, const char* outName = "defaultName_FASTJETSKIM.root", Bool_t isGen = false)
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

  TFile* iniSkim_p = new TFile(listOfFiles[0].data(), "READ");
  GetFastJetIniSkim(iniSkim_p, sType, isGen);

  std::cout << "FastJet Skim Loaded" << std::endl;

  TFile *outFile_p = new TFile(Form("%s.root", outName), "RECREATE");
  InitFastJetAnaSkim(sType, isGen);

  Long64_t nentries = jetTreeIni_p->GetEntries();

  std::cout << nentries << std::endl;

  for(Long64_t jentry = 0; jentry < nentries; jentry++){
    if(jentry%1000 == 0) std::cout << "Entry: " << jentry << std::endl;

    if(!isGen){
      rechitTreeIni_p->GetEntry(jentry);
      pfcandTreeIni_p->GetEntry(jentry);
      trkTreeIni_p->GetEntry(jentry);
    }
    if(montecarlo) genTreeIni_p->GetEntry(jentry);
    jetTreeIni_p->GetEntry(jentry);

    InitJtVar();

    if(!isGen){
      getJt(nRechits_, rechitPt_, rechitPhi_, rechitEta_, rechitJtRawPt_, rechitJtRawPhi_, rechitJtRawEta_, rechitJtRawPTD_ , rechitJtRawR2_, rechitJtRawSigma_, rechitRawTau_, rechitSubJtRawPt_, rechitSubJtRawPhi_, rechitSubJtRawEta_, 0.010);
      getJt(nRechits_, rechitVsPt_, rechitPhi_, rechitEta_, rechitJtVsPt_, rechitJtVsPhi_, rechitJtVsEta_, rechitJtVsPTD_, rechitJtVsR2_, rechitJtVsSigma_, rechitVsTau_, rechitSubJtVsPt_, rechitSubJtVsPhi_, rechitSubJtVsEta_, 0.010);
      getJt(nPF_, pfPt_, pfPhi_, pfEta_, pfJtRawPt_, pfJtRawPhi_, pfJtRawEta_, pfJtRawPTD_, pfJtRawR2_, pfJtRawSigma_, pfRawTau_, pfSubJtRawPt_, pfSubJtRawPhi_, pfSubJtRawEta_, 0.010);
      getJt(nPF_, pfVsPt_, pfPhi_, pfEta_, pfJtVsPt_, pfJtVsPhi_, pfJtVsEta_, pfJtVsPTD_, pfJtVsR2_, pfJtVsSigma_, pfVsTau_, pfSubJtVsPt_, pfSubJtVsPhi_, pfSubJtVsEta_, 0.010);
      getJt(nPF_, pfPt_, pfPhi_, pfEta_, pfJtSKPt_, pfJtSKPhi_, pfJtSKEta_, pfJtSKPTD_, pfJtSKR2_, pfJtSKSigma_, pfSKTau_, pfSubJtSKPt_, pfSubJtSKPhi_, pfSubJtSKEta_, pfSKPtCut_);
      getJt(nTrk_, trkPt_, trkPhi_, trkEta_, trkJtRawPt_, trkJtRawPhi_, trkJtRawEta_, trkJtRawPTD_, trkJtRawR2_, trkJtRawSigma_, trkRawTau_, trkSubJtRawPt_, trkSubJtRawPhi_, trkSubJtRawEta_, 0.010);
      getJt(nTrk_, trkPt_, trkPhi_, trkEta_, trkJtSKPt_, trkJtSKPhi_, trkJtSKEta_, trkJtSKPTD_, trkJtSKR2_, trkJtSKSigma_, trkSKTau_, trkSubJtSKPt_, trkSubJtSKPhi_, trkSubJtSKEta_, trkSKPtCut_);
    }
    if(montecarlo){
      getJt(nGen_, genPt_, genPhi_, genEta_, genJtRawPt_, genJtRawPhi_, genJtRawEta_, genJtRawPTD_, genJtRawR2_, genJtRawSigma_, genRawTau_, genSubJtRawPt_, genSubJtRawPhi_, genSubJtRawEta_, 0.010);
      getJt(nGen_, genPt_, genPhi_, genEta_, genJtSKPt_, genJtSKPhi_, genJtSKEta_, genJtSKPTD_, genJtSKR2_, genJtSKSigma_, genSKTau_, genSubJtSKPt_, genSubJtSKPhi_, genSubJtSKEta_, genSKPtCut_);
    }

    run_ = runIni_;
    evt_ = evtIni_;
    lumi_ = lumiIni_;

    if(hi){
      hiBin_ = hiBinIni_;
      if(montecarlo) b_ = bIni_;
    }

    if(montecarlo) pthat_ = pthatIni_;

    if(hi){
      hiEvtPlane_ = hiEvtPlaneIni_;
      psin_ = psinIni_;
    }

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
    std::cout << "Usage: jetTestScript <inputFile> <sType> <outputFile> <isGenBool>" << std::endl;
    return 1;
  }

  int rStatus = -1;

  rStatus = makeFastJetAnaSkim(argv[1], sampleType(atoi(argv[2])), argv[3], Bool_t(atoi(argv[4])));

  return rStatus;
}
