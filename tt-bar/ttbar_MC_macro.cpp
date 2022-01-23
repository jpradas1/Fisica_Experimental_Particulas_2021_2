#include <iostream>
#include <stdio.h>
#include <string>

void ttbar_macro (){
    
    TFile *file = TFile::Open("ttbar_8TeV.root");
    TTree *tree = (TTree*) file->Get("mini");
    tree->Print();


}