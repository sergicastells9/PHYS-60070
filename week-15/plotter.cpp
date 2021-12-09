/*
	Author: Sergi Castells
	Plotter macro
*/

{
	// Read file
	TFile* file = new TFile("data.root");
	
	// Set up branch variables
	Int_t detector[4];
	Double_t energy[4];
	
	// Set branch addresses
	t1->SetBranchAddress("det", detector);
	t1->SetBranchAddress("ene", energy);
	
	// Prep canvases for plotting
	TCanvas* c1 = new TCanvas("c1", "Canvas1", 800, 800);
	TCanvas* c2 = new TCanvas("c2", "Canvas2", 800, 800);
	TCanvas* c3 = new TCanvas("c3", "Canvas3", 500, 500);
	c1->Divide(2,2);
	c2->Divide(2,2);
	
	// Prep histograms
	TH1D* h1 = new TH1D("h1", "Det 0", 100, 250, 350);
	TH1D* h2 = new TH1D("h2", "Det 1", 100, 350, 450);
	TH1D* h3 = new TH1D("h3", "Det 2", 100, 450, 550);
	TH1D* h4 = new TH1D("h4", "Det 3", 100, 550, 650);
	TH1D* h5 = new TH1D("h5", "Det 0 All Data", 100, 250, 350);
	TH1D* h6 = new TH1D("h6", "Det 0 Coincidence w Det 1", 100, 250, 350);
	TH1D* h7 = new TH1D("h7", "Det 0 Coincidence w Det 2", 100, 250, 350);
	TH1D* h8 = new TH1D("h8", "Det 0 Coincidence w Det 3", 100, 250, 350);
	TH1D* h9 = new TH1D("h9", "Det 0 Coincidence w Det 1 within Peak 0", 100, 250, 350);
	
	// Get number of entries
	Int_t nEntries = t1->GetEntries();
	
	// Set up variables
	Int_t binmax, binmin;
	Double_t x_max, x_min;
	Int_t random_count; // count # of random coincidences
	
	// Fill histograms
	for(Int_t i = 0; i < nEntries; i++) {
		t1->GetEntry(i);
		
		// Fill hists 1-4
		if(energy[0] != 0) h1->Fill(energy[0]);
		if(energy[1] != 0) h2->Fill(energy[1]);
		if(energy[2] != 0) h3->Fill(energy[2]);
		if(energy[3] != 0) h4->Fill(energy[3]);
		
		// Fill hists 5-8
		if(energy[0] != 0) h5->Fill(energy[0]);
		if(energy[0] != 0 && energy[1] != 0) h6->Fill(energy[0]);
		if(energy[0] != 0 && energy[2] != 0) h7->Fill(energy[0]);
		if(energy[0] != 0 && energy[3] != 0) h8->Fill(energy[0]);
		
		// Fill hist 9
		// There is no overlap between the peak from detector 0 and the peak from detector 1
		// so the histogram is empty.
		if(energy[0] != 0 && energy[1] != 0) {
			binmax = h2->GetMaximumBin();
			binmin = h2->GetMinimumBin();
			x_max = h2->GetXaxis()->GetBinCenter(binmax);
			x_min = h2->GetXaxis()->GetBinCenter(binmin);
			
			// Check bounds
			if(energy[0] < x_max && energy[0] > x_min) {
				h9->Fill(energy[0]);
				random_count += 1;
			}
			
			// Check # of random coincidences (can't difference since h9 is empty)
			Bool_t rc = (energy[0] > x_max || energy[0] < x_min) && !(energy[0] < x_max && energy[0] > x_min);
			if(rc) {
				random_count += 1;
			}
		}
	}
	
	// Draw each histogram
	// Plain energy plots
	c1->cd(1);
	h1->Draw();
	c1->cd(2);
	h2->Draw();
	c1->cd(3);
	h3->Draw();
	c1->cd(4);
	h4->Draw();
	
	// Coincidence plots
	c2->cd(1);
	h5->Draw();
	c2->cd(2);
	h6->Draw();
	c2->cd(3);
	h7->Draw();
	c2->cd(4);
	h8->Draw();
	
	// Overlap 0 with peak 1
	c3->cd();
	h9->Draw();
	
	// Print # of random coincidences
	std::cout << random_count << std::endl;
	// 1278 = same number as coincidences as expected since there is no overlap between peak 0 & peak 1
	
}