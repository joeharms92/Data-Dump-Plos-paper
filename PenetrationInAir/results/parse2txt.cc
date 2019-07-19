#include "TH1.h"
#include "TFile.h" 
#include "TString.h"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	TString basepath = "~/G4/beamDose/PenetrationInAir/results/";

	TFile* inFile = new TFile(basepath + "/ResultsAllHists.root");
	ofstream outfile;
	TH1D* lenr = (TH1D*)inFile->Get("lenrSpec");
	outfile.open("lenrPostSteelSpec2.txt");
	Int_t nBins = lenr->GetNbinsX();
	Double_t normFactor = lenr->GetBinContent(lenr->GetMaximumBin());
	//Double_t normFactor = lenr->GetSumOfWeights();
	for (Int_t i = 0; i < nBins; i++){
		Double_t binCount = lenr->GetBinContent(i+1);
		if (binCount > 0){
			outfile << lenr->GetBinCenter(i+1) << " " << binCount/normFactor << endl;
		}
	}
	outfile.close();
	TH1D* brem6 = (TH1D*)inFile->Get("brem6_wSpec");
	brem6->Rebin(100);
	outfile.open("brem6PostSteelSpec2.txt");
	nBins = brem6->GetNbinsX();
	normFactor = brem6->GetBinContent(brem6->GetMaximumBin());
	//normFactor = brem6->GetSumOfWeights();
	for (Int_t i = 0; i < nBins; i++){
		Double_t binCount = brem6->GetBinContent(i+1);
		if (binCount > 0){
			outfile << brem6->GetBinCenter(i+1) << " " << binCount/normFactor << endl;
		}
	}
	outfile.close();
	TH1D* brem9 = (TH1D*)inFile->Get("brem9_wSpec");
	brem9->Rebin(100);
	outfile.open("brem9PostSteelSpec2.txt");
	nBins = brem9->GetNbinsX();
	normFactor = brem9->GetBinContent(brem9->GetMaximumBin());
	//normFactor = brem9->GetSumOfWeights();
	for (Int_t i = 0; i < nBins; i++){
		Double_t binCount = brem9->GetBinContent(i+1);
		if (binCount > 0){
			outfile << brem9->GetBinCenter(i+1) << " " << binCount/normFactor << endl;
		}
	}
	outfile.close();
	TH1D* mps3_10 = (TH1D*)inFile->Get("mps3_10Spec");
	mps3_10->Rebin(5);
	outfile.open("mps3_10PostSteelSpec2.txt");
	nBins = mps3_10->GetNbinsX();
	normFactor = mps3_10->GetBinContent(mps3_10->GetMaximumBin());
	//normFactor = mps3_10->GetSumOfWeights();
	for (Int_t i = 0; i < nBins; i++){
		Double_t binCount = mps3_10->GetBinContent(i+1);
		if (binCount > 0){
			outfile << mps3_10->GetBinCenter(i+1) << " " << binCount/normFactor << endl;
		}
	}
	outfile.close();
	TH1D* mps6_10 = (TH1D*)inFile->Get("mps6_10Spec");
	mps6_10->Rebin(5);
	outfile.open("mps6_10PostSteelSpec2.txt");
	nBins = mps6_10->GetNbinsX();
	normFactor = mps6_10->GetBinContent(mps6_10->GetMaximumBin());
	//normFactor = mps6_10->GetSumOfWeights();
	for (Int_t i = 0; i < nBins; i++){
		Double_t binCount = mps6_10->GetBinContent(i+1);
		if (binCount > 0){
			outfile << mps6_10->GetBinCenter(i+1) << " " << binCount/normFactor << endl;
		}
	}
	outfile.close();
	TH1D* mps9_10 = (TH1D*)inFile->Get("mps9_10Spec");
	mps9_10->Rebin(5);
	outfile.open("mps9_10PostSteelSpec2.txt");
	nBins = mps9_10->GetNbinsX();
	normFactor = mps9_10->GetBinContent(mps9_10->GetMaximumBin());
	//normFactor = mps9_10->GetSumOfWeights();
	for (Int_t i = 0; i < nBins; i++){
		Double_t binCount = mps9_10->GetBinContent(i+1);
		if (binCount > 0){
			outfile << mps9_10->GetBinCenter(i+1) << " " << binCount/normFactor << endl;
		}
	}
	outfile.close();

	delete mps9_10;
	delete mps6_10;
	delete mps3_10;
	delete brem9;
	delete brem6;
	delete lenr;
	inFile->Close();
	delete inFile;

	return 0;
}