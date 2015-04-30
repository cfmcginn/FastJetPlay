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
#include "FastJetIniSkim.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>

#include "TComplex.h"
#include "TLorentzVector.h"

#include "softKiller.h"

const Float_t lJtPtCut = 120.;
const Float_t sLJtPtCut = 50.;
const Float_t jtEtaCut = 2.0; // Default Max at 2.4 to avoid transition junk, otherwise vary as needed
const Int_t nEvtPerFile = 10000;

const Float_t pPbEtaBoost = 0.4654094531;

collisionType getCType(sampleType sType);

void setJtBranches(TTree* inJtTree, Bool_t montecarlo = false, Bool_t isGen = false)
{
  inJtTree->SetBranchStatus("*", 0);
  inJtTree->SetBranchStatus("nref", 1);
  inJtTree->SetBranchStatus("jtpt", 1);
  inJtTree->SetBranchStatus("rawpt", 1);
  inJtTree->SetBranchStatus("jteta", 1);
  inJtTree->SetBranchStatus("jtphi", 1);

  if(montecarlo){
    inJtTree->SetBranchStatus("pthat", 1);
    inJtTree->SetBranchStatus("refparton_flavor", 1);
    inJtTree->SetBranchStatus("refpt", 1);
    inJtTree->SetBranchStatus("refeta", 1);
    inJtTree->SetBranchStatus("refphi", 1);

    if(isGen){
      inJtTree->SetBranchStatus("ngen", 1);
      inJtTree->SetBranchStatus("genpt", 1);
      inJtTree->SetBranchStatus("geneta", 1);
      inJtTree->SetBranchStatus("genphi", 1);
      inJtTree->SetBranchStatus("genmatchindex", 1);
    }
  }

  return;
}


