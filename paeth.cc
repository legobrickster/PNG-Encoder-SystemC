#include "paeth.h"
void Paethfilter::paethfiltering(void)
{
     //while(1)
          {
            WAIT4DATA(PinIn);
	    in_pin=PinIn.read();
            memcpy(&Image,in_pin.data,sizeof(int)*3216*2136);
	    //Paeth Filter
               for(j=1;j<2136;j++)
		{
		    for(i=1;i<3216;i++)
			{
			  PaethPredictor[i+j*3216]=Image[(i-1)+j*3216]+Image[i+(j-1)*3216]-Image[(i-1)+(j-1)*3216];
			  /*PaethA[i+j*3216]=abs(PaethPredictor[i+j*3216]-Image_Red[(i-1)+j*3216]);
			  PaethB[i+j*3216]=abs(PaethPredictor[i+j*3216]-Image_Red[i+(j-1)*3216]);
			  PaethC[i+j*3216]=abs(PaethPredictor[i+j*3216]-Image_Red[(i-1)+(j-1)*3216]);*/
			}
		    }
		for(j=0;j<2136;j++)
		{	
		 PaethPredictor[j*3216]=abs(Image[(j-1)*3216]);
		}
		for(i=0;i<3216;i++)
		{	
		 PaethPredictor[i]=abs(Image[i]);
		} 
		 PaethPredictor[0]=Image[0];
		for(j=0;j<2136;j++)
		{
		    for(i=0;i<3216;i++)
			{
			  PaethA[i+j*3216]=abs(PaethPredictor[i+j*3216]-Image[(i-1)+j*3216]);
			  PaethB[i+j*3216]=abs(PaethPredictor[i+j*3216]-Image[i+(j-1)*3216]);
			  PaethC[i+j*3216]=abs(PaethPredictor[i+j*3216]-Image[(i-1)+(j-1)*3216]);
			}
		    }
		for(j=0;j<2136;j++)
		{
		    for(i=0;i<3216;i++)
			{
			  if((PaethA[i+j*3216]<=PaethC[i+j*3216])&&(PaethA[i+j*3216]<=PaethB[i+j*3216]))
				{
                                   Predicted[i+j*3216]=Image[(i-1)+j*3216];
				}
			  else if((PaethB[i+j*3216]<=PaethC[i+j*3216]))
				{
                                   Predicted[i+j*3216]=Image[i+(j-1)*3216];
				}
		          else 
				{
                                   Predicted[i+j*3216]=Image[(i-1)+(j-1)*3216];
				}
			}
		    }
                    
		
                    
                 for(j=0;j<2136;j++)
		       {
		    for(i=0;i<3216;i++)
			  {
                             PaethFiltered[i+j*3216]=Image[i+j*3216]-Predicted[i+j*3216];
			     if(PaethFiltered[i+j*3216]<0)
			       {
				PaethFiltered[i+j*3216]=PaethFiltered[i+j*3216]+256;
				}
			  }
			}
		memcpy(pinout.data,PaethFiltered, sizeof(int)*3216*2136);
		  PinOut.write(pinout);
 		}
}
Paethfilter::Paethfilter( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
  SC_HAS_PROCESS(Paethfilter);
  SC_THREAD(paethfiltering);
  SET_STACK_SIZE();
}

