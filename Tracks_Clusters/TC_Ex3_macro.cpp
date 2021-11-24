#include<iostream>
#include<string>
#include<stdio.h>

void TC_Ex3_macro(){
    
  //##  Exercise 3 ##

  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  Float_t mu_mean = -1;
  UInt_t npv = -1;
  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu_mean);

  vector<float> *tracks_pt = {};
  vector<float> *clusters_pt = {};
  tree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Clusters_pt", &clusters_pt);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);

  TH2F *hist_npv_Tck = new TH2F("NPV_NTracks","NPV vs NTracks; Ntracks ; NPV ; Events ",50,1,1000,50,1,50);
  TH2F *hist_mu_Tck = new TH2F("mu_NTracks","mu vs NTracks; Ntracks ; mu_average ; Events ",50,1,1000,50,1,100);
  TH2F *hist_npv_Clt = new TH2F("NPV_NClusters","NPV vs NClusters; NClusters ; NPV ; Events ",50,1,1000,50,1,50);
  TH2F *hist_mu_Clt = new TH2F("mu_NClusters","mu vs NClusters; NClusters ; mu_average ; Events ",50,1,1000,50,1,100);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      hist_npv_Tck->Fill(tracks_pt->size(), npv);
      hist_mu_Tck->Fill(tracks_pt->size(),mu_mean);
      hist_npv_Clt->Fill(clusters_pt->size(),npv);
      hist_mu_Clt->Fill(clusters_pt->size(),mu_mean);
    }

  std::cout << "Done third exercise!" << std::endl;
    
  //## Histogram NPV vs NTracks

  hist_npv_Tck->SetFillColor(42);
  hist_npv_Tck->Draw("COL");
  canvas->Print("npv_Tck.pdf");
    
  //## Histogram mu vs NTracks

  hist_mu_Tck->SetFillColor(24);
  hist_mu_Tck->Draw("COL");
  canvas->Print("mu_Tck.pdf");
    
  //## Histogram NPV vs NClusters

  hist_npv_Clt->SetFillColor(33);
  hist_npv_Clt->Draw("COL");
  canvas->Print("npv_Clt.pdf");
    
  //## Histogram mu vs NClusters

  hist_mu_Clt->SetFillColor(0);
  hist_mu_Clt->Draw("COL");
  canvas->Print("mu_Clt.pdf");
  canvas->Draw();
  
}
