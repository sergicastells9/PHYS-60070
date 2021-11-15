// Author: Sergi Castells

{
	// Make Gaussian histograms
	TH1D* hGauss1 = new TH1D("hGauss1", "hGauss1", 1000, 0, 100);
	TH1D* hGauss2 = new TH1D("hGauss2", "hGauss2", 1000, 0, 100);
	TH1D* hGauss3 = new TH1D("hGauss3", "hGauss3", 1000, 0, 100);
	
	// Fill histograms
	for(int i = 0; i < 1000; i++) {
		// Area = 100 makes it too big to see background
		hGauss1->Fill(gRandom->Gaus(20, 1));
		hGauss2->Fill(gRandom->Gaus(50, 1));
		hGauss3->Fill(gRandom->Gaus(80, 1));
	}
	
	// Make background function
	TF1* fBgrd = new TF1("fBgrd", "[0]*std::pow(x,2) + [1]*x + [2]", 0, 100);
	fBgrd->SetParameter(0, -0.01);
	fBgrd->SetParameter(1, 1);
	fBgrd->SetParameter(2, 9);
	
	// Combine histograms
	TH1D* hAll = new TH1D("hAll", "hAll", 1000, 0, 100);
	hAll->Add(fBgrd);
	hAll->Add(hGauss1);
	hAll->Add(hGauss2);
	hAll->Add(hGauss3);
	
	// Make canvas and split into 4 pads
	TCanvas* canvas = new TCanvas("canvas", "Canvas", 1000, 1000);
	canvas->Divide(2,2);
	
	
	/////////////////
	// PAD 1 SETUP //
	/////////////////
	// Switch to pad 1
	canvas->cd(1);
	TH1D* h1 = new TH1D("Hist 1", "ShowBackground Fit", 1000, 0, 100);
	h1->Add(hAll);
	h1->Draw();
	
	// Fit to background
	TH1D* hBgrd = dynamic_cast<TH1D*>(hAll->ShowBackground(20, "same"));
	
	// Remove background
	TH1D* hDiff1 = new TH1D("hDiff1", "hDiff1", 1000, 0, 100);
	hDiff1->Add(h1, hBgrd, 1, -1);
	
	/////////////////
	// PAD 2 SETUP //
	/////////////////
	// Switch to pad 2
	canvas->cd(2);
	TH1D* h2 = new TH1D("Hist 2", "Quadractic with Peaks Fit", 1000, 0, 100);
	h2->Add(hAll);
	h2->Draw();
	
	// Define fitting function and fit to data
	TF1* f1_2 = new TF1("fitH2", "pol2", 0, 100);
	h2->Fit("fitH2", "RQ");
	
	// Remove background
	TH1D* hDiff2 = new TH1D("hDiff2", "hDiff2", 1000, 0, 100);
	hDiff2->Add(h2);
	hDiff2->Add(f1_2, -1);
	
	/////////////////
	// PAD 3 SETUP //
	/////////////////
	// Switch to pad 3
	canvas->cd(3);
	TH1D* h3 = new TH1D("Hist 3", "Quadractic without Peaks Fit", 1000, 0, 100);
	h3->Add(hAll);
	h3->Draw();
	
	// Define fitting functions
	TF1* f1_3 = new TF1("fit1", "pol2", 0, 15);
	TF1* f2_3 = new TF1("fit2", "pol2", 25, 45);
	TF1* f3_3 = new TF1("fit3", "pol2", 55, 75);
	TF1* f4_3 = new TF1("fit4", "pol2", 85, 100);
	
	// Fit functions to data
	h3->Fit("fit1", "QR0");
	h3->Fit("fit2", "QR0+");
	h3->Fit("fit3", "QR0+");
	h3->Fit("fit4", "QR0+");
	
	// Average parameters from fits
	Double_t par[3];
	par[0] = (f1_3->GetParameter(0) + f2_3->GetParameter(0) + f3_3->GetParameter(0) + f4_3->GetParameter(0))/4;
	par[1] = (f1_3->GetParameter(1) + f2_3->GetParameter(1) + f3_3->GetParameter(1) + f4_3->GetParameter(1))/4;
	par[2] = (f1_3->GetParameter(2) + f2_3->GetParameter(2) + f3_3->GetParameter(2) + f4_3->GetParameter(2))/4;
	
	// Plot quadratic without peaks
	TF1* fTotal = new TF1("fTotal", "pol2", 0, 100);
	fTotal->SetParameter(0, par[0]);
	fTotal->SetParameter(1, par[1]);
	fTotal->SetParameter(2, par[2]);
	fTotal->Draw("same");
	
	// Remove background
	TH1D* hDiff3 = new TH1D("hDiff3", "hDiff3", 1000, 0, 100);
	hDiff3->Add(h3);
	hDiff3->Add(fTotal, -1);
	
	/////////////////
	// PAD 4 SETUP //
	/////////////////
	// Switch to pad 4
	canvas->cd(4);
	
	// Set up THStack
	THStack* h4 = new THStack("", "Signals");
	
	// Set style/colors for histograms
	hDiff1->SetLineColor(kBlack);
	hDiff2->SetLineColor(kAzure);
	hDiff3->SetLineColor(kRed);
	
	// Add to THStack
	h4->Add(hDiff1);
	h4->Add(hDiff2);
	h4->Add(hDiff3);
	
	// Draw THStack
	h4->Draw("nostack");
	
	// TLegend setup and draw
	TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
	legend->SetHeader("LEGEND", "C");
	legend->AddEntry(hDiff1, "hDiff1", "l");
	legend->AddEntry(hDiff2, "hDiff2", "l");
	legend->AddEntry(hDiff3, "hDiff3", "l");
	legend->Draw("same");
	
	// Red plot looks the best so the 3rd method probably works the best here.
	
	// Save plots to file
	canvas->SaveAs("plots.png");
	
}