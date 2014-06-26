#include "/net/hisrv0001/home/cfmcginn/FastJet/CMSSW_5_3_12_patch3/src/FastJetIniSkim/cfmFastJetIniSkim.h"
#include "cfmFastJetAnaSkim.h"
#include <fstream>
#include "TLorentzVector.h"
#include <vector>
#include <string>

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include "../fjcontrib-install/include/fastjet/contrib/Nsubjettiness.hh"
#include "../fjcontrib-install/include/fastjet/contrib/Njettiness.hh"
#include "../fjcontrib-install/include/fastjet/contrib/NjettinessPlugin.hh"
 

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

  std::vector<fastjet::PseudoJet>* rechitPVect_p = new std::vector<fastjet::PseudoJet>;
  std::vector<fastjet::PseudoJet>* pfPVect_p = new std::vector<fastjet::PseudoJet>;
  std::vector<fastjet::PseudoJet>* trkPVect_p = new std::vector<fastjet::PseudoJet>;

  for(Long64_t jentry = 0; jentry < nentries; jentry++){
    if(jentry%10000 == 0)
      std::cout << jentry << std::endl;

    rechitTreeIni_p->GetEntry(jentry);
    pfcandTreeIni_p->GetEntry(jentry);
    trkTreeIni_p->GetEntry(jentry);
    jetTreeIni_p->GetEntry(jentry);

    InitJtVar();

    TLorentzVector tempTLVect;
    Double_t R = 0.3;
    Double_t beta = 1.0;
    fastjet::JetDefinition jetDef(fastjet::antikt_algorithm, R);

    fastjet::contrib::Nsubjettiness nSub1KT(1, fastjet::contrib::Njettiness::kt_axes, beta, R, R);
    fastjet::contrib::Nsubjettiness nSub2KT(2, fastjet::contrib::Njettiness::kt_axes, beta, R, R);
    fastjet::contrib::Nsubjettiness nSub3KT(3, fastjet::contrib::Njettiness::kt_axes, beta, R, R);

    for(Int_t rIter = 0; rIter < nRechits_; rIter++){
      tempTLVect.SetPtEtaPhiM(rechitPt_[rIter], rechitEta_[rIter], rechitPhi_[rIter], 0);
      rechitPVect_p->push_back(tempTLVect);
    }

    fastjet::ClusterSequence rechitCS(*rechitPVect_p, jetDef);
    std::vector<fastjet::PseudoJet> rechitJt = sorted_by_pt(rechitCS.inclusive_jets());

    for(Int_t rIter = 0; rIter < (Int_t)rechitJt.size(); rIter++){
      rechitJtRawPt_[rIter] = rechitJt[rIter].perp();
      rechitJtRawPhi_[rIter] = rechitJt[rIter].phi_std();
      rechitJtRawEta_[rIter] = rechitJt[rIter].eta();

      rechitTauOne_[rIter] = nSub1KT(rechitJt[rIter]);
      rechitTauTwo_[rIter] = nSub2KT(rechitJt[rIter]);
      rechitTauThree_[rIter] = nSub3KT(rechitJt[rIter]);

      if(rIter == 4) break;
    }

    rechitPVect_p->clear();
    rechitJt.clear();

    for(Int_t rIter = 0; rIter < nPF_; rIter++){
      tempTLVect.SetPtEtaPhiM(pfPt_[rIter], pfEta_[rIter], pfPhi_[rIter], 0);
      pfPVect_p->push_back(tempTLVect);
    }

    fastjet::ClusterSequence pfCS(*pfPVect_p, jetDef);
    std::vector<fastjet::PseudoJet> pfJt = sorted_by_pt(pfCS.inclusive_jets());

    for(Int_t pfIter = 0; pfIter < (Int_t)pfJt.size(); pfIter++){
      pfJtRawPt_[pfIter] = pfJt[pfIter].perp();
      pfJtRawPhi_[pfIter] = pfJt[pfIter].phi_std();
      pfJtRawEta_[pfIter] = pfJt[pfIter].eta();

      pfTauOne_[pfIter] = nSub1KT(pfJt[pfIter]);
      pfTauTwo_[pfIter] = nSub2KT(pfJt[pfIter]);
      pfTauThree_[pfIter] = nSub3KT(pfJt[pfIter]);

      if(pfIter == 4) break;
    }
    
    pfPVect_p->clear();
    pfJt.clear();

    for(Int_t trkIter = 0; trkIter < nTrk_; trkIter++){
      tempTLVect.SetPtEtaPhiM(trkPt_[trkIter], trkEta_[trkIter], trkPhi_[trkIter], 0);
      trkPVect_p->push_back(tempTLVect);
    }

    fastjet::ClusterSequence trkCS(*trkPVect_p, jetDef);
    std::vector<fastjet::PseudoJet> trkJt = sorted_by_pt(trkCS.inclusive_jets());

    for(Int_t trkIter = 0; trkIter < (Int_t)trkJt.size(); trkIter++){
      trkJtRawPt_[trkIter] = trkJt[trkIter].perp();
      trkJtRawPhi_[trkIter] = trkJt[trkIter].phi_std();
      trkJtRawEta_[trkIter] = trkJt[trkIter].eta();

      trkTauOne_[trkIter] = nSub1KT(trkJt[trkIter]);
      trkTauTwo_[trkIter] = nSub2KT(trkJt[trkIter]);
      trkTauThree_[trkIter] = nSub3KT(trkJt[trkIter]);

      if(trkIter == 4) break;
    }
    
    trkPVect_p->clear();
    trkJt.clear();

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

  delete trkPVect_p;
  delete pfPVect_p;
  delete rechitPVect_p;



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
