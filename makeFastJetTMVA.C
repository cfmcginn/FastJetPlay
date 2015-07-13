#include "TFile.h"
#include "TTree.h"
#include <string>
#include "VectFunc.h"
#include "TMVA/Factory.h"
#include "TMVA/Types.h"
#include "TMath.h"
#include "TCut.h"
#include <iostream>

const Float_t leadJtCut = 120.;
const Float_t subLeadJtCut = 50.;

const Float_t totJtPtCut = 50.;
const Float_t totJtEtaCut = 2.0;
const Float_t totJtAjCut = 0.33;

const Float_t pPbEtaBoost = 0.4654094531;

const std::string algType[5] = {"PuCalo", "VsCalo", "T", "PuPF", "VsPF"};

const Int_t ptCuts[6] = {60, 80, 100, 120, 140, 200};
const Int_t ptPosArr[5] = {3, 4, 5, 6, 7};


void makeQGTMVA(TTree* inTree_p)
{
  TFile* outFile_p = new TFile("/export/d00/scratch/cfmcginn/qGFactoryTest.root", "UPDATE");

  TMVA::Factory* qGFactory = new TMVA::Factory("qGFactory", outFile_p, "");


  TCut qCut = "TMath::Abs(refPart) < 9";
  TCut gCut = "TMath::Abs(refPart) == 21";

  qGFactory->SetInputTrees(inTree_p, qCut, gCut);

  outFile_p->cd();

  qGFactory->SetWeightExpression("pthatWeight");

  qGFactory->AddVariable("ffm13", 'F');
  qGFactory->AddVariable("ffm5", 'F');
  qGFactory->AddVariable("jtChg", 'F');
  qGFactory->AddVariable("jtEta", 'F');
  qGFactory->AddVariable("jtPt", 'F');
  qGFactory->AddVariable("sig2", 'F');
  //  qGFactory->AddVariable("jtN", 'I');

  TCut selectionCut = "";
  qGFactory->PrepareTrainingAndTestTree(selectionCut, "nTrain_Signal=0:nTest_Signal=0:nTrain_Background=0:nTest_Background=0");

  outFile_p->cd();

  qGFactory->BookMethod( TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

  qGFactory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );



  qGFactory->TrainAllMethods();
  qGFactory->TestAllMethods();
  qGFactory->EvaluateAllMethods();

  outFile_p->Close();
  delete outFile_p;

  return;
}


