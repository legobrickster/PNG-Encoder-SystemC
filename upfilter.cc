#include "upfilter.h"

void Upfilter::computeup(void)
{
  // while(1)
          {
            WAIT4DATA(PinIn);
	    in_pin=PinIn.read();
            memcpy(&Image,in_pin.data,sizeof(int)*3216*2136);
	    
		
//UP filter
            for(j=1;j<2136;j++)
		{
		    for(i=0;i<3216;i++)
			{
			  Up_Filter_Image[i+j*3216]=Image[i+j*3216]-Image[i+(j-1)*3216];
			  
			}
		    }

	    for(i=0;i<3216;i++)
		{	
		 Up_Filter_Image[i]=Image[i];
		 
		}
	    for(j=0;j<2136;j++)
		{
		    for(i=0;i<3216;i++)
			{
			  
			  if(Up_Filter_Image[i+j*3216]<0)
			   {
				Up_Filter_Image[i+j*3216]=Up_Filter_Image[i+j*3216]+256;
						
			    }
			}
		    }
	   memcpy(pinout.data,Up_Filter_Image, sizeof(int)*3216*2136);
		  PinOut.write(pinout);
        }
}
Upfilter::Upfilter( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
  SC_HAS_PROCESS(Upfilter);
  SC_THREAD(computeup);
  SET_STACK_SIZE();
}
