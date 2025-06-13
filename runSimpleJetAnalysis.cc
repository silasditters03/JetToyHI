#include <iostream>
#include <chrono>


#include "TFile.h"
#include "TTree.h"

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include "include/ProgressBar.h"

#include "PU14/EventMixer.hh"
#include "PU14/CmdLine.hh"
#include "PU14/PU14.hh"

#include "include/extraInfo.hh"
#include "include/jetCollection.hh"
#include "include/softDropGroomer.hh"
#include "include/treeWriter.hh"
#include "include/jetMatcher.hh"
#include "include/Angularity.hh"
#include "include/softDropCounter.hh"

using namespace std;
using namespace fastjet;

// ./runSimpleJetAnalysis -hard /Users/mverweij/mnt/eos/project/j/jetquenching/JetWorkshop2017/samples/pythia8/dijet120/PythiaEventsTune14PtHat120_0.pu14 -nev 10

int main (int argc, char ** argv) {

  auto start_time = chrono::steady_clock::now();
  
  CmdLine cmdline(argc,argv);
  // inputs read from command line
  int nEvent = cmdline.value<int>("-nev",1);  // first argument: command line option; second argument: default value
  //bool verbose = cmdline.present("-verbose");

  cout << "will run on " << nEvent << " events" << endl;

  // Uncomment to silence fastjet banner
  ClusterSequence::set_fastjet_banner_stream(NULL);

  //to write info to root tree
  treeWriter trw("jetTree");

  //Jet definition
  double R                   = 0.4;
  double ghostRapMax         = 6.0;
  double ghost_area          = 0.005;
  int    active_area_repeats = 1;
  GhostedAreaSpec ghost_spec(ghostRapMax, active_area_repeats, ghost_area);
  AreaDefinition area_def = AreaDefinition(active_area,ghost_spec);
  JetDefinition jet_def(antikt_algorithm, R);

  double jetRapMax = 3.0;
  Selector jet_selector = SelectorAbsRapMax(jetRapMax);

  Angularity width(1.,1.,R);
  Angularity pTD(0.,2.,R);
    
  ProgressBar Bar(cout, nEvent);
  Bar.SetStyle(-1);

  EventMixer mixer(&cmdline);  //the mixing machinery from PU14 workshop

  // loop over events
  int iev = 0;
  unsigned int entryDiv = (nEvent > 200) ? nEvent / 200 : 1;
  while ( mixer.next_event() && iev < nEvent )
  {
    // increment event number    
    iev++;

    Bar.Update(iev);
    Bar.PrintWithMod(entryDiv);

    vector<PseudoJet> particlesMergedAll = mixer.particles();

    vector<double> eventWeight;
    eventWeight.push_back(mixer.hard_weight());
    eventWeight.push_back(mixer.pu_weight());

    // extract hard partons that initiated the jets
    fastjet::Selector parton_selector = SelectorVertexNumber(-1);
    vector<PseudoJet> partons = parton_selector(particlesMergedAll);

    // select final state particles from hard event only
    fastjet::Selector sig_selector = SelectorVertexNumber(0);
    vector<PseudoJet> particlesSig = sig_selector(particlesMergedAll);

    // select final state particles from background event only
    fastjet::Selector bkg_selector = SelectorVertexNumber(1);
    vector<PseudoJet> particlesBkg = bkg_selector(particlesMergedAll);

     //charged particles
    fastjet::Selector charged_selector = SelectorIsCharged();
    vector<PseudoJet> particlesSigCh = charged_selector(particlesSig);

    vector<PseudoJet> particlesMerged = particlesBkg;
    particlesMerged.insert( particlesMerged.end(), particlesSig.begin(), particlesSig.end() );
    
    
    //vector<PseudoJet> particlesBkg, particlesSig;
    //SelectorIsHard().sift(particlesMerged, particlesSig, particlesBkg); // this sifts the full event into two vectors of PseudoJet, one for the hard event, one for the underlying event

    //---------------------------------------------------------------------------
    //   jet clustering  (for full jets)
    //---------------------------------------------------------------------------

    fastjet::ClusterSequenceArea csSig(particlesSig, jet_def, area_def);
    jetCollection jetCollectionSig(sorted_by_pt(jet_selector(csSig.inclusive_jets(10.))));

    //calculate some angularities
    vector<double> widthSig; widthSig.reserve(jetCollectionSig.getJet().size());
    vector<double> pTDSig;   pTDSig.reserve(jetCollectionSig.getJet().size());
    for(PseudoJet jet : jetCollectionSig.getJet()) {
      widthSig.push_back(width.result(jet));
      pTDSig.push_back(pTD.result(jet));
    }
    jetCollectionSig.addVector("widthSig", widthSig);
    jetCollectionSig.addVector("pTDSig", pTDSig);

   //---------------------------------
  // Calculations for hadron pairs
  //----------------------------------
  vector<vector<double>> all_zg_hadron_pairs;
  vector<vector<double>> all_dr_hadron_pairs;
  vector<vector<double>> all_E2C_hadron_pairs;
  vector<vector<double>> all_mom_pt_hadron_pairs;
  vector<vector<double>> all_jet_pt_hadron_pairs;

  // Loop over every Jet 
  for (PseudoJet jet : jetCollectionSig.getJet()) {
      // Get the constituents of the jet
      vector<PseudoJet> constituents = jet.constituents();
      int num_constituents = constituents.size();

      // Vectors to store the results for this jet 
      vector<double> dr_hadron_pairs;
      vector<double> zg_hadron_pairs;
      vector<double> E2C_hadron_pairs;
      vector<double> mom_pt_hadron_pairs;
      vector<double> jet_pt_hadron_pairs;

      // Loop over all pairs of constituents (hadrons) (i, j)
      for (int i = 0; i < num_constituents; ++i) {
          for (int j = i + 1; j < num_constituents; ++j) {
              // Get the i-th and j-th constituents
              const PseudoJet& part_i = constituents[i];
              const PseudoJet& part_j = constituents[j];

              if (part_i.pt() > 1.0 && part_j.pt() > 1.0) { //Only hadrons with pt > 1GeV/c are being considered

                  // Calculate zg for the hadron pair
                  double zg = std::min(part_i.pt(), part_j.pt()) / (part_i.pt() + part_j.pt());
                  zg_hadron_pairs.push_back(zg);

                  // Calculate drij (angular distance between the 2 hadrons i and j)
                  double DeltaR = std::sqrt(part_i.squared_distance(part_j));
                  dr_hadron_pairs.push_back(DeltaR);

                  // Calculate E2C of hadron pairs
                  double E2C = (part_i.pt() * part_j.pt()) / (pow(jet.pt(), 2));
                  E2C_hadron_pairs.push_back(E2C);

                  // Calculate mother p_T
                  double mpt = part_i.pt() + part_j.pt();
                  mom_pt_hadron_pairs.push_back(mpt);

                  // Add jet_pt to list
                  jet_pt_hadron_pairs.push_back(jet.pt());
              }
          }
      }

      // After collecting data for this jet, store the vectors in all_* vectors
      all_zg_hadron_pairs.push_back(zg_hadron_pairs);
      all_dr_hadron_pairs.push_back(dr_hadron_pairs);
      all_E2C_hadron_pairs.push_back(E2C_hadron_pairs);
      all_mom_pt_hadron_pairs.push_back(mom_pt_hadron_pairs);
      all_jet_pt_hadron_pairs.push_back(jet_pt_hadron_pairs);
  }

    // Adding the vectors to the jet collection
    jetCollectionSig.addVector("zg_hadron_pairs", all_zg_hadron_pairs);
    jetCollectionSig.addVector("dr_hadron_pairs", all_dr_hadron_pairs);
    jetCollectionSig.addVector("E2C_hadron_pairs", all_E2C_hadron_pairs);
    jetCollectionSig.addVector("mom_pt_hadron_pairs", all_mom_pt_hadron_pairs);
    jetCollectionSig.addVector("jet_pt_hadron_pairs", all_jet_pt_hadron_pairs);

    
    //---------------------------------------------------------------------------
    //   Groom the jets
    //---------------------------------------------------------------------------

    //SoftDrop grooming classic for signal jets (zcut=0.1, beta=0)
    softDropGroomer sdgSigBeta00Z01(0.0, 0.0, R); 
    jetCollection jetCollectionSigSDBeta00Z01(sdgSigBeta00Z01.doGrooming(jetCollectionSig));
    jetCollectionSigSDBeta00Z01.addVector("zgSigSDBeta00Z01",    sdgSigBeta00Z01.getZgs());
    jetCollectionSigSDBeta00Z01.addVector("eradSigSDBeta00Z01",    sdgSigBeta00Z01.getErads());
    jetCollectionSigSDBeta00Z01.addVector("dr12SigSDBeta00Z01",  sdgSigBeta00Z01.getDR12());
    jetCollectionSigSDBeta00Z01.addVector("productSigSDBeta00Z01",  sdgSigBeta00Z01.getProducts());


    //SoftDrop grooming classic for signal jets (zcut=0.2, beta=0)
    softDropGroomer sdgSigBeta00Z05(0.3, 0.0, R); 
    jetCollection jetCollectionSigSDBeta00Z05(sdgSigBeta00Z05.doGrooming(jetCollectionSig));
    jetCollectionSigSDBeta00Z05.addVector("zgSigSDBeta00Z05",    sdgSigBeta00Z05.getZgs());
    jetCollectionSigSDBeta00Z05.addVector("eradSigSDBeta00Z05",    sdgSigBeta00Z05.getErads());
    jetCollectionSigSDBeta00Z05.addVector("dr12SigSDBeta00Z05",  sdgSigBeta00Z05.getDR12());
    jetCollectionSigSDBeta00Z05.addVector("productSigSDBeta00Z05",  sdgSigBeta00Z05.getProducts());

    //SoftDrop grooming classic for signal jets (zcut=0.4, beta=0)
    softDropGroomer sdgSigBeta00Z03(0.4, 0.0, R); 
    jetCollection jetCollectionSigSDBeta00Z03(sdgSigBeta00Z03.doGrooming(jetCollectionSig));
    jetCollectionSigSDBeta00Z03.addVector("zgSigSDBeta00Z03",    sdgSigBeta00Z03.getZgs());
    jetCollectionSigSDBeta00Z03.addVector("eradSigSDBeta00Z03",    sdgSigBeta00Z03.getErads());
    jetCollectionSigSDBeta00Z03.addVector("dr12SigSDBeta00Z03",  sdgSigBeta00Z03.getDR12());
    jetCollectionSigSDBeta00Z03.addVector("productSigSDBeta00Z03",  sdgSigBeta00Z03.getProducts());
   
   
    // Here we are going to recluster the jets
    //jetCollection jetCollectionsubjetcounter(sdgSigBeta00Z01.doGrooming(jetCollectionSig));
    softDropCounter sdcSig(0.0,0.0, R, 0.0); // don't cut zg 
    sdcSig.setRecursiveAlgo(0);
    sdcSig.run(jetCollectionSig);

    jetCollectionSig.addVector("sigjetRecur_jetpt",     sdcSig.getPts());
    jetCollectionSig.addVector("sigjetRecur_z",         sdcSig.getZgs());
    jetCollectionSig.addVector("sigjetRecur_dr12",      sdcSig.getDRs());
    jetCollectionSig.addVector("sigjetRecur_erad",      sdcSig.getErads());
    jetCollectionSig.addVector("sigjetRecur_product",      sdcSig.getProducts());
    jetCollectionSig.addVector("sigjetRecur_mpt",      sdcSig.getMpts());
    jetCollectionSig.addVector("sigjetRecur_logdr12",   sdcSig.getLog1DRs());
    jetCollectionSig.addVector("sigjetRecur_logztheta", sdcSig.getLogzDRs());
   
    softDropCounter sdcSigzcut1 (0.08 ,0.0, R, 0.0);// cut zg 
    sdcSigzcut1.setRecursiveAlgo(0);
    sdcSigzcut1.run(jetCollectionSig);

    jetCollectionSig.addVector("sigjetRecurZcut1_jetpt",     sdcSigzcut1.getPts());
    jetCollectionSig.addVector("sigjetRecurZcut1_z",         sdcSigzcut1.getZgs());
    jetCollectionSig.addVector("sigjetRecurZcut1_dr12",      sdcSigzcut1.getDRs());
    jetCollectionSig.addVector("sigjetRecurZcut1_erad",      sdcSigzcut1.getErads());
    jetCollectionSig.addVector("sigjetRecurZcut1_product",      sdcSigzcut1.getProducts());
    jetCollectionSig.addVector("sigjetRecurZcut1_mpt",      sdcSigzcut1.getMpts());
    jetCollectionSig.addVector("sigjetRecurZcut1_logdr12",   sdcSigzcut1.getLog1DRs());
    jetCollectionSig.addVector("sigjetRecurZcut1_logztheta", sdcSigzcut1.getLogzDRs());

    softDropCounter sdcSigzcut2 (0.2, 0.0, R, 0.0);// cut zg 
    sdcSigzcut2.setRecursiveAlgo(0);
    sdcSigzcut2.run(jetCollectionSig);

    jetCollectionSig.addVector("sigjetRecurZcut2_jetpt",     sdcSigzcut2.getPts());
    jetCollectionSig.addVector("sigjetRecurZcut2_z",         sdcSigzcut2.getZgs());
    jetCollectionSig.addVector("sigjetRecurZcut2_dr12",      sdcSigzcut2.getDRs());
    jetCollectionSig.addVector("sigjetRecurZcut2_erad",      sdcSigzcut2.getErads());
    jetCollectionSig.addVector("sigjetRecurZcut2_product",      sdcSigzcut2.getProducts());
    jetCollectionSig.addVector("sigjetRecurZcut2_mpt",      sdcSigzcut2.getMpts());
    jetCollectionSig.addVector("sigjetRecurZcut2_logdr12",   sdcSigzcut2.getLog1DRs());
    jetCollectionSig.addVector("sigjetRecurZcut2_logztheta", sdcSigzcut2.getLogzDRs());

  /*
    //---------------------------------------------------------------------------
    // Clustering for charged particles
    //---------------------------------------------------------------------------
    fastjet::ClusterSequenceArea csSigCh(particlesSigCh, jet_def, area_def);
    jetCollection jetCollectionSigCh(sorted_by_pt(jet_selector(csSigCh.inclusive_jets(10.))));

    // Calculate angularities for charged jets
    vector<double> widthSigCh; widthSigCh.reserve(jetCollectionSigCh.getJet().size());
    vector<double> pTDSigCh;   pTDSigCh.reserve(jetCollectionSigCh.getJet().size());

    for (PseudoJet jet : jetCollectionSigCh.getJet()) {
        widthSigCh.push_back(width.result(jet));
        pTDSigCh.push_back(pTD.result(jet));
    }

    // Store the calculated angularities in the charged jet collection
    jetCollectionSigCh.addVector("widthSigCh", widthSigCh);
    jetCollectionSigCh.addVector("pTDSigCh", pTDSigCh);

  //---------------------------------
  // Calculations for hadron pairs in charged jets
  //----------------------------------
  for (PseudoJet jet : jetCollectionSigCh.getJet()) {
      vector<PseudoJet> constituents = jet.constituents();
      int num_constituents = constituents.size();

        vector<double> dr_hadron_pairs_ch;
        vector<double> zg_hadron_pairs_ch;
        vector<double> E2C_hadron_pairs_ch;

        for (int i = 0; i < num_constituents; ++i) {
            for (int j = i + 1; j < num_constituents; ++j) {
                const PseudoJet& part_i = constituents[i];
                const PseudoJet& part_j = constituents[j];

                if (part_i.pt() > 1.0 && part_j.pt() > 1.0) {
                  zg_hadron_pairs_ch.push_back(std::min(part_i.pt(), part_j.pt()) / (part_i.pt() + part_j.pt()));
                  dr_hadron_pairs_ch.push_back(std::sqrt(part_i.squared_distance(part_j)));
                  E2C_hadron_pairs_ch.push_back((part_i.pt() * part_j.pt()) / pow(part_i.pt() + part_j.pt(), 2));
                }
            }
        }
  
          jetCollectionSigCh.addVector("zg_hadron_pairs_ch", zg_hadron_pairs_ch);
          jetCollectionSigCh.addVector("dr_hadron_pairs_ch", dr_hadron_pairs_ch);
          jetCollectionSigCh.addVector("E2C_hadron_pairs_ch", E2C_hadron_pairs_ch);
  }
      
*/
    


    //---------------------------------------------------------------------------
    //   write tree
    //---------------------------------------------------------------------------
    
    //Give variable we want to write out to treeWriter.
    //Only vectors of the types 'jetCollection', and 'double', 'int', 'PseudoJet' are supported

    trw.addCollection("eventWeight",   eventWeight);
    trw.addPartonCollection("partons",       partons);

    trw.addCollection("sigJet",        jetCollectionSig);
    trw.addCollection("sigJetSDBeta00Z01",      jetCollectionSigSDBeta00Z01);
    trw.addCollection("sigJetSDBeta00Z05",      jetCollectionSigSDBeta00Z05);
    trw.addCollection("sigJetSDBeta00Z03",      jetCollectionSigSDBeta00Z03);
    //trw.addCollection("sigJetCh", jetCollectionSigCh);
    
    trw.fillTree();

  }//event loop

  Bar.Update(nEvent);
  Bar.Print();
  Bar.PrintLine();

  TTree *trOut = trw.getTree();

  TFile *fout = new TFile(cmdline.value<string>("-output", "JetToyHIResultSimpleJetAnalysis.root").c_str(), "RECREATE");
  trOut->Write();
  fout->Write();
  fout->Close();

  double time_in_seconds = chrono::duration_cast<chrono::milliseconds>
    (chrono::steady_clock::now() - start_time).count() / 1000.0;
  cout << "runFromFile: " << time_in_seconds << endl;
}
