{
	/*
	TFile* fOut = TFile::Open("sample.root", "RECREATE");
	TH1F* hist = new TH1F("hist", "Hist", 100, -10, 10);
	hist->FillRandom("gaus", 1000);
	fOut->ls();
		
	fOut->Write();
	fOut->Close();
	
	//////////////////////////////////////
	
	TFile* file1 = TFile::Open("file1.root", "RECREATE");
	TH1F* hist1 = new TH1F("hist1", "Hist1", 100, 0, 10);
	for(int i = 0; i < 10000; i++) {
		hist1->Fill(gRandom->Gaus(5,1));
	}
	file1->Write();
	
	TFile* file2 = TFile::Open("file2.root", "RECREATE");
	TH1F* hist2 = new TH1F("hist2", "Hist2", 100, 0, 10);
	for(int i = 0; i < 10000; i++) {
		hist2->Fill(gRandom->Uniform(10));
	}
	file2->Write();
	*/
	
	//////////////////////////////////////
	
	/*
	TFile* file1 = TFile::Open("file1.root", "UPDATE");
	TFile* file2 = TFile::Open("file2.root", "READ");
	
	TH1F* hist1;
	file1->GetObject("hist1", hist1);
	hist1->Fill(6, 100);
	file1->Write();
	file1->ls();
	
	file1->cd();
	TH1F* hPointer;
	file2->GetObject("hist2", hPointer);
	hist1->Add(hPointer);
	
	TFile* sum = TFile::Open("sum.root", "RECREATE");
	TH1F* hSum = new TH1F("hSum", "hSum", 100, 0, 10);
	hSum->Add(hist1);
	hSum->Draw();
	sum->Write();
	*/
	
	//////////////////////////////////////
	
	TFile* sum = TFile::Open("sum.root", "READ");
	TFile* sumFit = TFile::Open("sumFit.root", "RECREATE");
	
	TH1F* hSum;
	sum->GetObject("hSum", hSum);
	
	TF1* fSum = new TF1("fSum", "gaus(0) + pol0(3)", 0, 10);
	hSum->Fit(fSum);
	
	sumFit->Write();
	
	
	
	
	
}