#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "TCanvas.h"
#include "TLatex.h"
#include "TFile.h"
#include "TH3F.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

using namespace std;

void fitCorrelation(TString strIn = "JetToyResults.root") {

    TFile *f = new TFile(strIn.Data());

    

    //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 1) part 1
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h1 = (TH2F*)f->Get("h_correlation_tau_RL_pi1_w1");
    TProfile *prof1 = dynamic_cast<TProfile*>(h1->ProfileX("hist_px_def1_pi1",1,-1));

    prof1->SetTitle("");
    prof1->SetStats(0);
    prof1->GetYaxis()->SetTitle("Profile of R_{L}");
    prof1->SetMaximum(1);

    prof1->GetXaxis()->SetTitleSize(0.07);
    prof1->GetYaxis()->SetTitleSize(0.07);

    // function of form A*x^-n
    TF1 *func1 = new TF1("func", "[0]*pow(x,-[1])", 1, 1000); 

    func1->SetParameters(0.08,1);

    func1->SetLineColor(kRed);


    //Draw result
    TCanvas* c1 = new TCanvas("c1", "Power-law Fit", 800, 600);

    c1->SetLogx();
    c1->SetLeftMargin(0.15);
    c1->SetBottomMargin(0.15);

    h1->Draw();               // Draw histogram
    func1->Draw("same");     // Overlay fit function

    

    c1->cd();

    //Here we fit the function to the profile
    prof1->Fit(func1, "R");

    TPaveText *txtbox1 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox1->SetFillColor(0);     // Transparent
    txtbox1->SetBorderSize(0);    // Thin border
    txtbox1->SetTextFont(62);     // Standard font
    txtbox1->SetTextSize(0.03);

    
    txtbox1->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox1->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox1->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox1->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox1->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func1->GetChisquare()/func1->GetNDF()));

    txtbox1->Draw();

    TLegend *leg1 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg1->AddEntry(h1, "Simulation Data", "l");
    leg1->AddEntry(func1, "Fit Model", "l");
    leg1->Draw("same");

    c1->Update();
    c1->Draw();

     //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 1) part 2
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h2 = (TH2F*)f->Get("h_correlation_tau_RL_pi2_w1");
    TProfile *prof2 = dynamic_cast<TProfile*>(h2->ProfileX("hist_px_def1_pi2",1,-1));

    prof2->SetTitle("");
    prof2->SetStats(0);
    prof2->GetYaxis()->SetTitle("Profile of R_{L}");
    prof2->SetMaximum(1);

    prof2->GetXaxis()->SetTitleSize(0.07);
    prof2->GetYaxis()->SetTitleSize(0.07);


    // function of form A*x^-n
    TF1 *func2 = new TF1("func", "[0]*pow(x,-[1])", 1, 1000); 

    func2->SetParameters(0.08,1);

    func2->SetLineColor(kRed);


    //Draw result
    TCanvas* c2 = new TCanvas("c2", "Power-law Fit", 800, 600);

    c2->SetLogx();
    c2->SetLeftMargin(0.15);
    c2->SetBottomMargin(0.15);

    h2->Draw();               // Draw histogram
    func2->Draw("same");     // Overlay fit function

    

    c2->cd();

    //Here we fit the function to the profile
    prof2->Fit(func2, "R");

    TPaveText *txtbox2 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox2->SetFillColor(0);     // Transparent
    txtbox2->SetBorderSize(0);    // Thin border
    txtbox2->SetTextFont(62);     // Standard font
    txtbox2->SetTextSize(0.03);

    
    txtbox2->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox2->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox2->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox2->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox2->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func2->GetChisquare()/func2->GetNDF()));

    txtbox2->Draw();

    TLegend *leg2 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg2->AddEntry(h2, "Simulation Data", "l");
    leg2->AddEntry(func2, "Fit Model", "l");
    leg2->Draw("same");

    c2->Update();
    c2->Draw();


    
    //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 1) part 3
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h3 = (TH2F*)f->Get("h_correlation_tau_RL_pi3_w1");
    TProfile *prof3 = dynamic_cast<TProfile*>(h3->ProfileX("hist_px_def1_pi3",1,-1));

    prof3->SetTitle("");
    prof3->SetStats(0);
    prof3->GetYaxis()->SetTitle("Profile of R_{L}");
    prof3->SetMaximum(1);

    prof3->GetXaxis()->SetTitleSize(0.07);
    prof3->GetYaxis()->SetTitleSize(0.07);


    // function of form A*x^-n
    TF1 *func3 = new TF1("func", "[0]*pow(x,-[1])", 1, 1000); 

    func3->SetParameters(0.08,1);

    func3->SetLineColor(kRed);


    //Draw result
    TCanvas* c3 = new TCanvas("c3", "Power-law Fit", 800, 600);

    c3->SetLogx();
    c3->SetLeftMargin(0.15);
    c3->SetBottomMargin(0.15);

    h3->Draw();               // Draw histogram
    func3->Draw("same");     // Overlay fit function

    

    c3->cd();

    //Here we fit the function to the profile
    prof3->Fit(func3, "R");

    TPaveText *txtbox3 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox3->SetFillColor(0);     // Transparent
    txtbox3->SetBorderSize(0);    // Thin border
    txtbox3->SetTextFont(62);     // Standard font
    txtbox3->SetTextSize(0.03);

    
    txtbox3->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox3->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox3->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox3->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox3->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func3->GetChisquare()/func3->GetNDF()));

    txtbox3->Draw();

    TLegend *leg3 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg3->AddEntry(h3, "Simulation Data", "l");
    leg3->AddEntry(func3, "Fit Model", "l");
    leg3->Draw("same");

    c3->Update();
    c3->Draw();

    //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 1) part 4
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h4 = (TH2F*)f->Get("h_correlation_tau_RL_pi4_w1");
    TProfile *prof4 = dynamic_cast<TProfile*>(h4->ProfileX("hist_px_def1_pi4",1,-1));

    prof4->SetTitle("");
    prof4->SetStats(0);
    prof4->GetYaxis()->SetTitle("Profile of R_{L}");
    prof4->SetMaximum(1);

    prof4->GetXaxis()->SetTitleSize(0.07);
    prof4->GetYaxis()->SetTitleSize(0.07);


    // function of form A*x^-n
    TF1 *func4 = new TF1("func", "[0]*pow(x,-[1])", 1, 1000); 

    func4->SetParameters(0.08,1);

    func4->SetLineColor(kRed);


    //Draw result
    TCanvas* c4 = new TCanvas("c4", "Power-law Fit", 800, 600);

    c4->SetLogx();
    c4->SetLeftMargin(0.15);
    c4->SetBottomMargin(0.15);

    h4->Draw();               // Draw histogram
    func4->Draw("same");     // Overlay fit function

    

    c4->cd();

    //Here we fit the function to the profile
    prof4->Fit(func4, "R");

    TPaveText *txtbox4 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox4->SetFillColor(0);     // Transparent
    txtbox4->SetBorderSize(0);    // Thin border
    txtbox4->SetTextFont(62);     // Standard font
    txtbox4->SetTextSize(0.03);

    
    txtbox4->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox4->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox4->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox4->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox4->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func4->GetChisquare()/func4->GetNDF()));

    txtbox4->Draw();

    TLegend *leg4 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg4->AddEntry(h4, "Simulation Data", "l");
    leg4->AddEntry(func4, "Fit Model", "l");
    leg4->Draw("same");

    c4->Update();
    c4->Draw();

