#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>
#include <TRandom3.h>

#include <iostream>
#include <fstream>

void            Plot(TH2D*, TString);
const static Int_t demultiplier = 1;

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  //TH1::AddDirectory(kTRUE);

  gStyle->SetPalette(53);
  TString baseFolder = "~/Dropbox/Grad School/PhD Research/G4/ANSIsimulations/CNR_Zeff/ReconImages/";

  TFile* inputFileBrem= new TFile(baseFolder + "bremRatiosNS.root");
  TH2D* ratioBremOrig = (TH2D*)inputFileBrem->Get("bremRatioOrigtoss"+TString::Itoa(demultiplier,10));
  TH2D* ratioBremNS = (TH2D*)inputFileBrem->Get("bremRatioNStoss"+TString::Itoa(demultiplier,10));

  TFile* inputFileLenr= new TFile(baseFolder + "lenrRatiosNS.root");
  TH2D* ratioLenrOrig = (TH2D*)inputFileLenr->Get("lenrRatioOrigtoss"+TString::Itoa(demultiplier,10));
  TH2D* ratioLenrNS = (TH2D*)inputFileLenr->Get("lenrRatioNStoss"+TString::Itoa(demultiplier,10));

  Plot(ratioBremOrig, baseFolder + "bremRatioRawDataOrigToss"+TString::Itoa(demultiplier,10)+".eps");
  Plot(ratioBremNS, baseFolder + "bremRatioRawDataNSToss"+TString::Itoa(demultiplier,10)+".eps");
  Plot(ratioLenrOrig, baseFolder + "lenrRatioRawDataOrigToss"+TString::Itoa(demultiplier,10)+".eps");
  Plot(ratioLenrNS, baseFolder + "lenrRatioRawDataNSToss"+TString::Itoa(demultiplier,10)+".eps");

  delete ratioLenrOrig;
  delete ratioLenrNS;
  delete ratioBremOrig;
  delete ratioBremNS;
  inputFileLenr->Close();
  delete inputFileLenr;
  inputFileBrem->Close();
  delete inputFileBrem;

  return 0;
  
}

void Plot(TH2D* ratio, TString fileName)
{
  double levels[99];
  levels[0] = 0;
  levels[1] = 0.4;
  for (int i = 1; i < 98; i++){
    levels[i+1] = ((1.4-0.4)/97.)*i+0.4;
  }

  TCanvas *c4 = new TCanvas(fileName,"RatioMap",0,0,700,600);
  c4->SetLeftMargin(0.01);
  c4->SetBottomMargin(0.02);
  c4->SetTopMargin(0.02);
  c4->SetRightMargin(0.22);

  ratio->GetXaxis()->SetNdivisions(206);
  ratio->GetXaxis()->SetLabelSize(0.0);
  ratio->GetXaxis()->SetTickLength(0.0);

  ratio->GetYaxis()->SetNdivisions(140);
  ratio->GetYaxis()->SetLabelSize(0.0);
  ratio->GetYaxis()->SetTickLength(0.0);

  ratio->GetZaxis()->SetNdivisions(7);
  ratio->GetZaxis()->SetLabelSize(0.07);
  ratio->GetZaxis()->SetTitleSize(0.08);
  ratio->GetZaxis()->SetTitleOffset(1.1);
  ratio->GetZaxis()->SetTitle("R-Value");
  ratio->GetZaxis()->SetRangeUser(0.001,1.4);
  ratio->GetZaxis()->SetDecimals(kTRUE);
  ratio->GetZaxis()->CenterTitle();

  ratio->SetTitle("");
  ratio->Draw("COLZ");
  ratio->SetStats(kFALSE);
  ratio->SetContour(99,levels);
  c4->cd();
  c4->SaveAs(fileName);
}
