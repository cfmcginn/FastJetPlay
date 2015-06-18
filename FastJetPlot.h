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
JetSubstructHist* rechitRawJt_HistPbPbTot_p = 0;
JetSubstructHist* rechitVsJt_HistPbPbTot_p = 0;

JetSubstructHist* rechitRawJt_HistPPTot_p = 0;
JetSubstructHist* rechitVsJt_HistPPTot_p = 0;

JetSubstructHist* rechitRawJt_HistHIMCTot_p = 0;
JetSubstructHist* rechitVsJt_HistHIMCTot_p = 0;

JetSubstructHist* rechitRawJt_HistHIMCQ_p = 0;
JetSubstructHist* rechitVsJt_HistHIMCQ_p = 0;

JetSubstructHist* rechitRawJt_HistHIMCG_p = 0;
JetSubstructHist* rechitVsJt_HistHIMCG_p = 0;

JetSubstructHist* rechitRawJt_HistPPMCTot_p = 0;
JetSubstructHist* rechitVsJt_HistPPMCTot_p = 0;

JetSubstructHist* rechitRawJt_HistPPMCQ_p = 0;
JetSubstructHist* rechitVsJt_HistPPMCQ_p = 0;

JetSubstructHist* rechitRawJt_HistPPMCG_p = 0;
JetSubstructHist* rechitVsJt_HistPPMCG_p = 0;

//pf substruct hist                                                          

JetSubstructHist* pfRawJt_HistPbPbTot_p = 0;
JetSubstructHist* pfVsJt_HistPbPbTot_p = 0;
JetSubstructHist* pfSKJt_HistPbPbTot_p = 0;

JetSubstructHist* pfRawJt_HistPPTot_p = 0;
JetSubstructHist* pfVsJt_HistPPTot_p = 0;
JetSubstructHist* pfSKJt_HistPPTot_p = 0;

JetSubstructHist* pfRawJt_HistHIMCTot_p = 0;
JetSubstructHist* pfVsJt_HistHIMCTot_p = 0;
JetSubstructHist* pfSKJt_HistHIMCTot_p = 0;

JetSubstructHist* pfRawJt_HistHIMCQ_p = 0;
JetSubstructHist* pfVsJt_HistHIMCQ_p = 0;
JetSubstructHist* pfSKJt_HistHIMCQ_p = 0;

JetSubstructHist* pfRawJt_HistHIMCG_p = 0;
JetSubstructHist* pfVsJt_HistHIMCG_p = 0;
JetSubstructHist* pfSKJt_HistHIMCG_p = 0;

JetSubstructHist* pfRawJt_HistPPMCTot_p = 0;
JetSubstructHist* pfVsJt_HistPPMCTot_p = 0;
JetSubstructHist* pfSKJt_HistPPMCTot_p = 0;

JetSubstructHist* pfRawJt_HistPPMCQ_p = 0;
JetSubstructHist* pfVsJt_HistPPMCQ_p = 0;
JetSubstructHist* pfSKJt_HistPPMCQ_p = 0;

JetSubstructHist* pfRawJt_HistPPMCG_p = 0;
JetSubstructHist* pfVsJt_HistPPMCG_p = 0;
JetSubstructHist* pfSKJt_HistPPMCG_p = 0;

//track substruct hist

JetSubstructHist* trkRawJt_HistPbPbTot_p = 0;
JetSubstructHist* trkSKJt_HistPbPbTot_p = 0;
JetSubstructHist* trk3CutJt_HistPbPbTot_p = 0;

JetSubstructHist* trkRawJt_HistPPTot_p = 0;
JetSubstructHist* trkSKJt_HistPPTot_p = 0;
JetSubstructHist* trk3CutJt_HistPPTot_p = 0;

JetSubstructHist* trkRawJt_HistHIMCTot_p = 0;
JetSubstructHist* trkSKJt_HistHIMCTot_p = 0;
JetSubstructHist* trk3CutJt_HistHIMCTot_p = 0;

JetSubstructHist* trkRawJt_HistHIMCQ_p = 0;
JetSubstructHist* trkSKJt_HistHIMCQ_p = 0;
JetSubstructHist* trk3CutJt_HistHIMCQ_p = 0;

