/*
	Author: Sergi Castells
*/

{
	// Extract data from ROOT file
	TFile* file = new TFile("data.root");
	
	TTree* tree = dynamic_cast<TTree*>(file->Get("t1"));
	
	// Set up data variables
	Double_t gamma1, gamma2, energy;
	Int_t detector;
	Double_t TGraphData[7];
	
	// Set up branches for reading
	t1->SetBranchAddress("g1", &gamma1);
	t1->SetBranchAddress("g2", &gamma2);
	t1->SetBranchAddress("det", &detector);
	t1->SetBranchAddress("ene", &energy);
	
	// Set up arrays of decay/angle information
	Double_t decays[6] = {1385, 1258, 976, 849, 409, 127}; // Possible gamma decay energies for 1358 keV nucleus
	Double_t angles[7] = {7, 22, 47, 67, 92, 127, 177}; // Detector angles
	Double_t x_errors[7]; // Detectors span 5 degrees each
	Double_t y_errors[7]; // 1/sqrt(N)
	
	// Set up histograms
	Int_t numBins = 100;
	Int_t x_min = 13000;
	Int_t x_max = 15000;
	TH1D* h0 = new TH1D("h0", "Detector 0", numBins, x_min, x_max);
	TH1D* h1 = new TH1D("h1", "Detector 1", numBins, x_min, x_max);
	TH1D* h2 = new TH1D("h2", "Detector 2", numBins, x_min, x_max);
	TH1D* h3 = new TH1D("h3", "Detector 3", numBins, x_min, x_max);
	TH1D* h4 = new TH1D("h4", "Detector 4", numBins, x_min, x_max);
	TH1D* h5 = new TH1D("h5", "Detector 5", numBins, x_min, x_max);
	TH1D* h6 = new TH1D("h6", "Detector 6", numBins, x_min, x_max);
	
	// Make hist vector for easy access and filling (Using a vector because range checking is nice)
	// There isn't a huge time difference than with using an array. I checked.
	std::vector<TH1D*> histograms = {h0, h1, h2, h3, h4, h5, h6};
	
	// Get number of events
	Int_t nEntries = t1->GetEntries();
	Int_t doubleGammas = 0;
	std::cout << "# of events: " << nEntries << std::endl;
	
	// Time filling histograms for my own sanity
	clock_t tStart = clock();
	clock_t tMiddle = tStart;
	
	// Loop over events
	for(Int_t i = 0; i < nEntries; i++) {
		t1->GetEntry(i);
		
		// Check for double gammas
		if(gamma1 > 0.001 && gamma2 > 0.001) {
			doubleGammas += 1;
		}
		
		// No need to check for double counting since there are no double gamma events
		if(std::find(decays.begin(), decays.end(), gamma1) || std::find(decays.begin(), decays.end(), gamma2)) {
			histograms.at(detector)->Fill(energy);
		}
		
		// Check time per 1000 rows (it increases for some reason???)
		if(i%1000 < 0.001) {
			std::cout << "Processing row " << i;
			std::cout << ".\t Time taken for row: " << static_cast<Double_t>((clock() - tMiddle)/CLOCKS_PER_SEC);
			std::cout << "s" << std::endl;
			tMiddle = clock();
		}
	}
	
	// Print # of double gamma events
	std::cout << "# of double gamma events: " << doubleGammas << std::endl;
	
	// Set up TCanvas
	TCanvas* c1 = new TCanvas("c1", "Particle/Gamma Coincidences", 1200, 1200);
	c1->Divide(3,3);
	TCanvas* c2 = new TCanvas("c2", "Angular Distribution", 800, 800);
	
	// Set up and draw histograms
	for(Int_t i = 0; i < 7; i ++) {
		// Set correct TPad
		c1->cd(i+1);
		
		// Set titles, units, axis formatting
		histograms.at(i)->GetXaxis()->SetTitle("Energy (keV)");
		histograms.at(i)->GetXaxis()->CenterTitle();
		histograms.at(i)->GetYaxis()->SetTitle("Counts");
		histograms.at(i)->GetYaxis()->CenterTitle();
		
		histograms.at(i)->Draw();
		
		// Get TGraph data
		TGraphData[i] = histograms.at(i)->GetEntries(); // check over/underflow
		
		// Fill error arrays
		x_errors[i] = 2.5;
		y_errors[i] = 100/sqrt(TGraphData[i]); // scaled up errors so fitting actually works
	}
	
	// Set up angular distribution graph
	TGraphErrors* g0 = new TGraphErrors(7, angles, TGraphData, x_errors, y_errors);
	g0->SetNameTitle("g0", "Angular Distribution");
	g0->GetXaxis()->SetTitle("Angle (degrees)");
	g0->GetXaxis()->CenterTitle();
	g0->GetYaxis()->SetTitle("Counts");
	g0->GetYaxis()->CenterTitle();
	
	// Set TCanvas for drawing angular distribution plot
	c2->cd();
	g0->Draw("A*");
	
	// Set up TF1 for fitting TGraph
	TF1* f1 = new TF1("f1", "[0]*TMath::Cos((3.14*x/180)*[1] + [2]) + [3]", 0, 180);
	f1->SetParameters(1,1,1,1500);
	g0->Fit(f1);
	
	// Save plots to file
	c1->SaveAs("coincidences.png");
	c2->SaveAs("angular_dist.png");
}