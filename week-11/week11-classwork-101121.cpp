{
	int bins = 10;
	TH1D* h1 = new TH1D("h1", "Histogram", bins, 0, 10);
	//h1->Sumw2(false);
	
	for(int i = 0; i < 4; i++) {
		h1->Fill(i, i);
	}
	
	h1->Sumw2(false);
	h1->SetStats(0);
	
	for(int i = 4; i < bins; i++) {
		h1->Fill(i, i);
	}
	
	TCanvas* canavas = new TCanvas("canvas", "Plot", 500, 500);
	h1->Draw("e");
	
	for(int i = 1; i <= bins; i++) {
		std::cout << h1->GetBinError(i) << std::endl;
	}
	
	
}