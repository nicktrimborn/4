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
* average latency = 259.58
* worst case = 348413

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
* average latency = 925.26
* worst case = 552121


## 5. Compare the results of questions 2 and 4; do they differ significantly? why?
* average latency is increased when applying the RT patch
* worst case latency is much reduced, except for one outlier on line 4

## 6. Compare the plots for the 8 different profiles. Describe each of them and compare them?
#### non-RT_noTorture
* Lowest average latency of the 4 plots
* has the occasional spikes in latency and a single large peak around IRQ no 250
* The latencies for each irq are somewhat inconsistent
#### non-RT_Torture
* average latency is higher compared to noTorture case
* worst case latency is lower than noTorture case (vertical scale is lower)
* does not exhibit a single large spike like in RT_noTorture but rather has multiple spike approximately every 100 IRQ's 

#### RT_noTorture
* Exhibits similar behaviour to non-RT (including the large single spike) however has increased average latency
* Although latencies are higher, they are more consistent than the non-RT case 
* A few IRQ have latencies lower than the average minimum

#### RT_Torture
* Exhibits highest average latency, however worst case latency is more consistent
* Worst case peaks are not much larger than the average latency values
* Worst case peaks seem to happen more frequently compared to non-RT case
* overall the system appears to react in a more predictable fashion.


## 7. Document the RT performance differences and their reasons
* Average latencies are higher than non-RT
* Peak latencies are lower and there are less outliers are reduced
* Worst case is better with RT-patch compared to non-RT

## 8. Is there any noticeable difference between the two images when saturating the system with IRQ?
* when saturating the system the non-RT system basically hangs at iteration 1/100 as it is flooded with IRQ requests
* when saturating the system the with RT patch the system seems to hand at iteration 1/100 as well
* IRQs are still being genearted in the background and can be seen on the serial terminal.

## 9. Using the information in [scripts/README.txt](scripts/README.txt), try to tune the RT-system to overcome the limits described in the previous question
* Doesnt make any difference. hangs the terminal as the system is flooded
* Tried different methods of setting the PID priority scheduling and setting full CPU time. Did not seem to have any effect
* Test script still hangs at at iteration 1/100
* Board no longer responds to ssh and commands issued in the exisiting ssh session dont seem get executed.

## 10. What is the goal of this exercise? What did you accomplish?
* The goal is to benchmark the IRQ handling latency of the developed LKM module
* compare the differences between the regular Linux environment and this Real-Time solution
* analyse the effect on average and maximum latencies between the regular Linux environment and the Real-Time solution
* analyse the effect on average and maximum latencies when modifying the IRQ handler thread priority and scheduled CPU time.

## 11. Feedback (what was difficult? what was easy? how would you improve it?)
* Disabling the ack was step was quite ambiguous and was not able to observe much difference when chaning the process priority and CPU time allocation
