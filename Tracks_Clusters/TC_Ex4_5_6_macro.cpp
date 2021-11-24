#include<iostream>
#include<string>
#include<stdio.h>

void TC_Ex4_5_6_macro(){

  //##  Exercise 4, 5 and 6 ##
    
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();
    
  vector<float> *tracks_pt = {};
  vector<float> *tracks_eta = {};
  vector<float> *tracks_phi = {};
  vector<float> *tracks_m = {};
  vector<float> *tracks_vtx = {};
  ree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Tracks_eta", &tracks_eta);
  tree->SetBranchAddress("Tracks_phi", &tracks_phi);
  tree->SetBranchAddress("Tracks_m", &tracks_m);
  tree->SetBranchAddress("Tracks_vtx", &tracks_vtx);
    
  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);
    
  TH1F *hist_track_pT = new TH1F("Track_pT","Example plot: Track pT; pT (MeV) ; Events ",50,100,1000);
  TH1F *hist_track_eta = new TH1F("Track_eta","Track eta; eta (Rad) ; Events ",50,-3,3);
  TH1F *hist_track_phi = new TH1F("Track_phi","Track phi; phi (Rad) ; Events ",50,-4,4);
  TH1F *hist_track_m = new TH1F("Track_m","Track m; M (MeV) ; Events ",50,0,200);
  TH1F *hist_track_vtx = new TH1F("Track_vtx","Track vtx; vtx (Rad) ; Events ",50,-5,40);
  
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++){
      nbytes = tree->GetEntry(i);
      for(int tr=0; tr<tracks_pt->size(); tr++){
          hist_track_pt->Fill(tracks_pt->at(tr));
          hist_track_eta->Fill(tracks_eta->at(tr));
          hist_track_phi->Fill(tracks_phi->at(tr));
          hist_track_m->Fill(tracks_m->at(tr));
          hist_track_vtx->Fill(tracks_vtx->at(tr));}
  }

  std::cout << "Done the last exercise!" << std::endl;
    
  hist_track_eta->SetFillColor(8);
  hist_track_eta->Draw();
  canvas->Print("Track_eta.pdf");
    
  hist_track_phi->SetFillColor(16);
  hist_track_phi->Draw();
  canvas->Print("Track_phi.pdf");
    
  hist_track_pt->SetFillColor(24);
  hist_track_pt->Draw();
  canvas->Print("Track_pt.pdf");
  canvas->Draw();
  
  hist_track_m->SetFillColor(32);
  hist_track_m->Draw();
  canvas->Print("Track_m.pdf");
    
  hist_track_vtx->SetFillColor(40);
  hist_track_vtx->Draw();
  canvas->Print("Track_vtx.pdf");
  
}
