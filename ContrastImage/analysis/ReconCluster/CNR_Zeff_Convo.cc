#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TSystem.h>
#include <TRandom.h>

#include <iostream>
#include <fstream>
#include <thread>

#include <mpi.h>
#include <omp.h>

#define NUM_THREADS 8

void            Convolution(int, int, TH1D*, TH1D*, TH2D*, int);

const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static TString source = "lenr";

using namespace std;

int main(int argc, char * argv[]) 
{
  gSystem->Load("libTree");
  //TH1::AddDirectory(kTRUE);

  TString baseFolder = "/nv/hp17/jharms7/data/ANSIsimulations/CNR_Zeff/";
  TString histFolder = baseFolder + "results/" + source + "/";

  TString crfFileName = "/nv/hp17/jharms7/data/CherenkovResponse/SmallDetector/results/NormalizedResults6mmCDF.root";
  TFile* crfFile = new TFile(crfFileName);
  TH2D* crf = (TH2D*)crfFile->Get("Normalized CRF");

  TH1D* dummyHist = crf->ProjectionX("dummyProjection",0,1);

  // Initialize MPI
  int idMPI; int pMPI; int provided;
  MPI_Init_thread( &argc, &argv, MPI_THREAD_SERIALIZED, &provided);
  if (provided < MPI_THREAD_SERIALIZED){
    cout << "error " << endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  MPI_Comm_rank( MPI_COMM_WORLD, &idMPI);
  MPI_Comm_size( MPI_COMM_WORLD, &pMPI);

  Int_t lower = idMPI*numSlices/pMPI;
  Int_t upper = (idMPI+1)*numSlices/pMPI;
  if (upper > numSlices) upper = numSlices;
  for (Int_t sliceNum = lower; sliceNum < upper; sliceNum++){
    TFile * outputHistFile = new TFile(histFolder + "convSlice" + TString::Itoa(sliceNum, 10) + "_" + source + ".root","RECREATE");
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for   
    for (Int_t i = 0; i < numDets*2; i++){
      TFile* inputFile;
      if (i%2 == 0) inputFile = new TFile(histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run1_lenr.root");
      else inputFile = new TFile(histFolder + "Slice" + TString::Itoa(sliceNum, 10) + "_run0_lenr.root");
      TH1D* convolvedHist = (TH1D*)dummyHist->Clone("Det" + TString::Itoa(i, 10) );
      Convolution(convolvedHist, (TH1D*)inputFile->Get("Det" + TString::Itoa(i/2, 10)), crf, spectrumLength);
      outputHistFile->cd();
      convolvedHist->Write();
      delete [] convolvedHist;
      delete inputFile;
    }
  }

  MPI_Finalize();

  return 0;
  
}

void Convolution(TH1D* newSpec, TH1D* rawSpec, TH2D* CRFhist2D, int spectrumLength)
{
  TRandom* rando = new TRandom();
  Int_t nBinsOld = rawSpec->GetNbinsX();
  for (Int_t i = 0; i < nBinsOld; i++){
    Double_t currEnergy = rawSpec->GetBinCenter(i+1);
    Int_t energyBinNo = CRFhist2D->GetYaxis()->FindBin(currEnergy);
    Double_t maxCdfVal = CRFhist2D->GetBinContent(CRFhist2D->GetBin(spectrumLength - 1, energyBinNo));
    Int_t numInBin0 = rawSpec->GetBinContent(i+1);
    for (Int_t j = 0; j < numInBin0; j++){
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
