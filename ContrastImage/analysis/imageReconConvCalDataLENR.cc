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

TH2D*        Transmission(TString, TString);
TH2D*        CalculateRatio(TH2D*, TH2D*);
void            Plot(TH2D*, TH2D*, TH2D*, TH2D*, TString);
Double_t GetMinimumAboveZero(TH2D*);

const static Double_t low_lower = 2.5;
const static Double_t low_upper = 4.5;
const static Double_t high_lower = 10.0;
const static Double_t high_upper = 15.5;
const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static Int_t numNewSlices = numSlices - 14;

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  //TH1::AddDirectory(kTRUE);

  TString outputFileName = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/imgs_lenrConvCalDataToss1.root";

    TString histOutFilePath = "/home/jharms/G4/ANSIsimulations/CNR_Zeff/results/lenr/";
    TH2D* transTotal = Transmission("total", histOutFilePath);
    TH2D* trans4 = Transmission("low", histOutFilePath);
    TH2D* trans15 = Transmission("high", histOutFilePath);

    TH2D* ratio = CalculateRatio(trans4, trans15);

    TFile* outputFile = new TFile(outputFileName, "RECREATE");
    trans4->Write();
    trans15->Write();
    transTotal->Write();
    ratio->Write();
    outputFile->Close();

    Plot(transTotal, trans4, trans15, ratio, "/home/jharms/G4/ANSIsimulations/CNR_Zeff/ReconImages/");

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
                                          numDets*2, 0 , numDets*2);

  Double_t lowerBound, upperBound;

  if (whichEnergy == "low"){
      lowerBound = low_lower;      
      upperBound = low_upper;
  }
  else if (whichEnergy == "high"){
      lowerBound = high_lower;    
      upperBound = high_upper;
  }
  else {
    lowerBound = 1.0;
    upperBound = 15.5;
  }

  Double_t countsAir[numDets*2];
  for (Int_t i = 0; i < numDets*2; i++){
    countsAir[i] = 0;
  }

  Int_t ffSliceNumbers[14];
  for (Int_t i = 0; i < 6; i++){
    ffSliceNumbers[i] = i;
  }
  for (Int_t i = 0; i < 8; i++){
    ffSliceNumbers[i+6] = 209 + i;
  }
  for (Int_t i = 0; i < 14; i++){
    TFile * ffFile = new TFile(path + "ConvCalSlice" + TString::Itoa(ffSliceNumbers[i], 10) + "_toss1_2.root");
    for (Int_t detIter = 0; detIter < 2*numDets; detIter++){
      TH1D* ff = (TH1D*)ffFile->Get("ConvCalDet"+TString::Itoa(detIter, 10) );
      Double_t ffCounts = ff->Integral( ff->FindBin(lowerBound), ff->FindBin(upperBound) ); ; 
      countsAir[detIter] += ffCounts;
    }
    ffFile->Close();
    delete ffFile;
  }
  for (Int_t i = 0; i < numDets*2; i++){
    countsAir[i] /= 14.;
  }

  for (Int_t sliceIter = 6; sliceIter < numSlices - 7; sliceIter++){
    TFile * histFile = new TFile(path + "ConvCalSlice"+TString::Itoa(sliceIter,10) + "_toss1_2.root");
    for (Int_t detIter = 0; detIter < 2*numDets; detIter++){
      TH1D * hist = (TH1D*)histFile->Get("ConvCalDet" + TString::Itoa(detIter, 10));
      Double_t counts = hist->Integral( hist->FindBin(lowerBound), hist->FindBin(upperBound) );
      Int_t binNum = img->GetBin(sliceIter - 6, detIter+1);
      img->SetBinContent(binNum, counts/countsAir[detIter]);
      Double_t transmissionError = sqrt((countsAir[detIter]*counts + counts*counts)/(countsAir[detIter]*countsAir[detIter]*countsAir[detIter]));
      img->SetBinError(binNum, transmissionError);
    }
    histFile->Close();
    delete histFile;
  }

  return img;

}

