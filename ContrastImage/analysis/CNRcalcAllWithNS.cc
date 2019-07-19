#include "TH2.h"
#include "TSystem.h"
#include "TFile.h"

#include <iostream>

using namespace std;

Double_t MeanWater(TH2D*);
Double_t WaterNoiseSTD(TH2D*, Double_t);
Double_t WaterUncertainty(TH2D*);
Double_t * RodMeans(TH2D*, Int_t**);
Double_t * RodNoiseSTD(TH2D*, Double_t*, Int_t**);
Double_t * RodsUncertainty(TH2D*, Int_t**);

const static Int_t lowerBoundBgX = 76;
const static Int_t lowerBoundBgY = 56;
const static Int_t upperBoundBgX = 130;
const static Int_t upperBoundBgY = 85;
const static Double_t minorRad = 3.5;
const static Double_t majorRad = 6.5;

int main() 
{
	gSystem->Load("libTree");

	TString source = "lenr";

	TString baseFolder = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/";
	TFile * inFile = new TFile(baseFolder + source + "RatiosNS.root");
	TH2D** imgsOrig = new  TH2D*[10];
	TH2D** imgsNS = new TH2D*[10];
	for (Int_t i = 0; i < 10; i++){
		imgsOrig[i] = (TH2D*)inFile->Get(source+"RatioOrigtoss" + TString::Itoa(i+1,10));
		imgsNS[i] = (TH2D*)inFile->Get(source+"RatioNStoss" + TString::Itoa(i+1,10));
	}

	Double_t * waterMeansOrig = new Double_t[10];
	Double_t * waterMeansNS = new Double_t[10];
	for (Int_t i = 0; i < 10; i++){
		waterMeansOrig[i] = MeanWater(imgsOrig[i]);
		waterMeansNS[i] = MeanWater(imgsNS[i]);
	}
	Double_t * waterNoiseSTDOrig = new Double_t[10];
	Double_t * waterNoiseSTDNS = new Double_t[10];
	for (Int_t i = 0; i < 10; i++){
		waterNoiseSTDOrig[i] = WaterNoiseSTD(imgsOrig[i], waterMeansOrig[i]);
		waterNoiseSTDNS[i] = WaterNoiseSTD(imgsNS[i], waterMeansNS[i]);
	}
	Double_t * waterUncertaintyOrig = new Double_t[10];
	Double_t * waterUncertaintyNS = new Double_t[10];
	for (Int_t i = 0; i < 10; i++){
		waterUncertaintyOrig[i] = WaterUncertainty(imgsOrig[i]);
		waterUncertaintyNS[i] = WaterUncertainty(imgsNS[i]);
	}

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


	for (Int_t i = 0; i < 10; i++){
		Double_t * meanValsOrig = RodMeans(imgsOrig[i], centers);
		Double_t * meanValsNS = RodMeans(imgsNS[i], centers);

		Double_t * rodsNoiseSTDOrig = RodNoiseSTD(imgsOrig[i], meanValsOrig, centers);
		Double_t * rodsNoiseSTDNS = RodNoiseSTD(imgsNS[i], meanValsNS, centers);

		Double_t * rodsUncertaintyOrig = RodsUncertainty(imgsOrig[i], centers);
		Double_t * rodsUncertaintyNS = RodsUncertainty(imgsNS[i], centers);

		cout << "------------" << source << " Toss " << i+1 << "------------" << endl;
		cout << "||||| ORIG |||||" << endl;
		cout << meanValsOrig[0] << endl;
		cout << meanValsOrig[2] << endl;
		cout << meanValsOrig[3] << endl;
		cout << meanValsOrig[1] << endl;
		cout << meanValsOrig[4] << endl;
		cout << meanValsOrig[5] << endl;
		cout << waterMeansOrig[i] << endl << endl;

		cout << rodsNoiseSTDOrig[0] << endl;
		cout << rodsNoiseSTDOrig[2] << endl;
		cout << rodsNoiseSTDOrig[3] << endl;
		cout << rodsNoiseSTDOrig[1] << endl;
		cout << rodsNoiseSTDOrig[4] << endl;
		cout << rodsNoiseSTDOrig[5] << endl;
		cout << waterNoiseSTDOrig[i] << endl << endl;

		cout << rodsUncertaintyOrig[0] <<  endl;
		cout << rodsUncertaintyOrig[2] <<  endl;
		cout << rodsUncertaintyOrig[3] <<  endl;
		cout << rodsUncertaintyOrig[1] <<  endl;
		cout << rodsUncertaintyOrig[4] <<  endl;
		cout << rodsUncertaintyOrig[5] << endl;
		cout << waterUncertaintyOrig[i] << endl <<  endl;

		cout << "||||| NS |||||" << endl;
		cout << meanValsNS[0] << endl;
		cout << meanValsNS[2] << endl;
		cout << meanValsNS[3] << endl;
		cout << meanValsNS[1] << endl;
		cout << meanValsNS[4] << endl;
		cout << meanValsNS[5] << endl;
		cout << waterMeansNS[i] << endl << endl;

		cout << rodsNoiseSTDNS[0] << endl;
		cout << rodsNoiseSTDNS[2] << endl;
		cout << rodsNoiseSTDNS[3] << endl;
		cout << rodsNoiseSTDNS[1] << endl;
		cout << rodsNoiseSTDNS[4] << endl;
		cout << rodsNoiseSTDNS[5] << endl;
		cout << waterNoiseSTDNS[i] << endl << endl;

		cout << rodsUncertaintyNS[0] <<  endl;
		cout << rodsUncertaintyNS[2] <<  endl;
		cout << rodsUncertaintyNS[3] <<  endl;
		cout << rodsUncertaintyNS[1] <<  endl;
		cout << rodsUncertaintyNS[4] <<  endl;
		cout << rodsUncertaintyNS[5] << endl;
		cout << waterUncertaintyNS[i] << endl <<  endl;

		delete meanValsOrig;
		delete meanValsNS;
		delete rodsNoiseSTDOrig;
		delete rodsNoiseSTDNS;
		delete rodsUncertaintyOrig;
		delete rodsUncertaintyNS;

	}

	for (Int_t i = 0; i < 6; i++){
		delete centers[i];
	}
	delete[] centers;

	delete waterMeansOrig;
	delete waterMeansNS;
	delete waterNoiseSTDOrig;
	delete waterNoiseSTDNS;
	delete waterUncertaintyOrig;
	delete waterUncertaintyNS; 
	for (Int_t i = 0; i < 10; i++){
		delete imgsOrig[i];
		delete imgsNS[i];
	}
	delete[] imgsOrig;
	delete[] imgsNS;
	inFile->Close();
	delete inFile;
	
	return 0;
}

