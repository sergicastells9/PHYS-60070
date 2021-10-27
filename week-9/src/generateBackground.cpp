#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include "distributions.h"
#include "generateBackground.h"

using namespace std;

//generate a uniform background
void GenerateBackground(int *hist, int nBins, int nEvents, float mean){
    srand(time(0));
    int ene;
    int eve=0;
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