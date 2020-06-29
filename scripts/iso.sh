#!/bin/sh
set -e

. ./config.sh

mkdir -p ../isodir/boot/

cp ../sysroot/boot/coffee.kernel ../isodir/boot/coffee.kernel
cp -r ../kernel/arch/"$(./target-triplet-to-arch.sh $HST)"/boot/grub  ../isodir/boot/grub
"$GRUB_MKRESCUE_TOOL" -o ../coffee.iso ../isodir
