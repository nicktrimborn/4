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
* Drivers expecting platform data should check the dev.platform_data pointer in the usual way. If there is a non-null value there, the driver has been instantiated in the traditional way and device tree does not enter into the picture; the platform data should be used in the usual way. If, however, the driver has been instantiated from the device tree code, the platform_data pointer will be null, indicating that the information must be acquired from the device tree directly.

## 4. Why did we bother to rewrite the LKM code to implement a platform device driver?
* Want to use the Device Model for devices that are not on buses that can auto-detect devices
* Description through a Device Tree .dts file, manage them through the platform bus.  
* The platform bus is used by the driver to retrieve information about the device such as IRQ numbers, platform resources and other properties.  With the LKM this was all hardcoded

## 5. Imagine you are developing a product on the PYNQ-Z1 board involving several IP blocks of your own design to squeeze all the resources and cabalities of the SoC FPGA; most IP blocks are accessible from the PS through the AMBA/AXI bus. Do you need to alter the device-tree we are using? What's the minimum set of information that you would require for each addressable IP block?
* Would need to add a device tree entry for each IP Block
* Specify compatible ID which is linked to the device tree using struct of_device_id properties
* Need to provide memory address

## 6. What capabilities are exposed through the current sysfs interface of the `irqgen`? Describe the available entry points inside `/sys/kernel/irqgen` and their functions.
#### Generation/Control
* Amount - amount of interrupts to generate
* line - interrup line 
* delay - interrupt generation delay
* enabled - enable/disable irqgenerator ip block
#### Results
* latency - latency of last irq server (ns)
* latencies - latencies (clock edges) for each line
* line_count - interrupt line count
#### Bookeeping / Platform specific
* count_register - count since boot
* intr_acks - ack values from devicetree
* intr_ids - linux IRQ number
* intr_idx - interupt index
* intr_handled - count of interupts handled by each line
* total_handled - total number of interupts handled

## 7. Are there code sections that are missing concurrency barriers? Where? Can you think of a way of triggering unintended behaviour?
* IRQ handler implement concurrency barries when reading and writing register values
* Need to ensure IP block contol such as enable/disable etc are not executed while interup generation/handling is occuring 
## 8. Feedback (what was difficult? what was easy? how would you improve it?)
* Instructions were clear and helpful
