#include<iostream>
#include<string>
#include<stdio.h>

void TC_Ex4_5_6_macro(){

  //##  Exercise 4, 5 and 6 ##
    
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  //tree->Print();
    
  vector<float> *tracks_pt = {};
  vector<float> *tracks_eta = {};
  vector<float> *tracks_phi = {};
  vector<float> *tracks_m = {};
  vector<float> *tracks_vtx = {};
  tree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Tracks_eta", &tracks_eta);
  tree->SetBranchAddress("Tracks_phi", &tracks_phi);
  tree->SetBranchAddress("Tracks_m", &tracks_m);
  tree->SetBranchAddress("Tracks_vtx", &tracks_vtx);
  
  vector<float> *clusters_pt = {};
  vector<float> *clusters_eta = {};
  vector<float> *clusters_phi = {};
  vector<float> *clusters_m = {};
  tree->SetBranchAddress("Clusters_pt", &clusters_pt);
  tree->SetBranchAddress("Clusters_eta", &clusters_eta);
  tree->SetBranchAddress("Clusters_phi", &clusters_phi);
  tree->SetBranchAddress("Clusters_m", &clusters_m);
    
  vector<float> *particles_pt = {};
  vector<float> *particles_eta = {};
  vector<float> *particles_phi = {};
  vector<float> *particles_m = {};
  vector<float> *particles_pdgID = {};
  tree->SetBranchAddress("Particles_pt", &particles_pt);
  tree->SetBranchAddress("Particles_eta", &particles_eta);
  tree->SetBranchAddress("Particles_phi", &particles_phi);
  tree->SetBranchAddress("Particles_m", &particles_m);
  tree->SetBranchAddress("Particles_pdgID", &particles_pdgID);
    
  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);
    
  TH1F *hist_track_pT = new TH1F("Track_pT","Example plot: Track pT; pT (MeV) ; Events ",50,100,1000);
  TH1F *hist_track_eta = new TH1F("Track_eta","Track eta; eta (Rad) ; Events ",50,-3,3);
  TH1F *hist_track_phi = new TH1F("Track_phi","Track phi; phi (Rad) ; Events ",50,-4,4);
  TH1F *hist_track_m = new TH1F("Track_m","Track M; M (MeV) ; Events ",50,100,180);
  TH1F *hist_track_vtx = new TH1F("Track_vtx","Track vertex; vertex ; Events ",50,-5,40);
    
  TH1F *hist_cluster_pT = new TH1F("Cluster_pT","Cluster pT; pT (MeV) ; Events ",50,100,1000);
  TH1F *hist_cluster_eta = new TH1F("Cluster_eta","Cluster eta; eta (Rad) ; Events ",50,-3,3);
  TH1F *hist_cluster_phi = new TH1F("Cluster_phi","Cluster phi; phi (Rad) ; Events ",50,-4,4);
  TH1F *hist_cluster_m = new TH1F("Cluster_m","Cluster M; M (MeV) ; Events ",50,-10,10);
  
  TH1F *hist_particle_pT = new TH1F("Particle_pT","Particle pT; pT (MeV) ; Events ",50,100,1000);
  TH1F *hist_particle_eta = new TH1F("Particle_eta","Particle eta; eta (Rad) ; Events ",50,-3,3);
  TH1F *hist_particle_phi = new TH1F("Particle_phi","Particle phi; phi (Rad) ; Events ",50,-4,4);
  TH1F *hist_particle_m = new TH1F("Particle_m","Particle M; M (MeV) ; Events ",50,-10,500);
  TH1F *hist_particle_pdgID = new TH1F("Particle_pdgID","Particle pdgID; pdgID ; Events ",50,100,1000);
  
  
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++){
      nbytes = tree->GetEntry(i);
      for(int tr=0; tr<tracks_pt->size(); tr++){
          hist_track_pT->Fill(tracks_pt->at(tr));
          hist_track_eta->Fill(tracks_eta->at(tr));
          hist_track_phi->Fill(tracks_phi->at(tr));
          hist_track_m->Fill(tracks_m->at(tr));
          hist_track_vtx->Fill(tracks_vtx->at(tr));}
      
      for (int tr=0; tr < clusters_pt->size(); tr++){
          hist_cluster_pT->Fill(clusters_pt->at(tr));
          hist_cluster_eta->Fill(clusters_eta->at(tr));
          hist_cluster_phi->Fill(clusters_phi->at(tr));
          hist_cluster_m->Fill(clusters_m->at(tr));}
      
      for (int tr=0; tr < particles_pt->size(); tr++){
          hist_particle_pT->Fill(particles_pt->at(tr));
          hist_particle_eta->Fill(particles_eta->at(tr));
          hist_particle_phi->Fill(particles_phi->at(tr));
          hist_particle_m->Fill(particles_m->at(tr));
          hist_particle_pdgID->Fill(particles_pdgID->at(tr));}
  }

  std::cout << "Done the last exercises!" << std::endl;
  
  //Print track variables
  
  hist_track_eta->SetFillColor(8);
  hist_track_eta->Draw();
  canvas->Print("Track_eta.png");
    
  hist_track_phi->SetFillColor(16);
  hist_track_phi->Draw();
  canvas->Print("Track_phi.png");
    
  hist_track_pT->SetFillColor(24);
  hist_track_pT->Draw();
  canvas->Print("Track_pt.png");
  
  hist_track_m->SetFillColor(32);
  hist_track_m->Draw();
  canvas->Print("Track_m.png");
    
  hist_track_vtx->SetFillColor(40);
  hist_track_vtx->Draw();
  canvas->Print("Track_vtx.png");
    
  //Print cluster variables
    
  hist_cluster_pT->SetFillColor(7);
  hist_cluster_pT->Draw();
  canvas->Print("Cluster_pt.png");
    
  hist_cluster_eta->SetFillColor(14);
  hist_cluster_eta->Draw();
  canvas->Print("Cluster_eta.png");
    
  hist_cluster_phi->SetFillColor(21);
  hist_cluster_phi->Draw();
  canvas->Print("Cluster_phi.png");
    
  hist_cluster_m->SetFillColor(28);
  hist_cluster_m->Draw();
  canvas->Print("Cluster_m.png");
  canvas->Draw();
    
  //Print particule variables
    
  hist_particle_pT->SetFillColor(6);
  hist_particle_pT->Draw();
  canvas->Print("Particle_pt.png");
    
  hist_particle_eta->SetFillColor(12);
  hist_particle_eta->Draw();
  canvas->Print("Particle_eta.png");
    
  hist_particle_phi->SetFillColor(18);
  hist_particle_phi->Draw();
  canvas->Print("Particle_phi.png");
  
  hist_particle_m->SetFillColor(24);
  hist_particle_m->Draw();
  canvas->Print("Particle_m.png");
    
  hist_particle_pdgID->SetFillColor(30);
  hist_particle_pdgID->Draw();
  canvas->Print("Particle_pdgID.png");
  canvas->Draw();

}
