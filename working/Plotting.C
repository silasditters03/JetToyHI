#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "TCanvas.h"
#include "TLatex.h"
#include "TMath.h"
#include "TFile.h"
#include "TH3F.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

using namespace std;

int colors[4] = {1,kRed+1,4,kGreen+2};
int styles[4] = {20,25,24,21};

TH1F *DrawFrame(double xmin = 0., double xmax = 1., double ymin = 0., double ymax = 1., TString xTitle = "x", TString yTitle = "y", bool setMargins = true);

void yScaling(TH1F* hists[4], std::vector<double> PtAverages ) {
    for (int i = 0; i < 4; ++i){
        hists[i]->Scale( log(PtAverages[i])/(PtAverages[i] ) );
    }
}

void Plotting(TString strIn = "JetToyResults.root") {

    TFile *f = new TFile(strIn.Data());

    //Imports the average P_T's per bin
    TH1F *PtAve = (TH1F*)f->Get("Pt_averages");

    double PtAveBin0 = PtAve->GetBinContent(1); //P_T average for bin 40-60
    double PtAveBin1 = PtAve->GetBinContent(2); //P_T average for bin 60-80
    double PtAveBin2 = PtAve->GetBinContent(3); //P_T average for bin 80-100
    double PtAveBin3 = PtAve->GetBinContent(4); //P_T average for bin 100-120

    std::vector<double> PtAverages = {PtAveBin0, PtAveBin1, PtAveBin2, PtAveBin3};

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)
    //---------------------------------------------------------------------------------------
    gStyle->SetOptStat(0000000);
    //Retrieve Histograms
    TH1F *h1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1");
    TH1F *h2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2");
    TH1F *h3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3");
    TH1F *h4 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4");

    // Create canvas
    TCanvas *h_overlay_def1 = new TCanvas("h_overlay_def1", "Overlaid Histograms", 800, 600);

    h_overlay_def1->SetLeftMargin(0.15);
    h_overlay_def1->SetBottomMargin(0.15);


    h1->SetTitle("");
    h1->GetXaxis()->SetTitleSize(0.07);
    h1->GetYaxis()->SetTitleSize(0.05);
    h1->SetStats(0);
    

    h_overlay_def1->SetLogx();

    TH1F* hists[4] = {h1, h2, h3, h4};

    for (int i = 0; i < 4; ++i) {
        hists[i]->SetLineColor(colors[i]);
        hists[i]->SetMarkerColor(colors[i]);
        hists[i]->SetMarkerStyle(styles[i]);
        hists[i]->SetMarkerSize(0.2);
    }


          // Draw the first histogram
    h1->Draw("P"); 
    h2->Draw("P SAME");
    h3->Draw("P SAME");
    h4->Draw("P SAME");

    TPaveText *txtbox1 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox1->SetFillColor(0);     // Transparent
    txtbox1->SetBorderSize(0);    // Thin border
    txtbox1->SetTextFont(62);     // Standard font
    txtbox1->SetTextSize(0.03);

    
    txtbox1->AddText("Final State Hadron Pairs");
    txtbox1->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox1->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox1->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox1->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox1->Draw();


    h1->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");

    // Find the maximum value of all histograms
    double maxY = h1->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax = hists[i]->GetMaximum();
        if (histMax > maxY) {
            maxY = histMax;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1->GetYaxis()->SetRangeUser(0, 1.2 * maxY);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg->AddEntry(h1, "40-60 GeV/#it{c}", "l");
    leg->AddEntry(h2, "60-80 GeV/#it{c}", "l");
    leg->AddEntry(h3, "80-100 GeV/#it{c}", "l");
    leg->AddEntry(h4, "100-120 GeV/#it{c}", "l");
    leg->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1_def2");
    TH1F *h6 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2_def2");
    TH1F *h7 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3_def2");
    TH1F *h8 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4_def2");

    

    // Create canvas
    TCanvas *h_overlay_def2 = new TCanvas("h_overlay_def2", "Overlaid Histograms", 800, 600);

    h_overlay_def2->SetLeftMargin(0.15);
    h_overlay_def2->SetBottomMargin(0.15);

    h5->SetTitle("");
    h5->GetXaxis()->SetTitleSize(0.07);
    h5->GetYaxis()->SetTitleSize(0.05);
    h5->SetStats(0);

    h_overlay_def2->SetLogx();

    TH1F* hists2[4] = {h5, h6, h7, h8};

    for (int i = 0; i < 4; ++i) {
        hists2[i]->SetLineColor(colors[i]);
        hists2[i]->SetMarkerColor(colors[i]);
        hists2[i]->SetMarkerStyle(styles[i]);
        hists2[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h5->Draw("P");  //
    h6->Draw("P SAME");
    h7->Draw("P SAME");
    h8->Draw("P SAME");

    TPaveText *txtbox2 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox2->SetFillColor(0);     // Transparent
    txtbox2->SetBorderSize(0);    // Thin border
    txtbox2->SetTextFont(62);     // Standard font
    txtbox2->SetTextSize(0.03);

    
    txtbox2->AddText("Final State Hadron Pairs");
    txtbox2->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox2->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox2->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox2->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox2->Draw();

    h5->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");



    // Find the maximum value of all histograms
    double maxY2 = h5->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2 = hists2[i]->GetMaximum();
        if (histMax2 > maxY2) {
            maxY2 = histMax2;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5->GetYaxis()->SetRangeUser(0, 1.2 * maxY2);  // Add a little margin above the maximum value
 

    // Add legend
    TLegend *leg2 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2->AddEntry(h5, "40-60 GeV/#it{c}", "l");
    leg2->AddEntry(h6, "60-80 GeV/#it{c}", "l");
    leg2->AddEntry(h7, "80-100 GeV/#it{c}", "l");
    leg2->AddEntry(h8, "100-120 GeV/#it{c}", "l");
    leg2->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h1_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi1");
    TH1F *h2_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi2");
    TH1F *h3_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi3");
    TH1F *h4_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi4");

    // Create canvas
    TCanvas *h_overlay_def1_scaled = new TCanvas("h_overlay_def1_scaled", "Overlaid of Scaled Histograms", 800, 600);

    h_overlay_def1_scaled->SetLeftMargin(0.15);
    h_overlay_def1_scaled->SetBottomMargin(0.15);

    h1_sc->SetTitle("");
    h1_sc->GetXaxis()->SetTitleSize(0.07);
    h1_sc->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def1_scaled->SetLogx();

    TH1F* hists_sc[4] = {h1_sc, h2_sc, h3_sc, h4_sc};

    yScaling(hists_sc,PtAverages);

    for (int i = 0; i < 4; ++i) {
        hists_sc[i]->SetLineColor(colors[i]);
        hists_sc[i]->SetMarkerColor(colors[i]);
        hists_sc[i]->SetMarkerStyle(styles[i]);
        hists_sc[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h1_sc->Draw("P");  // 
    h2_sc->Draw("P SAME");
    h3_sc->Draw("P SAME");
    h4_sc->Draw("P SAME");

    txtbox1->Draw();

    h1_sc->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");

    

    // Find the maximum value of all histograms
    double maxY_sc = h1_sc->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax_sc = hists_sc[i]->GetMaximum();
        if (histMax_sc > maxY_sc) {
            maxY_sc = histMax_sc;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1_sc->GetYaxis()->SetRangeUser(0, 1.2 * maxY_sc);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg_sc = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_sc->AddEntry(h1_sc, "40-60 GeV/#it{c}", "l");
    leg_sc->AddEntry(h2_sc, "60-80 GeV/#it{c}", "l");
    leg_sc->AddEntry(h3_sc, "80-100 GeV/#it{c}", "l");
    leg_sc->AddEntry(h4_sc, "100-120 GeV/#it{c}", "l");
    leg_sc->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi1");
    TH1F *h6_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi2");
    TH1F *h7_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi3");
    TH1F *h8_sc = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi4");

    // Create canvas
    TCanvas *h_overlay_def2_scaled = new TCanvas("h_overlay_def2_scaled", "Overlaid Histograms", 800, 600);

    h_overlay_def2_scaled->SetLeftMargin(0.15);
    h_overlay_def2_scaled->SetBottomMargin(0.15);

    h5_sc->SetTitle("");
    h5_sc->GetXaxis()->SetTitleSize(0.07);
    h5_sc->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def2_scaled->SetLogx();

    TH1F* hists2_sc[4] = {h5_sc, h6_sc, h7_sc, h8_sc};

    


    yScaling(hists2_sc,PtAverages);

    std::vector<double> values;
    double val = 0;
    for (int i = 0; i < 4; i++){
        int maxBin = hists2_sc[i]->GetMaximumBin();
        double xAtMax = hists2_sc[i]->GetXaxis()->GetBinCenter(maxBin);
        val += xAtMax;
        values.push_back(xAtMax);
    }

    double stddev = TMath::RMS(values.size(), values.data());
    cout << "x_peak is at " << val/4 << "±" << stddev << endl;

    for (int i = 0; i < 4; ++i) {
        hists2_sc[i]->SetLineColor(colors[i]);
        hists2_sc[i]->SetMarkerColor(colors[i]);
        hists2_sc[i]->SetMarkerStyle(styles[i]);
        hists2_sc[i]->SetMarkerSize(0.2);
    }

    // Draw the first histogram
    h5_sc->Draw("P SAME"); 
    h6_sc->Draw("P SAME");
    h7_sc->Draw("P SAME");
    h8_sc->Draw("P SAME");
    

    h5_sc->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");


    // Find the maximum value of all histograms
    double maxY2_sc = h5_sc->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2_sc = hists2_sc[i]->GetMaximum();
        if (histMax2_sc > maxY2_sc) {
            maxY2_sc = histMax2_sc;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5_sc->GetYaxis()->SetRangeUser(0, 1.2 * maxY2_sc);  // Add a little margin above the maximum value

    TLine *line = new TLine(val/4, h5_sc->GetMinimum(), val/4, 1.2*maxY2_sc);
    line->SetLineColor(kGray+1);     // Customize color
    line->SetLineWidth(2);        // Thicker line
    line->SetLineStyle(1);        // Dashed, optional
    line->Draw("same"); 

    TPaveText *txtbox4 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox4->SetFillColor(0);     // Transparent
    txtbox4->SetBorderSize(0);    // Thin border
    txtbox4->SetTextFont(62);     // Standard font
    txtbox4->SetTextSize(0.03);

    
    txtbox4->AddText("Final State Hadron Pairs");
    txtbox4->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox4->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox4->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox4->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox4->AddText(Form("#it{#tau}_{f}^{peak} = %.2f #pm %.2f fm GeV/#it{c}/<#it{p}_{T}^{#it{ch jet}}>", val/4, stddev));

    txtbox4->Draw();

 
    // Set the X-axis range for the histograms on h_overlay_def2
    //h5_sc->GetXaxis()->SetRangeUser(0, 100);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg2_sc = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_sc->AddEntry(h5_sc, "40-60 GeV/#it{c}", "l");
    leg2_sc->AddEntry(h6_sc, "60-80 GeV/#it{c}", "l");
    leg2_sc->AddEntry(h7_sc, "80-100 GeV/#it{c}", "l");
    leg2_sc->AddEntry(h8_sc, "100-120 GeV/#it{c}", "l");
    leg2_sc->Draw();

    //----------------------------------------------------------------------
    //Plotting overlap for  hE2C_sum_vs_dr12_zcut1_pi(i)
    //----------------------------------------------------------------------

//----------------------------------------------------------------
// Now we plot overlaps for splittings
//----------------------------------------------------------------

    //---------------------------------------------------------------------------------------
    //Overlap of hSplitZcut1E2C_sum_vs_taupi(i)
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h9 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi1");
    TH1F *h10 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi2");
    TH1F *h11 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi3");
    TH1F *h12 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi4");

    // Create canvas
    TCanvas *split_overlay_def1 = new TCanvas("split_overlay_def1", "Overlaid Histograms", 800, 600);

    split_overlay_def1->SetLeftMargin(0.15);
    split_overlay_def1->SetBottomMargin(0.15);

    h9->SetTitle("");
    h9->GetXaxis()->SetTitleSize(0.07);
    h9->GetYaxis()->SetTitleSize(0.05);
    h9->SetStats(0);

    split_overlay_def1->SetLogx();

    TH1F* split_hists[4] = {h9, h10, h11, h12};

    for (int i = 0; i < 4; ++i) {
        split_hists[i]->SetLineColor(colors[i]);
        split_hists[i]->SetMarkerColor(colors[i]);
        split_hists[i]->SetMarkerStyle(styles[i]);
        split_hists[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h9->Draw("P");  // 
    h10->Draw("P SAME");
    h11->Draw("P SAME");
    h12->Draw("P SAME");

    TPaveText *txtbox5 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox5->SetFillColor(0);     // Transparent
    txtbox5->SetBorderSize(0);    // Thin border
    txtbox5->SetTextFont(62);     // Standard font
    txtbox5->SetTextSize(0.03);

    
    txtbox5->AddText("Jet Subtructure splittings");
    txtbox5->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox5->AddText("PYTHIA8, C/A particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox5->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox5->AddText("#it{p}_{T,parent} = #it{p}_{T,m} (taken directly)");

    txtbox5->Draw();

    h9->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");

    // Find the maximum value of all histograms
    double maxY3 = h9->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax3 = split_hists[i]->GetMaximum();
        if (histMax3 > maxY3) {
            maxY3 = histMax3;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h9->GetYaxis()->SetRangeUser(0, 1.2 * maxY3);  // Add a little margin above the maximum value

    // Set the X-axis range for the histograms on split_overlay_def2
    //h9->GetXaxis()->SetRangeUser(0, 1);  // Set x-axis range (adjust maximum as needed)


    // Add legend
    TLegend *leg3 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg3->AddEntry(h9, "40-60 GeV/#it{c}", "l");
    leg3->AddEntry(h10, "60-80 GeV/#it{c}", "l");
    leg3->AddEntry(h11, "80-100 GeV/#it{c}", "l");
    leg3->AddEntry(h12, "100-120 GeV/#it{c}", "l");
    leg3->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hSplitZcut1E2C_sum_vs_tau_def2pi(i)
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h13 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi1");
    TH1F *h14 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi2");
    TH1F *h15 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi3");
    TH1F *h16 = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi4");

    // Create canvas
    TCanvas *split_overlay_def2 = new TCanvas("split_overlay_def2", "Overlaid Histograms", 800, 600);

    split_overlay_def2->SetLeftMargin(0.15);
    split_overlay_def2->SetBottomMargin(0.15);

    h13->SetTitle("");
    h13->GetXaxis()->SetTitleSize(0.07);
    h13->GetYaxis()->SetTitleSize(0.05);
    h13->SetStats(0);

    split_overlay_def2->SetLogx();

    TH1F* split_hists2[4] = {h13, h14, h15, h16};

    for (int i = 0; i < 4; ++i) {
        split_hists2[i]->SetLineColor(colors[i]);
        split_hists2[i]->SetMarkerColor(colors[i]);
        split_hists2[i]->SetMarkerStyle(styles[i]);
        split_hists2[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h13->Draw("P");  // , E = errors
    h14->Draw("P SAME");
    h15->Draw("P SAME");
    h16->Draw("P SAME");

    TPaveText *txtbox6 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox6->SetFillColor(0);     // Transparent
    txtbox6->SetBorderSize(0);    // Thin border
    txtbox6->SetTextFont(62);     // Standard font
    txtbox6->SetTextSize(0.03);

    
    txtbox6->AddText("Jet Subtructure splittings");
    txtbox6->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox6->AddText("PYTHIA8, C/A particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox6->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox6->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox6->Draw();

    h13->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");

    // Find the maximum value of all histograms
    double maxY4 = h13->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax4 = split_hists2[i]->GetMaximum();
        if (histMax4 > maxY4) {
            maxY4 = histMax4;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h13->GetYaxis()->SetRangeUser(0, 1.2 * maxY4);  // Add a little margin above the maximum value
 
    // Set the X-axis range for the histograms on split_overlay_def2
    //h13->GetXaxis()->SetRangeUser(0, 1);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg4 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg4->AddEntry(h13, "40-60 GeV/#it{c}", "l");
    leg4->AddEntry(h14, "60-80 GeV/#it{c}", "l");
    leg4->AddEntry(h15, "80-100 GeV/#it{c}", "l");
    leg4->AddEntry(h16, "100-120 GeV/#it{c}", "l");
    leg4->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hSplitZcut1E2C_sum_vs_taupi(i)_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h9_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi1_scaled");
    TH1F *h10_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi2_scaled");
    TH1F *h11_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi3_scaled");
    TH1F *h12_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_taupi4_scaled");

    // Create canvas
    TCanvas *split_overlay_def1_scaled = new TCanvas("split_overlay_def1_scaled", "Overlaid Histograms", 800, 600);

    split_overlay_def1_scaled->SetLeftMargin(0.15);
    split_overlay_def1_scaled->SetBottomMargin(0.15);

    h9_sc->SetTitle("");
    h9_sc->GetXaxis()->SetTitleSize(0.07);
    h9_sc->GetYaxis()->SetTitleSize(0.05);

    split_overlay_def1_scaled->SetLogx();

    TH1F* split_hists_sc[4] = {h9_sc, h10_sc, h11_sc, h12_sc};

    yScaling(split_hists_sc,PtAverages);

    for (int i = 0; i < 4; ++i) {
        split_hists_sc[i]->SetLineColor(colors[i]);
        split_hists_sc[i]->SetMarkerColor(colors[i]);
        split_hists_sc[i]->SetMarkerStyle(styles[i]);
        split_hists_sc[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h9_sc->Draw("P");  // 
    h10_sc->Draw("P SAME");
    h11_sc->Draw("P SAME");
    h12_sc->Draw("P SAME");

    txtbox5->Draw();

    h9_sc->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");

    // Find the maximum value of all histograms
    double maxY3_sc = h9_sc->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax3_sc = split_hists_sc[i]->GetMaximum();
        if (histMax3_sc > maxY3_sc) {
            maxY3_sc = histMax3_sc;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h9_sc->GetYaxis()->SetRangeUser(0, 1.2 * maxY3_sc);  // Add a little margin above the maximum value

    // Set the X-axis range for the histograms on h_overlay_def2
    //h9_sc->GetXaxis()->SetRangeUser(0, 50);  // Set x-axis range (adjust maximum as needed)


    // Add legend
    TLegend *leg3_sc = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg3_sc->AddEntry(h9_sc, "40-60 GeV/#it{c}", "l");
    leg3_sc->AddEntry(h10_sc, "60-80 GeV/#it{c}", "l");
    leg3_sc->AddEntry(h11_sc, "80-100 GeV/#it{c}", "l");
    leg3_sc->AddEntry(h12_sc, "100-120 GeV/#it{c}", "l");
    leg3_sc->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hSplitZcut1E2C_sum_vs_tau_def2pi(i)_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h13_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi1_scaled");
    TH1F *h14_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi2_scaled");
    TH1F *h15_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi3_scaled");
    TH1F *h16_sc = (TH1F*)f->Get("hSplitZcut1E2C_sum_vs_tau_def2pi4_scaled");

    // Create canvas
    TCanvas *split_overlay_def2_scaled = new TCanvas("split_overlay_def2_scaled", "Overlaid Histograms", 800, 600);

    split_overlay_def2_scaled->SetLeftMargin(0.15);
    split_overlay_def2_scaled->SetBottomMargin(0.15);


    h13_sc->SetTitle("");
    h13_sc->GetXaxis()->SetTitleSize(0.07);
    h13_sc->GetYaxis()->SetTitleSize(0.05);

    split_overlay_def2_scaled->SetLogx();

    TH1F* split_hists2_sc[4] = {h13_sc, h14_sc, h15_sc, h16_sc};

    yScaling(split_hists2_sc,PtAverages);

    for (int i = 0; i < 4; ++i) {
        split_hists2_sc[i]->SetLineColor(colors[i]);
        split_hists2_sc[i]->SetMarkerColor(colors[i]);
        split_hists2_sc[i]->SetMarkerStyle(styles[i]);
        split_hists2_sc[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h13_sc->Draw("P");  // , E = errors
    h14_sc->Draw("P SAME");
    h15_sc->Draw("P SAME");
    h16_sc->Draw("P SAME");

    txtbox6->Draw();

    h13_sc->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");

    // Find the maximum value of all histograms
    double maxY4_sc = h13_sc->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax4_sc = split_hists2_sc[i]->GetMaximum();
        if (histMax4_sc > maxY4_sc) {
            maxY4_sc = histMax4_sc;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h13_sc->GetYaxis()->SetRangeUser(0, 1.2 * maxY4_sc);  // Add a little margin above the maximum value
 
    // Set the X-axis range for the histograms on h_overlay_def2
    //h13_sc->GetXaxis()->SetRangeUser(0, 50);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg4_sc = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg4_sc->AddEntry(h13_sc, "40-60 GeV/#it{c}", "l");
    leg4_sc->AddEntry(h14_sc, "60-80 GeV/#it{c}", "l");
    leg4_sc->AddEntry(h15_sc, "80-100 GeV/#it{c}", "l");
    leg4_sc->AddEntry(h16_sc, "100-120 GeV/#it{c}", "l");
    leg4_sc->Draw();


//---------------------------------------------------------------------------------
//Below we plot the same overlay for the EEC as a function of R_L
//---------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_dr12_pi(i)
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h1dr = (TH1F*)f->Get("hE2C_sum_vs_dr12_pi1");
    TH1F *h2dr = (TH1F*)f->Get("hE2C_sum_vs_dr12_pi2");
    TH1F *h3dr = (TH1F*)f->Get("hE2C_sum_vs_dr12_pi3");
    TH1F *h4dr = (TH1F*)f->Get("hE2C_sum_vs_dr12_pi4");

    // Create canvas
    TCanvas *h_overlay_dr = new TCanvas("h_overlay_dr", "Overlaid Histograms", 800, 600);

    h1dr->SetTitle("");
    h1dr->GetXaxis()->SetTitleSize(0.07);
    h1dr->GetYaxis()->SetTitleSize(0.05);
    h1dr->SetStats(0);

    h_overlay_dr->SetLogx();


    TH1F* hists_dr[4] = {h1dr, h2dr, h3dr, h4dr};

    for (int i = 0; i < 4; ++i) {
        hists_dr[i]->SetLineColor(colors[i]);
        hists_dr[i]->SetMarkerColor(colors[i]);
        hists_dr[i]->SetMarkerStyle(styles[i]);
        hists_dr[i]->SetMarkerSize(0.2);
    }


          // Draw the first histogram
    h1dr->Draw("P");  // 
    h2dr->Draw("P SAME");
    h3dr->Draw("P SAME");
    h4dr->Draw("P SAME");

    h1dr->GetYaxis()->SetTitle("#Sigma_{EEC}(R_{L})");

    // Find the maximum value of all histograms
    double maxYdr = h1dr->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMaxdr = hists_dr[i]->GetMaximum();
        if (histMaxdr > maxYdr) {
            maxYdr = histMaxdr;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1dr->GetYaxis()->SetRangeUser(0, 1.2 * maxYdr);  // Add a little margin above the maximum value


    // Add legend
    TLegend *legdr = new TLegend(0.7, 0.7, 0.89, 0.89);
    legdr->AddEntry(h1, "40-60 GeV/#it{c}", "l");
    legdr->AddEntry(h2, "60-80 GeV/#it{c}", "l");
    legdr->AddEntry(h3, "80-100 GeV/#it{c}", "l");
    legdr->AddEntry(h4, "100-120 GeV/#it{c}", "l");
    legdr->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_dr12_scaledpi(i)
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h1dr_sc = (TH1F*)f->Get("hE2C_sum_vs_dr12_scaledpi1");
    TH1F *h2dr_sc = (TH1F*)f->Get("hE2C_sum_vs_dr12_scaledpi2");
    TH1F *h3dr_sc = (TH1F*)f->Get("hE2C_sum_vs_dr12_scaledpi3");
    TH1F *h4dr_sc = (TH1F*)f->Get("hE2C_sum_vs_dr12_scaledpi4");

    // Create canvas
    TCanvas *h_overlay_dr_scaled = new TCanvas("h_overlay_dr_scaled", "Overlaid Histograms", 800, 600);

    h1dr_sc->SetTitle("");
    h1dr_sc->GetXaxis()->SetTitleSize(0.07);
    h1dr_sc->GetYaxis()->SetTitleSize(0.05);

    h_overlay_dr_scaled->SetLogx();


    TH1F* hists_dr_sc[4] = {h1dr_sc, h2dr_sc, h3dr_sc, h4dr_sc};

    yScaling(hists_dr_sc,PtAverages);

    double val2 = 0;
    for (int i = 0; i < 4; i++){
        int maxBin = hists_dr_sc[i]->GetMaximumBin();
        double xAtMax = hists_dr_sc[i]->GetXaxis()->GetBinCenter(maxBin);
        val2 += xAtMax;
    }

    cout << "x_peak is at " << val2/4 << endl;


    for (int i = 0; i < 4; ++i) {
        hists_dr_sc[i]->SetLineColor(colors[i]);
        hists_dr_sc[i]->SetMarkerColor(colors[i]);
        hists_dr_sc[i]->SetMarkerStyle(styles[i]);
        hists_dr_sc[i]->SetMarkerSize(0.2);
    }


          // Draw the first histogram
    h1dr_sc->Draw("P");  // 
    h2dr_sc->Draw("P SAME");
    h3dr_sc->Draw("P SAME");
    h4dr_sc->Draw("P SAME");

    h1dr_sc->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");

    // Find the maximum value of all histograms
    double maxYdr_sc = h1dr_sc->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMaxdr_sc = hists_dr_sc[i]->GetMaximum();
        if (histMaxdr_sc > maxYdr_sc) {
            maxYdr_sc = histMaxdr_sc;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1dr_sc->GetYaxis()->SetRangeUser(0, 1.2 * maxYdr_sc);  // Add a little margin above the maximum value

    TLine *line2 = new TLine(val2/4, h1dr_sc->GetMinimum(), val2/4, 1.2*maxYdr_sc);
    line2->SetLineColor(kGray+1);     // Customize color
    line2->SetLineWidth(2);        // Thicker line
    line2->SetLineStyle(1);        // Dashed, optional
    line2->Draw("same"); 


    // Add legend
    TLegend *legdr_sc = new TLegend(0.7, 0.7, 0.89, 0.89);
    legdr_sc->AddEntry(h1, "40-60 GeV/#it{c}", "l");
    legdr_sc->AddEntry(h2, "60-80 GeV/#it{c}", "l");
    legdr_sc->AddEntry(h3, "80-100 GeV/#it{c}", "l");
    legdr_sc->AddEntry(h4, "100-120 GeV/#it{c}", "l");
    legdr_sc->Draw();

//------------------------------------------------------------------------------------------
//Here we do the EEC's per R_L regime
//------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------
    //For R1
    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_R1
    //---------------------------------------------------------------------------------------
    gStyle->SetOptStat(0000000);
    //Retrieve Histograms
    TH1F *h1_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1_R1");
    TH1F *h2_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2_R1");
    TH1F *h3_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3_R1");
    TH1F *h4_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4_R1");

    // Create canvas
    TCanvas *h_overlay_def1_R1 = new TCanvas("h_overlay_def1_R1", "Overlaid Histograms", 800, 600);

    h_overlay_def1_R1->SetLeftMargin(0.15);
    h_overlay_def1_R1->SetBottomMargin(0.15);
    

    h1_R1->SetTitle("");
    h1_R1->GetXaxis()->SetTitleSize(0.07);
    h1_R1->GetYaxis()->SetTitleSize(0.05);
    h1_R1->SetStats(0);
    

    h_overlay_def1_R1->SetLogx();

    TH1F* hists_R1[4] = {h1_R1, h2_R1, h3_R1, h4_R1};

    for (int i = 0; i < 4; ++i) {
        hists_R1[i]->SetLineColor(colors[i]);
        hists_R1[i]->SetMarkerColor(colors[i]);
        hists_R1[i]->SetMarkerStyle(styles[i]);
        hists_R1[i]->SetMarkerSize(0.2);
    }


          // Draw the first histogram
    h1_R1->Draw("P");  // 
    h2_R1->Draw("P SAME");
    h3_R1->Draw("P SAME");
    h4_R1->Draw("P SAME");

    TPaveText *txtbox7 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox7->SetFillColor(0);     // Transparent
    txtbox7->SetBorderSize(0);    // Thin border
    txtbox7->SetTextFont(62);     // Standard font
    txtbox7->SetTextSize(0.03);

    
    txtbox7->AddText("Final State Hadron Pairs for #it{R_{L}} #in [0.01, 0.7 GeV/#it{c}/<#it{p}_{T}^{#it{ch jet}}>]");
    txtbox7->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox7->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox7->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox7->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox7->Draw();

    h1_R1->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");

    // Find the maximum value of all histograms
    double maxY_R1 = h1_R1->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax1_R1 = hists_R1[i]->GetMaximum();
        if (histMax1_R1 > maxY_R1) {
            maxY_R1 = histMax1_R1;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1_R1->GetYaxis()->SetRangeUser(0, 1.2 * maxY_R1);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg_R1 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_R1->AddEntry(h1_R1, "40-60 GeV/#it{c}", "l");
    leg_R1->AddEntry(h2_R1, "60-80 GeV/#it{c}", "l");
    leg_R1->AddEntry(h3_R1, "80-100 GeV/#it{c}", "l");
    leg_R1->AddEntry(h4_R1, "100-120 GeV/#it{c}", "l");
    leg_R1->Draw();

     //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2_R1
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1_def2_R1");
    TH1F *h6_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2_def2_R1");
    TH1F *h7_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3_def2_R1");
    TH1F *h8_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4_def2_R1");

    

    // Create canvas
    TCanvas *h_overlay_def2_R1 = new TCanvas("h_overlay_def2_R1", "Overlaid Histograms", 800, 600);

    h_overlay_def2_R1->SetLeftMargin(0.15);
    h_overlay_def2_R1->SetBottomMargin(0.15);

    h5_R1->SetTitle("");
    h5_R1->GetXaxis()->SetTitleSize(0.07);
    h5_R1->GetYaxis()->SetTitleSize(0.05);
    h5_R1->SetStats(0);

    h_overlay_def2_R1->SetLogx();

    TH1F* hists2_R1[4] = {h5_R1, h6_R1, h7_R1, h8_R1};

    for (int i = 0; i < 4; ++i) {
        hists2_R1[i]->SetLineColor(colors[i]);
        hists2_R1[i]->SetMarkerColor(colors[i]);
        hists2_R1[i]->SetMarkerStyle(styles[i]);
        hists2_R1[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h5_R1->Draw("P");  // , E = errors
    h6_R1->Draw("P SAME");
    h7_R1->Draw("P SAME");
    h8_R1->Draw("P SAME");

    TPaveText *txtbox8 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox8->SetFillColor(0);     // Transparent
    txtbox8->SetBorderSize(0);    // Thin border
    txtbox8->SetTextFont(62);     // Standard font
    txtbox8->SetTextSize(0.03);

    
    txtbox8->AddText("Final State Hadron Pairs for #it{R_{L}} #in [0.01, 0.7 GeV/#it{c}/<#it{p}_{T}^{#it{ch jet}}>]");
    txtbox8->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox8->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox8->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox8->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox8->Draw();

    h5_R1->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");



    // Find the maximum value of all histograms
    double maxY2_R1 = h5_R1->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2_R1 = hists2_R1[i]->GetMaximum();
        if (histMax2_R1 > maxY2_R1) {
            maxY2_R1 = histMax2_R1;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5_R1->GetYaxis()->SetRangeUser(0, 1.2 * maxY2_R1);  // Add a little margin above the maximum value
 
    // Set the X-axis range for the histograms on h_overlay_def2
    //h5->GetXaxis()->SetRangeUser(0, 1);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg2_R1 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_R1->AddEntry(h5_R1, "40-60 GeV/#it{c}", "l");
    leg2_R1->AddEntry(h6_R1, "60-80 GeV/#it{c}", "l");
    leg2_R1->AddEntry(h7_R1, "80-100 GeV/#it{c}", "l");
    leg2_R1->AddEntry(h8_R1, "100-120 GeV/#it{c}", "l");
    leg2_R1->Draw();

    
    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h1_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi1_R1");
    TH1F *h2_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi2_R1");
    TH1F *h3_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi3_R1");
    TH1F *h4_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi4_R1");

    // Create canvas
    TCanvas *h_overlay_def1_scaled_R1 = new TCanvas("h_overlay_def1_scaled_R1", "Overlaid of Scaled Histograms", 800, 600);

    h_overlay_def1_scaled_R1->SetLeftMargin(0.15);
    h_overlay_def1_scaled_R1->SetBottomMargin(0.15);

    h1_sc_R1->SetTitle("");
    h1_sc_R1->GetXaxis()->SetTitleSize(0.07);
    h1_sc_R1->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def1_scaled_R1->SetLogx();

    TH1F* hists_sc_R1[4] = {h1_sc_R1, h2_sc_R1, h3_sc_R1, h4_sc_R1};

    yScaling(hists_sc_R1,PtAverages);

    for (int i = 0; i < 4; ++i) {
        hists_sc_R1[i]->SetLineColor(colors[i]);
        hists_sc_R1[i]->SetMarkerColor(colors[i]);
        hists_sc_R1[i]->SetMarkerStyle(styles[i]);
        hists_sc_R1[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h1_sc_R1->Draw("P");  // 
    h2_sc_R1->Draw("P SAME");
    h3_sc_R1->Draw("P SAME");
    h4_sc_R1->Draw("P SAME");

    txtbox7->Draw();

    h1_sc_R1->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");

    

    // Find the maximum value of all histograms
    double maxY_sc_R1 = h1_sc_R1->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax_sc_R1 = hists_sc_R1[i]->GetMaximum();
        if (histMax_sc_R1 > maxY_sc_R1) {
            maxY_sc_R1 = histMax_sc_R1;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1_sc_R1->GetYaxis()->SetRangeUser(0, 1.2 * maxY_sc_R1);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg_sc_R1 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_sc_R1->AddEntry(h1_sc_R1, "40-60 GeV/#it{c}", "l");
    leg_sc_R1->AddEntry(h2_sc_R1, "60-80 GeV/#it{c}", "l");
    leg_sc_R1->AddEntry(h3_sc_R1, "80-100 GeV/#it{c}", "l");
    leg_sc_R1->AddEntry(h4_sc_R1, "100-120 GeV/#it{c}", "l");
    leg_sc_R1->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi1_def2_R1");
    TH1F *h6_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi2_def2_R1");
    TH1F *h7_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi3_def2_R1");
    TH1F *h8_sc_R1 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi4_def2_R1");

    // Create canvas
    TCanvas *h_overlay_def2_scaled_R1 = new TCanvas("h_overlay_def2_scaled_R1", "Overlaid Histograms", 800, 600);

    h_overlay_def2_scaled_R1->SetLeftMargin(0.15);
    h_overlay_def2_scaled_R1->SetBottomMargin(0.15);

    h5_sc_R1->SetTitle("");
    h5_sc_R1->GetXaxis()->SetTitleSize(0.07);
    h5_sc_R1->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def2_scaled_R1->SetLogx();

    TH1F* hists2_sc_R1[4] = {h5_sc_R1, h6_sc_R1, h7_sc_R1, h8_sc_R1};

    


    yScaling(hists2_sc_R1,PtAverages);

    for (int i = 0; i < 4; ++i) {
        hists2_sc_R1[i]->SetLineColor(colors[i]);
        hists2_sc_R1[i]->SetMarkerColor(colors[i]);
        hists2_sc_R1[i]->SetMarkerStyle(styles[i]);
        hists2_sc_R1[i]->SetMarkerSize(0.2);
    }

    // Draw the first histogram
    h5_sc_R1->Draw("P SAME"); 
    h6_sc_R1->Draw("P SAME");
    h7_sc_R1->Draw("P SAME");
    h8_sc_R1->Draw("P SAME");

    txtbox8->Draw();

    

    h5_sc_R1->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");


    // Find the maximum value of all histograms
    double maxY2_sc_R1 = h5_sc_R1->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2_sc_R1 = hists2_sc_R1[i]->GetMaximum();
        if (histMax2_sc_R1 > maxY2_sc_R1) {
            maxY2_sc_R1 = histMax2_sc_R1;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5_sc_R1->GetYaxis()->SetRangeUser(0, 1.2 * maxY2_sc_R1);  // Add a little margin above the maximum value

    // Set the X-axis range for the histograms on h_overlay_def2
    //h5_sc->GetXaxis()->SetRangeUser(0, 100);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg2_sc_R1 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_sc_R1->AddEntry(h5_sc_R1, "40-60 GeV/#it{c}", "l");
    leg2_sc_R1->AddEntry(h6_sc_R1, "60-80 GeV/#it{c}", "l");
    leg2_sc_R1->AddEntry(h7_sc_R1, "80-100 GeV/#it{c}", "l");
    leg2_sc_R1->AddEntry(h8_sc_R1, "100-120 GeV/#it{c}", "l");
    leg2_sc_R1->Draw();


    //---------------------------------------------------------------------------------------
    //For R2
    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_R2
    //---------------------------------------------------------------------------------------
    gStyle->SetOptStat(0000000);
    //Retrieve Histograms
    TH1F *h1_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1_R2");
    TH1F *h2_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2_R2");
    TH1F *h3_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3_R2");
    TH1F *h4_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4_R2");

    // Create canvas
    TCanvas *h_overlay_def1_R2 = new TCanvas("h_overlay_def1_R2", "Overlaid Histograms", 800, 600);

    h_overlay_def1_R2->SetLeftMargin(0.15);
    h_overlay_def1_R2->SetBottomMargin(0.15);


    h1_R2->SetTitle("");
    h1_R2->GetXaxis()->SetTitleSize(0.07);
    h1_R2->GetYaxis()->SetTitleSize(0.05);
    
    h1_R2->SetStats(0);
    

    h_overlay_def1_R2->SetLogx();

    TH1F* hists_R2[4] = {h1_R2, h2_R2, h3_R2, h4_R2};

    for (int i = 0; i < 4; ++i) {
        hists_R2[i]->SetLineColor(colors[i]);
        hists_R2[i]->SetMarkerColor(colors[i]);
        hists_R2[i]->SetMarkerStyle(styles[i]);
        hists_R2[i]->SetMarkerSize(0.2);
    }


          // Draw the first histogram
    h1_R2->Draw("P");  // 
    h2_R2->Draw("P SAME");
    h3_R2->Draw("P SAME");
    h4_R2->Draw("P SAME");

    TPaveText *txtbox9 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox9->SetFillColor(0);     // Transparent
    txtbox9->SetBorderSize(0);    // Thin border
    txtbox9->SetTextFont(62);     // Standard font
    txtbox9->SetTextSize(0.03);

    
    txtbox9->AddText("Final State Hadron Pairs for #it{R_{L}} #in [0.7, 12] GeV/#it{c}/<#it{p}_{T}^{#it{ch jet}}>");
    txtbox9->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox9->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox9->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox9->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox9->Draw();

    h1_R2->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");

    // Find the maximum value of all histograms
    double maxY_R2 = h1_R2->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax1_R2 = hists_R2[i]->GetMaximum();
        if (histMax1_R2 > maxY_R2) {
            maxY_R2 = histMax1_R2;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1_R2->GetYaxis()->SetRangeUser(0, 1.2 * maxY_R2);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg_R2 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_R2->AddEntry(h1_R2, "40-60 GeV/#it{c}", "l");
    leg_R2->AddEntry(h2_R2, "60-80 GeV/#it{c}", "l");
    leg_R2->AddEntry(h3_R2, "80-100 GeV/#it{c}", "l");
    leg_R2->AddEntry(h4_R2, "100-120 GeV/#it{c}", "l");
    leg_R2->Draw();

     //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2_R2
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1_def2_R2");
    TH1F *h6_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2_def2_R2");
    TH1F *h7_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3_def2_R2");
    TH1F *h8_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4_def2_R2");

    

    // Create canvas
    TCanvas *h_overlay_def2_R2 = new TCanvas("h_overlay_def2_R2", "Overlaid Histograms", 800, 600);

    h_overlay_def2_R2->SetLeftMargin(0.15);
    h_overlay_def2_R2->SetBottomMargin(0.15);

    h5_R2->SetTitle("");
    h5_R2->GetXaxis()->SetTitleSize(0.07);
    h5_R2->GetYaxis()->SetTitleSize(0.05);
    h5_R2->SetStats(0);

    h_overlay_def2_R2->SetLogx();

    TH1F* hists2_R2[4] = {h5_R2, h6_R2, h7_R2, h8_R2};

    for (int i = 0; i < 4; ++i) {
        hists2_R2[i]->SetLineColor(colors[i]);
        hists2_R2[i]->SetMarkerColor(colors[i]);
        hists2_R2[i]->SetMarkerStyle(styles[i]);
        hists2_R2[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h5_R2->Draw("P");  // , E = errors
    h6_R2->Draw("P SAME");
    h7_R2->Draw("P SAME");
    h8_R2->Draw("P SAME");

    TPaveText *txtbox10 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox10->SetFillColor(0);     // Transparent
    txtbox10->SetBorderSize(0);    // Thin border
    txtbox10->SetTextFont(62);     // Standard font
    txtbox10->SetTextSize(0.03);

    
    txtbox10->AddText("Final State Hadron Pairs for #it{R_{L}} #in [0.7, 12] GeV/#it{c}/<#it{p}_{T}^{#it{ch jet}}>");
    txtbox10->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox10->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox10->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox10->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox10->Draw();

    h5_R2->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");



    // Find the maximum value of all histograms
    double maxY2_R2 = h5_R2->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2_R2 = hists2_R2[i]->GetMaximum();
        if (histMax2_R2 > maxY2_R2) {
            maxY2_R2 = histMax2_R2;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5_R2->GetYaxis()->SetRangeUser(0, 1.2 * maxY2_R2);  // Add a little margin above the maximum value
 
    // Set the X-axis range for the histograms on h_overlay_def2
    //h5->GetXaxis()->SetRangeUser(0, 1);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg2_R2 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_R2->AddEntry(h5_R2, "40-60 GeV/#it{c}", "l");
    leg2_R2->AddEntry(h6_R2, "60-80 GeV/#it{c}", "l");
    leg2_R2->AddEntry(h7_R2, "80-100 GeV/#it{c}", "l");
    leg2_R2->AddEntry(h8_R2, "100-120 GeV/#it{c}", "l");
    leg2_R2->Draw();

    
    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h1_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi1_R2");
    TH1F *h2_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi2_R2");
    TH1F *h3_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi3_R2");
    TH1F *h4_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi4_R2");

    // Create canvas
    TCanvas *h_overlay_def1_scaled_R2 = new TCanvas("h_overlay_def1_scaled_R2", "Overlaid of Scaled Histograms", 800, 600);

    h_overlay_def1_scaled_R2->SetLeftMargin(0.15);
    h_overlay_def1_scaled_R2->SetBottomMargin(0.15);

    h1_sc_R2->SetTitle("");
    h1_sc_R2->GetXaxis()->SetTitleSize(0.07);
    h1_sc_R2->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def1_scaled_R2->SetLogx();

    TH1F* hists_sc_R2[4] = {h1_sc_R2, h2_sc_R2, h3_sc_R2, h4_sc_R2};

    yScaling(hists_sc_R2,PtAverages);

    for (int i = 0; i < 4; ++i) {
        hists_sc_R2[i]->SetLineColor(colors[i]);
        hists_sc_R2[i]->SetMarkerColor(colors[i]);
        hists_sc_R2[i]->SetMarkerStyle(styles[i]);
        hists_sc_R2[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h1_sc_R2->Draw("P");  // 
    h2_sc_R2->Draw("P SAME");
    h3_sc_R2->Draw("P SAME");
    h4_sc_R2->Draw("P SAME");

    txtbox9->Draw();

    h1_sc_R2->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");

    

    // Find the maximum value of all histograms
    double maxY_sc_R2 = h1_sc_R2->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax_sc_R2 = hists_sc_R2[i]->GetMaximum();
        if (histMax_sc_R2 > maxY_sc_R2) {
            maxY_sc_R2 = histMax_sc_R2;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1_sc_R2->GetYaxis()->SetRangeUser(0, 1.2 * maxY_sc_R2);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg_sc_R2 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_sc_R2->AddEntry(h1_sc_R2, "40-60 GeV/#it{c}", "l");
    leg_sc_R2->AddEntry(h2_sc_R2, "60-80 GeV/#it{c}", "l");
    leg_sc_R2->AddEntry(h3_sc_R2, "80-100 GeV/#it{c}", "l");
    leg_sc_R2->AddEntry(h4_sc_R2, "100-120 GeV/#it{c}", "l");
    leg_sc_R2->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi1_def2_R2");
    TH1F *h6_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi2_def2_R2");
    TH1F *h7_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi3_def2_R2");
    TH1F *h8_sc_R2 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi4_def2_R2");

    // Create canvas
    TCanvas *h_overlay_def2_scaled_R2 = new TCanvas("h_overlay_def2_scaled_R2", "Overlaid Histograms", 800, 600);

    h_overlay_def2_scaled_R2->SetLeftMargin(0.15);
    h_overlay_def2_scaled_R2->SetBottomMargin(0.15);

    h5_sc_R2->SetTitle("");
    h5_sc_R2->GetXaxis()->SetTitleSize(0.07);
    h5_sc_R2->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def2_scaled_R2->SetLogx();

    TH1F* hists2_sc_R2[4] = {h5_sc_R2, h6_sc_R2, h7_sc_R2, h8_sc_R2};

    yScaling(hists2_sc_R2,PtAverages);

    for (int i = 0; i < 4; ++i) {
        hists2_sc_R2[i]->SetLineColor(colors[i]);
        hists2_sc_R2[i]->SetMarkerColor(colors[i]);
        hists2_sc_R2[i]->SetMarkerStyle(styles[i]);
        hists2_sc_R2[i]->SetMarkerSize(0.2);
    }

    // Draw the first histogram
    h5_sc_R2->Draw("P SAME"); 
    h6_sc_R2->Draw("P SAME");
    h7_sc_R2->Draw("P SAME");
    h8_sc_R2->Draw("P SAME");

    txtbox10->Draw();

    

    h5_sc_R2->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");


    // Find the maximum value of all histograms
    double maxY2_sc_R2 = h5_sc_R2->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2_sc_R2 = hists2_sc_R2[i]->GetMaximum();
        if (histMax2_sc_R2 > maxY2_sc_R2) {
            maxY2_sc_R2 = histMax2_sc_R2;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5_sc_R2->GetYaxis()->SetRangeUser(0, 1.2 * maxY2_sc_R2);  // Add a little margin above the maximum value

    // Set the X-axis range for the histograms on h_overlay_def2
    //h5_sc->GetXaxis()->SetRangeUser(0, 100);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg2_sc_R2 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_sc_R2->AddEntry(h5_sc_R2, "40-60 GeV/#it{c}", "l");
    leg2_sc_R2->AddEntry(h6_sc_R2, "60-80 GeV/#it{c}", "l");
    leg2_sc_R2->AddEntry(h7_sc_R2, "80-100 GeV/#it{c}", "l");
    leg2_sc_R2->AddEntry(h8_sc_R2, "100-120 GeV/#it{c}", "l");
    leg2_sc_R2->Draw();


    //---------------------------------------------------------------------------------------
    //For R3
    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_R3
    //---------------------------------------------------------------------------------------
    gStyle->SetOptStat(0000000);
    //Retrieve Histograms
    TH1F *h1_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1_R3");
    TH1F *h2_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2_R3");
    TH1F *h3_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3_R3");
    TH1F *h4_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4_R3");

    // Create canvas
    TCanvas *h_overlay_def1_R3 = new TCanvas("h_overlay_def1_R3", "Overlaid Histograms", 800, 600);

    h_overlay_def1_R3->SetLeftMargin(0.15);
    h_overlay_def1_R3->SetBottomMargin(0.15);


    h1_R3->SetTitle("");
    h1_R3->GetXaxis()->SetTitleSize(0.07);
    h1_R3->GetYaxis()->SetTitleSize(0.05);
    h1_R3->SetStats(0);
    

    h_overlay_def1_R3->SetLogx();

    TH1F* hists_R3[4] = {h1_R3, h2_R3, h3_R3, h4_R3};

    for (int i = 0; i < 4; ++i) {
        hists_R3[i]->SetLineColor(colors[i]);
        hists_R3[i]->SetMarkerColor(colors[i]);
        hists_R3[i]->SetMarkerStyle(styles[i]);
        hists_R3[i]->SetMarkerSize(0.2);
    }


          // Draw the first histogram
    h1_R3->Draw("P");  // 
    h2_R3->Draw("P SAME");
    h3_R3->Draw("P SAME");
    h4_R3->Draw("P SAME");

    TPaveText *txtbox11 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox11->SetFillColor(0);     // Transparent
    txtbox11->SetBorderSize(0);    // Thin border
    txtbox11->SetTextFont(62);     // Standard font
    txtbox11->SetTextSize(0.03);

    
    txtbox11->AddText("Final State Hadron Pairs for #it{R_{L}} #in [12 GeV/#it{c}/<#it{p}_{T}^{#it{ch jet}}>, 0.4]");
    txtbox11->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox11->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox11->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox11->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox11->Draw();

    h1_R3->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");

    // Find the maximum value of all histograms
    double maxY_R3 = h1_R3->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax1_R3 = hists_R3[i]->GetMaximum();
        if (histMax1_R3 > maxY_R3) {
            maxY_R3 = histMax1_R3;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1_R3->GetYaxis()->SetRangeUser(0, 1.2 * maxY_R3);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg_R3 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_R3->AddEntry(h1_R3, "40-60 GeV/#it{c}", "l");
    leg_R3->AddEntry(h2_R3, "60-80 GeV/#it{c}", "l");
    leg_R3->AddEntry(h3_R3, "80-100 GeV/#it{c}", "l");
    leg_R3->AddEntry(h4_R3, "100-120 GeV/#it{c}", "l");
    leg_R3->Draw();

     //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2_R3
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi1_def2_R3");
    TH1F *h6_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi2_def2_R3");
    TH1F *h7_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi3_def2_R3");
    TH1F *h8_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_pi4_def2_R3");

    

    // Create canvas
    TCanvas *h_overlay_def2_R3 = new TCanvas("h_overlay_def2_R3", "Overlaid Histograms", 800, 600);

    h_overlay_def2_R3->SetLeftMargin(0.15);
    h_overlay_def2_R3->SetBottomMargin(0.15);

    h5_R3->SetTitle("");
    h5_R3->GetXaxis()->SetTitleSize(0.07);
    h5_R3->GetYaxis()->SetTitleSize(0.05);
    h5_R3->SetStats(0);

    h_overlay_def2_R3->SetLogx();

    TH1F* hists2_R3[4] = {h5_R3, h6_R3, h7_R3, h8_R3};

    for (int i = 0; i < 4; ++i) {
        hists2_R3[i]->SetLineColor(colors[i]);
        hists2_R3[i]->SetMarkerColor(colors[i]);
        hists2_R3[i]->SetMarkerStyle(styles[i]);
        hists2_R3[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h5_R3->Draw("P");  // , E = errors
    h6_R3->Draw("P SAME");
    h7_R3->Draw("P SAME");
    h8_R3->Draw("P SAME");

    TPaveText *txtbox12 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox12->SetFillColor(0);     // Transparent
    txtbox12->SetBorderSize(0);    // Thin border
    txtbox12->SetTextFont(62);     // Standard font
    txtbox12->SetTextSize(0.03);

    
    txtbox12->AddText("Final State Hadron Pairs for #it{R_{L}} #in [12 GeV/#it{c}/<#it{p}_{T}^{#it{ch jet}}>, 0.4]");
    txtbox12->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox12->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox12->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox12->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox12->Draw();

    h5_R3->GetYaxis()->SetTitle("#Sigma_{EEC}(#tau_{f})");



    // Find the maximum value of all histograms
    double maxY2_R3 = h5_R3->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2_R3 = hists2_R3[i]->GetMaximum();
        if (histMax2_R3 > maxY2_R3) {
            maxY2_R3 = histMax2_R3;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5_R3->GetYaxis()->SetRangeUser(0, 1.2 * maxY2_R3);  // Add a little margin above the maximum value
 
    // Set the X-axis range for the histograms on h_overlay_def2
    //h5->GetXaxis()->SetRangeUser(0, 1);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg2_R3 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_R3->AddEntry(h5_R3, "40-60 GeV/#it{c}", "l");
    leg2_R3->AddEntry(h6_R3, "60-80 GeV/#it{c}", "l");
    leg2_R3->AddEntry(h7_R3, "80-100 GeV/#it{c}", "l");
    leg2_R3->AddEntry(h8_R3, "100-120 GeV/#it{c}", "l");
    leg2_R3->Draw();

    
    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h1_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi1_R3");
    TH1F *h2_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi2_R3");
    TH1F *h3_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi3_R3");
    TH1F *h4_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi4_R3");

    // Create canvas
    TCanvas *h_overlay_def1_scaled_R3 = new TCanvas("h_overlay_def1_scaled_R3", "Overlaid of Scaled Histograms", 800, 600);

    h_overlay_def1_scaled_R3->SetLeftMargin(0.15);
    h_overlay_def1_scaled_R3->SetBottomMargin(0.15);

    h1_sc_R3->SetTitle("");
    h1_sc_R3->GetXaxis()->SetTitleSize(0.07);
    h1_sc_R3->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def1_scaled_R3->SetLogx();

    TH1F* hists_sc_R3[4] = {h1_sc_R3, h2_sc_R3, h3_sc_R3, h4_sc_R3};

    yScaling(hists_sc_R3,PtAverages);

    for (int i = 0; i < 4; ++i) {
        hists_sc_R3[i]->SetLineColor(colors[i]);
        hists_sc_R3[i]->SetMarkerColor(colors[i]);
        hists_sc_R3[i]->SetMarkerStyle(styles[i]);
        hists_sc_R3[i]->SetMarkerSize(0.2);
    }

          // Draw the first histogram
    h1_sc_R3->Draw("P");  // 
    h2_sc_R3->Draw("P SAME");
    h3_sc_R3->Draw("P SAME");
    h4_sc_R3->Draw("P SAME");

    txtbox11->Draw();

    h1_sc_R3->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");

    

    // Find the maximum value of all histograms
    double maxY_sc_R3 = h1_sc_R3->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax_sc_R3 = hists_sc_R3[i]->GetMaximum();
        if (histMax_sc_R3 > maxY_sc_R3) {
            maxY_sc_R3 = histMax_sc_R3;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h1_sc_R3->GetYaxis()->SetRangeUser(0, 1.2 * maxY_sc_R3);  // Add a little margin above the maximum value


    // Add legend
    TLegend *leg_sc_R3 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_sc_R3->AddEntry(h1_sc_R3, "40-60 GeV/#it{c}", "l");
    leg_sc_R3->AddEntry(h2_sc_R3, "60-80 GeV/#it{c}", "l");
    leg_sc_R3->AddEntry(h3_sc_R3, "80-100 GeV/#it{c}", "l");
    leg_sc_R3->AddEntry(h4_sc_R3, "100-120 GeV/#it{c}", "l");
    leg_sc_R3->Draw();

    //---------------------------------------------------------------------------------------
    //Overlap of hE2C_sum_vs_tau_pi(i)_def2_scaled
    //---------------------------------------------------------------------------------------

    //Retrieve Histograms
    TH1F *h5_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi1_def2_R3");
    TH1F *h6_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi2_def2_R3");
    TH1F *h7_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi3_def2_R3");
    TH1F *h8_sc_R3 = (TH1F*)f->Get("hE2C_sum_vs_tau_scaledpi4_def2_R3");

    // Create canvas
    TCanvas *h_overlay_def2_scaled_R3 = new TCanvas("h_overlay_def2_scaled_R3", "Overlaid Histograms", 800, 600);

    h_overlay_def2_scaled_R3->SetLeftMargin(0.15);
    h_overlay_def2_scaled_R3->SetBottomMargin(0.15);

    h5_sc_R3->SetTitle("");
    h5_sc_R3->GetXaxis()->SetTitleSize(0.07);
    h5_sc_R3->GetYaxis()->SetTitleSize(0.05);

    h_overlay_def2_scaled_R3->SetLogx();

    TH1F* hists2_sc_R3[4] = {h5_sc_R3, h6_sc_R3, h7_sc_R3, h8_sc_R3};

    


    yScaling(hists2_sc_R3,PtAverages);

    for (int i = 0; i < 4; ++i) {
        hists2_sc_R3[i]->SetLineColor(colors[i]);
        hists2_sc_R3[i]->SetMarkerColor(colors[i]);
        hists2_sc_R3[i]->SetMarkerStyle(styles[i]);
        hists2_sc_R3[i]->SetMarkerSize(0.2);
    }

    // Draw the first histogram
    h5_sc_R3->Draw("P SAME"); 
    h6_sc_R3->Draw("P SAME");
    h7_sc_R3->Draw("P SAME");
    h8_sc_R3->Draw("P SAME");

    txtbox12->Draw();

    

    h5_sc_R3->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((GeV/#it{c})^{-1})");


    // Find the maximum value of all histograms
    double maxY2_sc_R3 = h5_sc_R3->GetMaximum();
    for (int i = 1; i < 4; ++i) {
        double histMax2_sc_R3 = hists2_sc_R3[i]->GetMaximum();
        if (histMax2_sc_R3 > maxY2_sc_R3) {
            maxY2_sc_R3 = histMax2_sc_R3;
        }
    }

    // Set the Y-axis range to ensure all histograms fit
    h5_sc_R3->GetYaxis()->SetRangeUser(0, 1.2 * maxY2_sc_R3);  // Add a little margin above the maximum value

    // Set the X-axis range for the histograms on h_overlay_def2
    //h5_sc->GetXaxis()->SetRangeUser(0, 100);  // Set x-axis range (adjust maximum as needed)

    // Add legend
    TLegend *leg2_sc_R3 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_sc_R3->AddEntry(h5_sc_R3, "40-60 GeV/#it{c}", "l");
    leg2_sc_R3->AddEntry(h6_sc_R3, "60-80 GeV/#it{c}", "l");
    leg2_sc_R3->AddEntry(h7_sc_R3, "80-100 GeV/#it{c}", "l");
    leg2_sc_R3->AddEntry(h8_sc_R3, "100-120 GeV/#it{c}", "l");
    leg2_sc_R3->Draw();

//-----------------------------------------------------------------------
// Here I make a plot of a energy scale of R1-R3
//-----------------------------------------------------------------------
 /*
// Create canvas
    TCanvas *h_overlay_R1to3_1 = new TCanvas("h_overlay_R1to3_1", "Overlaid Histograms", 800, 600);

    h_overlay_R1to3_1->SetLeftMargin(0.15);
    h_overlay_R1to3_1->SetBottomMargin(0.15);

    h_overlay_R1to3_1->SetLogx();

    h_overlay_R1to3_1->cd();

    
    h1_R1->SetLineColor(colors[1]);
    h1_R2->SetLineColor(colors[2]);
    h1_R3->SetLineColor(colors[3]);

    h1_R1->SetMarkerColor(colors[1]);
    h1_R2->SetMarkerColor(colors[2]);
    h1_R3->SetMarkerColor(colors[3]);

    

    // Draw the first histogram
    h1_R3->Draw("P" );
    h1_R1->Draw("P SAME"); 
    h1_R2->Draw("P SAME");



    // Add legend
    TLegend *leg_R1to3_1 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg_R1to3_1->AddEntry(h1_R1, "small R_{L} range", "l");
    leg_R1to3_1->AddEntry(h1_R2, "intermediate R_{L} range", "l");
    leg_R1to3_1->AddEntry(h1_R3, "large R_{L} range", "l");
    leg_R1to3_1->Draw();

    h_overlay_R1to3_1->Update();

    */

    //-----------------------------------------------------------------------
    //Here we write it all out to a ROOT File called OverlayPlot.root
    //-----------------------------------------------------------------------

    TFile *fout;
    fout = new TFile("OverlayPlot.root","RECREATE");

    h_overlay_def1->Write();
    h_overlay_def2->Write();
    h_overlay_def1_scaled->Write();
    h_overlay_def2_scaled->Write();

    split_overlay_def1->Write();
    split_overlay_def2->Write();
    split_overlay_def1_scaled->Write();
    split_overlay_def2_scaled->Write();

    h_overlay_dr->Write();
    h_overlay_dr_scaled->Write();

    h_overlay_def1_R1->Write();
    h_overlay_def2_R1->Write();
    h_overlay_def1_scaled_R1->Write();
    h_overlay_def2_scaled_R1->Write();

    h_overlay_def1_R2->Write();
    h_overlay_def2_R2->Write();
    h_overlay_def1_scaled_R2->Write();
    h_overlay_def2_scaled_R2->Write();

    h_overlay_def1_R3->Write();
    h_overlay_def2_R3->Write();
    h_overlay_def1_scaled_R3->Write();
    h_overlay_def2_scaled_R3->Write();



    fout->Write();
    fout->Close();


}
