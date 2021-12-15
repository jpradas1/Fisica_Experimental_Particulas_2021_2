#include<iostream>
#include<string>
#include<stdio.h>

void Jets_Ex4_macro(){
  //## Exercise 4 ##
    
  TFile *file = TFile::Open("../Tracks_Clusters/Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();
    
  float evtw = -1;
  vector<float> *reco_R4_pt = {};
  vector<float> *truth_R4_pt = {};
  vector<float> *track_R4_pt = {};
  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
  tree->SetBranchAddress("TrackJets_R4_pt", &track_R4_pt);
    
  vector<float> *reco_R4_jvf = {};
  tree->SetBranchAddress("RecoJets_R4_jvf", &reco_R4_jvf);

  TCanvas *canvas = new TCanvas("Canvas","Canvas",800,600);
    
  vector<float> *reco_R4_eta = {};
  vector<float> *reco_R4_phi = {};
  vector<float> *reco_R4_m = {};
  tree->SetBranchAddress("RecoJets_R4_eta", &reco_R4_eta);
  tree->SetBranchAddress("RecoJets_R4_phi", &reco_R4_phi);
  tree->SetBranchAddress("RecoJets_R4_m", &reco_R4_m);
    
  vector<float> *truth_R4_eta = {};
  vector<float> *truth_R4_phi = {};
  vector<float> *truth_R4_m = {};
  tree->SetBranchAddress("TruthJets_R4_eta", &truth_R4_eta);
  tree->SetBranchAddress("TruthJets_R4_phi", &truth_R4_phi);
  tree->SetBranchAddress("TruthJets_R4_m", &truth_R4_m);
    
  vector<float> *track_R4_eta = {};
  vector<float> *track_R4_phi = {};
  vector<float> *track_R4_m = {};
  tree->SetBranchAddress("TrackJets_R4_eta", &track_R4_eta);
  tree->SetBranchAddress("TrackJets_R4_phi", &track_R4_phi);
  tree->SetBranchAddress("TrackJets_R4_m", &track_R4_m);
    
  TH1F *hist_DR_reco_truth = new TH1F("Delta R reco","Delta R; #Delta R; Events",20,0,2);
  TH1F *hist_DR_Creco_truth = new TH1F("Delta R reco","Delta R (|JVF|>0.5); #Delta R; Events",20,0,2);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();
    
  for (i = 0; i < nentries; i++){
      nbytes = tree->GetEntry(i);

      if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
          TLorentzVector truthJet;
          truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),
                                truth_R4_eta->at(0),
                                truth_R4_phi->at(0),
                                truth_R4_m->at(0)); 
          
          if(reco_R4_pt->size()!=0 && fabs(reco_R4_jvf->at(0))>0.5){
              TLorentzVector recoJet;
              recoJet.SetPtEtaPhiM(reco_R4_pt->at(0),
                                   reco_R4_eta->at(0),
                                   reco_R4_phi->at(0),
                                   reco_R4_m->at(0));       
        //Plot the Delta R
        hist_DR_reco_truth->Fill(truthJet.DeltaR(recoJet),evtw);}
      }
  }

  std::cout << "Done 4!" << std::endl;
    
  hist_DR_reco_truth->Scale(1/hist_DR_reco_truth->Integral());
  hist_DR_reco_truth->DrawNormalized("");
  canvas->Print("Graphs/DR_RT.png");
    
  //hist_DR_Creco_truth->Scale(1/hist_DR_Creco_truth->Integral());
  //hist_DR_Creco_truth->DrawNormalized("");
  //canvas->Print("Graphs/DR_RT_Cut.png");
  //canvas->Draw();
    
  //## Exercise 5 ##
    
  TH1F *hist_matched_reco_truth_20 = new TH1F("Matched R-T 20","Matched (RT) 20; Reco/Truth; Events",20,0,2);
  TH1F *hist_matched_reco_truth_100 = new TH1F("Matched R-T 100","Matched (RT) 100; Reco/Truth; Events",20,0,2);
  TH1F *hist_matched_reco_truth_500 = new TH1F("Matched R-T 500","Matched (RT) 500; Reco/Truth ; Events",20,0,2);
  TH1F *hist_matched_track_truth_20 = new TH1F("Matched T-T 20","Matched (TT) 20; Track/Truth; Events",20,0,2);
  TH1F *hist_matched_track_truth_100 = new TH1F("Matched T-T 100","Matched (TT) 100; Track/Truth; Events",20,0,2);
  TH1F *hist_matched_track_truth_500 = new TH1F("Matched T-T 500","Matched (TT) 500; Track/Truth; Events",20,0,2);
    
  for (i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    if(truth_R4_pt->size()!=0){
      TLorentzVector truthJet;
      truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),
                            truth_R4_eta->at(0),
                            truth_R4_phi->at(0),
                            truth_R4_m->at(0)
                           );

      if(reco_R4_pt->size() != 0){
        TLorentzVector recoJet;
        recoJet.SetPtEtaPhiM(reco_R4_pt->at(0),
                             reco_R4_eta->at(0),
                             reco_R4_phi->at(0),
                             reco_R4_m->at(0));

        if (truthJet.DeltaR(recoJet) < 0.3) {
          if (truth_R4_pt->at(0) > 20000.) {
            hist_matched_reco_truth_20->Fill(truth_R4_pt->at(0) / reco_R4_pt->at(0),evtw);}

          if (truth_R4_pt->at(0) > 100000.) {
            hist_matched_reco_truth_100->Fill(truth_R4_pt->at(0) / reco_R4_pt->at(0),evtw);}

          if (truth_R4_pt->at(0) > 500000.) {
              hist_matched_reco_truth_500->Fill(truth_R4_pt->at(0) / reco_R4_pt->at(0),evtw);}
        }
      }


      if(track_R4_pt->size() != 0){
        TLorentzVector trackJet;
        trackJet.SetPtEtaPhiM(track_R4_pt->at(0),
                              track_R4_eta->at(0),                            
                              track_R4_phi->at(0),         
                              track_R4_m->at(0));

        //Plot the Delta R
        if (truthJet.DeltaR(trackJet) < 0.3) {
          if (truth_R4_pt->at(0)>20000.) {
            hist_matched_track_truth_20->Fill(truth_R4_pt->at(0) / track_R4_pt->at(0),evtw);}

          if (truth_R4_pt->at(0)>100000.) {
              hist_matched_track_truth_100->Fill(truth_R4_pt->at(0) / track_R4_pt->at(0),evtw);}

          if (truth_R4_pt->at(0)>500000.) {
            hist_matched_track_truth_500->Fill(truth_R4_pt->at(0) / track_R4_pt->at(0),evtw);}
        }
      }
    }
  }
    
  std::cout << "Done 5!" << std::endl;
    
  hist_matched_reco_truth_20->SetMarkerStyle(20);
  hist_matched_reco_truth_20->SetMarkerColor(kRed);
  hist_matched_reco_truth_20->Draw("");
    
  hist_matched_reco_truth_100->SetMarkerStyle(20);
  hist_matched_reco_truth_100->SetMarkerColor(kRed);
  hist_matched_reco_truth_100->Draw("");
    
  hist_matched_reco_truth_500->SetMarkerStyle(20);
  hist_matched_reco_truth_500->SetMarkerColor(kRed);
  hist_matched_reco_truth_500->Draw("");
  canvas->Print("ReTruth_03.pdf");
    
  hist_matched_track_truth_20->SetMarkerStyle(20);
  hist_matched_track_truth_20->SetMarkerColor(kRed);
  hist_matched_track_truth_20->Draw("");
    
  hist_matched_track_truth_100->SetMarkerStyle(20);
  hist_matched_track_truth_100->SetMarkerColor(kRed);
  hist_matched_track_truth_100->Draw("");
  
  hist_matched_track_truth_500->SetMarkerStyle(20);
  hist_matched_track_truth_500->SetMarkerColor(kRed);
  hist_matched_track_truth_500->Draw("");
  canvas->Print("TraTru_03.pdf");
}