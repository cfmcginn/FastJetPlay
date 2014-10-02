#ifndef getTau_h
#define getTau_h

#include "fastjet/PseudoJet.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"
#include "fastjet/contrib/WinnerTakeAllRecombiner.hh"

const fastjet::contrib::WTA_KT_Axes axisMode;

Float_t getTau(fastjet::PseudoJet inJt, Float_t ptCut, Int_t tauNumber, Double_t beta)
{
  Float_t tau = -1;

  if(inJt.perp() > ptCut){
    fastjet::contrib::UnnormalizedMeasure measureSpec(beta);
    fastjet::contrib::Nsubjettiness nSub(tauNumber, axisMode, measureSpec);
    tau = nSub(inJt);
  }

  return tau;
}

Float_t getTauRatio(fastjet::PseudoJet inJt, Float_t ptCut, Int_t tauNum, Int_t tauDenom, Double_t beta)
{
  Float_t tauR = -1;
  
  if(inJt.perp() > ptCut){       
    fastjet::contrib::UnnormalizedMeasure measureSpec(beta);
    fastjet::contrib::NsubjettinessRatio nSub(tauNum, tauDenom, axisMode, measureSpec);
    tauR = nSub(inJt);      
  }  

  return tauR;
}

#endif
