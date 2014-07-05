#include <vector>
#include "TMath.h"

const Int_t etaBins = 12;
const Int_t phiBins = 16;

const Float_t etaWidth = 4.8/etaBins;
const Float_t phiWidth = 2.0*TMath::Pi()/phiBins;

Float_t etaSKGrid[etaBins+1];
Float_t phiSKGrid[phiBins+1];
std::vector<Float_t>* etaPhiSKGrid_PartPt_p[etaBins][phiBins];
Float_t etaPhiSKGrid_Sum[etaBins][phiBins];

void InitEtaSKGrid()
{
  for(Int_t iter = 0; iter < etaBins+1; iter++){
    etaSKGrid[iter] = -2.4 + iter*etaWidth;
  }
  return;
}

void InitPhiSKGrid()
{
  for(Int_t iter = 0; iter < phiBins+1; iter++){
    phiSKGrid[iter] = -TMath::Pi() + iter*phiWidth;
  }
  return;
}


void testSKGrids()
{
  for(Int_t iter = 0; iter < etaBins+1; iter++){
    std::cout << etaSKGrid[iter] << std::endl;
  }

  for(Int_t iter = 0; iter < phiBins+1; iter++){
    std::cout << phiSKGrid[iter] << std::endl;
  }

  return;
}


void InitSKGridVect()
{
  for(Int_t etaIter = 0; etaIter < etaBins; etaIter++){
    for(Int_t phiIter = 0; phiIter < phiBins; phiIter++){
      etaPhiSKGrid_PartPt_p[etaIter][phiIter] = new std::vector<Float_t>;
    }
  }
  return;
}


void CleanSKGridVect()
{
  for(Int_t etaIter = 0; etaIter < etaBins; etaIter++){
    for(Int_t phiIter = 0; phiIter < phiBins; phiIter++){
      delete etaPhiSKGrid_PartPt_p[etaIter][phiIter];
      etaPhiSKGrid_PartPt_p[etaIter][phiIter] = 0;
    }
  }
  return;
}


void FillSKGridVect(Int_t nPart, Float_t partPt[], Float_t partPhi[], Float_t partEta[])
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

    etaPhiSKGrid_PartPt_p[etaBin][phiBin]->push_back(partPt[partIter]);
  }

  return;
}


void SumSKGridVect(Float_t ptCut)
{
  for(Int_t etaIter = 0; etaIter < etaBins; etaIter++){
    for(Int_t phiIter = 0; phiIter < phiBins; phiIter++){
      etaPhiSKGrid_Sum[etaIter][phiIter] = 0;
      for(Int_t partIter = 0; partIter < (Int_t)etaPhiSKGrid_PartPt_p[etaIter][phiIter]->size(); partIter++){
	if(etaPhiSKGrid_PartPt_p[etaIter][phiIter]->at(partIter) < ptCut) continue;

	etaPhiSKGrid_Sum[etaIter][phiIter] += etaPhiSKGrid_PartPt_p[etaIter][phiIter]->at(partIter);
      }
    }
  }

  return;
}


Bool_t isSKMedianZero()
{
  Int_t zeroCount = 0;
  for(Int_t etaIter = 0; etaIter < etaBins; etaIter++){
    for(Int_t phiIter = 0; phiIter < phiBins; phiIter++){
      if(etaPhiSKGrid_Sum[etaIter][phiIter] < .01) zeroCount++;
    }
  }

  if(zeroCount >= etaBins*phiBins/2.0) return true;
  else return false;
}


Float_t getSKPtCut(Int_t nPart, Float_t partPt[], Float_t partPhi[], Float_t partEta[])
{
  InitSKGridVect();
  FillSKGridVect(nPart, partPt, partPhi, partEta);

  Float_t minSKPtCut;
  Float_t lowSKPtCut = 0.5;
  Float_t hiSKPtCut = 10.0;
  Float_t epsSK = .00001;

  while(hiSKPtCut - lowSKPtCut > epsSK){
    minSKPtCut = (hiSKPtCut + lowSKPtCut)/2.0;
    SumSKGridVect(minSKPtCut);
    if(isSKMedianZero()) hiSKPtCut = minSKPtCut;
    else lowSKPtCut = minSKPtCut;
  }

  CleanSKGridVect();

  return minSKPtCut;
}
