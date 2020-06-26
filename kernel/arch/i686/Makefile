
default: boot

.PHONY: boot
boot: boot/obj/boot.o

boot/obj/boot.o: boot/boot.S
	@mkdir -p boot/obj
	$(AS) boot/boot.S -o boot/obj/boot.o

clean:
	rm -rf boot/obj
