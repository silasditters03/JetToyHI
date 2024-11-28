//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  2 14:47:15 2021 by ROOT version 6.12/06
// from TTree jetTreeSig/JetToyHI tree
// found on file: JetToyHIResultTimeClusBkg_Merged.root
//////////////////////////////////////////////////////////

#ifndef jetTreeSig2_h
#define jetTreeSig2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class jetTreeSig2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   // Parton info only in pythia.
   vector<double>  *eventWeight;
   vector<double>  *partonsPt;
   vector<double>  *partonsEta;
   vector<double>  *partonsPhi;
   vector<double>  *partonsM;
   vector<int>     *partonsPDG;
   vector<double>  *partonsFirstSplitPt;
   vector<double>  *partonsFirstSplitEta;
   vector<double>  *partonsFirstSplitPhi;
   vector<double>  *partonsFirstSplitM;
   vector<int>     *partonsFirstSplitPDG;

   vector<double>  *drSplit;
   vector<double>  *tfSplit;
   vector<double>  *sigJetPt;
   vector<double>  *sigJetEta;
   vector<double>  *sigJetE;

   vector<double>  *sigJetPhi;
   vector<double>  *sigJetM;
   vector<double>  *sigJetArea;


   //extend for the vectors you declared in softDropGroomer part
   vector<double>  *sigJetSDBeta00Z01Pt;
   vector<double>  *sigJetSDBeta00Z05Pt;
   vector<double>  *sigJetSDBeta00Z03Pt;
   vector<double>  *zgSigSDBeta00Z01;
   vector<double>  *eradSigSDBeta00Z01;
   vector<double>  *productSigSDBeta00Z01;
   vector<double>  *dr12SigSDBeta00Z01;
   vector<double>  *zgSigSDBeta00Z05;
   vector<double>  *eradSigSDBeta00Z05;
   vector<double>  *productSigSDBeta00Z05;
   vector<double>  *dr12SigSDBeta00Z05;
   vector<double>  *zgSigSDBeta00Z03;
   vector<double>  *eradSigSDBeta00Z03;
   vector<double>  *productSigSDBeta00Z03;
   vector<double>  *dr12SigSDBeta00Z03;

    //vectors for hadron pairs
   vector<vector<double> > *zg_hadron_pairs;
   vector<vector<double> > *dr_hadron_pairs;
   vector<vector<double> > *E2C_hadron_pairs;


   /*
   vector<vector<double> > *E2C_hadron_pairs_zcut2;
   vector<vector<double> > *E2C_hadron_pairs_zcut3;
   vector<vector<double> > *E2C_hadron_pairs_zcut4;
   vector<vector<double> > *E2C_hadron_pairs_zcut5;

   vector<vector<double> > *dr_hadron_pairs_zcut2;
   vector<vector<double> > *dr_hadron_pairs_zcut3;
   vector<vector<double> > *dr_hadron_pairs_zcut4;
   vector<vector<double> > *dr_hadron_pairs_zcut5;
*/