JetSubstructHist* trkRawJt_HistHIMCG_p = 0;
JetSubstructHist* trkSKJt_HistHIMCG_p = 0;
JetSubstructHist* trk3CutJt_HistHIMCG_p = 0;

JetSubstructHist* trkRawJt_HistPPMCTot_p = 0;
JetSubstructHist* trkSKJt_HistPPMCTot_p = 0;
JetSubstructHist* trk3CutJt_HistPPMCTot_p = 0;

JetSubstructHist* trkRawJt_HistPPMCQ_p = 0;
JetSubstructHist* trkSKJt_HistPPMCQ_p = 0;
JetSubstructHist* trk3CutJt_HistPPMCQ_p = 0;

JetSubstructHist* trkRawJt_HistPPMCG_p = 0;
JetSubstructHist* trkSKJt_HistPPMCG_p = 0;
JetSubstructHist* trk3CutJt_HistPPMCG_p = 0;

//gen substruct hist

JetSubstructHist* genRawJt_HistHIMCTot_p = 0;
JetSubstructHist* genSKJt_HistHIMCTot_p = 0;
JetSubstructHist* genSUBEJt_HistHIMCTot_p = 0;
JetSubstructHist* genChgJt_HistHIMCTot_p = 0;
JetSubstructHist* genSKChgJt_HistHIMCTot_p = 0;

JetSubstructHist* genRawJt_HistHIMCQ_p = 0;
JetSubstructHist* genSKJt_HistHIMCQ_p = 0;
JetSubstructHist* genSUBEJt_HistHIMCQ_p = 0;
JetSubstructHist* genChgJt_HistHIMCQ_p = 0;
JetSubstructHist* genSKChgJt_HistHIMCQ_p = 0;

JetSubstructHist* genRawJt_HistHIMCG_p = 0;
JetSubstructHist* genSKJt_HistHIMCG_p = 0;
JetSubstructHist* genSUBEJt_HistHIMCG_p = 0;
JetSubstructHist* genChgJt_HistHIMCG_p = 0;
JetSubstructHist* genSKChgJt_HistHIMCG_p = 0;

JetSubstructHist* genRawJt_HistPPMCTot_p = 0;
JetSubstructHist* genSKJt_HistPPMCTot_p = 0;
JetSubstructHist* genSUBEJt_HistPPMCTot_p = 0;
JetSubstructHist* genChgJt_HistPPMCTot_p = 0;
JetSubstructHist* genSKChgJt_HistPPMCTot_p = 0;

JetSubstructHist* genRawJt_HistPPMCQ_p = 0;
JetSubstructHist* genSKJt_HistPPMCQ_p = 0;
JetSubstructHist* genSUBEJt_HistPPMCQ_p = 0;
JetSubstructHist* genChgJt_HistPPMCQ_p = 0;
JetSubstructHist* genSKChgJt_HistPPMCQ_p = 0;

JetSubstructHist* genRawJt_HistPPMCG_p = 0;
JetSubstructHist* genSKJt_HistPPMCG_p = 0;
JetSubstructHist* genSUBEJt_HistPPMCG_p = 0;
JetSubstructHist* genChgJt_HistPPMCG_p = 0;
JetSubstructHist* genSKChgJt_HistPPMCG_p = 0;

JetSubstructHist* T_genSUBEJt_HistPPMCTot_p = 0;
JetSubstructHist* T_genSUBEJt_HistHIMCTot_p = 0;

void GetHistForPlot(TFile* pbpbFile_p, TFile* ppFile_p, TFile* hiMCFile_p, TFile* ppMCFile_p,  const std::string evtSelAlg, Bool_t isGenHI, Bool_t isGenPP);

