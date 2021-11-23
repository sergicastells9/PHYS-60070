// Finds number and locations of peaks
Double_t* get_peaks(TH1F* hist, double xMin, double xMax) {
	// Sets range to xMin/xMax and creates TSpectrum instance
	hist->GetXaxis()->SetRangeUser(xMin, xMax);
	TSpectrum* s = new TSpectrum(30);
	
	// Saves number of peaks and locations
	Int_t nfound = s->Search(hist, 2, "", 0.0095);
	Double_t* xpeaks = s->GetPositionX();
	
	// Prints number of peaks and returns locations
	std::cout << "Found " << nfound << " peaks." << std::endl;
	return xpeaks;
}

// Main function
void week12_homework() {
	// Histogram and canvas setup. Divide in 3 pads stacked vertically
	TH1F* h1 = new TH1F("152 Eu", "152 Eu", 8192, 0, 8192);
	TCanvas* canvas = new TCanvas("canvas", "Canvas", 600, 900);
	canvas->Divide(1,3);
	
	// Access data file
	std::fstream fs("152Eu_data.dat");
	Float_t tmp;
	
	// Save data and fill histogram
	for(int i = 0; i < 8192; i++) {
		fs >> tmp;
		fs >> tmp;
		h1->SetBinContent(i, tmp);
	}
	
	// Set up histogram and draw
	canvas->cd(1);
	h1->GetXaxis()->SetTitle("Channels");
	h1->GetXaxis()->CenterTitle();
	h1->GetXaxis()->SetTitleSize(0.05);
	h1->GetYaxis()->SetTitle("Counts");
	h1->GetYaxis()->CenterTitle();
	h1->GetYaxis()->SetTitleSize(0.05);
	
	h1->Draw();
	
	// Call get_peaks and set up order array
	const int arraySize = 16;
	Double_t* xpeaks = get_peaks(h1, 0, 8192);
	int order[arraySize] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	
	// Sort order array
	TMath::Sort(arraySize, static_cast<const Double_t*>(xpeaks), order, false);
	
	// Set up various arrays for later
	Double_t sigma = 2;
	int min[arraySize], max[arraySize];
	Double_t mean[arraySize], x_error[arraySize], zero[arraySize];
	Double_t energy[arraySize] = {121.78, 244.7, 344.28, 367.79, 411.12, 443.97, 688.67, 778.9,
							879.38, 964.08, 1085.87, 1089.74, 1112.07, 1212.95, 1299.14, 1408.01};
	
	// Fit each peak and save mean/error
	for(int i = 0; i < arraySize; i++) {
		min[i] = xpeaks[order[i]] - 2*sigma;
		max[i] = xpeaks[order[i]] + 2*sigma;
		
		TF1* f1 = new TF1("f1", "gaus", min[i], max[i]);
		h1->Fit(f1, "QR0");
		mean[i] = f1->GetParameter(1);
		x_error[i] = (f1->GetParError(1));
		zero[i] = 0.01;
	}
	
	// TGraphError setup
	TGraphErrors* graph = new TGraphErrors(arraySize, mean, energy, x_error, zero);
	
	// Set up graph
	canvas->cd(2);
	graph->SetTitle("Energy vs Channel");
	graph->GetYaxis()->SetTitle("Energy (keV)");
	graph->GetYaxis()->CenterTitle();
	graph->GetYaxis()->SetTitleSize(0.05);
	graph->GetXaxis()->SetTitle("Channel");
	graph->GetXaxis()->CenterTitle();
	graph->GetXaxis()->SetTitleSize(0.05);
	graph->SetMinimum(0);
	
	// Draw and fit graph
	graph->Draw("A*");
	TF1* f2 = new TF1("f2", "pol2", 0, 8192);
	graph->Fit(f2);
	f2->SetNpx(1000);
	f2->SetLineStyle(kDashed);
	
	
	// Set up residuals and y_error array
	Double_t residuals[arraySize];
	Double_t y_error[arraySize];
	
	// Fill residuals and y_errors array
	for(int i = 0; i < arraySize; i++) {
		residuals[i] = energy[i] - f2->Eval(mean[i]);
		
		// propagate quadradtic and energy error
		y_error[i] = std::sqrt(std::pow(f2->GetParError(0),2) + std::pow(mean[i]*f2->GetParError(1),2)
							+ std::pow(std::pow(mean[i],2) * f2->GetParError(2),2) + std::pow(0.01,2));
	}
	
	// TGraphError setup
	TGraphErrors* res_graph = new TGraphErrors(arraySize, mean, residuals, x_error, y_error);
	
	// Set up graph
	canvas->cd(3);
	res_graph->SetTitle("Residuals");
	res_graph->GetYaxis()->SetTitle("E_{#gamma} - E_{fit}(keV)");
	res_graph->GetYaxis()->CenterTitle();
	res_graph->GetYaxis()->SetTitleSize(0.05);
	res_graph->GetXaxis()->SetTitle("Channel");
	res_graph->GetXaxis()->CenterTitle();
	res_graph->GetXaxis()->SetTitleSize(0.05);
	
	// Draw graph
	res_graph->Draw("A*");
	
	
	
}