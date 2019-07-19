#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>

#include <iostream>
#include <fstream>

TH2D*        Transmission(TString, TString);
TH2D*        CalculateRatio(TH2D*, TH2D*);
TH2D*        CalculateZeff(TH2D*);
void            Plot(TH2D*, TH2D*, TH2D*, TH2D*, TH2D*, TString);
Double_t*   CreateEnergyAxis(TH1D*);

const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static Int_t numNewSlices = numSlices - 4; // flatfield is first and last slices
const static TString source = "lenr";
const static Int_t multiplier = 50;

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  //TH1::AddDirectory(kTRUE);

  TString baseFolder = "/home/jharms/G4/ANSIsimulations/CNR_Zeff/results/" + source + "/";

  TString outputFileName = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/imgs_" + source + "_" + TString::Itoa(multiplier, 10) + "x.root";

    TH2D* trans4 = Transmission("low", baseFolder);
    TH2D* trans15 = Transmission("high", baseFolder);
    TH2D* transTotal = Transmission("total", baseFolder);

    TH2D* ratio = CalculateRatio(trans4, trans15);
    TH2D* zeff = CalculateZeff(ratio);

    TFile* outputFile = new TFile(outputFileName, "RECREATE");
    trans4->Write();
    trans15->Write();
    transTotal->Write();
    ratio->Write();
    zeff->Write();
    outputFile->Close();

    Plot(transTotal, trans4, trans15, ratio, zeff, "/home/jharms/G4/ANSIsimulations/CNR_Zeff/ReconImages/");

  return 0;
  
}

TH2D* Transmission(TString whichEnergy, TString path)
{
  TString histTitle;
  if (whichEnergy == "low"){
    histTitle = "T4";
  }
  else if (whichEnergy == "high"){
    histTitle = "T15";
  }
  else {
    // default is the total
    histTitle = "Ttotal";
  }

  TH2D* img = new TH2D(histTitle, "", numNewSlices, 0, numNewSlices, 
                                          numDets*2-1, 0 , numDets*2-1);

  Double_t lowerBound, upperBound;

  if (whichEnergy == "low"){
      lowerBound = 0;      
      upperBound = 150;
  }
  else if (whichEnergy == "high"){
      lowerBound = 1000;    
      upperBound = 3000;
  }
  else {
    lowerBound = 0;
    upperBound = 3000;
  }

  Double_t countsAir[numDets*2-1];

  TFile * ff1File = new TFile(path + "convSlice0" + "_" + source + "_" + TString::Itoa(multiplier, 10) + "x.root");
  TFile * ff2File = new TFile(path + "convSlice1" + "_" + source + "_" + TString::Itoa(multiplier, 10) + "x.root");
  TFile * ff3File = new TFile(path + "convSlice218" + "_" + source + "_" + TString::Itoa(multiplier, 10) + "x.root");
  TFile * ff4File = new TFile(path + "convSlice219" + "_" + source + "_" + TString::Itoa(multiplier, 10) + "x.root");

  for (Int_t detIter = 0; detIter < numDets*2-1; detIter++){
    countsAir[detIter] = 0;
    TH1D* ff1 = (TH1D*)ff1File->Get("Det"+TString::Itoa(detIter+1, 10) );
    TH1D* ff2 = (TH1D*)ff2File->Get("Det"+TString::Itoa(detIter+1, 10) );
    TH1D* ff3 = (TH1D*)ff3File->Get("Det"+TString::Itoa(detIter+1, 10) );
    TH1D* ff4 = (TH1D*)ff4File->Get("Det"+TString::Itoa(detIter+1, 10) );
    Double_t ff1Counts = ff1->Integral( ff1->FindBin(lowerBound), ff1->FindBin(upperBound) ); 
    Double_t ff2Counts = ff2->Integral( ff2->FindBin(lowerBound), ff2->FindBin(upperBound) ); 
    Double_t ff3Counts = ff3->Integral( ff3->FindBin(lowerBound), ff3->FindBin(upperBound) ); 
    Double_t ff4Counts = ff4->Integral( ff4->FindBin(lowerBound), ff4->FindBin(upperBound) ); 
    countsAir[detIter] = (ff1Counts + ff2Counts + ff3Counts + ff4Counts) / 4.;
  }
  ff1File->Close();
  ff2File->Close();
  ff3File->Close();
  ff4File->Close();
  delete ff1File;
  delete ff2File;
  delete ff3File;
  delete ff4File;

  for (Int_t sliceIter = 2; sliceIter < numSlices - 2; sliceIter++){
    TFile * histFile = new TFile(path + "convSlice"+TString::Itoa(sliceIter,10) + "_" + source + "_" + TString::Itoa(multiplier, 10) + "x.root");
    for (Int_t detIter = 0; detIter < numDets*2-1; detIter++){
      TH1D * hist = (TH1D*)histFile->Get("Det" + TString::Itoa(detIter+1, 10));
      Int_t binNum = img->GetBin(sliceIter , detIter+1);
      Double_t pixelVal = hist->Integral( hist->FindBin(lowerBound), hist->FindBin(upperBound) ) / countsAir[detIter];
      img->SetBinContent(binNum, pixelVal);
    }
    histFile->Close();
    delete histFile;
  }

  return img;

}

