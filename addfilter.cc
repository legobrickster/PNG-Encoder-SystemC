#include "addfilter.h"

void Subfilter::say_hello(void)
{
     //while(1)
          {
            WAIT4DATA(PinIn);
	    in_pin=PinIn.read();
            memcpy(&Image,in_pin.data,sizeof(int)*3216*2136);
	    
		
           //Subtract filter
	   for(j=0;j<2136;j++)
		{
		    for(i=1;i<3216;i++)
			{
			  Subtract_Filter[i+j*3216]=Image[i+j*3216]-Image[(i-1)+j*3216];
			  
			  if(Subtract_Filter[i+j*3216]<0)
			   {
				Subtract_Filter[i+j*3216]=Subtract_Filter[i+j*3216]+256;
						
			    }
			}
		    }
		
	    	for(j=0;j<2136;j++)
		{	
		 Subtract_Filter[j*3216]=Image[j*3216];
		 
		}
//UP filter
            
		//delete []imsumblue;
                  //memcpy(&redout.data,imsumred, sizeof(int)*3216*2136);
		  memcpy(pinout.data,Subtract_Filter, sizeof(int)*3216*2136);
		  PinOut.write(pinout);
                  //printf("\n \nPaeth Filtered Value in module at 86th row=%d",Subtract_Filter[3216*86]);
		  //p=&imred;
		  
		  /*for(j=0;j<2136;j++)
            {
	     for(i=0;i<3216;i++)
	      {
               delete (*imred)[i+j*3216];
	      }
            }*/
		  
        }
	
}
Subfilter::Subfilter( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
  SC_HAS_PROCESS(Subfilter);
  SC_THREAD(say_hello);
  SET_STACK_SIZE();
}
