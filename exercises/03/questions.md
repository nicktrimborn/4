# TIE-50307 - Exercise 03 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- Understand and debug a typical LKM (typically documentation is lacking)
- Fix Bugs in the LKM module code to function as intended, and to pass an automated test script

## 2. Where is the `evil-tests` script installed inside the image? Where is the accompanying data installed? Describe how this is set up in Yocto.
- evil-tests.sh is located in /opt/evil-tests/sbin/evil-tests.sh
- data.txt is located in /opt/evil-tests/share/data.txt
- the files themselves are located in meta-tie50307/Recipes-tests/evil-tests/files
- The tests recipe contains the paths to the files to install (evil-tests.sh and data.txt)
- evil-tests.bb contains the instructions to install the files for evil-tests in the do_install() method

## 3. How are the LKM and `evil-tests` added to `core-image-minimal`? Briefly describe what sets apart the `evil-tests` recipe compared with most recipes included in `meta-groupXX`, `meta-pynq`, `meta-xilinx` and `poky`.
- the "recipies-core" recipe contains the core-image-minimal.bbappend file which ensures that the evil-mod and evil-tests recipes are appended to core-image-minimal recipe.
- the build/bblayers.conf is processed to include the meta-tie50307 in the build process and ensure the files end up inside the image
- evil-tests does not require any building and does not inherit "module" to produce an LKM
- Other packages provide BSP packages, configure the kernel or expand the core image with different packages.  evil test just installs a test script and files that are used at run runtime.


## 4. How many buffers does the `evil` LKM use? List their names, their size and their purpose. How is their memory allocated?
- evil has 2 buffers
- input_buf:
    - static assigned char array of size 1000 bytes (char = 1 byte)
    - buffers input to tasklet which stores data to data_storage
- data_storage:
    - used for reading/writing data using sysfs
    - allocated using kmalloc (GFP_KERNEL)
    - Size (1 Page - PAGE_SIZE) - 4096 bytes

## 5. How are user-input strings stored inside the module? How does the module iterate over this list? What's the loop end condition?
- strings are stored inside data_storage with store_evil function which uses a tasklet to write to the data_storage buffer.
-  The tasklet recieves the buffered data from input_buf, and replaces 'a' with ' ' before storing the data in data_storage using sprintf
- successive writes append strings to this data_storage array based on bytes_stored global variable
- show_evil function loops data_storage and writes to output buffer (buf) until sprinf return 0 to indicate end of string, reporting number of bytes read

## 6. What is the path for the `evil` LKM's sysfs entry? How is it determined? How is it mapped to the module functionality?
- /sys/kernel/evil_module/evil
- sysfs entry created with kobject_create_and_add("evil_module", kernel_kobj);
- evil file is created with sysfs_create_file(evil_kobj, &dev_attr_evil.attr)
- read/write functions are called show_evil and store_evil respectively and perform the required tasks
- these functions are specified in device_attribute dev_attr_evil and are called when read/write is requested 


## 7. What bugs did you find/fix? Categorize them and briefly describe each matching *category* (what's the *impact* of each *category*? How common do you *think* it is?)
Bugs:

Memory Management:\
    1) no memory allocated for tasklet - Serious: Segfault | uncommon: would cause segfault during development\
    2) evil_exit() tries to free tasklet memory before executing tasklet_kill - Serious: can cause kernel panic | common: easy mistake to make\
    3) evil_init() depending on errors, not all memory is free'd such as kfree(data_storage)
kobject_del(evil_kobj).  Memory should be free in the opposite order in which it was allocated - Moderate: Memory leaks | common: easy mistake to forget to free allocated memory\
    4) allocated , data_storage should be initialised to 0 to avoid undefined behaviour with memset.  input_buf should also be cleared between write calls Moderate: may lead unexpected behaviou | common: easy mistake to make when allocating memory and can be hard to debug as it may be intermittent

Buffer handling:\
    1) in show_evil() += used instead of = for sprintf return value  Serious: non functional code | uncommon: would cause errors during development\
    2) store_evil() function needs to check for buffer overflow of input_buf when storing user-input strings and return an error (-1) when overflow would occur - Serious: Segfault | common: would cause segfault only in overflow cases\

Permissions:\
    1) sysfs dev_attr_evil needs to be set to allow for r/w access (644 used) Serious: permmission denied | uncommon: would cause permission errors during development\


## 8. What are out-of-bounds accesses and stack overflows? Are they relevant for this exercise? What could be the consequences of such defects in a LKM?
- Out of bounds accesses are when we try access a memory location outside of the array(buffer) 
- Out of bounds accesses usually has "undefined behaviour". This might access some piece of memory already owned by the running process. undefined behavior, and can result in crashes or incorrect program output.
- Stack overflow occurs when the call stack pointer exceed the stack bounds. (Attempts an out of bound access) This is essentially a buffer overflow and results in crashing the running processes
- Unlike user mode, the kernel mode stack lives in directly mapped memory and is of a fixed size.  Stack overflow caused by an LKM module can lead to exceptions or system crashes and should be avoided.
- This is relevant as the input_buf is allocated on the stack char array and overflowing this buffer could lead to stack overflow issues described above.

## 9. Feedback (what was difficult? what was easy? how would you improve it?)
- had some difficulty due to heading down the wrong path when fixing bugs, overcomplicated things