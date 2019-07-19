#include "TH2.h"
#include "TSystem.h"
#include "TFile.h"

#include <iostream>

using namespace std;

int main() 
{
	gSystem->Load("libTree");

	Int_t multiplier = 5;
	TString source = "lenr";

	TString baseFolder = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/";
	TFile * inFile = new TFile(baseFolder + "imgs_" + source + "RawDataToss" + TString::Itoa(multiplier,10) + ".root");
	TH2D * img = (TH2D*)inFile->Get("Ratio");

	Int_t ** centers = new Int_t*[6];
	for (Int_t i = 0; i < 6; i++){
		centers[i] = new Int_t[2];
	}
	centers[0][0] = 83;
	centers[0][1] = 92;
	centers[1][0] = 125;
	centers[1][1] = 49;
	centers[2][0] = 125;
	centers[2][1] = 92;
	centers[3][0] = 145;
	centers[3][1] = 71;
	centers[4][0] = 83;
	centers[4][1] = 49;
	centers[5][0] = 62;
	centers[5][1] = 71;

	Int_t lowerBoundBgX = 76;
	Int_t lowerBoundBgY = 56;
	Int_t upperBoundBgX = 130;
	Int_t upperBoundBgY = 85;
	Double_t* waterVal = new Double_t[1650];
	Int_t counter = 0;
	Double_t runningSum = 0;

	Double_t waterStatErrorSum = 0;
	for (Int_t i = lowerBoundBgX; i <= upperBoundBgX; i++){
		for (Int_t j = lowerBoundBgY; j <= upperBoundBgY; j++){
			Int_t binNo = img->GetBin(i, j);
			waterVal[counter] = img->GetBinContent(binNo);
			waterStatErrorSum += img->GetBinError(binNo)*img->GetBinError(binNo);
			runningSum += waterVal[counter];
			counter++;
		}
	} 
	Double_t meanWater = runningSum / (Double_t)counter;

	Double_t stdevCounter = 0;
	for (Int_t i = 0; i < 1650; i++){
		stdevCounter += (meanWater - waterVal[i])*(meanWater - waterVal[i]);
	}

	Double_t stdev = sqrt( (1./1650.) * stdevCounter);
	Double_t waterRatioError = sqrt(waterStatErrorSum)/1650.;


	Double_t * meanVals = new Double_t[6];
	Double_t * errorsImg = new Double_t[6];
	Double_t * errorsStats = new Double_t[6];


	Double_t minorRad = 3.5;
	Double_t majorRad = 6.5;
	Double_t rSqEllipse = minorRad*minorRad*majorRad*majorRad;
	Int_t iterVal = 0;
	for (Int_t i = 0; i < 6; i++){
		meanVals[i] = 0;
		Int_t lowerBoundCircleX = centers[i][0]-7;
		Int_t upperBoundCircleX = centers[i][0]+7;
		Int_t lowerBoundCircleY = centers[i][1] - 4;
		Int_t upperBoundCircleY = centers[i][1] + 4;
		for (Int_t m = lowerBoundCircleX; m <= upperBoundCircleX; m++){
			for (Int_t n = lowerBoundCircleY; n <= upperBoundCircleY; n++){
				Double_t ellipVal = ((Double_t)(m-centers[i][0])*(m-centers[i][0]))*minorRad*minorRad + ((Double_t)(n-centers[i][1])*(n-centers[i][1]))*majorRad*majorRad;
				if ( ellipVal < rSqEllipse){
					Int_t binNo = img->GetBin(m,n);
					meanVals[i] += img->GetBinContent(binNo);
					iterVal++;				
				}
			}
		}
		meanVals[i] /= iterVal;
		iterVal = 0;
	}

	Double_t thisStDevSum = 0;
	Double_t thisStatErrorSum = 0;
	Int_t statCounter = 0;
	for (Int_t i = 0; i < 6; i++){
		Int_t lowerBoundCircleX = centers[i][0]-7;
		Int_t upperBoundCircleX = centers[i][0]+7;
		Int_t lowerBoundCircleY = centers[i][1] - 4;
		Int_t upperBoundCircleY = centers[i][1] + 4;
		for (Int_t m = lowerBoundCircleX; m <= upperBoundCircleX; m++){
			for (Int_t n = lowerBoundCircleY; n <= upperBoundCircleY; n++){
				Double_t ellipVal = ((Double_t)(m-centers[i][0])*(m-centers[i][0]))*minorRad*minorRad + ((Double_t)(n-centers[i][1])*(n-centers[i][1]))*majorRad*majorRad;
				if ( ellipVal < rSqEllipse){
					Int_t binNo = img->GetBin(m,n);
					Double_t binContent = img->GetBinContent(binNo);
					if (binContent > 0){
						thisStDevSum += (meanVals[i] - img->GetBinContent(binNo))*(meanVals[i] - img->GetBinContent(binNo));
						iterVal++;	
						Double_t binError = img->GetBinError(binNo);
						if (binError> 0){
							thisStatErrorSum += img->GetBinError(binNo)*img->GetBinError(binNo);
							statCounter++;
						}
					}	
				}
			}
		}
		errorsImg[i] = sqrt(thisStDevSum / (iterVal - 1));
		errorsStats[i] = sqrt(thisStatErrorSum)/statCounter;
		iterVal = 0;
		statCounter = 0;
		thisStDevSum = 0;
		thisStatErrorSum = 0;
	}

	cout << meanVals[0] << endl;
	cout << meanVals[2] << endl;
	cout << meanVals[3] << endl;
	cout << meanVals[1] << endl;
	cout << meanVals[4] << endl;
	cout << meanVals[5] << endl;
	cout << meanWater << endl << endl;

	cout << errorsImg[0] << endl;
	cout << errorsImg[2] << endl;
	cout << errorsImg[3] << endl;
	cout << errorsImg[1] << endl;
	cout << errorsImg[4] << endl;
	cout << errorsImg[5] << endl;
	cout << stdev << endl << endl;

	cout << meanWater << " " << stdev << endl << endl;
	cout << errorsStats[0] <<  endl;
	cout << errorsStats[2] <<  endl;
	cout << errorsStats[3] <<  endl;
	cout << errorsStats[1] <<  endl;
	cout << errorsStats[4] <<  endl;
	cout << errorsStats[5] << endl;
	cout << waterRatioError << endl <<  endl;


	delete errorsImg;
	delete errorsStats;
	delete meanVals;
	delete waterVal;
	for (Int_t i = 0; i < 6; i++){
		delete centers[i];
	}
	delete[] centers;

	delete inFile;



	return 0;
}