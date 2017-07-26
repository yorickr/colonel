#!/bin/bash

sh ./clean.sh && sh ./build.sh
cp kernel/kernel.img /run/media/imegumii/boot/kernel.img && sync
md5sum kernel/kernel.img && md5sum /run/media/imegumii/boot/kernel.img
sudo umount /run/media/imegumii/*
