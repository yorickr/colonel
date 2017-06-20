#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/colonel.kernel isodir/boot/colonel.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "colonel" {
	multiboot /boot/colonel.kernel
}
EOF
grub-mkrescue -o colonel.iso isodir
