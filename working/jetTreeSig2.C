#define jetTreeSig2_cxx
#include "jetTreeSig2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <cmath>
#include <vector>

void Hadronloop(TH1* histogram, const std::vector<double>* E2C_hadron_pairs, 
                          const std::vector<double>* dr_hadron_pairs, 
                          const std::vector<double>& ptAverages, int ptBin, 
                          double total_n_Jets) {
    
    double binWidth1 = histogram->GetBinWidth(1); // Width of the first bin for scaling

    // Loop over pairs in E2C and dr vectors
    for (int p = 0; p < E2C_hadron_pairs->size(); ++p) {
        double sig_E2C_pairs = E2C_hadron_pairs->at(p);
        double sig_dr_pairs = dr_hadron_pairs->at(p);
        double scaled_sig_dr_pairs = sig_dr_pairs * ptAverages[ptBin];

        // Fill histogram with scaled values
        histogram->Fill(scaled_sig_dr_pairs, sig_E2C_pairs / (binWidth1 * total_n_Jets));
    }
}

void Scalex_axishistogram(TH1D* originalHist, TH1D* scaledHist, double scaleFactor) {
    for (int bin = 1; bin <= originalHist->GetNbinsX(); ++bin) {

        double content = originalHist->GetBinContent(bin);
        double error = originalHist->GetBinError(bin);

        double originalBinCenter = originalHist->GetBinCenter(bin);
        int scaledBin = scaledHist->FindBin(originalBinCenter * scaleFactor);

        scaledHist->SetBinContent(scaledBin, content);
        scaledHist->SetBinError(scaledBin, error);
    }
}

std::vector<double> ScaleBinEdges(const std::vector<double>& binEdges, double scaleFactor) {
    std::vector<double> scaledBinEdges;
    scaledBinEdges.reserve(binEdges.size());
    for (double edge : binEdges) {
        scaledBinEdges.push_back(edge * scaleFactor);
    }
    return scaledBinEdges;
}

   void RatioHistogram(TH1D* hist1, TH1D* hist2, TH1D* hist_ratio) {

    int nBins = hist1->GetNbinsX();
    for (int i = 1; i <= nBins; ++i) { 
        double y1 = hist1->GetBinContent(i); 
        double y2 = hist2->GetBinContent(i); 
        double e1 = hist1->GetBinError(i);   
        double e2 = hist2->GetBinError(i);   

        if (y2 != 0) { // Avoid division by zero
            double ratio = y1 / y2; 
            double ratioError = ratio * sqrt((e1 / y1) * (e1 / y1) + (e2 / y2) * (e2 / y2)); 
            hist_ratio->SetBinContent(i, ratio); 
            hist_ratio->SetBinError(i, ratioError); 
        } else {
            hist_ratio->SetBinContent(i, 0);
            hist_ratio->SetBinError(i, 0);   
        }
    }
}





void jetTreeSig2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L jetTreeSig2.C
//      root> jetTreeSig2 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//    Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
//fChain->SetBranchStatus("*",0);
//fChain->SetBranchStatus("b_partonsPt",1);  // activate branchname
//fChain->SetBranchStatus("b_zgSigSDBeta00Z01",1);  // activate branchname
   std::cout<<"before chian"<<std::endl;
   
   if (fChain == 0) return;

   //Long64_t nentries = fChain->GetEntries();
   int nentries = fChain->GetEntriesFast();
   std::cout << "nentries: " << nentries << std::endl;
   /*
   //Define 1D histograms for grooming
   TH1F *h1JPtW = new TH1F("h1JPtW","h1JPtW",40,0.,400.);// with weight
   TH1F *h1JPt = new TH1F("h1JPt","h1JPt",40,0.,400.);//no weight

   TH1F *h1PtSigSD01 = new TH1F("h1PtSigSD01","h1PtSigSD01",50,0.,400.);
   TH1F *h1zgSigSD01 = new TH1F("h1zgSigSD01","h1zgSigSD01",50,0.,1.);
   TH1F *h1eradSigSD01 = new TH1F("h1eradSigSD01","h1eradSigSD01",50,0.,500.);
   TH1F *h1E2CSigSD01 = new TH1F("h1E2CSigSD01","h1E2CSigSD01",50,0.,1.);
   TH1F *h1dr12SigSD01 = new TH1F("h1dr12SigSD01","h1dr12SigSD01",50,0.,1.);
   TH1F *h1PtSigSD05 = new TH1F("h1PtSigSD05","h1PtSigSD05",50,0.,400.);
   TH1F *h1zgSigSD05 = new TH1F("h1zgSigSD05","h1zgSigSD05",50,0.,1.);
   TH1F *h1eradSigSD05 = new TH1F("h1eradSigSD05","h1eradSigSD05",50,0.,500.);
   TH1F *h1E2CSigSD05 = new TH1F("h1E2CSigSD05","h1E2CSigSD05",50,0.,1.);
   TH1F *h1dr12SigSD05 = new TH1F("h1dr12SigSD05","h1dr12SigSD05",50,0.,1.);
   TH1F *h1PtSigSD03 = new TH1F("h1PtSigSD03","h1PtSigSD03",50,0.,400.);
   TH1F *h1zgSigSD03 = new TH1F("h1zgSigSD03","h1zgSigSD03",50,0.,1.);
   TH1F *h1eradSigSD03 = new TH1F("h1eradSigSD03","h1eradSigSD03",50,0.,500.);
   TH1F *h1E2CSigSD03 = new TH1F("h1E2CSigSD03","h1E2CSigSD03",50,0.,1.);
   TH1F *h1dr12SigSD03 = new TH1F("h1dr12SigSD03","h1dr12SigSD03",50,0.,1.);

    // Define the 2D histograms for E2C vs dr12
   TH2F *h2E2C_vs_dr12_SD01 = new TH2F("h2E2C_vs_dr12_SD01", "E2C vs dr12 (SD01); E2C; dr12", 50, 0., 0.5, 50, 0., 1.);
   TH2F *h2E2C_vs_dr12_SD05 = new TH2F("h2E2C_vs_dr12_SD05", "E2C vs dr12 (SD05); E2C; dr12", 50, 0., 0.5, 50, 0., 1.);
   TH2F *h2E2C_vs_dr12_SD03 = new TH2F("h2E2C_vs_dr12_SD03", "E2C vs dr12 (SD03); E2C; dr12", 50, 0., 0.5, 50, 0., 1.);
   */
//---------------------------------------------
   //Define histograms 
