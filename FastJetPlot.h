//=============================================
// Author: Chris McGinn
//
// FastJet Histogram Class (MC)
//
//=============================================
#ifndef FastJetHist_h
#define FastJetHist_h

#include "FastJetAnaSkim.h"

//rechit substruct hist
JetSubstructHist* rechitRawJt_HistPbPbTot_p;
JetSubstructHist* rechitVsJt_HistPbPbTot_p;

JetSubstructHist* rechitRawJt_HistPPTot_p;
JetSubstructHist* rechitVsJt_HistPPTot_p;

JetSubstructHist* rechitRawJt_HistHIMCTot_p;
JetSubstructHist* rechitVsJt_HistHIMCTot_p;

JetSubstructHist* rechitRawJt_HistHIMCQ_p;
JetSubstructHist* rechitVsJt_HistHIMCQ_p;

JetSubstructHist* rechitRawJt_HistHIMCG_p;
JetSubstructHist* rechitVsJt_HistHIMCG_p;

JetSubstructHist* rechitRawJt_HistPPMCTot_p;
JetSubstructHist* rechitVsJt_HistPPMCTot_p;

JetSubstructHist* rechitRawJt_HistPPMCQ_p;
JetSubstructHist* rechitVsJt_HistPPMCQ_p;

JetSubstructHist* rechitRawJt_HistPPMCG_p;
JetSubstructHist* rechitVsJt_HistPPMCG_p;

//pf substruct hist                                                          

JetSubstructHist* pfRawJt_HistPbPbTot_p;
JetSubstructHist* pfVsJt_HistPbPbTot_p;
JetSubstructHist* pfSKJt_HistPbPbTot_p;

JetSubstructHist* pfRawJt_HistPPTot_p;
JetSubstructHist* pfVsJt_HistPPTot_p;
JetSubstructHist* pfSKJt_HistPPTot_p;

JetSubstructHist* pfRawJt_HistHIMCTot_p;
JetSubstructHist* pfVsJt_HistHIMCTot_p;
JetSubstructHist* pfSKJt_HistHIMCTot_p;

JetSubstructHist* pfRawJt_HistHIMCQ_p;
JetSubstructHist* pfVsJt_HistHIMCQ_p;
JetSubstructHist* pfSKJt_HistHIMCQ_p;

JetSubstructHist* pfRawJt_HistHIMCG_p;
JetSubstructHist* pfVsJt_HistHIMCG_p;
JetSubstructHist* pfSKJt_HistHIMCG_p;

JetSubstructHist* pfRawJt_HistPPMCTot_p;
JetSubstructHist* pfVsJt_HistPPMCTot_p;
JetSubstructHist* pfSKJt_HistPPMCTot_p;

JetSubstructHist* pfRawJt_HistPPMCQ_p;
JetSubstructHist* pfVsJt_HistPPMCQ_p;
JetSubstructHist* pfSKJt_HistPPMCQ_p;

JetSubstructHist* pfRawJt_HistPPMCG_p;
JetSubstructHist* pfVsJt_HistPPMCG_p;
JetSubstructHist* pfSKJt_HistPPMCG_p;

//track substruct hist

JetSubstructHist* trkRawJt_HistPbPbTot_p;
JetSubstructHist* trkSKJt_HistPbPbTot_p;

JetSubstructHist* trkRawJt_HistPPTot_p;
JetSubstructHist* trkSKJt_HistPPTot_p;

JetSubstructHist* trkRawJt_HistHIMCTot_p;
JetSubstructHist* trkSKJt_HistHIMCTot_p;

JetSubstructHist* trkRawJt_HistHIMCQ_p;
JetSubstructHist* trkSKJt_HistHIMCQ_p;

JetSubstructHist* trkRawJt_HistHIMCG_p;
JetSubstructHist* trkSKJt_HistHIMCG_p;

JetSubstructHist* trkRawJt_HistPPMCTot_p;
JetSubstructHist* trkSKJt_HistPPMCTot_p;

JetSubstructHist* trkRawJt_HistPPMCQ_p;
JetSubstructHist* trkSKJt_HistPPMCQ_p;

JetSubstructHist* trkRawJt_HistPPMCG_p;
JetSubstructHist* trkSKJt_HistPPMCG_p;

//gen substruct hist

JetSubstructHist* genRawJt_HistHIMCTot_p;
JetSubstructHist* genSKJt_HistHIMCTot_p;
JetSubstructHist* genSUBEJt_HistHIMCTot_p;

