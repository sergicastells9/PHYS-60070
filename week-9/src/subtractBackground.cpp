#include "subtractBackground.h"

using namespace std;

//subtract background from a histogram and write the result into a separate output array
void SubtractBgrd(int *hist, int *bgrd, int *histOut, int nBins, float scaling){
    
    for (int ii=0; ii<nBins; ii++)
    {
        histOut[ii] = hist[ii] - bgrd[ii] * scaling;
    }
}