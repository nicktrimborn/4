#!/bin/sh
cd /media/student/62E7-CD76
#rm -R .
cp -L ~/4/build/tmp/deploy/images/pynq/boot.bin .
cp -L ~/4/build/tmp/deploy/images/pynq/uImage .
cp -L ~/4/build/tmp/deploy/images/pynq/u-boot.img .
cp -L ~/4/build/tmp/deploy/images/pynq/core-image-minimal-pynq.cpio.gz.u-boot .
cp -L ~/4/build/tmp/deploy/images/pynq/uEnv.txt .
cp -L ~/4/build/tmp/deploy/images/pynq/devicetree.dtb .