void GetHistForPlot(TFile* pbpbFile_p, TFile* ppFile_p, TFile* hiMCFile_p, TFile* ppMCFile_p,  const std::string evtSelAlg, Bool_t isGenHI, Bool_t isGenPP)
{
  if(pbpbFile_p != 0){
    GetJetSubstructHist(pbpbFile_p, rechitRawJt_HistPbPbTot_p, kHIDATA, Form("%srechitRawTotDir/%s_rechitRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, rechitVsJt_HistPbPbTot_p, kHIDATA, Form("%srechitVsTotDir/%s_rechitVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(pbpbFile_p, pfRawJt_HistPbPbTot_p, kHIDATA, Form("%spfRawTotDir/%s_pfRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, pfVsJt_HistPbPbTot_p, kHIDATA, Form("%spfVsTotDir/%s_pfVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, pfSKJt_HistPbPbTot_p, kHIDATA, Form("%spfSKTotDir/%s_pfSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(pbpbFile_p, trkRawJt_HistPbPbTot_p, kHIDATA, Form("%strkRawTotDir/%s_trkRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, trkSKJt_HistPbPbTot_p, kHIDATA, Form("%strkSKTotDir/%s_trkSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(pbpbFile_p, trk3CutJt_HistPbPbTot_p, kHIDATA, Form("%strk3CutTotDir/%s_trk3CutTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
  }

  if(ppFile_p != 0){
    GetJetSubstructHist(ppFile_p, rechitRawJt_HistPPTot_p, kPPDATA, Form("%srechitRawTotDir/%s_rechitRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, rechitVsJt_HistPPTot_p, kPPDATA, Form("%srechitVsTotDir/%s_rechitVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppFile_p, pfRawJt_HistPPTot_p, kPPDATA, Form("%spfRawTotDir/%s_pfRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, pfVsJt_HistPPTot_p, kPPDATA, Form("%spfVsTotDir/%s_pfVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, pfSKJt_HistPPTot_p, kPPDATA, Form("%spfSKTotDir/%s_pfSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppFile_p, trkRawJt_HistPPTot_p, kPPDATA, Form("%strkRawTotDir/%s_trkRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, trkSKJt_HistPPTot_p, kPPDATA, Form("%strkSKTotDir/%s_trkSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppFile_p, trk3CutJt_HistPPTot_p, kPPDATA, Form("%strk3CutTotDir/%s_trk3CutTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
  }

  if(hiMCFile_p != 0){
    GetJetSubstructHist(hiMCFile_p, rechitRawJt_HistHIMCTot_p, kHIMC, Form("%srechitRawTotDir/%s_rechitRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, rechitVsJt_HistHIMCTot_p, kHIMC, Form("%srechitVsTotDir/%s_rechitVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, rechitRawJt_HistHIMCQ_p, kHIMC, Form("%srechitRawQDir/%s_rechitRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, rechitVsJt_HistHIMCQ_p, kHIMC, Form("%srechitVsQDir/%s_rechitVsQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, rechitRawJt_HistHIMCG_p, kHIMC, Form("%srechitRawGDir/%s_rechitRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, rechitVsJt_HistHIMCG_p, kHIMC, Form("%srechitVsGDir/%s_rechitVsG", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, pfRawJt_HistHIMCTot_p, kHIMC, Form("%spfRawTotDir/%s_pfRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfVsJt_HistHIMCTot_p, kHIMC, Form("%spfVsTotDir/%s_pfVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfSKJt_HistHIMCTot_p, kHIMC, Form("%spfSKTotDir/%s_pfSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, pfRawJt_HistHIMCQ_p, kHIMC, Form("%spfRawQDir/%s_pfRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfVsJt_HistHIMCQ_p, kHIMC, Form("%spfVsQDir/%s_pfVsQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfSKJt_HistHIMCQ_p, kHIMC, Form("%spfSKQDir/%s_pfSKQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, pfRawJt_HistHIMCG_p, kHIMC, Form("%spfRawGDir/%s_pfRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfVsJt_HistHIMCG_p, kHIMC, Form("%spfVsGDir/%s_pfVsG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, pfSKJt_HistHIMCG_p, kHIMC, Form("%spfSKGDir/%s_pfSKG", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, trkRawJt_HistHIMCTot_p, kHIMC, Form("%strkRawTotDir/%s_trkRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trkSKJt_HistHIMCTot_p, kHIMC, Form("%strkSKTotDir/%s_trkSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trk3CutJt_HistHIMCTot_p, kHIMC, Form("%strk3CutTotDir/%s_trk3CutTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, trkRawJt_HistHIMCQ_p, kHIMC, Form("%strkRawQDir/%s_trkRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trkSKJt_HistHIMCQ_p, kHIMC, Form("%strkSKQDir/%s_trkSKQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trk3CutJt_HistHIMCQ_p, kHIMC, Form("%strk3CutQDir/%s_trk3CutQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, trkRawJt_HistHIMCG_p, kHIMC, Form("%strkRawGDir/%s_trkRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trkSKJt_HistHIMCG_p, kHIMC, Form("%strkSKGDir/%s_trkSKG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, trk3CutJt_HistHIMCG_p, kHIMC, Form("%strk3CutGDir/%s_trk3CutG", evtSelAlg.c_str(), evtSelAlg.c_str()));

    std::cout << Form("%sgenSKTotDir/%s_genSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()) << std::endl;

    GetJetSubstructHist(hiMCFile_p, genRawJt_HistHIMCTot_p, kHIMC, Form("%sgenRawTotDir/%s_genRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKJt_HistHIMCTot_p, kHIMC, Form("%sgenSKTotDir/%s_genSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSUBEJt_HistHIMCTot_p, kHIMC, Form("%sgenSUBETotDir/%s_genSUBETot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genChgJt_HistHIMCTot_p, kHIMC, Form("%sgenChgTotDir/%s_genChgTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKChgJt_HistHIMCTot_p, kHIMC, Form("%sgenSKChgTotDir/%s_genSKChgTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, genRawJt_HistHIMCQ_p, kHIMC, Form("%sgenRawQDir/%s_genRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKJt_HistHIMCQ_p, kHIMC, Form("%sgenSKQDir/%s_genSKQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSUBEJt_HistHIMCQ_p, kHIMC, Form("%sgenSUBEQDir/%s_genSUBEQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genChgJt_HistHIMCQ_p, kHIMC, Form("%sgenChgQDir/%s_genChgQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKChgJt_HistHIMCQ_p, kHIMC, Form("%sgenSKChgQDir/%s_genSKChgQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(hiMCFile_p, genRawJt_HistHIMCG_p, kHIMC, Form("%sgenRawGDir/%s_genRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKJt_HistHIMCG_p, kHIMC, Form("%sgenSKGDir/%s_genSKG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSUBEJt_HistHIMCG_p, kHIMC, Form("%sgenSUBEGDir/%s_genSUBEG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genChgJt_HistHIMCG_p, kHIMC, Form("%sgenChgGDir/%s_genChgG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(hiMCFile_p, genSKChgJt_HistHIMCG_p, kHIMC, Form("%sgenSKChgGDir/%s_genSKChgG", evtSelAlg.c_str(), evtSelAlg.c_str()));

    if(isGenHI) GetJetSubstructHist(hiMCFile_p, T_genSUBEJt_HistHIMCTot_p, kHIMC, Form("TgenSUBETotDir/T_genSUBETot"));
  }

  if(ppMCFile_p != 0){
    GetJetSubstructHist(ppMCFile_p, rechitRawJt_HistPPMCTot_p, kPPMC, Form("%srechitRawTotDir/%s_rechitRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, rechitVsJt_HistPPMCTot_p, kPPMC, Form("%srechitVsTotDir/%s_rechitVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, rechitRawJt_HistPPMCQ_p, kPPMC, Form("%srechitRawQDir/%s_rechitRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, rechitVsJt_HistPPMCQ_p, kPPMC, Form("%srechitVsQDir/%s_rechitVsQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, rechitRawJt_HistPPMCG_p, kPPMC, Form("%srechitRawGDir/%s_rechitRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, rechitVsJt_HistPPMCG_p, kPPMC, Form("%srechitVsGDir/%s_rechitVsG", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, pfRawJt_HistPPMCTot_p, kPPMC, Form("%spfRawTotDir/%s_pfRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfVsJt_HistPPMCTot_p, kPPMC, Form("%spfVsTotDir/%s_pfVsTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfSKJt_HistPPMCTot_p, kPPMC, Form("%spfSKTotDir/%s_pfSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, pfRawJt_HistPPMCQ_p, kPPMC, Form("%spfRawQDir/%s_pfRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfVsJt_HistPPMCQ_p, kPPMC, Form("%spfVsQDir/%s_pfVsQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfSKJt_HistPPMCQ_p, kPPMC, Form("%spfSKQDir/%s_pfSKQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, pfRawJt_HistPPMCG_p, kPPMC, Form("%spfRawGDir/%s_pfRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfVsJt_HistPPMCG_p, kPPMC, Form("%spfVsGDir/%s_pfVsG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, pfSKJt_HistPPMCG_p, kPPMC, Form("%spfSKGDir/%s_pfSKG", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, trkRawJt_HistPPMCTot_p, kPPMC, Form("%strkRawTotDir/%s_trkRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trkSKJt_HistPPMCTot_p, kPPMC, Form("%strkSKTotDir/%s_trkSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trk3CutJt_HistPPMCTot_p, kPPMC, Form("%strk3CutTotDir/%s_trk3CutTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, trkRawJt_HistPPMCQ_p, kPPMC, Form("%strkRawQDir/%s_trkRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trkSKJt_HistPPMCQ_p, kPPMC, Form("%strkSKQDir/%s_trkSKQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trk3CutJt_HistPPMCQ_p, kPPMC, Form("%strk3CutQDir/%s_trk3CutQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, trkRawJt_HistPPMCG_p, kPPMC, Form("%strkRawGDir/%s_trkRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trkSKJt_HistPPMCG_p, kPPMC, Form("%strkSKGDir/%s_trkSKG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, trk3CutJt_HistPPMCG_p, kPPMC, Form("%strk3CutGDir/%s_trk3CutG", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, genRawJt_HistPPMCTot_p, kPPMC, Form("%sgenRawTotDir/%s_genRawTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKJt_HistPPMCTot_p, kPPMC, Form("%sgenSKTotDir/%s_genSKTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSUBEJt_HistPPMCTot_p, kPPMC, Form("%sgenSUBETotDir/%s_genSUBETot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genChgJt_HistPPMCTot_p, kPPMC, Form("%sgenChgTotDir/%s_genChgTot", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKChgJt_HistPPMCTot_p, kPPMC, Form("%sgenSKChgTotDir/%s_genSKChgTot", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, genRawJt_HistPPMCQ_p, kPPMC, Form("%sgenRawQDir/%s_genRawQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKJt_HistPPMCQ_p, kPPMC, Form("%sgenSKQDir/%s_genSKQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSUBEJt_HistPPMCQ_p, kPPMC, Form("%sgenSUBEQDir/%s_genSUBEQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genChgJt_HistPPMCQ_p, kPPMC, Form("%sgenChgQDir/%s_genChgQ", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKChgJt_HistPPMCQ_p, kPPMC, Form("%sgenSKChgQDir/%s_genSKChgQ", evtSelAlg.c_str(), evtSelAlg.c_str()));

    GetJetSubstructHist(ppMCFile_p, genRawJt_HistPPMCG_p, kPPMC, Form("%sgenRawGDir/%s_genRawG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKJt_HistPPMCG_p, kPPMC, Form("%sgenSKGDir/%s_genSKG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSUBEJt_HistPPMCG_p, kPPMC, Form("%sgenSUBEGDir/%s_genSUBEG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genChgJt_HistPPMCG_p, kPPMC, Form("%sgenChgGDir/%s_genChgG", evtSelAlg.c_str(), evtSelAlg.c_str()));
    GetJetSubstructHist(ppMCFile_p, genSKChgJt_HistPPMCG_p, kPPMC, Form("%sgenSKChgGDir/%s_genSKChgG", evtSelAlg.c_str(), evtSelAlg.c_str()));


    if(isGenPP) GetJetSubstructHist(ppMCFile_p, T_genSUBEJt_HistPPMCTot_p, kPPMC, Form("TgenSUBEGDir/T_genSUBEG"));
  }

  return;
}

#endif
