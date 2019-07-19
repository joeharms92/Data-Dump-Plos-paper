{

	TCanvas *c1 = new TCanvas("c1","Beam Comparison",0,0,800,600);
	c1->SetLeftMargin(0.12);
	c1->SetBottomMargin(0.12);
  c1->SetRightMargin(0.02);
	//c1->SetLogy();
	gStyle->SetOptStat(0);

	gStyle->SetBarWidth(0.02);

	TGraph * lenr = new TGraph("lenrPostSteelSpec2.txt");
	lenr->SetLineWidth(2);
	lenr->SetLineColor(kBlue+2);
	lenr->SetMarkerStyle(kFullCircle);
	lenr->SetMarkerSize(0.1);
	lenr->SetFillStyle(1);
	lenr->SetFillColor(0);
	lenr->SetName("LENR");
	lenr->SetTitle("");
	lenr->Draw("a b");

	TGraph * brem6 = new TGraph("brem6PostSteelSpec2.txt");
	brem6->SetLineWidth(2);
	brem6->SetLineColor(kGreen + 1);
	brem6->SetFillStyle(0);
	brem6->SetFillColor(0);
	brem6->SetMarkerSize(0);
	brem6->SetTitle("Brem. 6 MV");
	brem6->Draw("same");

	TGraph * brem9 = new TGraph("brem9PostSteelSpec2.txt");
	brem9->SetLineWidth(2);
	brem9->SetLineColor(kRed + 1);
	brem9->SetFillStyle(0);
	brem9->SetFillColor(0);
	brem9->SetMarkerSize(0);
	brem9->SetTitle("Brem. 9 MV");
	brem9->Draw("same");

  lenr->GetXaxis()->SetTitle("Energy (MeV)");
  lenr->GetXaxis()->CenterTitle();
  lenr->GetXaxis()->SetLabelSize(.04);
  lenr->GetXaxis()->SetTitleSize(.05);
  lenr->GetXaxis()->SetTitleOffset(1.0);
  lenr->GetXaxis()->SetRangeUser(0., 16);

  lenr->GetYaxis()->SetTitle("Rel. Probability");
  lenr->GetYaxis()->CenterTitle();
  lenr->GetYaxis()->SetLabelSize(.04);
  lenr->GetYaxis()->SetTitleSize(.05);
  lenr->GetYaxis()->SetTitleOffset(0.9);
  lenr->GetYaxis()->SetDecimals(kTRUE);
  lenr->GetYaxis()->SetRangeUser(0.01, 1.1);
  //lenr->GetYaxis()->SetRangeUser(5E-9,0.0014);

  TLegend * leg = c1->BuildLegend(0.7, 0.67, 0.95, 0.89);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  gStyle->SetOptTitle(kFALSE);

TCanvas *c2 = new TCanvas("c2","Beam Comparison2",0,0,800,600);
  c2->SetLeftMargin(0.12);
  c2->SetBottomMargin(0.12);
  c2->SetRightMargin(0.02);
  //c2->SetLogy();
  gStyle->SetOptStat(0);


TGraph * mps9 = new TGraph("mps9_10PostSteelSpec2.txt");
mps9->SetLineWidth(2);
mps9->SetLineColor(kGreen+1);
mps9->SetMarkerSize(0);
mps9->SetFillStyle(0);
mps9->SetFillColor(0);
mps9->SetName("MPS 9 MeV");
mps9->SetTitle("");
mps9->Draw("");

TGraph * mps6 = new TGraph("mps6_10PostSteelSpec2.txt");
mps6->SetLineWidth(2);
mps6->SetLineColor(kBlue+1);
mps6->SetFillStyle(0);
mps6->SetFillColor(0);
mps6->SetMarkerSize(0);
mps6->SetTitle("MPS 6 MeV");
mps6->Draw("same");

TGraph * mps3 = new TGraph("mps3_10PostSteelSpec2.txt");
mps3->SetLineWidth(2);
mps3->SetLineColor(kRed + 1);
mps3->SetFillStyle(0);
mps3->SetFillColor(0);
mps3->SetMarkerSize(0);
mps3->SetTitle("MPS 3 MeV");
mps3->Draw("same");

mps9->GetXaxis()->SetTitle("Energy (MeV)");
mps9->GetXaxis()->CenterTitle();
mps9->GetXaxis()->SetLabelSize(.04);
mps9->GetXaxis()->SetTitleSize(.05);
mps9->GetXaxis()->SetTitleOffset(1.0);
mps9->GetXaxis()->SetRangeUser(0., 16);

mps9->GetYaxis()->SetTitle("Rel. Probability");
mps9->GetYaxis()->CenterTitle();
mps9->GetYaxis()->SetLabelSize(.04);
mps9->GetYaxis()->SetTitleSize(.05);
mps9->GetYaxis()->SetTitleOffset(1.0);
mps9->GetYaxis()->SetDecimals(kTRUE);
mps9->GetYaxis()->SetRangeUser(0.01, 1.1);
//mps9->GetYaxis()->SetRangeUser(5E-9,0.0014);

gStyle->SetOptTitle(kFALSE);
  TLegend* legend = new TLegend(0.7, 0.67, 0.95, 0.89);
  legend->SetBorderSize(0);
  legend -> AddEntry(mps3,"MPS 3 MeV", "l");
  legend -> AddEntry(mps6,"MPS 6 MeV", "l");
  legend -> AddEntry(mps9,"MPS 9 MeV", "l");
  legend -> Draw();

}