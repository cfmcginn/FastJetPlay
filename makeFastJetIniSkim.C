//=============================================
// Author: Chris McGinn
// 
// FastJet IniSkim Class (MC)
//
// !!NOTE: Written for jets sorted by pt, tracks unsorted!!
//
//=============================================

#include "TFile.h"
#include "TTree.h"
#include "/net/hisrv0001/home/cfmcginn/emDiJet/CMSSW_5_3_12_patch3/tempHIFA/HiForestAnalysis/hiForest.h"
#include "cfmFastJetIniSkim.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>

#include "TComplex.h"

#include "TLorentzVector.h"

const Float_t lJtPtCut = 120.;
const Float_t sLJtPtCut = 50.;
const Float_t jtEtaCut = 2.0; // Default Max at 2.4 to avoid transition junk, otherwise vary as needed

collisionType getCType(sampleType sType);

Bool_t passesDijet(Jets jtCollection, Int_t &leadJtIndex, Int_t &subLeadJtIndex, Int_t &leadJtCut, Int_t &subLeadJtCut)
{
  if(jtCollection.nref == 0){
    leadJtCut++;
    return false;
  }
  else if(jtCollection.nref == 1){
    subLeadJtCut++;
    return false;
  }

  for(Int_t jtEntry = 0; jtEntry < jtCollection.nref; jtEntry++){
    if(leadJtIndex < 0){
      if(jtCollection.jtpt[jtEntry] > lJtPtCut){
	if(TMath::Abs(jtCollection.jteta[jtEntry]) < jtEtaCut)
	  leadJtIndex = jtEntry;
      }
      else{
	leadJtCut++;
	return false;
      }
    }
    else if(subLeadJtIndex < 0){
      if(jtCollection.jtpt[jtEntry] > sLJtPtCut){
	if(TMath::Abs(jtCollection.jteta[jtEntry]) < jtEtaCut)
	  subLeadJtIndex = jtEntry;
      }
      else{
	subLeadJtCut++;
	return false;
      }
    }
    else
      return true;
  }

  if(leadJtIndex >= 0){
    if(subLeadJtIndex >= 0)
      return true;
    else{
      subLeadJtCut++;
      return false;
    }
  }
  else{
    leadJtCut++;
    return false;
  }
  
  
  return false;
}


