#ifndef _MEMORY_MAP_H_
#define _MEMORY_MAP_H_

enum memoryType{
  MULTIBOOT_MEMORY_AVAILABLE = 1,
  MULTIBOOT_MEMORY_RESERVED,
  MULTIBOOT_MEMORY_ACPI_RECLAIMABLE,
  MULTIBOOT_MEMORY_NVS,
  MULTIBOOT_MEMORY_BADRAM,
};

struct multibootMemoryMap{
  uint32_t size;
  uint64_t addr;
  uint64_t len;
  #define MULTIBOOT_MEMORY_AVAILABLE              1
  #define MULTIBOOT_MEMORY_RESERVED               2
  #define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
  #define MULTIBOOT_MEMORY_NVS                    4
  #define MULTIBOOT_MEMORY_BADRAM                 5
  uint32_t type;
} __attribute__((packed));

/* The symbol table for a.out. */
struct multibootAoutSymbolTable{
  uint32_t tabsize;
  uint32_t strsize;
  uint32_t addr;
  uint32_t reserved;
};

/* The section header table for ELF. */
struct multibootElfSectionHeaderTable{
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
};

#endif
