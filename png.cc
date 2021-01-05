/***********************************************************
* png.cc: VG
***********************************************************/

#include "png.h"

Top::Top( sc_core::sc_module_name _nm )
  : sc_core::sc_module( _nm )
  , chStimToSubR(FIFO_SIZE)
  , chStimToSubG(FIFO_SIZE)
  , chStimToSubB(FIFO_SIZE)
  , chStimToUpR(FIFO_SIZE)
  , chStimToUpG(FIFO_SIZE)
  , chStimToUpB(FIFO_SIZE)
  , chStimToPaethR(FIFO_SIZE)
  , chStimToPaethG(FIFO_SIZE)
  , chStimToPaethB(FIFO_SIZE)
  , chStimToMonitorR(FIFO_SIZE) 
  , chStimToMonitorG(FIFO_SIZE)
  , chStimToMonitorB(FIFO_SIZE)
  , chSubRToMonitor(FIFO_SIZE)
  , chSubGToMonitor(FIFO_SIZE)
  , chSubBToMonitor(FIFO_SIZE)
  , chUpRToMonitor(FIFO_SIZE)
  , chUpGToMonitor(FIFO_SIZE)
  , chUpBToMonitor(FIFO_SIZE)
  , chPaethRToMonitor(FIFO_SIZE)
  , chPaethGToMonitor(FIFO_SIZE)
  , chPaethBToMonitor(FIFO_SIZE)
  , stimulus("stimulus")
  , subR("subR")
  , upR("upR")
  , paethR("paethR")
  , subG("subG")
  , upG("upG")
  , paethG("paethG")
  , subB("subB")
  , upB("upB")
  , paethB("paethB")
  , monitor("monitor")
{
  // no thread here
}

void Top::before_end_of_elaboration()
{
  stimulus.poutr1.bind(chStimToSubR);
  stimulus.poutr2.bind(chStimToUpR);
  stimulus.poutr3.bind(chStimToPaethR);
  subR.PinIn.bind(chStimToSubR);
  upR.PinIn.bind(chStimToUpR);
  paethR.PinIn.bind(chStimToPaethR);
  stimulus.poutg1.bind(chStimToSubG);
  stimulus.poutg2.bind(chStimToUpG);
  stimulus.poutg3.bind(chStimToPaethG);
  subG.PinIn.bind(chStimToSubG);
  upG.PinIn.bind(chStimToUpG);
  paethG.PinIn.bind(chStimToPaethG);
  stimulus.poutb1.bind(chStimToSubB);
  stimulus.poutb2.bind(chStimToUpB);
  stimulus.poutb3.bind(chStimToPaethB);
  subB.PinIn.bind(chStimToSubB);
  upB.PinIn.bind(chStimToUpB);
  paethB.PinIn.bind(chStimToPaethB);
  
  subR.PinOut.bind(chSubRToMonitor);
  upR.PinOut.bind(chUpRToMonitor);
  paethR.PinOut.bind(chPaethRToMonitor);
  monitor.PortSubR.bind(chSubRToMonitor);
  monitor.PortUpR.bind(chUpRToMonitor);
  monitor.PortPaethR.bind(chPaethRToMonitor);

  subG.PinOut.bind(chSubGToMonitor);
  upG.PinOut.bind(chUpGToMonitor);
  paethG.PinOut.bind(chPaethGToMonitor);
  monitor.PortSubG.bind(chSubGToMonitor);
  monitor.PortUpG.bind(chUpGToMonitor);
  monitor.PortPaethG.bind(chPaethGToMonitor);

  subB.PinOut.bind(chSubBToMonitor);
  upB.PinOut.bind(chUpBToMonitor);
  paethB.PinOut.bind(chPaethBToMonitor);
  monitor.PortSubB.bind(chSubBToMonitor);
  monitor.PortUpB.bind(chUpBToMonitor);
  monitor.PortPaethB.bind(chPaethBToMonitor);
  
  stimulus.poutr4.bind(chStimToMonitorR);
  stimulus.poutg4.bind(chStimToMonitorG);
  stimulus.poutb4.bind(chStimToMonitorB);
  monitor.PortR.bind(chStimToMonitorR);
  monitor.PortG.bind(chStimToMonitorG);
  monitor.PortB.bind(chStimToMonitorB);
 
 
}

Top top("top");

int sc_main(int argc, char* argv[])
{
  TIME_RESOLUTION();

#if VERBOSE
  PRINT_TIME();
  PRINT_NAME(__FUNCTION__);
  printf("PNG encoder starts.\n");
  //printf("number %d",top.stimulus.output_blocks[2].blkCount);
  //printf("number %d",top.stimulus.Rows.data);
#endif

  if (argc == 3)
  { top.stimulus.fNameIn = argv[1];
    //top.monitor.fNameOut = argv[2];
  }
  else if (argc == 2)
  { top.stimulus.fNameIn = argv[1];
    //top.monitor.fNameOut = IMAGE_FILE_OUT;
  }
  else
  { top.stimulus.fNameIn = IMAGE_FILE_IN;
    //top.monitor.fNameOut = IMAGE_FILE_OUT;
  }
#if VERBOSE
  PRINT_TIME();
  PRINT_NAME(__FUNCTION__);
  printf("encoding image \"%s\" into ",
	top.stimulus.fNameIn);
#endif

  sc_start();

#if VERBOSE
  PRINT_TIME();
  PRINT_NAME(__FUNCTION__);
  printf("PNG encoder done.\n");
#endif
  return 0;
}

// EOF
