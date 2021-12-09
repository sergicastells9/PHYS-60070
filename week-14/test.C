#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <math.h>


//ROOT stuff
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCutG.h"
#include "TGraph.h"
#include "fill.h"

using namespace std;


int main(){

	//create an output file and ROOT objects within it
	TFile* file = TFile::Open("test.root","RECREATE");
	TH1F* h1 = new TH1F("h1","",100,0,100);
	
	fillHist(h1);

	file->Write();
	file->Close();
}
