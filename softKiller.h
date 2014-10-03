#ifndef softKiller_h
#define softKiller_h

#include <algorithm>
#include <iostream>
#include "TMath.h"

const Int_t etaBins = 12;
const Int_t phiBins = 16;

const Float_t etaWidth = 4.8/etaBins;
const Float_t phiWidth = 2.0*TMath::Pi()/phiBins;

Float_t etaSKGrid[etaBins+1];
Float_t phiSKGrid[phiBins+1];
Float_t etaPhiSKGrid_PartPt[etaBins*phiBins];

void InitEtaSKGrid()
{
  for(Int_t iter = 0; iter < etaBins+1; iter++){
    etaSKGrid[iter] = -2.4 + iter*etaWidth;
  }
  std::cout << "Init Eta Grid" << std::endl;
  return;
}

void InitPhiSKGrid()
{
  for(Int_t iter = 0; iter < phiBins+1; iter++){
    phiSKGrid[iter] = -TMath::Pi() + iter*phiWidth;
  }
  std::cout << "Init Phi Grid" << std::endl;
  return;
}


void InitSKGrid()
{
  for(Int_t iter = 0; iter < etaBins*phiBins; iter++){
    etaPhiSKGrid_PartPt[iter] = 0;
  }
  return;
}


void FillSKGrid(Int_t nPart, Float_t partPt[], Float_t partPhi[], Float_t partEta[])
{
  for(Int_t partIter = 0; partIter < nPart; partIter++){
    Int_t etaBin = -1;
    Int_t phiBin = -1;
    
    for(Int_t etaIter = 0; etaIter < etaBins; etaIter++){
      if(partEta[partIter] > etaSKGrid[etaIter] && partEta[partIter] < etaSKGrid[etaIter+1]){
	etaBin = etaIter;
	break;
      }
    }
    
    for(Int_t phiIter = 0; phiIter < phiBins; phiIter++){
      if(partPhi[partIter] > phiSKGrid[phiIter] && partPhi[partIter] < phiSKGrid[phiIter+1]){
	phiBin = phiIter;
	break;
      }
    }
    
    if(etaPhiSKGrid_PartPt[etaBin*phiBins + phiBin] < partPt[partIter]){
      etaPhiSKGrid_PartPt[etaBin*phiBins + phiBin] = partPt[partIter];
    }
  }  
  return;
}
  

void testSKGrids()
{
  std::cout << "Output SKGrid: " << std::endl;
  for(Int_t iter = 0; iter < etaBins*phiBins; iter++){
    std::cout << "   Iter " << iter << ": " << etaPhiSKGrid_PartPt[iter] << std::endl;
  }

  return;
}


Float_t getSKMedianPt()
{
  std::sort(etaPhiSKGrid_PartPt, etaPhiSKGrid_PartPt + etaBins*phiBins);
  if((etaBins*phiBins)%2 == 0) return etaPhiSKGrid_PartPt[(etaBins*phiBins)/2 - 1] + .0001;
  else return etaPhiSKGrid_PartPt[(etaBins*phiBins - 1)/2] + .0001;
}


Float_t getSKPtCut(Int_t nPart, Float_t partPt[], Float_t partPhi[], Float_t partEta[])
{
  InitSKGrid();
  FillSKGrid(nPart, partPt, partPhi, partEta);

  Float_t skCut = getSKMedianPt();
  if(skCut < 0.010) skCut = 0.010;
  return skCut;
}


/*
Use:
  InitSKEtaGrid;
  InitSKPhiGrid;
  for(Int_t iter = 0; iter < nEvents; iter++){
    // Get entries
    InitSKGrid;
    eventSKPtCut = getSKPtCut(nPart, partPt, partPhi, partEta);
  }
*/

#endif