JetSubstructHist* genRawJt_HistHIMCQ_p;
JetSubstructHist* genSKJt_HistHIMCQ_p;
JetSubstructHist* genSUBEJt_HistHIMCQ_p;

JetSubstructHist* genRawJt_HistHIMCG_p;
JetSubstructHist* genSKJt_HistHIMCG_p;
JetSubstructHist* genSUBEJt_HistHIMCG_p;

JetSubstructHist* genRawJt_HistPPMCTot_p;
JetSubstructHist* genSKJt_HistPPMCTot_p;
JetSubstructHist* genSUBEJt_HistPPMCTot_p;

JetSubstructHist* genRawJt_HistPPMCQ_p;
JetSubstructHist* genSKJt_HistPPMCQ_p;
JetSubstructHist* genSUBEJt_HistPPMCQ_p;

JetSubstructHist* genRawJt_HistPPMCG_p;
JetSubstructHist* genSKJt_HistPPMCG_p;
JetSubstructHist* genSUBEJt_HistPPMCG_p;

void GetHistForPlot(TFile* pbpbFile_p, TFile* ppFile_p, TFile* hiMCFile_p, TFile* ppMCFile_p,  const std::string evtSelAlg);
//void CleanHistAll(sampleType sType);
//void CleanSubstructAll(sampleType sType);


