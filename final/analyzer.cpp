/*
	Author: Sergi Castells
*/

{
	// Extract data from ROOT file
	TFile* file = new TFile("data.root");
	
	// Set up data variables
	Double_t gamma1, gamma2, energy;
	Int_t detector;
	
	// Set up branches for reading
	t1->SetBranchAddress("g1", &gamma1);
	t1->SetBranchAddress("g2", &gamma2);
	t1->SetBranchAddress("det", &detector);
	t1->SetBranchAddress("ene", &energy);
	
	// Set up arrays of decay/angle information
	Double_t decays[6] = {1385, 1258, 976, 849, 409, 127}; // Possible gamma decay energies for 1358 keV nucleus
	Double_t angles[7] = {7, 22, 47, 67, 92, 127, 177}; // Detector angles
	
	// Set up histograms
	Int_t numBins = 100;
	TH1D* h0 = new TH1D("h0", "Detector 0", numBins, 13000, 15000);
	TH1D* h1 = new TH1D("h1", "Detector 1", numBins, 13000, 15000);
	TH1D* h2 = new TH1D("h2", "Detector 2", numBins, 13000, 15000);
	TH1D* h3 = new TH1D("h3", "Detector 3", numBins, 13000, 15000);
	TH1D* h4 = new TH1D("h4", "Detector 4", numBins, 13000, 15000);
	TH1D* h5 = new TH1D("h5", "Detector 5", numBins, 13000, 15000);
	TH1D* h6 = new TH1D("h6", "Detector 6", numBins, 13000, 15000);
	
	// Make hist vector for easy access and filling (Using a vector because range checking is nice)
	// There isn't a huge time difference than with using an array. I checked.
	std::vector<TH1D*> histograms = {h0, h1, h2, h3, h4, h5, h6};
	
	// Get number of events
	Int_t nEntries = t1->GetEntries();
	std::cout << "# of events: " << nEntries << std::endl;
	
	// Time filling histograms for my own sanity
	clock_t tStart = clock();
	clock_t tMiddle = tStart;
	
	// Loop over events
	for(Int_t i = 0; i < nEntries; i++) {
		t1->GetEntry(i);
		
		// Fill histograms
		for(Int_t j = 0; j < 6; j++) {
			// Check if allowed decay energy
			if((gamma1 > decays[j]-1 && gamma1 < decays[j]+1) || (gamma2 > decays[j]-1 && gamma2 < decays[j]+1)) {
				histograms.at(detector)->Fill(energy);
				break;
			}
		}
		
		// Check time per 1000 rows (it increases for some reason???)
		if(i%1000 < 0.001) {
			std::cout << "Processing row " << i;
			std::cout << ".\t Time taken for row: " << static_cast<Double_t>((clock() - tMiddle)/CLOCKS_PER_SEC);
			std::cout << "s" << std::endl;
			tMiddle = clock();
		}
	}
	
	// Set up TCanvas
	TCanvas* c1 = new TCanvas("c1", "Particle/Gamma Coincidences", 1200, 1200);
	c1->Divide(3,3);
	
	// Set up and draw histograms
	for(Int_t i = 0; i < 7; i ++) {
		// Set correct TPad
		c1->cd(i+1);
		
		// Rotate and format axis labels so they are easier to read
		Int_t nDiv = histograms.at(i)->GetNdivisions();
		for(Int_t j = 0; j < numBins; j++) {
			histograms.at(i)->GetXaxis()->ChangeLabel(j,70);
			//histograms.at(i)->GetXaxis()->SetLabelOffset(0.01); // this doesn't work?
		}
		
		// Set titles, units, axis formatting
		histograms.at(i)->GetXaxis()->SetTitle("Energy (keV)");
		//histograms.at(i)->GetXaxis()->SetTitleOffset(1.5); // this also doesn't work?
		histograms.at(i)->GetYaxis()->SetTitle("Counts");
		
		histograms.at(i)->Draw();
	}
	
	// Save histograms to file
	c1->SaveAs("coincidences.png");
	
}