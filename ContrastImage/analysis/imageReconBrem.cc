#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>

#include <iostream>
#include <fstream>

TH2D* Transmission(TString, TString);
TH2D* CalculateRatio(TH2D*, TH2D*);
TH2D* CalculateZeff(TH2D*);
void Plot(TH2D*, TH2D*, TH2D*, TH2D*, TString);
Double_t* CreateEnergyAxis(TH1D*);

const static Int_t numSlices = 220;
const static Int_t numDets = 70;
const static Int_t numNewSlices = numSlices - 4; // flatfield is first and last slices
const static Int_t multiplier = 25;


using namespace std;

int main(int argc, char * argv[]) 
{
	gSystem->Load("libTree");

	TString baseFolder = "/home/jharms/G4/ANSIsimulations/CNR_Zeff/results/";

  TString outputFileName = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/imgs_brem_" + TString::Itoa(multiplier, 10) + "x.root";

	TH2D* trans6 = Transmission("brem6", baseFolder);
	TH2D* trans9 = Transmission("brem9", baseFolder);
	TH2D* transTotal = Transmission("both", baseFolder);

	TH2D* ratio = CalculateRatio(trans6, trans9);
	TH2D* zeff = CalculateZeff(ratio);

	TFile* outputFile = new TFile(outputFileName, "RECREATE");
	transTotal->Write();
	trans6->Write();
	trans9->Write();
	ratio->Write();
	zeff->Write();
	outputFile->Close();

	Plot(transTotal, trans6, trans9, zeff, "/home/jharms/G4/ANSIsimulations/CNR_Zeff/ReconImages/");

	return 0;

}

