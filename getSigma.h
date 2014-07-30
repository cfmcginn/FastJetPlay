#include <vector>

#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"

Float_t getAveEta(std::vector<fastjet::PseudoJet>* inConst)
{
  Float_t aveEta = 0;


}

Float_t getAvePhi(std::vector<fastjet::PseudoJet>* inConst)
{
  Float_t avePhi = 0;
}


Float_t getSigma(fastjet::PseudoJet* inJt)
{
  std::vector<fastjet::PseudoJet> jtConst = inJt->constituents();


}