void GetHistForPlot(TFile* pbpbFile_p, TFile* ppFile_p, TFile* hiMCFile_p, TFile* ppMCFile_p,  const std::string evtSelAlg)
{
  if(pbpbFile_p != 0){
    GetJetSubstructHist(pbpbFile_p, rechitRawJt_HistPbPbTot_p, kHIDATA, Form("%s_rechitRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, rechitVsJt_HistPbPbTot_p, kHIDATA, Form("%s_rechitVsTot", evtSelAlg.c_str()));

    GetJetSubstructHist(pbpbFile_p, pfRawJt_HistPbPbTot_p, kHIDATA, Form("%s_pfRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, pfVsJt_HistPbPbTot_p, kHIDATA, Form("%s_pfVsTot", evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, pfSKJt_HistPbPbTot_p, kHIDATA, Form("%s_pfSKTot", evtSelAlg.c_str()));

    GetJetSubstructHist(pbpbFile_p, trkRawJt_HistPbPbTot_p, kHIDATA, Form("%s_trkRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, trkSKJt_HistPbPbTot_p, kHIDATA, Form("%s_trkSKTot", evtSelAlg.c_str()));
  }

  if(ppFile_p != 0){
    GetJetSubstructHist(ppFile_p, rechitRawJt_HistPPTot_p, kPPDATA, Form("%s_rechitRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, rechitVsJt_HistPPTot_p, kPPDATA, Form("%s_rechitVsTot", evtSelAlg.c_str()));

    GetJetSubstructHist(ppFile_p, pfRawJt_HistPPTot_p, kPPDATA, Form("%s_pfRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, pfVsJt_HistPPTot_p, kPPDATA, Form("%s_pfVsTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, pfSKJt_HistPPTot_p, kPPDATA, Form("%s_pfSKTot", evtSelAlg.c_str()));

    GetJetSubstructHist(ppFile_p, trkRawJt_HistPPTot_p, kPPDATA, Form("%s_trkRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, trkSKJt_HistPPTot_p, kPPDATA, Form("%s_trkSKTot", evtSelAlg.c_str()));
  }
  std::cout << "BREAK 1" << std::endl;
  if(hiMCFile_p != 0){
    GetJetSubstructHist(hiMCFile_p, rechitRawJt_HistHIMCTot_p, kHIMC, Form("%s_rechitRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, rechitVsJt_HistHIMCTot_p, kHIMC, Form("%s_rechitVsTot", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, rechitRawJt_HistHIMCQ_p, kHIMC, Form("%s_rechitRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, rechitVsJt_HistHIMCQ_p, kHIMC, Form("%s_rechitVsQ", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, rechitRawJt_HistHIMCG_p, kHIMC, Form("%s_rechitRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, rechitVsJt_HistHIMCG_p, kHIMC, Form("%s_rechitVsG", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, pfRawJt_HistHIMCTot_p, kHIMC, Form("%s_pfRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfVsJt_HistHIMCTot_p, kHIMC, Form("%s_pfVsTot", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfSKJt_HistHIMCTot_p, kHIMC, Form("%s_pfSKTot", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, pfRawJt_HistHIMCQ_p, kHIMC, Form("%s_pfRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfVsJt_HistHIMCQ_p, kHIMC, Form("%s_pfVsQ", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfSKJt_HistHIMCQ_p, kHIMC, Form("%s_pfSKQ", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, pfRawJt_HistHIMCG_p, kHIMC, Form("%s_pfRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfVsJt_HistHIMCG_p, kHIMC, Form("%s_pfVsG", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfSKJt_HistHIMCG_p, kHIMC, Form("%s_pfSKG", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, trkRawJt_HistHIMCTot_p, kHIMC, Form("%s_trkRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trkSKJt_HistHIMCTot_p, kHIMC, Form("%s_trkSKTot", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, trkRawJt_HistHIMCQ_p, kHIMC, Form("%s_trkRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trkSKJt_HistHIMCQ_p, kHIMC, Form("%s_trkSKQ", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, trkRawJt_HistHIMCG_p, kHIMC, Form("%s_trkRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trkSKJt_HistHIMCG_p, kHIMC, Form("%s_trkSKG", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, genRawJt_HistHIMCTot_p, kHIMC, Form("%s_genRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKJt_HistHIMCTot_p, kHIMC, Form("%s_genSKTot", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSUBEJt_HistHIMCTot_p, kHIMC, Form("%s_genSUBETot", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, genRawJt_HistHIMCQ_p, kHIMC, Form("%s_genRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKJt_HistHIMCQ_p, kHIMC, Form("%s_genSKQ", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSUBEJt_HistHIMCQ_p, kHIMC, Form("%s_genSUBEQ", evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, genRawJt_HistHIMCG_p, kHIMC, Form("%s_genRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKJt_HistHIMCG_p, kHIMC, Form("%s_genSKG", evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSUBEJt_HistHIMCG_p, kHIMC, Form("%s_genSUBEG", evtSelAlg.c_str()));
  }
  std::cout << "BREAK 2" << std::endl;
  if(ppMCFile_p != 0){
    GetJetSubstructHist(ppMCFile_p, rechitRawJt_HistPPMCTot_p, kPPMC, Form("%s_rechitRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, rechitVsJt_HistPPMCTot_p, kPPMC, Form("%s_rechitVsTot", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, rechitRawJt_HistPPMCQ_p, kPPMC, Form("%s_rechitRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, rechitVsJt_HistPPMCQ_p, kPPMC, Form("%s_rechitVsQ", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, rechitRawJt_HistPPMCG_p, kPPMC, Form("%s_rechitRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, rechitVsJt_HistPPMCG_p, kPPMC, Form("%s_rechitVsG", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, pfRawJt_HistPPMCTot_p, kPPMC, Form("%s_pfRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfVsJt_HistPPMCTot_p, kPPMC, Form("%s_pfVsTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfSKJt_HistPPMCTot_p, kPPMC, Form("%s_pfSKTot", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, pfRawJt_HistPPMCQ_p, kPPMC, Form("%s_pfRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfVsJt_HistPPMCQ_p, kPPMC, Form("%s_pfVsQ", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfSKJt_HistPPMCQ_p, kPPMC, Form("%s_pfSKQ", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, pfRawJt_HistPPMCG_p, kPPMC, Form("%s_pfRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfVsJt_HistPPMCG_p, kPPMC, Form("%s_pfVsG", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfSKJt_HistPPMCG_p, kPPMC, Form("%s_pfSKG", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, trkRawJt_HistPPMCTot_p, kPPMC, Form("%s_trkRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trkSKJt_HistPPMCTot_p, kPPMC, Form("%s_trkSKTot", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, trkRawJt_HistPPMCQ_p, kPPMC, Form("%s_trkRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trkSKJt_HistPPMCQ_p, kPPMC, Form("%s_trkSKQ", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, trkRawJt_HistPPMCG_p, kPPMC, Form("%s_trkRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trkSKJt_HistPPMCG_p, kPPMC, Form("%s_trkSKG", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, genRawJt_HistPPMCTot_p, kPPMC, Form("%s_genRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKJt_HistPPMCTot_p, kPPMC, Form("%s_genSKTot", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSUBEJt_HistPPMCTot_p, kPPMC, Form("%s_genSUBETot", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, genRawJt_HistPPMCQ_p, kPPMC, Form("%s_genRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKJt_HistPPMCQ_p, kPPMC, Form("%s_genSKQ", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSUBEJt_HistPPMCQ_p, kPPMC, Form("%s_genSUBEQ", evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, genRawJt_HistPPMCG_p, kPPMC, Form("%s_genRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKJt_HistPPMCG_p, kPPMC, Form("%s_genSKG", evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSUBEJt_HistPPMCG_p, kPPMC, Form("%s_genSUBEG", evtSelAlg.c_str()));
  }
  std::cout << "BREAK 3" << std::endl;

  return;
}

/*
void CleanHistAll(sampleType sType)
{
  Bool_t isMC = isMonteCarlo(sType);

  CleanupJetSubstructHist(rechitRawJt_HistTot_p, sType);
  CleanupJetSubstructHist(rechitVsJt_HistTot_p, sType);

  if(isMC){
    CleanupJetSubstructHist(rechitRawJt_HistQ_p, sType);
    CleanupJetSubstructHist(rechitVsJt_HistQ_p, sType);

    CleanupJetSubstructHist(rechitRawJt_HistG_p, sType);
    CleanupJetSubstructHist(rechitVsJt_HistG_p, sType);
  }

  CleanupJetSubstructHist(pfRawJt_HistTot_p, sType);
  CleanupJetSubstructHist(pfVsJt_HistTot_p, sType);
  CleanupJetSubstructHist(pfSKJt_HistTot_p, sType);

  if(isMC){
    CleanupJetSubstructHist(pfRawJt_HistQ_p, sType);
    CleanupJetSubstructHist(pfVsJt_HistQ_p, sType);
    CleanupJetSubstructHist(pfSKJt_HistQ_p, sType);
    
    CleanupJetSubstructHist(pfRawJt_HistG_p, sType);
    CleanupJetSubstructHist(pfVsJt_HistG_p, sType);
    CleanupJetSubstructHist(pfSKJt_HistG_p, sType);
  }

  CleanupJetSubstructHist(trkRawJt_HistTot_p, sType);
  CleanupJetSubstructHist(trkSKJt_HistTot_p, sType);

  if(isMC){
    CleanupJetSubstructHist(trkRawJt_HistQ_p, sType);
    CleanupJetSubstructHist(trkSKJt_HistQ_p, sType);
    
    CleanupJetSubstructHist(trkRawJt_HistG_p, sType);
    CleanupJetSubstructHist(trkSKJt_HistG_p, sType);
  }

  if(isMC){
    CleanupJetSubstructHist(genRawJt_HistTot_p, sType);
    CleanupJetSubstructHist(genSKJt_HistTot_p, sType);
    CleanupJetSubstructHist(genSUBEJt_HistTot_p, sType);

    CleanupJetSubstructHist(genRawJt_HistQ_p, sType);
    CleanupJetSubstructHist(genSKJt_HistQ_p, sType);
    CleanupJetSubstructHist(genSUBEJt_HistQ_p, sType);
    
    CleanupJetSubstructHist(genRawJt_HistG_p, sType);
    CleanupJetSubstructHist(genSKJt_HistG_p, sType);
    CleanupJetSubstructHist(genSUBEJt_HistG_p, sType);
  }

  return;
}


void CleanSubstructAll(sampleType sType)
{
  Bool_t isMC = isMonteCarlo(sType);

  delete rechitRawJt_HistTot_p;
  delete rechitVsJt_HistTot_p;

  delete pfRawJt_HistTot_p;
  delete pfVsJt_HistTot_p;
  delete pfSKJt_HistTot_p;

  delete trkRawJt_HistTot_p;
  delete trkSKJt_HistTot_p;

  if(isMC){
    delete genRawJt_HistTot_p;
    delete genSKJt_HistTot_p;
    delete genSUBEJt_HistTot_p;

    delete rechitRawJt_HistQ_p;
    delete rechitVsJt_HistQ_p;
    
    delete pfRawJt_HistQ_p;
    delete pfVsJt_HistQ_p;
    delete pfSKJt_HistQ_p;
    
    delete trkRawJt_HistQ_p;
    delete trkSKJt_HistQ_p;
    
    delete genRawJt_HistQ_p;
    delete genSKJt_HistQ_p;
    delete genSUBEJt_HistQ_p;
    
    delete rechitRawJt_HistG_p;
    delete rechitVsJt_HistG_p;
    
    delete pfRawJt_HistG_p;
    delete pfVsJt_HistG_p;
    delete pfSKJt_HistG_p;
    
    delete trkRawJt_HistG_p;
    delete trkSKJt_HistG_p;
    
    delete genRawJt_HistG_p;
    delete genSKJt_HistG_p;
    delete genSUBEJt_HistG_p;
  }

  return;
}
*/

#endif
