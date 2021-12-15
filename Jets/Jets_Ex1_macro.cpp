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

  std::cout << "Done 1!" << std::endl;
    
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
  
  canvas->Draw();
  canvas->Clear();
    
  //## Exercise 2
    
  UInt_t npv = -1;
  tree->SetBranchAddress("NPV", &npv);

  float mu = -1;
  tree->SetBranchAddress("mu_average", &mu);
    
  TH2F *hist_Rjetpt_npv = new TH2F("Reco-jet pT vs. NPV",";NPV; jet pT",50,1,50, 20, 0, 200);
  TProfile *prof_Rjetpt_npv = new TProfile("Profile Reco-jet pT vs. NPV",";NPV; jet pT",50,1,50, 0, 200);

  TH2F *hist_Tjetpt_npv = new TH2F("Truthjet pT vs. NPV",";NPV; jet pT",50,1,50, 20, 0, 200);
  TProfile *prof_Tjetpt_npv = new TProfile("Profile Truth-jet pT vs. NPV",";NPV; jet pT",50,1,50, 0, 200);
    
  //int nentries, nbytes, i;
  //nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++){
      nbytes = tree->GetEntry(i);

      if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000.){
          for(int j=0; j<reco_R4_pt->size(); j++){
              hist_Rjetpt_npv->Fill(reco_R4_pt->at(j)/1000.,npv,evtw);
              prof_Rjetpt_npv->Fill(reco_R4_pt->at(j)/1000.,npv,evtw);
          }
      }
      
      if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
          for(int j=0; j<truth_R4_pt->size(); j++){
              hist_Tjetpt_npv->Fill(truth_R4_pt->at(j)/1000.,npv,evtw);
              prof_Tjetpt_npv->Fill(truth_R4_pt->at(j)/1000.,npv,evtw);
          }
      }
  }

  std::cout << "Done 2" << std::endl;
   
  TCanvas *canvas2 = new TCanvas("Canvas2","",800,600);

  hist_Rjetpt_npv->Draw("colz"); 
  canvas2->Print("Graphs/Reco_npv.png");
  prof_Rjetpt_npv->Draw("");
  canvas2->Print("Graphs/Reco_npv_prof.png");
    
  hist_Tjetpt_npv->Draw("colz"); 
  canvas2->Print("Graphs/Truth_npv.png");
  prof_Tjetpt_npv->Draw("");
  canvas2->Print("Graphs/Truth_npv_prof.png");
  canvas2->Draw();
    
  //## Exercise 3 ##
    
  vector<float> *reco_R4_jvf;
  tree->SetBranchAddress("RecoJets_R4_jvf", &reco_R4_jvf);
    
  // No cut  
  TH1F *hist_leadreco_jvf = new TH1F("Lead Reco-jet JVF","Leading-R jet JVF; JVF;Events",20,-1,1);
  TH1F *hist_leadreco100_jvf = new TH1F("Lead Reco-jet JVF","Leading-R jet JVF; JVF;Events",20,-1,1);
  TH1F *hist_leadtruth_jvf = new TH1F("Lead Truth-jet JVF","Leading-T jet JVF; JVF;Events",20,-1,1);
  TH1F *hist_leadtruth100_jvf = new TH1F("Lead Truth-jet JVF","Leading-T jet JVF; JVF;Events",20,-1,1);
    
  for (i = 0; i < nentries; i++){
      nbytes = tree->GetEntry(i);

      if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000.){
          hist_leadreco_jvf->Fill(reco_R4_jvf->at(0), evtw);
          if(reco_R4_pt->at(0)>100000.){hist_leadreco100_jvf->Fill(reco_R4_jvf->at(0), evtw);}
      }
      
      if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000.){
          hist_leadtruth_jvf->Fill(reco_R4_jvf->at(0), evtw);
          if(reco_R4_pt->at(0)>100000.){hist_leadtruth100_jvf->Fill(reco_R4_jvf->at(0), evtw);}
      }
  }
    
  // Applying cut
    
  TH1F *hist_Cleadreco_jvf = new TH1F("Lead Reco-jet JVF","Leading-R jet JVF; JVF;Events",20,-1,1);
  TH1F *hist_Cleadreco100_jvf = new TH1F("Lead Reco-jet JVF","Leading-R jet JVF; JVF;Events",20,-1,1);
  TH1F *hist_Cleadtruth_jvf = new TH1F("Lead Truth-jet JVF","Leading-T jet JVF; JVF;Events",20,-1,1);
  TH1F *hist_Cleadtruth100_jvf = new TH1F("Lead Truth-jet JVF","Leading-T jet JVF; JVF;Events",20,-1,1);
   
  for (i = 0; i < nentries; i++){
      nbytes = tree->GetEntry(i);

      if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000. && reco_R4_jvf->at(0)>0.5 ){
          hist_Cleadreco_jvf->Fill(reco_R4_jvf->at(0), evtw);
          if(reco_R4_pt->at(0)>100000.){hist_Cleadreco100_jvf->Fill(reco_R4_jvf->at(0), evtw);}
      }
      
      if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000. && reco_R4_jvf->at(0)>0.5 ){
          hist_Cleadtruth_jvf->Fill(reco_R4_jvf->at(0), evtw);
          if(reco_R4_pt->at(0)>100000.){hist_Cleadtruth100_jvf->Fill(reco_R4_jvf->at(0), evtw);}
      }
  }
  
  std::cout << "Done 3!" << std::endl;
    
  hist_leadreco_jvf->SetMarkerStyle(20);
  hist_leadreco_jvf->SetMarkerColor(kRed);
  hist_leadreco_jvf->DrawNormalized("");
  hist_leadreco100_jvf->SetMarkerStyle(22);
  hist_leadreco100_jvf->SetMarkerColor(kBlue);
  hist_leadreco100_jvf->DrawNormalized("same");
  canvas2->Print("Graphs/leadR_jvf.png");
  
  hist_leadtruth_jvf->SetMarkerStyle(30);
  hist_leadtruth_jvf->SetMarkerColor(kRed);
  hist_leadtruth_jvf->DrawNormalized("");
  hist_leadtruth100_jvf->SetMarkerStyle(32);
  hist_leadtruth100_jvf->SetMarkerColor(kBlue);
  hist_leadtruth100_jvf->DrawNormalized("same");
  canvas2->Print("Graphs/leadT_jvf.png");
    
  hist_Cleadreco_jvf->SetMarkerStyle(20);
  hist_Cleadreco_jvf->SetMarkerColor(kRed);
  hist_Cleadreco_jvf->DrawNormalized("");
  hist_Cleadreco100_jvf->SetMarkerStyle(22);
  hist_Cleadreco100_jvf->SetMarkerColor(kBlue);
  hist_Cleadreco100_jvf->DrawNormalized("same");
  canvas2->Print("Graphs/CleadR_jvf.png");
  
  hist_Cleadtruth_jvf->SetMarkerStyle(30);
  hist_Cleadtruth_jvf->SetMarkerColor(kRed);
  hist_Cleadtruth_jvf->DrawNormalized("");
  hist_Cleadtruth100_jvf->SetMarkerStyle(32);
  hist_Cleadtruth100_jvf->SetMarkerColor(kBlue);
  hist_Cleadtruth100_jvf->DrawNormalized("same");
  canvas2->Print("Graphs/CleadT_jvf.png");
  canvas2->Draw();
    
}