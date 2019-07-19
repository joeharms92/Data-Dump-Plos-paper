#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>
#include <TRandom.h>
#include <TROOT.h>

#include <iostream>
#include <fstream>
#include <thread>

#include <sys/time.h>
#include <ctime>

#include <mpi.h>

// MUST BE TYPE int (NOT Int_t) for OpenMP
//#define NUM_THREADS 4

void            Convolution(int, int, TH1D*, TH1D*, TH2D*, int);
TH2D*        Transmission(TString, TString);
TH2D*        CalculateRatio(TH2D*, TH2D*);
TH2D*        CalculateZeff(TH2D*);
void            Plot(TH2D*, TH2D*, TH2D*, TH2D*, TH2D*, TString);
Double_t*   CreateEnergyAxis(TH1D*);

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

const static Int_t numSlices = 12;
const static Int_t numDets = 10;
const static Int_t numNewSlices = numSlices - 4; // flatfield is first and last slices
const static TString source = "lenr";

const static int nThrds = 2;

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  gROOT->SetBatch();
  ROOT::EnableThreadSafety();
  //TH1::AddDirectory(kTRUE);

  TString baseFolder = "/nv/hp17/jharms7/data/ANSIsimulations/CNR_Zeff/";

  TString outputFileName = baseFolder + "results/" + source + "/cnrImgs" + source + TString::Itoa(nThrds, 10) + ".root";

  TString crfFileName = "/nv/hp17/jharms7/data/CherenkovResponse/SmallDetector/results/NormalizedResults6mmCDF.root";
  TFile* crfFile = new TFile(crfFileName);
  TH2D* crf = (TH2D*)crfFile->Get("Normalized CRF");

  TH1D* dummyHist = crf->ProjectionX("dummyProjection",0,1);
  int spectrumLength = dummyHist->GetNbinsX();
  Double_t* newEnergyAxis = CreateEnergyAxis(dummyHist);

  // Initialize MPI
  int idMPI; int pMPI;
  MPI_Init( &argc, &argv);
  MPI_Comm_rank( MPI_COMM_WORLD, &idMPI);
  MPI_Comm_size( MPI_COMM_WORLD, &pMPI);
  timestamp_t t1 = get_timestamp();

  Int_t lower = idMPI*numSlices/pMPI;
  Int_t upper = (idMPI+1)*numSlices/pMPI;
  if (upper > numSlices) upper = numSlices;
  for (Int_t sliceNum = lower; sliceNum < upper; sliceNum++){
    cout << "Slice " << sliceNum << endl;
    TFile * outputHistFile = new TFile(baseFolder + "results/results" + source + "/convolvedSlice" + TString::Itoa(sliceNum, 10) + "_" + source + ".root","RECREATE");
    for (Int_t i = 0; i < numDets*2; i++){
      //cout << "Det " << i << endl;
      TFile* inputFile;
      if (i%2 == 0) inputFile = new TFile(baseFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run1_lenr.root");
      else inputFile = new TFile(baseFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run0_lenr.root");
      thread workers[nThrds];
      TH1D** convolvedHist = new TH1D*[nThrds];
      for (Int_t j = 0; j < nThrds; j++){
        convolvedHist[j] = new TH1D(TString::Itoa(i,10) + TString::Itoa(j,10), "", spectrumLength-1, newEnergyAxis);
        //cout << 
        workers[j] = thread(Convolution, j, nThrds, convolvedHist[j], (TH1D*)inputFile->Get("Det" + TString::Itoa(i/2, 10)), crf, spectrumLength);
        //cout << "past convo " << endl;
      }
      for (auto &th : workers){
        th.join();
      }
      // Add histograms
      for (Int_t j = 1; j < nThrds; j++){
        convolvedHist[0]->Add(convolvedHist[0], convolvedHist[j], 1, 1);
      }
      convolvedHist[0]->SetName("Det" + TString::Itoa(i,10));
      outputHistFile->cd();
      convolvedHist[0]->Write();
      cout << "writing" << endl;
      delete [] convolvedHist;
      delete inputFile;
    }
  }

  //MPI_Wait(&request, &status);

  MPI_Finalize();

  /*if (idMPI == 0){
    timestamp_t t2 = get_timestamp();
    cout << "Convolution time: " << ( t2 - t1 ) / 1000000.0L << " s " << endl;
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

    Plot(transTotal, trans4, trans15, ratio, zeff, "/home/jharms/G4/ANSIsimulations/CNR_Zeff/analysis/DebugImages/");
  };*/

  return 0;
  
}

void Convolution(int id, int p, TH1D* newSpec, TH1D* rawSpec, TH2D* CRFhist2D, int spectrumLength)
{
  //cout << "convolving in thread " << id << endl;
  TRandom* rando = new TRandom();
  //cout << "random" << endl;
  Int_t nBinsOld = rawSpec->GetNbinsX();
  //cout << "accessed spec " << endl;
  for (Int_t i = 0; i < nBinsOld; i++){
    Double_t currEnergy = rawSpec->GetBinCenter(i+1);
    Int_t energyBinNo = CRFhist2D->GetYaxis()->FindBin(currEnergy);
    Double_t maxCdfVal = CRFhist2D->GetBinContent(CRFhist2D->GetBin(spectrumLength - 1, energyBinNo));
    Int_t numInBin0 = rawSpec->GetBinContent(i+1);
    Int_t lowerBound = id*numInBin0/p;
    Int_t upperBound = (id+1)*numInBin0/p;
    if (upperBound > numInBin0) upperBound = numInBin0;
    for (Int_t j = lowerBound; j < upperBound; j++){
      Double_t randNum = rando->Rndm();
      if (randNum < maxCdfVal ){
        Int_t k = 0;
        while (CRFhist2D->GetBinContent(CRFhist2D->GetBin(k+1, energyBinNo)) < randNum ) {
          k++;
        }
        newSpec->Fill(newSpec->GetBinCenter(k));
      }
    }
  }

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
      lowerBound = 1.5;      
      upperBound = 2.5;
  }
  else if (whichEnergy == "high"){
      lowerBound = 9.5;    
      upperBound = 11.0;
  }
  else {
    lowerBound = 0.0;
    upperBound = 15.1;
  }

  Double_t countsAir[numDets*2];

  TFile * ff1File = new TFile(path + "convolvedSlice0" + "_" + source + ".root");
  TFile * ff2File = new TFile(path + "convolvedSlice1" + "_" + source + ".root");
  TFile * ff3File = new TFile(path + "convolvedSlice218" + "_" + source + ".root");
  TFile * ff4File = new TFile(path + "convolvedSlice219" + "_" + source + ".root");

  for (Int_t detIter = 0; detIter < numDets*2; detIter++){
    countsAir[detIter] = 0;
    TH1D* ff1 = (TH1D*)ff1File->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff2 = (TH1D*)ff2File->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff3 = (TH1D*)ff3File->Get("Det"+TString::Itoa(detIter, 10) );
    TH1D* ff4 = (TH1D*)ff4File->Get("Det"+TString::Itoa(detIter, 10) );
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
    TFile * histFile = new TFile(path + "convolvedSlice"+TString::Itoa(sliceIter,10) + "_" + source + ".root");
    for (Int_t detIter = 0; detIter < numDets*2; detIter++){
      TH1D * hist = (TH1D*)histFile->Get("Det" + TString::Itoa(detIter, 10));
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
                                          numDets*2, 0 , numDets*2);

  Double_t val4, val15, ratioVal;

  for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
    for (Int_t detIter = 0; detIter < numDets*2; detIter++){

      Int_t binNum = ratio->GetBin(sliceIter,detIter+1);
      val4 = t4->GetBinContent(binNum) ;
      val15 = t15->GetBinContent(binNum);
      if (val4 >=1 || val15 >=1 ){
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
                                          numDets*2, 0 , numDets*2);

  Double_t zVal;
  for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
    for (Int_t detIter = 0; detIter < numDets*2; detIter++){
      Int_t binNum = ratio->GetBin(sliceIter,detIter+1);
      Double_t ratioVal = ratio->GetBinContent(binNum);

      zVal = 34.8968699522 * pow(ratioVal, 3.3664812921);

      if ( zVal < 0.01) zVal = 0.01;
      else if (zVal > 92) zVal = 92;
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

  transmissionTotal->GetYaxis()->SetNdivisions(numDets*2);
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
  transmission4->GetYaxis()->SetNdivisions(numDets);
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
  transmission15->GetYaxis()->SetNdivisions(numDets);
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
  ratio->GetYaxis()->SetNdivisions(numDets);
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
  zeff->GetYaxis()->SetNdivisions(numDets);
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
  
  c5->cd();
  c5->SetRightMargin(0.3);

  c1->SaveAs(path+ "transmissionTotal" + source + ".eps");
  c2->SaveAs(path+"transmission4" + source + ".eps");
  c3->SaveAs(path+"transmission15" + source + ".eps");
  c4->SaveAs(path+"ratio" + source + ".eps");
  c5->SaveAs(path+"zeff" + source + ".eps");
}

Double_t * CreateEnergyAxis(TH1D* dummyHist)
{
  Int_t spectrumLength = dummyHist->GetNbinsX();
  Double_t* calibratedEAxis = new Double_t[spectrumLength]; 
  for (Int_t i = 0; i < spectrumLength; i++){
    Double_t xVal = dummyHist->GetBinCenter(i+1);
    calibratedEAxis[i] = 3.595E-5 * xVal * xVal + 3.198822E-2 * xVal + 0.39110786
                - 0.0159317504;
  }
  return calibratedEAxis;  
}