TH2D* Transmission(TString whichEnergy, TString path)
{

	TH2D* img = new TH2D(whichEnergy, "", numNewSlices, 0, numNewSlices, 
	numDets*2, 0 , numDets*2);

	Double_t lowerBound, upperBound;
	Double_t countsAir[numDets*2];

	 if (whichEnergy == "both"){
		TFile * ff1File6 = new TFile(path + "brem6/" + "convSlice0_brem6_" + TString::Itoa(multiplier, 10) + "x.root");
		TFile * ff1File9 = new TFile(path + "brem9/" + "convSlice0_brem9_" + TString::Itoa(multiplier, 10) + "x.root");
		TFile * ff2File6 = new TFile(path + "brem6/" + "convSlice1_brem6_" + TString::Itoa(multiplier, 10) + "x.root");
		TFile * ff2File9 = new TFile(path + "brem9/" + "convSlice1_brem9_" + TString::Itoa(multiplier, 10) + "x.root");
		TFile * ff3File6 = new TFile(path + "brem6/" + "convSlice218_brem6_" + TString::Itoa(multiplier, 10) + "x.root");
		TFile * ff3File9 = new TFile(path + "brem9/" + "convSlice218_brem9_" + TString::Itoa(multiplier, 10) + "x.root");
		TFile * ff4File6 = new TFile(path + "brem6/" + "convSlice219_brem6_" + TString::Itoa(multiplier, 10) + "x.root");
		TFile * ff4File9 = new TFile(path + "brem9/" + "convSlice219_brem9_" + TString::Itoa(multiplier, 10) + "x.root");

		for (Int_t detIter = 0; detIter < numDets*2; detIter++){
			countsAir[detIter] = 0;
			TH1D* ff1_6 = (TH1D*)ff1File6->Get("Det"+TString::Itoa(detIter, 10) );
			TH1D* ff2_6 = (TH1D*)ff2File6->Get("Det"+TString::Itoa(detIter, 10) );
			TH1D* ff3_6 = (TH1D*)ff3File6->Get("Det"+TString::Itoa(detIter, 10) );
			TH1D* ff4_6 = (TH1D*)ff4File6->Get("Det"+TString::Itoa(detIter, 10) );
			TH1D* ff1_9 = (TH1D*)ff1File9->Get("Det"+TString::Itoa(detIter, 10) );
			TH1D* ff2_9 = (TH1D*)ff2File9->Get("Det"+TString::Itoa(detIter, 10) );
			TH1D* ff3_9 = (TH1D*)ff3File9->Get("Det"+TString::Itoa(detIter, 10) );
			TH1D* ff4_9 = (TH1D*)ff4File9->Get("Det"+TString::Itoa(detIter, 10) );
			Double_t ff1Counts = ff1_6->Integral( ff1_6->FindBin(150), ff1_6->FindBin(800) ) + ff1_9->Integral(ff1_9->FindBin(800), ff1_9->GetNbinsX()-1); 
			Double_t ff2Counts = ff2_6->Integral( ff2_6->FindBin(150), ff2_6->FindBin(800) ) + ff2_9->Integral(ff2_9->FindBin(800), ff2_9->GetNbinsX()-1); 
			Double_t ff3Counts = ff3_6->Integral( ff3_6->FindBin(150), ff3_6->FindBin(800) ) + ff3_9->Integral(ff3_9->FindBin(800), ff3_9->GetNbinsX()-1); 
			Double_t ff4Counts = ff4_6->Integral( ff4_6->FindBin(150), ff4_6->FindBin(800) ) + ff4_9->Integral(ff4_9->FindBin(800), ff4_9->GetNbinsX()-1); 
			countsAir[detIter] = (ff1Counts + ff2Counts + ff3Counts + ff4Counts) / 4.;
		}
		ff1File6->Close();
		ff2File6->Close();
		ff3File6->Close();
		ff4File6->Close();
		ff1File9->Close();
		ff2File9->Close();
		ff3File9->Close();
		ff4File9->Close();
		delete ff1File6;
		delete ff2File6;
		delete ff3File6;
		delete ff4File6;
		delete ff1File9;
		delete ff2File9;
		delete ff3File9;
		delete ff4File9;

		for (Int_t sliceIter = 2; sliceIter < numSlices - 2; sliceIter++){
			TFile * histFile6 = new TFile(path + "brem6/" + "convSlice"+TString::Itoa(sliceIter,10) + "_brem6_" + TString::Itoa(multiplier, 10) + "x.root");
			TFile * histFile9 = new TFile(path + "brem9/" + "convSlice"+TString::Itoa(sliceIter,10) + "_brem9_" + TString::Itoa(multiplier, 10) + "x.root");
			for (Int_t detIter = 0; detIter < numDets*2; detIter++){
				TH1D * hist6 = (TH1D*)histFile6->Get("Det" + TString::Itoa(detIter, 10));
				TH1D * hist9 = (TH1D*)histFile9->Get("Det" + TString::Itoa(detIter, 10));
				Int_t binNum = img->GetBin(sliceIter , detIter+1);
				Double_t pixelVal = (hist6->Integral( hist6->FindBin(150), hist6->FindBin(800) ) + hist9->Integral(hist9->FindBin(800), hist9->GetNbinsX()-1) ) / countsAir[detIter];
				img->SetBinContent(binNum, pixelVal);
			}
			histFile6->Close();
			histFile9->Close();
			delete histFile6;
			delete histFile9;
		}

		return img;
	}

	else if (whichEnergy == "brem6"){
		lowerBound = 150;
		upperBound = 800;
	}
	else if (whichEnergy == "brem9"){
		lowerBound = 800;
		upperBound = 3000.;
	}

	TFile * ff1File = new TFile(path + whichEnergy + "/" + "convSlice0_" + whichEnergy + "_" + TString::Itoa(multiplier, 10) + "x.root");
	TFile * ff2File = new TFile(path + whichEnergy + "/" + "convSlice1_" + whichEnergy + "_" + TString::Itoa(multiplier, 10) + "x.root");
	TFile * ff3File = new TFile(path + whichEnergy + "/" + "convSlice218_" + whichEnergy + "_" + TString::Itoa(multiplier, 10) + "x.root");
	TFile * ff4File = new TFile(path + whichEnergy + "/" + "convSlice219_" + whichEnergy + "_" + TString::Itoa(multiplier, 10) + "x.root");

	for (Int_t detIter = 0; detIter < numDets*2; detIter++){
		countsAir[detIter] = 0;
		TH1D* ff1 = (TH1D*)ff1File->Get("Det"+TString::Itoa(detIter, 10) );
		TH1D* ff2 = (TH1D*)ff2File->Get("Det"+TString::Itoa(detIter, 10) );
		TH1D* ff3 = (TH1D*)ff3File->Get("Det"+TString::Itoa(detIter, 10) );
		TH1D* ff4 = (TH1D*)ff4File->Get("Det"+TString::Itoa(detIter, 10) );
		Double_t ff1Counts = ff1->Integral( ff1->FindBin(lowerBound), ff1->FindBin(upperBound) ); 
		Double_t ff2Counts = ff2->Integral( ff2->FindBin(lowerBound), ff2->FindBin(upperBound) ); 
		Double_t ff3Counts = ff3->Integral( ff3->FindBin(lowerBound), ff3->FindBin(upperBound) ); 
		Double_t ff4Counts = ff4->Integral( ff4->FindBin(lowerBound), ff4->FindBin(upperBound) ); 
		countsAir[detIter] = (ff1Counts + ff2Counts + ff3Counts + ff4Counts) / 4.;
	}
	ff1File->Close();
	ff2File->Close();
	ff3File->Close();
	ff4File->Close();
	delete ff1File;
	delete ff2File;
	delete ff3File;
	delete ff4File;

	for (Int_t sliceIter = 2; sliceIter < numSlices - 2; sliceIter++){
		TFile * histFile = new TFile(path + whichEnergy + "/" + "convSlice"+TString::Itoa(sliceIter,10) + "_" + whichEnergy + "_" + TString::Itoa(multiplier, 10) + "x.root");
		for (Int_t detIter = 0; detIter < numDets*2; detIter++){
			TH1D * hist = (TH1D*)histFile->Get("Det" + TString::Itoa(detIter, 10));
			Int_t binNum = img->GetBin(sliceIter , detIter+1);
			Double_t pixelVal = hist->Integral( hist->FindBin(lowerBound), hist->FindBin(upperBound) ) / countsAir[detIter];
			img->SetBinContent(binNum, pixelVal);
		}
		histFile->Close();
		delete histFile;
	}

	return img;

}

