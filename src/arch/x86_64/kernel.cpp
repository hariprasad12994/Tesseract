#include "types.h"
#include "video.h"
#include "multiboot.h"
#include "lib.h"

extern "C" void kernelMain(uint32_t multiboot_structure,
                           uint32_t multiBootMagicNumber){
  multibootInfo Info(multiboot_structure);

  primitiveVGA vga((uint8_t)Cyan, (uint8_t)Black);
  vga.clearScreen();
  vga.print("Hello World\n");
  vga.print("Bootloader:%s\n",Info.bootloaderName);

  while(1);
}
