#include "systemc.h"
#include "types.h"

class Upfilter:public sc_core::sc_module
{
public: 
	int i,j=0;
	int Image[2136*3216];
	int Up_Filter_Image[2136*3216];
	sc_fifo_in<Blocks> PinIn;
	sc_fifo_out<Blocks> PinOut;
	Blocks pinout;
	Blocks in_pin;
	
 // Constructor
  	Upfilter( sc_core::sc_module_name _nm );
	
  // Method/Thread declarations
  	void computeup(void);
};