TH2D* CalculateRatio(TH2D* t4, TH2D* t15)
{

  TH2D* ratio = new TH2D("Ratio", "", numNewSlices, 0, numNewSlices, 
                                          numDets*2, 0 , numDets*2);

  Double_t val4, val15, error4, error15, ratioVal;
  Double_t min4 = GetMinimumAboveZero(t4);
  Double_t min15 = GetMinimumAboveZero(t15);

  for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
    for (Int_t detIter = 0; detIter < numDets*2; detIter++){

      Int_t binNum = ratio->GetBin(sliceIter+1,detIter+1);
      val4 = t4->GetBinContent(binNum) ;
      val15 = t15->GetBinContent(binNum);
      error4 = t4->GetBinError(binNum) ;
      error15 = t15->GetBinError(binNum);
      if (val4 == 0) val4 = min4; 
      else if (val4 > 1) val4 = 1.0;
      if (val15 == 0) val15 = min15; 
      else if (val15 > 1) val15 = 1.0;

      Double_t log4 = log(val4);
      Double_t log15 = log(val15);
      ratioVal = log15/log4;
      ratio->SetBinContent(binNum, ratioVal);
      Double_t t4Sq = val4*val4;
      Double_t t15Sq = val15*val15;
      Double_t lnT4Sq = log4*log4;
      Double_t lnT15Sq = log15*log15;
      Double_t ratioUncertainty = sqrt( (t4Sq * lnT4Sq * error15 * error15 + 
                                        t15Sq * lnT15Sq * error4 * error4) /
                                        (t4Sq * t15Sq * lnT4Sq * lnT4Sq) );
      ratio->SetBinError(binNum, ratioUncertainty);
    }
  }
  return ratio;
}
/*
TH2D* CalculateZeff(TH2D* ratio)
{
  TH2D* zeff = new TH2D("Zeff", "", numNewSlices, 0, numNewSlices, 
                                          numDets*2-1, 0 , numDets*2-1);

  Double_t zVal;
  for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
    for (Int_t detIter = 0; detIter < numDets*2-1; detIter++){
      Int_t binNum = ratio->GetBin(sliceIter,detIter+1);
      Double_t ratioVal = ratio->GetBinContent(binNum);
      if (ratioVal > 0.5 && ratioVal < 1.2) {
        zVal =  49.0410047271*ratioVal*ratioVal - 20.0870450228*ratioVal + 1.380531631;
      }
      else zVal = 0.9456060664*exp(3.306075377*ratioVal);

      if (zVal > 100) zVal = 100;
      
      zeff->SetBinContent(binNum, zVal);
    }

  }
  return zeff;  
}
*/

