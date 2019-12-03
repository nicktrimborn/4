# TIE-50307 - Exercise 07 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
* Develop a Character device driver to interface with the custom IP-BLock
* This character device driver allows interaction with a user-space application
* The user application provides summary statistics of the interrupt counts, average latency, max latencies of the interrupts serviced by the Processing system from the IP block.  
* Metrics such as interrupt handled  count, average latency, and worst case latencyetc for each line are printed

## 2. What is a Character Device? How is it different from a Block Device?
Character devices are devices that transfers a streams of bytes directly from kernel to user space unbuffered and synchronous access. Character devices are represented in the kernel as instances of struct cdev
#### Character devices:
* Generally not addressable
* Character Device is a device whose driver communicates by sending and receiving single characters (bytes, octets)
* Provides data a character at a time in a sequential data stream

#### Block devices:
* Addressable in device-specified chunks called blocks and generally support seeking
* Block Device is a device whose driver communicates by sending entire blocks of data and can provide random access data

## 3. What design limits of the Ex6 version of `irqgen-mod` do we try to address adding a character device?
* The driver data structure in ex6 did not provide concurrent access protection.
* The character driver copies the data from kernel-space to user-space.  

## 4. What system calls are we implementing for the filesystem representation of our character device?
#### To create the character device we need to utilise the following:
* alloc_chrdev_region() - dynamically allocate a major and minor number from the system
* class_create() - Create a class for the device
* cdev_add() - add to the system the cdev for the allocated (major,minor)
* device_create() - used to add the "irqgen" node in the /dev/ filesystem

#### The following functions are implemented to support filesystem operations:
* open - first operation performed on device file
* release - invoked when file structure is released
* read - copying data from the kernel and user space