int makeFastJetIniSkim(string fList = "", sampleType sType = kHIDATA, const char *outName = "defaultName_CFMSKIM.root", Int_t num = 0)
{
  //Define MC or Data
  Bool_t montecarlo = false;
  if(sType == kPPMC || sType == kPAMC || sType == kHIMC)
    montecarlo = true;

  std::cout << sType << std::endl;
  std::cout << montecarlo << std::endl;

  collisionType cType = getCType(sType);

  string buffer;
  std::vector<string> listOfFiles;
  int nLines = 0;
  ifstream inFile(fList.data());

  std::cout << fList << std::endl;
  std::cout << inFile.is_open() << std::endl;

  if(!inFile.is_open()){
    std::cout << "Error opening file. Exiting." <<std::endl;
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

  //Setup correction tables

  TFile *outFile = new TFile(Form("%s_%d.root", outName, num), "RECREATE");

  InitFastJetIniSkim(montecarlo, sType);

  HiForest *c = new HiForest(listOfFiles[0].data(), "Forest", cType, montecarlo);

  c->InitTree();

  c->LoadNoTrees();

  c->hasSkimTree = true;
  c->hasEvtTree = true;
  c->hasTowerTree = true;
  c->hasPFTree = true;
  c->hasTrackTree = true;

  if(sType == kHIDATA || sType == kHIMC){
    c->hasAkPu3JetTree = true;
    c->hasAkPu3CaloJetTree = true;
    c->hasAkVs3CaloJetTree = true;
    c->hasAkVs3PFJetTree = true;
  }
  else if(sType == kPPDATA || sType == kPPMC){
    c->hasAk3CaloJetTree = true;
  }

  std::cout << "TreeTruth: " << c->hasAk3CaloJetTree << std::endl;

  Float_t meanVz = 0;

  if(sType == kHIMC){
    c->hasGenParticleTree = true;
    //mean mc .16458, mean data -.337
    meanVz = .16458 + .337;
  }
  else if(sType == kPPMC){
    c->hasGenParticleTree = true;
    //MC vz = .4205,  Data vz = .6953
    meanVz = .4205 - .6953;
  }

  Long64_t nentries;

  if(sType == kPPDATA || sType == kPPMC)
    nentries = c->ak3CaloJetTree->GetEntries();
  else
    nentries = c->GetEntries();

  std::cout << nentries << std::endl;

  Int_t totEv = 0;
  Int_t selectCut = 0;
  Int_t vzCut = 0;

  Int_t AlgIniLeadJtPtCut[5] = {0, 0, 0, 0, 0};
  Int_t AlgIniSubLeadJtPtCut[5] = {0, 0, 0, 0, 0};

  std::cout << "Cuts, Jet pt, eta: " << lJtPtCut << ", " << jtEtaCut << std::endl; 

  for(Long64_t jentry = 0; jentry < nentries; jentry++){
    c->GetEntry(jentry);

    totEv++;

    if(jentry%1000 == 0)
      std::cout << jentry << std::endl;

    if(!c->selectEvent()){
      selectCut++;
      continue;
    }

    if(TMath::Abs(c->evt.vz - meanVz) > 15){
      vzCut++;
      continue;
    }

    //particle flow

    Jets AlgIniJtCollection[5];

    if(sType == kHIDATA || sType == kHIMC){
      AlgIniJtCollection[0] = c->akPu3Calo;
      AlgIniJtCollection[1] = c->akVs3Calo;

      AlgIniJtCollection[3] = c->akPu3PF;
      AlgIniJtCollection[4] = c->akVs3PF;
    }
    else if(sType == kPPDATA || sType == kPPMC){
      AlgIniJtCollection[0] = c->akPu3Calo;
      AlgIniJtCollection[1] = c->ak3Calo;
    }

    Bool_t algPasses[5] = {false, false, false, false, false};

    Int_t jtIndex[5][2];
    
    for(Int_t algIter = 0; algIter < 5; algIter++){
      for(Int_t jtIter = 0; jtIter < 2; jtIter++){
	jtIndex[algIter][jtIter] = -1;
      }
    }

    for(Int_t algIter = 0; algIter < 5; algIter++){
      if(algIter != 2)
	algPasses[algIter] = passesDijet(AlgIniJtCollection[algIter], jtIndex[algIter][0], jtIndex[algIter][1], AlgIniLeadJtPtCut[algIter], AlgIniSubLeadJtPtCut[algIter]);
    }

    //truth, doesn't work w/ getLeadJt because truth doesnt get its own tree

    if(montecarlo){
      if(c->akPu3PF.ngen == 0){
	AlgIniLeadJtPtCut[2]++;
	algPasses[2] = false;
      }
      else if(c->akPu3PF.ngen == 1){
	AlgIniSubLeadJtPtCut[2]++;
	algPasses[2] = false;
      }
      else{
	for(Int_t jtEntry = 0; jtEntry < c->akPu3PF.ngen; jtEntry++){
	  if(jtIndex[2][0] < 0){
	    if(c->akPu3PF.genpt[jtEntry] > lJtPtCut){
	      if(TMath::Abs(c->akPu3PF.geneta[jtEntry]) < jtEtaCut)
		jtIndex[2][0] = jtEntry;
	    }
	    else{
	      algPasses[2] = false;
	      break;
	    }
	  }
	  else if(jtIndex[2][1] < 0){
	    if(c->akPu3PF.genpt[jtEntry] > sLJtPtCut){
	      if(TMath::Abs(c->akPu3PF.geneta[jtEntry]) < jtEtaCut)
		jtIndex[2][1] = jtEntry;
	    }
	    else{
	      algPasses[2] = false;
	      break;
	    }
	  }
	  else{
	    algPasses[2] = true;
	    break;
	  }
	}
      }

      if(jtIndex[2][0] >= 0){
	if(jtIndex[2][1] >= 0)
	  algPasses[2] = true;
	else
	  algPasses[2] = false;
      }
      else{
	AlgIniLeadJtPtCut[2]++;
	algPasses[2] = false;
      }
    }
    
    if(algPasses[0] == false && algPasses[1] == false && algPasses[2] == false && algPasses[3] == false && algPasses[4] == false)
      continue;

    if(kHIMC) pthatIni_ = c->akPu3PF.pthat;
    else if(kPPMC) pthatIni_ = c->ak3Calo.pthat;

    if(sType == kHIDATA || sType == kHIMC){
      hiEvtPlaneIni_ = c->evt.hiEvtPlanes[21];                                                  
      TComplex cn1((c->pf.sumpt[0])*(c->pf.vn[2][0]), c->pf.psin[2][0], true);                    
      TComplex cn2((c->pf.sumpt[14])*(c->pf.vn[2][14]), c->pf.psin[2][14], true);                
      TComplex cn = cn1+cn2;                                                                    
      psinIni_ = cn.Theta();      
    }      

    runIni_ = c->evt.run;
    evtIni_ = c->evt.evt;
    lumiIni_ = c->evt.lumi;

    if(sType == kHIDATA || sType == kHIMC)
      hiBinIni_ = c->evt.hiBin;

    //Iterate over jets

    Int_t algMax = 5;

    for(Int_t algIter = 0; algIter < algMax; algIter++){
      if(algIter == 2 && !montecarlo)
	continue;

      for(Int_t jtIter = 0; jtIter < 2; jtIter++){
	if(jtIndex[algIter][jtIter] >= 0){
	  AlgIniJtPt_[algIter][jtIter] = AlgIniJtCollection[algIter].jtpt[jtIndex[algIter][jtIter]];
	  AlgIniJtPhi_[algIter][jtIter] = AlgIniJtCollection[algIter].jtphi[jtIndex[algIter][jtIter]];
	  AlgIniJtEta_[algIter][jtIter] = AlgIniJtCollection[algIter].jteta[jtIndex[algIter][jtIter]];

	  AlgIniJtRawPt_[algIter][jtIter] = AlgIniJtCollection[algIter].rawpt[jtIndex[algIter][jtIter]];

	  if(montecarlo){
	    AlgIniRefPt_[algIter][jtIter] = AlgIniJtCollection[algIter].refpt[jtIndex[algIter][jtIter]];
	    AlgIniRefPhi_[algIter][jtIter] = AlgIniJtCollection[algIter].refphi[jtIndex[algIter][jtIter]];
	    AlgIniRefEta_[algIter][jtIter] = AlgIniJtCollection[algIter].refeta[jtIndex[algIter][jtIter]];
	  }
	}
      }
    }

    //Iterate over rechits

    nRechits_ = 0;

    for(Int_t rechitIter = 0; rechitIter < c->tower.n; rechitIter++){
      if(TMath::Abs(c->tower.eta[rechitIter]) < 2.3){
	rechitPt_[nRechits_] = c->tower.et[rechitIter];
	rechitPhi_[nRechits_] = c->tower.phi[rechitIter];
	rechitEta_[nRechits_] = c->tower.eta[rechitIter];
	nRechits_++;
      }
    }

    //Iterate over pf

    nPF_ = 0;

    for(Int_t pfIter = 0; pfIter < c->pf.nPFpart; pfIter++){
      if(TMath::Abs(c->pf.pfEta[pfIter]) < 2.3){
	pfPt_[nPF_] = c->pf.pfPt[pfIter];
	pfPhi_[nPF_] = c->pf.pfPhi[pfIter];
	pfEta_[nPF_] = c->pf.pfEta[pfIter];
	nPF_++;
      }
    }

    //Iterate over tracks

    nTrk_ = 0;

    for(Int_t trkIter = 0; trkIter < c->track.nTrk; trkIter++){
      if(TMath::Abs(c->track.trkEta[trkIter]) > 2.4)
	continue;

      if(c->track.trkPt[trkIter] <= 0.5)
	continue;

      if(!c->track.highPurity[trkIter])
	continue;

      if(TMath::Abs(c->track.trkDz1[trkIter]/c->track.trkDzError1[trkIter]) > 3)
	continue;

      if(TMath::Abs(c->track.trkDxy1[trkIter]/c->track.trkDxyError1[trkIter]) > 3)
	continue;

      if(c->track.trkPtError[trkIter]/c->track.trkPt[trkIter] > 0.1)
	continue;

      trkPt_[nTrk_] = c->track.trkPt[trkIter];
      trkPhi_[nTrk_] = c->track.trkPhi[trkIter];
      trkEta_[nTrk_] = c->track.trkEta[trkIter];
      nTrk_++;
    }

    rechitTreeIni_p->Fill();
    pfcandTreeIni_p->Fill();
    trkTreeIni_p->Fill();
    jetTreeIni_p->Fill();
  }

  std::cout << "totEv: " << totEv << std::endl;
  Int_t tempTot = totEv - selectCut;
  std::cout << "selectCut: " << tempTot << std::endl;
  tempTot = tempTot - vzCut;
  std::cout << "vzCut: " << tempTot << std::endl;

  for(Int_t cutIter = 0; cutIter < 5; cutIter++){
    std::cout << std::endl;
    tempTot = totEv - selectCut - vzCut - AlgIniLeadJtPtCut[cutIter];
    std::cout << "AlgIniLeadJtPtCut[" << cutIter << "]: " << tempTot << std::endl;
    tempTot = tempTot - AlgIniSubLeadJtPtCut[cutIter];
    std::cout << "AlgIniSubLeadJtPtCut[" << cutIter << "]: " << tempTot << std::endl;
  }

  outFile->cd();

  rechitTreeIni_p->Write("", TObject::kOverwrite);
  pfcandTreeIni_p->Write("", TObject::kOverwrite);
  trkTreeIni_p->Write("", TObject::kOverwrite);
  jetTreeIni_p->Write("", TObject::kOverwrite);

  outFile->Close();

  delete c;
  CleanupFastJetIniSkim();
  delete outFile;

  printf("Done.\n");
  return(0);
}


collisionType getCType(sampleType sType)
{
  switch (sType)
    {
    case kPPDATA:
    case kPPMC:
      return cPP;
    case kPADATA:
    case kPAMC:
      return cPPb;
    case kHIDATA:
    case kHIMC:
      return cPbPb;
    }
  return cPbPb; //probably a bad guess
}


int main(int argc, char *argv[])
{
  if(argc != 5)
    {
      std::cout << "Usage: makeFastJetIniSkim <inputFile> <MCBool> <outputFile> <#>" << std::endl;
      return 1;
    }

  int rStatus = -1;

  rStatus = makeFastJetIniSkim(argv[1], sampleType(atoi(argv[2])), argv[3], atoi(argv[4]));

  return rStatus;
}
