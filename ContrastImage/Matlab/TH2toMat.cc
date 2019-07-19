#include <TH2.h>
#include <TFile.h>
#include <TString.h>

#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
	TString basePath = "~/G4/ANSIsimulations/CNR_Zeff/";
	TString source = "brem";
	for (Int_t toss = 1; toss <= 10; toss++){
		TFile * inputFile = new TFile(basePath + "/ReconImages/imgs_" + source +
							 "RawDataToss" + TString::Itoa(toss,10) + ".root");
		TH2D* trans4 = (TH2D*)inputFile->Get("tLow");
		TH2D* trans15 = (TH2D*)inputFile->Get("tHigh");
		TH2D* transTotal = (TH2D*)inputFile->Get("Ttotal");
		Int_t nBinsX = trans4->GetNbinsX();
		Int_t nBinsY = trans4->GetNbinsY();
		ofstream outFile4, outFile15, outFileTotal;
		outFile4.open("MatrixTxtFiles/" + source + "Tlow_toss"+to_string(toss)+"_errorSTD.txt");
		outFile15.open("MatrixTxtFiles/" + source + "Thigh_toss"+to_string(toss)+"_errorSTD.txt");
		outFileTotal.open("MatrixTxtFiles/" + source + "Ttotal_toss"+to_string(toss)+"_errorSTD.txt");
		for (Int_t j = nBinsY; j > 0; j--){
			for (Int_t i  = 0; i < nBinsX; i++){
				Int_t binNo = trans4->GetBin(i+1,j);
				outFile4 << trans4->GetBinError(binNo) << " ";
				outFile15 << trans15->GetBinError(binNo) << " ";
				outFileTotal << transTotal->GetBinError(binNo) << " ";			
			}
			outFile4 << endl;
			outFile15 << endl;
			outFileTotal << endl;
		}
		outFile4.close();
		outFile15.close();
		outFileTotal.close();

		delete transTotal;
		delete trans4;
		delete trans15;
		inputFile->Close();
		delete inputFile;
	}
	
	return 0;
}