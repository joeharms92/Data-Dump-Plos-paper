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

void            TossDataAllHists(TString, Int_t, TRandom3*, TH1D*, Double_t);
TH2D*        Transmission(TString, TString);
TH2D*        CalculateRatio(TH2D*, TH2D*);
//TH2D*        CalculateZeff(TH2D*);
void            Plot(TH2D*, TH2D*, TH2D*, TString);
void TossData(TH1D*, TRandom3*, TH1D*, Double_t, Double_t, Double_t);
Double_t GetMinimumAboveZero(TH2D*);

const static Double_t low_lower = 1.0;
const static Double_t low_upper = 5.0;
const static Double_t high_lower = 5.0;
const static Double_t high_upper = 9.0;
const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static Int_t numNewSlices = numSlices - 14; // flatfield is first and last slices
const static Int_t demultiplier = 10;

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  //TH1::AddDirectory(kTRUE);

  TString baseFolder = "/home/jharms/G4/ANSIsimulations/CNR_Zeff/results/";

  TString outputFileName = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/imgs_bremRawDataToss"+TString::Itoa(demultiplier,10)+".root";
  /*TFile* efficiencyFile = new TFile("~/G4/CherenkovResponse/Results/G4Outputs/totalQuartzEfficiencies.root");
  TH1D* efficencyHist = (TH1D*)efficiencyFile->Get("efficiency");
  TRandom3 * rando = new TRandom3();
  // This ratio reduces the total dose to 5 mrem if demultiplier = 1
  TossDataAllHists(baseFolder, 6, rando, efficencyHist, 154.3727535*((Double_t)demultiplier));
  TossDataAllHists(baseFolder, 9, rando, efficencyHist, 45.81010304*((Double_t)demultiplier));
  delete efficencyHist;
  efficiencyFile->Close();
  delete efficiencyFile;*/
  TH2D* trans4 = Transmission("low", baseFolder);
  TH2D* trans15 = Transmission("high", baseFolder);
  TH2D* transTotal = Transmission("total", baseFolder);
  TH2D* ratio = CalculateRatio(trans4, trans15);
  TFile* outputFile = new TFile(outputFileName, "RECREATE");
  trans4->Write();
  trans15->Write();
  transTotal->Write();
  ratio->Write();
  outputFile->Close();

  Plot(trans4, trans15, ratio, "/home/jharms/G4/ANSIsimulations/CNR_Zeff/ReconImages/");

  return 0;
  
}