//---------------------------------------------
   // smaller bin sizes for low dr12 values
  std::vector<double> binEdges;
   for (double binEdge = 0.0; binEdge < 0.07; binEdge += 0.003) { // Up to but not including 0.04
    binEdges.push_back(binEdge);
   }
   for (double binEdge = 0.07; binEdge <= 1; binEdge += 0.005) { // Start from 0.04
    binEdges.push_back(binEdge);
   }

   std::vector<double> binEdgesh;
   for (double binEdge = 0.0; binEdge < 0.07; binEdge += 0.003) { // Up to but not including 0.035
    binEdgesh.push_back(binEdge);
   }
   for (double binEdge = 0.07; binEdge <= 1; binEdge += 0.005) { // Start from 0.035
    binEdgesh.push_back(binEdge);
   }


   // 1D Histograms counter
   TH1D *hSplitDr12 = new TH1D("hSplitDr12", "dr12 for splits", 100, 0, 1);
   TH1D *hSplitErad = new TH1D("hSplitErad", "Erad for splits", 100, 0, 100);
   TH1D *hSplitProduct = new TH1D("hSplitProduct", "Product for splits", 100, 0, 100);
   TH1D *hSplitJetPt = new TH1D("hSplitJetPt", "Jet Pt for splits", 100, 0, 500);
   TH1D *hSplitLogDr12 = new TH1D("hSplitLogDr12", "Log(dr12) for splits", 100, 0, 6);
   TH1D *hSplitLogZTheta = new TH1D("hSplitLogZTheta", "Log(z * theta) for splits", 100, -6, 1);
   TH1D *hSplitZ = new TH1D("hSplitZ", "z for splits", 100, 0, 1);

   TH1D *hSplitZcut1Dr12 = new TH1D("hSplitZcut1Dr12", "dr12 for splits with Zcut", 100, 0, 1);
   TH1D *hSplitZcut1Erad = new TH1D("hSplitZcut1Erad", "Erad for splits with Zcut", 100, 0, 100);
   TH1D *hSplitZcut1Product = new TH1D("hSplitZcut1Product", "Product for splits with Zcut", 100, 0, 100);
   TH1D *hSplitZcut1JetPt = new TH1D("hSplitZcut1JetPt", "Jet Pt for splits with Zcut", 100, 0, 500);
   TH1D *hSplitZcut1LogDr12 = new TH1D("hSplitZcut1LogDr12", "Log(dr12) for splits with Zcut", 100, 0, 6);
   TH1D *hSplitZcut1LogZTheta = new TH1D("hSplit1ZcutLogZTheta", "Log(z * theta) for splits with Zcut", 100, -6, 1);
   TH1D *hSplitZcut1Z = new TH1D("hSplit1ZcutZ", "z for splits", 100, 0, 1);
   
   // 2D Histograms for counter E2C vs dr12 
   TH2D *hSplitZcut1E2C_vs_dr12 = new TH2D("hSplitZcut1E2C_vs_dr12", "E2C vs dr12 (Zcut1); dr12; E2C", 200, 0., 0.5, 100, 0., 1.); //defenition 1 of E2C
   TH2D *hSplitZcut2E2C_vs_dr12 = new TH2D("hSplitZcut2E2C_vs_dr12", "E2C vs dr12 (Zcut2); dr12; E2C", 200, 0., 0.5, 100, 0., 1.);
   TH2D *hSplitE2C_vs_dr12= new TH2D("hSplitE2C_vs_dr12", "E2C vs dr12 (No zcut); dr12; E2C", 200, 0., 0.5, 100, 0., 1.);

   // 2D Histograms for counter log(zdr) vs log(1/dr)
   TH2D *hSplitZcut1logzdr_vs_1dr12 = new TH2D("Lund plane with applied Zcut1", "Lund plane with applied Zcut1; Log(1/dR); Log(z*dR)", 100, 0., 10., 100, -10., 0.);
   TH2D *hSplitZcut2logzdr_vs_1dr12 = new TH2D("Lund plane with applied Zcut2", "Lund plane with applied Zcut2; Log(1/dR); Log(z*dR)", 100, 0., 10., 100, -10., 0.);
   TH2D *hSplitlogzdr_vs_1dr12= new TH2D("Lund plane without Zcut", "Lund plane without Zcut; Log(1/dR); Log(z*dR)",  100, 0., 10., 100, -10., 0.);

   // 1D Histograms for counter nomalised EEC vs dr12 and also for normalised and scaled
   //with Zcut
   TH1D *hSplitZcut1E2C_sum_vs_dr12pi1 = new TH1D("hSplitZcut1E2C_sum_vs_dr12pi1", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut1E2C_sum_vs_dr12pi2 = new TH1D("hSplitZcut1E2C_sum_vs_dr12pi2", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut1E2C_sum_vs_dr12pi3 = new TH1D("hSplitZcut1E2C_sum_vs_dr12pi3", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut1E2C_sum_vs_dr12pi4 = new TH1D("hSplitZcut1E2C_sum_vs_dr12pi4", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut1E2C_sum_vs_dr12def2pi1 = new TH1D("hSplitZcut1E2C_sum_vs_dr12def2pi1", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut1E2C_sum_vs_dr12def2pi2 = new TH1D("hSplitZcut1E2C_sum_vs_dr12def2pi2", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut1E2C_sum_vs_dr12def2pi3 = new TH1D("hSplitZcut1E2C_sum_vs_dr12def2pi3", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut1E2C_sum_vs_dr12def2pi4 = new TH1D("hSplitZcut1E2C_sum_vs_dr12def2pi4", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);

   TH1D *hSplitZcut2E2C_sum_vs_dr12pi1 = new TH1D("hSplitZcut2E2C_sum_vs_dr12pi1", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut2E2C_sum_vs_dr12pi2 = new TH1D("hSplitZcut2E2C_sum_vs_dr12pi2", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut2E2C_sum_vs_dr12pi3 = new TH1D("hSplitZcut2E2C_sum_vs_dr12pi3", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut2E2C_sum_vs_dr12pi4 = new TH1D("hSplitZcut2E2C_sum_vs_dr12pi4", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut2E2C_sum_vs_dr12def2pi1 = new TH1D("hSplitZcut2E2C_sum_vs_dr12def2pi1", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut2E2C_sum_vs_dr12def2pi2 = new TH1D("hSplitZcut2E2C_sum_vs_dr12def2pi2", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut2E2C_sum_vs_dr12def2pi3 = new TH1D("hSplitZcut2E2C_sum_vs_dr12def2pi3", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitZcut2E2C_sum_vs_dr12def2pi4 = new TH1D("hSplitZcut2E2C_sum_vs_dr12def2pi4", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);

   //without Zcut
   TH1D *hSplitE2C_sum_vs_dr12pi1 = new TH1D("hSplitE2C_sum_vs_dr12pi1", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitE2C_sum_vs_dr12pi2 = new TH1D("hSplitE2C_sum_vs_dr12pi2", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitE2C_sum_vs_dr12pi3 = new TH1D("hSplitE2C_sum_vs_dr12pi3", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitE2C_sum_vs_dr12pi4 = new TH1D("hSplitE2C_sum_vs_dr12pi4", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitE2C_sum_vs_dr12def2pi1 = new TH1D("hSplitE2C_sum_vs_dr12def2pi1", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitE2C_sum_vs_dr12def2pi2 = new TH1D("hSplitE2C_sum_vs_dr12def2pi2", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitE2C_sum_vs_dr12def2pi3 = new TH1D("hSplitE2C_sum_vs_dr12def2pi3", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);
   TH1D *hSplitE2C_sum_vs_dr12def2pi4 = new TH1D("hSplitE2C_sum_vs_dr12def2pi4", "Summed E2C per dr12; dr12; Summed E2C", binEdges.size() - 1, &binEdges[0]);

 //Ratios for EEC's for zcuts
   TH1D *ratio_EEC_zcut01_pi1 = new TH1D("ratio_EEC_zcut01_pi1", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);
   TH1D *ratio_EEC_zcut01_pi2 = new TH1D("ratio_EEC_zcut01_pi2", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);
   TH1D *ratio_EEC_zcut01_pi3 = new TH1D("ratio_EEC_zcut01_pi3", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);
   TH1D *ratio_EEC_zcut01_pi4 = new TH1D("ratio_EEC_zcut01_pi4", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);

   TH1D *ratio_EEC_zcut02_pi1 = new TH1D("ratio_EEC_zcut02_pi1", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);
   TH1D *ratio_EEC_zcut02_pi2 = new TH1D("ratio_EEC_zcut02_pi2", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);
   TH1D *ratio_EEC_zcut02_pi3 = new TH1D("ratio_EEC_zcut02_pi3", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);
   TH1D *ratio_EEC_zcut02_pi4 = new TH1D("ratio_EEC_zcut02_pi4", "ratio between EEC's of zcut and no zcut; dr12; ratio", binEdges.size() - 1, &binEdges[0]);

   // Histograms for hadron pairs
   TH2D *hE2C_hadron_pairs = new TH2D("hE2C_hadron_pairs0p5", "EC2 vs dr12 (hadron pairs); dr12; E2C", 200, 0., 0.8, 100, 0., 1.);
   
   TH1D *hE2C_sum_vs_dr12_zcut1_pi1 = new TH1D("hE2C_sum_vs_dr12_pi1", "Summed E2C per dr12; dr12; Summed E2C", binEdgesh.size() - 1, &binEdgesh[0]);
   TH1D *hE2C_sum_vs_dr12_zcut1_pi2 = new TH1D("hE2C_sum_vs_dr12_pi2", "Summed E2C per dr12; dr12; Summed E2C", binEdgesh.size() - 1, &binEdgesh[0]);
   TH1D *hE2C_sum_vs_dr12_zcut1_pi3 = new TH1D("hE2C_sum_vs_dr12_pi3", "Summed E2C per dr12; dr12; Summed E2C", binEdgesh.size() - 1, &binEdgesh[0]);
   TH1D *hE2C_sum_vs_dr12_zcut1_pi4 = new TH1D("hE2C_sum_vs_dr12_pi4", "Summed E2C per dr12; dr12; Summed E2C", binEdgesh.size() - 1, &binEdgesh[0]);
   
   /*
   TH1D *hE2C_sum_vs_dr12_scaled_zcut2 = new TH1D("hE2C_sum_vs_dr12_scaled2", "Scaled E2C per dr12; dr12; Summed E2C", 200, 0., 400.);
   TH1D *hE2C_sum_vs_dr12_scaled_zcut3 = new TH1D("hE2C_sum_vs_dr12_scaled3", "Scaled E2C per dr12; dr12; Summed E2C", 200, 0., 400.);
   TH1D *hE2C_sum_vs_dr12_scaled_zcut4 = new TH1D("hE2C_sum_vs_dr12_scaled4", "Scaled E2C per dr12; dr12; Summed E2C", 200, 0., 400.);
   TH1D *hE2C_sum_vs_dr12_scaled_zcut5 = new TH1D("hE2C_sum_vs_dr12_scaled5", "Scaled E2C per dr12; dr12; Summed E2C", 200, 0., 400.);
   */


   //Histogram for jets
   TH1D *Ptjet = new TH1D("Pt jet", "Ptjet",100, 1., 500.);

   Long64_t nbytes = 0, nb = 0;
   std::cout << "before first loop " << std::endl;
   double prev_evWeight = 0;


   //Loops for calculating pt sums and counts
   const int numIntervals = 5; // 10 intervals 
   double ptIntervalWidth = 20.0; // Pt intervals of 30 Gev
   std::vector<double> ptSums(numIntervals, 0.0); // Sum of pt for each interval
   std::vector<int> ptCounts(numIntervals, 0); // Count of jets in each interval
   TH1D *Pt_averages = new TH1D("Pt_averages", "Pt_averages", numIntervals, 40, 40 + numIntervals * ptIntervalWidth);
   //event loop
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //jet loop
      for(int i = 0; i<sigJetPt->size(); ++i) {
         double sigPt = sigJetPt->at(i);
         if(sigPt<40. || abs(sigJetEta->at(i))>2) continue; 
         Ptjet->Fill(sigPt);
         // Calculate sums of pt and pt count for this jet
        int ptBin = static_cast<int>((sigPt-40)/ ptIntervalWidth);
        if (ptBin >= 0 && ptBin < numIntervals) {
            ptSums[ptBin] += sigPt;
            ptCounts[ptBin]++;
        }
      }
   }

   int total_n_Jets = Ptjet->GetEntries(); // calculating total number of jets

      //Calculation average jet pt per pt interval
   std::vector<double> ptAverages(numIntervals, 0.0);
   for (int j = 0; j < numIntervals; ++j) {
      if (ptCounts[j] > 0) {
         ptAverages[j] = ptSums[j] / ptCounts[j]; // Average for each interval
         }
          std::cout << "ptBin " << j << " (" << (40 + j * ptIntervalWidth) << "-"
           << (40 + (j + 1) * ptIntervalWidth) << " GeV): "
           << ptAverages[j] << std::endl;
         }
   

   //Loops for filling histograms
   //event loop
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //if (Cut(ientry) < 0) continue;
      //double evWeight = eventWeight->at(0);
      //std::cout << "jentry: " << jentry << std::endl;
      //std::cout << "ientry: " << ientry << std::endl;
      //std::cout << "event weight in first loop: " << evWeight << std::endl;

      //loop over jets 
      for(int i = 0; i<sigJetPt->size(); ++i) {
        double sigPt = sigJetPt->at(i);
        double sigE = sigJetE->at(i);
        if(sigPt<40. || abs(sigJetEta->at(i))>2) continue;//there Rosa can make her cuts

         // Calculate jet interval index
        int ptBin = static_cast<int>((sigPt - 40) / ptIntervalWidth);
        if (ptBin < 0 || ptBin >= numIntervals) continue; 

         //loop over hadron pairs
         for(int p = 0; p < E2C_hadron_pairs->at(i).size(); ++p) {
            double sig_E2C_pairs = E2C_hadron_pairs->at(i).at(p);
            double sig_dr_pairs = dr_hadron_pairs->at(i).at(p);
            double sig_zg_pairs = zg_hadron_pairs->at(i).at(p);

            hE2C_hadron_pairs->Fill(sig_dr_pairs, sig_E2C_pairs);

            int binIndex = hE2C_sum_vs_dr12_zcut1_pi1->GetXaxis()->FindBin(sig_dr_pairs);
            double binWidth = hE2C_sum_vs_dr12_zcut1_pi1->GetBinWidth(binIndex);
            if (ptBin == 0) {
            hE2C_sum_vs_dr12_zcut1_pi1->Fill(sig_dr_pairs, sig_E2C_pairs / (binWidth * total_n_Jets));
            }
            if (ptBin == 1) {
            hE2C_sum_vs_dr12_zcut1_pi2->Fill(sig_dr_pairs, sig_E2C_pairs / (binWidth * total_n_Jets));
            }
            if (ptBin == 2) {
            hE2C_sum_vs_dr12_zcut1_pi3->Fill(sig_dr_pairs, sig_E2C_pairs / (binWidth * total_n_Jets));
            }
            if (ptBin == 3) {
            hE2C_sum_vs_dr12_zcut1_pi4->Fill(sig_dr_pairs, sig_E2C_pairs / (binWidth * total_n_Jets));
            }
          
         }
         /*
         Hadronloop(hE2C_sum_vs_dr12_scaled_zcut2, E2C_hadron_pairs_zcut2, dr_hadron_pairs_zcut2, ptAverages, ptBin, total_n_Jets);
         Hadronloop(hE2C_sum_vs_dr12_scaled_zcut3, E2C_hadron_pairs_zcut3, dr_hadron_pairs_zcut3, ptAverages, ptBin, total_n_Jets);
         Hadronloop(hE2C_sum_vs_dr12_scaled_zcut4, E2C_hadron_pairs_zcut4, dr_hadron_pairs_zcut4, ptAverages, ptBin, total_n_Jets);
         Hadronloop(hE2C_sum_vs_dr12_scaled_zcut5, E2C_hadron_pairs_zcut5, dr_hadron_pairs_zcut5, ptAverages, ptBin, total_n_Jets);
         */
         


        /*
        double sigJetSDBeta00Z01Pt_val = sigJetSDBeta00Z01Pt->at(i);
        double zgSigSDBeta00Z01_val = zgSigSDBeta00Z01->at(i);
        double eradSigSDBeta00Z01_val = eradSigSDBeta00Z01->at(i);  
        double productSigSDBeta00Z01_val = productSigSDBeta00Z01->at(i);  
        double dr12SigSDBeta00Z01_val = dr12SigSDBeta00Z01->at(i);
        double sigJetSDBeta00Z05Pt_val = sigJetSDBeta00Z05Pt->at(i);
        double zgSigSDBeta00Z05_val = zgSigSDBeta00Z05->at(i);
        double eradSigSDBeta00Z05_val = eradSigSDBeta00Z05->at(i);  
        double productSigSDBeta00Z05_val = productSigSDBeta00Z05->at(i);  
        double dr12SigSDBeta00Z05_val = dr12SigSDBeta00Z05->at(i);
        double sigJetSDBeta00Z03Pt_val = sigJetSDBeta00Z03Pt->at(i);
        double zgSigSDBeta00Z03_val = zgSigSDBeta00Z03->at(i);
        double eradSigSDBeta00Z03_val = eradSigSDBeta00Z03->at(i);  
        double productSigSDBeta00Z03_val = productSigSDBeta00Z03->at(i);  
        double dr12SigSDBeta00Z03_val = dr12SigSDBeta00Z03->at(i);
        //std::cout<<"EC301: "<< productSigSDBeta00Z01_val/sigE <<std::endl; //print values of erad
        //std::cout<< sigE <<std::endl;
        //h1JPtW->Fill(sigPt, evWeight);// add jet norm im plotting - from pt spectrun
        //Fill 1D histograms
        h1JPt->Fill(sigPt);
        h1PtSigSD01->Fill(sigJetSDBeta00Z01Pt_val);
        h1zgSigSD01->Fill(zgSigSDBeta00Z01_val);
        h1eradSigSD01->Fill(eradSigSDBeta00Z01_val);
        if((sigE == 0) || (productSigSDBeta00Z01_val == 0))continue;
        else {h1E2CSigSD01->Fill(productSigSDBeta00Z01_val/pow(sigE, 2));
        }
        
        h1dr12SigSD01->Fill(dr12SigSDBeta00Z01_val);

        h1PtSigSD05->Fill(sigJetSDBeta00Z05Pt_val);
        h1zgSigSD05->Fill(zgSigSDBeta00Z05_val);
        h1eradSigSD05->Fill(eradSigSDBeta00Z05_val);
        if((sigE == 0) || (productSigSDBeta00Z05_val == 0))continue;
        else {h1E2CSigSD05->Fill(productSigSDBeta00Z05_val/pow(sigE, 2));
        }
        h1dr12SigSD05->Fill(dr12SigSDBeta00Z05_val);

        h1PtSigSD03->Fill(sigJetSDBeta00Z03Pt_val);
        h1zgSigSD03->Fill(zgSigSDBeta00Z03_val);
        h1eradSigSD03->Fill(eradSigSDBeta00Z03_val);
        if((sigE == 0) || (productSigSDBeta00Z03_val == 0))continue;
        else {h1E2CSigSD03->Fill(productSigSDBeta00Z03_val/pow(sigE, 2));
        }
        h1dr12SigSD03->Fill(dr12SigSDBeta00Z03_val);
        
        //Fill 2D histograms 
        if((sigE == 0) || (productSigSDBeta00Z01_val == 0))continue;
        else {h2E2C_vs_dr12_SD01->Fill(productSigSDBeta00Z01_val/pow(sigE, 2), dr12SigSDBeta00Z01_val);
        }
        if((sigE == 0) || (productSigSDBeta00Z05_val == 0))continue;
        else {h2E2C_vs_dr12_SD05->Fill(productSigSDBeta00Z05_val/pow(sigE, 2), dr12SigSDBeta00Z05_val);
        }
        if((sigE == 0) || (productSigSDBeta00Z03_val == 0))continue;
        else {h2E2C_vs_dr12_SD03->Fill(productSigSDBeta00Z03_val/pow(sigE, 2), dr12SigSDBeta00Z03_val);
        }
        */

        // Loop over the splits per jet to get substructure information
        for (int j = 0; j < sigjetRecurZcut1_jetpt->at(i).size(); ++j) {

            double split_Zcutdr12 = sigjetRecurZcut1_dr12->at(i).at(j);
            double split_Zcuterad = sigjetRecurZcut1_erad->at(i).at(j);
            double split_Zcutproduct = sigjetRecurZcut1_product->at(i).at(j);
            double split_Zcutjetpt = sigjetRecurZcut1_jetpt->at(i).at(j);
            double split_Zcutlogdr12 = sigjetRecurZcut1_logdr12->at(i).at(j);
            double split_Zcutlogztheta = sigjetRecurZcut1_logztheta->at(i).at(j);
            double split_Zcutz = sigjetRecurZcut1_z->at(i).at(j);
            double split_Zcutmpt = sigjetRecurZcut1_mpt->at(i).at(j);

            // Fill histograms for each split (substructure) inside the current jet
            hSplitZcut1Dr12->Fill(split_Zcutdr12);
            hSplitZcut1Erad->Fill(split_Zcuterad);
            hSplitZcut1Product->Fill(split_Zcutproduct);
            hSplitZcut1JetPt->Fill(split_Zcutjetpt);
            hSplitZcut1LogDr12->Fill(split_Zcutlogdr12);
            hSplitZcut1LogZTheta->Fill(split_Zcutlogztheta);
            hSplitZcut1Z->Fill(split_Zcutz);
            
            // 2D EC2 histograms of def 1 and 2
            hSplitZcut1logzdr_vs_1dr12->Fill(split_Zcutlogdr12, split_Zcutlogztheta);
            if((split_Zcutmpt == 0) || (split_Zcutproduct == 0))continue;
            else {hSplitZcut1E2C_vs_dr12->Fill(split_Zcutdr12, split_Zcutproduct/pow(split_Zcutmpt, 2));
            }
            
            // 1D EC2 histogram def 1 and 2
            int binIndex = hSplitZcut1E2C_sum_vs_dr12pi1->GetXaxis()->FindBin(split_Zcutdr12);
            double binWidth = hSplitZcut1E2C_sum_vs_dr12pi1->GetBinWidth(binIndex);
            if((split_Zcutmpt == 0) || (split_Zcutproduct == 0))continue;
            else{
            if (ptBin == 0) {
            hSplitZcut1E2C_sum_vs_dr12pi1->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut1E2C_sum_vs_dr12def2pi1->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
            }
            if (ptBin == 1) {
            hSplitZcut1E2C_sum_vs_dr12pi2->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut1E2C_sum_vs_dr12def2pi2->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
             }
            if (ptBin == 2) {
            hSplitZcut1E2C_sum_vs_dr12pi3->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut1E2C_sum_vs_dr12def2pi3->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
             }
            if (ptBin == 3) {
            hSplitZcut1E2C_sum_vs_dr12pi4->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut1E2C_sum_vs_dr12def2pi4->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
             }
            }
         }

         
         // Loop over the splits per jet to get substructure information
        for (int k = 0; k < sigjetRecur_jetpt->at(i).size(); ++k) {

            double split_dr12 = sigjetRecur_dr12->at(i).at(k);
            double split_erad = sigjetRecur_erad->at(i).at(k);
            double split_product = sigjetRecur_product->at(i).at(k);
            double split_jetpt = sigjetRecur_jetpt->at(i).at(k);
            double split_logdr12 = sigjetRecur_logdr12->at(i).at(k);
            double split_logztheta = sigjetRecur_logztheta->at(i).at(k);
            double split_z = sigjetRecur_z->at(i).at(k);
            double split_mpt = sigjetRecur_mpt->at(i).at(k);
            

            hSplitDr12->Fill(split_dr12);
            hSplitErad->Fill(split_erad);
            hSplitProduct->Fill(split_product);
            hSplitJetPt->Fill(split_jetpt);
            hSplitLogDr12->Fill(split_logdr12);
            hSplitLogZTheta->Fill(split_logztheta);
            hSplitZ->Fill(split_z);

            //2D E2C histograms
            hSplitlogzdr_vs_1dr12->Fill(split_logdr12, split_logztheta);
            if((split_mpt == 0) || (split_product == 0))continue;
            else {hSplitE2C_vs_dr12->Fill(split_dr12, split_product/pow(split_mpt, 2));
            }
            // 1D EC2 histogram def 1 and 2
            int binIndex = hSplitE2C_sum_vs_dr12pi1->GetXaxis()->FindBin(split_dr12);
            double binWidth = hSplitE2C_sum_vs_dr12pi1->GetBinWidth(binIndex);
            if((split_mpt == 0) || (split_product == 0))continue;
            else{
            if (ptBin == 0) {
            hSplitE2C_sum_vs_dr12pi1->Fill(split_dr12, split_product/(pow(split_mpt, 2)*binWidth*total_n_Jets));
            hSplitE2C_sum_vs_dr12def2pi1->Fill(split_dr12, split_product/(pow(sigPt, 2)*binWidth*total_n_Jets));
            }
            if (ptBin == 1) {
            hSplitE2C_sum_vs_dr12pi2->Fill(split_dr12, split_product/(pow(split_mpt, 2)*binWidth*total_n_Jets));
            hSplitE2C_sum_vs_dr12def2pi2->Fill(split_dr12, split_product/(pow(sigPt, 2)*binWidth*total_n_Jets));
             }
            if (ptBin == 2) {
            hSplitE2C_sum_vs_dr12pi3->Fill(split_dr12, split_product/(pow(split_mpt, 2)*binWidth*total_n_Jets));
            hSplitE2C_sum_vs_dr12def2pi3->Fill(split_dr12, split_product/(pow(sigPt, 2)*binWidth*total_n_Jets));
            }
            if (ptBin == 3) {
            hSplitE2C_sum_vs_dr12pi4->Fill(split_dr12, split_product/(pow(split_mpt, 2)*binWidth*total_n_Jets));
            hSplitE2C_sum_vs_dr12def2pi4->Fill(split_dr12, split_product/(pow(sigPt, 2)*binWidth*total_n_Jets));

             }
            }
            
            }// end substructure loop

         // Loop over the splits per jet to get substructure information
        for (int j = 0; j < sigjetRecurZcut2_jetpt->at(i).size(); ++j) {

            double split_Zcutdr12 = sigjetRecurZcut2_dr12->at(i).at(j);
            double split_Zcutproduct = sigjetRecurZcut2_product->at(i).at(j);
            double split_Zcutjetpt = sigjetRecurZcut2_jetpt->at(i).at(j);
            double split_Zcutlogdr12 = sigjetRecurZcut2_logdr12->at(i).at(j);
            double split_Zcutlogztheta = sigjetRecurZcut2_logztheta->at(i).at(j);
            double split_Zcutz = sigjetRecurZcut2_z->at(i).at(j);
            double split_Zcutmpt = sigjetRecurZcut2_mpt->at(i).at(j);
            
            // 2D histograms
            hSplitZcut2logzdr_vs_1dr12->Fill(split_Zcutlogdr12, split_Zcutlogztheta);
            if((split_Zcutmpt == 0) || (split_Zcutproduct == 0))continue;
            else {hSplitZcut2E2C_vs_dr12->Fill(split_Zcutdr12, split_Zcutproduct/pow(split_Zcutmpt, 2));
            }

            // 1D EC2 histogram def 1 and 2
            int binIndex = hSplitZcut2E2C_sum_vs_dr12pi1->GetXaxis()->FindBin(split_Zcutdr12);
            double binWidth = hSplitZcut2E2C_sum_vs_dr12pi1->GetBinWidth(binIndex);
            if((split_Zcutmpt == 0) || (split_Zcutproduct == 0))continue;
            else{
            if (ptBin == 0) {
            hSplitZcut2E2C_sum_vs_dr12pi1->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut2E2C_sum_vs_dr12def2pi1->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
            }
            if (ptBin == 1) {
            hSplitZcut2E2C_sum_vs_dr12pi2->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut2E2C_sum_vs_dr12def2pi2->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
             }
            if (ptBin == 2) {
            hSplitZcut2E2C_sum_vs_dr12pi3->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut2E2C_sum_vs_dr12def2pi3->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
            }
            if (ptBin == 3) {
            hSplitZcut2E2C_sum_vs_dr12pi4->Fill(split_Zcutdr12, split_Zcutproduct/(pow(split_Zcutmpt, 2)*binWidth*total_n_Jets));
            hSplitZcut2E2C_sum_vs_dr12def2pi4->Fill(split_Zcutdr12, split_Zcutproduct/(pow(sigPt, 2)*binWidth*total_n_Jets));
            }
             }
            
            
            } // end substructure loop
      } // end loop over jets
   
   } // end loop over events

   for (int j = 0; j < numIntervals; ++j) {
        if (ptAverages[j] > 0) {
            Pt_averages->SetBinContent(j + 1, ptAverages[j]); // Bins are 1-indexed in ROOT
        }
    }

   std::vector<double> binEdgeshScaled1 = ScaleBinEdges(binEdgesh, ptAverages[0]);
   std::vector<double> binEdgeshScaled2 = ScaleBinEdges(binEdgesh, ptAverages[1]);
   std::vector<double> binEdgeshScaled3 = ScaleBinEdges(binEdgesh, ptAverages[2]);
   std::vector<double> binEdgeshScaled4 = ScaleBinEdges(binEdgesh, ptAverages[3]);

   TH1D *hE2C_sum_vs_dr12_zcut1_pi1_scaled = new TH1D("hE2C_sum_vs_dr12_scaledpi1", "Scaled E2C per dr12; dr12; Summed E2C", binEdgeshScaled1.size() - 1, &binEdgeshScaled1[0]);
   TH1D *hE2C_sum_vs_dr12_zcut1_pi2_scaled = new TH1D("hE2C_sum_vs_dr12_scaledpi2", "Scaled E2C per dr12; dr12; Summed E2C", binEdgeshScaled2.size() - 1, &binEdgeshScaled2[0]);
   TH1D *hE2C_sum_vs_dr12_zcut1_pi3_scaled = new TH1D("hE2C_sum_vs_dr12_scaledpi3", "Scaled E2C per dr12; dr12; Summed E2C", binEdgeshScaled3.size() - 1, &binEdgeshScaled3[0]);
   TH1D *hE2C_sum_vs_dr12_zcut1_pi4_scaled = new TH1D("hE2C_sum_vs_dr12_scaledpi4", "Scaled E2C per dr12; dr12; Summed E2C", binEdgeshScaled4.size() - 1, &binEdgeshScaled4[0]);

   Scalex_axishistogram(hE2C_sum_vs_dr12_zcut1_pi1, hE2C_sum_vs_dr12_zcut1_pi1_scaled, ptAverages[0]);
   Scalex_axishistogram(hE2C_sum_vs_dr12_zcut1_pi2, hE2C_sum_vs_dr12_zcut1_pi2_scaled, ptAverages[1]);
   Scalex_axishistogram(hE2C_sum_vs_dr12_zcut1_pi3, hE2C_sum_vs_dr12_zcut1_pi3_scaled, ptAverages[2]);
   Scalex_axishistogram(hE2C_sum_vs_dr12_zcut1_pi4, hE2C_sum_vs_dr12_zcut1_pi4_scaled, ptAverages[3]);

  // Define scaled histograms with scaled bin edges
   // Scale bin edges for each ptAverage
   std::vector<double> binEdgesScaled1 = ScaleBinEdges(binEdges, ptAverages[0]);
   std::vector<double> binEdgesScaled2 = ScaleBinEdges(binEdges, ptAverages[1]);
   std::vector<double> binEdgesScaled3 = ScaleBinEdges(binEdges, ptAverages[2]);
   std::vector<double> binEdgesScaled4 = ScaleBinEdges(binEdges, ptAverages[3]);

   TH1D* hSplitE2C_sum_vs_dr12_scaledpi1 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi1", "Scaled EEC per pt interval (no Zcut); dr12; Normalised EEC", binEdgesScaled1.size() - 1, &binEdgesScaled1[0]);
   TH1D* hSplitE2C_sum_vs_dr12_scaledpi2 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi2", "Scaled EEC per pt interval (no Zcut); dr12; Normalised EEC", binEdgesScaled2.size() - 1, &binEdgesScaled2[0]);
   TH1D* hSplitE2C_sum_vs_dr12_scaledpi3 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi3", "Scaled EEC per pt interval (no Zcut); dr12; Normalised EEC", binEdgesScaled3.size() - 1, &binEdgesScaled3[0]);
   TH1D* hSplitE2C_sum_vs_dr12_scaledpi4 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi4", "Scaled EEC per pt interval (no Zcut); dr12; Normalised EEC", binEdgesScaled4.size() - 1, &binEdgesScaled4[0]);

   TH1D* hSplitE2C_sum_vs_dr12_scaledpi1_d2 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi1_d2", "Scaled EEC per pt interval (no Zcut) def2; dr12; Normalised EEC", binEdgesScaled1.size() - 1, &binEdgesScaled1[0]);
   TH1D* hSplitE2C_sum_vs_dr12_scaledpi2_d2 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi2_d2", "Scaled EEC per pt interval (no Zcut) def2; dr12; Normalised EEC", binEdgesScaled2.size() - 1, &binEdgesScaled2[0]);
   TH1D* hSplitE2C_sum_vs_dr12_scaledpi3_d2 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi3_d2", "Scaled EEC per pt interval (no Zcut) def2; dr12; Normalised EEC", binEdgesScaled3.size() - 1, &binEdgesScaled3[0]);
   TH1D* hSplitE2C_sum_vs_dr12_scaledpi4_d2 = new TH1D("hSplitE2C_sum_vs_dr12_scaledpi4_d2", "Scaled EEC per pt interval (no Zcut) def2; dr12; Normalised EEC", binEdgesScaled4.size() - 1, &binEdgesScaled4[0]);

   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi1 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi1", "Scaled EEC per pt interval (Zcut1); dr12; Summed E2C", binEdgesScaled1.size() - 1, &binEdgesScaled1[0]);
   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi2 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi2", "Scaled EEC per pt interval (Zcut1); dr12; Summed E2C", binEdgesScaled2.size() - 1, &binEdgesScaled2[0]);
   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi3 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi3", "Scaled EEC per pt interval (Zcut1); dr12; Summed E2C", binEdgesScaled3.size() - 1, &binEdgesScaled3[0]);
   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi4 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi4", "Scaled EEC per pt interval (Zcut1); dr12; Summed E2C", binEdgesScaled4.size() - 1, &binEdgesScaled4[0]);

   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi1_d2 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi1_d2", "Scaled EEC per pt interval (Zcut1) def2; dr12; Summed E2C", binEdgesScaled1.size() - 1, &binEdgesScaled1[0]);
   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi2_d2 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi2_d2", "Scaled EEC per pt interval (Zcut1) def2; dr12; Summed E2C", binEdgesScaled2.size() - 1, &binEdgesScaled2[0]);
   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi3_d2 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi3_d2", "Scaled EEC per pt interval (Zcut1) def2; dr12; Summed E2C", binEdgesScaled3.size() - 1, &binEdgesScaled3[0]);
   TH1D* hSplitZcut1E2C_sum_vs_dr12_scaledpi4_d2 = new TH1D("hSplitZcut1E2C_sum_vs_dr12_scaledpi4_d2", "Scaled EEC per pt interval (Zcut1) def2; dr12; Summed E2C", binEdgesScaled4.size() - 1, &binEdgesScaled4[0]);

   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi1 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi1", "Scaled EEC per pt interval (Zcut2); dr12; Summed E2C", binEdgesScaled1.size() - 1, &binEdgesScaled1[0]);
   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi2 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi2", "Scaled EEC per pt interval (Zcut2); dr12; Summed E2C", binEdgesScaled2.size() - 1, &binEdgesScaled2[0]);
   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi3 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi3", "Scaled EEC per pt interval (Zcut2); dr12; Summed E2C", binEdgesScaled3.size() - 1, &binEdgesScaled3[0]);
   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi4 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi4", "Scaled EEC per pt interval (Zcut2); dr12; Summed E2C", binEdgesScaled4.size() - 1, &binEdgesScaled4[0]);

   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi1_d2 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi1_d2", "Scaled EEC per pt interval (Zcut2) def2; dr12; Summed E2C", binEdgesScaled1.size() - 1, &binEdgesScaled1[0]);
   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi2_d2 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi2_d2", "Scaled EEC per pt interval (Zcut2) def2; dr12; Summed E2C", binEdgesScaled2.size() - 1, &binEdgesScaled2[0]);
   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi3_d2 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi3_d2", "Scaled EEC per pt interval (Zcut2) def2; dr12; Summed E2C", binEdgesScaled3.size() - 1, &binEdgesScaled3[0]);
   TH1D* hSplitZcut2E2C_sum_vs_dr12_scaledpi4_d2 = new TH1D("hSplitZcut2E2C_sum_vs_dr12_scaledpi4_d2", "Scaled EEC per pt interval (Zcut2) def2; dr12; Summed E2C", binEdgesScaled4.size() - 1, &binEdgesScaled4[0]);

   Scalex_axishistogram(hSplitE2C_sum_vs_dr12pi1, hSplitE2C_sum_vs_dr12_scaledpi1 ,ptAverages[0]);
   Scalex_axishistogram(hSplitE2C_sum_vs_dr12pi2, hSplitE2C_sum_vs_dr12_scaledpi2 ,ptAverages[1]);
   Scalex_axishistogram(hSplitE2C_sum_vs_dr12pi3, hSplitE2C_sum_vs_dr12_scaledpi3 ,ptAverages[2]);
   Scalex_axishistogram(hSplitE2C_sum_vs_dr12pi4, hSplitE2C_sum_vs_dr12_scaledpi4 ,ptAverages[3]);

   Scalex_axishistogram(hSplitE2C_sum_vs_dr12def2pi1, hSplitE2C_sum_vs_dr12_scaledpi1_d2 ,ptAverages[0]);
   Scalex_axishistogram(hSplitE2C_sum_vs_dr12def2pi2, hSplitE2C_sum_vs_dr12_scaledpi2_d2 ,ptAverages[1]);
   Scalex_axishistogram(hSplitE2C_sum_vs_dr12def2pi3, hSplitE2C_sum_vs_dr12_scaledpi3_d2 ,ptAverages[2]);
   Scalex_axishistogram(hSplitE2C_sum_vs_dr12def2pi4, hSplitE2C_sum_vs_dr12_scaledpi4_d2 ,ptAverages[3]);

   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12pi1, hSplitZcut1E2C_sum_vs_dr12_scaledpi1 ,ptAverages[0]);
   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12pi2, hSplitZcut1E2C_sum_vs_dr12_scaledpi2 ,ptAverages[1]);
   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12pi3, hSplitZcut1E2C_sum_vs_dr12_scaledpi3 ,ptAverages[2]);
   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12pi4, hSplitZcut1E2C_sum_vs_dr12_scaledpi4 ,ptAverages[3]);

   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12def2pi1, hSplitZcut1E2C_sum_vs_dr12_scaledpi1_d2 ,ptAverages[0]);
   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12def2pi2, hSplitZcut1E2C_sum_vs_dr12_scaledpi2_d2 ,ptAverages[1]);
   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12def2pi3, hSplitZcut1E2C_sum_vs_dr12_scaledpi3_d2 ,ptAverages[2]);
   Scalex_axishistogram(hSplitZcut1E2C_sum_vs_dr12def2pi4, hSplitZcut1E2C_sum_vs_dr12_scaledpi4_d2 ,ptAverages[3]);

   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12pi1, hSplitZcut2E2C_sum_vs_dr12_scaledpi1 ,ptAverages[0]);
   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12pi2, hSplitZcut2E2C_sum_vs_dr12_scaledpi2 ,ptAverages[1]);
   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12pi3, hSplitZcut2E2C_sum_vs_dr12_scaledpi3 ,ptAverages[2]);
   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12pi4, hSplitZcut2E2C_sum_vs_dr12_scaledpi4 ,ptAverages[3]);

   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12def2pi1, hSplitZcut2E2C_sum_vs_dr12_scaledpi1_d2 ,ptAverages[0]);
   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12def2pi2, hSplitZcut2E2C_sum_vs_dr12_scaledpi2_d2 ,ptAverages[1]);
   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12def2pi3, hSplitZcut2E2C_sum_vs_dr12_scaledpi3_d2 ,ptAverages[2]);
   Scalex_axishistogram(hSplitZcut2E2C_sum_vs_dr12def2pi4, hSplitZcut2E2C_sum_vs_dr12_scaledpi4_d2 ,ptAverages[3]);


   RatioHistogram(hSplitZcut1E2C_sum_vs_dr12pi1, hSplitE2C_sum_vs_dr12pi1, ratio_EEC_zcut01_pi1);
   RatioHistogram(hSplitZcut1E2C_sum_vs_dr12pi2, hSplitE2C_sum_vs_dr12pi2, ratio_EEC_zcut01_pi2);
   RatioHistogram(hSplitZcut1E2C_sum_vs_dr12pi3, hSplitE2C_sum_vs_dr12pi3, ratio_EEC_zcut01_pi3);
   RatioHistogram(hSplitZcut1E2C_sum_vs_dr12pi4, hSplitE2C_sum_vs_dr12pi4, ratio_EEC_zcut01_pi4);

   RatioHistogram(hSplitZcut2E2C_sum_vs_dr12pi1, hSplitE2C_sum_vs_dr12pi1, ratio_EEC_zcut02_pi1);
   RatioHistogram(hSplitZcut2E2C_sum_vs_dr12pi2, hSplitE2C_sum_vs_dr12pi2, ratio_EEC_zcut02_pi2);
   RatioHistogram(hSplitZcut2E2C_sum_vs_dr12pi3, hSplitE2C_sum_vs_dr12pi3, ratio_EEC_zcut02_pi3);
   RatioHistogram(hSplitZcut2E2C_sum_vs_dr12pi4, hSplitE2C_sum_vs_dr12pi4, ratio_EEC_zcut02_pi4);




   TFile *fout;
   fout = new TFile("JetToyResults.root","RECREATE");

  // Write 1D histograms
   //std::cout << "write content" << std::endl;S
   /*
   h1JPtW->Write();
   h1JPt->Write();
   h1E2CSigSD01->Write();
   h1PtSigSD01->Write();
   h1zgSigSD01->Write();
   h1eradSigSD01->Write();
   h1dr12SigSD01->Write();
   h1PtSigSD05->Write();
   h1zgSigSD05->Write();
   h1eradSigSD05->Write();
   h1E2CSigSD05->Write();
   h1dr12SigSD05->Write();
   h1PtSigSD03->Write();
   h1zgSigSD03->Write();
   h1eradSigSD03->Write();
   h1E2CSigSD03->Write();
   h1dr12SigSD03->Write();

   // Write 2D histograms
   h2E2C_vs_dr12_SD01->Write();
   h2E2C_vs_dr12_SD05->Write();
   h2E2C_vs_dr12_SD03->Write();
   */

   //Histograms for Counter (splits)
      //With Zcut
   hSplitZcut1Dr12->Write();
   hSplitZcut1Erad->Write();
   hSplitZcut1Product->Write();
   hSplitZcut1JetPt->Write();
   hSplitZcut1LogDr12->Write();
   hSplitZcut1LogZTheta->Write();
   hSplitZcut1Z->Write();
      //Without Zcut
   hSplitDr12->Write();
   hSplitErad->Write();
   hSplitProduct->Write();
   hSplitJetPt->Write();
   hSplitLogDr12->Write();
   hSplitLogZTheta->Write();
   hSplitZ->Write();

      // 2D Histograms: E2C vs dr12 splits
   hSplitZcut1E2C_vs_dr12->Write();
   hSplitZcut2E2C_vs_dr12->Write();
   hSplitE2C_vs_dr12->Write(); 

      // 2D histograms: Lund planes for splits (with and without Zcut)
   hSplitZcut1logzdr_vs_1dr12->Write();
   hSplitZcut2logzdr_vs_1dr12->Write();
   hSplitlogzdr_vs_1dr12->Write();

      // 1D histograms: Normalised E2C for four pt intervals (with and without Zcut)
   hSplitZcut1E2C_sum_vs_dr12pi1->Write();
   hSplitZcut1E2C_sum_vs_dr12pi2->Write();
   hSplitZcut1E2C_sum_vs_dr12pi3->Write();
   hSplitZcut1E2C_sum_vs_dr12pi4->Write();
   hSplitZcut1E2C_sum_vs_dr12def2pi1->Write();
   hSplitZcut1E2C_sum_vs_dr12def2pi2->Write();
   hSplitZcut1E2C_sum_vs_dr12def2pi3->Write();
   hSplitZcut1E2C_sum_vs_dr12def2pi4->Write();

   hSplitZcut1E2C_sum_vs_dr12_scaledpi1->Write();
   hSplitZcut1E2C_sum_vs_dr12_scaledpi2->Write();
   hSplitZcut1E2C_sum_vs_dr12_scaledpi3->Write();
   hSplitZcut1E2C_sum_vs_dr12_scaledpi4->Write();
   hSplitZcut1E2C_sum_vs_dr12_scaledpi1_d2->Write();
   hSplitZcut1E2C_sum_vs_dr12_scaledpi2_d2->Write();
   hSplitZcut1E2C_sum_vs_dr12_scaledpi3_d2->Write();
   hSplitZcut1E2C_sum_vs_dr12_scaledpi4_d2->Write();

   hSplitZcut2E2C_sum_vs_dr12pi1->Write();
   hSplitZcut2E2C_sum_vs_dr12pi2->Write();
   hSplitZcut2E2C_sum_vs_dr12pi3->Write();
   hSplitZcut2E2C_sum_vs_dr12pi4->Write();
   hSplitZcut2E2C_sum_vs_dr12def2pi1->Write();
   hSplitZcut2E2C_sum_vs_dr12def2pi2->Write();
   hSplitZcut2E2C_sum_vs_dr12def2pi3->Write();
   hSplitZcut2E2C_sum_vs_dr12def2pi4->Write();

   hSplitZcut2E2C_sum_vs_dr12_scaledpi1->Write();
   hSplitZcut2E2C_sum_vs_dr12_scaledpi2->Write();
   hSplitZcut2E2C_sum_vs_dr12_scaledpi3->Write();
   hSplitZcut2E2C_sum_vs_dr12_scaledpi4->Write();
   hSplitZcut2E2C_sum_vs_dr12_scaledpi1_d2->Write();
   hSplitZcut2E2C_sum_vs_dr12_scaledpi2_d2->Write();
   hSplitZcut2E2C_sum_vs_dr12_scaledpi3_d2->Write();
   hSplitZcut2E2C_sum_vs_dr12_scaledpi4_d2->Write();

   hSplitE2C_sum_vs_dr12pi1->Write();
   hSplitE2C_sum_vs_dr12pi2->Write();
   hSplitE2C_sum_vs_dr12pi3->Write();
   hSplitE2C_sum_vs_dr12pi4->Write();
   hSplitE2C_sum_vs_dr12def2pi1->Write();
   hSplitE2C_sum_vs_dr12def2pi2->Write();
   hSplitE2C_sum_vs_dr12def2pi3->Write();
   hSplitE2C_sum_vs_dr12def2pi4->Write();

   hSplitE2C_sum_vs_dr12_scaledpi1->Write();
   hSplitE2C_sum_vs_dr12_scaledpi2->Write();
   hSplitE2C_sum_vs_dr12_scaledpi3->Write();
   hSplitE2C_sum_vs_dr12_scaledpi4->Write();
   hSplitE2C_sum_vs_dr12_scaledpi1_d2->Write();
   hSplitE2C_sum_vs_dr12_scaledpi2_d2->Write();
   hSplitE2C_sum_vs_dr12_scaledpi3_d2->Write();
   hSplitE2C_sum_vs_dr12_scaledpi4_d2->Write();

   ratio_EEC_zcut01_pi1->Write();
   ratio_EEC_zcut01_pi2->Write();
   ratio_EEC_zcut01_pi3->Write();
   ratio_EEC_zcut01_pi4->Write();
   ratio_EEC_zcut02_pi1->Write();
   ratio_EEC_zcut02_pi2->Write();
   ratio_EEC_zcut02_pi3->Write();
   ratio_EEC_zcut02_pi4->Write();

     
   // Histograms for hadron pairs
   hE2C_hadron_pairs->Write(); // 2D E2C vs dr12
   hE2C_sum_vs_dr12_zcut1_pi1->Write(); // 1D normalised E2C
   hE2C_sum_vs_dr12_zcut1_pi2->Write();
   hE2C_sum_vs_dr12_zcut1_pi3->Write();
   hE2C_sum_vs_dr12_zcut1_pi4->Write();

   hE2C_sum_vs_dr12_zcut1_pi1_scaled->Write(); // 1D normalised and scaled E2C
   hE2C_sum_vs_dr12_zcut1_pi2_scaled->Write(); 
   hE2C_sum_vs_dr12_zcut1_pi3_scaled->Write(); 
   hE2C_sum_vs_dr12_zcut1_pi4_scaled->Write(); 
   
   Pt_averages->Write();

   /*
   hE2C_sum_vs_dr12_scaled_zcut2->Write();
   hE2C_sum_vs_dr12_scaled_zcut3->Write();
   hE2C_sum_vs_dr12_scaled_zcut4->Write();
   hE2C_sum_vs_dr12_scaled_zcut5->Write();
   */



   Ptjet->Write();

   fout->Write();
   fout->Close();
   

}