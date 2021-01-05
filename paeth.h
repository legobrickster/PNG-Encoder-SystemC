#include "systemc.h"
#include "types.h"
class Paethfilter:public sc_core::sc_module
{
public: 
	int i,j=0;
	int Image[2136*3216];
	//unsigned int *imred;
	int PaethPredictor[2136*3216];
	int PaethA[2136*3216];
	int PaethB[2136*3216];
	int PaethC[2136*3216];
	int Predicted[2136*3216];
	int PaethFiltered[2136*3216];


	sc_fifo_in<Blocks> PinIn;
	sc_fifo_out<Blocks> PinOut;
	Blocks pinout;
	Blocks in_pin;
// Constructor
  	Paethfilter( sc_core::sc_module_name _nm );
	
  // Method/Thread declarations
  	void paethfiltering(void);
};
