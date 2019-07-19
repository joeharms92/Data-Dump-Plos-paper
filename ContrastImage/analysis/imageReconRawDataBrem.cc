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
void            Plot(/*TH2D*,*/ TH2D*, TH2D*, TH2D*, TH2D*, TString);

const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static Int_t numNewSlices = numSlices - 4; // flatfield is first and last slices
const static Int_t multiplier = 50;

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  //TH1::AddDirectory(kTRUE);

  TString baseFolder = "/home/jharms/G4/ANSIsimulations/CNR_Zeff/results/";

  TString outputFileName = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/imgs_bremRawData.root";

    TH2D* trans4 = Transmission("low", baseFolder);
    TH2D* trans15 = Transmission("high", baseFolder);
    //TH2D* transTotal = Transmission("total", baseFolder);

    TH2D* ratio = CalculateRatio(trans4, trans15);
    TH2D* zeff = CalculateZeff(ratio);

    TFile* outputFile = new TFile(outputFileName, "RECREATE");
    trans4->Write();
    trans15->Write();
    //transTotal->Write();
    ratio->Write();
    zeff->Write();
    outputFile->Close();

    Plot(/*transTotal,*/ trans4, trans15, ratio, zeff, "/home/jharms/G4/ANSIsimulations/CNR_Zeff/ReconImages/");

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

  TFile * ff1File_run0;
  TFile * ff1File_run1;
  TFile * ff2File_run0;
  TFile * ff2File_run1;
  TFile * ff3File_run0;
  TFile * ff3File_run1;
  TFile * ff4File_run0;
  TFile * ff4File_run1;

  if (whichEnergy == "low"){
      lowerBound = 1.0;      
      upperBound = 5.0;
      ff1File_run0 = new TFile(path + "brem6/Slice0_run0_brem6.root");
      ff1File_run1 = new TFile(path + "brem6/Slice0_run1_brem6.root");
      ff2File_run0 = new TFile(path + "brem6/Slice1_run0_brem6.root");
      ff2File_run1 = new TFile(path + "brem6/Slice1_run1_brem6.root");
      ff3File_run0 = new TFile(path + "brem6/Slice218_run0_brem6.root");
      ff3File_run1 = new TFile(path + "brem6/Slice218_run1_brem6.root");
      ff4File_run0 = new TFile(path + "brem6/Slice219_run0_brem6.root");
      ff4File_run1 = new TFile(path + "brem6/Slice219_run1_brem6.root");
  }
  else {
      lowerBound = 5.0;    
      upperBound = 9.0;
      ff1File_run0 = new TFile(path + "brem9/Slice0_run0_brem9.root");
      ff1File_run1 = new TFile(path + "brem9/Slice0_run1_brem9.root");
      ff2File_run0 = new TFile(path + "brem9/Slice1_run0_brem9.root");
      ff2File_run1 = new TFile(path + "brem9/Slice1_run1_brem9.root");
      ff3File_run0 = new TFile(path + "brem9/Slice218_run0_brem9.root");
      ff3File_run1 = new TFile(path + "brem9/Slice218_run1_brem9.root");
      ff4File_run0 = new TFile(path + "brem9/Slice219_run0_brem9.root");
      ff4File_run1 = new TFile(path + "brem9/Slice219_run1_brem9.root");
  }

  Double_t countsAir[numDets*2];


  for (Int_t detIter = 0; detIter < numDets; detIter++){
    countsAir[2*detIter] = 0;
    countsAir[2*detIter+1] = 0;
    TH1D* ff1_run0 = (TH1D*)ff1File_run0->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff1_run1 = (TH1D*)ff1File_run1->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff2_run0 = (TH1D*)ff2File_run0->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff2_run1 = (TH1D*)ff2File_run1->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff3_run0 = (TH1D*)ff3File_run0->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff3_run1 = (TH1D*)ff3File_run1->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff4_run0 = (TH1D*)ff4File_run0->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff4_run1 = (TH1D*)ff4File_run1->Get("Det"+TString::Itoa(detIter, 10) );
    Double_t ff1Counts_run0 = ff1_run0->Integral( ff1_run0->FindBin(lowerBound), ff1_run0->FindBin(upperBound) ); 
    Double_t ff1Counts_run1 = ff1_run1->Integral( ff1_run1->FindBin(lowerBound), ff1_run1->FindBin(upperBound) ); 
    Double_t ff2Counts_run0 = ff2_run0->Integral( ff2_run0->FindBin(lowerBound), ff2_run0->FindBin(upperBound) ); 
    Double_t ff2Counts_run1 = ff2_run1->Integral( ff2_run1->FindBin(lowerBound), ff2_run1->FindBin(upperBound) ); 
    Double_t ff3Counts_run0 = ff3_run0->Integral( ff3_run0->FindBin(lowerBound), ff3_run0->FindBin(upperBound) ); 
    Double_t ff3Counts_run1 = ff3_run1->Integral( ff3_run1->FindBin(lowerBound), ff3_run1->FindBin(upperBound) ); 
    Double_t ff4Counts_run0 = ff4_run0->Integral( ff4_run0->FindBin(lowerBound), ff4_run0->FindBin(upperBound) ); 
    Double_t ff4Counts_run1 = ff4_run1->Integral( ff4_run1->FindBin(lowerBound), ff4_run1->FindBin(upperBound) ); 
    countsAir[2*detIter+1] = (ff1Counts_run0 + ff2Counts_run0 + ff3Counts_run0 + ff4Counts_run0) / 4.;
    countsAir[2*detIter] = (ff1Counts_run1 + ff2Counts_run1 + ff3Counts_run1 + ff4Counts_run1) / 4.;
  }
  ff1File_run0->Close();
  ff2File_run0->Close();
  ff3File_run0->Close();
  ff4File_run0->Close();
  delete ff1File_run0;
  delete ff2File_run0;
  delete ff3File_run0;
  delete ff4File_run0;
  ff1File_run1->Close();
  ff2File_run1->Close();
  ff3File_run1->Close();
  ff4File_run1->Close();
  delete ff1File_run1;
  delete ff2File_run1;
  delete ff3File_run1;
  delete ff4File_run1;

  for (Int_t sliceIter = 2; sliceIter < numSlices - 2; sliceIter++){
    TFile* histFile_run0;
    TFile* histFile_run1;
    if (whichEnergy == "low"){
      histFile_run0 = new TFile(path + "brem6/Slice"+TString::Itoa(sliceIter,10) + "_run0_brem6.root");
      histFile_run1 = new TFile(path + "brem6/Slice"+TString::Itoa(sliceIter,10) + "_run1_brem6.root");
    } else{
      histFile_run0 = new TFile(path + "brem9/Slice"+TString::Itoa(sliceIter,10) + "_run0_brem9.root");
      histFile_run1 = new TFile(path + "brem9/Slice"+TString::Itoa(sliceIter,10) + "_run1_brem9.root");
    }
    for (Int_t detIter = 0; detIter < numDets; detIter++){
      TH1D * hist_run0 = (TH1D*)histFile_run0->Get("Det" + TString::Itoa(detIter, 10));
      TH1D * hist_run1 = (TH1D*)histFile_run1->Get("Det" + TString::Itoa(detIter, 10));
      Double_t pixelVal_run0 = hist_run0->Integral( hist_run0->FindBin(lowerBound), hist_run0->FindBin(upperBound) ) / countsAir[2*detIter];
      Double_t pixelVal_run1 = hist_run1->Integral( hist_run1->FindBin(lowerBound), hist_run1->FindBin(upperBound) ) / countsAir[2*detIter+1];
      Int_t binNum_run0 = img->GetBin(sliceIter , 2*detIter+2);
      img->SetBinContent(binNum_run0, pixelVal_run0);
      Int_t  binNum_run1 = img->GetBin(sliceIter, 2*detIter + 1);
      img->SetBinContent(binNum_run1, pixelVal_run1);
    }
    histFile_run0->Close();
    delete histFile_run0;
    histFile_run1->Close();
    delete histFile_run1;
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

void Plot(/*TH2D* transmissionTotal,*/ TH2D* transmission4, TH2D* transmission15,  TH2D* ratio, TH2D* zeff, TString path)
{
  gStyle->SetPalette(53);
  gStyle->SetOptStat(0);

 /* TCanvas *c1 = new TCanvas("c1","Total Transmission",0,0,528,378);

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
  c1->cd();*/

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

  //c1->SaveAs(path+"BremtransmissionTotalRawData.eps");
  c2->SaveAs(path+"Bremtransmission4RawData.eps");
  c3->SaveAs(path+"Bremtransmission15RawData.eps");
  c4->SaveAs(path+"BremratioRawData.eps");
  c5->SaveAs(path+"BremzeffRawData.eps");
}
