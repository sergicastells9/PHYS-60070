#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <math.h>
#include "distributions.h"

using namespace std;

//generate a number from a normal distribution
float Normal(float mean, float stdev){
    
    float R1;
    R1 = (float)rand()/(float)(RAND_MAX);
    float R2;
    R2 = (float)rand()/(float)(RAND_MAX);
    return mean + stdev*cos(2*3.14*R1)*sqrt(-log(R2));
    
}

//generate a number from an uniform distribution
float Uniform(float mean){
    return (float)rand()/(float)(RAND_MAX) * 2* mean;
}