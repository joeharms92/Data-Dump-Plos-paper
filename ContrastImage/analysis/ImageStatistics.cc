#include "TH2.h"
#include "TSystem.h"
#include "TFile.h"

#include <iostream>

using namespace std;

Double_t MeanBG(TH2D*, Int_t, Int_t, Int_t, Int_t);
Double_t BGNoiseSTD(TH2D*, Double_t, Int_t, Int_t, Int_t, Int_t);
Double_t BGUncertainty(TH2D*, Int_t, Int_t, Int_t, Int_t)

int main() 
{
	gSystem->Load("libTree");

	Int_t multiplier = 1;
	TString source = "lenr";

	TString baseFolder = "~/G4/ContainerBigRun/ContainerPerformance/ReconImages/";
	TFile * inFile = new TFile(baseFolder + "imgs_" + source + "RawDataToss" + TString::Itoa(multiplier,10) + ".root");
	TH2D * img = (TH2D*)inFile->Get("Ratio");

	Int_t ** centers = new Int_t*[6];
	for (Int_t i = 0; i < 6; i++){
		centers[i] = new Int_t[2];
	}
	centers[0][0] = 237;
	centers[0][1] = 174;
	centers[1][0] = 237;
	centers[1][1] = 221;
	centers[2][0] = 237;
	centers[2][1] = 267;
	centers[3][0] = 237;
	centers[3][1] = 314;
	centers[4][0] = 237;
	centers[4][1] = 361;
	centers[5][0] = 237;
	centers[5][1] = 408;

	// uniform region 1
	Int_t lowerBoundBgX_1 = 5;
	Int_t lowerBoundBgY_1 = 160;
	Int_t upperBoundBgX_1 = 60;
	Int_t upperBoundBgY_1 = 420;
	Double_t meanRegion1 = MeanBG(img, lowerBoundBgX_1, upperBoundBgX_1, lowerBoundBgY_1, upperBoundBgY_1);
	Double_t noiseSTDRegion1 = BGNoiseSTD(img, meanRegion1,
									lowerBoundBgX_1, upperBoundBgX_1, lowerBoundBgY_1, upperBoundBgY_1);
	Double_t uncertaintyRegion1 = BGNoiseSTD(img,
									lowerBoundBgX_1, upperBoundBgX_1, lowerBoundBgY_1, upperBoundBgY_1);


	// uniform region2
	Int_t lowerBoundBgX_2 = 95;
	Int_t lowerBoundBgY_2 = lowerBoundBgY_1;
	Int_t upperBoundBgX_2 = 140;
	Int_t upperBoundBgY_2 = upperBoundBgY_1;
	Double_t meanRegion2 = MeanBG(img, lowerBoundBgX_2, upperBoundBgX_2, lowerBoundBgY_2, upperBoundBgY_2);
	Double_t noiseSTDRegion2 = BGNoiseSTD(img, meanRegion2,
									lowerBoundBgX_2, upperBoundBgX_2, lowerBoundBgY_2, upperBoundBgY_2);
	Double_t uncertaintyRegion2 = BGNoiseSTD(img,
									lowerBoundBgX_2, upperBoundBgX_2, lowerBoundBgY_2, upperBoundBgY_2);


	// uniform region 3
	Int_t lowerBoundBgX_3 = 170;
	Int_t lowerBoundBgY_3 = lowerBoundBgY_1;
	Int_t upperBoundBgX_3 = 220;
	Int_t upperBoundBgY_3 = upperBoundBgY_1;
	Double_t meanRegion3 = MeanBG(img, lowerBoundBgX_3, upperBoundBgX_3, lowerBoundBgY_3, upperBoundBgY_3);
	Double_t noiseSTDRegion3 = BGNoiseSTD(img, meanRegion3,
									lowerBoundBgX_3, upperBoundBgX_3, lowerBoundBgY_3, upperBoundBgY_3);
	Double_t uncertaintyRegion3 = BGNoiseSTD(img,
									lowerBoundBgX_3, upperBoundBgX_3, lowerBoundBgY_3, upperBoundBgY_3);


	// region in the water
	Int_t lowerBoundBgX_4 = 285;
	Int_t lowerBoundBgY_4 = lowerBoundBgY_1;
	Int_t upperBoundBgX_4 = 305;
	Int_t upperBoundBgY_4 = upperBoundBgY_1;
	Double_t meanRegion4 = MeanBG(img, lowerBoundBgX_4, upperBoundBgX_4, lowerBoundBgY_4, upperBoundBgY_4);
	Double_t noiseSTDRegion4 = BGNoiseSTD(img, meanRegion4,
									lowerBoundBgX_4, upperBoundBgX_4, lowerBoundBgY_4, upperBoundBgY_4);
	Double_t uncertaintyRegion4 = BGNoiseSTD(img,
									lowerBoundBgX_4, upperBoundBgX_4, lowerBoundBgY_4, upperBoundBgY_4);


	Int_t lowerBoundBgX_5 = 330;
	Int_t lowerBoundBgY_5 = lowerBoundBgY_1;
	Int_t upperBoundBgX_5 = 350;
	Int_t upperBoundBgY_5 = upperBoundBgY_1;
	Double_t meanRegion5 = MeanBG(img, lowerBoundBgX_5, upperBoundBgX_5, lowerBoundBgY_5, upperBoundBgY_5);
	Double_t noiseSTDRegion5 = BGNoiseSTD(img, meanRegion5,
									lowerBoundBgX_5, upperBoundBgX_5, lowerBoundBgY_5, upperBoundBgY_5);
	Double_t uncertaintyRegion5 = BGNoiseSTD(img,
									lowerBoundBgX_5, upperBoundBgX_5, lowerBoundBgY_5, upperBoundBgY_5);


	// background below and above the steel plates
	// no plate but blocks
	Int_t lowerBoundBgX_6 = 500;
	Int_t lowerBoundBgY_6 = 160;
	Int_t upperBoundBgX_6 = 549;
	Int_t upperBoundBgY_6 = 260;
	Double_t meanRegion6 = MeanBG(img, lowerBoundBgX_6, upperBoundBgX_6, lowerBoundBgY_6, upperBoundBgY_6);
	Double_t noiseSTDRegion6 = BGNoiseSTD(img, meanRegion6,
									lowerBoundBgX_6, upperBoundBgX_6, lowerBoundBgY_6, upperBoundBgY_6);
	Double_t uncertaintyRegion6 = BGNoiseSTD(img,
									lowerBoundBgX_6, upperBoundBgX_6, lowerBoundBgY_6, upperBoundBgY_6);


	Int_t lowerBoundBgX_7 = 500;
	Int_t lowerBoundBgY_7 = 325;
	Int_t upperBoundBgX_7 = 549;
	Int_t upperBoundBgY_7 = 420;
	Double_t meanRegion7 = MeanBG(img, lowerBoundBgX_7, upperBoundBgX_7, lowerBoundBgY_7, upperBoundBgY_7);
	Double_t noiseSTDRegion7 = BGNoiseSTD(img, meanRegion7,
									lowerBoundBgX_7, upperBoundBgX_7, lowerBoundBgY_7, upperBoundBgY_7);
	Double_t uncertaintyRegion7 = BGNoiseSTD(img,
									lowerBoundBgX_7, upperBoundBgX_7, lowerBoundBgY_7, upperBoundBgY_7);


	//10 cm plate
	Int_t lowerBoundBgX_8 = 551;
	Int_t lowerBoundBgY_8 = lowerBoundBgY_6;
	Int_t upperBoundBgX_8 = 622;
	Int_t upperBoundBgY_8 = upperBoundBgY_6;
	Double_t meanRegion8 = MeanBG(img, lowerBoundBgX_8, upperBoundBgX_8, lowerBoundBgY_8, upperBoundBgY_8);
	Double_t noiseSTDRegion8 = BGNoiseSTD(img, meanRegion8,
									lowerBoundBgX_8, upperBoundBgX_8, lowerBoundBgY_8, upperBoundBgY_8);
	Double_t uncertaintyRegion8 = BGNoiseSTD(img,
									lowerBoundBgX_8, upperBoundBgX_8, lowerBoundBgY_8, upperBoundBgY_8);


	Int_t lowerBoundBgX_9 = 551;
	Int_t lowerBoundBgY_9 = lowerBoundBgY_7;
	Int_t upperBoundBgX_9 = 622;
	Int_t upperBoundBgY_9 = upperBoundBgY_7;
	Double_t meanRegion9 = MeanBG(img, lowerBoundBgX_9, upperBoundBgX_9, lowerBoundBgY_9, upperBoundBgY_9);
	Double_t noiseSTDRegion9 = BGNoiseSTD(img, meanRegion9,
									lowerBoundBgX_9, upperBoundBgX_9, lowerBoundBgY_9, upperBoundBgY_9);
	Double_t uncertaintyRegion9 = BGNoiseSTD(img,
									lowerBoundBgX_9, upperBoundBgX_9, lowerBoundBgY_9, upperBoundBgY_9);


	//20 cm plate
	Int_t lowerBoundBgX_10 = 625;
	Int_t lowerBoundBgY_10 = lowerBoundBgY_6;
	Int_t upperBoundBgX_10 = 690;
	Int_t upperBoundBgY_10 = upperBoundBgY_6;
	Double_t meanRegion10 = MeanBG(img, lowerBoundBgX_10, upperBoundBgX_10, lowerBoundBgY_10, upperBoundBgY_10);
	Double_t noiseSTDRegion10 = BGNoiseSTD(img, meanRegion10,
									lowerBoundBgX_10, upperBoundBgX_10, lowerBoundBgY_10, upperBoundBgY_10);
	Double_t uncertaintyRegion10 = BGNoiseSTD(img,
									lowerBoundBgX_10, upperBoundBgX_10, lowerBoundBgY_10, upperBoundBgY_10);


	Int_t lowerBoundBgX_11 = 625;
	Int_t lowerBoundBgY_11 = lowerBoundBgY_7;
	Int_t upperBoundBgX_11 = 690;
	Int_t upperBoundBgY_11 = upperBoundBgY_7;
	Double_t meanRegion11 = MeanBG(img, lowerBoundBgX_11, upperBoundBgX_11, lowerBoundBgY_11, upperBoundBgY_11);
	Double_t noiseSTDRegion11 = BGNoiseSTD(img, meanRegion11,
									lowerBoundBgX_11, upperBoundBgX_11, lowerBoundBgY_11, upperBoundBgY_11);
	Double_t uncertaintyRegion11 = BGNoiseSTD(img,
									lowerBoundBgX_11, upperBoundBgX_11, lowerBoundBgY_11, upperBoundBgY_11);

	cout << meanRegion1 << " " << noiseSTDRegion1 << " " << uncertaintyRegion1 << endl;
	/*Double_t* waterVal = new Double_t[1650];
	Int_t counter = 0;
	Double_t runningSum = 0;

	Double_t waterStatErrorSum = 0;
	for (Int_t i = lowerBoundBgX_1; i <= upperBoundBgX_1; i++){
		for (Int_t j = lowerBoundBgY_1; j <= upperBoundBgY_1; j++){
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
	delete waterVal;*/
	for (Int_t i = 0; i < 6; i++){
		delete centers[i];
	}
	delete[] centers;

	delete inFile;



	return 0;
}

