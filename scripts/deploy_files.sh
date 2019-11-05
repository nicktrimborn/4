#!/bin/sh
SDCARD=/media/$USER/056C-3FA9
ID=056C-3FA9
# udisksctl mount -b $(mount | grep ${ID} | cut -d" "  -f1)
# udisksctl mount -b ${SDCARD}
#rm -R .
echo "Copying files"
# cp -L ~/4/exercises/04/bitstream ${SDCARD}
cp -L ~/4/exercises/05/bitstream ${SDCARD}
cp -L ~/4/build/tmp/deploy/images/pynq/boot.bin ${SDCARD}
cp -L ~/4/build/tmp/deploy/images/pynq/uImage ${SDCARD}
cp -L ~/4/build/tmp/deploy/images/pynq/u-boot.img ${SDCARD}
cp -L ~/4/build/tmp/deploy/images/pynq/core-image-minimal-pynq.cpio.gz.u-boot ${SDCARD}
cp -L ~/4/build/tmp/deploy/images/pynq/uEnv.txt ${SDCARD}
cp -L ~/4/build/tmp/deploy/images/pynq/devicetree.dtb ${SDCARD}
echo "Files Copied"
cd ~/4/
echo "Unmounting"
udisksctl unmount -b $(mount | grep ${ID}  | cut -d" "  -f1)