void TossDataAllHists(TString path, Int_t energy, TRandom3* rng, TH1D* effHist, Double_t actualTossNo)
{
  for (Int_t sliceIter = 0; sliceIter < numSlices; sliceIter++){
    cout << sliceIter << endl;
    TFile * outputHistFile = new TFile(path + "brem" + TString::Itoa(energy, 10) + "/Slice" + TString::Itoa(sliceIter, 10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem" + TString::Itoa(energy, 10) + ".root", "RECREATE");
    TFile * histFile_run0 = new TFile(path + "brem" + TString::Itoa(energy, 10) + "/Slice"+TString::Itoa(sliceIter,10) + "_run0_brem" + TString::Itoa(energy, 10) + ".root");
    TFile * histFile_run1 = new TFile(path + "brem" + TString::Itoa(energy, 10) + "/Slice"+TString::Itoa(sliceIter,10) + "_run1_brem" + TString::Itoa(energy, 10) + ".root");
    for (Int_t detIter = 0; detIter < numDets; detIter++){
      TH1D * hist_run0 = (TH1D*)histFile_run0->Get("Det" + TString::Itoa(detIter, 10));
      TossData(hist_run0,rng, effHist, low_lower, high_upper, actualTossNo);
      TH1D * hist_run1 = (TH1D*)histFile_run1->Get("Det" + TString::Itoa(detIter, 10));
      TossData(hist_run1,rng, effHist, low_lower, high_upper, actualTossNo);
      hist_run0->SetName("Det" + TString::Itoa(2*detIter+1, 10));
      hist_run1->SetName("Det" + TString::Itoa(2*detIter, 10));
      outputHistFile->cd();
      hist_run1->Write();
      hist_run0->Write();
      delete hist_run1;
      delete hist_run0;
    }
    outputHistFile->Close();
    delete outputHistFile;
    histFile_run0->Close();
    delete histFile_run0;
    histFile_run1->Close();
    delete histFile_run1;
  }

}

TH2D* Transmission(TString whichEnergy, TString path)
{
  TString histTitle;
  if (whichEnergy == "low"){
    histTitle = "tLow";
  }
  else if (whichEnergy == "high"){
    histTitle = "tHigh";
  }
  else {
    // default is the total
    histTitle = "Ttotal";
  }

  TH2D* img = new TH2D(histTitle, "", numNewSlices, 0, numNewSlices, 
                                          numDets*2, 0 , numDets*2);

  Double_t lowerBound, upperBound;
  if (whichEnergy == "low"){
      lowerBound = 1.0;      
      upperBound = 5.0;
  }
  else if (whichEnergy == "high"){
      lowerBound = 5.0;    
      upperBound = 9.0;
  }
  else {
    lowerBound = 1.0;
    upperBound = 6.0;
  }

  Double_t countsAir[numDets*2];
  for (Int_t i = 0; i < numDets*2; i++){
    countsAir[i] = 0;
  }

  Int_t ffSliceNumbers[14];
  for (Int_t i = 0; i < 6; i++){
    ffSliceNumbers[i] = i;
  }
  for (Int_t i = 0; i < 10; i++){
    ffSliceNumbers[i+6] = 209 + i;
  }
  for (Int_t i = 0; i < 14; i++){
    TFile * ffFile1, *ffFile2;
    if (whichEnergy == "low"){
      ffFile1 = new TFile(path + "brem6/Slice" + TString::Itoa(ffSliceNumbers[i], 10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem6.root");
      //delete ffFile2;
    } else if (whichEnergy == "high"){
      ffFile1 = new TFile(path + "brem9/Slice" + TString::Itoa(ffSliceNumbers[i], 10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem9.root");
      //delete ffFile2;
    } else {
      ffFile1 = new TFile(path + "brem6/Slice" + TString::Itoa(ffSliceNumbers[i], 10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem6.root");
      ffFile2 = new TFile(path + "brem9/Slice" + TString::Itoa(ffSliceNumbers[i], 10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem9.root");
    }
    for (Int_t detIter = 0; detIter < 2*numDets; detIter++){
      TH1D* ff1 = (TH1D*)ffFile1->Get("Det"+TString::Itoa(detIter, 10) );
      Double_t ffCounts = ff1->Integral( ff1->FindBin(lowerBound), ff1->FindBin(upperBound) );
      if (whichEnergy == "total"){
        TH1D* ff2 = (TH1D*)ffFile2->Get("Det"+TString::Itoa(detIter, 10) );
        ffCounts +=  ff2->Integral( ff2->FindBin(lowerBound), ff2->FindBin(9.0) );
      }
      countsAir[detIter] += ffCounts;
    }
    ffFile1->Close();
    delete ffFile1;
    if (whichEnergy == "total"){
      ffFile2->Close();
      delete ffFile2;
    }
  }
  for (Int_t i = 0; i < numDets*2; i++){
    countsAir[i] /= 14.;
  }

  for (Int_t sliceIter = 6; sliceIter < numSlices - 7; sliceIter++){
    TFile* histFile1, *histFile2;
    if (whichEnergy == "low"){
      histFile1 = new TFile(path + "brem6/Slice"+TString::Itoa(sliceIter,10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem6.root");
      //delete histFile1;
    } else if (whichEnergy == "high") {
      histFile1 = new TFile(path + "brem9/Slice"+TString::Itoa(sliceIter,10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem9.root");
      //delete histFile2;
    } else {
      histFile1 = new TFile(path + "brem6/Slice"+TString::Itoa(sliceIter,10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem6.root");
      histFile2 = new TFile(path + "brem9/Slice"+TString::Itoa(sliceIter,10) + "_toss" + TString::Itoa(demultiplier, 10) + "_brem9.root");
    }
    for (Int_t detIter = 0; detIter < 2*numDets; detIter++){
      TH1D * hist1 = (TH1D*)histFile1->Get("Det" + TString::Itoa(detIter, 10));
      Double_t counts = hist1->Integral( hist1->FindBin(lowerBound), hist1->FindBin(upperBound) );
      if (whichEnergy == "total") {
        TH1D * hist2 = (TH1D*)histFile2->Get("Det" + TString::Itoa(detIter, 10));
        counts += hist2->Integral( hist2->FindBin(lowerBound), hist2->FindBin(9.0) );
      }
      Int_t binNum = img->GetBin(sliceIter  - 6, detIter+1);
      img->SetBinContent(binNum, counts/countsAir[detIter]);
      Double_t transmissionError = sqrt((countsAir[detIter]*counts + counts*counts)/(countsAir[detIter]*countsAir[detIter]*countsAir[detIter]));
      img->SetBinError(binNum, transmissionError);
    }
    histFile1->Close();
    delete histFile1;
    if (whichEnergy == "total") {
      histFile2->Close();
      delete histFile2;
    }
  }

  return img;

}

TH2D* CalculateRatio(TH2D* tLow, TH2D* tHigh)
{

  TH2D* ratio = new TH2D("Ratio", "", numNewSlices, 0, numNewSlices, 
                                          numDets*2, 0 , numDets*2);

  Double_t valLow, valHigh, errorLow, errorHigh, ratioVal;
  Double_t minLow = GetMinimumAboveZero(tLow);
  Double_t minHigh = GetMinimumAboveZero(tHigh);

  for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
    for (Int_t detIter = 0; detIter < numDets*2; detIter++){

      Int_t binNum = ratio->GetBin(sliceIter+1,detIter+1);
      valLow = tLow->GetBinContent(binNum) ;
      valHigh = tHigh->GetBinContent(binNum);
      errorLow = tLow->GetBinError(binNum) ;
      errorHigh = tHigh->GetBinError(binNum);
      if (valLow == 0) valLow = minLow; 
      else if (valLow > 1) valLow = 1.0;
      if (valHigh == 0) valHigh = minHigh; 
      else if (valHigh > 1) valHigh = 1.0;

      Double_t logLow = log(valLow);
      Double_t logHigh = log(valHigh);
      ratioVal = logHigh/logLow;
      ratio->SetBinContent(binNum, ratioVal);
      Double_t tLowSq = valLow*valLow;
      Double_t tHighSq = valHigh*valHigh;
      Double_t lnTLowSq = logLow*logLow;
      Double_t lnTHighSq = logHigh*logHigh;
      Double_t ratioUncertainty = sqrt( (tLowSq * lnTLowSq * errorHigh * errorHigh + 
                                        tHighSq * lnTHighSq * errorLow * errorLow) /
                                        (tLowSq * tHighSq * lnTLowSq * lnTLowSq) );
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
      if (ratioVal > 0.53 && ratioVal < 0.85) {
        zVal =  130.4071084059*ratioVal*ratioVal - 35.9209088589*ratioVal -15.2356549151;
      }
      else zVal = 0.154910799*exp(6.7447754752*ratioVal);

      if (zVal > 100) zVal = 100;
      
      zeff->SetBinContent(binNum, zVal);
    }

  }
  return zeff;  
}
*/
void Plot(TH2D* transmissionLow, TH2D* transmissionHigh,  TH2D* ratio, TString path)
{
  gStyle->SetPalette(53);
  gStyle->SetOptStat(0);

  TCanvas *c2 = new TCanvas("c2","tLow MeV",0,0,528,378);

  transmissionLow->GetZaxis()->SetTitle("");
  transmissionLow->GetZaxis()->SetRangeUser(0.0,1.);
  
  transmissionLow->GetXaxis()->SetNdivisions(numNewSlices);
  transmissionLow->GetYaxis()->SetNdivisions(numDets*2-1);
  transmissionLow->GetZaxis()->SetNdivisions(5);

  transmissionLow->GetYaxis()->SetLabelSize(0.0);
  transmissionLow->GetXaxis()->SetLabelSize(0.0);
  transmissionLow->GetZaxis()->SetLabelSize(0.07);
  transmissionLow->GetZaxis()->SetTitleOffset(1.0);

  transmissionLow->SetTitle("");
  transmissionLow->Draw("COLZ");
  transmissionLow->SetStats(kFALSE);
  transmissionLow->SetContour(99);

  c2->SetRightMargin(0.3);
  c2->cd();


  TCanvas *c3 = new TCanvas("c3","tHigh MeV",0,0,528,378);

  transmissionHigh->GetZaxis()->SetTitle("");
  transmissionHigh->GetZaxis()->SetRangeUser(0.0,1.);
  
  transmissionHigh->GetXaxis()->SetNdivisions(numNewSlices);
  transmissionHigh->GetYaxis()->SetNdivisions(numDets*2-1);
  transmissionHigh->GetZaxis()->SetNdivisions(5);

  transmissionHigh->GetYaxis()->SetLabelSize(0.0);
  transmissionHigh->GetXaxis()->SetLabelSize(0.0);
  transmissionHigh->GetZaxis()->SetLabelSize(0.07);
  transmissionHigh->GetZaxis()->SetTitleOffset(1.0);

  transmissionHigh->SetTitle("");
  transmissionHigh->Draw("COLZ");
  transmissionHigh->SetStats(kFALSE);
  transmissionHigh->SetContour(99);

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
  ratio->GetYaxis()->SetNdivisions(numDets*2);
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

  c2->SaveAs(path+"BremtransmissionLowRawDataToss"+TString::Itoa(demultiplier,10)+".eps");
  c3->SaveAs(path+"BremtransmissionHighRawDataToss"+TString::Itoa(demultiplier,10)+".eps");
  c4->SaveAs(path+"BremratioRawDataToss"+TString::Itoa(demultiplier,10)+".eps");
}

void TossData(TH1D* hist, TRandom3* rng, TH1D* effHist, Double_t lowerBound, Double_t upperBound, Double_t tossNo)
{
  Int_t nBins = hist->GetNbinsX();
  Double_t reduction = 1./tossNo;
  for (Int_t i = 0; i < nBins; i++){
    Double_t bincenter = hist->GetBinCenter(i+1);
    if (bincenter < lowerBound || bincenter > upperBound) {
      hist->SetBinContent(i+1,0);
      continue;
    }
    Int_t numInBin = hist->GetBinContent(i+1);
    Double_t efficiencyVal = effHist->GetBinContent(effHist->FindBin(hist->GetBinCenter(i+1)));
    Double_t threshold = efficiencyVal*reduction;
    hist->SetBinContent(i+1, 0);
    //cout << threshold << endl;
    for (Int_t j = 0; j < numInBin; j++){
      Double_t rndmNum = rng->Rndm();
      if (rndmNum < threshold) hist->AddBinContent(i+1);
    }
  }
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