TH2D* CalculateRatio(TH2D* t4, TH2D* t15)
{

  TH2D* ratio = new TH2D("Ratio", "", numNewSlices, 0, numNewSlices, 
                                          numDets*2-1, 0 , numDets*2-1);

  Double_t val4, val15, ratioVal;

  for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
    for (Int_t detIter = 0; detIter < numDets*2-1; detIter++){

      Int_t binNum = ratio->GetBin(sliceIter,detIter+1);
      val4 = t4->GetBinContent(binNum) ;
      val15 = t15->GetBinContent(binNum);
      if ((sliceIter > 0 && sliceIter < numNewSlices-1) && (detIter > 0 && detIter < numDets*2-2)){
        if (val4 == 0){
          Double_t val4_yup = t4->GetBinContent(ratio->GetBin(sliceIter-1, detIter));
          Double_t val4_ydown = t4->GetBinContent(ratio->GetBin(sliceIter-1, detIter+2));
          Double_t val4_xup = t4->GetBinContent(ratio->GetBin(sliceIter, detIter+1));
          Double_t val4_xdown = t4->GetBinContent(ratio->GetBin(sliceIter-2, detIter+1));
          val4 = 0.25*(val4_ydown + val4_yup + val4_xup + val4_xdown);
        }
        else if (val15 == 0){
          Double_t val15_yup = t15->GetBinContent(ratio->GetBin(sliceIter-1, detIter));
          Double_t val15_ydown = t15->GetBinContent(ratio->GetBin(sliceIter-1, detIter+2));
          Double_t val15_xup = t15->GetBinContent(ratio->GetBin(sliceIter, detIter+1));
          Double_t val15_xdown = t15->GetBinContent(ratio->GetBin(sliceIter-2, detIter+1));
          val15 = 0.25*(val15_ydown + val15_yup + val15_xup + val15_xdown);
        }
      }


      if (val4 >=1 || val15 >=1 ){
        ratioVal = 0.01;
      }
      else if (val4 == 0 || val15 == 0){
        ratioVal = 0.01;
      } else {
        ratioVal = log(val15)/log(val4);
      }
      if ( (ratioVal > 1.5) || (ratioVal <= 0) ) {
        ratioVal = 0.01;
      }
      ratio->SetBinContent(binNum, ratioVal);
    }
  }
  return ratio;
}

TH2D* CalculateZeff(TH2D* ratio)
{
  TH2D* zeff = new TH2D("Zeff", "", numNewSlices, 0, numNewSlices, 
                                          numDets*2-1, 0 , numDets*2-1);

  Double_t zVal;
  for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
    for (Int_t detIter = 0; detIter < numDets*2-1; detIter++){
      Int_t binNum = ratio->GetBin(sliceIter,detIter+1);
      Double_t ratioVal = ratio->GetBinContent(binNum);
      if (ratioVal < 0.6) zVal =  44.4526769455 * pow(ratioVal, 3.3422754017);
      else if (ratioVal < 1.1) zVal = 72.0564036518*ratioVal*ratioVal - 32.1593779377*ratioVal + 2.3154223811;
      else zVal = 2118.657236905*ratioVal*ratioVal - 4524.030697996*ratioVal + 2467.1041152516;

      if (zVal > 100) zVal = 100;
      
      zeff->SetBinContent(binNum, zVal);
    }

  }
  return zeff;  
}

