#!/bin/sh
cd /media/student/056C-3FA9
#rm -R .
echo "Copying files"
cp -L ~/4/build/tmp/deploy/images/pynq/boot.bin .
cp -L ~/4/build/tmp/deploy/images/pynq/uImage .
cp -L ~/4/build/tmp/deploy/images/pynq/u-boot.img .
cp -L ~/4/build/tmp/deploy/images/pynq/core-image-minimal-pynq.cpio.gz.u-boot .
cp -L ~/4/build/tmp/deploy/images/pynq/uEnv.txt .
cp -L ~/4/build/tmp/deploy/images/pynq/devicetree.dtb .
echo "Files Copied"

