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

void makeFastJetTMVA(const std::string inFileName, const std::string outFileName, TString myMethodList = "CutsGA")
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

  factory->AddVariable("pfJtVsPTD", 'F');
  factory->AddVariable("pfJtVsR2", 'F');
  factory->AddVariable("pfJtVsSigma", 'F');

  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");

  std::cout << "--- TMVAClassification : Using input file: " << inFile_p->GetName() << std::endl;

  TTree* signalTree_p = (TTree*)inFile_p->Get("pfCandTreeAna");
  TTree* backgroundTree_p = (TTree*)inFile_p->Get("pfCandTreeAna");

  std::cout << "1" << std::endl;

  TTree* friendTree_p = (TTree*)inFile_p->Get("jetTreeAna");

  signalTree_p->AddFriend(friendTree_p);
  backgroundTree_p->AddFriend(friendTree_p);

  std::cout << "2" << std::endl;

  Double_t signalWeight = 1.0;
  Double_t backgroundWeight = 1.0;

  factory->AddSignalTree(signalTree_p, signalWeight);
  factory->AddBackgroundTree(backgroundTree_p, backgroundWeight);

  std::cout << "3" << std::endl;

  TCut signalCuts = Form("pthatWeight*(pthat > 80 && pfJtVsPt > 100 && TMath::Abs(pfJtVsEta) < 2.0 && TMath::Abs(pfJtVsRefPart) < 9)");
  TCut backgroundCuts = Form("pthatWeight*(pthat > 80 && pfJtVsPt > 100 && TMath::Abs(pfJtVsEta) < 2.0 && TMath::Abs(pfJtVsRefPart) == 21)");

  factory->PrepareTrainingAndTestTree(signalCuts, backgroundCuts, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );


  std::cout << "4" << std::endl;

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


  if(Use["PDERS"]) factory->BookMethod(TMVA::Types::kPDERS, "PDERS", "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600");
  if(Use["PDERSD"]) factory->BookMethod(TMVA::Types::kPDERS, "PDERSD", "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate");
  if(Use["PDERSPCA"]) factory->BookMethod(TMVA::Types::kPDERS, "PDERSPCA", "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA");
  if(Use["PDEFoam"]) factory->BookMethod(TMVA::Types::kPDEFoam, "PDEFoam", "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T");
  if(Use["PDEFoamBoost"]) factory->BookMethod(TMVA::Types::kPDEFoam, "PDEFoamBoost", "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T");


  if(Use["KNN"]) factory->BookMethod(TMVA::Types::kKNN, "KNN", "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim");
  if(Use["HMatrix"]) factory->BookMethod(TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None");
  if(Use["LD"]) factory->BookMethod(TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10");
  if(Use["Fisher"]) factory->BookMethod(TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10");
  if(Use["FisherG"]) factory->BookMethod(TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss");
  if(Use["BoostedFisher"]) factory->BookMethod(TMVA::Types::kFisher, "BoostedFisher", "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring");


  if(Use["FDA_MC"]) factory->BookMethod(TMVA::Types::kFDA, "FDA_MC", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1");
  if(Use["FDA_GA"]) factory->BookMethod(TMVA::Types::kFDA, "FDA_GA", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1");
  if(Use["FDA_SA"]) factory->BookMethod(TMVA::Types::kFDA, "FDA_SA", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale");
  if(Use["FDA_MT"]) factory->BookMethod(TMVA::Types::kFDA, "FDA_MT", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch");
  if(Use["FDA_GAMT"]) factory->BookMethod(TMVA::Types::kFDA, "FDA_GAMT", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim");
  if(Use["FDA_MCMT"]) factory->BookMethod(TMVA::Types::kFDA, "FDA_MCMT", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20");

  
  if(Use["MLP"]) factory->BookMethod(TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator");
  if(Use["MLPBFGS"]) factory->BookMethod(TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator");
  if(Use["MLPBNN"]) factory->BookMethod(TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator"); 
  if(Use["CFMlpANN"]) factory->BookMethod(TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N" ); 
  if(Use["TMlpANN"]) factory->BookMethod(TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3" ); 
  if(Use["SVM"]) factory->BookMethod(TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm");


  if(Use["BDTG"]) factory->BookMethod(TMVA::Types::kBDT, "BDTG", "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2");
  if(Use["BDT"]) factory->BookMethod(TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
  if(Use["BDTB"]) factory->BookMethod(TMVA::Types::kBDT, "BDTB", "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20");
  if(Use["BDTD"]) factory->BookMethod(TMVA::Types::kBDT, "BDTD", "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate");
  if(Use["BDTF"]) factory->BookMethod(TMVA::Types::kBDT, "BDTMitFisher", "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20");
  if(Use["RuleFit"]) factory->BookMethod(TMVA::Types::kRuleFit, "RuleFit", "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02");

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  outFile_p->Close();

  std::cout << "==> Wrote root file: " << outFile_p->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;

  delete factory;

  if(!gROOT->IsBatch()) TMVAGui(outFileName.c_str());

  return;
}

