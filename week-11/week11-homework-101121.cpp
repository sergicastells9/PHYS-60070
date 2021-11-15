// Author: Sergi Castells

{
	// Problem 1.1
	/*
	// Set up functions
	TF1 *fPeak1 = new TF1("fPeak1", "30*TMath::Gaus(x,5,1)", 0, 20);
	TF1 *fPeak2 = new TF1("fPeak2", "20*TMath::Gaus(x,15,1)", 0, 20);
	TF1 *fBgrd = new TF1("fBgrd", "-2*x + 30", 0, 20);
	TF1 *fSum = new TF1("fSum", "fPeak1+fPeak2+fBgrd", 0, 20);
	
	
	// Set up histogram
	TH1D* hist = new TH1D("hist", "fSum Hist", 200, 0, 20);
	hist->GetYaxis()->SetRangeUser(0, 55);
	
	// Fill histogram bins
	for(float i = 0; i < 200; i++) {
		double center = hist->GetBinCenter(i);
		hist->Fill(center, fSum->Eval(center));
	}
	
	// Set up and draw on canvas
	TCanvas *canvas = new TCanvas("canvas", "Canvas", 500, 500);
	hist->Draw("hist");
	
	canvas->SaveAs("hist_plot.png");
	*/
	
	
	
	// Problem 2.1
	// Set up h1 and h2
	TH1D* h1 = new TH1D("h1", "h1", 100, 0, 10);
	TH1D* h2 = new TH1D("h2", "h2", 100, 0, 10);
	
	// Fill h1 and h2
	for(int i = 0; i < 1000; i++) {
		h1->Fill(gRandom->Gaus(5,1));
		for(int j = 0; j < 10; j++) {
			h2->Fill(gRandom->Uniform(10));
		}
	}
	
	// Set up hSignal = h1 + h2
	TH1D* hSignal = dynamic_cast<TH1D*>(h1->Clone("hSignal"));
	hSignal->Add(h2);
	
	// Set up hBgrd
	TH1D* hBgrd = new TH1D("hBgrd", "hBgrd", 100, 0, 10);
	
	// Fill hBgrd
	for(int i = 0; i < 100000; i++) {
		hBgrd->Fill(gRandom->Uniform(10));
	}
	
	// Normalize hBgrd to integral = 1000
	hBgrd->Scale(1000.0/hBgrd->Integral(0,10));
	
	// Set up hDiff and subtract hBgrd from hSignal
	TH1D* hDiff = dynamic_cast<TH1D*>(hSignal->Clone("hDiff"));
	hDiff->Add(hBgrd, -1);
	
	// Set up canvas and draw with errors
	TCanvas *canvas = new TCanvas("canvas", "Canvas", 500, 500);
	hDiff->Draw("e");
	
	cout << hDiff->Integral(0,10) << endl;
	
	
}