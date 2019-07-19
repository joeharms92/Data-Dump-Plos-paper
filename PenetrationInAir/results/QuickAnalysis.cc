#include "TH1.h"
#include "TFile.h" 
#include "TString.h"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	TString basepath = "~/G4/beamDose/PenetrationInAir/results/";


	TFile* outFile = new TFile(basepath + "/ResultsAllHists.root","RECREATE");

	TString histNames = "Spectrum";

	TString sources[6];
	sources[0] = "brem6_w";
	sources[1] = "brem9_w";
	sources[2] = "lenr";
	sources[3] = "mps3_10";
	sources[4] = "mps6_10";
	sources[5] = "mps9_10";

	Int_t steelZ[2];
	steelZ[0] = 20;
	steelZ[1] = 40;

	Int_t nRuns = 10;
	for (Int_t sourceIter = 0; sourceIter < 6; sourceIter++){
		for (Int_t steelID = 0; steelID < 2; steelID++){
			TFile * inFile = new TFile(basepath + "Dose" + sources[sourceIter] + "_steelZ" + TString::Itoa(steelZ[steelID],10) + "_run1.root");
			TH1D * inputHist = (TH1D*)inFile->Get(histNames);
			inputHist->SetName(sources[sourceIter] + "SpecSteelZ" + TString::Itoa(steelZ[steelID],10));
			for (Int_t runNo = 2; runNo <= nRuns; runNo ++){
				//if (sourceIter > 3 && runNo == 2) continue;
				TFile * inFile2 = new TFile(basepath + "Dose" + sources[sourceIter] 
											+ "_steelZ" + TString::Itoa(steelZ[steelID],10) + "_run" + TString::Itoa(runNo, 10) + ".root");
				inputHist->Add(inputHist,(TH1D*)inFile2->Get(histNames),1,1);
			}
			outFile->cd();
			inputHist->Write();
			Double_t edep = 0;
			Int_t nBins = inputHist->GetNbinsX();
			for (Int_t binNo = 0; binNo < nBins; binNo ++){
				edep += inputHist->GetBinContent(binNo + 1) * inputHist->GetBinCenter(binNo + 1);
			}
			cout << sources[sourceIter] << " " << steelZ[steelID] << endl;
			cout << " counts " << inputHist->GetEntries() << " edep " << edep <<  endl;
			cout << "avg energy " << edep/inputHist->GetEntries() << endl << endl;
			if (sourceIter == 0){
				edep = 0;
				cout << sources[sourceIter] << " " << steelZ[steelID] << " low " << endl;
				Int_t lowerBoundBin = inputHist->FindBin(1.0);
				Int_t upperBoundBin = inputHist->FindBin(5.0);
				Double_t counts = inputHist->Integral(lowerBoundBin,upperBoundBin);
				for (Int_t binNo = lowerBoundBin; binNo < upperBoundBin; binNo++){
					edep += inputHist->GetBinContent(binNo + 1) * inputHist->GetBinCenter(binNo + 1);
				}
				cout << " counts " << counts << " edep " << edep <<  endl;
				cout << "avg energy " << edep/counts << endl << endl;
			}
			else if (sourceIter == 1){
				edep = 0;
				cout << sources[sourceIter] << " " << steelZ[steelID] << " low " << endl;
				Int_t lowerBoundBin = inputHist->FindBin(5.0);
				Int_t upperBoundBin = inputHist->FindBin(9.0);
				Double_t counts = inputHist->Integral(lowerBoundBin,upperBoundBin);
				for (Int_t binNo = lowerBoundBin; binNo < upperBoundBin; binNo++){
					edep += inputHist->GetBinContent(binNo + 1) * inputHist->GetBinCenter(binNo + 1);
				}
				cout << " counts " << counts << " edep " << edep <<  endl;
				cout << "avg energy " << edep/counts << endl << endl;
			}
			else if (sourceIter == 2){
				cout << sources[sourceIter] << " " << steelZ[steelID] << " low " << endl;
				Double_t counts = inputHist->Integral(4438,4440);
				Double_t binCenter = inputHist->GetBinCenter(4439);
				cout << " counts " << counts << " edep " << counts*binCenter <<  endl;
				cout << sources[sourceIter] << " " << steelZ[steelID] << " high " << endl;
				counts = inputHist->Integral(15100,15102);
				binCenter = inputHist->GetBinCenter(15101);
				cout << " counts " << counts << " edep " << counts*binCenter <<  endl << endl;
			}
		}
	}

	outFile->Close();
	delete outFile;




	return 0;
}