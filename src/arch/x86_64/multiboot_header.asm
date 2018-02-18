section .multiboot_header

; Our kernel just needs to indicate that it supports Multiboot 
; and every Multiboot-compliant bootloader can boot it.

header_start:         ; header start label
  dd 0xe85250d6       ; magic number for grub to detect the OS(multiboot 2)
  dd 0                ; architecture 0 (protected mode i386)
  dd header_end - header_start ; header length
  ; checksum
  dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))


  ; end tag
  dw 0 ; type
  dw 0 ; flags
  dd 8 ; size
header_end:
