# arch ?= x86_64
# kernel := build/kernel-$(arch).bin
# iso := build/os-$(arch).iso
#
# linker_script := src/arch/$(arch)/linker.ld
# grub_cfg := src/arch/$(arch)/grub.cfg
# assembly_source_files := $(wildcard src/arch/$(arch)/*.asm)
# assembly_object_files := $(patsubst src/arch/$(arch)/%.asm, \
# 	build/arch/$(arch)/%.o, $(assembly_source_files))
#
# .PHONY: all clean run iso
#
# all: $(kernel)
#
# clean:
# 	@rm -r build
#
# run: $(iso)
# 	@qemu-system-x86_64 -cdrom $(iso)
#
# iso: $(iso)
#
# $(iso): $(kernel) $(grub_cfg)
# 	@mkdir -p build/isofiles/boot/grub
# 	@cp $(kernel) build/isofiles/boot/kernel.bin
# 	@cp $(grub_cfg) build/isofiles/boot/grub
# 	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
# 	@rm -r build/isofiles
#
# $(kernel): $(assembly_object_files) $(linker_script)
# 	@ld -n -T $(linker_script) -o $(kernel) $(assembly_object_files)
#
# # compile assembly files
# build/arch/$(arch)/%.o: src/arch/$(arch)/%.asm
# 	@mkdir -p $(shell dirname $@)
# 	@nasm -felf64 $< -o $@


GCCPARAMS = -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
NASMPARAMS = -felf64
grub_cfg := grub.cfg
objects = multiboot_header.o boot.o

%.o: %.cpp
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.asm
	nasm $(NASMPARAMS) $< -o $@

clean :
	rm -r build

mykernel.bin: linker.ld $(objects)
	ld -n -T $< -o $@ $(objects)

mykernel.iso: mykernel.bin
	mkdir -p build/isofiles/boot/grub
	cp $< build/isofiles/boot
	cp $(grub_cfg) build/isofiles/boot/grub
	# grub-mkrescue --output=$@ iso
	grub-mkrescue -o $@ $(grub_cfg) build/isofiles 2> /dev/null
	# rm -r build/isofiles

run: mykernel.iso
	qemu-system-x86_64 -cdrom mykernel.iso -m 512
