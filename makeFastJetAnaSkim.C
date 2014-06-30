#include "/net/hisrv0001/home/cfmcginn/FastJet/CMSSW_5_3_12_patch3/src/FastJetIniSkim/cfmFastJetIniSkim.h"
#include "cfmFastJetAnaSkim.h"
#include <fstream>
#include "TLorentzVector.h"
#include <vector>
#include <string>

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"

Double_t beta_5 = 0.5;
Double_t beta1 = 1.0;
Double_t beta2 = 2.0;
fastjet::contrib::WTA_KT_Axes axisMode1;
fastjet::contrib::UnnormalizedMeasure measureSpec_5(beta_5);
fastjet::contrib::UnnormalizedMeasure measureSpec1(beta1);
fastjet::contrib::UnnormalizedMeasure measureSpec2(beta2);

fastjet::contrib::Nsubjettiness nSub1_beta_5(1, axisMode1, measureSpec_5);
fastjet::contrib::Nsubjettiness nSub2_beta_5(2, axisMode1, measureSpec_5);
fastjet::contrib::Nsubjettiness nSub3_beta_5(3, axisMode1, measureSpec_5);
fastjet::contrib::NsubjettinessRatio nSub21_beta_5(2, 1, axisMode1, measureSpec_5);
fastjet::contrib::NsubjettinessRatio nSub32_beta_5(3, 2, axisMode1, measureSpec_5);

fastjet::contrib::Nsubjettiness nSub1_beta1(1, axisMode1, measureSpec1);
fastjet::contrib::Nsubjettiness nSub2_beta1(2, axisMode1, measureSpec1);
fastjet::contrib::Nsubjettiness nSub3_beta1(3, axisMode1, measureSpec1);
fastjet::contrib::NsubjettinessRatio nSub21_beta1(2, 1, axisMode1, measureSpec1);
fastjet::contrib::NsubjettinessRatio nSub32_beta1(3, 2, axisMode1, measureSpec1);

fastjet::contrib::Nsubjettiness nSub1_beta2(1, axisMode1, measureSpec2);
fastjet::contrib::Nsubjettiness nSub2_beta2(2, axisMode1, measureSpec2);
fastjet::contrib::Nsubjettiness nSub3_beta2(3, axisMode1, measureSpec2);
fastjet::contrib::NsubjettinessRatio nSub21_beta2(2, 1, axisMode1, measureSpec2);
fastjet::contrib::NsubjettinessRatio nSub32_beta2(3, 2, axisMode1, measureSpec2);

Double_t R = 0.3;
fastjet::JetAlgorithm algorithm = fastjet::antikt_algorithm;
fastjet::JetDefinition jetDef(algorithm, R, fastjet::E_scheme, fastjet::Best);

