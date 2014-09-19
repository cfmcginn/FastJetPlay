#include <vector>
#include <math.h>
#include "etaPhiFunc.h"
#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

Float_t getAveEta(std::vector<fastjet::PseudoJet>* inConst)
{
  Float_t etaSum = 0.0;
  Float_t ptSum = 0.0;

  for(Int_t iter = 0; iter < inConst.size(); iter++){
    etaSum += inConst.eta()*pow(inConst.perp(), 2.0);
    ptSum += pow(inConst.perp(), 2.0);
  }

  return etaSum/ptSum;
}

Float_t getAvePhi(std::vector<fastjet::PseudoJet>* inConst)
{
  Float_t phiSum = 0.0;
  Float_t ptSum = 0.0;

  for(Int_t iter = 0; iter < inConst.size(); iter++){
    phiSum += inConst.phi_std()*pow(inConst.perp(), 2.0);
    ptSum += pow(inConst.perp(), 2.0);
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

Float_t getSigma(fastjet::PseudoJet* inJt)
{
  std::vector<fastjet::PseudoJet> jtConst = inJt->constituents();

  Float_t aveEta = getAveEta(&jtConst);
  Float_t avePhi = getAvePhi(&jtConst);

  Float_t matElement[4] = {0.0, 0.0, 0.0, 0.0};
  Float_t ptSum = 0.0;

  Float_t eigen1 = 0.0;
  Float_t eigen2 = 0.0;

  for(Int_t iter = 0; iter < jtConst.size(); iter++){
    matElement[0] += pow(jtConst.perp(), 2.0)*pow(jtConst.eta() - aveEta, 2.0);
    matElement[1] -= pow(jtConst.perp(), 2.0)*TMath::Abs(jtConst.eta() - aveEta)*TMath::Abs(getDPHI(jtConst.phi_std(), avePhi));
    matElement[2] -= pow(jtConst.perp(), 2.0)*TMath::Abs(jtConst.eta() - aveEta)*TMath::Abs(getDPHI(jtConst.phi_std(), avePhi));
    matElement[3] += pow(jtConst.perp(), 2.0)*pow(getDPHI(jtConst.phi_std(), avePhi), 2.0);
  }

  getEigenN2(matElement, eigen1, eigen2);

  eigen1 = eigen1/ptSum;
  eigen2 = eigen2/ptSum;

  return TMath::Sqrt(eigen1*eigen1 + eigen2*eigen2);
}