void makeFastJetTMVA(const std::string inName)
{
  TFile* inFile_p = new TFile(inName.c_str(), "READ");

  Int_t refPartArr_[5];
  Float_t jtChgArr_[5][5];
  Float_t jtEtaArr_[5];
  Float_t jtFFMArr_[5][14];
  Float_t sig2Arr_[5][3];
  Float_t jtFFMRawArr_[5][14];
  Int_t jtConstNRawArr_[5];
  Int_t matchRaw_[5];
  Int_t matchSK_[5];
  Float_t matchSKPt_[5];


  Int_t refPart_;
  Float_t jtChg_;
  Float_t jtEta_;
  Float_t jtPt_;
  Float_t ffm13_;
  Float_t ffm5_;
  Float_t sig2_;
  Int_t jtN_;
  Float_t pthatWeight_;

  Bool_t eventSet[5];
  Float_t AlgJtPt[5][5];
  Float_t AlgJtEta[5][5];
  Float_t AlgJtDelPhi[5];
  Float_t pthat;

  TTree* jetTree_p = (TTree*)inFile_p->Get("jetTreeAna");
  jetTree_p->SetBranchStatus("*", 0);
  jetTree_p->SetBranchStatus("eventSet", 1);
  jetTree_p->SetBranchStatus("AlgJtPt", 1);
  jetTree_p->SetBranchStatus("AlgJtEta", 1);
  jetTree_p->SetBranchStatus("AlgJtDelPhi", 1);
  jetTree_p->SetBranchStatus("pthat", 1);
  jetTree_p->SetBranchStatus("pthatWeight", 1);

  jetTree_p->SetBranchAddress("eventSet", eventSet);
  jetTree_p->SetBranchAddress("AlgJtPt", AlgJtPt);
  jetTree_p->SetBranchAddress("AlgJtEta", AlgJtEta);
  jetTree_p->SetBranchAddress("AlgJtDelPhi", AlgJtDelPhi);
  jetTree_p->SetBranchAddress("pthat", &pthat);
  jetTree_p->SetBranchAddress("pthatWeight", &pthatWeight_);


  TTree* genTree_p = (TTree*)inFile_p->Get("genTreeAna");
  genTree_p->SetBranchStatus("*", 0);
  genTree_p->SetBranchStatus("genSKChg_jtRefPart", 1);
  genTree_p->SetBranchStatus("genSKChg_jtFFMUnsub", 1);
  genTree_p->SetBranchStatus("genRawChg_jtFFMSub", 1);
  genTree_p->SetBranchStatus("genSKChg_jtChg", 1);
  genTree_p->SetBranchStatus("genSKChg_jtSigma", 1);
  genTree_p->SetBranchStatus("genSKChg_jtEta", 1);
  genTree_p->SetBranchStatus("genSKChg_jtMatchIndex", 1);
  genTree_p->SetBranchStatus("genSKChg_jtMatchPt", 1);
  genTree_p->SetBranchStatus("genRawChg_jtMatchIndex", 1);
  genTree_p->SetBranchStatus("genRawChg_jtConstN", 1);

  genTree_p->SetBranchAddress("genSKChg_jtRefPart", refPartArr_);
  genTree_p->SetBranchAddress("genSKChg_jtFFMUnsub", jtFFMArr_);
  genTree_p->SetBranchAddress("genRawChg_jtFFMSub", jtFFMRawArr_);
  genTree_p->SetBranchAddress("genSKChg_jtSigma", sig2Arr_);
  genTree_p->SetBranchAddress("genSKChg_jtChg", jtChgArr_);
  genTree_p->SetBranchAddress("genSKChg_jtEta", jtEtaArr_);
  genTree_p->SetBranchAddress("genSKChg_jtMatchIndex", matchSK_);
  genTree_p->SetBranchAddress("genSKChg_jtMatchPt", matchSKPt_);
  genTree_p->SetBranchAddress("genRawChg_jtMatchIndex", matchRaw_);
  genTree_p->SetBranchAddress("genRawChg_jtConstN", jtConstNRawArr_);


  TFile* outFile_p = new TFile("quickTest_QG.root", "UPDATE");
  TTree* mvaTree_p = new TTree("mvaTree", "mvaTree");

  mvaTree_p->Branch("refPart", &refPart_, "refPart/I");
  mvaTree_p->Branch("jtChg", &jtChg_, "jtChg/F");
  mvaTree_p->Branch("jtEta", &jtEta_, "jtEta/F");
  mvaTree_p->Branch("jtPt", &jtPt_, "jtPt/F");
  mvaTree_p->Branch("sig2", &sig2_, "sig2/F");
  mvaTree_p->Branch("ffm13", &ffm13_, "ffm13/F");
  mvaTree_p->Branch("ffm5", &ffm5_, "ffm5/F");
  mvaTree_p->Branch("jtN", &jtN_, "jtN/I");
  mvaTree_p->Branch("pthatWeight", &pthatWeight_, "pthatWeight/F");
  
  Int_t nEntries = genTree_p->GetEntries();
  std::cout << "nEntries: " << nEntries << std::endl;

  for(Int_t iter = 0; iter < nEntries; iter++){
    genTree_p->GetEntry(iter);
    jetTree_p->GetEntry(iter);

    if(iter%10000 == 0){
      std::cout << iter << std::endl;
      
      std::cout << "EventSet: " << eventSet[2] << std::endl;
      std::cout << "pt1,2: " << AlgJtPt[2][0] << ", " << AlgJtPt[2][1] << std::endl;
      std::cout << "eta1,2: " << AlgJtEta[2][0] << ", " << AlgJtEta[2][1] << std::endl;
      std::cout << "dphi: " << AlgJtDelPhi[2] << std::endl;
      std::cout << "pthat: " << pthat << std::endl;
    }

    if(!eventSet[2]) continue;
    if(AlgJtPt[2][0] < 120 || AlgJtPt[2][1] < 50) continue;
    //    if(AlgJtPt[2][0] > 140) continue;
    if(TMath::Abs(AlgJtEta[2][0]) > 1.6 || TMath::Abs(AlgJtEta[2][1]) > 1.6) continue;
    if(AlgJtDelPhi[2] < TMath::Pi()*5.0/6.0) continue;
    if(pthat < 80) continue;
    
    Bool_t match[2] = {false, false};

    for(Int_t iter2 = 0; iter2 < 5; iter2++){
      if(matchSK_[iter2] == 0){
	refPart_ = refPartArr_[iter2];
	jtChg_ = jtChgArr_[iter2][2];
	jtEta_ = jtEtaArr_[iter2];
	sig2_ = sig2Arr_[iter2][2];
	ffm13_ = jtFFMArr_[iter2][13];
	jtPt_ = matchSKPt_[iter2];
	match[0] = true;
	break;
      }
    }

    for(Int_t iter2 = 0; iter2 < 5; iter2++){
      if(matchRaw_[iter2] == 0){
	ffm5_ = jtFFMRawArr_[iter2][5];
	jtN_ = jtConstNRawArr_[iter2];
	match[1] = true;
	break;
      }
    }

    if(!match[0] || !match[1]) continue;

    mvaTree_p->Fill();
  }

  inFile_p->Close();
  delete inFile_p;
  
  outFile_p->cd();
  mvaTree_p->Write("", TObject::kOverwrite);

  makeQGTMVA(mvaTree_p);

  delete mvaTree_p;
  outFile_p->Close();
  delete outFile_p;

  return;
}

