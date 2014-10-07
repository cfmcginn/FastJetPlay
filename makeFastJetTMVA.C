//=============================================
// Author: Chris McGinn
//
// FastJet TMVA
//
//
//=============================================                                                                                            

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVAGui.C"


#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void makeFastJetTMVA(const std::string inFileName, const std::stringm outFileName)
{

  TMVA::Tools::Instance();

  std::map<std::string,int> Use;

  Use["Cuts"] = 0;
  Use["CutsD"] = 0;
  Use["CutsPCA"] = 0;
  Use["CutsGA"] = 1;
  Use["CutsSA"] = 0;

  Use["Likelihood"] = 0;
  Use["LikelihoodD"] = 1; 
  Use["LikelihoodPCA"] = 0;
  Use["LikelihoodKDE"] = 0;
  Use["LikelihoodMIX"] = 0;

  Use["PDERS"] = 0;
  Use["PDERSD"] = 0;
  Use["PDERSPCA"] = 0;
  Use["PDEFoam"] = 0;
  Use["PDEFoamBoost"] = 0;
  Use["KNN"] = 0;

  Use["LD"] = 0;
  Use["Fisher"] = 0;
  Use["FisherG"] = 0;
  Use["BoostedFisher"] = 0;
  Use["HMatrix"] = 0;

  Use["FDA_GA"] = 0; 
  Use["FDA_SA"] = 0;
  Use["FDA_MC"] = 0;
  Use["FDA_MT"] = 0;
  Use["FDA_GAMT"] = 0;
  Use["FDA_MCMT"] = 0;

  Use["MLP"] = 0; 
  Use["MLPBFGS"] = 0;
  Use["MLPBNN"] = 0;
  Use["CFMlpANN"] = 0;
  Use["TMlpANN"] = 0; 

  Use["SVM"] = 0;

  Use["BDT"] = 0; 
  Use["BDTG"] = 0;
  Use["BDTB"] = 0;
  Use["BDTD"] = 0;
  Use["BDTF"] = 0;

  Use["RuleFit"] = 0;

  std::cout << std::endl;
  std::cout << "==> Start TMVAClassification" << std::endl;

  if(myMethodList != ""){
    for(std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

    std::vector<TString> mlist = TMVA::gTools().SplitString(myMethodList, ',');

    for (UInt_t i=0; i<mlist.size(); i++){
      std::string regMethod(mlist[i]);
      
      if(Use.find(regMethod) == Use.end()){
	std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return;
      }

      Use[regMethod] = 1;
    }
  }

  TFile* outFile_p = new TFile(outFileName.c_str(), "RECREATE");

  TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outFile_p,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

  factory->AddVariable("pfJtVsPTD", "F");
  factory->AddVariable("pfJtVsR2", "F");
  factory->AddVariable("pfJtVsSigma", "F");

  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");

  std::cout << "--- TMVAClassification : Using input file: " << inFile_p->GetName() << std::endl;

  TTree* signalTree_p = (TTree*)inFile_p->Get("pfCandTreeAna");
  TTree* backgroundTree_p = (TTree*)inFile_p->Get("pfCandTreeAna");

  TTree* friendTree_p = (TTree*)inFile_p->Get("jetTreeAna");

  signalTree_p->AddFriend(friendTree_p);
  backgroundTree_p->AddFriend(friendTree_p);

  Double_t signalWeight = 1.0;
  Double_t backgroundWeight = 1.0;

  factory->AddSignalTree(signalTree_p, signalWeight);
  factory->AddBackgroundTree(backgroundTree_p, backgroundWeight);

  TCut signalCuts = Form("pthatWeight*(pthat > 80 && pfJtVsPt > 100 && TMath::Abs(pfJtVsEta) < 2.0 && TMath::Abs(pfJtVsRefPart) < 9)");
  TCut backgroundCuts = Form("pthatWeight*(pthat > 80 && pfJtVsPt > 100 && TMath::Abs(pfJtVsEta) < 2.0 && TMath::Abs(pfJtVsRefPart) == 21)");

  factory->PrepareTrainingAndTestTree(signalCuts, backgroundCuts, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );


  if(Use["Cuts"]) factory->BookMethod(TMVA::Types::kCuts, "Cuts", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");
  if(Use["CutsD"]) factory->BookMethod(TMVA::Types::kCuts, "CutsD", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate");
  if(Use["CutsPCA"]) factory->BookMethod(TMVA::Types::kCuts, "CutsPCA", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA");
  if(Use["CutsGA"]) factory->BookMethod(TMVA::Types::kCuts, "CutsGA", "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95");
  if(Use["CutsSA"]) factory->BookMethod(TMVA::Types::kCuts, "CutsSA", "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale");

  if(Use["Likelihood"]) factory->BookMethod(TMVA::Types::kLikelihood, "Likelihood", "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50");
  if(Use["LikelihoodD"]) factory->BookMethod(TMVA::Types::kLikelihood, "LikelihoodD", "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate");
  if(Use["LikelihoodPCA"]) factory->BookMethod(TMVA::Types::kLikelihood, "LikelihoodPCA", "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA");
  if(Use["LikelihoodKDE"]) factory->BookMethod(TMVA::Types::kLikelihood, "LikelihoodKDE", "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50");
  if(Use["LikelihoodMIX"]) factory->BookMethod(TMVA::Types::kLikelihood, "LikelihoodMIX", "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50");



  return;
}

