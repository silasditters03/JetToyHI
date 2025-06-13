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
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

using namespace std;


void yScaling(TH1F* hists[4], std::vector<double> PtAverages ) {
    for (int i = 0; i < 4; ++i){
        hists[i]->Scale( log(PtAverages[i])/(PtAverages[i] ) );
    }
}


void fitLinear(TString strIn = "JetToyResults.root") {

    TFile *f = new TFile(strIn.Data());

    //Imports the average P_T's per bin
    TH1F *PtAve = (TH1F*)f->Get("Pt_averages");

    double PtAveBin0 = PtAve->GetBinContent(1); //P_T average for bin 40-60
    double PtAveBin1 = PtAve->GetBinContent(2); //P_T average for bin 60-80
    double PtAveBin2 = PtAve->GetBinContent(3); //P_T average for bin 80-100
    double PtAveBin3 = PtAve->GetBinContent(4); //P_T average for bin 100-120

    std::vector<double> PtAverages = {PtAveBin0, PtAveBin1, PtAveBin2, PtAveBin3};


    // histogram we want to fit
    TH1F *h1 = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi1");
    TH1F *h2 = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi2");
    TH1F *h3 = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi3");
    TH1F *h4 = (TH1F*)f->Get("hE2C_sum_vs_tau_def2_scaledpi4");

    h1->SetTitle("");
    h2->SetTitle("");
    h3->SetTitle("");
    h4->SetTitle("");

    h1->GetXaxis()->SetTitleSize(0.07);
    h1->GetYaxis()->SetTitleSize(0.05);
    h2->GetXaxis()->SetTitleSize(0.07);
    h2->GetYaxis()->SetTitleSize(0.05);
    h3->GetXaxis()->SetTitleSize(0.07);
    h3->GetYaxis()->SetTitleSize(0.05);
    h4->GetXaxis()->SetTitleSize(0.07);
    h4->GetYaxis()->SetTitleSize(0.05);

    TH1F* hists_sc[4] = {h1, h2, h3, h4};

    yScaling(hists_sc,PtAverages);


//-------------------------------------------------------------------
//From Here we fit each histogram for hadron pairs t_form_Def2
//------------------------------------------------------------------

    //------------------------------------------------------------
    // H1: hE2C_sum_vs_tau_def2_scaledpi1
    //------------------------------------------------------------
    gStyle->SetOptStat(0000000);
    // function of form A*x^-n
    TF1 *func1 = new TF1("func1", "[0]*x + [1]", 1.653, 4.959); 

    func1->SetParameters(0.004);


    //Draw result
    TCanvas* c1 = new TCanvas("c1", "Linear Fit", 800, 600);
    c1->SetTitle("");
    c1->SetLogx();

    c1->SetLeftMargin(0.15);
    c1->SetBottomMargin(0.15);

    c1->cd();

    // Perform the fit over the specified range (30 to xmax)
    h1->Fit(func1, "R");  // "R" = restrict fit to TF1 range
    h1->SetStats(0);

    h1->Draw();               // Draw histogram
    func1->Draw("same");     // Overlay fit function
    h1->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((#it{GeV/c})^{-1})");

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


    h1->GetYaxis()->SetRangeUser(0, 0.03);

    TLegend *leg1 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg1->AddEntry(h1, "Simulation Data", "l");
    leg1->AddEntry(func1, "Fit Model", "l");
    leg1->Draw("same");

    c1->Update();



    
    //prints fit results
    std::cout << "A = " << func1->GetParameter(0) << std::endl;

    //------------------------------------------------------------
    // H2: hE2C_sum_vs_tau_def2_scaledpi2
    //------------------------------------------------------------

    // function of form A*x^-n
    TF1 *func2 = new TF1("func2", "[0]*x + [1]", 1.69, 5.071); 

    func2->SetParameters(0.004);

   
    

    //Draw result
    TCanvas* c2 = new TCanvas("c2", "Linear Fit", 800, 600);
    c2->SetTitle("");
    c2->SetLogx();

    c2->SetLeftMargin(0.15);
    c2->SetBottomMargin(0.15);
 
    c2->cd();

     // Perform the fit over the specified range (30 to xmax)
    h2->Fit(func2, "R");  // "R" = restrict fit to TF1 range

    h2->Draw();               // Draw histogram
    func2->Draw("same");     // Overlay fit function
    h2->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((#it{GeV/c})^{-1})");

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

    TLegend *leg2 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2->AddEntry(h2, "Simulation Data", "l");
    leg2->AddEntry(func2, "Fit Model", "l");
    leg2->Draw("same");

    c2->Update();

    h2->GetYaxis()->SetRangeUser(0, 0.03);

    //prints fit results
    std::cout << "A = " << func2->GetParameter(0) << std::endl;

     //------------------------------------------------------------
    // H3: hE2C_sum_vs_tau_def2_scaledpi3
    //------------------------------------------------------------

    // function of form A*x^-n
    TF1 *func3 = new TF1("func3", "[0]*x + [1]", 1.981, 4.8435); 

    func3->SetParameters(0.004);

    
    

    //Draw result
    TCanvas* c3 = new TCanvas("c3", "Linear Fit", 800, 600);
    c3->SetTitle("");
    c3->SetLogx();

    c3->SetLeftMargin(0.15);
    c3->SetBottomMargin(0.15);
 
    c3->cd();

    // Perform the fit over the specified range (20 to xmax)
    h3->Fit(func3, "R");  // "R" = restrict fit to TF1 range

    h3->Draw();               // Draw histogram
    func3->Draw("same");     // Overlay fit function
    h3->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((#it{GeV/c})^{-1})");

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

    TLegend *leg3 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg3->AddEntry(h3, "Simulation Data", "l");
    leg3->AddEntry(func3, "Fit Model", "l");
    leg3->Draw("same");

    c3->Update();

    h3->GetYaxis()->SetRangeUser(0, 0.03);

    //prints fit results
    std::cout << "A = " << func3->GetParameter(0) << std::endl;

    //------------------------------------------------------------
    // H4: hE2C_sum_vs_tau_def2_scaledpi4
    //------------------------------------------------------------

    // function of form A*x^-n
    TF1 *func4 = new TF1("func4", "[0]*x + [1]", 1.896, 5); //4.876

    func4->SetParameters(0.004);


    //Draw result
    TCanvas* c4 = new TCanvas("c4", "Linear Fit", 800, 600);
    c4->SetTitle("");
    c4->SetLogx();

    c4->SetLeftMargin(0.15);
    c4->SetBottomMargin(0.15);
 
    c4->cd();

    // Perform the fit over the specified range (20 to xmax)
    h4->Fit(func4, "R");  // "R" = restrict fit to TF1 range

    h4->Draw();               // Draw histogram
    func4->Draw("same");     // Overlay fit function
    h4->GetYaxis()->SetTitle(" ln(<p_{T}^{ch jet}>)/<p_{T}^{ch jet}> #Sigma_{EEC} ((#it{GeV/c})^{-1})");

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

    TLegend *leg4 = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg4->AddEntry(h4, "Simulation Data", "l");
    leg4->AddEntry(func4, "Fit Model", "l");
    leg4->Draw("same");

    c4->Update();

    h4->GetYaxis()->SetRangeUser(0, 0.03);

    //prints fit results
    std::cout << "A = " << func4->GetParameter(0) << std::endl;

//-------------------------------------------------------------------
// INSTEAD OF CHI^2
//-------------------------------------------------------------------

    const int N1 = h1->FindBin(4.959) - h1->FindBin(1.653);
    const int N2 = h2->FindBin( 5.071) - h2->FindBin( 1.69);
    const int N3 = h3->FindBin(4.8435) - h3->FindBin(1.981);
    const int N4 = h4->FindBin(5) - h4->FindBin(1.896);
    TGraph* graph1 = new TGraph(N1);
    TGraph* graph2 = new TGraph(N2);
    TGraph* graph3 = new TGraph(N3);
    TGraph* graph4 = new TGraph(N4);


        for (int i = h1->FindBin(1.653); i <= h1->FindBin(4.959); ++i) {
            double val = h1->GetBinContent(i)/func1->Eval(h1->GetBinCenter(i));
            graph1->SetPoint(i, h1->GetBinCenter(i), val);
        }

         for (int i = h2->FindBin( 1.69); i <= h2->FindBin(5.071); ++i) {
            double val = h2->GetBinContent(i)/func2->Eval(h2->GetBinCenter(i));
            graph2->SetPoint(i, h2->GetBinCenter(i), val);
        }

        for (int i = h3->FindBin(1.981); i <= h3->FindBin(4.8425); ++i) {
            double val = h3->GetBinContent(i)/func3->Eval(h3->GetBinCenter(i));
            graph3->SetPoint(i, h3->GetBinCenter(i), val);
        }

        for (int i = h4->FindBin( 1.896); i <= h4->FindBin(5); ++i) {
            double val = h4->GetBinContent(i)/func4->Eval(h4->GetBinCenter(i));
            graph4->SetPoint(i, h4->GetBinCenter(i), val);
        }


    
    TCanvas* can = new TCanvas("can", "Value vs Index", 800, 600);
    graph1->SetTitle("; <p_{T}^{ch jet}>#it{#tau}_{f} (GeV/#it{c} fm); Data/Model");
    graph1->GetXaxis()->SetLimits(1, 5.5);

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

 
    TLine* line1 = new TLine(1,0.9, 5.5, 0.9);
    TLine* line2 = new TLine(1, 1.1, 5.5, 1.1);

    line1->SetLineColor(kBlack);
    line2->SetLineColor(kBlack);

    line1->SetLineStyle(2);  // dashed line
    line2->SetLineStyle(2);

    line1->Draw("same");
    line2->Draw("same");

    TPaveText *txtbox5 = new TPaveText(0.6, 0.7, 0.9, 0.85, "NDC"); // (x1,y1,x2,y2)
    txtbox5->SetFillColor(0);     // Transparent
    txtbox5->SetBorderSize(0);    // Thin border
    txtbox5->SetTextFont(62);     // Standard font
    txtbox5->SetTextSize(0.03);

    
    txtbox5->AddText("Ratio Data/Model for Linear fit in perturbative regime");
    txtbox5->AddText("pp #sqrt{#it{s}} = 5.02 TeV");
    txtbox5->AddText("PYTHIA8, Anti-#it{k}_{T} particle jets, #it{R} = 0.4, |#it{#eta}| < 2");
    txtbox5->AddText("#it{p}_{T,track} > 1 GeV/#it{c}");
    txtbox5->AddText("#it{p}_{T,parent} = #it{p}_{T,jet}");

    txtbox5->Draw();

     // Add legend
    TLegend *leg2_sc = new TLegend(0.7, 0.7, 0.89, 0.89);
    leg2_sc->AddEntry(graph1, "40-60 GeV/#it{c}", "l");
    leg2_sc->AddEntry(graph2, "60-80 GeV/#it{c}", "l");
    leg2_sc->AddEntry(graph3, "80-100 GeV/#it{c}", "l");
    leg2_sc->AddEntry(graph4, "100-120 GeV/#it{c}", "l");
    leg2_sc->Draw();






    //-------------------------------------------------------------------
    //Write to ROOT file
    //-------------------------------------------------------------------
    TFile *fout;
    fout = new TFile("fitLinear.root","RECREATE");

    h1->Write();
    func1->Write();
    c1->Write();

    h2->Write();
    func2->Write();
    c2->Write();

    h3->Write();
    func3->Write();
    c3->Write();

    h4->Write();
    func4->Write();
    c4->Write();

    can->Write();


}