void Plot(TH2D* tTotal, TH2D* tLow, TH2D* tHigh,  TH2D* ratio, TString path)
{
  gStyle->SetPalette(53);
  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("c1","Total Transmission",0,0,700, 600);
  c1->SetLeftMargin(0.01);
  c1->SetBottomMargin(0.02);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.16);

  tTotal->GetXaxis()->SetNdivisions(206);
  tTotal->GetXaxis()->SetLabelSize(0.0);
  tTotal->GetXaxis()->SetTickLength(0.0);

  tTotal->GetYaxis()->SetNdivisions(140);
  tTotal->GetYaxis()->SetLabelSize(0.0);
  tTotal->GetYaxis()->SetTickLength(0.0);

  tTotal->GetZaxis()->SetNdivisions(7);
  tTotal->GetZaxis()->SetLabelSize(0.04);
  tTotal->GetZaxis()->SetTitleSize(0.05);
  tTotal->GetZaxis()->SetTitleOffset(1.1);
  tTotal->GetZaxis()->SetTitle("Transmitted Fraction");
  tTotal->GetZaxis()->SetRangeUser(0.0,1.0);
  tTotal->GetZaxis()->SetDecimals(kTRUE);
  tTotal->GetZaxis()->CenterTitle();

  tTotal->SetTitle("");
  tTotal->Draw("COLZ");
  tTotal->SetStats(kFALSE);
  tTotal->SetContour(99);
  c1->cd();

  TCanvas *c2 = new TCanvas("c2","tLow",0,0,700,600);
  c2->SetLeftMargin(0.01);
  c2->SetBottomMargin(0.02);
  c2->SetTopMargin(0.02);
  c2->SetRightMargin(0.16);

  tLow->GetXaxis()->SetNdivisions(206);
  tLow->GetXaxis()->SetLabelSize(0.0);
  tLow->GetXaxis()->SetTickLength(0.0);

  tLow->GetYaxis()->SetNdivisions(140);
  tLow->GetYaxis()->SetLabelSize(0.0);
  tLow->GetYaxis()->SetTickLength(0.0);

  tLow->GetZaxis()->SetNdivisions(7);
  tLow->GetZaxis()->SetLabelSize(0.04);
  tLow->GetZaxis()->SetTitleSize(0.05);
  tLow->GetZaxis()->SetTitleOffset(1.1);
  tLow->GetZaxis()->SetTitle("Transmitted Fraction");
  tLow->GetZaxis()->SetRangeUser(0.0,1.0);
  tLow->GetZaxis()->SetDecimals(kTRUE);
  tLow->GetZaxis()->CenterTitle();

  tLow->SetTitle("");
  tLow->Draw("COLZ");
  tLow->SetStats(kFALSE);
  tLow->SetContour(99);
  c2->cd();

  TCanvas *c3 = new TCanvas("c3","tLow",0,0,700,600);
  c3->SetLeftMargin(0.01);
  c3->SetBottomMargin(0.02);
  c3->SetTopMargin(0.02);
  c3->SetRightMargin(0.16);

  tHigh->GetXaxis()->SetNdivisions(206);
  tHigh->GetXaxis()->SetLabelSize(0.0);
  tHigh->GetXaxis()->SetTickLength(0.0);

  tHigh->GetYaxis()->SetNdivisions(140);
  tHigh->GetYaxis()->SetLabelSize(0.0);
  tHigh->GetYaxis()->SetTickLength(0.0);

  tHigh->GetZaxis()->SetNdivisions(7);
  tHigh->GetZaxis()->SetLabelSize(0.04);
  tHigh->GetZaxis()->SetTitleSize(0.05);
  tHigh->GetZaxis()->SetTitleOffset(1.1);
  tHigh->GetZaxis()->SetTitle("Transmitted Fraction");
  tHigh->GetZaxis()->SetRangeUser(0.0,1.0);
  tHigh->GetZaxis()->SetDecimals(kTRUE);
  tHigh->GetZaxis()->CenterTitle();

  tHigh->SetTitle("");
  tHigh->Draw("COLZ");
  tHigh->SetStats(kFALSE);
  tHigh->SetContour(99);
  c3->cd();


  double levels[99];
  levels[0] = 0;
  levels[1] = 0.4;
  for (int i = 1; i < 98; i++){
    levels[i+1] = ((1.4-0.4)/97.)*i+0.4;
  }

  TCanvas *c4 = new TCanvas("c4","RatioMap",0,0,700,600);
  c4->SetLeftMargin(0.01);
  c4->SetBottomMargin(0.02);
  c4->SetTopMargin(0.02);
  c4->SetRightMargin(0.16);

  ratio->GetXaxis()->SetNdivisions(206);
  ratio->GetXaxis()->SetLabelSize(0.0);
  ratio->GetXaxis()->SetTickLength(0.0);

  ratio->GetYaxis()->SetNdivisions(140);
  ratio->GetYaxis()->SetLabelSize(0.0);
  ratio->GetYaxis()->SetTickLength(0.0);

  ratio->GetZaxis()->SetNdivisions(7);
  ratio->GetZaxis()->SetLabelSize(0.04);
  ratio->GetZaxis()->SetTitleSize(0.05);
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

  c1->SaveAs(path+ "lenrTTotalConvCalDataToss1.pdf");
  c2->SaveAs(path+ "lenrTLowConvCalDataToss1.pdf");
  c3->SaveAs(path+ "lenrTHighConvCalDataToss1.pdf");
  c4->SaveAs(path+ "lenrRatioConvCalDataToss1.pdf");
}

Double_t GetMinimumAboveZero(TH2D* hist)
{
  Int_t nBinsX = hist->GetNbinsX();
  Int_t nBinsY = hist->GetNbinsY();
  Double_t minValue = 1;
  for (Int_t i = 0; i < nBinsX; i++){
    for (Int_t j = 0; j < nBinsY; j++){
      Double_t binVal = hist->GetBinContent(hist->GetBin(i+1,j+1));
      if (binVal > 0 && binVal < minValue){
        minValue = binVal;
      }
    }
  }
  return minValue;
}