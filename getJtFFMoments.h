#ifndef getJetFFMoments_h
#define getJetFFMoments_h

#include "fastjet/JetDefinition.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include "fastjet/Selector.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/contrib/JetFFMoments.hh"

void getJtFFMoments(fastjet::PseudoJet inJt, const Double_t rhoJtR, fastjet::JetAlgorithm rhoJtAlg, fastjet::AreaDefinition areaDef, std::vector<fastjet::PseudoJet>* inEvt, Int_t nFF, Float_t FFLow, Float_t FFHi, Float_t outFFMUnsub[], Float_t outFFMSub[], Float_t outFFMSubBetter[])
{
  fastjet::JetDefinition rhoJtDef(rhoJtAlg, rhoJtR);
  fastjet::Selector rhoRange = fastjet::SelectorDoughnut(0.4, 1.2);
  fastjet::JetMedianBackgroundEstimator bge(rhoRange, rhoJtDef, areaDef);
  fastjet::Subtractor subtractor(&bge);

  fastjet::contrib::JetFFMoments FFMUnsub(FFLow, FFHi, nFF);
  fastjet::contrib::JetFFMoments FFMSub(FFLow, FFHi, nFF, &bge);
  fastjet::contrib::JetFFMoments FFMSubBetter(FFLow, FFHi, nFF, &bge);

  Double_t mu = 25.0;
  FFMSubBetter.set_improved_subtraction(mu, rhoRange, *inEvt, rhoJtDef, areaDef);

  bge.set_particles(*inEvt);

  std::vector<Double_t> FFMUnsub_Vect = FFMUnsub(inJt);
  std::vector<Double_t> FFMSub_Vect = FFMSub(inJt);
  std::vector<Double_t> FFMSubBetter_Vect = FFMSubBetter(inJt);

  for(Int_t FFIter = 0; FFIter < nFF; FFIter++){
    outFFMUnsub[FFIter] = FFMUnsub_Vect[FFIter];
    outFFMSub[FFIter] = FFMSub_Vect[FFIter];
    outFFMSubBetter[FFIter] = FFMSubBetter_Vect[FFIter];
  }

  return;
}

#endif
