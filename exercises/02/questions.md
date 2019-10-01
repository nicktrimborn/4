# TIE-50307 - Exercise 02 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- to create a new yocto layer contining a helloworld recipe that is built into a Loadable kernel module LKM 
- This appended to the core-image-minimal image using the OpenEmbedded build system
- The hello world LKM can be loaded and unloaded from the Linux with modprob command and customised to accept parameters and includes meta data about the module
## 2. What is a Yocto layer? What are the essential requirements to correctly define a new one?
Yocto layer is a logical collection of metadata in the form of recipies.
It requires:
- An appropriatly named folder, usually with the "meta-" prefix
- Inside this a directory with conf/layer.conf file defining layer recipies paths, priority etc
- An entry in the /build/conf/bblayers.conf with the layer path
- Folder containing recipies
    - this folder the recipe .bb file
    - a folder containing source files and make file
    - core-image-minimal.bbappend file in this case where Metadata of hello world layer is appended to another recipe ie.        core-image-minimal to make it acceble when booting the core image
- README File
- A licent File

## 3. What priority did you assign to your layer? How and why?
    Priority 6

## 4. What does LKM stand for (in the context of this exercise)? What does it mean and what are the characteristics of a LKM? What's the alternative?
    Linux kernel module - is a mechanism for adding code to, or removing code from, the Linux kernel at run time.
## 5. What does Out-of-Tree Module mean? What's the alternative and what are the differences?

## 6. How did you define the module metadata? How does it work?
Defined in the module source c file.  linux/modules.h defines macros that provide information on the module.  Not used by the kernel itself

## 7. How is the module built? How does it get installed inside `core-image-minimal`?
- Define a new meta-layer containing a recipes.
- Define a layer.conf file which defines the layer and dependacies
- Create recipe core folder containing core-image-minimal.bbappend file which points to recipe - To be appended to core image. (IMAGE_INSTALL_append = "hello")
- Each recipe contains a .bb file which defines the recipe
- Add new layer path to build/conf/bblayers.conf
- Bitbake then builds and appends the new recipe to core-image-minimal

## 8. What is the path for the `sysfs` entry for the module? List and explain its contents.
/sys/module/hello.  Contains:
coresize:
holders
initsize
initstate
notes
parameters : contains defined module_param variables
refcnt
sections
srcversion
taint
uevent
version : Version module meta data
## 9. Feedback (what was difficult? what was easy? how would you improve it?)
was a little difficult as info was hard to find,  help from course assistants required