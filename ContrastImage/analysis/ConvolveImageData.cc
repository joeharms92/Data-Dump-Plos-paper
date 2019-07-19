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
#include <TROOT.h>

#include <iostream>
#include <fstream>
//#include <omp.h>

//#define NUM_THREADS 4

void Convolution(TH1D*, TH1D*, TH2D*);

const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static TString source = "lenr";

using namespace std;

int main(int argc, char * argv[]) 
{
	gSystem->Load("libTree");
	//gROOT->SetBatch();
	//ROOT::EnableThreadSafety();

	TString crfFileName = "/home/jharms/G4/CherenkovResponse/Results/CDFOnlyForPlotting.root";
	TFile* crfFile = new TFile(crfFileName);
	TH2D* crf = (TH2D*)crfFile->Get("Normalized CRF");
	TH1D* dummyHist = crf->ProjectionX("dummyProjection",0,1);
	Int_t nBins = dummyHist->GetNbinsX();
	Double_t maxEdgeOp = dummyHist->GetBinCenter(nBins) + dummyHist->GetBinWidth(nBins)/2.;

	Int_t counter = 0;
	Int_t startX = 0;
	Int_t endX = 0;
	for (Int_t i = 0; i < nBins; i++){
		Double_t x = dummyHist->GetBinCenter(i+1);
		if (x > 70 && x < 1775) {
			if (counter == 0) startX = i;
			endX = i;
			counter++;
		}
	}
	Double_t* newXaxis = new Double_t[counter];
	for (Int_t i = startX; i < endX; i++){
		Double_t x = dummyHist->GetBinCenter(i+1);
		newXaxis[i-startX] = 0.9079 - 0.0003158*x + 1.124E-5*x*x - 9.318E-9*x*x*x + 3.195E-12*x*x*x*x;
	}


	TString path = "~/G4/ANSIsimulations/CNR_Zeff/results/" + source + "/";

	for (Int_t sliceIter = 0; sliceIter < numSlices; sliceIter++){
		cout << sliceIter << endl;
		TFile * outConvHistFile = new TFile(path + "ConvSlice"+TString::Itoa(sliceIter,10) + "_toss1_2.root","RECREATE");
		TFile * outConvCalHistFile = new TFile(path + "ConvCalSlice"+TString::Itoa(sliceIter,10) + "_toss1_2.root","RECREATE");
		TFile * histFile = new TFile(path + "Slice"+TString::Itoa(sliceIter,10) + "_toss1.root");
		for (Int_t detIter = 0; detIter < numDets*2; detIter++){
			TH1D * dataHist = (TH1D*)histFile->Get("Det" + TString::Itoa(detIter, 10));
			TH1D* convolvedHist = new TH1D("ConvDet" + TString::Itoa(detIter, 10), "", nBins, 0, maxEdgeOp);
			Convolution(convolvedHist, dataHist, crf);
			outConvHistFile->cd();
			convolvedHist->Write();

			TH1D* calHist = new TH1D("ConvCalDet" + TString::Itoa(detIter, 10), "",counter-2,newXaxis);
			for (Int_t i = startX; i < endX; i++){
				calHist->SetBinContent(i-startX+1, convolvedHist->GetBinContent(i+1));
			}
			outConvCalHistFile->cd();
			calHist->Write();
			delete calHist;
			delete convolvedHist;
		}
		outConvCalHistFile->Close();
		delete outConvCalHistFile;
		outConvHistFile->Close();
		delete outConvHistFile;	
	}
	return 0;

}

void Convolution(TH1D* newSpec, TH1D* rawSpec, TH2D* CRFhist2D)
{
  TRandom3* rando = new TRandom3();
	Int_t maxBinOpPhotonOutput = CRFhist2D->GetNbinsX();
	Int_t nBins = rawSpec->GetNbinsX();
	for (Int_t i = 0; i < nBins; i++){
		Double_t currEnergy = rawSpec->GetBinCenter(i+1);
		Int_t energyBinNo = CRFhist2D->GetYaxis()->FindBin(currEnergy);
		Double_t maxCdfVal = CRFhist2D->GetBinContent(
					CRFhist2D->GetBin(maxBinOpPhotonOutput - 1, energyBinNo));
		Int_t rawNumber = rawSpec->GetBinContent(i+1);
		Int_t numInBin = rando->Gaus(rawNumber*10, 10*sqrt(rawNumber));
		for (Int_t j = 0; j < numInBin; j++){
			Double_t randNum = rando->Rndm()*maxCdfVal;
			Int_t k = 0;
			while (CRFhist2D->GetBinContent(CRFhist2D->GetBin(k+1, energyBinNo)) < randNum ) {
				k++;
			}
			newSpec->Fill(newSpec->GetBinCenter(k));
		}
	}
}