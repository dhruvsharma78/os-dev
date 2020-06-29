DEFAULT_HOST  := $(shell ../scripts/default-host.sh)
HST           ?= $(DEFAULT_HOST)
HOSTARCH      := $(shell ../scripts/target-triplet-to-arch.sh $(HST))

CFLAGS        ?= -O2 -g
CPPFLAGS      ?=
LDFLAGS       ?=
LIBS          ?=

DEST_DIR      ?=
PREFIX        ?= /usr/local
EXEC_PREFIX   ?= $(PREFIX)
BOOT_DIR      ?= $(EXEC_PREFIX)/boot
INCLUDE_DIR   ?= $(PREFIX)/include

CFLAGS        := $(CFLAGS) -ffreestanding -Wall -Wextra -Werror
CPPFLAGS      := $(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS       := $(LD_FLAGS)
LIBS          := $(LIBS) -nostdlib -lk -lgcc

ARCH_DIR      := arch/$(HOSTARCH)

include $(ARCH_DIR)/make.config

CFLAGS        := $(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS      := $(CPPFLAGS) $(ARCH_CPPFLAGS)
LDFLAGS       := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS          := $(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS = \
			  $(KERNEL_ARCH_OBJS) \
			  kernel.o

OBJS = \
	   $(ARCH_DIR)/crti.o \
	   $(ARCH_DIR)/crtbegin.o \
	   $(KERNEL_OBJS) \
	   $(ARCH_DIR)/crtend.o \
	   $(ARCH_DIR)/crtn.o \

LINK_LIST = \
			$(LDFLAGS) \
			$(ARCH_DIR)/crti.o \
			$(ARCH_DIR)/crtbegin.o \
			$(KERNEL_OBJS) \
			$(LIBS) \
			$(ARCH_DIR)/crtend.o \
			$(ARCH_DIR)/crtn.o \

.SUFFIXES: .o .c .S

.PHONY: all
all: coffee.kernel

coffee.kernel: $(OBJS) $(ARCH_DIR)/linker.ld
	$(CC) -T $(ARCH_DIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	$(GRUB_FILE_TOOL) --is-x86-multiboot coffee.kernel

$(ARCH_DIR)/crtbegin.o $(ARCH_DIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.PHONY: clean
clean:
	rm -f coffee.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

.PHONE: install install-headers install-kernel

install: install-headers install-kernel

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	CP_FLAG=-p
else
	CP_FLAG=--preserve=timestamps
endif

install-headers:
	mkdir -p $(DEST_DIR)$(INCLUDE_DIR)
	cp -R $(CPFLAG) include/. $(DEST_DIR)$(INCLUDE_DIR)/.

install-kernel: coffee.kernel
	mkdir -p $(DEST_DIR)$(BOOT_DIR)
	cp coffee.kernel $(DEST_DIR)$(BOOT_DIR)

-include $(OBJS:.o=.d)
