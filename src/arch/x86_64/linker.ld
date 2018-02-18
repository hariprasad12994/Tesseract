ENTRY(start) /* start is the entry point of the program */

SECTIONS {
  . = 1M; /* We don't want to load the kernel to e.g. 0x0
             because there are many special memory areas below the 1MB mark
             (for example the so-called VGA buffer at 0xb8000,
             that we use to print OK to the screen) */

  .boot :
  {
    /* ensure that the multiboot header is at the beginning */
    *(.multiboot_header)
  }

  .text :
  {
    /* all text sections are added here */
    *(.text*)
  }
}
