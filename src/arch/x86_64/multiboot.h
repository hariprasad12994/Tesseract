#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include "types.h"
#include "memory_map.h"

#define MULTIBOOTMAGIC 0x2BADB002

class multibootInfo{
private:
  enum multibootInformationFlag{
    MEMORY                   = 1 << 0,
    BOOT_DEVICE              = 1 << 1,
    COMMAND_LINE             = 1 << 2,
    MODULES                  = 1 << 3,
    AOUT_SYMBOL_TABLE        = 1 << 4, // These two are
    ELF_SECTION_HEADER_TABLE = 1 << 5, // mutually exclusive.
    MEMORY_MAP               = 1 << 6,
    DRIVE_INFO               = 1 << 7,
    CONFIG_TABLE             = 1 << 8,
    BOOTLOADER_NAME          = 1 << 9,
    APM_TABLE                = 1 << 10,
    VIDEO_INFO               = 1 << 11
  };

  struct multibootInfoStruct{
    /* Multiboot info version number */
    uint32_t flags;

    /* Available memory from BIOS */
    uint32_t mem_lower;
    uint32_t mem_upper;

    /* "root" partition */
    uint32_t boot_device;

    /* Kernel command line */
    uint32_t cmdline;

    /* Boot-Module list */
    uint32_t mods_count;
    uint32_t mods_addr;

    union{
      multibootAoutSymbolTable aout_sym;
      multibootElfSectionHeaderTable elf_sec;
    } u;

    /* Memory Mapping buffer */
    uint32_t mmap_length;
    uint32_t mmap_addr;

    /* Drive Info buffer */
    uint32_t drives_length;
    uint32_t drives_addr;

    /* ROM configuration table */
    uint32_t config_table;

    /* Boot Loader Name */
    uint32_t boot_loader_name;

    /* APM table */
    uint32_t apm_table;

    /* Video */
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;

    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    #define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED 0
    #define MULTIBOOT_FRAMEBUFFER_TYPE_RGB     1
    #define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
    uint8_t framebuffer_type;
    union{
      struct{
         uint32_t framebuffer_palette_addr;
         uint16_t framebuffer_palette_num_colors;
      };
    struct{
       uint8_t framebuffer_red_field_position;
       uint8_t framebuffer_red_mask_size;
       uint8_t framebuffer_green_fimemoryMapeld_position;
       uint8_t framebuffer_green_mask_size;
       uint8_t framebuffer_blue_field_position;
       uint8_t framebuffer_blue_mask_size;
    };
    };
  };

  multibootInfoStruct* ptrToMultibootInfoBlock;
  bool checkFlagAvailability(multibootInformationFlag flagType);
  void parseMultiboot();
  void panic();

public:
  multibootInfo(uint32_t ptrToMultibootInfoBlock);
  char* bootloaderName;
  multibootMemoryMap* memoryMap;
  multibootElfSectionHeaderTable* elfSectionHeaderTable;
};

#endif
