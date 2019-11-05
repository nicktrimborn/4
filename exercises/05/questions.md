# TIE-50307 - Exercise 05 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
    - become familiar with how the ip-block is implemented
    - learn the basics of fpga development
    - introduction the vivado enviromnment and register manipulation in vivado

## 2. Describe your verilog coding process in 2 paragraphs


## 3. How much difference there is in latency between the regular driver build and the debug driver build? Why?
    - There is a large difference ~1080ns vs ~2.5ms 
    - debug build makes use of printk in the irqgen_irqhandler which introduces alot of delay
    - irq handler should return as quickly as possible and should avoid waits and prints etc    

## 4. How can you find the base address for the IP block register space in Vivado? Does it match the contents of the devicetree?


## 5. Feedback (what was difficult? what was easy? how would you improve it?)
- for someone who had not used vivado and verilog before, the learning curve was a little steep