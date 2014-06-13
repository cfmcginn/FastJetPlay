#include "fastjet/ClusterSequence.hh"
#include "cfmDiJetIniSkim.h"
#include <iostream>
#include <fstream>
#include "TLorentzVector.h"
#include <vector>
#include <string>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector>;
#endif

int jetTestScript(std::string fList = "", sampleType sType = kHIDATA, const char* outName = "defaultName_jetTestScript.root")
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
  GetDiJetIniSkim(iniSkim_p, montecarlo, sType);

  std::cout << "IniSkim Loaded" << std::endl;

  Long64_t nentries = trackTreeIni_p->GetEntries();

  std::cout << nentries << std::endl;

  std::vector<TLorentzVector>* trkLVect_p= new std::vector<TLorentzVector>;
  std::vector<fastjet::PseudoJet>* trkPVect_p = new std::vector<fastjet::PseudoJet>;

  for(Long64_t jentry = 0; jentry < nentries; jentry++){
    trackTreeIni_p->GetEntry(jentry);
    jetTreeIni_p->GetEntry(jentry);

    if(montecarlo)
      genTreeIni_p->GetEntry(jentry);

    if(jentry%1000 == 0)
      std::cout << jentry << std::endl;

    TLorentzVector tempVect;

    for(Int_t trkIter = 0; trkIter < nTrk_; trkIter++){
      tempVect.SetPtEtaPhiM(trkPt_[trkIter], trkEta_[trkIter], trkPhi_[trkIter], 0);
      trkLVect_p->push_back(tempVect);
    }

    for(Int_t vectIter = 0; vectIter < (Int_t)trkLVect_p->size(); vectIter++){
      trkPVect_p->push_back( fastjet::PseudoJet(trkLVect_p->at(vectIter)) );
    }

    Double_t R = 0.3;
    fastjet::JetDefinition jetDef(fastjet::antikt_algorithm, R);
    fastjet::ClusterSequence cs(*trkPVect_p, jetDef);

    std::vector<fastjet::PseudoJet> jetVect = sorted_by_pt(cs.inclusive_jets());

    std::cout << "Clustering with " << jetDef.description() << std::endl;

    for(Int_t jetIter = 0; jetIter < (Int_t)jetVect.size(); jetIter++){
      std::cout << "Jet " << jetIter << ": " << jetVect[jetIter].perp() << ", " << jetVect[jetIter].rap() << ", " << jetVect[jetIter].phi_std() << std::endl;

      if(jetVect[jetIter].perp() > 30){
	std::vector<fastjet::PseudoJet> constituents = jetVect[jetIter].constituents();
	
	for(Int_t constIter = 0; constIter < (Int_t)constituents.size(); constIter++){
	  std::cout << "     Consituent" << constIter << ": " << constituents[constIter].perp() << ", " << constituents[constIter].rap() << ", " << constituents[constIter].phi_std() << std::endl;
	}
      }
    }


    trkLVect_p->clear();
    trkPVect_p->clear();

    if(jentry == 0)
      break;
  }

  TFile* outFile_p =  new TFile(outName, "READ");

  outFile_p->Close();
  delete outFile_p;

  delete trkPVect_p;
  delete trkLVect_p;

  iniSkim_p->Close();
  delete iniSkim_p;

  return 0;
}



int main(int argc, char* argv[])
{
  if(argc!=4){
    std::cout << "Usage: jetTestScript <inputFile> <sType> <outputFile>" << std::endl;
  }

  int rStatus = -1;

  rStatus = jetTestScript(argv[1], sampleType(atoi(argv[2])), argv[3]);

  return rStatus;
}