Double_t MeanWater(TH2D* img)
{
	Int_t counter = 0;
	Double_t runningSum = 0;
	for (Int_t i = lowerBoundBgX; i <= upperBoundBgX; i++){
		for (Int_t j = lowerBoundBgY; j <= upperBoundBgY; j++){
			runningSum += img->GetBinContent(img->GetBin(i, j));
			counter++;
		}
	} 
	return (runningSum / (Double_t)counter);
}

Double_t WaterNoiseSTD(TH2D* img, Double_t mean)
{
	Int_t counter = 0;
	Double_t stdevCounter = 0;
	for (Int_t i = lowerBoundBgX; i <= upperBoundBgX; i++){
		for (Int_t j = lowerBoundBgY; j <= upperBoundBgY; j++){
			Double_t waterVal = img->GetBinContent(img->GetBin(i, j));
			stdevCounter += (mean - waterVal)*(mean - waterVal);
			counter++;
		}
	} 
	return (sqrt( (1./((Double_t)counter)) * stdevCounter));
}

Double_t WaterUncertainty(TH2D* img)
{
	Int_t counter = 0;
	Double_t runningSum = 0;
	for (Int_t i = lowerBoundBgX; i <= upperBoundBgX; i++){
		for (Int_t j = lowerBoundBgY; j <= upperBoundBgY; j++){
			Int_t binNo = img->GetBin(i, j);
			Double_t binVal = img->GetBinError(binNo);
			runningSum += binVal*binVal;
			counter++;
		}
	} 
	return (sqrt(runningSum)/(Double_t)counter);
}

Double_t * RodMeans(TH2D* img, Int_t** centers)
{
	Double_t rSqEllipse = minorRad*minorRad*majorRad*majorRad;
	Double_t* meanVals = new Double_t[6];
	Double_t minorRad = 3.5;
	Double_t majorRad = 6.5;
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
	return meanVals;
}

Double_t * RodNoiseSTD(TH2D* img, Double_t * means, Int_t** centers)
{
	Double_t rSqEllipse = minorRad*minorRad*majorRad*majorRad;
	Double_t *rodsNoiseSTD = new Double_t[6];
	Double_t thisStDevSum = 0;
	Double_t iterVal = 0;
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
						thisStDevSum += (means[i] - img->GetBinContent(binNo))*(means[i] - img->GetBinContent(binNo));
						iterVal++;	
					}	
				}
			}
		}
		rodsNoiseSTD[i] = sqrt(thisStDevSum / (iterVal - 1));
		iterVal = 0;
		thisStDevSum = 0;
	}
	return rodsNoiseSTD;
}

Double_t * RodsUncertainty(TH2D* imgError, Int_t** centers)
{
	Double_t rSqEllipse = minorRad*minorRad*majorRad*majorRad;
	Double_t* uncertainties = new Double_t[6];
	Double_t errorQuadSum = 0;
	Int_t iterVal = 0;
	for (Int_t i = 0; i < 6; i++){
		Int_t lowerBoundCircleX = centers[i][0]-7;
		Int_t upperBoundCircleX = centers[i][0]+7;
		Int_t lowerBoundCircleY = centers[i][1] - 4;
		Int_t upperBoundCircleY = centers[i][1] + 4;
		for (Int_t m = lowerBoundCircleX; m <= upperBoundCircleX; m++){
			for (Int_t n = lowerBoundCircleY; n <= upperBoundCircleY; n++){
				Double_t ellipVal = ((Double_t)(m-centers[i][0])*(m-centers[i][0]))*minorRad*minorRad + ((Double_t)(n-centers[i][1])*(n-centers[i][1]))*majorRad*majorRad;
				if ( ellipVal < rSqEllipse){
					Int_t binNo = imgError->GetBin(m,n);
					Double_t binContent = imgError->GetBinError(binNo);
					if (binContent > 0){
						errorQuadSum += binContent*binContent;
						iterVal++;	
					}	
				}
			}
		}
		uncertainties[i] = sqrt(errorQuadSum)/((Double_t)iterVal);
		iterVal = 0;
		errorQuadSum = 0;
	}
	return uncertainties;
}