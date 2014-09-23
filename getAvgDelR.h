#ifndef getAvgDelR_h
#define getAvgDelR_h

#include <vector>
#include <math.h>
#include "etaPhiFunc.h"
#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

Float_t getAvgDelR(fastjet::PseudoJet inJt, Float_t ptCut, Float_t ptWeight)
{
  Float_t delR = -1;
  
  if(inJt.perp() > ptCut){ 
    std::vector<fastjet::PseudoJet> constituents = inJt.constituents();
    Float_t R_sum = 0.0;
    Float_t pt_sum = 0.0;

    for(Int_t j = 0; j < (Int_t)(constituents.size()); j++){      
      Float_t distance = getDR(inJt.eta(), inJt.phi_std(), constituents[j].eta(), constituents[j].phi_std());
      R_sum += distance*pow(constituents[j].perp(), ptWeight);
      pt_sum += pow(constituents[j].perp(), ptWeight);
    }

    delR = R_sum/pt_sum;
  }
  
  return delR;
}

#endif