Bool_t passesDijet(Jets jtCollection, Int_t jtIndex[5], Int_t &leadJtCut, Int_t &subLeadJtCut)
{
  if(jtCollection.nref == 0){
    leadJtCut++;
    return false;
  }
  else if(jtCollection.nref == 1){
    subLeadJtCut++;
    return false;
  }

  Int_t nIndex = 2;

  for(Int_t jtEntry = 0; jtEntry < jtCollection.nref; jtEntry++){
    if(jtCollection.jtpt[jtEntry] < sLJtPtCut) break;

    if(jtIndex[0] < 0){
      if(jtCollection.jtpt[jtEntry] > lJtPtCut){
	if(TMath::Abs(jtCollection.jteta[jtEntry]) < jtEtaCut)
	  jtIndex[0] = jtEntry;
      }
      else{
	leadJtCut++;
	return false;
      }
    }
    else if(jtIndex[1] < 0){
      if(jtCollection.jtpt[jtEntry] > sLJtPtCut){
	if(TMath::Abs(jtCollection.jteta[jtEntry]) < jtEtaCut)
	  jtIndex[1] = jtEntry;
      }
      else{
	subLeadJtCut++;
	return false;
     }
    }
    else if(jtIndex[nIndex] < 0 && nIndex < 5){
      if(jtCollection.jtpt[jtEntry] > sLJtPtCut && TMath::Abs(jtCollection.jteta[jtEntry]) < jtEtaCut){
	 jtIndex[nIndex] = jtEntry;
	 nIndex++;
      }
    }
    else
      return true;
  }

  if(jtIndex[0] >= 0){
    if(jtIndex[1] >= 0)
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


Bool_t passesPPbJet(Jets jtCollection)
{
  for(Int_t jtEntry = 0; jtEntry < jtCollection.nref; jtEntry++){
    if(jtCollection.jtpt[jtEntry] < 60.) break;

    if(TMath::Abs(jtCollection.jteta[jtEntry] + pPbEtaBoost) < 1.5) return true;
  }

  return false;
}


int makeFastJetIniSkim(string fList = "", sampleType sType = kHIDATA, const char *outName = "defaultName_CFMSKIM.root", Int_t num = 0, Bool_t isGen = false)
{
  //Define MC or Data
  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);
  Bool_t pa = isPA(sType);

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

  //Setup correction tables

  HiForest *c = new HiForest(listOfFiles[num].data(), "Forest", cType, montecarlo);

  c->skimTree->SetBranchStatus("*", 0);
  c->skimTree->SetBranchStatus("pHBHENoiseFilter", 1);

  c->evtTree->SetBranchStatus("*", 0);
  c->evtTree->SetBranchStatus("vz", 1);
  if(hi) c->evtTree->SetBranchStatus("hiEvtPlanes", 1);
  c->evtTree->SetBranchStatus("run", 1);
  c->evtTree->SetBranchStatus("evt", 1);
  c->evtTree->SetBranchStatus("lumi", 1);

  c->pfTree->SetBranchStatus("*", 0);
  c->pfTree->SetBranchStatus("nPFpart", 1);
  c->pfTree->SetBranchStatus("pfPt", 1);
  if(hi) c->pfTree->SetBranchStatus("pfVsPt", 1);
  c->pfTree->SetBranchStatus("pfPhi", 1);
  c->pfTree->SetBranchStatus("pfEta", 1);
  if(hi){ 
    c->pfTree->SetBranchStatus("vn", 1);
    c->pfTree->SetBranchStatus("psin", 1);
    c->pfTree->SetBranchStatus("sumpt", 1);
  }

  if(!pa){
    c->towerTree->SetBranchStatus("*", 0);
    c->towerTree->SetBranchStatus("n", 1);
    c->towerTree->SetBranchStatus("et", 1);
    c->towerTree->SetBranchStatus("vsPt", 1);
    c->towerTree->SetBranchStatus("phi", 1);
    c->towerTree->SetBranchStatus("eta", 1);
  }

  c->trackTree->SetBranchStatus("*", 0);
  c->trackTree->SetBranchStatus("nTrk", 1);
  c->trackTree->SetBranchStatus("trkPt", 1);
  c->trackTree->SetBranchStatus("trkPhi", 1);
  c->trackTree->SetBranchStatus("trkEta", 1);
  c->trackTree->SetBranchStatus("highPurity", 1);
  c->trackTree->SetBranchStatus("trkDz1", 1);
  c->trackTree->SetBranchStatus("trkDzError1", 1);
  c->trackTree->SetBranchStatus("trkDxy1", 1);
  c->trackTree->SetBranchStatus("trkDxyError1", 1);
  c->trackTree->SetBranchStatus("trkPtError", 1);

  if(montecarlo && !pa){
    c->genParticleTree->SetBranchStatus("*", 0);
    c->genParticleTree->SetBranchStatus("b", 1);
    c->genParticleTree->SetBranchStatus("mult", 1);
    c->genParticleTree->SetBranchStatus("pt", 1);
    c->genParticleTree->SetBranchStatus("phi", 1);
    c->genParticleTree->SetBranchStatus("eta", 1);
    c->genParticleTree->SetBranchStatus("sube", 1);
  }

  if(hi){
    c->skimTree->SetBranchStatus("pcollisionEventSelection", 1);

    c->evtTree->SetBranchStatus("hiBin", 1);

    setJtBranches(c->akPu3CaloJetTree, montecarlo);
    setJtBranches(c->akVs3CaloJetTree, montecarlo);
    setJtBranches(c->akPu3PFJetTree, montecarlo, true);
    setJtBranches(c->akVs3PFJetTree, montecarlo);
  }
  else{
    c->skimTree->SetBranchStatus("pPAcollisionEventSelectionPA", 1);

    setJtBranches(c->akPu3CaloJetTree, montecarlo);
    setJtBranches(c->akPu3PFJetTree, montecarlo, true);
    setJtBranches(c->ak3CaloJetTree, montecarlo);
    setJtBranches(c->ak3PFJetTree, montecarlo);
  }

  c->LoadNoTrees();
  
  c->hasSkimTree = true;
  c->hasEvtTree = true;
  if(hi){
    c->hasAkPu3JetTree = true;
    c->hasAkPu3CaloJetTree = true;
    c->hasAkVs3CaloJetTree = true;
    c->hasAkVs3PFJetTree = true;
  }
  else{
    c->hasAkPu3JetTree = true;
    c->hasAkPu3CaloJetTree = true;
    c->hasAk3CaloJetTree = true;
    c->hasAk3JetTree = true;
  }

  if(!isGen){
    if(!pa) c->hasTowerTree = true;
    c->hasPFTree = true;
    c->hasTrackTree = true;
  }
  if(montecarlo && !pa) c->hasGenParticleTree = true;

  c->InitTree();

  std::cout << "TreeTruth: " << c->hasAk3CaloJetTree << std::endl;

  Float_t meanVz = 0;
  
  if(sType == kHIMC){
    //mean mc .16458, mean data -.337
    meanVz = .16458 + .337;
  }
  else if(sType == kPPMC){
    //MC vz = .4205,  Data vz = .6953
    meanVz = .4205 - .6953;
  }
  
  Long64_t nentries;

  Int_t nEvtsOutTag = 0;

  if(!hi) nentries = c->skimTree->GetEntries();
  else nentries = c->GetEntries();

  std::cout << nentries << std::endl;

  TFile *outFile = new TFile(Form("%s_%d_%d.root", outName, num, 0), "RECREATE");
  InitFastJetIniSkim(sType, isGen);

  Int_t totEv = 0;
  Int_t selectCut = 0;
  Int_t vzCut = 0;

  Int_t AlgIniLeadJtPtCut[5] = {0, 0, 0, 0, 0};
  Int_t AlgIniSubLeadJtPtCut[5] = {0, 0, 0, 0, 0};

  std::cout << "Cuts, Jet pt, eta: " << lJtPtCut << ", " << jtEtaCut << std::endl; 

  InitEtaSKGrid();
  InitPhiSKGrid();

  std::cout << "Grid Init" << std::endl;

  for(Long64_t jentry = 0; jentry < nentries; jentry++){
    if(!isGen){
      if(!pa) c->hasTowerTree = false;
      c->hasPFTree = false;
      c->hasTrackTree = false;
    }
    if(montecarlo) c->hasGenParticleTree = false;

    c->GetEntry(jentry);

    totEv++;

    if(jentry%1000 == 0) std::cout << jentry << ", " << nEvtsOutTag << std::endl;

    if(!c->selectEvent()){
      selectCut++;
      continue;
    }
    if(TMath::Abs(c->evt.vz - meanVz) > 15){
      vzCut++;
      continue;
    }

    if(pa && !montecarlo){
      if(c->evt.run >= 211313 || c->evt.run < 210676) continue;
    }

    //particle flow

    Jets AlgIniJtCollection[5];

    if(hi){
      AlgIniJtCollection[0] = c->akPu3Calo;
      AlgIniJtCollection[1] = c->akVs3Calo;
      AlgIniJtCollection[2] = c->akPu3PF;
      AlgIniJtCollection[3] = c->akPu3PF;
      AlgIniJtCollection[4] = c->akVs3PF;
    }
    else{
      AlgIniJtCollection[0] = c->akPu3Calo;
      AlgIniJtCollection[1] = c->ak3Calo;
      AlgIniJtCollection[2] = c->akPu3PF;
      AlgIniJtCollection[3] = c->akPu3PF;
      AlgIniJtCollection[4] = c->ak3PF;
    }
    

    Bool_t algPasses[5] = {false, false, false, false, false};

    Int_t jtIndex[5][5];
    
    for(Int_t algIter = 0; algIter < 5; algIter++){
      for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	jtIndex[algIter][jtIter] = -1;
      }
    }
    if(!pa){
      for(Int_t algIter = 0; algIter < 5; algIter++){
	if(algIter != 2) algPasses[algIter] = passesDijet(AlgIniJtCollection[algIter], jtIndex[algIter], AlgIniLeadJtPtCut[algIter], AlgIniSubLeadJtPtCut[algIter]);
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
	  Int_t nIndex = 2;
	  for(Int_t jtEntry = 0; jtEntry < c->akPu3PF.ngen; jtEntry++){
	    if(c->akPu3PF.genpt[jtEntry] < sLJtPtCut) break;

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
	    else if(jtIndex[2][nIndex] < 0 && nIndex < 5){
	      if(c->akPu3PF.genpt[jtEntry] > sLJtPtCut && TMath::Abs(c->akPu3PF.geneta[jtEntry]) < jtEtaCut){
		jtIndex[2][nIndex] = jtEntry;
		nIndex++;
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
    }
    else{
      for(Int_t algIter = 0; algIter < 5; algIter++){
        if(algIter != 2) algPasses[algIter] = passesPPbJet(AlgIniJtCollection[algIter]);
      }

      for(Int_t jtEntry = 0; jtEntry < c->akPu3PF.ngen; jtEntry++){
	if(c->akPu3PF.genpt[jtEntry] < 60.) break;

	if(TMath::Abs(c->akPu3PF.geneta[jtEntry] + pPbEtaBoost) < 1.5){
	  algPasses[jtEntry] = true;
	  break;
	}
      }

      for(Int_t algIter = 0; algIter < 5; algIter++){
	if(algPasses[algIter]){
	  if(algIter == 2){
	    for(Int_t jtIter = 0; jtIter < c->akPu3PF.ngen; jtIter++){
	      jtIndex[algIter][jtIter] = jtIter;
	      if(jtIter == 4) break;
	    }
	  }
	  else{
	    for(Int_t jtIter = 0; jtIter < AlgIniJtCollection[algIter].nref; jtIter++){
	      jtIndex[algIter][jtIter] = jtIter;
	      if(jtIter == 4) break;
	    }
	  }
	}
      }
    }

    if(algPasses[0] == false && algPasses[1] == false && algPasses[2] == false && algPasses[3] == false && algPasses[4] == false)
      continue;

    if(!isGen){
      if(!pa) c->hasTowerTree = true;
      c->hasPFTree = true;
      c->hasTrackTree = true;
    }    
    if(montecarlo && !pa) c->hasGenParticleTree = true;

    c->GetEntry(jentry);

    InitIniJtVar();

    if(kHIMC == sType) pthatIni_ = c->akPu3PF.pthat;
    else if(kPPMC == sType || kPAMC == sType) pthatIni_ = c->ak3Calo.pthat;

    if(hi){
      hiEvtPlaneIni_ = c->evt.hiEvtPlanes[21];                                                  
      TComplex cn1((c->pf.sumpt[0])*(c->pf.vn[2][0]), c->pf.psin[2][0], true);                    
      TComplex cn2((c->pf.sumpt[14])*(c->pf.vn[2][14]), c->pf.psin[2][14], true);                
      TComplex cn = cn1+cn2;                                                                    
      psinIni_ = cn.Theta();      
    }      

    runIni_ = c->evt.run;
    evtIni_ = c->evt.evt;
    lumiIni_ = c->evt.lumi;

    if(hi){
      hiBinIni_ = c->evt.hiBin;
      if(montecarlo) bIni_ = c->genparticle.b;
    }

    //Iterate over jets

    Int_t algMax = 5;
    if(!hi && !pa) algMax = 3;

    for(Int_t algIter = 0; algIter < algMax; algIter++){
      if(algIter == 2){
	if(!montecarlo)
	  continue;
	else{
	  for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	    if(jtIndex[algIter][jtIter] >= 0){
	      std::cout << AlgIniJtCollection[algIter].genpt[jtIndex[algIter][jtIter]] << std::endl;

	      AlgIniJtPt_[algIter][jtIter] = AlgIniJtCollection[algIter].genpt[jtIndex[algIter][jtIter]];
	      AlgIniJtPhi_[algIter][jtIter] = AlgIniJtCollection[algIter].genphi[jtIndex[algIter][jtIter]];
	      AlgIniJtEta_[algIter][jtIter] = AlgIniJtCollection[algIter].geneta[jtIndex[algIter][jtIter]];

	      AlgIniRefPartFlav_[algIter][jtIter] = AlgIniJtCollection[algIter].refparton_flavor[AlgIniJtCollection[algIter].genmatchindex[jtIndex[algIter][jtIter]]];
	    }
	  }
	}
      }
      else{
	for(Int_t jtIter = 0; jtIter < 5; jtIter++){
	  if(jtIndex[algIter][jtIter] >= 0){
	    AlgIniJtPt_[algIter][jtIter] = AlgIniJtCollection[algIter].jtpt[jtIndex[algIter][jtIter]];
	    AlgIniJtPhi_[algIter][jtIter] = AlgIniJtCollection[algIter].jtphi[jtIndex[algIter][jtIter]];
	    AlgIniJtEta_[algIter][jtIter] = AlgIniJtCollection[algIter].jteta[jtIndex[algIter][jtIter]];
	    
	    AlgIniJtRawPt_[algIter][jtIter] = AlgIniJtCollection[algIter].rawpt[jtIndex[algIter][jtIter]];

	    if(montecarlo){
	      AlgIniRefPartFlav_[algIter][jtIter] = AlgIniJtCollection[algIter].refparton_flavor[jtIndex[algIter][jtIter]];
	      AlgIniRefPt_[algIter][jtIter] = AlgIniJtCollection[algIter].refpt[jtIndex[algIter][jtIter]];
	      AlgIniRefPhi_[algIter][jtIter] = AlgIniJtCollection[algIter].refphi[jtIndex[algIter][jtIter]];
	      AlgIniRefEta_[algIter][jtIter] = AlgIniJtCollection[algIter].refeta[jtIndex[algIter][jtIter]];
	    }
	  }
	}
      }
    }
    
    if(!isGen){

      //Iterate over rechits
      
      nRechits_ = 0;
      if(pa){
	for(Int_t rechitIter = 0; rechitIter < c->tower.n; rechitIter++){
	  if(TMath::Abs(c->tower.eta[rechitIter]) < 2.3){
	    rechitPt_[nRechits_] = c->tower.et[rechitIter];
	    rechitVsPt_[nRechits_] = c->tower.vsPt[rechitIter];
	    rechitPhi_[nRechits_] = c->tower.phi[rechitIter];
	    rechitEta_[nRechits_] = c->tower.eta[rechitIter];
	    nRechits_++;
	  }
	}
      }
      
      //Iterate over pf
      
      nPF_ = 0;
      
      for(Int_t pfIter = 0; pfIter < c->pf.nPFpart; pfIter++){
	if(TMath::Abs(c->pf.pfEta[pfIter]) < 2.3){
	  pfPt_[nPF_] = c->pf.pfPt[pfIter];
	  pfVsPt_[nPF_] = c->pf.pfVsPt[pfIter];
	  pfPhi_[nPF_] = c->pf.pfPhi[pfIter];
	  pfEta_[nPF_] = c->pf.pfEta[pfIter];
	  nPF_++;
	}
      }
      
      //Iterate over tracks

      nTrk_ = 0;
      
      for(Int_t trkIter = 0; trkIter < c->track.nTrk; trkIter++){
	if(TMath::Abs(c->track.trkEta[trkIter]) > 2.4) continue;
	
	if(c->track.trkPt[trkIter] <= 0.5) continue;
	
	if(!c->track.highPurity[trkIter]) continue;
	
	if(TMath::Abs(c->track.trkDz1[trkIter]/c->track.trkDzError1[trkIter]) > 3) continue;
	
	if(TMath::Abs(c->track.trkDxy1[trkIter]/c->track.trkDxyError1[trkIter]) > 3) continue;
	
	if(c->track.trkPtError[trkIter]/c->track.trkPt[trkIter] > 0.1) continue;
	
	trkPt_[nTrk_] = c->track.trkPt[trkIter];
	trkPhi_[nTrk_] = c->track.trkPhi[trkIter];
	trkEta_[nTrk_] = c->track.trkEta[trkIter];
	nTrk_++;

	if(nTrk_ > maxTracks - 1){
	  printf("ERROR: Trk arrays not large enough.\n");
	  return(1);
	}
      }
    }
    if(montecarlo){
      nGen_ = 0;
      
      for(Int_t genIter = 0; genIter < c->genparticle.mult; genIter++){
	if(TMath::Abs(c->genparticle.eta[genIter]) > 2.4) continue;
	
	genPt_[nGen_] = c->genparticle.pt[genIter];
	genPhi_[nGen_] = c->genparticle.phi[genIter];
	genEta_[nGen_] = c->genparticle.eta[genIter];
	genSube_[nGen_] = c->genparticle.sube[genIter];
	
	nGen_++;

	if(nGen_ > maxEntrySim - 1){
	  printf("ERROR: Gen arrays not large enough.\n");
	  return(1);
	}
      }
    }

 
    if(!isGen){
      trkIniSKPtCut_ = getSKPtCut(nTrk_, trkPt_, trkPhi_, trkEta_);
      rechitIniSKPtCut_ = getSKPtCut(nRechits_, rechitPt_, rechitPhi_, rechitEta_);
      pfIniSKPtCut_ = getSKPtCut(nPF_, pfPt_, pfPhi_, pfEta_);
    }
    if(montecarlo) genIniSKPtCut_ = getSKPtCut(nGen_, genPt_, genPhi_, genEta_);
    
    if(!isGen){
      rechitTreeIni_p->Fill();
      pfcandTreeIni_p->Fill();
      trkTreeIni_p->Fill();
    }    
    if(montecarlo) genTreeIni_p->Fill();

    jetTreeIni_p->Fill();

    Int_t nEvtsPassed = jetTreeIni_p->GetEntries();

    Bool_t newFile = false;
    if(!pa && nEvtsPassed%nEvtPerFile == 0) newFile = true;
    else if(pa && nEvtsPassed%(2*nEvtPerFile) == 0) newFile = true;

    if(newFile){
      outFile->cd();

      nEvtsOutTag++;

      if(!isGen){
	rechitTreeIni_p->Write("", TObject::kOverwrite);
	pfcandTreeIni_p->Write("", TObject::kOverwrite);
	trkTreeIni_p->Write("", TObject::kOverwrite);
      }
      if(montecarlo) genTreeIni_p->Write("", TObject::kOverwrite);
      jetTreeIni_p->Write("", TObject::kOverwrite);

      CleanupFastJetIniSkim();
      outFile->Close();
      delete outFile;     
      outFile = new TFile(Form("%s_%d_%d.root", outName, num, nEvtsOutTag), "RECREATE");
      InitFastJetIniSkim(sType, isGen);
    }
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

  if(!isGen){
    rechitTreeIni_p->Write("", TObject::kOverwrite);
    pfcandTreeIni_p->Write("", TObject::kOverwrite);
    trkTreeIni_p->Write("", TObject::kOverwrite);
  }
  if(montecarlo) genTreeIni_p->Write("", TObject::kOverwrite);
  jetTreeIni_p->Write("", TObject::kOverwrite);
    
  CleanupFastJetIniSkim();
  outFile->Close();
  delete outFile;

  delete c;

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
  if(argc != 6)
    {
      std::cout << "Usage: makeFastJetIniSkim <inputFile> <sampleType> <outputFile> <#> <isGenBool>" << std::endl;
      return 1;
    }

  int rStatus = -1;

  rStatus = makeFastJetIniSkim(argv[1], sampleType(atoi(argv[2])), argv[3], atoi(argv[4]), Bool_t(atoi(argv[5])));

  return rStatus;
}
