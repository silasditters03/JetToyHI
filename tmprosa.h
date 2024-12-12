//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct  7 14:27:54 2024 by ROOT version 6.30/06
// from TTree jetTree/JetToyHI tree
// found on file: JetToyHIResultSimpleJetAnalysis.root
//////////////////////////////////////////////////////////

#ifndef tmprosa_h
#define tmprosa_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class tmprosa {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<double>  *eventWeight;
   vector<double>  *partonsPt;
   vector<double>  *partonsEta;
   vector<double>  *partonsE;
   vector<double>  *partonsPhi;
   vector<double>  *partonsM;
   vector<int>     *partonsPDG;
   vector<double>  *sigJetPt;
   vector<double>  *sigJetEta;
   vector<double>  *sigJetE;
   vector<double>  *sigJetPhi;
   vector<double>  *sigJetM;
   vector<double>  *sigJetArea;
   vector<double>  *pTDSig;
   vector<double>  *widthSig;
   vector<vector<double> > *sigJetRecurZcut_dr12;
   vector<vector<double> > *sigJetRecurZcut_erad;
   vector<vector<double> > *sigJetRecurZcut_jetpt;
   vector<vector<double> > *sigJetRecurZcut_logdr12;
   vector<vector<double> > *sigJetRecurZcut_logztheta;
   vector<vector<double> > *sigJetRecurZcut_z;
   vector<vector<double> > *sigJetRecur_dr12;
   vector<vector<double> > *sigJetRecur_erad;
   vector<vector<double> > *sigJetRecur_jetpt;
   vector<vector<double> > *sigJetRecur_logdr12;
   vector<vector<double> > *sigJetRecur_logztheta;
   vector<vector<double> > *sigJetRecur_z;
   vector<double>  *sigJetSDBeta00Z01Pt;
   vector<double>  *sigJetSDBeta00Z01Eta;
   vector<double>  *sigJetSDBeta00Z01E;
   vector<double>  *sigJetSDBeta00Z01Phi;
   vector<double>  *sigJetSDBeta00Z01M;
   vector<double>  *sigJetSDBeta00Z01Area;
   vector<double>  *dr12SigSDBeta00Z01;
   vector<double>  *eradSigSDBeta00Z01;
   vector<double>  *productSigSDBeta00Z01;
   vector<double>  *zgSigSDBeta00Z01;
   vector<double>  *sigJetSDBeta00Z05Pt;
   vector<double>  *sigJetSDBeta00Z05Eta;
   vector<double>  *sigJetSDBeta00Z05E;
   vector<double>  *sigJetSDBeta00Z05Phi;
   vector<double>  *sigJetSDBeta00Z05M;
   vector<double>  *sigJetSDBeta00Z05Area;
   vector<double>  *dr12SigSDBeta00Z05;
   vector<double>  *eradSigSDBeta00Z05;
   vector<double>  *productSigSDBeta00Z05;
   vector<double>  *zgSigSDBeta00Z05;
   vector<double>  *sigJetSDBeta00Z03Pt;
   vector<double>  *sigJetSDBeta00Z03Eta;
   vector<double>  *sigJetSDBeta00Z03E;
   vector<double>  *sigJetSDBeta00Z03Phi;
   vector<double>  *sigJetSDBeta00Z03M;
   vector<double>  *sigJetSDBeta00Z03Area;
   vector<double>  *dr12SigSDBeta00Z03;
   vector<double>  *eradSigSDBeta00Z03;
   vector<double>  *productSigSDBeta00Z03;
   vector<double>  *zgSigSDBeta00Z03;

   // List of branches
   TBranch        *b_eventWeight;   //!
   TBranch        *b_partonsPt;   //!
   TBranch        *b_partonsEta;   //!
   TBranch        *b_partonsE;   //!
   TBranch        *b_partonsPhi;   //!
   TBranch        *b_partonsM;   //!
   TBranch        *b_partonsPDG;   //!
   TBranch        *b_sigJetPt;   //!
   TBranch        *b_sigJetEta;   //!
   TBranch        *b_sigJetE;   //!
   TBranch        *b_sigJetPhi;   //!
   TBranch        *b_sigJetM;   //!
   TBranch        *b_sigJetArea;   //!
   TBranch        *b_pTDSig;   //!
   TBranch        *b_widthSig;   //!
   TBranch        *b_sigJetRecurZcut_dr12;   //!
   TBranch        *b_sigJetRecurZcut_erad;   //!
   TBranch        *b_sigJetRecurZcut_jetpt;   //!
   TBranch        *b_sigJetRecurZcut_logdr12;   //!
   TBranch        *b_sigJetRecurZcut_logztheta;   //!
   TBranch        *b_sigJetRecurZcut_z;   //!
   TBranch        *b_sigJetRecur_dr12;   //!
   TBranch        *b_sigJetRecur_erad;   //!
   TBranch        *b_sigJetRecur_jetpt;   //!
   TBranch        *b_sigJetRecur_logdr12;   //!
   TBranch        *b_sigJetRecur_logztheta;   //!
   TBranch        *b_sigJetRecur_z;   //!
   TBranch        *b_sigJetSDBeta00Z01Pt;   //!
   TBranch        *b_sigJetSDBeta00Z01Eta;   //!
   TBranch        *b_sigJetSDBeta00Z01E;   //!
   TBranch        *b_sigJetSDBeta00Z01Phi;   //!
   TBranch        *b_sigJetSDBeta00Z01M;   //!
   TBranch        *b_sigJetSDBeta00Z01Area;   //!
   TBranch        *b_dr12SigSDBeta00Z01;   //!
   TBranch        *b_eradSigSDBeta00Z01;   //!
   TBranch        *b_productSigSDBeta00Z01;   //!
   TBranch        *b_zgSigSDBeta00Z01;   //!
   TBranch        *b_sigJetSDBeta00Z05Pt;   //!
   TBranch        *b_sigJetSDBeta00Z05Eta;   //!
   TBranch        *b_sigJetSDBeta00Z05E;   //!
   TBranch        *b_sigJetSDBeta00Z05Phi;   //!
   TBranch        *b_sigJetSDBeta00Z05M;   //!
   TBranch        *b_sigJetSDBeta00Z05Area;   //!
   TBranch        *b_dr12SigSDBeta00Z05;   //!
   TBranch        *b_eradSigSDBeta00Z05;   //!
   TBranch        *b_productSigSDBeta00Z05;   //!
   TBranch        *b_zgSigSDBeta00Z05;   //!
   TBranch        *b_sigJetSDBeta00Z03Pt;   //!
   TBranch        *b_sigJetSDBeta00Z03Eta;   //!
   TBranch        *b_sigJetSDBeta00Z03E;   //!
   TBranch        *b_sigJetSDBeta00Z03Phi;   //!
   TBranch        *b_sigJetSDBeta00Z03M;   //!
   TBranch        *b_sigJetSDBeta00Z03Area;   //!
   TBranch        *b_dr12SigSDBeta00Z03;   //!
   TBranch        *b_eradSigSDBeta00Z03;   //!
   TBranch        *b_productSigSDBeta00Z03;   //!
   TBranch        *b_zgSigSDBeta00Z03;   //!

   tmprosa(TTree *tree=0);
   virtual ~tmprosa();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tmprosa_cxx
