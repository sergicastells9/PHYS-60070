/*
	Author: Sergi Castells
*/

// C++ includes
#include <fstream>

// ROOT includes
#include <TTree.h>
#include <TFile.h>


int main() {
	// Open up data file
	std::ifstream fileIn;
	fileIn.open("final.dat");
	
	// Set up data variables
	Double_t gamma1, gamma2, energy;
	Int_t detector;
	
	// Set up TTree and TBranches
	TTree* t1 = new TTree("t1", "Inelastic 1385 keV Scattering");
	t1->Branch("g1", &gamma1, "g1/D");
	t1->Branch("g2", &gamma2, "g2/D");
	t1->Branch("det", &detector, "det/I");
	t1->Branch("ene", &energy, "ene/D");
	
	// Loop over file
	while(!fileIn.eof()) {
		fileIn >> gamma1;
		fileIn >> gamma2;
		fileIn >> detector;
		fileIn >> energy;
		
		t1->Fill();
	}	
	
	// Set up TFile and save TTree
	TFile* file = new TFile("data.root", "RECREATE");
	t1->Write();
	
	// Close file
	file->Close();
	
	
	return 0;
}