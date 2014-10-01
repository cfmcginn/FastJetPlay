#ifndef getJetFFMoments_h
#define getJetFFMoments_h

#include "fastjet/JetDefinition.hh"
#include "fastjet/PseduoJet.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include "fastjet/Selector.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/contrib/JetFFMoments.hh"

fastjet::JetMedianBackgroundEstimator* bge;

void initBGE(const Double_t rhoJtR, fastjet::JetAlgorithm rhoJtAlg)
{
  fastjet::JetDefinition rhoJtDef(rhoJtAlg, rhoJtR);
  fastjet::AreadDefintion areaDef(fastjet::active_area, fastjet::GhostedAreaSpec(fastjet::SelectorAbsRapMax(2.0)));
  fastjet::Selector rhoRange = fastjet::SelectorDoughnut(0.4, 1.2);
  bge = new bge(rhoRange, rhoJtDef, areaDef);

  return;
}


void setBGEInput(std::vector<fastjet::PseudoJet>* inEvt)
{
  bge->set_particles(*inEvt);

  return;
}


void getJetFFMoments(fastjet::PseudoJet inJt, const Double_t rhoJtR, fastjet::JetAlgorithm rhoJtAlg, std::vector<Double_t>& FFMUnsub_Vect, std::vector<Double_t>& FFMSub_Vect, std::vector<Double_t>& FFMSubBetter_Vect)
{
  fastjet::Subtractor subtractor(bge);

  fastjet::contrib::JetFFMoments FFMUnsub(-0.5, 6.0, 14);
  fastjet::contrib::JetFFMoments FFMSub(-0.5, 6.0, 14, bge);
  fastjet::contrib::JetFFMoments FFMSubBetter(-0.5, 6.0, 14, bge);

  Double_t mu = 25.0;
  FFMSubBetter.set_improved_subtraction(mu);

  FFMUnsub_Vect = FFMUnsub(inJt);
  FFMSub_Vect = FFMSub(inJt);
  FFMSubBetter_Vect = FFMSubBetter(inJt);

  return;
}

#endif
