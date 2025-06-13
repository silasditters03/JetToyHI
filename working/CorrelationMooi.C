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

void CorrelationMooi(TString strIn = "JetToyResults.root") {


    TFile *f = new TFile(strIn.Data());

    TH2D *h1 = (TH2D*)f->Get("h_correlation_tau_RL_pi1_w1");
    TH2D *h2 = (TH2D*)f->Get("h_correlation_tau_RL_pi2_w1");
    TH2D *h3 = (TH2D*)f->Get("h_correlation_tau_RL_pi3_w1");
    TH2D *h4 = (TH2D*)f->Get("h_correlation_tau_RL_pi4_w1");
    TH2D *h5 = (TH2D*)f->Get("h_correlation_tau_RL_pi1_wEEC");
    TH2D *h6 = (TH2D*)f->Get("h_correlation_tau_RL_pi2_wEEC");
    TH2D *h7 = (TH2D*)f->Get("h_correlation_tau_RL_pi3_wEEC");
    TH2D *h8 = (TH2D*)f->Get("h_correlation_tau_RL_pi4_wEEC");
    TH2D *h9 = (TH2D*)f->Get("h_correlation_tau_RL_pi1_w1_def2");
    TH2D *h10 = (TH2D*)f->Get("h_correlation_tau_RL_pi2_w1_def2");
    TH2D *h11 = (TH2D*)f->Get("h_correlation_tau_RL_pi3_w1_def2");
    TH2D *h12 = (TH2D*)f->Get("h_correlation_tau_RL_pi4_w1_def2");
    TH2D *h13 = (TH2D*)f->Get("h_correlation_tau_RL_pi1_wEEC_def2");
    TH2D *h14 = (TH2D*)f->Get("h_correlation_tau_RL_pi2_wEEC_def2");
    TH2D *h15 = (TH2D*)f->Get("h_correlation_tau_RL_pi3_wEEC_def2");
    TH2D *h16 = (TH2D*)f->Get("h_correlation_tau_RL_pi4_wEEC_def2");

    TH2D* hists[16] = {h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,h13,h14,h15,h16};

    for (int i = 0; i < 16; i++) {

        hists[i]->GetYaxis()->SetTitle("#it{R_{L}} (rad)");
    }

//--------------------------------------------------------------------
//  FOR DEF1 W=1
//--------------------------------------------------------------------

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi1_w1
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi1_w1 = new TCanvas("h_correlation_tau_RL_pi1_w1", "Correlations", 800, 600);

    h_correlation_tau_RL_pi1_w1->cd();

    h1->GetXaxis()->SetTitleSize(0.07);
    h1->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi1_w1->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi1_w1->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi1_w1->SetLogz();
    h_correlation_tau_RL_pi1_w1->SetLogx();

    h1->Draw("COLZ");

    TPaveText *txtbox1 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox1->SetFillColor(0);     // Transparent
    txtbox1->SetBorderSize(0);    // Thin border
    txtbox1->SetTextFont(62);     // Standard font
    txtbox1->SetTextSize(0.03);

    
    txtbox1->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox1->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox1->AddText("40 < #it{p}_{T} < 60 GeV/#it{c}, w = 1");
    txtbox1->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox1->Draw();

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi2_w1
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi2_w1 = new TCanvas("h_correlation_tau_RL_pi2_w1", "Correlations", 800, 600);

    h_correlation_tau_RL_pi2_w1->cd();

    h2->GetXaxis()->SetTitleSize(0.07);
    h2->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi2_w1->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi2_w1->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi2_w1->SetLogz();
    h_correlation_tau_RL_pi2_w1->SetLogx();

    h2->Draw("COLZ");

    TPaveText *txtbox2 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox2->SetFillColor(0);     // Transparent
    txtbox2->SetBorderSize(0);    // Thin border
    txtbox2->SetTextFont(62);     // Standard font
    txtbox2->SetTextSize(0.03);

    
    txtbox2->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox2->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox2->AddText("60 < #it{p}_{T} < 80 GeV/#it{c}, w = 1");
    txtbox2->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox2->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi3_w1
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi3_w1 = new TCanvas("h_correlation_tau_RL_pi3_w1", "Correlations", 800, 600);

    h_correlation_tau_RL_pi3_w1->cd();

    h3->GetXaxis()->SetTitleSize(0.07);
    h3->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi3_w1->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi3_w1->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi3_w1->SetLogz();
    h_correlation_tau_RL_pi3_w1->SetLogx();

    h3->Draw("COLZ");

    TPaveText *txtbox3 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox3->SetFillColor(0);     // Transparent
    txtbox3->SetBorderSize(0);    // Thin border
    txtbox3->SetTextFont(62);     // Standard font
    txtbox3->SetTextSize(0.03);

    
    txtbox3->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox3->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox3->AddText("80 < #it{p}_{T} < 100 GeV/#it{c}, w = 1");
    txtbox3->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox3->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi4_w1
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi4_w1 = new TCanvas("h_correlation_tau_RL_pi4_w1", "Correlations", 800, 600);

    h_correlation_tau_RL_pi4_w1->cd();

    h4->GetXaxis()->SetTitleSize(0.07);
    h4->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi4_w1->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi4_w1->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi4_w1->SetLogz();
    h_correlation_tau_RL_pi4_w1->SetLogx();

    h4->Draw("COLZ");

    TPaveText *txtbox4 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox4->SetFillColor(0);     // Transparent
    txtbox4->SetBorderSize(0);    // Thin border
    txtbox4->SetTextFont(62);     // Standard font
    txtbox4->SetTextSize(0.03);

    
    txtbox4->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox4->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox4->AddText("100 < #it{p}_{T} < 120 GeV/#it{c}, w = 1");
    txtbox4->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox4->Draw();

//--------------------------------------------------------------------
//  FOR DEF1 W=EEC
//--------------------------------------------------------------------

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi1_wEEC
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi1_wEEC = new TCanvas("h_correlation_tau_RL_pi1_wEEC", "Correlations", 800, 600);

    h_correlation_tau_RL_pi1_wEEC->cd();

    h5->GetXaxis()->SetTitleSize(0.07);
    h6->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi1_wEEC->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi1_wEEC->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi1_wEEC->SetLogz();
    h_correlation_tau_RL_pi1_wEEC->SetLogx();

    h5->Draw("COLZ");

    TPaveText *txtbox5 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox5->SetFillColor(0);     // Transparent
    txtbox5->SetBorderSize(0);    // Thin border
    txtbox5->SetTextFont(62);     // Standard font
    txtbox5->SetTextSize(0.03);

    
    txtbox5->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox5->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox5->AddText("40 < #it{p}_{T} < 60 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox5->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox5->Draw();

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi2_wEEC
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi2_wEEC = new TCanvas("h_correlation_tau_RL_pi2_wEEC", "Correlations", 800, 600);

    h_correlation_tau_RL_pi2_wEEC->cd();

    h6->GetXaxis()->SetTitleSize(0.07);
    h6->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi2_wEEC->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi2_wEEC->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi2_wEEC->SetLogz();
    h_correlation_tau_RL_pi2_wEEC->SetLogx();

    h6->Draw("COLZ");

    TPaveText *txtbox6 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox6->SetFillColor(0);     // Transparent
    txtbox6->SetBorderSize(0);    // Thin border
    txtbox6->SetTextFont(62);     // Standard font
    txtbox6->SetTextSize(0.03);

    
    txtbox6->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox6->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox6->AddText("60 < #it{p}_{T} < 80 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox6->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox6->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi3_wEEC
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi3_wEEC = new TCanvas("h_correlation_tau_RL_pi3_wEEC", "Correlations", 800, 600);

    h_correlation_tau_RL_pi3_wEEC->cd();

    h7->GetXaxis()->SetTitleSize(0.07);
    h7->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi3_wEEC->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi3_wEEC->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi3_wEEC->SetLogz();
    h_correlation_tau_RL_pi3_wEEC->SetLogx();

    h7->Draw("COLZ");

    TPaveText *txtbox7 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox7->SetFillColor(0);     // Transparent
    txtbox7->SetBorderSize(0);    // Thin border
    txtbox7->SetTextFont(62);     // Standard font
    txtbox7->SetTextSize(0.03);

    
    txtbox7->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox7->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox7->AddText("80 < #it{p}_{T} < 100 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox7->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox7->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi4_wEEC
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi4_wEEC = new TCanvas("h_correlation_tau_RL_pi4_wEEC", "Correlations", 800, 600);

    h_correlation_tau_RL_pi4_wEEC->cd();

    h8->GetXaxis()->SetTitleSize(0.07);
    h8->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi4_wEEC->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi4_wEEC->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi4_wEEC->SetLogz();
    h_correlation_tau_RL_pi4_wEEC->SetLogx();

    h8->Draw("COLZ");

    TPaveText *txtbox8 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox8->SetFillColor(0);     // Transparent
    txtbox8->SetBorderSize(0);    // Thin border
    txtbox8->SetTextFont(62);     // Standard font
    txtbox8->SetTextSize(0.03);

    
    txtbox8->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox8->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox8->AddText("100 < #it{p}_{T} < 120 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox8->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox8->Draw();

//--------------------------------------------------------------------
//  FOR DEF2 W=1
//--------------------------------------------------------------------

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi1_w1_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi1_w1_def2 = new TCanvas("h_correlation_tau_RL_pi1_w1_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi1_w1_def2->cd();

    h9->GetXaxis()->SetTitleSize(0.07);
    h9->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi1_w1_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi1_w1_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi1_w1_def2->SetLogz();
    h_correlation_tau_RL_pi1_w1_def2->SetLogx();

    h9->Draw("COLZ");

    TPaveText *txtbox9 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox9->SetFillColor(0);     // Transparent
    txtbox9->SetBorderSize(0);    // Thin border
    txtbox9->SetTextFont(62);     // Standard font
    txtbox9->SetTextSize(0.03);

    
    txtbox9->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox9->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox9->AddText("40 < #it{p}_{T} < 60 GeV/#it{c}, w = 1");
    txtbox9->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox9->Draw();

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi2_w1_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi2_w1_def2 = new TCanvas("h_correlation_tau_RL_pi2_w1_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi2_w1_def2->cd();

    h10->GetXaxis()->SetTitleSize(0.07);
    h10->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi2_w1_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi2_w1_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi2_w1_def2->SetLogz();
    h_correlation_tau_RL_pi2_w1_def2->SetLogx();

    h10->Draw("COLZ");

    TPaveText *txtbox10 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox10->SetFillColor(0);     // Transparent
    txtbox10->SetBorderSize(0);    // Thin border
    txtbox10->SetTextFont(62);     // Standard font
    txtbox10->SetTextSize(0.03);

    
    txtbox10->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox10->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox10->AddText("60 < #it{p}_{T} < 80 GeV/#it{c}, w = 1");
    txtbox10->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox10->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi3_w1_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi3_w1_def2 = new TCanvas("h_correlation_tau_RL_pi3_w1_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi3_w1_def2->cd();

    h11->GetXaxis()->SetTitleSize(0.07);
    h11->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi3_w1_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi3_w1_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi3_w1_def2->SetLogz();
    h_correlation_tau_RL_pi3_w1_def2->SetLogx();

    h11->Draw("COLZ");

    TPaveText *txtbox11 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox11->SetFillColor(0);     // Transparent
    txtbox11->SetBorderSize(0);    // Thin border
    txtbox11->SetTextFont(62);     // Standard font
    txtbox11->SetTextSize(0.03);

    
    txtbox11->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox11->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox11->AddText("80 < #it{p}_{T} < 100 GeV/#it{c}, w = 1");
    txtbox11->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox11->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi4_w1_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi4_w1_def2 = new TCanvas("h_correlation_tau_RL_pi4_w1_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi4_w1_def2->cd();

    h12->GetXaxis()->SetTitleSize(0.07);
    h12->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi4_w1_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi4_w1_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi4_w1_def2->SetLogz();
    h_correlation_tau_RL_pi4_w1_def2->SetLogx();

    h12->Draw("COLZ");

    TPaveText *txtbox12 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox12->SetFillColor(0);     // Transparent
    txtbox12->SetBorderSize(0);    // Thin border
    txtbox12->SetTextFont(62);     // Standard font
    txtbox12->SetTextSize(0.03);

    
    txtbox12->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox12->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox12->AddText("100 < #it{p}_{T} < 120 GeV/#it{c}, w = 1");
    txtbox12->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox12->Draw();

//--------------------------------------------------------------------
//  FOR DEF2 W=EEC
//--------------------------------------------------------------------

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi1_wEEC_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi1_wEEC_def2 = new TCanvas("h_correlation_tau_RL_pi1_wEEC_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi1_wEEC_def2->cd();

    h13->GetXaxis()->SetTitleSize(0.07);
    h13->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi1_wEEC_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi1_wEEC_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi1_wEEC_def2->SetLogz();
    h_correlation_tau_RL_pi1_wEEC_def2->SetLogx();

    h13->Draw("COLZ");

    TPaveText *txtbox13 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox13->SetFillColor(0);     // Transparent
    txtbox13->SetBorderSize(0);    // Thin border
    txtbox13->SetTextFont(62);     // Standard font
    txtbox13->SetTextSize(0.03);

    
    txtbox13->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox13->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox13->AddText("40 < #it{p}_{T} < 60 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox13->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox13->Draw();

    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi2_wEEC_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi2_wEEC_def2 = new TCanvas("h_correlation_tau_RL_pi2_wEEC_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi2_wEEC_def2->cd();

    h14->GetXaxis()->SetTitleSize(0.07);
    h14->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi2_wEEC_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi2_wEEC_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi2_wEEC_def2->SetLogz();
    h_correlation_tau_RL_pi2_wEEC_def2->SetLogx();

    h14->Draw("COLZ");

    TPaveText *txtbox14 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox14->SetFillColor(0);     // Transparent
    txtbox14->SetBorderSize(0);    // Thin border
    txtbox14->SetTextFont(62);     // Standard font
    txtbox14->SetTextSize(0.03);

    
    txtbox14->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox14->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox14->AddText("60 < #it{p}_{T} < 80 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox14->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox14->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi3_wEEC_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi3_wEEC_def2 = new TCanvas("h_correlation_tau_RL_pi3_wEEC_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi3_wEEC_def2->cd();

    h15->GetXaxis()->SetTitleSize(0.07);
    h15->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi3_wEEC_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi3_wEEC_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi3_wEEC_def2->SetLogz();
    h_correlation_tau_RL_pi3_wEEC_def2->SetLogx();

    h15->Draw("COLZ");

    TPaveText *txtbox15 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox15->SetFillColor(0);     // Transparent
    txtbox15->SetBorderSize(0);    // Thin border
    txtbox15->SetTextFont(62);     // Standard font
    txtbox15->SetTextSize(0.03);

    
    txtbox15->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox15->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox15->AddText("80 < #it{p}_{T} < 100 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox15->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox15->Draw();


    //--------------------------------------------------------------------
    //  h_correlation_tau_RL_pi4_wEEC_def2
    //--------------------------------------------------------------------


    TCanvas *h_correlation_tau_RL_pi4_wEEC_def2 = new TCanvas("h_correlation_tau_RL_pi4_wEEC_def2", "Correlations", 800, 600);

    h_correlation_tau_RL_pi4_wEEC_def2->cd();

    h16->GetXaxis()->SetTitleSize(0.07);
    h16->GetYaxis()->SetTitleSize(0.07);

    h_correlation_tau_RL_pi4_wEEC_def2->SetLeftMargin(0.15);
    h_correlation_tau_RL_pi4_wEEC_def2->SetBottomMargin(0.15);

    h_correlation_tau_RL_pi4_wEEC_def2->SetLogz();
    h_correlation_tau_RL_pi4_wEEC_def2->SetLogx();

    h16->Draw("COLZ");

    TPaveText *txtbox16 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox16->SetFillColor(0);     // Transparent
    txtbox16->SetBorderSize(0);    // Thin border
    txtbox16->SetTextFont(62);     // Standard font
    txtbox16->SetTextSize(0.03);

    
    txtbox16->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox16->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox16->AddText("100 < #it{p}_{T} < 120 GeV/#it{c}, w = #frac{#it{p}_{T,i}#it{p}_{T,j}}{#it{p}_{T,jet}^{2}}");
    txtbox16->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox16->Draw();




//-------------------
// WRITE OUT
//-----------------

    TFile *fout;
    fout = new TFile("Correlations.root","RECREATE");

    h_correlation_tau_RL_pi1_w1->Write();
    h_correlation_tau_RL_pi2_w1->Write();
    h_correlation_tau_RL_pi3_w1->Write();
    h_correlation_tau_RL_pi4_w1->Write();

    h_correlation_tau_RL_pi1_wEEC->Write();
    h_correlation_tau_RL_pi2_wEEC->Write();
    h_correlation_tau_RL_pi3_wEEC->Write();
    h_correlation_tau_RL_pi4_wEEC->Write();

    h_correlation_tau_RL_pi1_w1_def2->Write();
    h_correlation_tau_RL_pi2_w1_def2->Write();
    h_correlation_tau_RL_pi3_w1_def2->Write();
    h_correlation_tau_RL_pi4_w1_def2->Write();

    h_correlation_tau_RL_pi1_wEEC_def2->Write();
    h_correlation_tau_RL_pi2_wEEC_def2->Write();
    h_correlation_tau_RL_pi3_wEEC_def2->Write();
    h_correlation_tau_RL_pi4_wEEC_def2->Write();


    fout->Write();
    fout->Close();




}
