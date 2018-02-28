arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso

GCCPARAMS = -fno-use-cxa-atexit -std=c++11 -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source_files := $(wildcard src/arch/$(arch)/*.asm)
assembly_object_files := $(patsubst src/arch/$(arch)/%.asm, \
	build/arch/$(arch)/%.o, $(assembly_source_files))
cpp_source_files := $(wildcard src/arch/$(arch)/*.cpp)
cpp_object_files := $(patsubst src/arch/$(arch)/%.cpp, \
	build/arch/$(arch)/%.o, $(cpp_source_files))

.PHONY: all clean run iso

all: $(kernel)

clean:
	@rm -r build

install: $(kernel)
	sudo cp $< /boot/kernel.bin

run: $(iso)
	@qemu-system-x86_64 $(iso) -m 4M -monitor stdio

debug: $(iso)
	@qemu-system-x86_64 -s -S $(iso) -m 4M -monitor stdio

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles

$(kernel): $(assembly_object_files) $(cpp_object_files) $(linker_script)
	@ld -n -T $(linker_script) -o $(kernel) $(assembly_object_files) $(cpp_object_files)

assembly_src = src/arch/$(arch)/%.asm
cpp_src = src/arch/$(arch)/%.cpp

# compile assembly files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@

build/arch/$(arch)/%.o: src/arch/$(arch)/%.cpp
	@gcc $(GCCPARAMS) -c -g -o $@ $<
