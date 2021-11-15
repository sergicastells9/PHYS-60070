{
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
	
	
	
	
	
}