void Plot(TH2D* transmissionTotal, TH2D* transmission4, TH2D* transmission15,  TH2D* ratio, TH2D* zeff, TString path)
{
  gStyle->SetPalette(53);
  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("c1","Total Transmission",0,0,528,378);

  transmissionTotal->GetXaxis()->SetNdivisions(0);
  transmissionTotal->GetXaxis()->SetLabelSize(0.0);

  transmissionTotal->GetYaxis()->SetNdivisions(numDets*2-1);
  transmissionTotal->GetYaxis()->SetLabelSize(0.0);
  transmissionTotal->GetYaxis()->SetTickLength(0.01);

  transmissionTotal->GetZaxis()->SetNdivisions(5);
  transmissionTotal->GetZaxis()->SetLabelSize(0.07);
  transmissionTotal->GetZaxis()->SetTitleOffset(1.0);
  transmissionTotal->GetZaxis()->SetTitle("");
  transmissionTotal->GetZaxis()->SetRangeUser(0.0,1.0);
  transmissionTotal->GetZaxis()->SetDecimals(kTRUE);

  transmissionTotal->SetTitle("");
  transmissionTotal->Draw("COLZ");
  transmissionTotal->SetStats(kFALSE);
  transmissionTotal->SetContour(99);
  
  c1->SetRightMargin(0.3);
  c1->cd();

  TCanvas *c2 = new TCanvas("c2","T4 MeV",0,0,528,378);

  transmission4->GetZaxis()->SetTitle("");
  transmission4->GetZaxis()->SetRangeUser(0.0,1.);
  
  transmission4->GetXaxis()->SetNdivisions(numNewSlices);
  transmission4->GetYaxis()->SetNdivisions(numDets*2-1);
  transmission4->GetZaxis()->SetNdivisions(5);

  transmission4->GetYaxis()->SetLabelSize(0.0);
  transmission4->GetXaxis()->SetLabelSize(0.0);
  transmission4->GetZaxis()->SetLabelSize(0.07);
  transmission4->GetZaxis()->SetTitleOffset(1.0);

  transmission4->SetTitle("");
  transmission4->Draw("COLZ");
  transmission4->SetStats(kFALSE);
  transmission4->SetContour(99);

  c2->SetRightMargin(0.3);
  c2->cd();


  TCanvas *c3 = new TCanvas("c3","T15 MeV",0,0,528,378);

  transmission15->GetZaxis()->SetTitle("");
  transmission15->GetZaxis()->SetRangeUser(0.0,1.);
  
  transmission15->GetXaxis()->SetNdivisions(numNewSlices);
  transmission15->GetYaxis()->SetNdivisions(numDets*2-1);
  transmission15->GetZaxis()->SetNdivisions(5);

  transmission15->GetYaxis()->SetLabelSize(0.0);
  transmission15->GetXaxis()->SetLabelSize(0.0);
  transmission15->GetZaxis()->SetLabelSize(0.07);
  transmission15->GetZaxis()->SetTitleOffset(1.0);

  transmission15->SetTitle("");
  transmission15->Draw("COLZ");
  transmission15->SetStats(kFALSE);
  transmission15->SetContour(99);

  c3->SetRightMargin(0.3);
  c3->cd();


  double levels[99];
  levels[0] = 0;
  levels[1] = 0.4;
  for (int i = 1; i < 98; i++){
    levels[i+1] = ((1.4-0.4)/97.)*i+0.4;
  }

  TCanvas *c4 = new TCanvas("c4","RatioMap",0,0,528,378);

  ratio->GetZaxis()->SetTitle("");
  ratio->GetZaxis()->SetRangeUser(0.001,1.4);
  
  ratio->GetXaxis()->SetNdivisions(numNewSlices);
  ratio->GetYaxis()->SetNdivisions(numDets*2-1);
  ratio->GetZaxis()->SetNdivisions(5);

  ratio->SetTitle("");
  ratio->Draw("COLZ");
  ratio->SetStats(kFALSE);
  ratio->SetContour(99,levels);

  ratio->GetYaxis()->SetLabelSize(0.0);
  ratio->GetXaxis()->SetLabelSize(0.0);
  ratio->GetZaxis()->SetLabelSize(0.07);
  ratio->GetZaxis()->SetTitleOffset(1.0);

  c4->SetRightMargin(0.3);
  c4->cd();


  TCanvas *c5 = new TCanvas("c5","Zeff",528,378);
  zeff->GetZaxis()->SetRangeUser(-.1,100);
  
  zeff->GetXaxis()->SetNdivisions(numNewSlices);
  zeff->GetYaxis()->SetNdivisions(numDets*2-1);
  zeff->GetZaxis()->SetNdivisions(5);

  zeff->GetZaxis()->SetTitle("Z_{eff}");
  zeff->GetZaxis()->SetTitleOffset(1.0);
  zeff->SetTitle("");
  zeff->Draw("COLZ");
  zeff->SetStats(kFALSE);


  zeff->GetYaxis()->SetLabelSize(0.0);
  zeff->GetXaxis()->SetLabelSize(0.0);
  zeff->GetZaxis()->SetLabelSize(0.07);
  zeff->GetZaxis()->SetTitleSize(0.0);
  zeff->SetContour(99);
  
  c5->cd();
  c5->SetRightMargin(0.3);

  c1->SaveAs(path+ "transmissionTotal" + source + "_" + TString::Itoa(multiplier, 10) + "x.eps");
  c2->SaveAs(path+"transmission4" + source + "_" + TString::Itoa(multiplier, 10) + "x.eps");
  c3->SaveAs(path+"transmission15" + source + "_" + TString::Itoa(multiplier, 10) + "x.eps");
  c4->SaveAs(path+"ratio" + source + "_" + TString::Itoa(multiplier, 10) + "x.eps");
  c5->SaveAs(path+"zeff" + source + "_" + TString::Itoa(multiplier, 10) + "x.eps");
}
