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
INCLUDE_DIR   ?= $(PREFIX)/include
LIB_DIR       ?= $(PREFIX)/lib

CFLAGS        := $(CFLAGS) -ffreestanding -Wall -Wextra -Werror
CPPFLAGS      := $(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS   := $(CFLAGS)
LIBK_CPPFLAGS := $(CPPFLAGS) -D__is_libk

ARCH_DIR      := arch/$(HOSTARCH)

include $(ARCH_DIR)/make.config

CFLAGS        := $(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS      := $(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS   := $(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS := $(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREE_OBJS := \
			$(ARCH_HOSTED_OBJS) \
			stdio/putchar.o \
			stdio/printf.o \
			stdio/puts.o \
			stdlib/abort.o \
			string/memcmp.o \
			string/memcpy.o \
			string/memmove.o \
			string/memset.o \
			string/strlen.o \

HOSTED_OBJS := \
	$(ARCH_FREE_OBJS) \

OBJS := \
	$(FREE_OBJS) \
	$(HOSTED_OBJS) \

LIBK_OBJS := $(FREE_OBJS:.o=.libk.o)

BINARIES := libk.a # libc.a # No libc rn

.SUFFIXES: .o .libk.o .c .S

.PHONY: all
all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)
 
.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.PHONY: clean
clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

.PHONY: install
install: install-headers install-libs

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	CP_FLAG=-p
else
	CP_FLAG=--preserve=timestamps
endif

.PHONY: install-headers
install-headers:
	mkdir -p $(DEST_DIR)$(INCLUDE_DIR)
	cp -R $(CP_FLAG) include/. $(DEST_DIR)$(INCLUDE_DIR)/.

.PHONY: install-libs
install-libs: $(BINARIES)
	mkdir -p $(DEST_DIR)$(LIB_DIR)
	cp $(BINARIES) $(DEST_DIR)$(LIB_DIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