TH2D* CalculateRatio(TH2D* t4, TH2D* t15)
{

	TH2D* ratio = new TH2D("Ratio", "", numNewSlices, 0, numNewSlices, 
	numDets*2, 0 , numDets*2);

	Double_t val4, val15, ratioVal;

	for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
		for (Int_t detIter = 0; detIter < numDets*2; detIter++){

			Int_t binNum = ratio->GetBin(sliceIter,detIter+1);
			val4 = t4->GetBinContent(binNum) ;
			val15 = t15->GetBinContent(binNum);
			if (val4 >=1 || val15 >=1 ){
				ratioVal = 0.01;
			}
      		else if (val4 == 0 || val15 == 0){
        		ratioVal = 0.01;
        	}	else {
				ratioVal = log(val15)/log(val4);
			}
			if ( (ratioVal > 1.5) || (ratioVal <= 0) ) {
				ratioVal = 0.01;
			}
			ratio->SetBinContent(binNum, ratioVal);
		}
	}
	return ratio;
}

TH2D* CalculateZeff(TH2D* ratio)
{
	TH2D* zeff = new TH2D("Zeff", "", numNewSlices, 0, numNewSlices, 
	numDets*2, 0 , numDets*2);

	Double_t zVal;
	for (Int_t sliceIter = 0; sliceIter < numNewSlices; sliceIter++){
		for (Int_t detIter = 0; detIter < numDets*2; detIter++){
			Int_t binNum = ratio->GetBin(sliceIter,detIter+1);
			Double_t ratioVal = ratio->GetBinContent(binNum);      
			if (ratioVal < 0.6) zVal =  67.3833302388* pow(ratioVal, 6.2489026105);
      	else if (ratioVal < 1.1) zVal = 196.1989152536*ratioVal*ratioVal - 165.3634129833*ratioVal + 27.4727791661;
      	else zVal = 6015.372628873*ratioVal*ratioVal - 11601.9735978539*ratioVal + 5646.402277446;

      	if (zVal > 100) zVal = 100;
			zeff->SetBinContent(binNum, zVal);

		}

	}
	return zeff;
}

