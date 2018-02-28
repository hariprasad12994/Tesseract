#include "multiboot.h"
#include "video.h"
#include "lib.h"
#include "memory_map.h"

multibootInfo :: multibootInfo(uint32_t ptrToMultibootInfoBlock){
  this->ptrToMultibootInfoBlock = (multibootInfoStruct*)ptrToMultibootInfoBlock;
  multibootInfo :: parseMultiboot();
}

bool multibootInfo :: checkFlagAvailability(multibootInformationFlag flagType){
  return (flagType & (this->ptrToMultibootInfoBlock->flags));
}

void multibootInfo :: parseMultiboot(){
  // printf("Parsing multiboot structure....\n");
  if(multibootInfo :: checkFlagAvailability(BOOTLOADER_NAME)){
    // printf("Bootloader Name :");
    this->bootloaderName = ((char*)this->ptrToMultibootInfoBlock->boot_loader_name);
  }
  else{
    // Issue an error message, method of handling to be decided
  }

  if(multibootInfo :: checkFlagAvailability(MEMORY_MAP)){
    // printf("Memory map present\n");
    this->memoryMap = (multibootMemoryMap*)this->ptrToMultibootInfoBlock->mmap_addr;
  }
  else{
    // Issue an error message, method of handling to be decided
  }

  if(multibootInfo :: checkFlagAvailability(ELF_SECTION_HEADER_TABLE)){
    // printf("Elf section present\n");
    this->elfSectionHeaderTable = &(this->ptrToMultibootInfoBlock->u.elf_sec);
  }
  return;
}
