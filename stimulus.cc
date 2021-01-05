/***********************************************************
* stimulus.cc: SystemC model by Weiwei Chen modified for PNG by Vivek G
* modifications:
* 
* 17/12/20 VG  Modified for PNG
* 01/18/13 WC	initial SystemC version
***********************************************************/

#include "stimulus.h"

void Stimulus::ReadRGB(int n)
{
    int x, y, i, j, pos;
    int i2 = 0;
    int borderX, borderY, rowLen, oddEnd;
    int i2Last, jLast;
    unsigned char* ptr;

    x = (n % strideX) * 8;
    if ((unsigned)(x + 8) > imageWidth)
    {
	borderX = 8 - imageWidth % 8;
    }
    else
    {
	borderX = 0;
    }
    if (topToBottom)
    {
	y = (n / strideX) * 8;
	if ((unsigned)(y + 8) > imageHeight)
	{
	    borderY = 8 - imageHeight % 8;
	}
	else
	{
	    borderY = 0;
	}
    }
    else
    {
	y = imageHeight - ((n / strideX) * 8) - 8;
	if (y < 0)
	{
	    borderY = 8 - imageHeight % 8;
	}
	else
	{
	    borderY = 0;
	}
    }
    rowLen = imageWidth * pixelLen;
    if ((oddEnd = rowLen % 4))
    {
	rowLen += 4 - oddEnd; // pad rows to multiple of 4 bytes (RD, 04/03/16)
    }
    pos = (y * rowLen) + x * pixelLen;
    ptr = &BMPdata[BMPoffset + pos];
    for(i = 0; i < 8-borderY; i ++)
    {
	i2 = (topToBottom) ? (i) : (7-i);
	for(j = 0; j < 8-borderX; j ++)
	{   // copy actual pixel colors
	    bInput[i*8+j] = ptr[i2 * rowLen + j * pixelLen];
	    gInput[i*8+j] = ptr[i2 * rowLen + j * pixelLen + 1];
	    rInput[i*8+j] = ptr[i2 * rowLen + j * pixelLen + 2];
	}
	jLast = j-1;
	for( ; j < 8; j ++)
	{   // fill right border with same color as in right column
	    bInput[i*8+j] = ptr[i2 * rowLen + jLast * pixelLen];
	    gInput[i*8+j] = ptr[i2 * rowLen + jLast * pixelLen + 1];
	    rInput[i*8+j] = ptr[i2 * rowLen + jLast * pixelLen + 2];
	}
    }
    i2Last = i2;
    for( ; i < 8; i ++)
    {
	for(j = 0; j < 8-borderX; j ++)
	{   // fill bottom border with same color as in bottom column
	    bInput[i*8+j] = ptr[i2Last * rowLen + j * pixelLen];
	    gInput[i*8+j] = ptr[i2Last * rowLen + j * pixelLen + 1];
	    rInput[i*8+j] = ptr[i2Last * rowLen + j * pixelLen + 2];
	}
	jLast = j-1;
	for( ; j < 8; j ++)
	{   // fill bottom right corner with same color as last pixel
	    bInput[i*8+j] = ptr[i2Last * rowLen + jLast * pixelLen];
	    gInput[i*8+j] = ptr[i2Last * rowLen + jLast * pixelLen + 1];
	    rInput[i*8+j] = ptr[i2Last * rowLen + jLast * pixelLen + 2];
	}
    }
}
void Stimulus::ReadBMP()
{
	FILE *fin;
	int i;
	unsigned char *ch;

#if VERBOSE
	PRINT_TIME();
   	PRINT_NAME(name());
	printf("reading image \"%s\"\n", fNameIn);
#endif
	fin = fopen(fNameIn, "rb");
	if (fin == NULL)
	{
		char ErrorMsg[1024];
		sprintf(ErrorMsg, "Cannot open file \"%s\" for reading!",
			fNameIn);
		sc_report_handler::report(SC_FATAL, "jpeg_encoder/Stimulus",
			ErrorMsg, __FILE__ , __LINE__);
	}
	fseek(fin, 0L, SEEK_END);
	BMPlength = ftell(fin);
	fseek(fin, 0L, SEEK_SET);
	BMPdata = new unsigned char[BMPlength];
	fread(BMPdata, sizeof(char), BMPlength, fin);
	fclose(fin);

	ch = BMPdata;
	ch ++;	/*'B'*/
	ch ++;	/*'M'*/
	ch += 8;
	BMPoffset = 0;
	for(i = 3; i >= 0; i --){
		BMPoffset = (BMPoffset << 8) | ch[i];
	}
#if VERBOSE
		PRINT_TIME();
		PRINT_NAME(name());
		/*printf("BMPDATA value %d %d %d %d %d\n",
			(BMPdata[57]),(ch[5001]),(BMPdata[25001]),(BMPdata[63001]),(BMPdata[51]));
		printf("BMPData length %d \n",
			(BMPlength));*/
#endif
	ch += 8;
	imageWidth = 0;
	for(i = 3; i >= 0; i --){
		imageWidth = (imageWidth << 8) | ch[i];
	}
	strideX = (imageWidth+(8-1)) >> 3;
	ch += 4;
	imageHeight = 0;
	for(i = 3; i >= 0; i --){
		imageHeight = (imageHeight << 8) | ch[i];
	}
	if ((int)imageHeight < 0) {
		topToBottom = true;
		imageHeight = -((int)imageHeight);
	}
	else {
		topToBottom = false;
	}
	strideY = (imageHeight+(8-1)) >> 3;
	ch += 6;
	pixelLen = 0;
	for(i = 1; i >= 0; i --){
		pixelLen = (pixelLen << 8) | ch[i];
	}
	pixelLen >>= 3;
	totalBlocks = strideX * strideY;
#if VERBOSE
	PRINT_TIME();
   	PRINT_NAME(name());
	printf("BMP image %dx%d pixels, %dx%d=%d blocks\n",
		imageWidth, imageHeight, strideX, strideY, totalBlocks);
#endif
}