//-----------------------------------------------------------------------------
//All for definition 2
//-----------------------------------------------------------------------------

cout << "------------------------------------" << endl;
cout << "Here begins definition 2" << endl;
cout << "------------------------------------" << endl;

    //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 2) part 1
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h5 = (TH2F*)f->Get("h_correlation_tau_RL_pi1_w1_def2");
    TProfile *prof5 = dynamic_cast<TProfile*>(h5->ProfileX("hist_px_def2_pi1",1,-1));

    prof5->SetTitle("");
    prof5->SetStats(0);
    prof5->GetYaxis()->SetTitle("Profile of R_{L}");
    prof5->SetMaximum(1);

    prof5->GetXaxis()->SetTitleSize(0.07);
    prof5->GetYaxis()->SetTitleSize(0.07);


    // function of form A*x^-n
    TF1 *func5 = new TF1("func", "[0]*pow(x,-[1])", 0.01, 1000); 

    func5->SetParameters(0.08,1);

    func5->SetLineColor(kRed);



    //Draw result
    TCanvas* c5 = new TCanvas("c5", "Power-law Fit", 800, 600);

    c5->SetLogx();
    c5->SetLeftMargin(0.15);
    c5->SetBottomMargin(0.15);

                // Draw histogram
    func5->Draw();     // Overlay fit function
    h5->Draw("same");   

    

    c5->cd();

    //Here we fit the function to the profile
    prof5->Fit(func5, "R");

    TPaveText *txtbox5 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox5->SetFillColor(0);     // Transparent
    txtbox5->SetBorderSize(0);    // Thin border
    txtbox5->SetTextFont(62);     // Standard font
    txtbox5->SetTextSize(0.03);

    
    txtbox5->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox5->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox5->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox5->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox5->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func5->GetChisquare()/func5->GetNDF()));

    txtbox5->Draw();

    TLegend *leg5 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg5->AddEntry(h5, "Simulation Data", "l");
    leg5->AddEntry(func5, "Fit Model", "l");
    leg5->Draw("same");
    c5->Update();




    c5->Update();
    c5->Draw();

    //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 2) part 2
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h6 = (TH2F*)f->Get("h_correlation_tau_RL_pi2_w1_def2");
    TProfile *prof6 = dynamic_cast<TProfile*>(h6->ProfileX("hist_px_def2_pi2",1,-1));

    prof6->SetTitle("");
    prof6->SetStats(0);
    prof6->GetYaxis()->SetTitle("Profile of R_{L}");
    prof6->SetMaximum(1);

    prof6->GetXaxis()->SetTitleSize(0.07);
    prof6->GetYaxis()->SetTitleSize(0.07);


    // function of form A*x^-n
    TF1 *func6 = new TF1("func", "[0]*pow(x,-[1])", 0.01, 1000); 

    func6->SetParameters(0.08,1);

    func6->SetLineColor(kRed);



    //Draw result
    TCanvas* c6 = new TCanvas("c6", "Power-law Fit", 800, 600);

    c6->SetLogx();
    c6->SetLeftMargin(0.15);
    c6->SetBottomMargin(0.15);

                // Draw histogram
    func6->Draw();     // Overlay fit function
    h6->Draw("same");   

   

    c6->cd();

    //Here we fit the function to the profile
    prof6->Fit(func6, "R");

     TPaveText *txtbox6 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox6->SetFillColor(0);     // Transparent
    txtbox6->SetBorderSize(0);    // Thin border
    txtbox6->SetTextFont(62);     // Standard font
    txtbox6->SetTextSize(0.03);

    
    txtbox6->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox6->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox6->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox6->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox6->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func6->GetChisquare()/func6->GetNDF()));

    txtbox6->Draw();

    TLegend *leg6 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg6->AddEntry(h6, "Simulation Data", "l");
    leg6->AddEntry(func6, "Fit Model", "l");
    leg6->Draw("same");
    c6->Update();


    c6->Update();
    c6->Draw();

    //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 2) part 3
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h7 = (TH2F*)f->Get("h_correlation_tau_RL_pi3_w1_def2");
    TProfile *prof7 = dynamic_cast<TProfile*>(h7->ProfileX("hist_px_def2_pi3",1,-1));

    prof7->SetTitle("");
    prof7->SetStats(0);
    prof7->GetYaxis()->SetTitle("Profile of R_{L}");
    prof7->SetMaximum(1);

    prof7->GetXaxis()->SetTitleSize(0.07);
    prof7->GetYaxis()->SetTitleSize(0.07);


    // function of form A*x^-n
    TF1 *func7 = new TF1("func", "[0]*pow(x,-[1])", 0.01, 1000); 

    func7->SetParameters(0.08,1);

    func7->SetLineColor(kRed);



    //Draw result
    TCanvas* c7 = new TCanvas("c7", "Power-law Fit", 800, 600);

    c7->SetLogx();
    c7->SetLeftMargin(0.15);
    c7->SetBottomMargin(0.15);

                // Draw histogram
    func7->Draw();     // Overlay fit function
    h7->Draw("same");   

   

    c7->cd();

    //Here we fit the function to the profile
    prof7->Fit(func7, "R");

     TPaveText *txtbox7 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox7->SetFillColor(0);     // Transparent
    txtbox7->SetBorderSize(0);    // Thin border
    txtbox7->SetTextFont(62);     // Standard font
    txtbox7->SetTextSize(0.03);

    
    txtbox7->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox7->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox7->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox7->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox7->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func7->GetChisquare()/func7->GetNDF()));

    txtbox7->Draw();

    TLegend *leg7 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg7->AddEntry(h7, "Simulation Data", "l");
    leg7->AddEntry(func7, "Fit Model", "l");
    leg7->Draw("same");
    c7->Update();


    c7->Update();
    c7->Draw();

    //-----------------------------------------------------------------------------
    //Fitting the correlation profile (def 2) part 4
    //-----------------------------------------------------------------------------

    // histogram we want to fit
    TH2F *h8 = (TH2F*)f->Get("h_correlation_tau_RL_pi4_w1_def2");
    TProfile *prof8 = dynamic_cast<TProfile*>(h8->ProfileX("hist_px_def2_pi4",1,-1));

    prof8->SetTitle("");
    prof8->SetStats(0);
    prof8->GetYaxis()->SetTitle("Profile of R_{L}");
    prof8->SetMaximum(1);

    prof8->GetXaxis()->SetTitleSize(0.07);
    prof8->GetYaxis()->SetTitleSize(0.07);


    // function of form A*x^-n
    TF1 *func8 = new TF1("func", "[0]*pow(x,-[1])", 0.001, 500); 

    func8->SetParameters(0.08,1);

    func8->SetLineColor(kRed);



    //Draw result
    TCanvas* c8 = new TCanvas("c8", "Power-law Fit", 800, 600);

    c8->SetLogx();
    c8->SetLeftMargin(0.15);
    c8->SetBottomMargin(0.15);

                // Draw histogram
    func8->Draw();     // Overlay fit function
    h8->Draw("same");   

    

    c8->cd();

    //Here we fit the function to the profile
    prof8->Fit(func8, "R");

    TPaveText *txtbox8 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox8->SetFillColor(0);     // Transparent
    txtbox8->SetBorderSize(0);    // Thin border
    txtbox8->SetTextFont(62);     // Standard font
    txtbox8->SetTextSize(0.03);

    
    txtbox8->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox8->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox8->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox8->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");
    txtbox8->AddText(Form("#it{#chi_{red}^{2}} = %.2f",func8->GetChisquare()/func8->GetNDF()));

    txtbox8->Draw();

    TLegend *leg8 = new TLegend(0.6, 0.6, 0.89, 0.89);
    leg8->AddEntry(h8, "Simulation Data", "l");
    leg8->AddEntry(func8, "Fit Model", "l");
    leg8->Draw("same");
    c8->Update();


    c8->Update();
    c8->Draw();

