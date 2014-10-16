xs//=============================================
// Author: Chris McGinn
//
// FastJet AnaSkim Class (MC)
//
//=============================================
#ifndef FastJetHist_h
#define FastJetHist_h

#include <string>

#include "FastJetAnaSkim.h"

#include "TH1F.h"

TH1F* ptdHist_Tot_p[4][2];
TH1F* ptdHist_Q_p[4][2];
TH1F* ptdHist_G_p[4][2];
TH1F* ptdHist_Else_p[4][2];

TH1F* tau21Hist_Tot_p[4][2][nBeta];
TH1F* tau21Hist_Q_p[4][2][nBeta];
TH1F* tau21Hist_G_p[4][2][nBeta];
TH1F* tau21Hist_Else_p[4][2][nBeta];

TH1F* tau32Hist_Tot_p[4][2][nBeta];
TH1F* tau32Hist_Q_p[4][2][nBeta];
TH1F* tau32Hist_G_p[4][2][nBeta];
TH1F* tau32Hist_Else_p[4][2][nBeta];

TH1F* pfSubRatHist_Tot_p[4][2][nSubjet];

std::string getCentString(sampleType sType, Int_t centLow, Int_t centHi);
void BookHist(sampleType sType = kHIDATA, const std::string evtSelAlg, const std::string clustAlg);
void CleanHist(TH1F* cleanHist_p);
void CleanHistAll(sampleType sType = kHIDATA);


std::string getCentString(sampleType sType, Int_t centLow, Int_t centHi)
{
  if(isHI(sType)) return Form("%d%d", (Int_t)(centLow*.5), (Int_t)((centHi+1)*.5));
  else return "PP";
}

void BookHist(sampleType sType = kHIDATA, const std::string evtSelAlg, const std::string clustAlg)
{
  const Bool_t hi = isHI(sType);

  const Int_t centLow[4] = {0, 20, 60, 100};
  const Int_t centHi[4] = {19, 59, 99, 199};

  Int_t centMax = 1;
  if(hi) centMax = 4;

  std::string centString[4];
  for(Int_t centIter = 0; centIter < centMax; centIter++){
    centString[centIter] = getCentString(sType, centLow[iter], centHi[iter]);
  }

  const Int_t jtMax = 2;
  const std::string jtOrder[jtMax] = {"Lead", "Sublead"};

  const Int_t nPTDBins = 20;
  const Float_t ptdLow = 0.0001;
  const Float_t ptdHi = 0.9999;

  const Int_t nTauBins = 10;
  const Float_t tauLow = 0.0001;
  const Float_t tauHi = 0.9999;

  const Int_t nSubBins  = 40;
  const Int_t subLow = 0;
  const Int_t subHi = 1;

  for(Int_t centIter = 0; centIter < centMax; centIter++){
    const std::string backStr = Form("_%s_h", centString[centIter].c_str());

    for(Int_t jtIter = 0; jtIter < jtMax; jtIter++){
      const std::string ptdStr = Form("%s%sPTD%s_", evtSelAlg.c_str(), clustAlg.c_str(), jtOrder[jtIter].c_str());
      const std::string tau21Str = Form("%s%sTau21%s_", evtSelAlg.c_str(), clustAlg.c_str(), jtOrder[jtIter].c_str());
      const std::string tau32Str = Form("%s%sTau32%s_", evtSelAlg.c_str(), clustAlg.c_str(), jtOrder[jtIter].c_str());
      const std::string ratStr = Form("%s%sRat%s_", evtSelAlg.c_str(), clustAlg.c_str(), jtOrder[jtIter].c_str());

      ptdHist_Tot_p[centIter][jtIter] = new TH1F(Form("%sTot%s", ptdStr.c_str(), backStr.c_str()), Form("%sTot%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);
      ptdHist_Q_p[centIter][jtIter] = new TH1F(Form("%sQ%s", ptdStr.c_str(), backStr.c_str()), Form("%sQ%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);
      ptdHist_G_p[centIter][jtIter] = new TH1F(Form("%sG%s", ptdStr.c_str(), backStr.c_str()), Form("%sG%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);
      ptdHist_Else_p[centIter][jtIter] = new TH1F(Form("%sElse%s", ptdStr.c_str(), backStr.c_str()), Form("%sElse%s", ptdStr.c_str(), backStr.c_str()), nPTDBins, ptdLow, ptdHi);

      for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	const std::string betaStr = Form("Beta%d_", betaIter);

	tau21Hist_Tot_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sTot%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sTot%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau21Hist_Q_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sQ%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sQ%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau21Hist_G_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sG%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sG%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau21Hist_Else_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sElse%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sElse%s", tau21Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);

	tau32Hist_Tot_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sTot%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sTot%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau32Hist_Q_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sQ%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sQ%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau32Hist_G_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sG%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sG%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
	tau32Hist_Else_p[centIter][jtIter][betaIter] = new TH1F(Form("%s%sElse%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), Form("%s%sElse%s", tau32Str.c_str(), betaStr.c_str(), backStr.c_str()), nTauBins, tauLow, tauHi);
      }

      for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
	const std::string subJtStr = Form("SubJt%d_", subJtIter);
	pfSubRatHist_Tot_p[centIter][jtIter][subJtIter] = new TH1F(Form("%s%sTot%s", ratStr.c_str(), subJtStr.c_str(), backStr.c_str()), Form("%s%sTot%s", ratStr.c_str(), subJtStr.c_str(), backStr.c_str()), nSubBins, subLow, subHi);
      }
    }
  }

  return;
}

void CleanHist(TH1F* cleanHist_p)
{
  if(cleanHist_p!=0){
    delete cleanHist_p;
    cleanHist_p = 0;
  }
  return;
}

void CleanHistAll(sampleType sType = kHIDATA)
{
  const Bool_t hi = isHI(sType);

  Int_t centMax = 1;
  if(hi) centMax = 4;

  const Int_t jtMax = 2;

  for(Int_t centIter = 0; centIter < centMax; centIter++){
    for(Int_t jtIter = 0; jtIter < jtMax; jtIter++){
      CleanHist(ptdHist_Tot_p[centIter][jtIter]);
      CleanHist(ptdHist_Q_p[centIter][jtIter]);
      CleanHist(ptdHist_G_p[centIter][jtIter]);
      CleanHist(ptdHist_Else_p[centIter][jtIter]);

      for(Int_t betaIter = 0; betaIter < nBeta; betaIter++){
	CleanHist(tau21Hist_Tot_p[centIter][jtIter][betaIter]);
	CleanHist(tau21Hist_Q_p[centIter][jtIter][betaIter]);
	CleanHist(tau21Hist_G_p[centIter][jtIter][betaIter]);
	CleanHist(tau21Hist_Else_p[centIter][jtIter][betaIter]);

	CleanHist(tau32Hist_Tot_p[centIter][jtIter][betaIter]);
	CleanHist(tau32Hist_Q_p[centIter][jtIter][betaIter]);
	CleanHist(tau32Hist_G_p[centIter][jtIter][betaIter]);
	CleanHist(tau32Hist_Else_p[centIter][jtIter][betaIter]);
      }

      for(Int_t subJtIter = 0; subJtIter < nSubjet; subJtIter++){
	CleanHist(pfSubRatHist_Tot_p[centIter][jtIter][subJtIter]);
      }
    }
  }

  return;
}


#endif
