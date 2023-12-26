#!/bin/bash

#sudo apt-get update
#sudo apt-get install libusb-1.0.0-dev libhidapi-dev libftdi-dev
#echo "[INFO]: Configuration Commencing\n[INFO]: Run from 'openocd/openocd/build/configure' for intended results"

$PWD/../configure \
--enable-dummy \
--enable-ftdi \
--enable-jlink \
--enable-stlink \
--enable-ft232r \
--enable-cmsis-dap \
--enable-cmsis-dap-v2 \
--enable-usb-blaster \
--enable-usb-blaster-2 \
--enable-bcm2835gpio \
--enable-sysfsgpio \

#echo "[INFO]: Configuration Complete\n[INFO]: Run 'make' to start building the kit"

exit 0
