#ifndef getSigma_h
#define getSigma_h

#include <vector>
#include <math.h>
#include "etaPhiFunc.h"
#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

Float_t internalSig[3] = {0.0, 0.0, 0.0};

Float_t getAveEta(std::vector<fastjet::PseudoJet>* inConst)
{
  Float_t etaSum = 0.0;
  Float_t ptSum = 0.0;

  for(Int_t iter = 0; iter < (Int_t)(inConst->size()); iter++){
    etaSum += inConst->at(iter).eta()*pow(inConst->at(iter).perp(), 2.0);
    ptSum += pow(inConst->at(iter).perp(), 2.0);
  }

  return etaSum/ptSum;
}

Float_t getAvePhi(std::vector<fastjet::PseudoJet>* inConst)
{
  Float_t phiSum = 0.0;
  Float_t ptSum = 0.0;

  for(Int_t iter = 0; iter < (Int_t)(inConst->size()); iter++){
    phiSum += inConst->at(iter).phi_std()*pow(inConst->at(iter).perp(), 2.0);
    ptSum += pow(inConst->at(iter).perp(), 2.0);
  }

  return phiSum/ptSum;
}

void getEigenN2(Float_t inMatrix[4], Float_t &eigen1, Float_t &eigen2)
{
  Float_t sqrtTerm = TMath::Sqrt(pow(inMatrix[0], 2.0) + pow(inMatrix[3], 2.0) - 2*inMatrix[0]*inMatrix[3] + 4*inMatrix[1]*inMatrix[2]);
  eigen1 = (inMatrix[0] + inMatrix[3] + sqrtTerm)/2;
  eigen2 = (inMatrix[0] + inMatrix[3] - sqrtTerm)/2;

  return;
}

void calcSigma(fastjet::PseudoJet* inJt)
{
  std::vector<fastjet::PseudoJet> jtConst = inJt->constituents();

  Float_t aveEta = getAveEta(&jtConst);
  Float_t avePhi = getAvePhi(&jtConst);

  Float_t matElement[4] = {0.0, 0.0, 0.0, 0.0};
  Float_t ptSum = 0.0;

  Float_t eigen1 = 0.0;
  Float_t eigen2 = 0.0;

  for(Int_t iter = 0; iter < (Int_t)(jtConst.size()); iter++){
    ptSum += jtConst[iter].perp()*jtConst[iter].perp();

    matElement[0] += pow(jtConst[iter].perp(), 2.0)*pow(jtConst[iter].eta() - aveEta, 2.0);
    matElement[1] -= pow(jtConst[iter].perp(), 2.0)*TMath::Abs(jtConst[iter].eta() - aveEta)*TMath::Abs(getDPHI(jtConst[iter].phi_std(), avePhi));
    matElement[2] -= pow(jtConst[iter].perp(), 2.0)*TMath::Abs(jtConst[iter].eta() - aveEta)*TMath::Abs(getDPHI(jtConst[iter].phi_std(), avePhi));
    matElement[3] += pow(jtConst[iter].perp(), 2.0)*pow(getDPHI(jtConst[iter].phi_std(), avePhi), 2.0);
  }

  getEigenN2(matElement, eigen1, eigen2);

  internalSig[0] = TMath::Sqrt(eigen1/ptSum);
  internalSig[1] = TMath::Sqrt(eigen2/ptSum);
  internalSig[2] = TMath::Sqrt(internalSig[0]*internalSig[0] + internalSig[1]*internalSig[1]);

  return;
}

Float_t getSigma(Int_t sigPos)
{
  if(sigPos > 2 || sigPos < 0) return -1;
  else return internalSig[sigPos];
}

#endif
