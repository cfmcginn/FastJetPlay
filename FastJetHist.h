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
JetSubstructHist* rechitRawJt_HistTot_p;
JetSubstructHist* rechitVsJt_HistTot_p;

JetSubstructHist* rechitRawJt_HistQ_p;
JetSubstructHist* rechitVsJt_HistQ_p;

JetSubstructHist* rechitRawJt_HistG_p;
JetSubstructHist* rechitVsJt_HistG_p;

//pf substruct hist                                                          

JetSubstructHist* pfRawJt_HistTot_p;
JetSubstructHist* pfVsJt_HistTot_p;
JetSubstructHist* pfSKJt_HistTot_p;

JetSubstructHist* pfRawJt_HistQ_p;
JetSubstructHist* pfVsJt_HistQ_p;
JetSubstructHist* pfSKJt_HistQ_p;

JetSubstructHist* pfRawJt_HistG_p;
JetSubstructHist* pfVsJt_HistG_p;
JetSubstructHist* pfSKJt_HistG_p;

//track substruct hist

JetSubstructHist* trkRawJt_HistTot_p;
JetSubstructHist* trkSKJt_HistTot_p;
JetSubstructHist* trk3CutJt_HistTot_p;

JetSubstructHist* trkRawJt_HistQ_p;
JetSubstructHist* trkSKJt_HistQ_p;
JetSubstructHist* trk3CutJt_HistQ_p;

JetSubstructHist* trkRawJt_HistG_p;
JetSubstructHist* trkSKJt_HistG_p;
JetSubstructHist* trk3CutJt_HistG_p;

//gen substruct hist

JetSubstructHist* genRawJt_HistTot_p;
JetSubstructHist* genSKJt_HistTot_p;
JetSubstructHist* genSUBEJt_HistTot_p;
JetSubstructHist* genChgJt_HistTot_p;
JetSubstructHist* genSKChgJt_HistTot_p;

JetSubstructHist* genRawJt_HistQ_p;
JetSubstructHist* genSKJt_HistQ_p;
JetSubstructHist* genSUBEJt_HistQ_p;
JetSubstructHist* genChgJt_HistQ_p;
JetSubstructHist* genSKChgJt_HistQ_p;

JetSubstructHist* genRawJt_HistG_p;
JetSubstructHist* genSKJt_HistG_p;
JetSubstructHist* genSUBEJt_HistG_p;
JetSubstructHist* genChgJt_HistG_p;
JetSubstructHist* genSKChgJt_HistG_p;

void BookHist(sampleType sType, const std::string evtSelAlg);
void ScaleHistAll(sampleType sType);
void WriteHistAll(TFile* outFile_p, sampleType sType, const std::string evtSelAlg);
void CleanHistAll(sampleType sType);
void CleanSubstructAll(sampleType sType);

