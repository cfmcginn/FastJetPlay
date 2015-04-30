#ifndef getJtCharge_h
#define getJtCharge_h

#include "fastjet/PseudoJet.hh"

Float_t getJtCharge(fastjet::PseudoJet *inJt)
{
  std::vector<fastjet::PseudoJet> jtConst = inJt->constituents();

  return jtConst[0].user_index();
}

#endif
