#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TSystem.h>
#include <TRandom.h>
#include <TROOT.h>
#include <TObject.h>

#include <iostream>
#include <fstream>
#include <thread>

//#include <omp.h>

#define NUM_THREADS 64

void Convolution(int, int, TH1D*, TH1D*, TH2D*, int);

const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static TString source = "brem6";

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  //gROOT->SetBatch();
  //ROOT::EnableThreadSafety();
  //TH1::AddDirectory(kTRUE);

  TString baseFolder = "/nv/hp17/jharms7/data/ANSIsimulations/CNR_Zeff/results/";
  TString histFolder = baseFolder + "/" + source;

  TString crfFileName = "/nv/hp17/jharms7/data/CherenkovResponse/SmallDetector/results/NormalizedResults6mmCDF.root";
  TFile* crfFile = new TFile(crfFileName);
  TH2D* crf = (TH2D*)crfFile->Get("Normalized CRF");

  TH1D* dummyHist = crf->ProjectionX("dummyProjection",0,1);
  int spectrumLength = dummyHist->GetNbinsX();
  Double_t newHistEnd = dummyHist->GetBinCenter(spectrumLength-1) + dummyHist->GetBinWidth(spectrumLength-1);

    for (Int_t sliceNum = 0; sliceNum < numSlices; sliceNum++){
      TFile * outputHistFile = new TFile(histFolder + "convSlice" + TString::Itoa(sliceNum, 10) + "_" + source + ".root","RECREATE");
      for (Int_t i = 0; i < numDets*2; i++){
        TString fileName0, fileName1, fileName2, fileName3;
        if (i%2 == 0){
          fileName0 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run1_" + source + ".root";
          fileName1 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run3_" + source + ".root";
          fileName2 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run5_" + source + ".root";
          fileName3 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run7_" + source + ".root";
        } else{
          fileName0 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run0_" + source + ".root";
          fileName1 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run2_" + source + ".root"; 
          fileName2 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run4_" + source + ".root";
          fileName3 = histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run6_" + source + ".root";  
        }
        TFile * inputFile0 = new TFile(fileName0);
        TFile * inputFile1 = new TFile(fileName1);
        TFile * inputFile2 = new TFile(fileName2);
        TFile * inputFile3 = new TFile(fileName3);
        TH1D* g4Hist = (TH1D*)inputFile0->Get("Det" + TString::Itoa(i/2, 10));
        g4Hist->Add(g4Hist, (TH1D*)inputFile1->Get("Det" + TString::Itoa(i/2, 10)), 1, 1);
        g4Hist->Add(g4Hist, (TH1D*)inputFile2->Get("Det" + TString::Itoa(i/2, 10)), 1, 1);
        g4Hist->Add(g4Hist, (TH1D*)inputFile3->Get("Det" + TString::Itoa(i/2, 10)), 1, 1);
        TH1D** convolvedHist = new TH1D*[NUM_THREADS];
        thread threads[NUM_THREADS];
        for (Int_t k = 0; k < NUM_THREADS; k++){
          convolvedHist[k] = new TH1D("Det" + TString::Itoa(i, 10) + "_" + TString::Itoa(k,10), "", spectrumLength, 0, newHistEnd );
          threads[k] = thread(Convolution, k, NUM_THREADS, convolvedHist[k], g4Hist, crf, spectrumLength);
        }
        // Rejoin threads
        for (auto& th : threads){
          th.join();
        }
        // Add histograms
        for (Int_t k = 1; k < NUM_THREADS; k++){
          convolvedHist[0]->Add(convolvedHist[0], convolvedHist[k], 1, 1);
        }
        convolvedHist[0]->SetName("Det" + TString::Itoa(i, 10));
        outputHistFile->cd();
        convolvedHist[0]->Write();
        delete [] convolvedHist;
        inputFile0->Close();
        delete inputFile0;
        inputFile1->Close();
        delete inputFile1;
        inputFile2->Close();
        delete inputFile2;
        inputFile3->Close();
        delete inputFile3;
      }
    }

  return 0;
  
}

void Convolution(int id, int p, TH1D* newSpec, TH1D* rawSpec, TH2D* CRFhist2D, int spectrumLength)
{
  TRandom* rando = new TRandom();
  for (Int_t i = 0; i < spectrumLength; i++){
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
        Double_t newBinCenter = newSpec->GetBinCenter(k);
        /*if ( (newBinCenter > 1.0) && (newBinCenter < 15.2) )*/ newSpec->Fill(newBinCenter);
      }
    }
  }

}