//extend for the vectors you declared in softDropCounter part
   vector<vector<double> > *sigjetRecurZcut1_dr12;
   vector<vector<double> > *sigjetRecurZcut1_erad;
   vector<vector<double> > *sigjetRecurZcut1_mpt;
   vector<vector<double> > *sigjetRecurZcut1_product;
   vector<vector<double> > *sigjetRecurZcut1_jetpt;
   vector<vector<double> > *sigjetRecurZcut1_logdr12;
   vector<vector<double> > *sigjetRecurZcut1_logztheta;
   vector<vector<double> > *sigjetRecurZcut1_z;
   vector<vector<double> > *sigjetRecurZcut2_dr12;
   vector<vector<double> > *sigjetRecurZcut2_erad;
   vector<vector<double> > *sigjetRecurZcut2_mpt;
   vector<vector<double> > *sigjetRecurZcut2_product;
   vector<vector<double> > *sigjetRecurZcut2_jetpt;
   vector<vector<double> > *sigjetRecurZcut2_logdr12;
   vector<vector<double> > *sigjetRecurZcut2_logztheta;
   vector<vector<double> > *sigjetRecurZcut2_z;
   vector<vector<double> > *sigjetRecur_dr12;
   vector<vector<double> > *sigjetRecur_erad;
   vector<vector<double> > *sigjetRecur_mpt;
   vector<vector<double> > *sigjetRecur_product;
   vector<vector<double> > *sigjetRecur_jetpt;
   vector<vector<double> > *sigjetRecur_logdr12;
   vector<vector<double> > *sigjetRecur_logztheta;
   vector<vector<double> > *sigjetRecur_z;

   


   // List of branches

   TBranch        *b_zg_hadron_pairs;
   TBranch        *b_dr_hadron_pairs;
   TBranch        *b_E2C_hadron_pairs;   
   
   /*
   TBranch        *b_dr_hadron_pairs_zcut2;
   TBranch        *b_dr_hadron_pairs_zcut3;
   TBranch        *b_dr_hadron_pairs_zcut4;
   TBranch        *b_dr_hadron_pairs_zcut5;
   TBranch        *b_E2C_hadron_pairs_zcut2;
   TBranch        *b_E2C_hadron_pairs_zcut3;
   TBranch        *b_E2C_hadron_pairs_zcut4;
   TBranch        *b_E2C_hadron_pairs_zcut5;
   */

   TBranch        *b_sigJetSDBeta00Z01Pt;   //!
   TBranch        *b_sigJetSDBeta00Z05Pt;   //!
   TBranch        *b_sigJetSDBeta00Z03Pt; 
   TBranch        *b_zgSigSDBeta00Z01;   //!
   TBranch        *b_eradSigSDBeta00Z01;
   TBranch        *b_productSigSDBeta00Z01;
   TBranch        *b_dr12SigSDBeta00Z01;
   TBranch        *b_zg;   //!
   TBranch        *b_zgSigSDBeta00Z05;   //!
   TBranch        *b_eradSigSDBeta00Z05;
   TBranch        *b_productSigSDBeta00Z05;
   TBranch        *b_dr12SigSDBeta00Z05;
   TBranch        *b_zgSigSDBeta00Z03;   //!
   TBranch        *b_eradSigSDBeta00Z03;
   TBranch        *b_productSigSDBeta00Z03;
   TBranch        *b_dr12SigSDBeta00Z03;
   TBranch        *b_eventWeight;   //!
   TBranch        *b_partonsPt;   //!
   TBranch        *b_partonsEta;   //!
   TBranch        *b_partonsPhi;   //!
   TBranch        *b_partonsM;   //!
   TBranch        *b_partonsPDG;   //!
   TBranch        *b_partonsFirstSplitPt;   //!
   TBranch        *b_partonsFirstSplitEta;   //!
   TBranch        *b_partonsFirstSplitPhi;   //!
   TBranch        *b_partonsFirstSplitM;   //!
   TBranch        *b_partonsFirstSplitPDG;   //!
   TBranch        *b_drSplit;   //!
   TBranch        *b_tfSplit;   //!
   TBranch        *b_sigJetPt;   //!
   TBranch        *b_sigJetEta;   //!
   TBranch        *b_sigJetE;   //!
   TBranch        *b_sigJetPhi;   //!
   TBranch        *b_sigJetM;   //!
   TBranch        *b_sigJetArea;   //!

   TBranch        *b_sigjetRecurZcut1_dr12;   //!
   TBranch        *b_sigjetRecurZcut1_erad;   //!
   TBranch        *b_sigjetRecurZcut1_mpt;   //!
   TBranch        *b_sigjetRecurZcut1_product;   //!
   TBranch        *b_sigjetRecurZcut1_jetpt;   //!
   TBranch        *b_sigjetRecurZcut1_logdr12;   //!
   TBranch        *b_sigjetRecurZcut1_logztheta;   //!
   TBranch        *b_sigjetRecurZcut1_z;   //!
   TBranch        *b_sigjetRecurZcut2_dr12;   //!
   TBranch        *b_sigjetRecurZcut2_erad;   //!
   TBranch        *b_sigjetRecurZcut2_mpt;   //!
   TBranch        *b_sigjetRecurZcut2_product;   //!
   TBranch        *b_sigjetRecurZcut2_jetpt;   //!
   TBranch        *b_sigjetRecurZcut2_logdr12;   //!
   TBranch        *b_sigjetRecurZcut2_logztheta;   //!
   TBranch        *b_sigjetRecurZcut2_z;   //!
   TBranch        *b_sigjetRecur_dr12;   //!
   TBranch        *b_sigjetRecur_erad;   //!
   TBranch        *b_sigjetRecur_mpt;   //!
   TBranch        *b_sigjetRecur_product;   //!
   TBranch        *b_sigjetRecur_jetpt;   //!
   TBranch        *b_sigjetRecur_logdr12;   //!
   TBranch        *b_sigjetRecur_logztheta;   //!
   TBranch        *b_sigjetRecur_z;   //!



   jetTreeSig2(TTree *tree=0);
   virtual ~jetTreeSig2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
  // virtual TTree*   CopyTree(const char* selection);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef jetTreeSig2_cxx
