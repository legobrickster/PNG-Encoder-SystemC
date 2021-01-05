/***********************************************************
* monitor.cc: SystemC model by Vivek

***********************************************************/

#include "monitor.h"



int Monitor::def(FILE *source, FILE *dest, int level)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK)
        return ret;

    /* compress until end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }
        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;
}










void Monitor::main(void)
{   
   // while(1)
    {
	    WAIT4DATA(PortR);
	    inputR=PortR.read();
	    inputSubR=PortSubR.read();
	    inputUpR=PortUpR.read();
	    inputPaethR=PortPaethR.read();

	    inputG=PortG.read();
	    inputSubG=PortSubG.read();
	    inputUpG=PortUpG.read();
	    inputPaethG=PortPaethG.read();

	    inputB=PortB.read();
	    inputSubB=PortSubB.read();
	    inputUpB=PortUpB.read();
	    inputPaethB=PortPaethB.read();
	    
	    memcpy(imred,inputPaethR.data,sizeof(int)*3216*2136);
	    
            for(j=0;j<2136;j++)
		{
		    for(i=0;i<3216;i++)
			{
			  R_Sum[j]+=abs(inputR.data[i+j*3216]);
			  G_Sum[j]+=abs(inputG.data[i+j*3216]);
			  B_Sum[j]+=abs(inputB.data[i+j*3216]);

			  Sub_R_Sum[j]+=abs(inputSubR.data[i+j*3216]);
			  Sub_G_Sum[j]+=abs(inputSubG.data[i+j*3216]);
			  Sub_B_Sum[j]+=abs(inputSubB.data[i+j*3216]);

			  Up_R_Sum[j]+=abs(inputUpR.data[i+j*3216]);
			  Up_G_Sum[j]+=abs(inputUpG.data[i+j*3216]);
			  Up_B_Sum[j]+=abs(inputUpB.data[i+j*3216]);

		          Paeth_R_Sum[j]+=abs(inputPaethR.data[i+j*3216]);
			  Paeth_G_Sum[j]+=abs(inputPaethG.data[i+j*3216]);
			  Paeth_B_Sum[j]+=abs(inputPaethB.data[i+j*3216]);
			  
			  Unfiltered_Sum[j]+=abs(inputR.data[i+j*3216]);
			  Unfiltered_Sum[j]+=abs(inputG.data[i+j*3216]);
			  Unfiltered_Sum[j]+=abs(inputB.data[i+j*3216]);

			  Sub_Sum[j]+=abs(inputSubR.data[i+j*3216]);
			  Sub_Sum[j]+=abs(inputSubG.data[i+j*3216]);
			  Sub_Sum[j]+=abs(inputSubB.data[i+j*3216]);

			  Up_Sum[j]+=abs(inputUpR.data[i+j*3216]);
			  Up_Sum[j]+=abs(inputUpG.data[i+j*3216]);
			  Up_Sum[j]+=abs(inputUpB.data[i+j*3216]);

		          Paeth_Sum[j]+=abs(inputPaethR.data[i+j*3216]);
			  Paeth_Sum[j]+=abs(inputPaethG.data[i+j*3216]);
			  Paeth_Sum[j]+=abs(inputPaethB.data[i+j*3216]);
			  
			}
		    }
	  /*  for(j=0;j<2136;j++)
		{
		   if(Unfiltered_Sum[j]<Sub_Sum[j] && Unfiltered_Sum[j]<Up_Sum[j] && Unfiltered_Sum[j]<Paeth_Sum[j])
                    { for(i=0;i<3216;i++)			
 			{inflate[((3216*3)+1)*j]=0;
 			 inflate[((3216*3)+1)*j+(i*3)+1]=inputR.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+2]=inputG.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+3]=inputB.data[i+j*3216];
			}
		    }
	           else if(Sub_Sum[j]<Up_Sum[j] && Sub_Sum[j]<Paeth_Sum[j])
                    { for(i=0;i<3216;i++)			
 			{inflate[((3216*3)+1)*j]=1;
 			 inflate[((3216*3)+1)*j+(i*3)+1]=inputSubR.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+2]=inputSubG.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+3]=inputSubB.data[i+j*3216];
			}
		    }
		   else if(Up_Sum[j]<Paeth_Sum[j])
                    { for(i=0;i<3216;i++)			
 			{inflate[((3216*3)+1)*j]=2;
 			 inflate[((3216*3)+1)*j+(i*3)+1]=inputUpR.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+2]=inputUpG.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+3]=inputUpB.data[i+j*3216];
			}
		    }
		   else
                    { for(i=0;i<3216;i++)			
 			{inflate[((3216*3)+1)*j]=4;
 			 inflate[((3216*3)+1)*j+(i*3)+1]=inputPaethR.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+2]=inputPaethG.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+3]=inputPaethB.data[i+j*3216];
			}
					
		    }
	      }*/
	      for(i=0;i<3216;i++)
	      {
	      inflate[0]=1;
 	      inflate[(i*3)+1]=inputSubR.data[i];
	      inflate[(i*3)+2]=inputSubG.data[i];
	      inflate[(i*3)+3]=inputSubB.data[i];
	      }
	      for(j=1;j<2136;j++)
		{
	             
	              for(i=0;i<3216;i++)			
 			{inflate[((3216*3)+1)*j]=4;
 			 inflate[((3216*3)+1)*j+(i*3)+1]=inputPaethR.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+2]=inputPaethG.data[i+j*3216];
			 inflate[((3216*3)+1)*j+(i*3)+3]=inputPaethB.data[i+j*3216];
			}
		}
	    
            for(i=0;i<20610264;i++)
		{
			sourcebuffer[i]=inflate[i];
			//printf("%d",inflate[i]);
		}
            
	    
	    //char headerbyte[60];
	    //int header[]={137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,12,144,0,0,8,88,8,2,0,0,0,172,106,53,150,0,0,0,7,116,73,77,69,7,228,11,9,12,22,30,164,84,252,127,0,0,32,0,73,68,65,84};
	int header[]={137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,12,144,0,0,8,88,8,2,0,0,0,172,106,53,150,0,197,236,2,73,68,65,84};
	    //char headerbyte[37];
	    //int header[]={137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,12,144,0,0,8,88,8,2,0,0,0,255,128,2,3,0,0,32,0};
	    //for(i=0;i<61;i++){headerbyte[i]=header[i];}
	    char headerbyte[41];
	   // int header[]={137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,12,144,0,0,8,88,8,2,0,0,0,35,8,162,193,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,4,103,65,77,65,0,0,177,143,11,252,97,5,0,0,0,9,112,72,89,115,0,0,46,34,0,0,46,34,1,170,226,221,146,0,0,20,0,73,68,65,84};


	    for(i=0;i<42;i++){headerbyte[i]=header[i];}
	    int end[]={0,0,0,0,73,69,78,68,174,66,96,130};
	    char endbyte[13];
	    for(i=0;i<13;i++){endbyte[i]=end[i];}
	    //for(i=0;i<11420452;i++){destination_pad[i]=destination[i];}
	    for(i=0;i<12970964;i++){destination_pad[i]=destination[i];}
	    FILE *f;
	    f=fopen("fungus_png.txt","wb");
            //fwrite(headerbyte, sizeof(unsigned char), sizeof(headerbyte), f);
	    fwrite(sourcebuffer, sizeof(unsigned char), sizeof(sourcebuffer), f);
	    fclose(f);
	    f=fopen("fungus_png.txt","rb");
	    //fwrite(endbyte, sizeof(unsigned char), sizeof(endbyte), f);
	    FILE *f1;
	    f1=fopen("fungus.png","wb");
	    fwrite(headerbyte, sizeof(unsigned char), sizeof(headerbyte), f1);
	    
	    //fclose(f);
	    int ret;


	    SET_BINARY_MODE(stdin);
    SET_BINARY_MODE(stdout);
            
	    ret=def(f, f1, Z_DEFAULT_COMPRESSION);
	    fwrite(endbyte, sizeof(unsigned char), sizeof(endbyte), f1);
	    
    }

}
Monitor::Monitor( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
    SC_HAS_PROCESS(Monitor);
    SC_THREAD(main);
    SET_STACK_SIZE();
}
// EOF
