SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HST=${HST:-$(./default-host.sh)}

export AR=${HST}-ar
export AS=${HST}-as
export CC=${HST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOT_DIR=/boot
export LIB_DIR=$EXEC_PREFIX/lib
export INCLUDE_DIR=$PREFIX/include

export GRUB_FILE_TOOL=i386-elf-grub-file
export GRUB_MKRESCUE_TOOL=i386-elf-grub-mkrescue

export CFLAGS='-O2 -g'
export CPPFLAGS=''

export SYSROOT="$(dirname $(pwd))/sysroot"
export CC="$CC --sysroot=$SYSROOT"

if echo "$HST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDE_DIR"
fi
