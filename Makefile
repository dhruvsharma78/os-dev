
ARCH   ?= i686

ifeq ($(ARCH), i686)
	CC           = i686-elf-gcc
	AS           = i686-elf-as
	GRUB_MKR_BIN = i386-elf-grub-mkrescue
	QEMU_BIN     = qemu-system-i386
else
	$(error This architecture is not recognized/supported)
endif

LDFLAGS = -lgcc -ffreestanding -O2 -nostdlib -Wall -Wextra -Werror
CFLAGS  = -std=gnu99 -ffreestanding -nostdlib -Wall -Wextra -Werror -pedantic -O2

export

default: all

all: kernel $(ARCH) build

.PHONY: kernel $(ARCH) build

kernel:
	@echo "Building kernel..."
	@$(MAKE) -C kernel

$(ARCH): kernel
	@echo "Building OS for: $(ARCH)..."
	@$(MAKE) -C kernel/arch/$@

build: $(ARCH)
	@mkdir -p build/$(ARCH)/boot
	@cp -r kernel/arch/$(ARCH)/boot/grub build/$(ARCH)/boot
	$(CC) $(LDFLAGS) -T kernel/linker.ld -o build/$(ARCH)/boot/os.bin kernel/kernel.o kernel/arch/$(ARCH)/boot/obj/boot.o

makeiso: all
	@echo "Making ISO for: $(ARCH)..."
	$(GRUB_MKR_BIN) -o build/$(ARCH)/os.iso build/$(ARCH)

run: all makeiso 
	$(QEMU_BIN) -cdrom build/$(ARCH)/os.iso

clean:
	@$(MAKE) -C kernel clean
	@$(MAKE) -C kernel/arch/$(ARCH) clean

cleanbuilds:
	rm -rf build
