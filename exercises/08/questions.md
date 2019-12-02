# TIE-50307 - Exercise 08 - Q&A

## 1. What is `uname -a` output on the PYNQ board before starting Ex 8?
##### The output of "uname -a" on te PYNQ board is:
    Linux pynq 4.9.0-xilinx-v2017.3 #1 SMP PREEMPT Thu Aug 9 16:33:05 UTC 2018 armv7l GNU/Linux

## 2. What is the average latency and worst case latency you measure after Ex 7 using the application you developed?
#### output:
0,11852,231.29,3645\
1,11783,238.17,3998\
2,11670,236.34,4908\
3,11022,241.58,4769\
4,10647,233.29,4455\
5,9532,248.60,29031\
6,10569,229.14,4305\
7,8770,237.27,3819\
8,8644,240.83,3800\
9,8532,247.89,3253\
10,9273,236.28,3333\
11,11241,243.42,3841\
12,10822,218.51,4201\
13,10174,233.07,3748\
14,10047,231.73,3313\
15,10748,279.84,347567\
-1,165326,239.20,347567\

#### stats:
* average latency = 239.20
* worst case = 347567

## 3. What is `uname -a` output on the PYNQ board after rebooting with the new kernel image?

## 4. What is the average latency and worst case latency you measure in the new kernel image (same procedure as question 2)?

## 5. Compare the results of questions 2 and 4; do they differ significantly? why?

## 6. Compare the plots for the 8 different profiles. Describe each of them and compare them?

## 7. Document the RT performance differences and their reasons

## 8. Is there any noticeable difference between the two images when saturating the system with IRQ?

## 9. Using the information in [scripts/README.txt](scripts/README.txt), try to tune the RT-system to overcome the limits described in the previous question

## 10. What is the goal of this exercise? What did you accomplish?

## 11. Feedback (what was difficult? what was easy? how would you improve it?)

