#include <TROOT.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <iostream>
#include "TGraphErrors.h"
#include <vector>
#include <string>
#include <utility>

#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TColor.h>


std::pair<double, double> GaussFit(TH1 *hist, double pt_av, const std::string &output_filename, double b1, double b2, double bound) {
    if (!hist || hist->GetEntries() == 0) {
        std::cout << "Error: Histogram null or empty" << std::endl;
        return {0.0, 0.0};
    }


    // Check if no values <= 0
    for (int i = 1; i <= hist->GetNbinsX(); ++i) {
        double bin_content = hist->GetBinContent(i);
        if (bin_content <= 0.) {
            hist->SetBinContent(i, 0); // invalid bins set to 0
        }
    }

std::cout << "define fit function" << std::endl;

    // Define function for the fitting
    const char *fit_function = "[0]*exp(-pow(log(x)-[1], 2)/(2*pow([2], 2)))";
    //std::unique_ptr<TF1> gaus(new TF1("gaus", fit_function, b1, b2));
    std::unique_ptr<TF1> gaus(new TF1("gaus", "gaus", b1, b2));

    // Initialize parameters
    double mean_dr = hist->GetMean();
    double mu_guess = mean_dr;
    std::cout << "mean_dr: " << mean_dr << std::endl;
    double sigma_guess = hist->GetRMS();
    double C_guess = hist->GetMaximum();
    std::cout << "sigma_dr: " << sigma_guess << std::endl;

    if (sigma_guess <= 0 || mean_dr <= 0) {
        std::cerr << "Error: Invalid mean or RMS" << std::endl;
        return {0.0, 0.0};
    }

    gaus->SetParameters(C_guess, mu_guess, sigma_guess);
    //gaus->SetParameters(1.,0.04,0.02);

    // Perform the initial fit
    auto fit_result = hist->Fit(gaus.get(), "R");
    if (fit_result != 0) {
        std::cerr << "Initial fit failed!" << std::endl;
        return {0.0, 0.0};
    }

    double mu = gaus->GetParameter(1);
    double sigma = gaus->GetParameter(2);

    // Set the fit range dynamically based on the initial fit
    double lower_bound = mu - bound * sigma;
    double upper_bound = mu + bound * sigma;
    std::cout << "low: " << lower_bound << "  upper_bound: " << upper_bound << std::endl;
    gaus->SetRange(lower_bound, upper_bound);

    // Second fit with restricted range
    fit_result = hist->Fit(gaus.get(), "R I");
    if (fit_result != 0) {
        std::cerr << "Refined fit failed!" << std::endl;
        return {0.0, 0.0};
    }

    // Retrieve final fit parameters
    double C_fit = gaus->GetParameter(0);
    mu = gaus->GetParameter(1);
    sigma = gaus->GetParameter(2);
    double mu_error = gaus->GetParError(1);
    double sigma_error = gaus->GetParError(2);

    // Draw histogram with fit
    std::cout << "draw histo" << std::endl;
    //auto canvas = std::make_unique<TCanvas>("canvas", "Gaussian Fit", 800, 600);
    TCanvas *canvas = new TCanvas("c1","c1",800,600);
    std::cout << "canvas made \n";
    canvas->SetLogx();
    std::cout << "log x done \n";
    hist->GetXaxis()->SetRangeUser(1e-3, 1);
    std::cout << "range done \n";
    hist->Draw();
    std::cout << "draw done \n";
    gaus->Draw("SAME");
    std::cout << "draw gaus done \n";
    std::cout << "output filename: " << output_filename << std::endl;
    canvas->SaveAs("test.png");//output_filename.c_str());
    std::cout << "saving done \n";

    // Extract dr_peak and scaled dr_peak
    std::cout << "extract peak info" << std::endl;
    double dr_peak = TMath::Exp(mu);
    double dr_error = dr_peak * mu_error;
    double scaled_dr_peak = dr_peak * pt_av;
    double scaled_dr_peak_error = dr_error * pt_av;

    // Print results
    std::cout << "Results for " << output_filename << ":" << std::endl;
    std::cout << "Reduced Chi^2: " << gaus->GetChisquare() / gaus->GetNDF() << std::endl;
    //std::cout << "mu = " << mu << " +/- " << mu_error << std::endl;
    //std::cout << "sigma = " << sigma << " +/- " << sigma_error << std::endl;
    std::cout << "dr peak = " << dr_peak << " +/- " << dr_error << std::endl;
    std::cout << "scaled dr peak = " << scaled_dr_peak << " +/- " << scaled_dr_peak_error << std::endl;

    return std::make_pair(scaled_dr_peak, scaled_dr_peak_error);
}


void plotdebug() {

TFile * f1 = new TFile("JetToyResults.root");
TH1 *g19dz1= dynamic_cast<TH1*>(f1->Get("hSplitZcut1E2C_sum_vs_dr12pi4"));  

TCanvas *c2 = new TCanvas("c2","c2",400,400);
g19dz1->Draw();
c2->SaveAs("test2.png");

std::vector<double> pt_av = {36.413, 57.2359, 77.9346, 98.1566}; //average pt's per pt interval
std::cout << "test1"  << std::endl;
auto [sdrpi3_split_zcut1, sdrpi3_split_zcut1_er] = GaussFit(g19dz1, pt_av[3], "fit_splitzcut1_pt[3].png", 0.001, 0.1, 0.9);
std::cout << "test2"  << std::endl;

}

