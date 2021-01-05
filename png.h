/***********************************************************
* png.h: SystemC model by VG
***********************************************************/

#ifndef _JPEG_H
#define _JPEG_H


#include "systemc.h"
#include "types.h"
#include "stimulus.h"
#include "monitor.h"
#include "addfilter.h"
#include "upfilter.h"
#include "paeth.h"
#include <stdio.h>
#include <string.h>  // for strlen
#include <assert.h>
#include "zlib.h"

SC_MODULE(Top)
{
  sc_fifo<Blocks> chStimToSubR, chStimToSubG, chStimToSubB, chStimToUpR, chStimToUpG, chStimToUpB, chStimToPaethR, chStimToPaethG, chStimToPaethB, chStimToMonitorR, chStimToMonitorG, chStimToMonitorB, chSubRToMonitor, chSubGToMonitor, chSubBToMonitor, chUpRToMonitor, chUpGToMonitor, chUpBToMonitor, chPaethRToMonitor, chPaethGToMonitor, chPaethBToMonitor;
 Stimulus stimulus;  
 Subfilter subR;
 Upfilter upR;
 Paethfilter paethR;
 Subfilter subG;
 Upfilter upG;
 Paethfilter paethG;
 Subfilter subB;
 Upfilter upB;
 Paethfilter paethB;
 Monitor monitor;
  
  // Port mapping
	void before_end_of_elaboration();
  // Constructor
	SC_CTOR(Top);
};

#endif

// EOF
