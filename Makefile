.PHONY: build clean default all iso run

all: default

default: build iso

build:
	@cd scripts && sh ./build.sh

clean:
	@cd scripts && sh ./clean.sh

iso: build
	@cd scripts && sh ./iso.sh

run: iso
	@cd scripts && sh ./qemu.sh
