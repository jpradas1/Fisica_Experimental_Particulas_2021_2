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
  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
    
  vector<float> *reco_R4_jvf = {};
  tree->SetBranchAddress("RecoJets_R4_jvf", &reco_R4_jvf);
  vector<float> *truth_R4_jvf = {};
  tree->SetBranchAddress("TruthJets_R4_jvf", &truth_R4_jvf);

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
    
  TH1F *hist_DR_reco_truth = new TH1F("Delta R reco","Delta R; #Delta R; Events",20,0,2);
  TH1F *hist_DR_Creco_truth = new TH1F("Delta R reco","Delta R (|JVF|>0.5); #Delta R; Events",20,0,2);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();
    
  for (i = 0; i < nentries; i++){
      nbytes = tree->GetEntry(i);

      if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
          TLorentzVector truthJet;
    truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0)); 
          
          if(reco_R4_pt->size()!=0 && fabs(reco_R4_jvf->at(0))>0.5){
              TLorentzVector recoJet;
    recoJet.SetPtEtaPhiM(reco_R4_pt->at(0),reco_R4_eta->at(0),reco_R4_phi->at(0),reco_R4_m->at(0));       
        //Plot the Delta R
        hist_DR_reco_truth->Fill(truthJet.DeltaR(recoJet),evtw);}
      }
      
     if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000. && fabs(truth_R4_jvf->at(0))>0.5){
          TLorentzVector truthJet;
    truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0)); 
          
          if(reco_R4_pt->size()!=0 && fabs(reco_R4_jvf->at(0))>0.5){
              TLorentzVector recoJet;
    recoJet.SetPtEtaPhiM(reco_R4_pt->at(0),reco_R4_eta->at(0),reco_R4_phi->at(0),reco_R4_m->at(0));       
        //Plot the Delta R
        hist_DR_reco_truth->Fill(truthJet.DeltaR(recoJet),evtw);}
      }
  }

  std::cout << "Done 4!" << std::endl;
    
  hist_DR_reco_truth->Scale(1/hist_DR_reco_truth->Integral());
  hist_DR_reco_truth->DrawNormalized("");
  canvas->Print("Graphs/DR_RT.png");
    
  hist_DR_Creco_truth->Scale(1/hist_DR_reco_truth->Integral());
  hist_DR_Creco_truth->DrawNormalized("");
  canvas->Print("Graphs/DR_RT_Cut.png");
  canvas->Draw();
}