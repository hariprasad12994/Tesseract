#include "types.h"
#include "video.h"
#include "multiboot.h"
#include "lib.h"

extern "C" void kernelMain(uint32_t multiboot_structure,
                           uint32_t multiBootMagicNumber){
  primitiveVGA vga((uint8_t)Green, (uint8_t)Black);
  vga.clearScreen();
  vga.print("[] Tesseract v0.1\n");
  multibootInfo Info(multiboot_structure);

  while(1);
}
