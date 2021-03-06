#include <iostream>
#include <stdio.h>
#include <string>

void ttbar_MC_macro (){
    
    TFile *file = TFile::Open("ttbar_8TeV.root");
    TTree *tree = (TTree*) file->Get("mini");
    tree->Print();
    
    Bool_t e_trig;
    Bool_t mu_trig;
    Bool_t good_vtx;
    UInt_t lep_n;
    UInt_t jet_n;
    
    Float_t MET;
    Float_t MET_phi;

    Float_t lep_pt[10];  
    Float_t lep_eta[10];  
    Float_t lep_phi[10];  
    Float_t lep_E[10];      
    Int_t lep_type[10];      
    Float_t lep_ptcone30[10];
    Float_t lep_etcone20[10];

    Float_t jet_pt[10];
    Float_t jet_eta[10];
    Float_t jet_jvf[10];
    Float_t jet_mv1[10];
    
    Float_t scalef_pileup;
    Float_t scalef_e;
    Float_t scalef_mu;
    Float_t scalef_btag;
    Float_t scalef_trigger;
    Float_t scalef_jvfsf;
    Float_t scalef_zvertex;
    
    tree->SetBranchAddress("trigE", &e_trig);
    tree->SetBranchAddress("trigM", &mu_trig);
    tree->SetBranchAddress("hasGoodVertex", &good_vtx);    
    tree->SetBranchAddress("lep_n", &lep_n);
    tree->SetBranchAddress("jet_n", &jet_n);    
    tree->SetBranchAddress("met_et", &MET);
    tree->SetBranchAddress("met_phi", &MET_phi);

    tree->SetBranchAddress("lep_pt", &lep_pt);
    tree->SetBranchAddress("lep_eta", &lep_eta);
    tree->SetBranchAddress("lep_phi", &lep_phi);
    tree->SetBranchAddress("lep_E", &lep_E);
    tree->SetBranchAddress("lep_type", &lep_type);
    tree->SetBranchAddress("lep_ptcone30", &lep_ptcone30);
    tree->SetBranchAddress("lep_etcone20", &lep_etcone20);

    tree->SetBranchAddress("jet_pt", &jet_pt);
    tree->SetBranchAddress("jet_eta", &jet_eta);
    tree->SetBranchAddress("jet_jvf", &jet_jvf);
    tree->SetBranchAddress("jet_MV1", &jet_mv1);
    
    tree->SetBranchAddress("scaleFactor_PILEUP", &scalef_pileup);
    tree->SetBranchAddress("scaleFactor_ELE", &scalef_e);
    tree->SetBranchAddress("scaleFactor_MUON", &scalef_mu);
    tree->SetBranchAddress("scaleFactor_BTAG", &scalef_btag);
    tree->SetBranchAddress("scaleFactor_TRIGGER", &scalef_trigger);
    tree->SetBranchAddress("scaleFactor_JVFSF", &scalef_jvfsf);
    tree->SetBranchAddress("scaleFactor_ZVERTEX", &scalef_zvertex);

    TCanvas *canvas = new TCanvas("Canvas","",800,600);
    
    //##Histograms
    
    // Histogram for cuts
    TH1F *cutflow = new TH1F("Cutflow","Cutflow; Cut; Events",10,0,10);

    // Histograms for Jets
    TH1F *hist_njets    = new TH1F("Number of jets","n-jets; Jet multiplicity; Events",10,0,10);
    TH1F *hist_jets_pt  = new TH1F("Jets pT","Jet pT; pT (GeV); Events",50,0,1000);
    TH1F *hist_jets_eta = new TH1F("Jets Eta","Jet Eta; Eta; Events",50,-5,5);
    TH1F *hist_jets_jvf = new TH1F("Jets JVF","Jet JVF; JVF; Events",50,0,1);
    TH1F *hist_jets_mv1 = new TH1F("Jets MV1","Jet MV1; MV1; Events",50,0.5,1);
    
    // Histogram for leptons
    TH1F *hist_lept_pt  = new TH1F("Leptons pT","Lepton pT; pT (GeV); Events",50,0,1000);
    TH1F *hist_lept_pt_cone30 = new TH1F("Track Isolation","Track Isolation; lept_ptcone30/lep_pt; Events",50,0,0.2);
    TH1F *hist_lept_et_cone20 = new TH1F("Calorimeter Isolation","Calorimeter Isolation; lept_etcone20/lep_pt; Events",50,0,0.2);
    TH1F *hist_lept_eta = new TH1F("Leptons Eta","Lepton Eta; ETa; Events",50,-5,5);
    
    //Histogram for bJets
    TH1F *hist_nbjets    = new TH1F("Number of b-jets","n-bjets; b-Jet multiplicity; Events",50,0,6);
    
    // Histogram for MET
    TH1F *hist_MET = new TH1F("MET","MET; MET (GeV); Events",50,0,200);
    
    // Histogram for mTW
    TH1F *hist_mTW = new TH1F("mTW","mTW; mTW (GeV); Events",50,0,200);
    
    int nentries, nbytes, i;
    nentries = (Int_t)tree->GetEntries();

    int cut1 = 0;
    int cut2 = 0;
    int cut3 = 0;
    int cut4 = 0;
    int cut5 = 0;
    int cut6 = 0;
    int cut7 = 0;
    int cut8 = 0;


    for (i = 0; i < nentries; i++){
        nbytes = tree->GetEntry(i);
        
        //Before anything else, it's defined weight variable
        Float_t sigma = 137.29749; // pb^-1
        Float_t N_MC_evt = 49761200.21;
        Float_t filter = 0.072212854;
        
        Float_t L_MC = N_MC_evt * filter / sigma;

        Float_t eventWeight = 1000 / L_MC;
        Float_t scaleF = scalef_pileup * scalef_e * scalef_mu * scalef_btag;
        scaleF *= scalef_trigger * scalef_jvfsf * scalef_zvertex;
        Float_t evtw = scaleF * eventWeight;

        //First cut: Good vertex
        if(!good_vtx) continue;
        cut1++;
        cutflow->Fill(1, evtw);

        //Second cut: Trigger
        if(!e_trig && !mu_trig) continue;
        cut2++;
        cutflow->Fill(2, evtw);
        
        // Preselection of good leptons                                                                
        int n_mu = 0;
        int n_el = 0;
        int n_lep = 0;
        int g_lep = 0;

        //Loop over leptons
        for(unsigned int ii=0; ii<lep_n; ii++){
            
            if( lep_pt[ii] < 25000.0 ) continue;
            hist_lept_pt->Fill(lep_pt[ii]/1000 , evtw);
            if( lep_ptcone30[ii]/lep_pt[ii] > 0.15 ) continue;
            hist_lept_pt_cone30->Fill(lep_ptcone30[ii] / lep_pt[ii] , evtw);
            if( lep_etcone20[ii]/lep_pt[ii] > 0.15 ) continue;  
            hist_lept_et_cone20->Fill(lep_etcone20[ii] / lep_pt[ii] , evtw);
            // Moun
            if( lep_type [ii]==13 && TMath::Abs(lep_eta[ii]) < 2.5 ){
                n_mu++; 
                g_lep = ii;
                hist_lept_eta->Fill(lep_eta[ii] , evtw);}
            // Electron
            if( lep_type [ii]==11 && TMath::Abs(lep_eta[ii]) < 2.5 ){
                if( TMath::Abs(lep_eta[ii]) < 1.40 || TMath::Abs(lep_eta[ii]) > 1.50 ){
                    n_el++; 
                    g_lep = ii;
                    hist_lept_eta->Fill(lep_eta[ii] , evtw);}}
        }
        n_lep = n_el + n_mu;
    
        //Select events with only 1 good lepton and fill the cutflow histogram 
        if (n_lep != 1) continue;
        //Example:
        //Third cut (one good lepton):
        cutflow->Fill(3, evtw); 
        cut3++;
    
        int n_jets=0;
        int n_bjets=0;

        //Fourth cut: At least 4 jets
        if(jet_n<4) continue; 
        cutflow->Fill(4, evtw); 
        cut4++;
        
        //Number of jets distribution
        hist_njets->Fill(jet_n , evtw);

        for(unsigned int jj=0; jj<jet_n; jj++){
            
            
            
            
            
            // To complete: apply jet cuts to find the good jets
            if(jet_pt[jj] < 25000.) continue;
            hist_jets_pt-> Fill(jet_pt[jj]/1000 , evtw);
            //Eta cut
            if(jet_eta[jj] > 2.5) continue;
            hist_jets_eta-> Fill(jet_eta[jj] , evtw);
            // JVF cleaning
            if(jet_pt[jj] < 50000. && TMath::Abs(jet_eta[jj]) < 2.4){
                if(jet_jvf[jj] < 0.5) continue;}
            hist_jets_jvf-> Fill(jet_jvf[jj] , evtw);
            
            n_jets++;
            // cut on 0.7892 MV1 and count the number of b-jets
            if(jet_mv1[jj] < 0.7892) continue;
            hist_jets_mv1-> Fill(jet_mv1[jj] , evtw);
            
            n_bjets++;
        }
    
        //Fifth cut: At least 4 good jets
        if(n_jets<4) continue; 
        cutflow->Fill(5, evtw); 
        cut5++;
    
        //Sixth cut: at least one b-jet
        if(n_bjets < 2) continue;
        
        //cutflow
        cutflow-> Fill(6, evtw);
        cut6++;
        
        hist_nbjets-> Fill(n_bjets , evtw);
        
        //Seventh cut: MET > 30 GeV
        if(MET < 30000.) continue;
        
        //cutflow
        cutflow-> Fill(7, evtw);
        cut7++;
        
        hist_MET-> Fill(MET / 1000 , evtw);
    
        // TLorentzVector definitions                                                               
        TLorentzVector Lepton  = TLorentzVector();
        TLorentzVector  MeT  = TLorentzVector();

        //To complete: Lorentz vectors for the lepton and MET. Use SetPtEtaPhiE().
        Lepton.SetPtEtaPhiE(lep_pt[g_lep], lep_eta[g_lep], lep_phi[g_lep], lep_E[g_lep]);
        MeT.SetPtEtaPhiE(MET, 0, MET_phi, MET);

        //Calculation of the mTW using TLorentz vectors  
        float mTW = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));

        //Eight cut: mTW > 30 GeV
        if (mTW < 30000.) continue;
        
        //curflow
        cutflow-> Fill(8, evtw);
        cut8++;
        
        hist_mTW-> Fill(mTW/1000 , evtw);
    }

    std::cout << "Done!" << std::endl;
    std::cout << "All events:" << nentries << std::endl;
    std::cout << "Cut1:" << cut1 << std::endl;
    std::cout << "Cut2:" << cut2 << std::endl;
    std::cout << "Cut3:" << cut3 << std::endl;
    std::cout << "Cut4:" << cut4 << std::endl;
    std::cout << "Cut5:" << cut5 << std::endl;
    std::cout << "Cut6:" << cut6 << std::endl;
    std::cout << "Cut7:" << cut7 << std::endl;
    std::cout << "Cut8:" << cut8 << std::endl;
    
    // Histogram for Cuts
    canvas-> SetLogy();
    cutflow->SetMarkerStyle(22);
    cutflow-> SetFillColor(kBlue);
    cutflow->Draw("");
    canvas-> Print("HGraphsMC/cutflow.png");
    canvas->Clear();
    
    //Histogram for Leptons
    hist_lept_pt->SetMarkerStyle(22);
    hist_lept_pt->SetFillColor(kRed);
    hist_lept_pt->Draw();
    canvas->Print("HGraphsMC/hist_lept_pt.png");
    canvas->Clear();

    hist_lept_pt_cone30->SetMarkerStyle(22);
    hist_lept_pt_cone30->SetFillColor(kRed);
    hist_lept_pt_cone30->Draw();
    canvas->Print("HGraphsMC/hist_lept_pt_cone30.png");
    canvas->Clear();

    hist_lept_et_cone20->SetMarkerStyle(22);
    hist_lept_et_cone20->SetFillColor(kRed);
    hist_lept_et_cone20->Draw();
    canvas->Print("HGraphsMC/hist_lept_et_cone20.png");
    canvas->Clear();

    hist_lept_eta->SetMarkerStyle(22);
    hist_lept_eta->SetFillColor(kRed);
    hist_lept_eta->Draw();
    canvas->Print("HGraphsMC/hist_lept_eta.png");
    canvas->Clear();

    //Histogram for Jets

    hist_njets->SetMarkerStyle(22);
    hist_njets->SetFillColor(kCyan);
    hist_njets->Draw();
    canvas->Print("HGraphsMC/hist_njets.png");
    canvas->Clear();

    hist_jets_pt->SetMarkerStyle(22);
    hist_jets_pt->SetFillColor(kCyan);
    hist_jets_pt->Draw();
    canvas->Print("HGraphsMC/hist_jets_pt.png");
    canvas->Clear();

    hist_jets_eta->SetMarkerStyle(22);
    hist_jets_eta->SetFillColor(kCyan);
    hist_jets_eta->Draw();
    canvas->Print("HGraphsMC/hist_jets_eta.png");
    canvas->Clear();

    hist_jets_jvf->SetMarkerStyle(22);
    hist_jets_jvf->SetFillColor(kCyan);
    hist_jets_jvf->Draw();
    canvas->Print("HGraphsMC/hist_jets_JVF.png");
    canvas->Clear();

    hist_jets_mv1->SetMarkerStyle(22);
    hist_jets_mv1->SetFillColor(kCyan);
    hist_jets_mv1->Draw();
    canvas->Print("HGraphsMC/hist_jets_MV1.png");
    canvas->Clear();

    //Histogram for b-Jets

    hist_nbjets->SetMarkerStyle(22);
    hist_nbjets->SetFillColor(kGreen);
    hist_nbjets->Draw();
    canvas->Print("HGraphsMC/hist_nbjets.png");
    canvas->Clear();
    canvas->SetLogy(false);

    //Histogram for MET

    hist_MET->SetMarkerStyle(22);
    hist_MET->SetFillColor(kGreen);
    hist_MET->Draw();
    canvas->Print("HGraphsMC/hist_MET.png");
    canvas->Clear();

    //Histogram for mTW

    hist_mTW->SetMarkerStyle(22);
    hist_mTW->SetFillColor(kGreen);
    hist_mTW->Draw();
    canvas->Print("HGraphsMC/hist_mTW.png");
    canvas->Clear();


}