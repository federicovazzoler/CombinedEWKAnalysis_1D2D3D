//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar  6 10:36:52 2015 by ROOT version 5.34/18
// from TTree limit/limit
// found on file: higgsCombineTest.MultiDimFit.mH120.root
//////////////////////////////////////////////////////////

#ifndef limit_h
#define limit_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class limit {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        limit;
   Double_t        limitErr;
   Double_t        mh;
   Int_t           syst;
   Int_t           iToy;
   Int_t           iSeed;
   Int_t           iChannel;
   Float_t         t_cpu;
   Float_t         t_real;
   Float_t         quantileExpected;
   Float_t         par1;
   Float_t         par2;
   Float_t         par3;
   Float_t         deltaNLL;

   // List of branches
   TBranch        *b_limit;   //!
   TBranch        *b_limitErr;   //!
   TBranch        *b_mh;   //!
   TBranch        *b_syst;   //!
   TBranch        *b_iToy;   //!
   TBranch        *b_iSeed;   //!
   TBranch        *b_iChannel;   //!
   TBranch        *b_t_cpu;   //!
   TBranch        *b_t_real;   //!
   TBranch        *b_quantileExpected;   //!
   TBranch        *b_par1;   //!
   TBranch        *b_par2;   //!
   TBranch        *b_par3;   //!
   TBranch        *b_deltaNLL;   //!

   limit(TTree *tree=0);
   virtual ~limit();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef limit_cxx
limit::limit(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("higgsCombineTest.MultiDimFit.mH120.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("higgsCombineTest.MultiDimFit.mH120.root");
      }
      f->GetObject("limit",tree);

   }
   Init(tree);
}

limit::~limit()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t limit::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t limit::LoadTree(Long64_t entry)
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

void limit::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("limit", &limit, &b_limit);
   fChain->SetBranchAddress("limitErr", &limitErr, &b_limitErr);
   fChain->SetBranchAddress("mh", &mh, &b_mh);
   fChain->SetBranchAddress("syst", &syst, &b_syst);
   fChain->SetBranchAddress("iToy", &iToy, &b_iToy);
   fChain->SetBranchAddress("iSeed", &iSeed, &b_iSeed);
   fChain->SetBranchAddress("iChannel", &iChannel, &b_iChannel);
   fChain->SetBranchAddress("t_cpu", &t_cpu, &b_t_cpu);
   fChain->SetBranchAddress("t_real", &t_real, &b_t_real);
   fChain->SetBranchAddress("quantileExpected", &quantileExpected, &b_quantileExpected);
   fChain->SetBranchAddress("par1", &par1, &b_par1);
   fChain->SetBranchAddress("par2", &par2, &b_par2);
   fChain->SetBranchAddress("par3", &par3, &b_par3);
   fChain->SetBranchAddress("deltaNLL", &deltaNLL, &b_deltaNLL);
   Notify();
}

Bool_t limit::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void limit::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t limit::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef limit_cxx