void Plot(TH2D* transmissionTotal, TH2D* transmission4, TH2D* transmission15, TH2D* zeff, TString path)
{
	gStyle->SetPalette(53);
	gStyle->SetOptStat(0);

	TCanvas *c1 = new TCanvas("c1","Total Transmission",0,0,528,378);

	transmissionTotal->GetXaxis()->SetNdivisions(0);
	transmissionTotal->GetXaxis()->SetLabelSize(0.0);

	transmissionTotal->GetYaxis()->SetNdivisions(numDets*2);
	transmissionTotal->GetYaxis()->SetLabelSize(0.0);
	transmissionTotal->GetYaxis()->SetTickLength(0.01);

	transmissionTotal->GetZaxis()->SetNdivisions(5);
	transmissionTotal->GetZaxis()->SetLabelSize(0.07);
	transmissionTotal->GetZaxis()->SetTitleOffset(1.0);
	transmissionTotal->GetZaxis()->SetTitle("");
	transmissionTotal->GetZaxis()->SetRangeUser(0.0,1.0);
	transmissionTotal->GetZaxis()->SetDecimals(kTRUE);

	transmissionTotal->SetTitle("");
	transmissionTotal->Draw("COLZ");
	transmissionTotal->SetStats(kFALSE);
	transmissionTotal->SetContour(99);

	c1->SetRightMargin(0.3);
	c1->cd();

	TCanvas *c2 = new TCanvas("c2","T4 MeV",0,0,528,378);

	transmission4->GetZaxis()->SetTitle("");
	transmission4->GetZaxis()->SetRangeUser(0.0,1.);

	transmission4->GetXaxis()->SetNdivisions(numNewSlices);
	transmission4->GetYaxis()->SetNdivisions(numDets);
	transmission4->GetZaxis()->SetNdivisions(5);

	transmission4->GetYaxis()->SetLabelSize(0.0);
	transmission4->GetXaxis()->SetLabelSize(0.0);
	transmission4->GetZaxis()->SetLabelSize(0.07);
	transmission4->GetZaxis()->SetTitleOffset(1.0);

	transmission4->SetTitle("");
	transmission4->Draw("COLZ");
	transmission4->SetStats(kFALSE);
	transmission4->SetContour(99);

	c2->SetRightMargin(0.3);
	c2->cd();


	TCanvas *c3 = new TCanvas("c3","T15 MeV",0,0,528,378);

	transmission15->GetZaxis()->SetTitle("");
	transmission15->GetZaxis()->SetRangeUser(0.0,1.);

	transmission15->GetXaxis()->SetNdivisions(numNewSlices);
	transmission15->GetYaxis()->SetNdivisions(numDets);
	transmission15->GetZaxis()->SetNdivisions(5);

	transmission15->GetYaxis()->SetLabelSize(0.0);
	transmission15->GetXaxis()->SetLabelSize(0.0);
	transmission15->GetZaxis()->SetLabelSize(0.07);
	transmission15->GetZaxis()->SetTitleOffset(1.0);

	transmission15->SetTitle("");
	transmission15->Draw("COLZ");
	transmission15->SetStats(kFALSE);
	transmission15->SetContour(99);

	c3->SetRightMargin(0.3);
	c3->cd();


	TCanvas *c5 = new TCanvas("c5","Zeff",528,378);
	zeff->GetZaxis()->SetRangeUser(-.1,100);

	zeff->GetXaxis()->SetNdivisions(numNewSlices);
	zeff->GetYaxis()->SetNdivisions(numDets);
	zeff->GetZaxis()->SetNdivisions(5);

	zeff->GetZaxis()->SetTitle("Z_{eff}");
	zeff->GetZaxis()->SetTitleOffset(1.0);
	zeff->SetTitle("");
	zeff->Draw("COLZ");
	zeff->SetStats(kFALSE);
	zeff->SetContour(99);

	zeff->GetYaxis()->SetLabelSize(0.0);
	zeff->GetXaxis()->SetLabelSize(0.0);
	zeff->GetZaxis()->SetLabelSize(0.07);
	zeff->GetZaxis()->SetTitleSize(0.0);

	c5->cd();
	c5->SetRightMargin(0.3);

	c1->SaveAs(path+ "transmissionTotalBrem" + TString::Itoa(multiplier, 10) + "x.eps");
	c2->SaveAs(path+"transmissionBrem6" + TString::Itoa(multiplier, 10) + "x.eps");
	c3->SaveAs(path+"transmissionBrem9_6" + TString::Itoa(multiplier, 10) + "x.eps");
	c5->SaveAs(path+"zeff9_6" + TString::Itoa(multiplier, 10) + "x.eps");
}

Double_t * CreateEnergyAxis(TH1D* dummyHist)
{
	Int_t spectrumLength = dummyHist->GetNbinsX();
	Double_t* calibratedEAxis = new Double_t[spectrumLength]; 
	for (Int_t i = 0; i < spectrumLength; i++){
		Double_t xVal = dummyHist->GetBinCenter(i+1);
		calibratedEAxis[i] = 3.595E-5 * xVal * xVal + 3.198822E-2 * xVal + 0.39110786
		- 0.0159317504;
	}
	return calibratedEAxis;
}