#include "types.h"
#include "video.h"

void checkMultiboot(){

}

extern "C" void kernelMain(){
  videoHandler handler((uint8_t)Black,(uint8_t)Cyan);
  handler.clearScreen();
  handler.printToScreen("booted");
  handler.printToScreen("\n");
  handler.printToScreen("initial screen tests - VGA mode\n");
  while(1);
}
