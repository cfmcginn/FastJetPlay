#ifndef getPTD_h
#define getPTD_h

#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"

Float_t getPTD(fastjet::PseudoJet inJt)
{
  Float_t numPTD = 0;
  Float_t denomPTD = 0;

  std::vector<fastjet::PseudoJet> jtConst = inJt.constituents();

  for(Int_t iter = 0; iter < (Int_t)(jtConst.size()); iter++){
    numPTD += (jtConst[iter].perp())*(jtConst[iter].perp());
    denomPTD += jtConst[iter].perp();
  }

  return TMath::Sqrt(numPTD)/denomPTD;
}

#endif
