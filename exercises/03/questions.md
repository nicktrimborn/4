# TIE-50307 - Exercise 03 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- Understand and debug a typical LKM (typically documentation is lacking)
- Modify the LKM module code to function as intended, and to pass an automated test script
- 
## 2. Where is the `evil-tests` script installed inside the image? Where is the accompanying data installed? Describe how this is set up in Yocto.
- evil-tests is located in /opt/evil-tests/sbin/evil-tests.sh
- data.txt is located in /opt/evil-tests/share/data.txt
- The tests recipe contains the files to install (evil-tests.sh and data.txt)
- evil-tests.bb contains the paths to install the files for evil-tests
- the "recipies-core" recipe contains the core-image-minimal.bbappend file which ensures that the evil-mod and evil-tests recipes are appended to core-image-minimal recipe.
- the build/bblayers.conf is processed to include the meta-tie50307 in the build process and ensure the files end up inside the image

## 3. How are the LKM and `evil-tests` added to `core-image-minimal`? Briefly describe what sets apart the `evil-tests` recipe compared with most recipes included in `meta-groupXX`, `meta-pynq`, `meta-xilinx` and `poky`.

## 4. How many buffers does the `evil` LKM use? List their names, their size and their purpose. How is their memory allocated?

## 5. How are user-input strings stored inside the module? How does the module iterate over this list? What's the loop end condition?

## 6. What is the path for the `evil` LKM's sysfs entry? How is it determined? How is it mapped to the module functionality?

## 7. What bugs did you find/fix? Categorize them and briefly describe each matching *category* (what's the *impact* of each *category*? How common do you *think* it is?)

## 8. What are out-of-bounds accesses and stack overflows? Are they relevant for this exercise? What could be the consequences of such defects in a LKM?

## 9. Feedback (what was difficult? what was easy? how would you improve it?)
