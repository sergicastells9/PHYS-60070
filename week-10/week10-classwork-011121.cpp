// Author: Sergi Castells

{
	// fPeak1 setup and set line settings
	TF1 *fPeak1 = new TF1("fPeak1", "30*TMath::Gaus(x,5,1)", 0, 20);
	fPeak1->SetLineStyle(kDashed);
	fPeak1->SetLineColor(kGreen);
	
	// fPeak2 setup and set line settings
	TF1 *fPeak2 = new TF1("fPeak2", "20*TMath::Gaus(x,15,1)", 0, 20);
	fPeak2->SetLineStyle(kDashed);
	fPeak2->SetLineColor(kBlue);
	
	// fBgrd setup and set line settings
	TF1 *fBgrd = new TF1("fBgrd", "-2*x + 30", 0, 20);
	fBgrd->SetLineStyle(kDotted);
	
	// fSum setup
	TF1 *fSum = new TF1("fSum", "fPeak1+fPeak2+fBgrd", 0, 20);
	fSum->SetLineColor(kBlack);
	
	// Title/axis formatting
	fPeak1->GetXaxis()->SetTitle("x");
	fPeak1->GetXaxis()->CenterTitle();
	fPeak1->GetYaxis()->SetTitle("f(x)");
	fPeak1->GetYaxis()->CenterTitle();
	fPeak1->SetTitle("Plots");
	fPeak1->GetYaxis()->SetRangeUser(0, 60);
	
	// Draw all on same canvas
	TCanvas *canvas = new TCanvas("canvas", "Canvas", 500, 500);
	fPeak1->Draw();
	fPeak2->Draw("same");
	fBgrd->Draw("same");
	fSum->Draw("same");
	
	// TLegend setup and draw
	TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
	legend->SetHeader("LEGEND", "C");
	legend->AddEntry(fPeak1, "fPeak1", "l");
	legend->AddEntry(fPeak2, "fPeak2", "l");
	legend->AddEntry(fBgrd, "fBgrd", "l");
	legend->AddEntry(fSum, "fSum", "l");
	legend->Draw();
	
	// Print requested values
	std::cout << '\n' << "Integral of fSum from (0,20): " << fSum->Integral(0,20) << std::endl;
	std::cout << "Derivative of fSum at (x = 6): " << fSum->Derivative(6) << std::endl;
	std::cout << "Value of fSum at (x = 15): " << fSum->Eval(15) << '\n' << std::endl;
	
	// Save plot
	canvas->SaveAs("plot.pdf");
}
