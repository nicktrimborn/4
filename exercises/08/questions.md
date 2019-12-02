# TIE-50307 - Exercise 08 - Q&A

## 1. What is `uname -a` output on the PYNQ board before starting Ex 8?
##### The output of "uname -a" on te PYNQ board is:
    Linux pynq 4.9.0-xilinx-v2017.3 #1 SMP PREEMPT Thu Aug 9 16:33:05 UTC 2018 armv7l GNU/Linux

## 2. What is the average latency and worst case latency you measure after Ex 7 using the application you developed?
#### output:
    0,11852,231.29,3645
    1,11783,238.17,3998
    2,11670,236.34,4908
    3,11022,241.58,4769
    4,10647,233.29,4455
    5,9532,248.60,29031
    6,10569,229.14,4305
    7,8770,237.27,3819
    8,8644,240.83,3800
    9,8532,247.89,3253
    10,9273,236.28,3333
    11,11241,243.42,3841
    12,10822,218.51,4201
    13,10174,233.07,3748
    14,10047,231.73,3313
    15,10748,279.84,347567
    -1,165326,239.20,347567

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

## 11. Feedback (what was difficult? what was easy? how would you improve it?)

