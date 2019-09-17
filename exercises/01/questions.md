# Exercise 01 - Q&A

## 1. What did you accomplish in this exercise?
Learned how to config the virtual machine with ssh and git profile
Learned how to add git sub modules to student repository
Learned how to configure the yocto build evironment for the pynq board and corresponding config files
Built and booted the pynq board using poky built using bitbake

## 2. How does Yocto recognize that the target machine "pynq" is supported?
set MACHINE ?= "pynq"
added paths to pynq and xilinx bsp directories to the bblayers.conf

## 3. Where do you find the device-tree source code for the PYNQ board?
device tree was located in meta-pynq

## 4. What is the priority of the PYNQ support layer?
BBFILE_PRIORITY_pynq = "5"

## 5. What additional applications are installed to the `core-image-minimal` target in the PYNQ support layer?
busybox
packagegroups