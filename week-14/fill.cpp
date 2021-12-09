#include "fill.h"
#include <TH1F.h>

void fillHist(TH1F* hist) {
	
	//fill in the histogram
	for (int i=0;i<100;i++)
	{
		hist->Fill(i,i*i);
	}
}