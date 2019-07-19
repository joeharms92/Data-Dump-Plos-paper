#include <TH2.h>
#include <TFile.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main ()
{
	TString basePath = "~/G4/ANSIsimulations/CNR_Zeff/";
	TString source = "brem";
	ifstream infile;
	Int_t rowCount = 0;
	Int_t colCount = 140;
	TFile * outFile = new TFile(basePath + "ReconImages/" + source + "RatiosNS.root","RECREATE");
	for (Int_t toss = 1; toss <= 10; toss++){
		colCount = 140;
		TH2D* histOrig = new TH2D(source+"RatioOrigtoss" + TString::Itoa(toss,10), "", 206, 0, 206, 140, 0, 140);
		infile.open("MatrixTxtFiles/ratioOrig"+source+"_toss"+to_string(toss)+".txt");
		while (infile.good()){
			string str;
			while (getline(infile, str)){
				colCount--;
				istringstream ss(str);
				double num;
				while (ss >> num){
					histOrig->SetBinContent(histOrig->GetBin(rowCount + 1, colCount + 1), num);
					rowCount++;
				}
				rowCount = 0;
			}
		}
		infile.close();
		colCount = 140;
		TH2D* histNS = new TH2D(source+"RatioNStoss" + TString::Itoa(toss,10), "", 206, 0, 206, 140, 0, 140);
		infile.open("MatrixTxtFiles/ratioNS"+source+"_toss"+to_string(toss)+".txt");
		while (infile.good()){
			string str;
			while (getline(infile, str)){
				colCount--;
				istringstream ss(str);
				double num;
				while (ss >> num){
					histNS->SetBinContent(histNS->GetBin(rowCount + 1, colCount + 1), num);
					rowCount++;
				}
				rowCount = 0;
			}
		}
		infile.close();
		colCount = 140;
		infile.open("MatrixTxtFiles/ratioOrigError"+source+"_toss"+to_string(toss)+".txt");
		while (infile.good()){
			string str;
			while (getline(infile, str)){
				colCount--;
				istringstream ss(str);
				double num;
				while (ss >> num){
					histOrig->SetBinError(histOrig->GetBin(rowCount + 1, colCount + 1), num);
					rowCount++;
				}
				rowCount = 0;
			}
		}
		infile.close();
		colCount = 140;
		infile.open("MatrixTxtFiles/ratioNSError"+source+"_toss"+to_string(toss)+".txt");
		while (infile.good()){
			string str;
			while (getline(infile, str)){
				colCount--;
				istringstream ss(str);
				double num;
				while (ss >> num){
					histNS->SetBinError(histNS->GetBin(rowCount + 1, colCount + 1), num);
					rowCount++;
				}
				rowCount = 0;
			}
		}
		infile.close();

		outFile->cd();
		histOrig->Write();
		histNS->Write();
		delete histOrig;
		delete histNS;
	}
	outFile->Close();
	delete outFile;
	
	return 0;
}