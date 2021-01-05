/***********************************************************
* config.h: model configuration settings
* modifications:
* 10/06/16 RD	default input image "images/fungus.bmp"
* 04/07/16 RD	fixed the WAIT_HUFFMAN timing (3 channels)
* 04/06/16 RD	option to use sc_buffer instead of sc_fifo
* 04/04/16 RD	added FIFO_SIZE configuration
* 04/04/16 RD	added PRINT_DELTA_CRUNCH() macro
* 04/04/16 RD	added PRINT_NAME() macro
* 04/01/16 RD	new default x86-64 3.0 GHz profiling times
* 03/20/16 RD	introduced PIPELINED_ENCODER option
* 03/20/16 RD	added RGB2YCC timing (guess from blue sky)
* 03/18/16 RD	removed hardcoded image constants
* 03/18/16 RD	initial version (separated from types.h)
***********************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

// log the encoding process (selectable)
//#define VERBOSE 0
#define VERBOSE 1

// pipelined vs. sequential encoder cores (selectable)
//#define PIPELINED_ENCODER 0
#define PIPELINED_ENCODER 1

// print time stamps (adjustable)
//#define PRINT_TIME()	// none
#define PRINT_TIME()	printf("%15s: ", sc_time_stamp().to_string().c_str())

// print object names (adjustable)
//#define PRINT_NAME(n)	// none
#define PRINT_NAME(n)	printf("%s: ", n)

// print fine-grained delta cycles (adjustable)
#define PRINT_DELTA_CRUNCH()	// none
/*#define PRINT_DELTA_CRUNCH()	printf("%6u: %s: starts crunching...\n", \
				(unsigned)sc_delta_count(), name())
*/

// timing annotations, per block (several options)
// (a) untimed
#define TIME_RESOLUTION()	// none
#define WAIT_RGB2YCC()	// untimed
#define WAIT_DCT()		// untimed
#define WAIT_QUANTIZE()	// untimed
#define WAIT_ZIGZAG()		// untimed
#define WAIT_HUFFMAN()	// untimed
// (b) estimated times (EECS222C in F08, lecture 10, slide 16)
//#define TIME_RESOLUTION()	sc_set_time_resolution(1.0, SC_NS)
//#define WAIT_RGB2YCC()	wait(   4200000/180, SC_NS)
//#define WAIT_DCT()		wait(2*10411200/180, SC_NS)
//#define WAIT_QUANTIZE()	wait(   7839030/180, SC_NS)
//#define WAIT_ZIGZAG()		wait(   2316600/180, SC_NS)
//#define WAIT_HUFFMAN()	wait(   8882810/180, SC_NS)
// (c) measured times (x86-64 4-core Intel CPU Q9650, 3.0 GHz)
//#define TIME_RESOLUTION()	sc_set_time_resolution(1.0, SC_PS)
//#define WAIT_RGB2YCC()		wait(778798, SC_PS)
//#define WAIT_DCT()		wait(721503, SC_PS)
//#define WAIT_QUANTIZE()		wait(477199, SC_PS)
//#define WAIT_ZIGZAG()		wait(337671, SC_PS)
//#define WAIT_HUFFMAN()		wait(338209, SC_PS)

// image file names (default)
#define IMAGE_FILE_IN	"images/fungus.bmp"
#define IMAGE_FILE_OUT	"test.jpg"

// size of a 8x8 pixel block (constant)
#define BLOCKSIZE 64

// number of blocks processed in each stage (adjustable)
//#define NUMBLOCKS 1		// one block at a time
//#define NUMBLOCKS 267		// one row at a time
//#define NUMBLOCKS 402		// one col at a time
#define NUMBLOCKS 267*402	// 9 chunks

// Huffman output buffer size to Monitor (adjustable)
//#define NUMBYTES	(64)
//#define NUMBYTES	(1024/2)
//#define NUMBYTES	(1024)
#define NUMBYTES	(16*1024)
//#define NUMBYTES	(1024*1024)

// larger image and block sizes require larger stack (adjustable)
//#define SET_STACK_SIZE()	// default size
#define SET_STACK_SIZE()	set_stack_size(128*1024*1024*10)

// type of communication channels (two options)
// (a) sc_fifo (default/safe choice)
#define FIFO_SIZE		1
#define WAIT_STIMULUS()		/*none*/
#define WAIT4DATA(p)		/*none, read is blocking*/
// (b) sc_buffer (max. synchronous parallelism)
//#define FIFO_SIZE		/*none*/
//#define sc_fifo		sc_buffer
//#define sc_fifo_in		sc_in
//#define sc_fifo_out		sc_out
//#define WAIT_STIMULUS()	wait(SC_ZERO_TIME)
//#define WAIT4DATA(p)		wait(p.default_event())
// note: sc_buffer implements weak synchronization, needs this:
// - option "(a) untimed" must be chosen (pure delta-cycle model)
// - NUMBYTES must hold all data for NUMBLOCKS (incl. header)

#endif

// EOF