void Stimulus::main(void)
{
    int blk, n;

    ReadBMP();
    for(i=0;i<2136;i++)
	{
	 for(j=0;j<3216;j++)
	  {
		rInput[i*3216+j]=BMPdata[56+j*4+i*3216*4];
		//printf(" %d ",rInput[i*3216+j]);
	  }
	}
	for(i=0;i<2136;i++)
	{
	 for(j=0;j<3216;j++)
	  {
		gInput[i*3216+j]=BMPdata[55+j*4+i*3216*4];
		//printf(" %d ",gInput[i*3216+j]);
	  }
	}
	for(i=0;i<2136;i++)
	{
	 for(j=0;j<3216;j++)
	  {
		bInput[i*3216+j]=BMPdata[54+j*4+i*3216*4];
	  }
	}
    for (blk=0; blk<totalBlocks; blk+=n)
    {
	WAIT_STIMULUS();
	/*for (n=0; n<NUMBLOCKS && blk+n<totalBlocks; n++)
	{
	    PRINT_DELTA_CRUNCH();
	    //ReadRGB(blk+n);
	    memcpy(&output_blocks[0].data[n*BLOCKSIZE],
		rInput, sizeof(int) * BLOCKSIZE);
	    memcpy(&output_blocks[1].data[n*BLOCKSIZE],
		gInput, sizeof(int) * BLOCKSIZE);
	    memcpy(&output_blocks[2].data[n*BLOCKSIZE],
		bInput, sizeof(int) * BLOCKSIZE);
	}*/
	memcpy(&output_blocks[0].data,rInput, sizeof(int)*3216*2136);
	memcpy(&output_blocks[1].data,gInput, sizeof(int)*3216*2136);
	memcpy(&output_blocks[2].data,bInput, sizeof(int)*3216*2136);
	output_blocks[0].imgWidth = imageWidth;
	output_blocks[0].imgHeight = imageHeight;
	output_blocks[0].blkCount = blk;
	output_blocks[0].blkNum = n;
	output_blocks[1].imgWidth = imageWidth;
	output_blocks[1].imgHeight = imageHeight;
	output_blocks[1].blkCount = blk;
	output_blocks[1].blkNum = n;
	output_blocks[2].imgWidth = imageWidth;
	output_blocks[2].imgHeight = imageHeight;
	output_blocks[2].blkCount = blk;
	output_blocks[2].blkNum = n;
	poutr1.write(output_blocks[0]);
	poutg1.write(output_blocks[1]);
	poutb1.write(output_blocks[2]);
	poutr2.write(output_blocks[0]);
	poutg2.write(output_blocks[1]);
	poutb2.write(output_blocks[2]);
	poutr3.write(output_blocks[0]);
	poutg3.write(output_blocks[1]);
	poutb3.write(output_blocks[2]);
	poutr4.write(output_blocks[0]);
	poutg4.write(output_blocks[1]);
	poutb4.write(output_blocks[2]);
        //printf("BMP image size %d",sizeof(pout1));
	//printf("copied value %d", rInput[60000]);
	
    }
    delete [] BMPdata;
}

Stimulus::Stimulus( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
  SC_HAS_PROCESS(Stimulus);
  SC_THREAD(main);
  SET_STACK_SIZE();
}

// EOF