tmprosa::tmprosa(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("JetToyHIResultSimpleJetAnalysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("JetToyHIResultSimpleJetAnalysis.root");
      }
      f->GetObject("jetTree",tree);

   }
   Init(tree);
}

tmprosa::~tmprosa()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tmprosa::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tmprosa::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tmprosa::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   eventWeight = 0;
   partonsPt = 0;
   partonsEta = 0;
   partonsE = 0;
   partonsPhi = 0;
   partonsM = 0;
   partonsPDG = 0;
   sigJetPt = 0;
   sigJetEta = 0;
   sigJetE = 0;
   sigJetPhi = 0;
   sigJetM = 0;
   sigJetArea = 0;
   pTDSig = 0;
   widthSig = 0;
   sigJetRecurZcut_dr12 = 0;
   sigJetRecurZcut_erad = 0;
   sigJetRecurZcut_jetpt = 0;
   sigJetRecurZcut_logdr12 = 0;
   sigJetRecurZcut_logztheta = 0;
   sigJetRecurZcut_z = 0;
   sigJetRecur_dr12 = 0;
   sigJetRecur_erad = 0;
   sigJetRecur_jetpt = 0;
   sigJetRecur_logdr12 = 0;
   sigJetRecur_logztheta = 0;
   sigJetRecur_z = 0;
   sigJetSDBeta00Z01Pt = 0;
   sigJetSDBeta00Z01Eta = 0;
   sigJetSDBeta00Z01E = 0;
   sigJetSDBeta00Z01Phi = 0;
   sigJetSDBeta00Z01M = 0;
   sigJetSDBeta00Z01Area = 0;
   dr12SigSDBeta00Z01 = 0;
   eradSigSDBeta00Z01 = 0;
   productSigSDBeta00Z01 = 0;
   zgSigSDBeta00Z01 = 0;
   sigJetSDBeta00Z05Pt = 0;
   sigJetSDBeta00Z05Eta = 0;
   sigJetSDBeta00Z05E = 0;
   sigJetSDBeta00Z05Phi = 0;
   sigJetSDBeta00Z05M = 0;
   sigJetSDBeta00Z05Area = 0;
   dr12SigSDBeta00Z05 = 0;
   eradSigSDBeta00Z05 = 0;
   productSigSDBeta00Z05 = 0;
   zgSigSDBeta00Z05 = 0;
   sigJetSDBeta00Z03Pt = 0;
   sigJetSDBeta00Z03Eta = 0;
   sigJetSDBeta00Z03E = 0;
   sigJetSDBeta00Z03Phi = 0;
   sigJetSDBeta00Z03M = 0;
   sigJetSDBeta00Z03Area = 0;
   dr12SigSDBeta00Z03 = 0;
   eradSigSDBeta00Z03 = 0;
   productSigSDBeta00Z03 = 0;
   zgSigSDBeta00Z03 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight);
   fChain->SetBranchAddress("partonsPt", &partonsPt, &b_partonsPt);
   fChain->SetBranchAddress("partonsEta", &partonsEta, &b_partonsEta);
   fChain->SetBranchAddress("partonsE", &partonsE, &b_partonsE);
   fChain->SetBranchAddress("partonsPhi", &partonsPhi, &b_partonsPhi);
   fChain->SetBranchAddress("partonsM", &partonsM, &b_partonsM);
   fChain->SetBranchAddress("partonsPDG", &partonsPDG, &b_partonsPDG);
   fChain->SetBranchAddress("sigJetPt", &sigJetPt, &b_sigJetPt);
   fChain->SetBranchAddress("sigJetEta", &sigJetEta, &b_sigJetEta);
   fChain->SetBranchAddress("sigJetE", &sigJetE, &b_sigJetE);
   fChain->SetBranchAddress("sigJetPhi", &sigJetPhi, &b_sigJetPhi);
   fChain->SetBranchAddress("sigJetM", &sigJetM, &b_sigJetM);
   fChain->SetBranchAddress("sigJetArea", &sigJetArea, &b_sigJetArea);
   fChain->SetBranchAddress("pTDSig", &pTDSig, &b_pTDSig);
   fChain->SetBranchAddress("widthSig", &widthSig, &b_widthSig);
   fChain->SetBranchAddress("sigJetRecurZcut_dr12", &sigJetRecurZcut_dr12, &b_sigJetRecurZcut_dr12);
   fChain->SetBranchAddress("sigJetRecurZcut_erad", &sigJetRecurZcut_erad, &b_sigJetRecurZcut_erad);
   fChain->SetBranchAddress("sigJetRecurZcut_jetpt", &sigJetRecurZcut_jetpt, &b_sigJetRecurZcut_jetpt);
   fChain->SetBranchAddress("sigJetRecurZcut_logdr12", &sigJetRecurZcut_logdr12, &b_sigJetRecurZcut_logdr12);
   fChain->SetBranchAddress("sigJetRecurZcut_logztheta", &sigJetRecurZcut_logztheta, &b_sigJetRecurZcut_logztheta);
   fChain->SetBranchAddress("sigJetRecurZcut_z", &sigJetRecurZcut_z, &b_sigJetRecurZcut_z);
   fChain->SetBranchAddress("sigJetRecur_dr12", &sigJetRecur_dr12, &b_sigJetRecur_dr12);
   fChain->SetBranchAddress("sigJetRecur_erad", &sigJetRecur_erad, &b_sigJetRecur_erad);
   fChain->SetBranchAddress("sigJetRecur_jetpt", &sigJetRecur_jetpt, &b_sigJetRecur_jetpt);
   fChain->SetBranchAddress("sigJetRecur_logdr12", &sigJetRecur_logdr12, &b_sigJetRecur_logdr12);
   fChain->SetBranchAddress("sigJetRecur_logztheta", &sigJetRecur_logztheta, &b_sigJetRecur_logztheta);
   fChain->SetBranchAddress("sigJetRecur_z", &sigJetRecur_z, &b_sigJetRecur_z);
   fChain->SetBranchAddress("sigJetSDBeta00Z01Pt", &sigJetSDBeta00Z01Pt, &b_sigJetSDBeta00Z01Pt);
   fChain->SetBranchAddress("sigJetSDBeta00Z01Eta", &sigJetSDBeta00Z01Eta, &b_sigJetSDBeta00Z01Eta);
   fChain->SetBranchAddress("sigJetSDBeta00Z01E", &sigJetSDBeta00Z01E, &b_sigJetSDBeta00Z01E);
   fChain->SetBranchAddress("sigJetSDBeta00Z01Phi", &sigJetSDBeta00Z01Phi, &b_sigJetSDBeta00Z01Phi);
   fChain->SetBranchAddress("sigJetSDBeta00Z01M", &sigJetSDBeta00Z01M, &b_sigJetSDBeta00Z01M);
   fChain->SetBranchAddress("sigJetSDBeta00Z01Area", &sigJetSDBeta00Z01Area, &b_sigJetSDBeta00Z01Area);
   fChain->SetBranchAddress("dr12SigSDBeta00Z01", &dr12SigSDBeta00Z01, &b_dr12SigSDBeta00Z01);
   fChain->SetBranchAddress("eradSigSDBeta00Z01", &eradSigSDBeta00Z01, &b_eradSigSDBeta00Z01);
   fChain->SetBranchAddress("productSigSDBeta00Z01", &productSigSDBeta00Z01, &b_productSigSDBeta00Z01);
   fChain->SetBranchAddress("zgSigSDBeta00Z01", &zgSigSDBeta00Z01, &b_zgSigSDBeta00Z01);
   fChain->SetBranchAddress("sigJetSDBeta00Z05Pt", &sigJetSDBeta00Z05Pt, &b_sigJetSDBeta00Z05Pt);
   fChain->SetBranchAddress("sigJetSDBeta00Z05Eta", &sigJetSDBeta00Z05Eta, &b_sigJetSDBeta00Z05Eta);
   fChain->SetBranchAddress("sigJetSDBeta00Z05E", &sigJetSDBeta00Z05E, &b_sigJetSDBeta00Z05E);
   fChain->SetBranchAddress("sigJetSDBeta00Z05Phi", &sigJetSDBeta00Z05Phi, &b_sigJetSDBeta00Z05Phi);
   fChain->SetBranchAddress("sigJetSDBeta00Z05M", &sigJetSDBeta00Z05M, &b_sigJetSDBeta00Z05M);
   fChain->SetBranchAddress("sigJetSDBeta00Z05Area", &sigJetSDBeta00Z05Area, &b_sigJetSDBeta00Z05Area);
   fChain->SetBranchAddress("dr12SigSDBeta00Z05", &dr12SigSDBeta00Z05, &b_dr12SigSDBeta00Z05);
   fChain->SetBranchAddress("eradSigSDBeta00Z05", &eradSigSDBeta00Z05, &b_eradSigSDBeta00Z05);
   fChain->SetBranchAddress("productSigSDBeta00Z05", &productSigSDBeta00Z05, &b_productSigSDBeta00Z05);
   fChain->SetBranchAddress("zgSigSDBeta00Z05", &zgSigSDBeta00Z05, &b_zgSigSDBeta00Z05);
   fChain->SetBranchAddress("sigJetSDBeta00Z03Pt", &sigJetSDBeta00Z03Pt, &b_sigJetSDBeta00Z03Pt);
   fChain->SetBranchAddress("sigJetSDBeta00Z03Eta", &sigJetSDBeta00Z03Eta, &b_sigJetSDBeta00Z03Eta);
   fChain->SetBranchAddress("sigJetSDBeta00Z03E", &sigJetSDBeta00Z03E, &b_sigJetSDBeta00Z03E);
   fChain->SetBranchAddress("sigJetSDBeta00Z03Phi", &sigJetSDBeta00Z03Phi, &b_sigJetSDBeta00Z03Phi);
   fChain->SetBranchAddress("sigJetSDBeta00Z03M", &sigJetSDBeta00Z03M, &b_sigJetSDBeta00Z03M);
   fChain->SetBranchAddress("sigJetSDBeta00Z03Area", &sigJetSDBeta00Z03Area, &b_sigJetSDBeta00Z03Area);
   fChain->SetBranchAddress("dr12SigSDBeta00Z03", &dr12SigSDBeta00Z03, &b_dr12SigSDBeta00Z03);
   fChain->SetBranchAddress("eradSigSDBeta00Z03", &eradSigSDBeta00Z03, &b_eradSigSDBeta00Z03);
   fChain->SetBranchAddress("productSigSDBeta00Z03", &productSigSDBeta00Z03, &b_productSigSDBeta00Z03);
   fChain->SetBranchAddress("zgSigSDBeta00Z03", &zgSigSDBeta00Z03, &b_zgSigSDBeta00Z03);
   Notify();
}

Bool_t tmprosa::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tmprosa::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tmprosa::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tmprosa_cxx