void BookHist(sampleType sType, const std::string evtSelAlg)
{
  Bool_t isMC = isMonteCarlo(sType);

  InitJetSubstructHist(rechitRawJt_HistTot_p, sType, Form("%s_rechitRawTot", evtSelAlg.c_str()));
  InitJetSubstructHist(rechitVsJt_HistTot_p, sType, Form("%s_rechitVsTot", evtSelAlg.c_str()));

  if(isMC){
    InitJetSubstructHist(rechitRawJt_HistQ_p, sType, Form("%s_rechitRawQ", evtSelAlg.c_str()));
    InitJetSubstructHist(rechitVsJt_HistQ_p, sType, Form("%s_rechitVsQ", evtSelAlg.c_str()));

    InitJetSubstructHist(rechitRawJt_HistG_p, sType, Form("%s_rechitRawG", evtSelAlg.c_str()));
    InitJetSubstructHist(rechitVsJt_HistG_p, sType, Form("%s_rechitVsG", evtSelAlg.c_str()));
  }

  InitJetSubstructHist(pfRawJt_HistTot_p, sType, Form("%s_pfRawTot", evtSelAlg.c_str()));
  InitJetSubstructHist(pfVsJt_HistTot_p, sType, Form("%s_pfVsTot", evtSelAlg.c_str()));
  InitJetSubstructHist(pfSKJt_HistTot_p, sType, Form("%s_pfSKTot", evtSelAlg.c_str()));

  if(isMC){
    InitJetSubstructHist(pfRawJt_HistQ_p, sType, Form("%s_pfRawQ", evtSelAlg.c_str()));
    InitJetSubstructHist(pfVsJt_HistQ_p, sType, Form("%s_pfVsQ", evtSelAlg.c_str()));
    InitJetSubstructHist(pfSKJt_HistQ_p, sType, Form("%s_pfSKQ", evtSelAlg.c_str()));
    
    InitJetSubstructHist(pfRawJt_HistG_p, sType, Form("%s_pfRawG", evtSelAlg.c_str()));
    InitJetSubstructHist(pfVsJt_HistG_p, sType, Form("%s_pfVsG", evtSelAlg.c_str()));
    InitJetSubstructHist(pfSKJt_HistG_p, sType, Form("%s_pfSKG", evtSelAlg.c_str()));
  }

  InitJetSubstructHist(trkRawJt_HistTot_p, sType, Form("%s_trkRawTot", evtSelAlg.c_str()));
  InitJetSubstructHist(trkSKJt_HistTot_p, sType, Form("%s_trkSKTot", evtSelAlg.c_str()));
  InitJetSubstructHist(trk3CutJt_HistTot_p, sType, Form("%s_trk3CutTot", evtSelAlg.c_str()));

  if(isMC){
    InitJetSubstructHist(trkRawJt_HistQ_p, sType, Form("%s_trkRawQ", evtSelAlg.c_str()));
    InitJetSubstructHist(trkSKJt_HistQ_p, sType, Form("%s_trkSKQ", evtSelAlg.c_str()));
    InitJetSubstructHist(trk3CutJt_HistQ_p, sType, Form("%s_trk3CutQ", evtSelAlg.c_str()));
    
    InitJetSubstructHist(trkRawJt_HistG_p, sType, Form("%s_trkRawG", evtSelAlg.c_str()));
    InitJetSubstructHist(trkSKJt_HistG_p, sType, Form("%s_trkSKG", evtSelAlg.c_str()));
    InitJetSubstructHist(trk3CutJt_HistG_p, sType, Form("%s_trk3CutG", evtSelAlg.c_str()));
  }

  if(isMC){
    InitJetSubstructHist(genRawJt_HistTot_p, sType, Form("%s_genRawTot", evtSelAlg.c_str()));
    InitJetSubstructHist(genSKJt_HistTot_p, sType, Form("%s_genSKTot", evtSelAlg.c_str()));
    InitJetSubstructHist(genSUBEJt_HistTot_p, sType, Form("%s_genSUBETot", evtSelAlg.c_str()));
    InitJetSubstructHist(genChgJt_HistTot_p, sType, Form("%s_genChgTot", evtSelAlg.c_str()));
    InitJetSubstructHist(genSKChgJt_HistTot_p, sType, Form("%s_genSKChgTot", evtSelAlg.c_str()));
    
    InitJetSubstructHist(genRawJt_HistQ_p, sType, Form("%s_genRawQ", evtSelAlg.c_str()));
    InitJetSubstructHist(genSKJt_HistQ_p, sType, Form("%s_genSKQ", evtSelAlg.c_str()));
    InitJetSubstructHist(genSUBEJt_HistQ_p, sType, Form("%s_genSUBEQ", evtSelAlg.c_str()));
    InitJetSubstructHist(genChgJt_HistQ_p, sType, Form("%s_genChgQ", evtSelAlg.c_str()));
    InitJetSubstructHist(genSKChgJt_HistQ_p, sType, Form("%s_genSKChgQ", evtSelAlg.c_str()));
    
    InitJetSubstructHist(genRawJt_HistG_p, sType, Form("%s_genRawG", evtSelAlg.c_str()));
    InitJetSubstructHist(genSKJt_HistG_p, sType, Form("%s_genSKG", evtSelAlg.c_str()));
    InitJetSubstructHist(genSUBEJt_HistG_p, sType, Form("%s_genSUBEG", evtSelAlg.c_str()));
    InitJetSubstructHist(genChgJt_HistG_p, sType, Form("%s_genChgG", evtSelAlg.c_str()));
    InitJetSubstructHist(genSKChgJt_HistG_p, sType, Form("%s_genSKChgG", evtSelAlg.c_str()));
  }

  return;
}


