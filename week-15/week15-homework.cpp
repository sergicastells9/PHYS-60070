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
	fileIn.open("four_detectors.dat");
	
	// Set up data variables
	Int_t detector[4];
	Double_t energy[4];
	Int_t temp;
	
	// Set up TTree and TBranches
	TTree* t1 = new TTree("t1", "Four Detectors TTree");
	t1->Branch("det", detector, "det[4]/I");
	t1->Branch("ene", energy, "ene[4]/D");
	
	// Get position and loop over file
	while(!fileIn.eof()) {
		// Skip buffer
		for(Int_t i = 0; i < 10; i++) {
			fileIn >> temp;
		}
		
		// Loop over events
		for(Int_t i = 0; i < 100; i++) {
			// Fill array values
			for(Int_t i = 0; i < 4; i++) {
				fileIn >> *(detector + i);
				fileIn >> *(energy + i);
			}
			
			t1->Fill();
		}
	}
	
	// Set up TFile and save TTree
	TFile* file = new TFile("data.root", "RECREATE");
	t1->Write();
	
	// Close file
	file->Close();
	
	
	return 0;
}