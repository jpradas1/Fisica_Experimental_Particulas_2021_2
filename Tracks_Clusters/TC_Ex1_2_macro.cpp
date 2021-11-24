#include<iostream>
#include<string>
#include<stdio.h>

void TC_Ex1_2_macro(){

  //##  Exercise 1 and 2  ##

  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  Float_t mu_mean = -1;
  UInt_t npv = -1;
  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu_mean);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);
  

  TH1F *hist_mu_mean = new TH1F("mu_average","Number of average interactions per bunch-crossingr of primary vertices; mu_average ; Events ",50,1,100);
  TH1F *hist_npv = new TH1F("NPV","Number of primary vertices; NPV ; Events ",50,1,50);
  TH2F *hist_npv_mu = new TH2F("NPV_mu","NPV vs mu_mean; mu_average ; NPV ; Events",50,1,100,50,1,50);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      hist_mu_mean->Fill(mu_mean);
      hist_npv->Fill(npv);
      hist_npv_mu->Fill(mu_mean, npv);
    }

  std::cout << "Done first two exercises!" << std::endl;
    
  //##  Histogram Event vs Average interactions 

  hist_mu_mean->SetFillColor(42);
  hist_mu_mean->Draw();
  canvas->Print("mu_mean.pdf");

  //##  Histogram Event vs NPV 

  hist_npv->SetFillColor(24);
  hist_npv->Draw();
  canvas->Print("npv.pdf");

  //##  Histogram NPV vs mu  ##

  hist_npv_mu->SetFillColor(33);
  hist_npv_mu->Draw();
  canvas->Print("npv_mu.pdf");
  canvas->Draw();
}
