#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"

#include "TH1F.h"
#include "TCanvas.h"

const Float_t ptHatCuts_PYTH[6] = {30, 50, 80, 120, 170, 1000000};
const Float_t crossSections_PYTH[6] = {.01075, .001025, .00009865, .00001129, .000001465, 0.000000000};

const Float_t ptHatCuts_PYTHPawan[7] = {15, 30, 50, 80, 120, 170, 10000000};
const Float_t crossSections_PYTHPawan[7] = {.20340, .01075, .001025, .00009865, .00001129, .000001465, 0.000000000};

const Float_t ptHatCuts_PYTHHYD[10] = {15, 30, 50, 80, 120, 170, 220, 280, 370, 1000000};
const Float_t crossSections_PYTHHYD[10] = {.20340, .01075, .001025, .00009865, .00001129, .000001465, .0000002837, .00000005323, .000000005934, .0000000000};

const Float_t ptHatCuts_FastJet[4] = {80, 100, 120, 1000000};
const Float_t crossSections_FastJet[4] = {.00009865, .00003069, .00001129, 0.0000000};

void derivePtHatWeights(const Int_t numCut,Float_t ptHatCuts[], Float_t crossSect[], std::string fList = "")
{
  std::string buffer;
  std::vector<std::string> listOfFiles;
  int nLines = 0;
  ifstream inFile(fList.data());

  std::cout << fList << std::endl;
  std::cout << inFile.is_open() << std::endl;

  if(!inFile.is_open()){
    std::cout << "Error opening file. Exiting." <<std::endl;
    return;
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

  TChain* ptHatChain_p = new TChain("akVs3CaloJetAnalyzer/t");

  for(Int_t iter = 0; iter < (Int_t)(listOfFiles.size()); iter++){
    ptHatChain_p->Add(listOfFiles[iter].c_str());

    std::cout << listOfFiles[iter] << std::endl;
  }

  Float_t ptHat_ = 0;

  ptHatChain_p->SetBranchStatus("*", 0);
  ptHatChain_p->SetBranchStatus("pthat", 1);
  ptHatChain_p->SetBranchAddress("pthat", &ptHat_);

  Int_t nEntries = ptHatChain_p->GetEntries();
  std::cout << nEntries << std::endl;

  Int_t hatEntries[numCut];
  Float_t hatWeight[numCut];

  for(Int_t iter = 0; iter < numCut; iter++){
    hatEntries[iter] = 0;
    hatWeight[iter] = 0;
  }

  for(Int_t evtIter = 0; evtIter < nEntries; evtIter++){
    ptHatChain_p->GetEntry(evtIter);

    for(Int_t hatIter = 0; hatIter < numCut; hatIter++){
      if(ptHat_ > ptHatCuts[hatIter] && ptHat_ < ptHatCuts[hatIter+1]){
	hatEntries[hatIter]++;
	break;
      }
    }
  }

  TH1F* pthatNoWeight_h = new TH1F("pthatNoWeight_h", "pthatNoWeight_h", 100, -0.5, 499.5);
  TH1F* pthatWeight_h = new TH1F("pthatWeight_h", "pthatWeight_h", 100, -0.5, 499.5);

  for(Int_t evtIter = 0; evtIter < nEntries; evtIter++){
    ptHatChain_p->GetEntry(evtIter);

    pthatNoWeight_h->Fill(ptHat_);

    for(Int_t hatIter = 0; hatIter < numCut; hatIter++){
      if(ptHat_ > ptHatCuts[hatIter] && ptHat_ < ptHatCuts[hatIter+1]){
	pthatWeight_h->Fill(ptHat_, (crossSect[hatIter] - crossSect[hatIter + 1])/hatEntries[hatIter]);	
      }
    }
  }

  TCanvas* hatCanv_c = new TCanvas("hatCanv_c", "hatCanv_c", 2*300, 1*350);
  hatCanv_c->Divide(2, 1, 0.0, 0.0);
  
  hatCanv_c->cd(1);
  gPad->SetLogy();
  pthatNoWeight_h->Draw("HIST");

  hatCanv_c->cd(2);
  gPad->SetLogy();
  pthatWeight_h->Draw("HIST");

  for(Int_t hatIter = 0; hatIter < numCut; hatIter++){
    std::cout << hatIter << ", " << ptHatCuts_PYTHHYD[hatIter] << std::endl;
    std::cout << "  hatEntries: " << hatEntries[hatIter] << std::endl;
    hatWeight[hatIter] = (crossSect[hatIter] - crossSect[hatIter+1])/hatEntries[hatIter];
    std::cout << "  hatWeight: " << hatWeight[hatIter] << std::endl;    
  }

  return;
}
