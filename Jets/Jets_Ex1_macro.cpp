#include<iostream>
#include<string>
#include<stdio.h>

void Jets_Ex1_macro(){

  //##  Exercise 1  ##

  TFile *file = TFile::Open("../Tracks_Clusters/Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();
    
  float evtw = -1;
  vector<float> *reco_R4_pt = {};
  vector<float> *truth_R4_pt = {};

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);

  TCanvas *canvas = new TCanvas("Canvas","Canvas",800,600);
  
  //## Weight
  TH1F *hist_Wleadreco_pt = new TH1F("Lead Reco-jet","Leading jet pT (Weight); pT(GeV);Events",50,10,200);
  TH1F *hist_Wreco_pt = new TH1F("Reco-jet","Jet pT (Weight); pT(GeV);Events",50,10,200);
    
  TH1F *hist_Wleadtruth_pt = new TH1F("Lead truth-jet","Leading jet pT (Weight); pT(GeV);Events",50,10,200);
  TH1F *hist_Wtruth_pt = new TH1F("Truth-jet","Jet pT (Weight); pT(GeV);Events",50,10,200);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
  {
      nbytes = tree->GetEntry(i);   
      if(reco_R4_pt->size()>0){
          hist_Wleadreco_pt->Fill(reco_R4_pt->at(0)/1000.,evtw);
          for(int j=0; j<reco_R4_pt->size(); j++){
              hist_Wreco_pt->Fill(reco_R4_pt->at(j)/1000.,evtw);}
      }
      
      if(truth_R4_pt->size()>0){
          hist_Wleadtruth_pt->Fill(truth_R4_pt->at(0)/1000.,evtw);
          for(int j=0; j<truth_R4_pt->size(); j++){
              hist_Wtruth_pt->Fill(truth_R4_pt->at(j)/1000.,evtw);}
      }
  }
    
  //## No Weight
    
  TH1F *hist_leadreco_pt = new TH1F("Lead Reco-jet","Leading jet pT (Weightless); pT(GeV);Events",50,10,200);
  TH1F *hist_reco_pt = new TH1F("Reco-jet","Jet pT (Weightless); pT(GeV);Events",50,10,200);
    
  TH1F *hist_leadtruth_pt = new TH1F("Lead truth-jet","Leading jet pT (Weightless); pT(GeV);Events",50,10,200);
  TH1F *hist_truth_pt = new TH1F("Truth-jet","Jet pT (Weightless); pT(GeV);Events",50,10,200);
    
  for (i = 0; i < nentries; i++)
  {
      nbytes = tree->GetEntry(i);   
      if(reco_R4_pt->size()>0){
          hist_leadreco_pt->Fill(reco_R4_pt->at(0)/1000);
          for(int j=0; j<reco_R4_pt->size(); j++){
              hist_reco_pt->Fill(reco_R4_pt->at(j)/1000);}
      }
      
      if(truth_R4_pt->size()>0){
          hist_leadtruth_pt->Fill(truth_R4_pt->at(0)/1000);
          for(int j=0; j<truth_R4_pt->size(); j++){
              hist_truth_pt->Fill(truth_R4_pt->at(j)/1000);}
      }
  }

  std::cout << "Done!" << std::endl;
    
  hist_Wleadtruth_pt->SetMarkerStyle(20);
  hist_Wleadtruth_pt->SetMarkerColor(kRed);
  hist_Wleadtruth_pt->Draw("");
  hist_Wleadreco_pt->SetMarkerStyle(21);
  hist_Wleadreco_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Graphs/WleadR_T.png");
    
  hist_Wreco_pt->SetMarkerStyle(20);
  hist_Wreco_pt->SetMarkerColor(kBlue);
  hist_Wreco_pt->Draw("");
  hist_Wtruth_pt->SetMarkerStyle(21);
  hist_Wtruth_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Graphs/WR_T.png");
    
  hist_leadtruth_pt->SetMarkerStyle(20);
  hist_leadtruth_pt->SetMarkerColor(kRed);
  hist_leadtruth_pt->Draw("");
  hist_leadreco_pt->SetMarkerStyle(21);
  hist_leadreco_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Graphs/leadR_T.png");
    
  hist_reco_pt->SetMarkerStyle(20);
  hist_reco_pt->SetMarkerColor(kBlue);
  hist_reco_pt->Draw("");
  hist_truth_pt->SetMarkerStyle(21);
  hist_truth_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Graphs/R_T.png");
  
  canvas->Draw();
    
}
