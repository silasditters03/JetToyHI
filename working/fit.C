#include "TF1.h"
#include "TH1.h"
#include "TFile.h"

std::vector<double> pt_av = {46.8391, 67.55, 87.9418, 108.261};


TF1 *fitTruncatedGaus(TH1 *h = NULL, double nl = 3., double nr = 3., double mean = -1., double sigma = -1.);

void fit(TString strIn = "JetToyResults.root", TString strHist = "hE2C_sum_vs_dr12_pi2") {

  TFile *f = new TFile(strIn.Data());
  TH1 *h1 = dynamic_cast<TH1*>(f->Get(strHist.Data()));
    
  TF1 *f1 = fitTruncatedGaus(h1, 0.4, 0.4, 0.07, h1->GetRMS());

  double peak = f1->GetParameter(1);  // Parameter 1 is the mean (mu)
  double peak_er= f1->GetParError(1);
  double chi2 = f1->GetChisquare();
  double ndf = f1->GetNDF();
  double reducedChi2 = chi2 / ndf;
  Printf("reduced Chi = %f", reducedChi2);
  Printf("The final peak of the Gaussian fit (mu) is: %f +/- %f", peak*pt_av[1], peak_er*pt_av[1]);

  TCanvas *c3 = new TCanvas("c3","c3",500,400);
  h1->Draw();
  f1->Draw("same");
  c3->SaveAs("iterive fit.png");
  
  delete f;
}


TF1 *fg1 = NULL;

TF1 *fitTruncatedGaus(TH1 *h, double nl, double nr, double mean, double sigma) {

  if(fg1) delete fg1;
  fg1 = new TF1("g1","gaus",h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());

  if(sigma>0.) {
    h->Fit(fg1,"R0I","",mean-nl*sigma,mean+nr*sigma);
  } else
    h->Fit(fg1,"R0I","",h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());
  
  sigma = fg1->GetParameter(2);
  mean  = fg1->GetParameter(1);
  Printf("--1 fit mean: %f sigma: %f",mean,sigma);

  int maxIter = 10;
  double meanOld = mean;
  for(int i = 0; i<maxIter; ++i) {
    meanOld = mean;
 
    h->Fit(fg1,"R0I","",mean-nl*sigma,mean+nr*sigma);
    sigma = fg1->GetParameter(2);
    mean  = fg1->GetParameter(1);
    fg1->SetRange(mean-nl*sigma,mean+nr*sigma);
    Printf("--%i fit mean: %f sigma: %f",i,mean,sigma);
    if(fabs(mean-meanOld)<0.001) return fg1;
  }

  return fg1;
}
