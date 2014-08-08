#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLine.h"

#include <iostream>
#include <fstream>
#include <string>

#include "TLatex.h"

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};
//std::string fastJtType[8] = {};

void plotFastJetPTD(const std::string histFileName, const std::string alg, const std::string fastJt)
{
  TFile *f = new TFile(histFileName.c_str(), "UPDATE");

  TH1F* getHist_p[4];

  const std::string centString = {"50100", "3050", "1030", "010"}

  for(Int_t iter = 0; iter < 4; iter++){
    getHist_p[iter] = (TH1F*)f->Get(Form("%sPFVsPTDHist_%s_h", alg.c_str(), centString[iter].c_str()));
  }
}


void makeFastJetPlots()
{
  TH1::SetDefaultSumw2();
}
