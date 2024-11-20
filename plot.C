void plot() {
    
    TFile *f1 = new TFile("JetToyHIResultSimpleJetAnalysis.root");

    TTree *tr = dynamic_cast<TTree*>(f1->Get("jetTree"));

    // First canvas and plot
    TCanvas *c1 = new TCanvas("c1", "c1");
    tr->Draw("sigJetEta:sigJetPhi", "", "colz");

    // Save the first plot
    c1->SaveAs("Geometricplot.png");

    // Jet Pt plot
    TCanvas *c2 = new TCanvas("c2", "c2");
    c2->SetLogy();  // Use c2->SetLogy() to set log scale for y-axis
    tr->Draw("sigJetPt", "sigJetPt>120. && abs(sigJetEta)<1.");
    c2->SaveAs("JetPt.png");
    



    TFile *f2 = new TFile("JetToyResults.root");
    TH1 *h= dynamic_cast<TH1*>(f2->Get("JetToyResults/h1zgSigSD01"));
    //TH1 *g= dynamic_cast<TH1*>(f1->Get("jetTree/zgSigSDBeta00Z05"));

    // Zg plot (softDropGroomer)
    TCanvas *c3 = new TCanvas("c3", "c3");
    c3->SetLogy();  // Use c3->SetLogy() to set log scale for y-axis
    c3->cd();
    h->GetYaxis()->SetTitle("Number of jets");
    h->GetXaxis()->SetTitle("Zg");
    h->Draw("E");
    c3->SaveAs("zgsoftgroomer.png");

    // erad plot (softDropGroomer)
    //TCanvas *c4 = new TCanvas("c4", "c4");
    //c4->SetLogy();  // Use c4->SetLogy() to set log scale for y-axis
    //tr->Draw("eradSigSDBeta00Z01");
    //c4->SaveAs("eradsoftgroomer.png", "sigJetPt>120. && abs(sigJetEta)<1.");
    f1->Close();
}