//-------------------------------------------------------------------
// INSTEAD OF CHI^2
//-------------------------------------------------------------------

    //-------------------------------------------------------------------
    // FOR DEF 1 W=1
    //-------------------------------------------------------------------

    const int N1 = prof1->FindBin(1000) - prof1->FindBin(1);
    const int N2 = prof2->FindBin(1000) - prof2->FindBin(1);
    const int N3 = prof3->FindBin(1000) - prof3->FindBin(1);
    const int N4 = prof4->FindBin(1000) - prof4->FindBin(1);
    TGraph* graph1 = new TGraph(N1);
    TGraph* graph2 = new TGraph(N2);
    TGraph* graph3 = new TGraph(N3);
    TGraph* graph4 = new TGraph(N4);


        for (int i = prof1->FindBin(1); i <= prof1->FindBin(1000); ++i) {
            double val = prof1->GetBinContent(i)/func1->Eval(prof1->GetBinCenter(i));
            graph1->SetPoint(i, prof1->GetBinCenter(i), val);
        }

         for (int i = prof2->FindBin( 1); i <= prof2->FindBin(1000); ++i) {
            double val = prof2->GetBinContent(i)/func2->Eval(prof2->GetBinCenter(i));
            graph2->SetPoint(i, prof2->GetBinCenter(i), val);
        }

        for (int i = prof3->FindBin(1); i <= prof3->FindBin(1000); ++i) {
            double val = prof3->GetBinContent(i)/func3->Eval(prof3->GetBinCenter(i));
            graph3->SetPoint(i, prof3->GetBinCenter(i), val);
        }

        for (int i = prof4->FindBin(1); i <= prof4->FindBin(1000); ++i) {
            double val = prof4->GetBinContent(i)/func4->Eval(prof4->GetBinCenter(i));
            graph4->SetPoint(i, prof4->GetBinCenter(i), val);
        }


    
    TCanvas* can = new TCanvas("can", "Value vs Index", 800, 600);
    graph1->SetTitle("; #it{#tau}_{f} (fm); Data/Model");
    graph1->GetXaxis()->SetLimits(1, 1000);

    can->SetLeftMargin(0.15);
    can->SetBottomMargin(0.15);
    can->SetLogx();

    TGraph* graphs[4] = {graph1, graph2, graph3, graph4};

    int colors[4] = {kRed, kBlue, kGreen+2, kMagenta};  // Choose distinct colors

    for (int i = 0; i < 4; ++i) {
    graphs[i]->SetMarkerStyle(20);         // Filled circle
    graphs[i]->SetMarkerSize(0.3);         // Size
    graphs[i]->SetMarkerColor(colors[i]);  // Unique color
    graphs[i]->SetLineColor(colors[i]);    // Optional: color the line too
    graphs[i]->Draw(i == 0 ? "AP" : "P same");
    graphs[i]->GetXaxis()->SetTitleSize(0.07);
    graphs[i]->GetYaxis()->SetTitleSize(0.07);
}

 
    TLine* line1 = new TLine(1,0.9, 1000, 0.9);
    TLine* line2 = new TLine(1, 1.1, 1000, 1.1);

    line1->SetLineColor(kBlack);
    line2->SetLineColor(kBlack);

    line1->SetLineStyle(2);  // dashed line
    line2->SetLineStyle(2);

    line1->Draw("same");
    line2->Draw("same");

    TPaveText *txtbox9 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox9->SetFillColor(0);     // Transparent
    txtbox9->SetBorderSize(0);    // Thin border
    txtbox9->SetTextFont(62);     // Standard font
    txtbox9->SetTextSize(0.03);

    
    txtbox9->AddText("Ratio Data/Model for Inverse Power Law fit");
    txtbox9->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox9->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox9->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox9->AddText("#it{p}_{T,parent} = #it{p}_{T,i} + #it{p}_{T,j}");

    txtbox9->Draw();

     // Add legend
    TLegend *leg9 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg9->AddEntry(graph1, "40-60 GeV/#it{c}", "l");
    leg9->AddEntry(graph2, "60-80 GeV/#it{c}", "l");
    leg9->AddEntry(graph3, "80-100 GeV/#it{c}", "l");
    leg9->AddEntry(graph4, "100-120 GeV/#it{c}", "l");
    leg9->Draw();

    //-------------------------------------------------------------------
    // FOR DEF 2 W=1
    //-------------------------------------------------------------------

    const int N5 = prof5->FindBin(0.1) - prof5->FindBin(1000);
    const int N6 = prof6->FindBin(0.1) - prof6->FindBin(1000);
    const int N7 = prof7->FindBin(0.1) - prof7->FindBin(1000);
    const int N8 = prof8->FindBin(0.01) - prof8->FindBin(500);
    TGraph* graph5 = new TGraph(N5);
    TGraph* graph6 = new TGraph(N6);
    TGraph* graph7 = new TGraph(N7);
    TGraph* graph8 = new TGraph(N8);


        for (int i = prof5->FindBin(0.1); i <= prof5->FindBin(1000); ++i) {
            double val = prof5->GetBinContent(i)/func5->Eval(prof5->GetBinCenter(i));
            graph5->SetPoint(i, prof5->GetBinCenter(i), val);
        }

         for (int i = prof6->FindBin(0.1); i <= prof6->FindBin(1000); ++i) {
            double val = prof6->GetBinContent(i)/func6->Eval(prof6->GetBinCenter(i));
            graph6->SetPoint(i, prof6->GetBinCenter(i), val);
        }

        for (int i = prof7->FindBin(0.1); i <= prof7->FindBin(1000); ++i) {
            double val = prof7->GetBinContent(i)/func7->Eval(prof7->GetBinCenter(i));
            graph7->SetPoint(i, prof7->GetBinCenter(i), val);
        }

        for (int i = prof8->FindBin(0.01); i <= prof8->FindBin(500); ++i) {
            double val = prof8->GetBinContent(i)/func8->Eval(prof8->GetBinCenter(i));
            graph8->SetPoint(i, prof8->GetBinCenter(i), val);
        }


    
    TCanvas* can2 = new TCanvas("can2", "Value vs Index", 800, 600);
    graph5->SetTitle("; #it{#tau}_{f} (fm); Data/Model");
    graph5->GetXaxis()->SetLimits(0.01, 1000);

    can2->SetLeftMargin(0.15);
    can2->SetBottomMargin(0.15);
    can2->SetLogx();

    TGraph* graphs2[4] = {graph5, graph6, graph7, graph8};
  // Choose distinct colors

    for (int i = 0; i < 4; ++i) {
    graphs2[i]->SetMarkerStyle(20);         // Filled circle
    graphs2[i]->SetMarkerSize(0.3);         // Size
    graphs2[i]->SetMarkerColor(colors[i]);  // Unique color
    graphs2[i]->SetLineColor(colors[i]);    // Optional: color the line too
    graphs2[i]->Draw(i == 0 ? "AP" : "P same");
    graphs2[i]->GetXaxis()->SetTitleSize(0.07);
    graphs2[i]->GetYaxis()->SetTitleSize(0.07);
    graphs2[i]->SetMaximum(1.3);
}

 
    TLine* line1b = new TLine(0.01,0.9,1000, 0.9);
    TLine* line2b = new TLine(0.01, 1.1, 1000, 1.1);

    line1b->SetLineColor(kBlack);
    line2b->SetLineColor(kBlack);

    line1b->SetLineStyle(2);  // dashed line
    line2b->SetLineStyle(2);

    line1b->Draw();
    line2b->Draw();

    TPaveText *txtbox10 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox10->SetFillColor(0);     // Transparent
    txtbox10->SetBorderSize(0);    // Thin border
    txtbox10->SetTextFont(62);     // Standard font
    txtbox10->SetTextSize(0.03);

    
    txtbox10->AddText("Ratio Data/Model for Inverse Power Law fit");
    txtbox10->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox10->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox10->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox10->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox10->Draw();

     // Add legend
    TLegend *leg10 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg10->AddEntry(graph1, "40-60 GeV/#it{c}", "l");
    leg10->AddEntry(graph2, "60-80 GeV/#it{c}", "l");
    leg10->AddEntry(graph3, "80-100 GeV/#it{c}", "l");
    leg10->AddEntry(graph4, "100-120 GeV/#it{c}", "l");
    leg10->Draw();



    //----------------------------------------------------------------------------------------
    //Her we write out to the ROOT file
    //----------------------------------------------------------------------------------------
    
    TFile *fout;
    fout = new TFile("fitCorrelation.root","RECREATE");
    
    //h1->Write();
    //prof1->Write();
    //func1->Write();
    c1->Write();

    //h2->Write();
    //prof2->Write();
    //func2->Write();
    c2->Write();

    //h3->Write();
    //prof3->Write();
    //func3->Write();
    c3->Write();

   //h4->Write();
    //prof4->Write();
    //func4->Write();
    c4->Write();

    //h5->Write();
    //prof5->Write();
    //func5->Write();
    c5->Write();

    //h6->Write();
    //prof6->Write();
    //func6->Write();
    c6->Write();

    //h7->Write();
    //prof7->Write();
    //func7->Write();
    c7->Write();

    //h8->Write();
    //prof8->Write();
    //func8->Write();
    c8->Write();

    can->Write();
    can2->Write();


    fout->Close();

}