void GetHist(TFile* outFile_p, sampleType sType, const std::string evtSelAlg)
{
  Bool_t isMC = isMonteCarlo(sType);

  GetJetSubstructHist(outFile_p, rechitRawJt_HistTot_p, sType, Form("%s_rechitRawTot", evtSelAlg.c_str()));
  GetJetSubstructHist(outFile_p, rechitVsJt_HistTot_p, sType, Form("%s_rechitVsTot", evtSelAlg.c_str()));

  if(isMC){
    GetJetSubstructHist(outFile_p, rechitRawJt_HistQ_p, sType, Form("%s_rechitRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, rechitVsJt_HistQ_p, sType, Form("%s_rechitVsQ", evtSelAlg.c_str()));

    GetJetSubstructHist(outFile_p, rechitRawJt_HistG_p, sType, Form("%s_rechitRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, rechitVsJt_HistG_p, sType, Form("%s_rechitVsG", evtSelAlg.c_str()));
  }

  GetJetSubstructHist(outFile_p, pfRawJt_HistTot_p, sType, Form("%s_pfRawTot", evtSelAlg.c_str()));
  GetJetSubstructHist(outFile_p, pfVsJt_HistTot_p, sType, Form("%s_pfVsTot", evtSelAlg.c_str()));
  GetJetSubstructHist(outFile_p, pfSKJt_HistTot_p, sType, Form("%s_pfSKTot", evtSelAlg.c_str()));

  if(isMC){
    GetJetSubstructHist(outFile_p, pfRawJt_HistQ_p, sType, Form("%s_pfRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, pfVsJt_HistQ_p, sType, Form("%s_pfVsQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, pfSKJt_HistQ_p, sType, Form("%s_pfSKQ", evtSelAlg.c_str()));
    
    GetJetSubstructHist(outFile_p, pfRawJt_HistG_p, sType, Form("%s_pfRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, pfVsJt_HistG_p, sType, Form("%s_pfVsG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, pfSKJt_HistG_p, sType, Form("%s_pfSKG", evtSelAlg.c_str()));
  }

  GetJetSubstructHist(outFile_p, trkRawJt_HistTot_p, sType, Form("%s_trkRawTot", evtSelAlg.c_str()));
  GetJetSubstructHist(outFile_p, trkSKJt_HistTot_p, sType, Form("%s_trkSKTot", evtSelAlg.c_str()));
  GetJetSubstructHist(outFile_p, trk3CutJt_HistTot_p, sType, Form("%s_trk3CutTot", evtSelAlg.c_str()));

  if(isMC){
    GetJetSubstructHist(outFile_p, trkRawJt_HistQ_p, sType, Form("%s_trkRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, trkSKJt_HistQ_p, sType, Form("%s_trkSKQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, trk3CutJt_HistQ_p, sType, Form("%s_trk3CutQ", evtSelAlg.c_str()));
    
    GetJetSubstructHist(outFile_p, trkRawJt_HistG_p, sType, Form("%s_trkRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, trkSKJt_HistG_p, sType, Form("%s_trkSKG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, trk3CutJt_HistG_p, sType, Form("%s_trk3CutG", evtSelAlg.c_str()));
  }

  if(isMC){
    GetJetSubstructHist(outFile_p, genRawJt_HistTot_p, sType, Form("%s_genRawTot", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSKJt_HistTot_p, sType, Form("%s_genSKTot", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSUBEJt_HistTot_p, sType, Form("%s_genSUBETot", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genChgJt_HistTot_p, sType, Form("%s_genChgTot", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSKChgJt_HistTot_p, sType, Form("%s_genSKChgTot", evtSelAlg.c_str()));
    
    GetJetSubstructHist(outFile_p, genRawJt_HistQ_p, sType, Form("%s_genRawQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSKJt_HistQ_p, sType, Form("%s_genSKQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSUBEJt_HistQ_p, sType, Form("%s_genSUBEQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genChgJt_HistQ_p, sType, Form("%s_genChgQ", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSKChgJt_HistQ_p, sType, Form("%s_genSKChgQ", evtSelAlg.c_str()));   

    GetJetSubstructHist(outFile_p, genRawJt_HistG_p, sType, Form("%s_genRawG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSKJt_HistG_p, sType, Form("%s_genSKG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSUBEJt_HistG_p, sType, Form("%s_genSUBEG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genChgJt_HistG_p, sType, Form("%s_genChgG", evtSelAlg.c_str()));
    GetJetSubstructHist(outFile_p, genSKChgJt_HistG_p, sType, Form("%s_genSKChgG", evtSelAlg.c_str()));
  }

  return;
}


void ScaleHistAll(sampleType sType)
{
  Bool_t isMC = isMonteCarlo(sType);

  if(isMC){
    ScaleJetSubstructHist(rechitRawJt_HistQ_p, rechitRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(rechitRawJt_HistG_p, rechitRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(rechitVsJt_HistQ_p, rechitVsJt_HistTot_p, sType);
    ScaleJetSubstructHist(rechitVsJt_HistG_p, rechitVsJt_HistTot_p, sType);
    
    ScaleJetSubstructHist(pfRawJt_HistQ_p, pfRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(pfRawJt_HistG_p, pfRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(pfVsJt_HistQ_p, pfVsJt_HistTot_p, sType);
    ScaleJetSubstructHist(pfVsJt_HistG_p, pfVsJt_HistTot_p, sType);
    ScaleJetSubstructHist(pfSKJt_HistQ_p, pfSKJt_HistTot_p, sType);
    ScaleJetSubstructHist(pfSKJt_HistG_p, pfSKJt_HistTot_p, sType);
    
    ScaleJetSubstructHist(trkRawJt_HistQ_p, trkRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(trkRawJt_HistG_p, trkRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(trkSKJt_HistQ_p, trkSKJt_HistTot_p, sType);
    ScaleJetSubstructHist(trkSKJt_HistG_p, trkSKJt_HistTot_p, sType);
    ScaleJetSubstructHist(trk3CutJt_HistQ_p, trk3CutJt_HistTot_p, sType);
    ScaleJetSubstructHist(trk3CutJt_HistG_p, trk3CutJt_HistTot_p, sType);
    
    ScaleJetSubstructHist(genRawJt_HistQ_p, genRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(genRawJt_HistG_p, genRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSKJt_HistQ_p, genSKJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSKJt_HistG_p, genSKJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSUBEJt_HistQ_p, genSUBEJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSUBEJt_HistG_p, genSUBEJt_HistTot_p, sType);
    ScaleJetSubstructHist(genChgJt_HistQ_p, genChgJt_HistTot_p, sType);
    ScaleJetSubstructHist(genChgJt_HistG_p, genChgJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSKChgJt_HistQ_p, genSKChgJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSKChgJt_HistG_p, genSKChgJt_HistTot_p, sType);
  }
    
  ScaleJetSubstructHist(rechitRawJt_HistTot_p, rechitRawJt_HistTot_p, sType);
  ScaleJetSubstructHist(rechitVsJt_HistTot_p, rechitVsJt_HistTot_p, sType);
  ScaleJetSubstructHist(pfRawJt_HistTot_p, pfRawJt_HistTot_p, sType);
  ScaleJetSubstructHist(pfVsJt_HistTot_p, pfVsJt_HistTot_p, sType);
  ScaleJetSubstructHist(pfSKJt_HistTot_p, pfSKJt_HistTot_p, sType);
  ScaleJetSubstructHist(trkRawJt_HistTot_p, trkRawJt_HistTot_p, sType);
  ScaleJetSubstructHist(trkSKJt_HistTot_p, trkSKJt_HistTot_p, sType);
  ScaleJetSubstructHist(trk3CutJt_HistTot_p, trk3CutJt_HistTot_p, sType);
  if(isMC){
    ScaleJetSubstructHist(genRawJt_HistTot_p, genRawJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSKJt_HistTot_p, genSKJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSUBEJt_HistTot_p, genSUBEJt_HistTot_p, sType);
    ScaleJetSubstructHist(genChgJt_HistTot_p, genChgJt_HistTot_p, sType);
    ScaleJetSubstructHist(genSKChgJt_HistTot_p, genSKChgJt_HistTot_p, sType);
  }

  return;
}


void WriteHistAll(TFile* outFile_p, sampleType sType, const std::string evtSelAlg)
{
  Bool_t isMC = isMonteCarlo(sType);

  WriteJetSubstructHist(outFile_p, rechitRawJt_HistTot_p, sType, evtSelAlg, "rechitRawTot");
  WriteJetSubstructHist(outFile_p, rechitVsJt_HistTot_p, sType, evtSelAlg, "rechitVsTot");

  if(isMC){
    WriteJetSubstructHist(outFile_p, rechitRawJt_HistQ_p, sType, evtSelAlg, "rechitRawQ");
    WriteJetSubstructHist(outFile_p, rechitVsJt_HistQ_p, sType, evtSelAlg, "rechitVsQ");

    WriteJetSubstructHist(outFile_p, rechitRawJt_HistG_p, sType, evtSelAlg, "rechitRawG");
    WriteJetSubstructHist(outFile_p, rechitVsJt_HistG_p, sType, evtSelAlg, "rechitVsG");
  }

  WriteJetSubstructHist(outFile_p, pfRawJt_HistTot_p, sType, evtSelAlg, "pfRawTot");
  WriteJetSubstructHist(outFile_p, pfVsJt_HistTot_p, sType, evtSelAlg, "pfVsTot");
  WriteJetSubstructHist(outFile_p, pfSKJt_HistTot_p, sType, evtSelAlg, "pfSKTot");

  if(isMC){
    WriteJetSubstructHist(outFile_p, pfRawJt_HistQ_p, sType, evtSelAlg, "pfRawQ");
    WriteJetSubstructHist(outFile_p, pfVsJt_HistQ_p, sType, evtSelAlg, "pfVsQ");
    WriteJetSubstructHist(outFile_p, pfSKJt_HistQ_p, sType, evtSelAlg, "pfSKQ");
    
    WriteJetSubstructHist(outFile_p, pfRawJt_HistG_p, sType, evtSelAlg, "pfRawG");
    WriteJetSubstructHist(outFile_p, pfVsJt_HistG_p, sType, evtSelAlg, "pfVsG");
    WriteJetSubstructHist(outFile_p, pfSKJt_HistG_p, sType, evtSelAlg, "pfSKG");
  }

  WriteJetSubstructHist(outFile_p, trkRawJt_HistTot_p, sType, evtSelAlg, "trkRawTot");
  WriteJetSubstructHist(outFile_p, trkSKJt_HistTot_p, sType, evtSelAlg, "trkSKTot");
  WriteJetSubstructHist(outFile_p, trk3CutJt_HistTot_p, sType, evtSelAlg, "trk3CutTot");

  if(isMC){
    WriteJetSubstructHist(outFile_p, trkRawJt_HistQ_p, sType, evtSelAlg, "trkRawQ");
    WriteJetSubstructHist(outFile_p, trkSKJt_HistQ_p, sType, evtSelAlg, "trkSKQ");
    WriteJetSubstructHist(outFile_p, trk3CutJt_HistQ_p, sType, evtSelAlg, "trk3CutQ");
    
    WriteJetSubstructHist(outFile_p, trkRawJt_HistG_p, sType, evtSelAlg, "trkRawG");
    WriteJetSubstructHist(outFile_p, trkSKJt_HistG_p, sType, evtSelAlg, "trkSKG");
    WriteJetSubstructHist(outFile_p, trk3CutJt_HistG_p, sType, evtSelAlg, "trk3CutG");
  }

  if(isMC){
    WriteJetSubstructHist(outFile_p, genRawJt_HistTot_p, sType, evtSelAlg, "genRawTot");
    WriteJetSubstructHist(outFile_p, genSKJt_HistTot_p, sType, evtSelAlg, "genSKTot");
    WriteJetSubstructHist(outFile_p, genSUBEJt_HistTot_p, sType, evtSelAlg, "genSUBETot");
    WriteJetSubstructHist(outFile_p, genChgJt_HistTot_p, sType, evtSelAlg, "genChgTot");
    WriteJetSubstructHist(outFile_p, genSKChgJt_HistTot_p, sType, evtSelAlg, "genSKChgTot");

    WriteJetSubstructHist(outFile_p, genRawJt_HistQ_p, sType, evtSelAlg, "genRawQ");
    WriteJetSubstructHist(outFile_p, genSKJt_HistQ_p, sType, evtSelAlg, "genSKQ");
    WriteJetSubstructHist(outFile_p, genSUBEJt_HistQ_p, sType, evtSelAlg, "genSUBEQ");
    WriteJetSubstructHist(outFile_p, genChgJt_HistQ_p, sType, evtSelAlg, "genChgQ");
    WriteJetSubstructHist(outFile_p, genSKChgJt_HistQ_p, sType, evtSelAlg, "genSKChgQ");
    
    WriteJetSubstructHist(outFile_p, genRawJt_HistG_p, sType, evtSelAlg, "genRawG");
    WriteJetSubstructHist(outFile_p, genSKJt_HistG_p, sType, evtSelAlg, "genSKG");
    WriteJetSubstructHist(outFile_p, genSUBEJt_HistG_p, sType, evtSelAlg, "genSUBEG");
    WriteJetSubstructHist(outFile_p, genChgJt_HistG_p, sType, evtSelAlg, "genChgG");
    WriteJetSubstructHist(outFile_p, genSKChgJt_HistG_p, sType, evtSelAlg, "genSKChgG");
  }

  return;
}


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
  CleanupJetSubstructHist(trk3CutJt_HistTot_p, sType);

  if(isMC){
    CleanupJetSubstructHist(trkRawJt_HistQ_p, sType);
    CleanupJetSubstructHist(trkSKJt_HistQ_p, sType);
    CleanupJetSubstructHist(trk3CutJt_HistQ_p, sType);
    
    CleanupJetSubstructHist(trkRawJt_HistG_p, sType);
    CleanupJetSubstructHist(trkSKJt_HistG_p, sType);
    CleanupJetSubstructHist(trk3CutJt_HistG_p, sType);
  }

  if(isMC){
    CleanupJetSubstructHist(genRawJt_HistTot_p, sType);
    CleanupJetSubstructHist(genSKJt_HistTot_p, sType);
    CleanupJetSubstructHist(genSUBEJt_HistTot_p, sType);
    CleanupJetSubstructHist(genChgJt_HistTot_p, sType);
    CleanupJetSubstructHist(genSKChgJt_HistTot_p, sType);

    CleanupJetSubstructHist(genRawJt_HistQ_p, sType);
    CleanupJetSubstructHist(genSKJt_HistQ_p, sType);
    CleanupJetSubstructHist(genSUBEJt_HistQ_p, sType);
    CleanupJetSubstructHist(genChgJt_HistQ_p, sType);
    CleanupJetSubstructHist(genSKChgJt_HistQ_p, sType);
    
    CleanupJetSubstructHist(genRawJt_HistG_p, sType);
    CleanupJetSubstructHist(genSKJt_HistG_p, sType);
    CleanupJetSubstructHist(genSUBEJt_HistG_p, sType);
    CleanupJetSubstructHist(genChgJt_HistG_p, sType);
    CleanupJetSubstructHist(genSKChgJt_HistG_p, sType);
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
  delete trk3CutJt_HistTot_p;

  if(isMC){
    delete genRawJt_HistTot_p;
    delete genSKJt_HistTot_p;
    delete genSUBEJt_HistTot_p;
    delete genChgJt_HistTot_p;
    delete genSKChgJt_HistTot_p;

    delete rechitRawJt_HistQ_p;
    delete rechitVsJt_HistQ_p;
    
    delete pfRawJt_HistQ_p;
    delete pfVsJt_HistQ_p;
    delete pfSKJt_HistQ_p;
    
    delete trkRawJt_HistQ_p;
    delete trkSKJt_HistQ_p;
    delete trk3CutJt_HistQ_p;
    
    delete genRawJt_HistQ_p;
    delete genSKJt_HistQ_p;
    delete genSUBEJt_HistQ_p;
    delete genChgJt_HistQ_p;
    delete genSKChgJt_HistQ_p;
    
    delete rechitRawJt_HistG_p;
    delete rechitVsJt_HistG_p;
    
    delete pfRawJt_HistG_p;
    delete pfVsJt_HistG_p;
    delete pfSKJt_HistG_p;
    
    delete trkRawJt_HistG_p;
    delete trkSKJt_HistG_p;
    delete trk3CutJt_HistG_p;
    
    delete genRawJt_HistG_p;
    delete genSKJt_HistG_p;
    delete genSUBEJt_HistG_p;
    delete genChgJt_HistG_p;
    delete genSKChgJt_HistG_p;
  }

  return;
}


#endif
