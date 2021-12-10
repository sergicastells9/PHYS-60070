/*
	Author: Sergi Castells
*/


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// Overload #1: Only calibrates a single detector at a time. Calibrates detector 1
float Calibrator(float channel) {
	float ene;
	float aa = 1.05;
	float bb = -20;
	
	// Linear calibration here
	ene = aa*channel + bb;
	
	return ene;
}

// Overload #2: Also takes calibration parameters
float Calibrator(float channel, float aa, float bb) {
	float ene;
	
	// Linear calibration here
	ene = aa * channel + bb;
	
	return ene;
}

// Overload #3: Also takes energy array and detNo. Saves to file
void Calibrator(float *channel, float *energy, const float *aa, const float *bb, const int detNo) {
	// Calibrate data
	for(int i = 0; i < detNo; i++) {
		energy[i] = aa[i] * channel[i] + bb[i];
	}
	
	// No need to return anything since energy is passed by reference
}

// Overload #4: Returns energy calibration calculated in function
float* Calibrator(float *channel, const float *aa, const float *bb, const int detNo) {
	// Dynamically allocated so the pointer doesn't go out of scope
	float* energy = new float[detNo];
	
	// Calibrate data
	for(int i = 0; i < detNo; i++) {
		energy[i] = aa[i] * channel[i] + bb[i];
	}
	
	return energy;
}


int main() {
	// Input file setup
	std::fstream infile("hist.dat", std::fstream::in);
	
	if(!infile) {
		std::cout << "Input file failed to open!" << std::endl;
		exit(1);
	}
	
	// Output file setup
	std::fstream outfile("output.dat", std::fstream::out);
	
	if(!outfile) {
		std::cout << "Output file failed to open!" << std::endl;
		exit(1);
	}
	
	// Setup calibration variables
	int events = 100000;
	int det[4] = {1, 2, 3, 4};
	float aa[4] = {1.05, 1.05, 0.95, 0.95};
	float bb[4] = {-20, 20, -20, 20};
	int detNo = 4;
	std::string buffer;
	
	// Setup histogram bins
	int hist1[100] = {};
	int hist2[100] = {};
	int hist3[100] = {};
	int hist4[100] = {};
	int bins[100] = {};
	
	// Setup arrays for calibrated/uncalibrated data
	float channel[events];
	float* energy;
	
	// Loop through events, calibrate, fill histograms
	for(int i = 0; i < events; i++) {
		// Fill channel
		for(int j = 0; j < detNo; j++) {
			infile >> channel[j];
		}
		
		// Cycle to next event
		std::getline(infile, buffer);
		
		
		// I'm commenting out calls for the first 3 calibration functions so I only do it once
		
		/*
		
		// 1st Calibrator call
		float fEnergy = Calibrator(channel[0]);
		
		for(int j = 0; j < 100; j++) {
			if(fEnergy >= j * 10 && fEnergy < (j+1) * 10) {
				hist[j] += 1;
			}
		}
		
		
		// 2nd Calibrator call
		for(int j = 0; j < detNo; j++) {
			energy[j] = Calibrator(channel[j], aa[j], bb[j]);
		}
		
		
		// 3rd Calibrator call
		Calibrator(channel, energy, aa, bb, detNo);
		
		*/
		
		
		// 4th Calibrator call
		energy = Calibrator(channel, aa, bb, detNo);
		
		// Fill histograms
		for(int j = 0; j < 100; j++) {
			bins[j] = j * 10;
			
			if(energy[0] >= j * 10 && energy[0] < (j+1) * 10){
                hist1[j] += 1;
            }
            if(energy[1] >= j * 10 && energy[1] < (j+1) * 10){
                hist2[j] += 1;
            }
            if(energy[2] >= j * 10 && energy[2] < (j+1) * 10){
                hist3[j] += 1;
            }
            if(energy[3] >= j * 10 && energy[3] < (j+1) * 10){
                hist4[j] += 1;
            }
		}
	}
	
	
	// Save to output file
	for(int i = 0; i < 100; i++) {
		outfile << std::setw(4) << bins[i] << " " << hist1[i] << " " << hist2[i] << " " << hist3[i] << " " << hist4[i] << std::endl;
	}
	
	// Housekeeping stuff
	infile.close();
	outfile.close();
	delete energy;
	
	
	return 0;
}