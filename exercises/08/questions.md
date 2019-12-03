# TIE-50307 - Exercise 08 - Q&A

## 1. What is `uname -a` output on the PYNQ board before starting Ex 8?
##### The output of "uname -a" on te PYNQ board is:
    Linux pynq 4.9.0-xilinx-v2017.3 #1 SMP PREEMPT Thu Aug 9 16:33:05 UTC 2018 armv7l GNU/Linux

## 2. What is the average latency and worst case latency you measure after Ex 7 using the application you developed?
#### output:
    0,20000,275.69,344423
    1,20000,236.90,192783
    2,20000,242.32,5014
    3,20000,228.85,5433
    4,20000,226.21,5738
    5,20000,258.09,346959
    6,20000,251.44,342294
    7,20000,272.29,348044
    8,20000,238.17,4908
    9,20000,251.38,345715
    10,20000,230.73,5428
    11,20000,243.10,5444
    12,20000,242.53,343121
    13,20000,378.03,347268
    14,20000,229.24,5518
    15,20000,348.25,348413
    -1,320000,259.58,348413
    
#### stats:
* Average latency = 259.58
* Worst case = 348413

## 3. What is `uname -a` output on the PYNQ board after rebooting with the new kernel image?
    Linux pynq 4.9.0-rt1-xilinx-v2017.3 #1 SMP PREEMPT RT Mon Dec 2 14:25:13 UTC 2019 armv7l GNU/Linux
    
## 4. What is the average latency and worst case latency you measure in the new kernel image (same procedure as question 2)?
#### output:
    0,20000,931.97,5882
    1,20000,905.52,6256
    2,20000,886.67,6447
    3,20000,873.74,6549
    4,20000,920.65,552121
    5,20000,896.79,6704
    6,20000,916.14,6235
    7,20000,953.81,6534
    8,20000,942.53,6757
    9,20000,943.76,6643
    10,20000,1000.85,6436
    11,20000,937.04,6705
    12,20000,976.26,6728
    13,20000,920.97,7069
    14,20000,910.61,6622
    15,20000,886.88,7845
    -1,320000,925.26,552121
    
#### stats:
* Average latency = 925.26
* Worst case = 552121


## 5. Compare the results of questions 2 and 4; do they differ significantly? why?

* Average latency is increased after adding the RT-PREEMPT Patch to the kernel.
* With the RT-PREEMPT Patch, worst case latencies of each line are much smaller and consistent, except for one outlier on line 4.

## 6. Compare the plots for the 8 different profiles. Describe each of them and compare them?
#### non-RT_noTorture
* Lowest average latency of the 4 plots.
* Has the occasional spikes in latency and a single large peak around IRQ no 250.
* The latencies for each irq are somewhat inconsistent.

#### non-RT_Torture
* Average latency is higher compared to noTorture case.
* Worst case latency is lower than noTorture case (vertical scale is lower).
* Does not exhibit a single large spike like in RT_noTorture but rather has multiple spike approximately every 100 IRQ's. 

#### RT_noTorture
* Exhibits similar behaviour to non-RT (including the large single spike) however has increased average latency.
* Although latencies are higher, they are more consistent than the non-RT case. 
* A few IRQ have latencies lower than the average minimum.

#### RT_Torture
* Exhibits highest average latency, however worst case latency is more consistent.
* Worst case peaks are not much larger than the average latency values.
* Worst case peaks seem to happen more frequently compared to non-RT case.
* overall the system appears to react in a more predictable fashion.


## 7. Document the RT performance differences and their reasons
#### Differences
* Average latencies is higher than non-RT.
* Peak latencies are lower resulting in fewer outliers in the latencies.
* Worst case is better with RT-patch compared to non-RT.

#### Reasons
* Every interrupt handler is run on a kernel thread
* The RT patch converts all spin_locks to mutexes, making them interruptible.
* Running every interrupt handler in a kernel thread causes scheduling overhead which
increases best-case and average interrupt latency. 
* However this decreases the Worst Case Latency, which is more important in an RT aspect. 

## 8. Is there any noticeable difference between the two images when saturating the system with IRQ?
* When saturating the system the non-RT system basically hangs at iteration 1/100 as it is flooded with IRQ requests.
* When saturating the system the with RT patch the system seems to hang at iteration 1/100 as well.
* IRQs are still being genearted in the background and can be seen on the serial terminal.

## 9. Using the information in [scripts/README.txt](scripts/README.txt), try to tune the RT-system to overcome the limits described in the previous question
* Following the recommendations in the "scripts/README.txt" didn't seem to have any effect on the system as the terminal hangs when the system is being flooded
* Tried different methods of setting the PID priority scheduling and setting full CPU time. Did not seem to have any effect.
* Test script still hangs at at iteration 1/100.
* Board no longer responds to ssh and commands issued in the exisiting ssh session dont seem get executed.

## 10. What is the goal of this exercise? What did you accomplish?
* The goal is to benchmark the IRQ handling latency of the developed LKM module.
* Compare the differences between the regular Linux environment and this Real-Time solution.
* Analyse the effect on average and maximum latencies between the regular Linux environment and the Real-Time solution.
* Analyse the effect on average and maximum latencies when modifying the IRQ handler thread priority and scheduled CPU time..

## 11. Feedback (what was difficult? what was easy? how would you improve it?)
* Disabling the ack step was quite ambiguous and was not able to observe much difference when changing the process priority and CPU time allocation.
* A better explanation of the expected system behaviour would be much more helpful to estimate wether the steps we followed and executed are correct.
