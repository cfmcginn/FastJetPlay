#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"
#include "fastjet/contrib/WinnerTakeAllRecombiner.hh"

const fastjet::contrib::WTA_KT_Axes axisMode;

Float_t getTau(fastjet::PseudoJet inJt, Float_t ptCut, Int_t tauNumber, Double_t beta)
{
  Float_t tau;
  
  fastjet::contrib::UnnormalizedMeasure measureSpec(beta);

  if(inJt.perp() > ptCut){
    fastjet::contrib::Nsubjettiness nSub(tauNumber, axisMode, measureSpec);
    tau = nSub(inJt);
  }
  else tau = -1;
  
  return tau;
}

Float_t getTauRatio(fastjet::PseudoJet inJt, Float_t ptCut, Int_t tauNum, Int_t tauDenom, Double_t beta)
{
  Float_t tauR;
  
  fastjet::contrib::UnnormalizedMeasure measureSpec(beta);
  
  if(inJt.perp() > ptCut){       
    fastjet::contrib::NsubjettinessRatio nSub(tauNum, tauDenom, axisMode, measureSpec);
    tauR = nSub(inJt);      
  }  
  else tauR = -1;

  return tauR;
}
