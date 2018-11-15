# Introduction

In this exercise we will resume the driver development started in EX04, to support a custom device, in this case represented by an FPGA IP block that can be setup to generate interrupt requests (IRQs).

We already improved a lot the quality of the driver in last exercise: this week we will be adding a character device and experiment with interaction between regular userland applications and the driver.


To speed up the process, rather than starting from scratch, you are going to work on a stub driver implementation that provides a structure but leaves to be implemented the core functionality.

Your task, in short, is to fill the stub with the right functionality by resolving every FIXME and TODO included in the source files.

The kernel module comes in a the `meta-tie50307` Yocto layer, under `recipes-kernel/irqgen-mod`.

The spec document for the IRQ Generator module is included in the same folder where you found these instructions and contains important informations you will need to solve this exercise.

**NOTE:** you will be using the `bitstream` you generated in EX05, which should now be feature complete w.r.t. the IRQ Generator Spec.

**The guideline in *completing* the *stub* module source code is to limit yourself to fix only the items highlighted by FIXME and TODO comments. While you progress, you should remove the FIXME/TODO commets to keep track of your progress. Don't add new features and avoid any major redesign.**

As usual, rather than providing step-by-step instructions, we provide a list of reading materials and resources you should familiarize with in order to solve the task at hand.

We will use the same Ubuntu virtual machine (which already includes all the required prerequisites to successfully build the Yocto Project).
It's located in `C:\Work\TIE-50307-course-vm` in TC219 workstations.
The username and (very secure) password for the VM account are: `student`/`student`.

**WARNING**: be aware that **files on the VM will be erased at each reboot**, commit and push your work to your remote repository (or save your important files to an external drive) before rebooting the VM.

**REMINDER**: we strongly recommend you to add & commit your changes after each step (or even more frequently): saving your work and being able to revisit what you did and in what order is way more important than having a tidy git history. We are not going to evaluate your weekly exercises on the basis of the git history, but if we were to, several micro-commits would definitely look better than a single macro-commit pushing in one go all the changes and results of your task.


# Resources and reading material

- Resuming your work...
  - [course_upstream repo][course_upstream] *(instructions on how to clone your personal repository, new instructions and materials for the exercise of this week)*
  - [Git Submodules Manual][Git_Submodules]
  - [**Lectures on Moodle**][moodle.tie50307] *(check the presentations about device-tree and platform device drivers)*
  - [meta-pynq layer repository][meta-pynq]
- Yocto-related resources
  - [Yocto SDK Manual][yocto-sdk-manual] **(very important!!)**
  - [Yocto Development Manual][YoctoDEVMAN:cha4]
  - [BitBake User Manual][bitbakeUSRMAN]
  - [Yocto Reference Manual][YoctoREFMAN]
  - [*Embedded Linux Systems With the Yocto Project* (2016)][book:YOCTO:2016]
  - [Yocto Project Linux Kernel Dev Manual (C#2.10: *Working with Out-of-Tree Modules*)][YoctoKDEVMAN:sec2.10]
- Developing Kernel Drivers & Linux Internals
  - [***linux-insides***][book:linux-insides] *(A book-in-progress about the linux kernel and its insides.)*
  - [***Linux device drivers development*** (2017)][book:LDDD:2017]
  - [***Linux Device Drivers (3rd ed.)*** (2005)][book:LDD3:2005]
  - [*Linux Kernel Development (3rd ed.)* (2010)][book:LKD:2010]
  - [ERRNO manpage, for selecting proper error codes][man:3:errno]

# Checklist

- [ ] preparations to resume your work
  - [ ] clone your repository, <u>with its submodules and LFS data!</u>
    - **Hint**: check the updated instructions in the main README of [course_upstream]
  - [ ] pull the changes published in [course_upstream] using the provided script
  - [ ] remember to specify the path for the proper `build` folder when sourcing the Yocto script for setting up the build environment
  - [ ] build `core-image-minimal` once again, to verify that everything works.
- [ ] remember to write the `bitstream` file from EX05 to the microSD root.
- [ ] locate the source files for the module
- [ ] add yourselves as additional authors
- Reiterate the following **until all the required functionality has been implemented and tested**:
  - [ ] boot the PYNQ board, login to the console (usr:`root`, no passwd), load the `irqgen`/`irqgen_dbg` module and test its functionality (load, unload, error handling, check and experiment with `/sys/kernel/irqgen/*`)
  - [ ] edit (**only!!!**) `irqgen_main.c`, `irqgen.h`, `irqgen_sysfs.c` and `irqgen_cdev.c`
  - [ ] rebuild `core-image-minimal` and deploy the updated images to the microSD card
  - [ ] use the `sysfs` interface to generate interrupts while a background process reads from `/dev/irqgen`
- [ ] Use the [Yocto SDK for the PYNQ board][../07/yocto_sdk.md] to compile your `statistics` application according to [specification][../07/statistics_app/specs.md]
- [ ] <u>**remeber to push all your commits to your remote repository**</u>
- [ ] demonstrate to the TA
- [ ] <u>remember to recover your microSD card before leaving</u>
- [ ] edit `exercises/06/questions.md` to provide your answers


[course_upstream]: https://course-gitlab.tut.fi/tie-50307-rt-systems-2018/course_upstream
[Git_Submodules]: https://git-scm.com/book/en/v2/Git-Tools-Submodules
[YoctoQS]: https://www.yoctoproject.org/docs/2.4.3/yocto-project-qs/yocto-project-qs.html
[moodle.tie50307]: https://moodle2.tut.fi/course/view.php?id=11830
[YoctoDEVMAN:cha4]: https://www.yoctoproject.org/docs/2.4.3/dev-manual/dev-manual.html#extendpoky
[YoctoREFMAN]: https://www.yoctoproject.org/docs/2.4.3/ref-manual/ref-manual.html
[YoctoKDEVMAN:sec2.10]: https://www.yoctoproject.org/docs/2.4.3/kernel-dev/kernel-dev.html#working-with-out-of-tree-modules
[bitbakeUSRMAN]: https://www.yoctoproject.org/docs/2.4.3/bitbake-user-manual/bitbake-user-manual.html
[PYNQ-Z1-REFMAN]: https://reference.digilentinc.com/_media/reference/programmable-logic/pynq-z1/pynq-rm.pdf
[meta-pynq]: https://course-gitlab.tut.fi/tie-50307-rt-systems-2018/meta-pynq
[devtree-spec]: https://github.com/devicetree-org/devicetree-specification/releases/tag/v0.2
[man:3:errno]: http://man7.org/linux/man-pages/man3/errno.3.html
[book:LDDD:2017]: https://tut.finna.fi/Record/tutcat.256856
[book:LDD3:2005]: https://tut.finna.fi/Record/tutcat.256859
[book:LKD:2010]: https://tut.finna.fi/Record/tutcat.256860
[book:YOCTO:2016]: https://tut.finna.fi/Record/tutcat.256857
[book:linux-insides]: https://0xax.gitbooks.io/linux-insides/content/index.html
[yocto-sdk-manual]: https://www.yoctoproject.org/docs/2.4.3/sdk-manual/sdk-manual.html
[sdk-archive]: ../../build/tmp/deploy/sdk/poky-glibc-x86_64-core-image-minimal-cortexa9hf-neon-toolchain-2.4.3.sh
