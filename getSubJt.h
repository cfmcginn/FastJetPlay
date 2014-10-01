#ifndef getSubJt_h
#define getSubJt_h

#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

void getSubJt(fastjet::PseudoJet inJt, const Double_t subJtR, fastjet::JetAlgorithm subJtAlg, Int_t nSubJt, Float_t subPt[], Float_t subPhi[], Float_t subEta[])
{
  fastjet::JetDefinition subJtDef(subJtAlg, subJtR, fastjet::E_scheme, fastjet::Best);
  fastjet::ClusterSequence subCS(inJt.constituents(), subJtDef);
  std::vector<fastjet::PseudoJet> subJts = fastjet::sorted_by_pt(subCS.inclusive_jets());

  if(nSubJt > (Int_t)subJts.size()) nSubJt = subJts.size();

  for(Int_t subIter = 0; subIter < nSubJt; subIter++){
    subPt[subIter] = subJts[subIter].perp();
    subPhi[subIter] = subJts[subIter].phi_std();
    subEta[subIter] = subJts[subIter].eta();
  }

  subJts.clear();
  return;
}

#endif