## 5. How does a device node differ from a regular file? What things are similar/identical?
#### Struct_inode
*  The kernel describes files as instances of struct inode (Not structure file) 
structure
* Struct_inode is a file system data structure and contains information relevant
to the OS. 
* It contains material that helps the OS find the underlying file structure (Pipe, 
directory, regular disk file block/character device file 

#### Struct file
* struct file structure is actually a higher level of file description that
represents an open file in the kernel and which relies on the lower
struct_inode
* It is used as generic structure that represent and open file and provices a set 
of functions related to methods one can perform on the underlying file
structure.
* Such methods are open, write , seek, read, select

#### Differences (device node vs regular file)
##### Device node:
* Correspond to resources that have already been allocated by the operating system Kernel
* Identified by a major number (device driver) and a minor number(devices), which are stored as part of the structure of a node
* Major number identifies the device driver and the minor number identifies a particular device (possibly out of many) that the driver controls, and is passed to the driver as an argument

##### Regular file:
* User read/writeable
* Supports various formats
* Kernel memory not allocated

#### Similarity
* Device nodes are accessed using standard system calls and treated like regular files

## 6. Which parts of our LKM code are potentially running in parallel? Which parts could interact in a conflicting way? Make a few concrete examples of conditions in which conflicts in concurrency may arise.
#### Parallel execution and conflicts
* Need to protect members of irqgen_data from concurrent access to protect the data integrity
* As interruts are generating intr_handled, total_handled, latencies, wp and rp are changing
* At the same time they are trying to be accessed in cdev read, and sysfs _show functions
* Need to use spinlocks to ensure access read/write sequence is not affected

#### specifically:
    u32 *intr_handled;
    u32 total_handled;
    struct latency_data *latencies;
    int wp;
    int rp;

#### members are accesed in accessed in:
* irqgen_irqhandler()
* irqgen_cdev_read()
* intr_handled_show()
* total_handled_show()

#### Examples:
* when using the measuring.sh script the total_handled variable is read at the same time as interrupts are generating and incrementing this variable

## 7. In the proposed structure, we opted for a single lock for the whole `irqgen_data` structure. Could you describe advantages and disadvantages of a single lock vs several locks? What about the effects on the IRQ handling latency?
* Single lock simplifies the lockinging logic and minimises the risk of deadlocks/race conditions
* Several locks would ensure that only the required resource is locked, the others can continue operating
* Waiting to aquire a lock, wastes time that might be productively spent elsewher. This increases the IRQ handling latency
* Waiting to aquire a lock on a resource with a single spinlock has higher latency than waiting on the same resouce which has been locked more intelligently with multiple spinlocks on specific members within the resource.

## 8. To avoid concurrency issues among the different parts of `irqgen-mod` you had to choose a synchronization mechanisms. What kind did you choose? Why? Where? What alternatives did you consider? Why did you reject them?
* decided on using spinlocks. specifically spin_lock_irqsave() as it stores previous interrupt state in a flags variable.  Safer as we can be 100% sure that the interrupts should be re-enabled when you releasing the spinlock
* Alternatives include mutex's and semaphores.
* The problem with mutexes is that putting threads to sleep and waking them up again are both rather expensive operations. If now the mutex was only locked for a very short amount of time, the time spent in putting a thread to sleep and waking it up again might exceed the time the thread has actually slept by far and it might even exceed the time the thread would have wasted by constantly polling on a spinlock.
* Pynq has multiple processors so spin_lock makes sense.  we believe the time spent in the lock is quite short, and thus may be more efficient than a mutex however no comparison was made in performance.

## 9. To optimize even more the IRQ handling latency we should abandon the monolithic handler function for a more efficient pattern: what's its name? Describe how the code currently handling the requests would be organized and describe a few reasons to choose the alternative over the monolithic style.
* The interrupt handler currently works by acknowledging the interrupt by setting the appropriate register on the IP-Block
* The critical section for updating the irqgen_data data structure is spin_locked to prevent concurrency issues.
* the handler returns once these task are completed indicating that the IRQ has been sucessfully served
#### Alternative:
* An alternative to the above monolithic approach would be to have a more layered approach (Top-half / bottom-half)
* Non-critical section and acknowledge sections could be handled separately to the critical section.
* In the Top-half the interrupt could be acknowledged and interrupt handled could be returned.  The critical section and data storage could be scheduled to execute later (tasklet or Workqueue)
* This approach may mean that the interrupt handler can return quicker to reduce latency in interrupt handling.  
* As a multi-layered approach would not block the whole interrupt handler (spin locked critical section) and could improve handling latency
* As such acknowledgment and data read/write would be occuring separately

## 10. What is an SDK?
An SDK is a Software Development Kit

#### The yocto SDK include the following:
* Cross-Development Toolchain: This toolchain contains a compiler, debugger, and various miscellaneous tools.
* Libraries, Headers, and Symbols: The libraries, headers, and symbols are specific to the image (i.e. they match the image).
* Environment Setup Script: This *.sh file, once run, sets up the cross-development environment by defining variables and preparing for SDK use.

The Yocto SDK is completely self-contained and is used to independently develop and test code that is destined to run on some target machine.

In this excersise the SDK was used to cross-compile the statistics application on the virtual machine to run on the specific image of the pynq board

## 11. In the context of the Yocto Project, what are the differences between the Standard and the Extensible SDK?
#### Standard SDK only includes:
* Toolchain
* Debugger

#### the eSDK include the following additional features over the standard SDK:
* devtool 
* Build Images
* Updateable
* Managed Sysroot
## 12. Describe your workflow in developing and testing the `irqgen_statistics` app
* The character driver was developed and tested first.
* Interupts were generated using the sysfs /sys/kernel/irqgen/ interface and stored into a .csv file. this file was copied from the pynq board to the virtual machine via the sdcard

``` 
tail -f /dev/irqgen | tee -a ~/irqgen.csv & 
```

* The statistics app was developed and tested on the virtual machine enviromnent with this .csv file
* the application continuously reads from stdin using fgets
* the .csv fields are tokenised and extracted using the strtok
* Internal int and float arrays are used to store the required statistics for each IRQ line
* Counts are incrimented, averages are calculated and maximums determined and stored in these arrays
* The application implements a signal handler that waits for the SIGINT signal to stop waiting for input.
* After receiving this signal, statistics are printed to the user using printf based on the specification and the program exist gracefully
* After the program was tested sucessfully on the virtual machine, it was cross compiled using the sdk and copied to the sdcard
* The measuring.sh script was then used to test the system, and print the required statistics using the cross-compiled app

## 13. Feedback (what was difficult? what was easy? how would you improve it?)
* Found the excerise a little difficult.  Had alot of issues related to ensurig the locks were in the right place, also had issue getting the statistic app to behave correctly with the -INT signal sent from the measuring.sh script 
