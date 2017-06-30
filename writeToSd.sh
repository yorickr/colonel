#!/bin/bash

./clean && ./build.sh
cp kernel/kernel.img /run/media/imegumii/boot/kernel.img && sync
sudo umount /run/media/imegumii/*
