#ifndef getJtCharge_h
#define getJtCharge_h

#include "fastjet/PseudoJet.hh"
#include "TMath.h"

Float_t getJtCharge(fastjet::PseudoJet *inJt, Double_t inBeta)
{
  std::vector<fastjet::PseudoJet> jtConst = inJt->constituents();

  Float_t jtChg = 0;

  for(Int_t iter = 0; iter < (Int_t)(jtConst.size()); iter++){
    jtChg += jtConst[iter].user_index()*TMath::Power(jtConst[iter].perp(), inBeta); 
  }

  return jtChg/TMath::Power(inJt->perp(), inBeta);
}

#endif
