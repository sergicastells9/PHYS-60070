#ifndef INPUT_H
#define INPUT_H



//user parameters
const int nBins = 100;
int nEvents = 10000;
float mean = 50;
float sigma = 10;
float factor = 0.7;

//histograms
int histogram[nBins] = {0};
int background[nBins] = {0};
int result[nBins] = {0};





#endif