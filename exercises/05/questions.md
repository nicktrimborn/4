# TIE-50307 - Exercise 05 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
    - become familiar with how the ip-block is implemented
    - learn the basics of fpga development
    - introduction the vivado enviromnment and register manipulation in vivado

## 2. Describe your verilog coding process in 2 paragraphs
    - added IRQ_GEN_LATENCY_REG at 0x000c from IP block datasheet
    - Initialise IRQ_GEN_LATENCY_REG and read registers into master
    - Added irq_latency_counter_r, irq_latency_r to IRQ counter circuit and initialise them to d0
    - On each positive clock edge, increment irq_latency_counter_r by 1
        - If an new interrupt was generated to some IRQ line:
            * increment irq_count_r count by 1
            * set irq_pending_r to 1 (signaling it is awaiting ack)
            * added a line to reset irq_latency_counter_r
        - If an interrupt was served from some IRQ line (ack Recieved)
            * set irq_pending_r to 0
            * copy the irq_latency_counter_r value to irq_latency_r
            * reset irq_latency_counter_r to 0

## 3. How much difference there is in latency between the regular driver build and the debug driver build? Why?
    - There is a large difference ~2-3000ns vs ~2.5ms 
    - debug build makes use of printk in the irqgen_irqhandler which introduces alot of delay
    - irq handler should return as quickly as possible and should avoid waits and prints etc    

## 4. How can you find the base address for the IP block register space in Vivado? Does it match the contents of the devicetree?
    - base address for the IP block is found in the address editor under the name of the block.  The offset address 0x43C0_0000 matches the register address in the device tree.

## 5. Feedback (what was difficult? what was easy? how would you improve it?)
- for someone who had not used vivado and verilog before, the learning curve was a little steep