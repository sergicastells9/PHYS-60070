/*
	Author: Sergi Castells
*/

{
	// Load in data.root file
	TFile* file = TFile::Open("data.root");
	
	// One angle per particle
	Double_t theta1, theta2, theta3;
	
	// Set aliases for different thetas
	t1->SetAlias("theta1", "180/pi * acos(Pz[0]/sqrt(Px[0]*Px[0]+Py[0]*Py[0]+Pz[0]*Pz[0]))");
	t1->SetAlias("theta2", "180/pi * acos(Pz[1]/sqrt(Px[1]*Px[1]+Py[1]*Py[1]+Pz[1]*Pz[1]))");
	t1->SetAlias("theta3", "180/pi * acos(Pz[2]/sqrt(Px[2]*Px[2]+Py[2]*Py[2]+Pz[2]*Pz[2]))");
	
	// Set up histograms
	THStack* hs = new THStack("hs", "E[0] vs E[0] with cuts"); // Use this to stack E[0] cuts vs no cuts
	TH2D* h2d1 = new TH2D("h2d1", "E vs theta1", 200, -10, 190, 200, 0, 2);
	TH2D* h2d2 = new TH2D("h2d2", "theta1 vs theta2", 200, -10, 190, 200, -10, 190);
	TH1D* h1d1 = new TH1D("h1d1", "E without cuts", 200, 0, 2);
	TH1D* h1d2 = new TH1D("h1d2", "E with cuts", 200, 0, 2);
	
	// Draw E[0] vs theta1
	TCanvas* c1 = new TCanvas("c1", "Canvas1", 500, 500);
	c1->Divide(3);
	c1->cd(1);
	t1->Draw("E[0]:theta1>>h2d1", "", "colz");
	
	// Set up cuts and draw theta1 vs theta2
	TCut cut1 = "theta1 > 12";
	TCut cut2 = "theta2 < 45";
	c1->cd(2);
	t1->Draw("theta1:theta2>>h2d2", "", "colz");
	
	// Plot E[0] vs E[0] with cuts on THStack
	c1->cd(3);
	t1->Draw("E[0]>>h1d1", "", "goff");
	t1->Draw("E[0]>>h1d2", cut1 && cut2, "goff");
	hs->Add(h1d1);
	hs->Add(h1d2);
	hs->Draw("nostack");
	
	// Add legend to distinguish plots
	gPad->BuildLegend(0.75,0.75,0.95,0.95,"");
	
	
	// Plot thetas by themselves
	TCanvas* c2 = new TCanvas("c2", "Canvas2", 500, 500);
	c2->Divide(3);
	c2->cd(1);
	t1->Draw("theta1");
	c2->cd(2);
	t1->Draw("theta2");
	c2->cd(3);
	t1->Draw("theta3");
	
	// Variables for rest mass
	Double_t mass1, mass2;
	t1->SetAlias("mass1", "sqrt(E[0]*E[0] - (Px[0]*Px[0]+Py[0]*Py[0]+Pz[0]*Pz[0]))");
	t1->SetAlias("mass2", "sqrt(E[1]*E[1] - (Px[1]*Px[1]+Py[1]*Py[1]+Pz[1]*Pz[1]))");
	
	// Plot masses
	TCanvas* c4 = new TCanvas("c3", "Canvas3", 500, 500);
	c4->Divide(2);
	c4->cd(1);
	t1->Draw("mass1"); // this looks like a proton ~940 MeV
	c4->cd(2);
	t1->Draw("mass2"); // this looks like a pion ~134 MeV
}