Double_t MeanBG(TH2D* img, Int_t lowX, Int_t highX, Int_t lowY, Int_t highY)
{
	Int_t counter = 0;
	Double_t runningSum = 0;
	for (Int_t i = lowX; i <= highX; i++){
		for (Int_t j = lowY; j <= highY; j++){
			runningSum += img->GetBinContent(img->GetBin(i, j));
			counter++;
		}
	} 
	return (runningSum / (Double_t)counter);
}

Double_t BGNoiseSTD(TH2D* img, Double_t mean, Int_t lowX, Int_t highX, Int_t lowY, Int_t highY)
{
	Int_t counter = 0;
	Double_t stdevCounter = 0;
	for (Int_t i = lowX; i <= highX; i++){
		for (Int_t j = lowY; j <= highY; j++){
			Double_t val = img->GetBinContent(img->GetBin(i, j));
			stdevCounter += (mean - val)*(mean - val);
			counter++;
		}
	} 
	return (sqrt( (1./((Double_t)counter)) * stdevCounter));
}

Double_t BGUncertainty(TH2D* img, Int_t lowX, Int_t highX, Int_t lowY, Int_t highY)
{
	Int_t counter = 0;
	Double_t runningSum = 0;
	for (Int_t i = lowX; i <= highX; i++){
		for (Int_t j = lowY; j <= highY; j++){
			Int_t binNo = img->GetBin(i, j);
			Double_t binVal = img->GetBinError(binNo);
			runningSum += binVal*binVal;
			counter++;
		}
	} 
	return (sqrt(runningSum)/(Double_t)counter);
}