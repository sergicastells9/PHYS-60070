#include <iostream>
#include "input.h"
#include "generateHistogram.h"
#include "generateBackground.h"
#include "subtractBackground.h"

using namespace std;

int main(){
    GenerateHistogram(histogram, nBins, nEvents, mean, sigma);
    
    GenerateBackground(background, nBins, nEvents, mean);
    
    SubtractBgrd(histogram,background, result, nBins, factor);

    //print out the result to the screen
   for (int ii=0;ii<nBins;ii++){
        cout  << ii << " " << histogram[ii] << " " << background[ii] << " " << result[ii] << endl;
    }
}