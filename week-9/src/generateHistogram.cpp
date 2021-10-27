#include "distributions.h"
#include "generateHistogram.h"
#include <math.h>

//generate a histogram with a specified number of events
//histogram contains a gaussian plus uniform background
void GenerateHistogram(int *hist, int nBins, int nEvents, float mean, float sigma) {
    float ene;
    int eve=0;
    while (eve<nEvents){
        ene = Normal(mean,sigma);
        hist[(int)floor(ene)]++;
        eve++;
    }
    eve=0;
    while (eve<(int)(0.7*nEvents)){
        ene = Uniform(mean);
        for (int bin=0; bin<nBins;bin++){
            if (ene>bin && ene<=bin+1){
                hist[bin]++;
                break;
            }
        }
        eve++;
    }
}