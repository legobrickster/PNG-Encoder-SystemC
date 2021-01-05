#include "systemc.h"
#include "types.h"

class Subfilter:public sc_core::sc_module
{
public: 
	int i,j=0;
	int Image[2136*3216];
	//unsigned int *imred;
	
	int Subtract_Filter[2136*3216];
	
	int Row_Sum_SubtractFilter_Red[2136];
	int Row_Sum_SubtractFilter_Green[2136];
	int Row_Sum_SubtractFilter_Blue[2136];
	int sum,ui=0;
	sc_fifo_in<Blocks> PinIn;
	sc_fifo_out<Blocks> PinOut;
	Blocks pinout;
	Blocks in_pin;
	
 // Constructor
  	Subfilter( sc_core::sc_module_name _nm );
	
  // Method/Thread declarations
  	void say_hello(void);
};
