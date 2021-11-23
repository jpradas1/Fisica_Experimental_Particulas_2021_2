#include<iostream>
#include<string>
#include<stdio.h>

void Tracks_Clusters_macro(){

  //Histogram Event vs Average interactions

  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  Float_t mu_mean = -1;
  tree->SetBranchAddress("mu_average", &mu_mean);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);
  

  TH1F *hist_mu_mean = new TH1F("mu_average","Number of average interactions per bunch-crossingr of primary vertices; mu_average ; Events ",50,1,100);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      hist_mu_mean->Fill(mu_mean);
    }

  std::cout << "Done mu-histogram!" << std::endl;

  hist_mu_mean->SetFillColor(42);
  hist_mu_mean->Draw();
  canvas->Print("mu_mean.pdf");
  //canvas->Draw();
  //canvas->Clear();

  //Histogram Event vs NPV 

  UInt_t npv = -1;
  tree->SetBranchAddress("NPV", &npv);

  TH1F *hist_npv = new TH1F("NPV","; Number of primary vertices; NPV ; Events ",50,1,50);

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      hist_npv->Fill(npv);
    }

  std::cout << "Done npv-histogram!" << std::endl;

  hist_npv->SetFillColor(24);
  hist_npv->Draw();
  canvas->Print("npv.pdf");
  canvas->Draw();
  //canvas->Clear();

  //Histogram NPV vs mu

  //Float_t npv_mu = -1;
  //tree->SetBranchAddress("NPV", &npv_mu);

  TH2F *hist_npv_mu = new TH2F("NPV_mu","NPV vs mu_mean; NPV ; mu_average ; Events",50,1,50,50,1,100);

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      hist_npv_mu->Fill(npv, mu_mean);
    }

  std::cout << "Done npv-mu-histogram!" << std::endl;

  hist_npv_mu->SetFillColor(33);
  hist_npv_mu->Draw();
  canvas->Print("npv_mu.pdf");
  canvas->Draw();

}
