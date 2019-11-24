# TIE-50307 - Exercise 06 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
* to write support for a custom device, in this case represented by an FPGA IP block 
* Develop a platform driver and support for a description of the platform devices through a devicetree
* Learn about Devres or Device-managed resources

## 2. What is a platform device? What makes such a device different from, e.g., a USB device or a PCI device?
* Platform device are normally hard-wired, non pluggable devices
* Drivers for a platform device do not need to check for the presence of the actual device
* Description of device the platform devices can be done through a devicetree

## 3. What is the relation between the device-tree and platform device drivers?
* The platform device drivers are linked to the device tree using the the compatible id
* The device tree includes a platform device, and it will be instantiated and matched against a driver. 
* Memory-mapped I/O and interrupt resources will be marshalled from the device tree description and made available to the device's probe() function.

## 4. Why did we bother to rewrite the LKM code to implement a platform device driver?
* Want to use the Device Model for devices that are not on buses that can auto-detect devices
* Description through a Device Tree .dts file, manage them through the platform bus.  
* The platform bus is used by the driver to retrieve information about the device such as IRQ numbers, platform resources and other properties.  With the LKM this was all hardcoded
* With the LKM the HW addresses were hardcoded, so on a different device, that driver would not have worked. Now we have a "configurable" driver, that is configurable via the device tree and is therefore more portable

## 5. Imagine you are developing a product on the PYNQ-Z1 board involving several IP blocks of your own design to squeeze all the resources and cabalities of the SoC FPGA; most IP blocks are accessible from the PS through the AMBA/AXI bus. Do you need to alter the device-tree we are using? What's the minimum set of information that you would require for each addressable IP block?
* Would need to add a device tree entry for each IP Block
* Specify compatible ID which is linked to the device tree using struct of_device_id properties
* Need to provide start and end memory addresses

## 6. What capabilities are exposed through the current sysfs interface of the `irqgen`? Describe the available entry points inside `/sys/kernel/irqgen` and their functions.
#### Generation/Control
* Amount - amount of interrupts to generate
* line - interrup line on which to generate irqs
* delay - interrupt generation delay
* enabled - enable/disable irqgenerator ip block
#### Results
* latency - latency of last irq served (ns)
* latencies - circular buffer for IRQ latencies from the IRQ generator, capacity is MAX_LATENCIES elems
#### Bookeeping / Platform driver specific
* count_register - count since boot
* intr_acks - the interrupt ACK values read from the device tree
* intr_ids - the interrupt IDs allocated for the IRQ lines
* intr_idx - incremental index for each IRQ line
* intr_handled - count of total handled interrupts per interrupt ID
* total_handled - count of total handled interrupts

## 7. Are there code sections that are missing concurrency barriers? Where? Can you think of a way of triggering unintended behaviour?
* IRQ handler implement needs to implement concurrency barries when reading and writing register values
* members of irqgen_data need to be protected from concurrent access
* If we trigger another interrupt while the handler is still running, that might cause problems.
## 8. Feedback (what was difficult? what was easy? how would you improve it?)
* Instructions were clear and helpful
* a few sneaky missing memory allocations
