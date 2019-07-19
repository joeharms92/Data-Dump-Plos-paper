{
  gStyle->SetPalette(53);
  TString path = "~/G4/ANSIsimulations/CNR_Zeff/ReconImages/";
  TString source = "lenr";
  Int_t demultiplier = 5;

  TFile* inputFile = new TFile(path + "imgs_" + source + "RawDataToss"+TString::Itoa(demultiplier,10)+".root");
  TH2D* ratio = (TH2D*)inputFile->Get("Ratio");
  TH2D* transmissionLow, *transmissionHigh;
  if (source == "brem") transmissionLow = (TH2D*)inputFile->Get("tLow");
  else transmissionLow = (TH2D*)inputFile->Get("T4");
  if (source == "brem") transmissionHigh = (TH2D*)inputFile->Get("tHigh");
  else transmissionHigh = (TH2D*)inputFile->Get("T15");

  double levels[99];
  levels[0] = 0;
  levels[1] = 0.4;
  for (int i = 1; i < 98; i++){
    levels[i+1] = ((1.4-0.4)/97.)*i+0.4;
  }

  TCanvas *c2 = new TCanvas("c2","tLOW",0,0,700,600);
  //TCanvas *c2 = new TCanvas("c2","RatioMap",0,0,600,600);
  c2->SetLeftMargin(0.01);
  c2->SetBottomMargin(0.02);
  c2->SetTopMargin(0.02);
  //c2->SetRightMargin(0.01);
  c2->SetRightMargin(0.16);

  transmissionLow->GetXaxis()->SetLabelSize(0.0);
  transmissionLow->GetXaxis()->SetNdivisions(216);
  transmissionLow->GetXaxis()->SetTickLength(0.00);

  transmissionLow->GetYaxis()->SetNdivisions(140);
  transmissionLow->GetYaxis()->SetLabelSize(0.0);
  transmissionLow->GetYaxis()->SetTickLength(0.00);

  transmissionLow->GetZaxis()->SetLabelSize(0.04);
  transmissionLow->GetZaxis()->SetTitleOffset(1.1);
  transmissionLow->GetZaxis()->SetTitleSize(0.05);
  transmissionLow->GetZaxis()->SetNdivisions(7);
  transmissionLow->GetZaxis()->SetTitle("Transmitted Fraction");
  transmissionLow->GetZaxis()->SetRangeUser(0.0,1.);
  transmissionLow->GetZaxis()->SetDecimals(kTRUE);
  transmissionLow->GetZaxis()->CenterTitle();

  /*transmissionLow->GetZaxis()->SetTitle("");
  transmissionLow->GetZaxis()->SetRangeUser(0.0,1);
  transmissionLow->GetZaxis()->SetNdivisions(7);
  transmissionLow->GetZaxis()->SetLabelSize(0.00);
  transmissionLow->GetZaxis()->SetTitleSize(0.00);
  transmissionLow->GetZaxis()->SetTitleOffset(0);*/

  transmissionLow->SetTitle("");
  transmissionLow->Draw("COLZ");
  //transmissionLow->Draw("COL");
  transmissionLow->SetStats(kFALSE);
  transmissionLow->SetContour(99);
  c2->cd();

  TCanvas *c3 = new TCanvas("c3","tHIGH",0,0,700,600);
  //TCanvas *c3 = new TCanvas("c3","RatioMap",0,0,600,600);
  c3->SetLeftMargin(0.01);
  c3->SetBottomMargin(0.02);
  c3->SetTopMargin(0.02);
  //c3->SetRightMargin(0.01);
  c3->SetRightMargin(0.16);

  transmissionHigh->GetXaxis()->SetLabelSize(0.0);
  transmissionHigh->GetXaxis()->SetNdivisions(216);
  transmissionHigh->GetXaxis()->SetTickLength(0.00);

  transmissionHigh->GetYaxis()->SetNdivisions(140);
  transmissionHigh->GetYaxis()->SetLabelSize(0.0);
  transmissionHigh->GetYaxis()->SetTickLength(0.00);

  transmissionHigh->GetZaxis()->SetLabelSize(0.04);
  transmissionHigh->GetZaxis()->SetTitleOffset(1.1);
  transmissionHigh->GetZaxis()->SetTitleSize(0.05);
  transmissionHigh->GetZaxis()->SetNdivisions(7);
  transmissionHigh->GetZaxis()->SetTitle("Transmitted Fraction");
  transmissionHigh->GetZaxis()->SetRangeUser(0.0,1.);
  transmissionHigh->GetZaxis()->SetDecimals(kTRUE);
  transmissionHigh->GetZaxis()->CenterTitle();

  /*transmissionHigh->GetZaxis()->SetTitle("");
  transmissionHigh->GetZaxis()->SetRangeUser(0.0,1);
  transmissionHigh->GetZaxis()->SetNdivisions(7);
  transmissionHigh->GetZaxis()->SetLabelSize(0.00);
  transmissionHigh->GetZaxis()->SetTitleSize(0.00);
  transmissionHigh->GetZaxis()->SetTitleOffset(0);*/

  transmissionHigh->SetTitle("");
  transmissionHigh->Draw("COLZ");
  //transmissionHigh->Draw("COL");
  transmissionHigh->SetStats(kFALSE);
  transmissionHigh->SetContour(99);
  c3->cd();


  TCanvas *c4 = new TCanvas("c4","RatioMap",0,0,700,600);
  //TCanvas *c4 = new TCanvas("c4","RatioMap",0,0,600,600);
  c4->SetLeftMargin(0.01);
  c4->SetBottomMargin(0.02);
  c4->SetTopMargin(0.02);
  //c4->SetRightMargin(0.01);
  c4->SetRightMargin(0.16);

  ratio->GetXaxis()->SetNdivisions(216);
  ratio->GetXaxis()->SetLabelSize(0.0);

  ratio->GetYaxis()->SetNdivisions(140);
  ratio->GetYaxis()->SetLabelSize(0.0);

  ratio->GetZaxis()->SetTitle("R-value");
  ratio->GetZaxis()->SetRangeUser(0.0,1.4);
  ratio->GetZaxis()->SetNdivisions(7);
  ratio->GetZaxis()->SetLabelSize(0.04);
  ratio->GetZaxis()->SetTitleSize(0.05);
  ratio->GetZaxis()->SetTitleOffset(1.1);
  ratio->GetZaxis()->SetDecimals(kTRUE);
  ratio->GetZaxis()->CenterTitle();

  /*ratio->GetZaxis()->SetTitle("");
  ratio->GetZaxis()->SetRangeUser(0.0,1.4);
  ratio->GetZaxis()->SetNdivisions(7);
  ratio->GetZaxis()->SetLabelSize(0.00);
  ratio->GetZaxis()->SetTitleSize(0.00);
  ratio->GetZaxis()->SetTitleOffset(0);*/

  ratio->SetTitle("");
  ratio->Draw("COLZ");
  //ratio->Draw("COL");
  ratio->SetStats(kFALSE);
  ratio->SetContour(99,levels);

  c4->cd();

  c2->SaveAs(path + source + "TLowToss"+TString::Itoa(demultiplier,10)+".eps");
  c3->SaveAs(path + source + "THighToss"+TString::Itoa(demultiplier,10)+".eps");
  c4->SaveAs(path + source + "RatioToss"+TString::Itoa(demultiplier,10)+".eps");
}