void getJt(Int_t nMax, Float_t pt[], Float_t phi[], Float_t eta[], Float_t outPt[5], Float_t outPhi[5], Float_t outEta[5], Float_t tau1[5][3], Float_t tau2[5][3], Float_t tau3[5][3], Float_t tau21[5][3], Float_t tau32[5][3])
{
  std::vector<fastjet::PseudoJet>* algVect_p = new std::vector<fastjet::PseudoJet>;
  TLorentzVector tempTL;

  for(Int_t iter = 0; iter < nMax; iter++){
    if(pt[iter] > .010){
       tempTL.SetPtEtaPhiM(pt[iter], eta[iter], phi[iter], 0);
       algVect_p->push_back(tempTL);
    }       
  }

  fastjet::ClusterSequence cs(*algVect_p, jetDef);
  std::vector<fastjet::PseudoJet> algSortVect = sorted_by_pt(cs.inclusive_jets());

  Int_t breakIter = 0;

  for(Int_t iter = 0; iter < (Int_t)algSortVect.size(); iter++){
    if(TMath::Abs(algSortVect[iter].eta()) < 2.0){
      outPt[breakIter] = algSortVect[iter].perp();
      outPhi[breakIter] = algSortVect[iter].phi_std();
      outEta[breakIter] = algSortVect[iter].eta();
	 
      tau1[breakIter][0] = nSub1_beta_5(algSortVect[iter]);
      tau2[breakIter][0] = nSub2_beta_5(algSortVect[iter]);
      tau3[breakIter][0] = nSub3_beta_5(algSortVect[iter]);
      tau21[breakIter][0] = nSub21_beta_5(algSortVect[iter]);
      tau32[breakIter][0] = nSub32_beta_5(algSortVect[iter]);

      tau1[breakIter][1] = nSub1_beta1(algSortVect[iter]);
      tau2[breakIter][1] = nSub2_beta1(algSortVect[iter]);
      tau3[breakIter][1] = nSub3_beta1(algSortVect[iter]);
      tau21[breakIter][1] = nSub21_beta1(algSortVect[iter]);
      tau32[breakIter][1] = nSub32_beta1(algSortVect[iter]);

      tau1[breakIter][2] = nSub1_beta2(algSortVect[iter]);
      tau2[breakIter][2] = nSub2_beta2(algSortVect[iter]);
      tau3[breakIter][2] = nSub3_beta2(algSortVect[iter]);
      tau21[breakIter][2] = nSub21_beta2(algSortVect[iter]);
      tau32[breakIter][2] = nSub32_beta2(algSortVect[iter]);

      if(breakIter == 4) break;

      breakIter++;
    }
  }

  algSortVect.clear();
  algVect_p->clear();
  delete algVect_p;
}

 
int makeFastJetAnaSkim(std::string fList = "", sampleType sType = kHIDATA, const char* outName = "defaultName_FASTJETSKIM.root")
{
  Bool_t montecarlo = false;
  if(sType == kPPMC || sType == kPAMC || sType == kHIMC)
    montecarlo = true;

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
    while(!inFile.eof()){
      inFile >> buffer;
      listOfFiles.push_back(buffer);
      nLines++;
    }
  }
  
  std::cout << "FileList Loaded" << std::endl;

  TFile* iniSkim_p = new TFile(listOfFiles[0].data(), "READ");
  GetFastJetIniSkim(iniSkim_p, montecarlo, sType);

  std::cout << "FastJet Skim Loaded" << std::endl;

  TFile *outFile_p = new TFile(Form("%s.root", outName), "RECREATE");
  InitFastJetAnaSkim(montecarlo, sType);

  Long64_t nentries = rechitTreeIni_p->GetEntries();

  std::cout << nentries << std::endl;

  for(Long64_t jentry = 0; jentry < 10000; jentry++){
    if(jentry%1000 == 0)
      std::cout << jentry << std::endl;

    rechitTreeIni_p->GetEntry(jentry);
    pfcandTreeIni_p->GetEntry(jentry);
    trkTreeIni_p->GetEntry(jentry);
    jetTreeIni_p->GetEntry(jentry);

    InitJtVar();

    getJt(nRechits_, rechitPt_, rechitPhi_, rechitEta_, rechitJtRawPt_, rechitJtRawPhi_, rechitJtRawEta_, rechitRawTau1_, rechitRawTau2_, rechitRawTau3_, rechitRawTau21_, rechitRawTau32_);
    getJt(nRechits_, rechitVsPt_, rechitPhi_, rechitEta_, rechitJtVsPt_, rechitJtVsPhi_, rechitJtVsEta_, rechitVsTau1_, rechitVsTau2_, rechitVsTau3_, rechitVsTau21_, rechitVsTau32_);
    getJt(nPF_, pfPt_, pfPhi_, pfEta_, pfJtRawPt_, pfJtRawPhi_, pfJtRawEta_, pfRawTau1_, pfRawTau2_, pfRawTau3_, pfRawTau21_, pfRawTau32_);
    getJt(nPF_, pfVsPt_, pfPhi_, pfEta_, pfJtVsPt_, pfJtVsPhi_, pfJtVsEta_, pfVsTau1_, pfVsTau2_, pfVsTau3_, pfVsTau21_, pfVsTau32_);
    getJt(nTrk_, trkPt_, trkPhi_, trkEta_, trkJtRawPt_, trkJtRawPhi_, trkJtRawEta_, trkRawTau1_, trkRawTau2_, trkRawTau3_, trkRawTau21_, trkRawTau32_);

    run_ = runIni_;
    evt_ = evtIni_;
    lumi_ = lumiIni_;
    hiBin_ = hiBinIni_;

    if(montecarlo) pthat_ = pthatIni_;

    if(sType == kHIDATA || sType == kHIMC){
      hiEvtPlane_ = hiEvtPlaneIni_;
      psin_ = psinIni_;
    }

    for(Int_t algIter = 0; algIter < 5; algIter++){
      if(!montecarlo && algIter == 2) continue;

      for(Int_t jtIter = 0; jtIter < 2; jtIter++){
	AlgJtPt_[algIter][jtIter] = AlgIniJtPt_[algIter][jtIter];
	AlgJtPhi_[algIter][jtIter] = AlgIniJtPhi_[algIter][jtIter];
	AlgJtEta_[algIter][jtIter] = AlgIniJtEta_[algIter][jtIter];
	AlgJtRawPt_[algIter][jtIter] = AlgIniJtRawPt_[algIter][jtIter];

	if(montecarlo){
	  AlgRefPt_[algIter][jtIter] = AlgIniRefPt_[algIter][jtIter];
	  AlgRefPhi_[algIter][jtIter] = AlgIniRefPhi_[algIter][jtIter];
	  AlgRefEta_[algIter][jtIter] = AlgIniRefEta_[algIter][jtIter];
	}
      }
    }

    rechitTreeAna_p->Fill();
    pfcandTreeAna_p->Fill();
    trkTreeAna_p->Fill();
    jetTreeAna_p->Fill();
  }

  rechitTreeAna_p->Write("", TObject::kOverwrite);
  pfcandTreeAna_p->Write("", TObject::kOverwrite);
  trkTreeAna_p->Write("", TObject::kOverwrite);
  jetTreeAna_p->Write("", TObject::kOverwrite);
  outFile_p->Close();
  delete outFile_p;

  CleanupFastJetAnaSkim();

  iniSkim_p->Close();
  delete iniSkim_p;

  return 0;
}


int main(int argc, char* argv[])
{
  if(argc!=4){
    std::cout << "Usage: jetTestScript <inputFile> <sType> <outputFile>" << std::endl;
    return 1;
  }

  int rStatus = -1;

  rStatus = makeFastJetAnaSkim(argv[1], sampleType(atoi(argv[2])), argv[3]);

  return rStatus;
}
