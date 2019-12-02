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
*

## 6. Compare the plots for the 8 different profiles. Describe each of them and compare them?

## 7. Document the RT performance differences and their reasons

## 8. Is there any noticeable difference between the two images when saturating the system with IRQ?

## 9. Using the information in [scripts/README.txt](scripts/README.txt), try to tune the RT-system to overcome the limits described in the previous question

## 10. What is the goal of this exercise? What did you accomplish?
* The goal is to benchmark the IRQ handling latency of the developed LKM module
* compare the differences between the regular Linux environment and this Real-Time solution
* analyse the effect on average and maximum latencies between the regular Linux environment and the Real-Time solution
* analyse the effect on average and maximum latencies when modifying the IRQ handler thread priority and scheduled CPU time.

## 11. Feedback (what was difficult? what was easy? how would you improve it?)
* tasks were relatively straight forward. Disabling the ack was step was quite ambiguous
