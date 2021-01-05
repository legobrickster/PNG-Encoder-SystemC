/***********************************************************
* stimulus.cc: SystemC model by Weiwei Chen modified for PNG by Vivek G
* modifications:
* 
* 17/12/20 VG  Modified for PNG
* 01/18/13 WC	initial SystemC version
***********************************************************/

#ifndef _STIMULUS_H
#define _STIMULUS_H

//#define XSIZE,YSIZE

#include "systemc.h"
#include "types.h"

class Stimulus : public sc_core::sc_module
{
public:
	unsigned int  BMPlength;
	int           BMPoffset;
	unsigned int  imageWidth;
	unsigned int  imageHeight;
	bool          topToBottom;
	int           totalBlocks;
	int           strideX;
	int           strideY;
	int           pixelLen;
	int i,j;
	unsigned int  rInput[YSIZE*XSIZE];
	unsigned int  gInput[YSIZE*XSIZE];
	unsigned int  bInput[2136*3216];
	Blocks output_blocks[3];
	void ReadRGB(int n);
	void ReadBMP();

//public:
	const char *fNameIn;
	unsigned char *BMPdata;
	sc_fifo_out<Blocks> poutr1;
    	sc_fifo_out<Blocks> poutg1;
      	sc_fifo_out<Blocks> poutb1;
	sc_fifo_out<Blocks> poutr2;
    	sc_fifo_out<Blocks> poutg2;
      	sc_fifo_out<Blocks> poutb2;
      	sc_fifo_out<Blocks> poutr3;
    	sc_fifo_out<Blocks> poutg3;
      	sc_fifo_out<Blocks> poutb3;
	sc_fifo_out<Blocks> poutr4;
    	sc_fifo_out<Blocks> poutg4;
      	sc_fifo_out<Blocks> poutb4;
      	
  // Constructor
  	Stimulus( sc_core::sc_module_name _nm );

  // Method/Thread declarations
  	void main(void);
};

#endif

// EOF
