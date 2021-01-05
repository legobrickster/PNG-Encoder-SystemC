/***********************************************************
* stimulus.cc: SystemC model by Weiwei Chen modified for PNG by Vivek G
* modifications:
* 
* 17/12/20 VG  Modified for PNG
* 01/18/13 WC	initial SystemC version
***********************************************************/
#ifndef _MONITOR_H
#define _MONITOR_H

#include "systemc.h"
#include "types.h"
#include <stdio.h>
#include <string.h>  // for strlen
#include <assert.h>
#include "zlib.h"
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 8192
//16384

class Monitor : public sc_core::sc_module
{
private:

public:
	const char *fNameOut;
	int i,j=0;
	sc_fifo_in<Blocks> PortSubR;
	sc_fifo_in<Blocks> PortSubG;
	sc_fifo_in<Blocks> PortSubB;
	sc_fifo_in<Blocks> PortUpR;
	sc_fifo_in<Blocks> PortUpG;
	sc_fifo_in<Blocks> PortUpB;
	sc_fifo_in<Blocks> PortPaethR;
	sc_fifo_in<Blocks> PortPaethG;
	sc_fifo_in<Blocks> PortPaethB;
	sc_fifo_in<Blocks> PortR;
	sc_fifo_in<Blocks> PortG;
	sc_fifo_in<Blocks> PortB;
	Blocks inputR;
	Blocks inputSubR;
	Blocks inputUpR;
	Blocks inputPaethR;
	Blocks inputG;
	Blocks inputSubG;
	Blocks inputUpG;
	Blocks inputPaethG;
	Blocks inputB;
	Blocks inputSubB;
	Blocks inputUpB;
	Blocks inputPaethB;
	int R_Sum[2136];
        int G_Sum[2136];
	int B_Sum[2136];

	int Sub_R_Sum[2136];
        int Sub_G_Sum[2136];
	int Sub_B_Sum[2136];
		  
	int Up_R_Sum[2136];
        int Up_G_Sum[2136];
	int Up_B_Sum[2136];

	int Paeth_R_Sum[2136];
        int Paeth_G_Sum[2136];
	int Paeth_B_Sum[2136];
	int Unfiltered_Sum[2136];
	int Sub_Sum[2136];
	int Up_Sum[2136];
	int Paeth_Sum[2136];
	int imred[3216*2136];
	int inflate[20610264];
	char inflatec[20610264];
	char out[20610264];
	char sourcebuffer[20610264];
	Bytef destination[20610264];
	Bytef destination_pad[12970964];	

	unsigned int IDAT;
	unsigned char *PNGdata;
	//Bytef destination_pad[11420452];
	int def(FILE *source, FILE *dest, int level);
  // Method/Thread declarations
  	void main(void);

  // Constructor
	Monitor( sc_core::sc_module_name _nm ); 
};

#endif

// EOF

/*Bytef sourcebuffer[20610264];
	Bytef destination[20610264];
	Bytef destination_pad[12970964];	
	//Bytef destination_pad[11420452];
uLongf destLen;
	uLong sourceLen=20610264;
	Bytef *dest=&destination[0];
	    Bytef *source=&sourcebuffer[0];
	    destLen=compressBound(sourceLen);
	    ulong *dl=&destLen;
	    compress(dest, dl, source, sourceLen);
	    printf("\n compressed %d",destination[0]);
	    printf("size of compressed string: %d", destLen);
	    //char header[]="89 50 4e 47 0d 0a 1a 0a 00 00 00 0d 49 48 44 52 00 00 0c 90 00 00 08 58 08 02 00 00 00 ac 6a 35 96 00 00 00 07 74 49 4d 45 07 e4 0b 09 0c 16 1e a4 54 fc 7f 00 00 20 00 49 44 41 54 ";
	    Bytef headerbyte[60];
	    int header[]={137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,12,144,0,0,8,88,8,2,0,0,0,172,106,53,150,0,0,0,7,116,73,77,69,7,228,11,9,12,22,30,164,84,252,127,0,0,32,0,73,68,65,84};
	    for(i=0;i<61;i++){headerbyte[i]=header[i];}
	    printf("%d header %d",headerbyte[59],header[59]);
	    //char end[]="00 00 00 00 49 45 4e 44 ae 42 60 82";
	    int end[]={73,69,78,68,174,66,96,130};
	    Bytef endbyte[8];
	    for(i=0;i<9;i++){endbyte[i]=end[i];}
	    //for(i=0;i<11420452;i++){destination_pad[i]=destination[i];}
	    for(i=0;i<12970964;i++){destination_pad[i]=destination[i];}
	    //uncompress(dest, dl, source, sourceLen);*/
