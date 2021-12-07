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
	/*
	TCanvas* c1 = new TCanvas("c1", "Canvas1", 500, 500);
	TCanvas* c2 = new TCanvas("c2", "Canvas2", 500, 500);
	TCanvas* c3 = new TCanvas("c3", "Canvas3", 500, 500);
	TCanvas* c4 = new TCanvas("c4", "Canvas4", 500, 500);
	*/
	TCanvas* c5 = new TCanvas("c5", "Canvas5", 500, 500);
	TCanvas* c6 = new TCanvas("c6", "Canvas6", 500, 500);
	TCanvas* c7 = new TCanvas("c7", "Canvas7", 500, 500);
	TCanvas* c8 = new TCanvas("c8", "Canvas8", 500, 500);
	
	// Prep histograms
	TH1D* h1 = new TH1D("h1", "Det 1", 100, 250, 350);
	TH1D* h2 = new TH1D("h2", "Det 2", 100, 350, 450);
	TH1D* h3 = new TH1D("h3", "Det 3", 100, 450, 550);
	TH1D* h4 = new TH1D("h4", "Det 4", 100, 550, 650);
	TH1D* h5 = new TH1D("h5", "Det 1 All Data", 100, 250, 350);
	TH1D* h6 = new TH1D("h6", "Det 1 Coincidence w Det 2", 100, 250, 350);
	TH1D* h7 = new TH1D("h7", "Det 1 Coincidence w Det 3", 100, 250, 350);
	TH1D* h8 = new TH1D("h8", "Det 1 Coincidence w Det 4", 100, 250, 350);
	
	// Get number of entries
	Int_t nEntries = t1->GetEntries();
	
	// Fill histograms
	for(Int_t i = 0; i < nEntries; i++) {
		t1->GetEntry(i);
		if(energy[0] != 0) h1->Fill(energy[0]);
		if(energy[1] != 0) h2->Fill(energy[1]);
		if(energy[2] != 0) h3->Fill(energy[2]);
		if(energy[3] != 0) h4->Fill(energy[3]);
		
		if(energy[0] != 0) h5->Fill(energy[0]);
		if(energy[0] != 0 && energy[1] != 0) h6->Fill(energy[0]);
		if(energy[0] != 0 && energy[2] != 0) h7->Fill(energy[0]);
		if(energy[0] != 0 && energy[3] != 0) h8->Fill(energy[0]);
	}
	
	// Draw each histogram
	/*
	c1->cd();
	h1->Draw();
	c2->cd();
	h2->Draw();
	c3->cd();
	h3->Draw();
	c4->cd();
	h4->Draw();
	*/
	c5->cd();
	h5->Draw();
	c6->cd();
	h6->Draw();
	c7->cd();
	h7->Draw();
	c8->cd();
	h8->Draw();
	
	
	
	
}