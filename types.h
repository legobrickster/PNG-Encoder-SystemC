/***********************************************************
* types.h: SystemC model by Weiwei Chen
* modifications:
* 04/05/16 RD	provided clean/proper sc_trace methods
*		(needed by sc_signal, sc_buffer)
* 03/18/16 RD	added image context to Blocks data
* 03/17/16 RD	major code cleanup
* 03/03/16 RD	initial version, extracted from jpeg.h
***********************************************************/

#ifndef _TYPES_H
#define _TYPES_H

#include "systemc.h"
#include "config.h"

class Blocks
{
  public:
    int imgWidth, imgHeight;
    int blkCount, blkNum;
    int data[NUMBLOCKS * BLOCKSIZE];

    void CopyImageContext(const Blocks &rhs)
    {
	imgWidth = rhs.imgWidth;
	imgHeight = rhs.imgHeight;
	blkCount = rhs.blkCount;
	blkNum = rhs.blkNum;
    }

    inline bool operator == (const Blocks &rhs) const
    {
	if (imgWidth != rhs.imgWidth || imgHeight != rhs.imgHeight)
	      return false;
	if (blkCount != rhs.blkCount || blkNum != rhs.blkNum)
	      return false;
	return memcmp(data, rhs.data, sizeof(int) * BLOCKSIZE * NUMBLOCKS);
    }

    inline Blocks& operator = (const Blocks &rhs)
    {
	CopyImageContext(rhs);
	memcpy(data, rhs.data, sizeof(int) * BLOCKSIZE * NUMBLOCKS);
	return *this;
    }

    inline friend ostream& operator << (ostream& os, Blocks const &v)
    {
	int i;

	os << "(" << v.imgWidth << "x" << v.imgHeight << ",";
	os << v.blkCount << "," << v.blkNum << ";";
	for(i = 0; i < BLOCKSIZE * NUMBLOCKS; i++)
    	{
		os << v.data[i] << ",";
	}
	os << ")";
	return os;
    }

    inline friend void sc_trace(
	sc_trace_file *tf, const Blocks &v, const std::string &NAME)
    {
	sc_trace(tf, v.imgWidth, NAME + ".imgWidth");
	sc_trace(tf, v.imgHeight, NAME + ".imgHeight");
	sc_trace(tf, v.blkCount, NAME + ".blkCount");
	sc_trace(tf, v.blkNum, NAME + ".blkNum");
	// blocks data omitted
    }

    // constructor
    Blocks(void)
    {
	imgWidth = 0;
	imgHeight = 0;
	blkCount = 0;
	blkNum = 0;
    }
};

class Bytes
{
  public:
    int n;
    unsigned char b[NUMBYTES];

    inline bool operator == (const Bytes &rhs) const
    {
	return (rhs.n==n && memcmp(b, rhs.b, sizeof(unsigned char) * NUMBYTES));
    }

    inline Bytes& operator = (const Bytes &rhs)
    {
	n = rhs.n;
	memcpy(b, rhs.b, sizeof(unsigned char) * NUMBYTES);
	return *this;
    }

    inline friend ostream& operator << (ostream &os, Bytes const &v)
    {
	int i;

	os << "(" << v.n << ":";
	for(i=0; i<NUMBYTES; i++)
	{
		os << v.b[i] << ",";
	}
	os << ")";
	return os;
    }

    inline friend void sc_trace(
	sc_trace_file *tf, const Bytes &v, const std::string &NAME)
    {
	sc_trace(tf, v.n, NAME + ".n");
	// bytes data omitted
    }

    // constructor
    Bytes(void)
    {
	n = 0;
    }
};

#endif

// EOF
