{
  gStyle->SetPalette(53);
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetOptStat(kFALSE);
  TString path = "~/Dropbox/Grad School/PhD Research/G4/ANSIsimulations/CNR_Zeff/ReconImages/";
  Int_t demultiplier = 10;

  TFile* inputFileBrem = new TFile(path + "bremRatiosNS.root");
  TH2D* ratioBremOrig = (TH2D*)inputFileBrem->Get("bremRatioNStoss" + TString::Itoa(demultiplier,10));
  TH1D* crossLineXBremOrig = ratioBremOrig->ProjectionX("Brem. X",71,71);
  TH1D* crossLineYBremOrig = ratioBremOrig->ProjectionY("Brem. Y",82,82);

  TFile* inputFileLenr = new TFile(path + "lenrRatiosNS.root");
  TH2D* ratioLenrOrig = (TH2D*)inputFileLenr->Get("lenrRatioNStoss" + TString::Itoa(demultiplier,10));
  TH1D* crossLineXLenrOrig = ratioLenrOrig->ProjectionX("LENR X",71,71);
  TH1D* crossLineYLenrOrig = ratioLenrOrig->ProjectionY("LENR Y",82,82);

  Int_t nBinsXProj = crossLineXLenrOrig->GetNbinsX();
  Double_t maxBinEdgeX = crossLineXLenrOrig->GetBinCenter(nBinsXProj-1) + crossLineXLenrOrig->GetBinWidth(nBinsXProj-1)/2.;
  TH1D* dummyHistX = new TH1D("dummyX", "", nBinsXProj, 0, maxBinEdgeX);
  Int_t i = 0;
  while (dummyHistX->GetBinCenter(i+1) < 54){
    dummyHistX->SetBinContent(i+1, 0);
    i++;
  }
  while (dummyHistX->GetBinCenter(i+1) < 70){
    dummyHistX->SetBinContent(i+1, 2.0);
    i++;
  }
  while (dummyHistX->GetBinCenter(i+1) < 137.5){
    dummyHistX->SetBinContent(i+1, 0);
    i++;
  }
  while (dummyHistX->GetBinCenter(i+1) < 153.5){
    dummyHistX->SetBinContent(i+1, 2.0);
    i++;
  }
  for (Int_t iter = i; iter < nBinsXProj; iter++){
    dummyHistX->SetBinContent(iter+1,0);
  }

  for (Int_t i = 0; i < 4; i++){
    crossLineXLenrOrig->SetBinContent(i+1, 0);
    crossLineXBremOrig->SetBinContent(i+1, 0);
  }
  for (Int_t i = 202; i < nBinsXProj; i++){
    crossLineXLenrOrig->SetBinContent(i+1, 0);
    crossLineXBremOrig->SetBinContent(i+1, 0);
  }

  Int_t nBinsYProj = crossLineYLenrOrig->GetNbinsX();
  Double_t maxBinEdgeY = crossLineYLenrOrig->GetBinCenter(nBinsYProj-1) + crossLineYLenrOrig->GetBinWidth(nBinsYProj-1)/2.;
  TH1D* dummyHistY = new TH1D("dummyY", "", nBinsYProj, 0, maxBinEdgeY);
  i = 0;
  while (dummyHistY->GetBinCenter(i+1) < 44){
    dummyHistY->SetBinContent(i+1, 0);
    i++;
  }
  while (dummyHistY->GetBinCenter(i+1) < 52.5){
    dummyHistY->SetBinContent(i+1, 2.0);
    i++;
  }
  while (dummyHistY->GetBinCenter(i+1) < 87.5){
    dummyHistY->SetBinContent(i+1, 0);
    i++;
  }
  while (dummyHistY->GetBinCenter(i+1) < 96.5){
    dummyHistY->SetBinContent(i+1, 2.0);
    i++;
  }
  for (Int_t iter = i; iter < nBinsYProj; iter++){
    dummyHistY->SetBinContent(iter+1,0);
  }


  TCanvas *c1 = new TCanvas("c1","X",0,0,600,600);
  c1->SetRightMargin(0.18);
  c1->SetBottomMargin(0.18);
  c1->SetLeftMargin(0.02);
  c1->SetTopMargin(0.02);
  
  dummyHistX->GetXaxis()->SetTitle("Pixel");
  dummyHistX->GetXaxis()->SetTitleSize(0.08);
  dummyHistX->GetXaxis()->SetLabelSize(0.07);
  dummyHistX->GetXaxis()->CenterTitle();
  dummyHistX->GetXaxis()->SetTitleOffset(1.1);
  dummyHistX->GetXaxis()->SetDecimals(kTRUE);
  dummyHistX->GetXaxis()->SetRangeUser(4,202);
  dummyHistX->GetXaxis()->SetNdivisions(5);

  dummyHistX->GetYaxis()->SetTitle("R-value");
  dummyHistX->GetYaxis()->SetTitleSize(0.08);
  dummyHistX->GetYaxis()->SetLabelSize(0.07);
  dummyHistX->GetYaxis()->SetDecimals(kTRUE);
  dummyHistX->GetYaxis()->CenterTitle();
  dummyHistX->GetYaxis()->SetTitleOffset(1.1);
  dummyHistX->GetYaxis()->SetRangeUser(0.01,2.0);
  dummyHistX->GetYaxis()->SetNdivisions(5);

  dummyHistX->SetLineColor(kGray);
  //dummyHistX->DrawCopy("hist same"); 
  dummyHistX->SetLineWidth(0);
  dummyHistX->SetFillStyle(3001);
  dummyHistX->SetFillColorAlpha(kGray, 0.3);
  //dummyHistX->SetMarkerColor(kGray, 0.3);
  dummyHistX->Draw("Y+");

  crossLineXLenrOrig->SetLineColor(kRed+1);
  crossLineXLenrOrig->DrawCopy("hist same");
  crossLineXLenrOrig->SetLineWidth(2);
  crossLineXLenrOrig->SetFillStyle(3001);
  crossLineXLenrOrig->SetFillColorAlpha(kRed+1, 0.3);
  crossLineXLenrOrig->SetMarkerColor(kRed+1);
  crossLineXLenrOrig->Draw("same e2");

  crossLineXBremOrig->SetLineColor(kBlue+1);
  crossLineXBremOrig->DrawCopy("hist same"); 
  crossLineXBremOrig->SetLineWidth(2);
  crossLineXBremOrig->SetFillStyle(3001);
  crossLineXBremOrig->SetFillColorAlpha(kBlue+1, 0.3);
  crossLineXBremOrig->SetMarkerColor(kBlue+1);
  crossLineXBremOrig->Draw("e2 same");


    TLatex * pbLabel = new TLatex(54, 0.2, "Pb");
    pbLabel->SetTextColorAlpha(kBlack, 1);
    pbLabel->SetTextFont(42);
    pbLabel->SetTextSize(0.07);
    pbLabel->Draw();

    TLatex * feLabel = new TLatex(138, 0.2, "Fe");
    feLabel->SetTextColorAlpha(kBlack, 1);
    feLabel->SetTextFont(42);
    feLabel->SetTextSize(0.07);
    feLabel->Draw();

  TLegend * leg1 = new TLegend(0.05, 0.8, 0.25, 0.95);
  leg1->SetBorderSize(0);
  leg1->SetTextFont(42);
  leg1->AddEntry(crossLineXLenrOrig, "LENR");
  leg1->AddEntry(crossLineXBremOrig, "Brem.");
  leg1->Draw();
  gStyle->SetOptTitle(kFALSE);

  TCanvas *c2 = new TCanvas("c2","Y",0,0,600,600);
  c2->SetRightMargin(0.18);
  c2->SetBottomMargin(0.18);
  c2->SetLeftMargin(0.02);
  c2->SetTopMargin(0.02);
  
  dummyHistY->GetXaxis()->SetTitle("Pixel");
  dummyHistY->GetXaxis()->SetTitleSize(0.08);
  dummyHistY->GetXaxis()->SetLabelSize(0.07);
  dummyHistY->GetXaxis()->CenterTitle();
  dummyHistY->GetXaxis()->SetTitleOffset(1.1);
  dummyHistY->GetXaxis()->SetDecimals(kTRUE);
  dummyHistY->GetXaxis()->SetRangeUser(9,131);

  dummyHistY->GetYaxis()->SetTitle("R-value");
  dummyHistY->GetYaxis()->SetTitleSize(0.08);
  dummyHistY->GetYaxis()->SetLabelSize(0.07);
  dummyHistY->GetYaxis()->SetDecimals(kTRUE);
  dummyHistY->GetYaxis()->CenterTitle();
  dummyHistY->GetYaxis()->SetTitleOffset(1.1);
  dummyHistY->GetYaxis()->SetRangeUser(0.01,2.0);
  dummyHistY->GetYaxis()->SetNdivisions(5);

  dummyHistY->SetLineColor(kGray);
  //dummyHistY->DrawCopy("hist same"); 
  dummyHistY->SetLineWidth(0);
  dummyHistY->SetFillStyle(3001);
  dummyHistY->SetFillColorAlpha(kGray, 0.3);
  //dummyHistY->SetMarkerColor(kGray, 0.3);
  dummyHistY->Draw("Y+");

  crossLineYLenrOrig->SetLineColor(kRed+1);
  crossLineYLenrOrig->DrawCopy("hist same");
  crossLineYLenrOrig->SetLineWidth(2);
  crossLineYLenrOrig->SetFillStyle(3001);
  crossLineYLenrOrig->SetFillColorAlpha(kRed+1, 0.3);
  crossLineYLenrOrig->SetMarkerColor(kRed+1);
  crossLineYLenrOrig->Draw("same e2");

  crossLineYBremOrig->SetLineColor(kBlue+1);
  crossLineYBremOrig->DrawCopy("hist same"); 
  crossLineYBremOrig->SetLineWidth(2);
  crossLineYBremOrig->SetFillStyle(3001);
  crossLineYBremOrig->SetFillColorAlpha(kBlue+1, 0.3);
  crossLineYBremOrig->SetMarkerColor(kBlue+1);
  crossLineYBremOrig->Draw("e2 same");

    TLatex * wLabel = new TLatex(44, 0.2, "W");
    wLabel->SetTextColorAlpha(kBlack, 1);
    wLabel->SetTextFont(42);
    wLabel->SetTextSize(0.07);
    wLabel->Draw();

    TLatex * cLabel = new TLatex(89, 0.2, "C");
    cLabel->SetTextColorAlpha(kBlack, 1);
    cLabel->SetTextFont(42);
    cLabel->SetTextSize(0.07);
    cLabel->Draw();

  TLegend * leg2 = new TLegend(0.05, 0.8, 0.25, 0.95);
  leg2->SetBorderSize(0);
  leg2->SetTextFont(42);
  leg2->AddEntry(crossLineYLenrOrig, "LENR");
  leg2->AddEntry(crossLineYBremOrig, "Brem.");
  leg2->Draw();
  gStyle->SetOptTitle(kFALSE);
}