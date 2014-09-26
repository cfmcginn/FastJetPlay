#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH1I.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TDatime.h"

#include "commonSetup.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

const Float_t bBins[5] = {0.00000, 8.48859, 11.6098, 13.9928, 20.0000};
const Float_t bBins2[5] = {0.0, 8.5, 11.6, 14.0, 20.0};

void makeFastJetHists_Jet(std::string fList = "", const std::string outName = "defaultOutName.root")
{
  std::string buffer;
  std::vector<std::string> listOfFiles;
  Int_t nLines = 0;
  ifstream inFile(fList.data());

  std::cout << fList << std::endl;
  std::cout << inFile.is_open() << std::endl;

  if(!inFile.is_open()){
    std::cout << "Error opening file. Exiting." << std::endl;
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

  for(Int_t iter = 0; iter < (Int_t)listOfFiles.size(); iter++){
    std::cout << listOfFiles.at(iter) << std::endl;
  }

  TChain* jetChain_p = new TChain("jetTreeIni");
  TChain* genChain_p = new TChain("genTreeIni");

  for(Int_t iter = 0; iter < (Int_t)listOfFiles.size(); iter++){
    jetChain_p->Add(listOfFiles.at(iter).c_str());
    genChain_p->Add(listOfFiles.at(iter).c_str());
  }

  Int_t hiBinIni_ = 0;
  Float_t bIni_ = 0;
  Float_t genIniSKPtCut_ = 0;
  Float_t pthatIni_ = 0;

  Float_t AlgIniJtPt_[5][5];
  Float_t AlgIniJtEta_[5][5];

  Int_t nGen_;
  Float_t genPt_[maxEntrySim];
  Int_t genSube_[maxEntrySim];

  jetChain_p->SetBranchStatus("*", 0);

  jetChain_p->SetBranchStatus("hiBinIni", 1);
  jetChain_p->SetBranchStatus("bIni", 1);
  jetChain_p->SetBranchStatus("pthatIni", 1);
  jetChain_p->SetBranchStatus("AlgIniJtPt", 1);
  jetChain_p->SetBranchStatus("AlgIniJtEta", 1);
  jetChain_p->SetBranchAddress("hiBinIni", &hiBinIni_);
  jetChain_p->SetBranchAddress("bIni", &bIni_);
  jetChain_p->SetBranchAddress("pthatIni", &pthatIni_);
  jetChain_p->SetBranchAddress("AlgIniJtPt", AlgIniJtPt_);
  jetChain_p->SetBranchAddress("AlgIniJtEta", AlgIniJtEta_);

  genChain_p->SetBranchStatus("*", 0);

  genChain_p->SetBranchStatus("genIniSKPtCut", 1);
  genChain_p->SetBranchStatus("nGen", 1);
  genChain_p->SetBranchStatus("genPt", 1);
  genChain_p->SetBranchStatus("genSube", 1);

  genChain_p->SetBranchAddress("genIniSKPtCut", &genIniSKPtCut_);
  genChain_p->SetBranchAddress("nGen", &nGen_);
  genChain_p->SetBranchAddress("genPt", genPt_);
  genChain_p->SetBranchAddress("genSube", genSube_);

  TH2F* impactCut = new TH2F("impactCut_h", "impactCut_h", 40, 0.0001, 19.9999, 60, 0.0001, 2.9999);
  TH2F* hiBinB = new TH2F("hiBinB_h", "hiBinB_h", 40, .0001, 19.9999, 200, -.5, 199.5);
  std::vector<Float_t>* bVect_p = new std::vector<Float_t>;

  TH1D* genSubeRaw[4];
  TH1D* genSubeSK[4];
  for(Int_t iter = 0; iter < 4; iter++){
    genSubeRaw[iter] = new TH1D(Form("genSubeRaw_b%d_h", iter), Form("genSubeRaw_b%d_h", iter), 2, -0.4999, 1.4999);
    genSubeSK[iter] = new TH1D(Form("genSubeSK_b%d_h", iter), Form("genSubeSK_b%d_h", iter), 2, -0.4999, 1.4999);
  }

  Int_t nentries = jetChain_p->GetEntries();

  std::cout << "Events: " << nentries << std::endl;

  for(Int_t iter = 0; iter < nentries; iter++){
    jetChain_p->GetEntry(iter);
    genChain_p->GetEntry(iter);

    if(iter%10000 == 0) std::cout << iter << std::endl;

    if(pthatIni_ < 80) continue;

    if(AlgIniJtPt_[2][0] < 120.0) continue;
    if(AlgIniJtPt_[2][1] < 50.0) continue;

    bVect_p->push_back(bIni_);

    impactCut->Fill(bIni_, genIniSKPtCut_);
    hiBinB->Fill(bIni_, hiBinIni_);

    Int_t bPos = -1;
    for(Int_t iter2 = 0; iter2 < 4; iter2++){
      if(bIni_ < bBins[iter2+1]){
	bPos = iter2;
	break;
      }
    }

    for(Int_t genIter = 0; genIter < nGen_; genIter++){
      Int_t fillVal = 0;
      if(genSube_[genIter] != 0) fillVal = 1;

      genSubeRaw[bPos]->Fill(fillVal, genPt_[genIter]);

      if(genPt_[genIter] > genIniSKPtCut_) genSubeSK[bPos]->Fill(fillVal, genPt_[genIter]);
    }
  }

  std::sort(bVect_p->begin(), bVect_p->end());

  Int_t vectSize = bVect_p->size();
  std::cout << "bIni intervals: " << bVect_p->at(vectSize/4) << ", " << bVect_p->at(vectSize/2) << ", " << bVect_p->at(vectSize*3/4) << std::endl;

  TFile* outFile_p = new TFile(outName.c_str(), "UPDATE");
  impactCut->Write("", TObject::kOverwrite);
  hiBinB->Write("", TObject::kOverwrite);

  for(Int_t iter = 0; iter < 4; iter++){
    genSubeRaw[iter]->Scale(1.0/genSubeRaw[iter]->Integral());
    genSubeRaw[iter]->Write("", TObject::kOverwrite);

    genSubeSK[iter]->Scale(1.0/genSubeSK[iter]->Integral());
    genSubeSK[iter]->Write("", TObject::kOverwrite);
  }

  outFile_p->Close();

  delete outFile_p;
  for(Int_t iter = 0; iter < 4; iter++){
    delete genSubeSK[iter];
    delete genSubeRaw[iter];
  }
  bVect_p->clear();
  delete bVect_p;
  delete hiBinB;
  delete impactCut;
  delete genChain_p;
  delete jetChain_p;

  return;
}