jetTreeSig2::jetTreeSig2(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Volumes/D2/users/rosa/JetToyHI/JetToyHIResultSimpleJetAnalysis.root");
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("JetToyHIResultTimeClusJewel_simple.root");
      if (!f || !f->IsOpen()) {
     //   std::cout<<"problemo"<<std::endl;
         f = new TFile("../JetToyHIResultSimpleJetAnalysis.root");
         //f = new TFile("JetToyHIResultTimeClusJewel_simple.root");// JetToyHIResultTimeClusJewel_vac.root
      }
      f->GetObject("jetTree",tree);

   }
   Init(tree);
}

jetTreeSig2::~jetTreeSig2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t jetTreeSig2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t jetTreeSig2::LoadTree(Long64_t entry)
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

void jetTreeSig2::Init(TTree *tree)
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
   /*
   partonsPt = 0;
   partonsEta = 0;
   partonsPhi = 0;
   partonsM = 0;
   partonsPDG = 0;
   partonsFirstSplitPt = 0;
   partonsFirstSplitEta = 0;
   partonsFirstSplitPhi = 0;
   partonsFirstSplitM = 0;
   partonsFirstSplitPDG = 0;
   drSplit = 0;
   tfSplit = 0;
   */
   sigJetPt = 0;
   sigJetEta = 0;
   sigJetE = 0;
   sigJetPhi = 0;
   sigJetM = 0;
   sigJetArea = 0;
   // hadron pairs
   zg_hadron_pairs = 0;
   dr_hadron_pairs = 0;
   E2C_hadron_pairs = 0;
   /*
   E2C_hadron_pairs_zcut2 = 0;
   E2C_hadron_pairs_zcut3 = 0;
   E2C_hadron_pairs_zcut4 = 0;
   E2C_hadron_pairs_zcut5 = 0;
   dr_hadron_pairs_zcut2 = 0;
   dr_hadron_pairs_zcut3 = 0;
   dr_hadron_pairs_zcut4 = 0;
   dr_hadron_pairs_zcut5 = 0;
   */
   


   // Reclustering effects
   sigJetSDBeta00Z01Pt = 0;
   sigJetSDBeta00Z05Pt = 0;
   sigJetSDBeta00Z03Pt = 0;
   zgSigSDBeta00Z01 = 0;
   eradSigSDBeta00Z01 = 0;
   productSigSDBeta00Z01 = 0;
   dr12SigSDBeta00Z01 = 0;
   zgSigSDBeta00Z05 = 0;
   eradSigSDBeta00Z05 = 0;
   productSigSDBeta00Z05 = 0;
   dr12SigSDBeta00Z05 = 0;
   zgSigSDBeta00Z03 = 0;
   eradSigSDBeta00Z03 = 0;
   productSigSDBeta00Z03 = 0;
   dr12SigSDBeta00Z03 = 0;
   //SoftDropCounter
   sigjetRecurZcut1_dr12 = 0;
   sigjetRecurZcut1_erad = 0;
   sigjetRecurZcut1_mpt = 0;
   sigjetRecurZcut1_product = 0;
   sigjetRecurZcut1_jetpt = 0;
   sigjetRecurZcut1_logdr12 = 0;
   sigjetRecurZcut1_logztheta = 0;
   sigjetRecurZcut1_z = 0;
   sigjetRecurZcut2_dr12 = 0;
   sigjetRecurZcut2_erad = 0;
   sigjetRecurZcut2_mpt = 0;
   sigjetRecurZcut2_product = 0;
   sigjetRecurZcut2_jetpt = 0;
   sigjetRecurZcut2_logdr12 = 0;
   sigjetRecurZcut2_logztheta = 0;
   sigjetRecurZcut2_z = 0;
   sigjetRecur_dr12 = 0;
   sigjetRecur_erad = 0;
   sigjetRecur_mpt = 0;
   sigjetRecur_product = 0;
   sigjetRecur_jetpt = 0;
   sigjetRecur_logdr12 = 0;
   sigjetRecur_logztheta = 0;
   sigjetRecur_z = 0;

   // Set branch addresses and branch pointers
   if (!tree){
    std::cout<<"P2"<<std::endl;
    return;
   }
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight);
   // True parton info
   /*fChain->SetBranchAddress("partonsPt", &partonsPt, &b_partonsPt);
   fChain->SetBranchAddress("partonsEta", &partonsEta, &b_partonsEta);
   fChain->SetBranchAddress("partonsPhi", &partonsPhi, &b_partonsPhi);
   fChain->SetBranchAddress("partonsM", &partonsM, &b_partonsM);
   fChain->SetBranchAddress("partonsPDG", &partonsPDG, &b_partonsPDG);
   fChain->SetBranchAddress("partonsFirstSplitPt", &partonsFirstSplitPt, &b_partonsFirstSplitPt);
   fChain->SetBranchAddress("partonsFirstSplitEta", &partonsFirstSplitEta, &b_partonsFirstSplitEta);
   fChain->SetBranchAddress("partonsFirstSplitPhi", &partonsFirstSplitPhi, &b_partonsFirstSplitPhi);
   fChain->SetBranchAddress("partonsFirstSplitM", &partonsFirstSplitM, &b_partonsFirstSplitM);
   fChain->SetBranchAddress("partonsFirstSplitPDG", &partonsFirstSplitPDG, &b_partonsFirstSplitPDG);
   fChain->SetBranchAddress("drSplit", &drSplit, &b_drSplit);
   fChain->SetBranchAddress("tfSplit", &tfSplit, &b_tfSplit);
   */
   // True jet info (anti-kt clustering)
   fChain->SetBranchAddress("sigJetPt", &sigJetPt, &b_sigJetPt);
   fChain->SetBranchAddress("sigJetEta", &sigJetEta, &b_sigJetEta);
   fChain->SetBranchAddress("sigJetE", &sigJetE, &b_sigJetE);
   fChain->SetBranchAddress("sigJetPhi", &sigJetPhi, &b_sigJetPhi);
   fChain->SetBranchAddress("sigJetM", &sigJetM, &b_sigJetM);
   fChain->SetBranchAddress("sigJetArea", &sigJetArea, &b_sigJetArea);

   //for hadron pairs
   fChain->SetBranchAddress("E2C_hadron_pairs", &E2C_hadron_pairs, &b_E2C_hadron_pairs);
   fChain->SetBranchAddress("dr_hadron_pairs", &dr_hadron_pairs, &b_dr_hadron_pairs);
   fChain->SetBranchAddress("zg_hadron_pairs", &zg_hadron_pairs, &b_zg_hadron_pairs);
   /*
   fChain->SetBranchAddress("E2C_hadron_pairs_zcut2", &E2C_hadron_pairs_zcut2, &b_E2C_hadron_pairs_zcut2);
   fChain->SetBranchAddress("E2C_hadron_pairs_zcut3", &E2C_hadron_pairs_zcut3, &b_E2C_hadron_pairs_zcut3);
   fChain->SetBranchAddress("E2C_hadron_pairs_zcut4", &E2C_hadron_pairs_zcut4, &b_E2C_hadron_pairs_zcut4);
   fChain->SetBranchAddress("E2C_hadron_pairs_zcut5", &E2C_hadron_pairs_zcut5, &b_E2C_hadron_pairs_zcut5);
   fChain->SetBranchAddress("dr_hadron_pairs_zcut2", &dr_hadron_pairs_zcut2, &b_dr_hadron_pairs_zcut2);
   fChain->SetBranchAddress("dr_hadron_pairs_zcut3", &dr_hadron_pairs_zcut3, &b_dr_hadron_pairs_zcut3);
   fChain->SetBranchAddress("dr_hadron_pairs_zcut4", &dr_hadron_pairs_zcut4, &b_dr_hadron_pairs_zcut4);
   fChain->SetBranchAddress("dr_hadron_pairs_zcut5", &dr_hadron_pairs_zcut5, &b_dr_hadron_pairs_zcut5);
   */
   

   // from here on you need to add your vectors/addresses
   fChain->SetBranchAddress("sigJetSDBeta00Z01Pt", &sigJetSDBeta00Z01Pt, &b_sigJetSDBeta00Z01Pt);
   fChain->SetBranchAddress("sigJetSDBeta00Z05Pt", &sigJetSDBeta00Z05Pt, &b_sigJetSDBeta00Z05Pt);
   fChain->SetBranchAddress("sigJetSDBeta00Z03Pt", &sigJetSDBeta00Z03Pt, &b_sigJetSDBeta00Z03Pt);
   fChain->SetBranchAddress("zgSigSDBeta00Z01", &zgSigSDBeta00Z01, &b_zgSigSDBeta00Z01);
   fChain->SetBranchAddress("eradSigSDBeta00Z01", &eradSigSDBeta00Z01, &b_eradSigSDBeta00Z01);
   fChain->SetBranchAddress("productSigSDBeta00Z01", &productSigSDBeta00Z01, &b_productSigSDBeta00Z01);
   fChain->SetBranchAddress("dr12SigSDBeta00Z01", &dr12SigSDBeta00Z01, &b_dr12SigSDBeta00Z01);
   fChain->SetBranchAddress("zgSigSDBeta00Z05", &zgSigSDBeta00Z05, &b_zgSigSDBeta00Z05);
   fChain->SetBranchAddress("eradSigSDBeta00Z05", &eradSigSDBeta00Z05, &b_eradSigSDBeta00Z05);
   fChain->SetBranchAddress("productSigSDBeta00Z05", &productSigSDBeta00Z05, &b_productSigSDBeta00Z05);
   fChain->SetBranchAddress("dr12SigSDBeta00Z05", &dr12SigSDBeta00Z05, &b_dr12SigSDBeta00Z05);
   fChain->SetBranchAddress("zgSigSDBeta00Z03", &zgSigSDBeta00Z03, &b_zgSigSDBeta00Z03);
   fChain->SetBranchAddress("eradSigSDBeta00Z03", &eradSigSDBeta00Z03, &b_eradSigSDBeta00Z03);
   fChain->SetBranchAddress("productSigSDBeta00Z03", &productSigSDBeta00Z03, &b_productSigSDBeta00Z03);
   fChain->SetBranchAddress("dr12SigSDBeta00Z03", &dr12SigSDBeta00Z03, &b_dr12SigSDBeta00Z03);

   fChain->SetBranchAddress("sigjetRecurZcut1_dr12", &sigjetRecurZcut1_dr12, &b_sigjetRecurZcut1_dr12);
   fChain->SetBranchAddress("sigjetRecurZcut1_erad", &sigjetRecurZcut1_erad, &b_sigjetRecurZcut1_erad);
   fChain->SetBranchAddress("sigjetRecurZcut1_mpt", &sigjetRecurZcut1_mpt, &b_sigjetRecurZcut1_mpt);
   fChain->SetBranchAddress("sigjetRecurZcut1_product", &sigjetRecurZcut1_product, &b_sigjetRecurZcut1_product);
   fChain->SetBranchAddress("sigjetRecurZcut1_jetpt", &sigjetRecurZcut1_jetpt, &b_sigjetRecurZcut1_jetpt);
   fChain->SetBranchAddress("sigjetRecurZcut1_logdr12", &sigjetRecurZcut1_logdr12, &b_sigjetRecurZcut1_logdr12);
   fChain->SetBranchAddress("sigjetRecurZcut1_logztheta", &sigjetRecurZcut1_logztheta, &b_sigjetRecurZcut1_logztheta);
   fChain->SetBranchAddress("sigjetRecurZcut1_z", &sigjetRecurZcut1_z, &b_sigjetRecurZcut1_z);
   fChain->SetBranchAddress("sigjetRecurZcut2_dr12", &sigjetRecurZcut2_dr12, &b_sigjetRecurZcut2_dr12);
   fChain->SetBranchAddress("sigjetRecurZcut2_erad", &sigjetRecurZcut2_erad, &b_sigjetRecurZcut2_erad);
   fChain->SetBranchAddress("sigjetRecurZcut2_mpt", &sigjetRecurZcut2_mpt, &b_sigjetRecurZcut2_mpt);
   fChain->SetBranchAddress("sigjetRecurZcut2_product", &sigjetRecurZcut2_product, &b_sigjetRecurZcut2_product);
   fChain->SetBranchAddress("sigjetRecurZcut2_jetpt", &sigjetRecurZcut2_jetpt, &b_sigjetRecurZcut2_jetpt);
   fChain->SetBranchAddress("sigjetRecurZcut2_logdr12", &sigjetRecurZcut2_logdr12, &b_sigjetRecurZcut2_logdr12);
   fChain->SetBranchAddress("sigjetRecurZcut2_logztheta", &sigjetRecurZcut2_logztheta, &b_sigjetRecurZcut2_logztheta);
   fChain->SetBranchAddress("sigjetRecurZcut2_z", &sigjetRecurZcut2_z, &b_sigjetRecurZcut2_z);
   fChain->SetBranchAddress("sigjetRecur_dr12", &sigjetRecur_dr12, &b_sigjetRecur_dr12);
   fChain->SetBranchAddress("sigjetRecur_erad", &sigjetRecur_erad, &b_sigjetRecur_erad);
   fChain->SetBranchAddress("sigjetRecur_mpt", &sigjetRecur_mpt, &b_sigjetRecur_mpt);
   fChain->SetBranchAddress("sigjetRecur_product", &sigjetRecur_product, &b_sigjetRecur_product);
   fChain->SetBranchAddress("sigjetRecur_jetpt", &sigjetRecur_jetpt, &b_sigjetRecur_jetpt);
   fChain->SetBranchAddress("sigjetRecur_logdr12", &sigjetRecur_logdr12, &b_sigjetRecur_logdr12);
   fChain->SetBranchAddress("sigjetRecur_logztheta", &sigjetRecur_logztheta, &b_sigjetRecur_logztheta);
   fChain->SetBranchAddress("sigjetRecur_z", &sigjetRecur_z, &b_sigjetRecur_z);

   Notify();
}

Bool_t jetTreeSig2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void jetTreeSig2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t jetTreeSig2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef jetTreeSig2_cxx