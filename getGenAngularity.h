#ifndef getGenAngularity_h
#define getGenAngularity_h


#include "TMath.h"
#include "etaPhiFunc.h"
#include "fastjet/PseudoJet.hh"

Float_t getGenAngularity(fastjet::PseudoJet *inJt, Float_t jtR = 0.3, Float_t ptWeight = 1.0, Float_t rWeight = 1.0)
{
  Float_t genAngularity = 0;

  std::vector<fastjet::PseudoJet> jtConst = inJt->constituents();

  for(Int_t iter = 0; iter < (Int_t)(jtConst.size()); iter++){
    Float_t constDelR = getDR(jtConst[iter].eta(), jtConst[iter].phi_std(), inJt->eta(), inJt->phi_std());

    genAngularity += TMath::Power(jtConst[iter].perp()/inJt->perp(), ptWeight)*TMath::Power(constDelR/jtR, rWeight);
  }

  return genAngularity;
}

#endif
