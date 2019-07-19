#include "TH1.h"
#include "TFile.h" 
#include "TString.h"

#include <iostream>

using namespace std;

int main()
{
	TString basepath = "~/G4/beamDose/SteelPlateDose/";

	TString histPath = basepath + "results/";

	TFile* outFile = new TFile(basepath + "results/ResultsAllHists.root","RECREATE");

	TString sources[6];
	sources[0] = "brem6_W";
	sources[1] = "brem9_W";
	sources[2] = "lenr";
	sources[3] = "mps3_10";
	sources[4] = "mps6_10";
	sources[5] = "mps9_10";

	for (Int_t i = 0; i < 5; i++){
		TFile * file1 = new TFile(histPath + "PlateDose" + sources[i] +"_run1.root");
		TH1D * baseHist = (TH1D*)file1->Get("Edep");
		baseHist->SetName(sources[i] + "PlateDose");
		for (Int_t runNo = 2; runNo <= 10; runNo ++){
			TFile * file2 = new TFile(histPath + "PlateDose" + sources[i] +"_run" + TString::Itoa(runNo, 10) + ".root");
			baseHist->Add(baseHist,(TH1D*)file2->Get("Edep"),1,1);
		}
		outFile->cd();
		baseHist->Write();

		Double_t sumEdep = 0;
		Int_t nBins = baseHist->GetNbinsX();
		Double_t binWidth = baseHist->GetBinWidth(1);
		for (Int_t binNo = 0; binNo < nBins; binNo ++){
			sumEdep += baseHist->GetBinContent(binNo + 1) * baseHist->GetBinCenter(binNo + 1)/binWidth;
		}
		cout << sources[i] << " edep " << sumEdep << endl;
	}
	outFile->Close();
	delete outFile;




	return 0;
}