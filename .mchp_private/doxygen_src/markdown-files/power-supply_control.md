# Power Supply Control

<span id="startDoc"><a name="startDoc"> </a></span> <!-- start tag for internal references -->
<div style="text-align:left">
    <img src="images/startbanner.png" alt="Firmware Quick-Start Guide" height="70" width="880">
</div>

## Table of Contents

- [DPSK3 Buck Converter Average Current Mode Control Implementation](#vmc_1)
- [Control Loop Block Diagram](#vmc_2)
- [Control Loop Timing](#vmc_3)
- [Control Loop Flow Chart](#vmc_4)
- [Control Loop Firmware Implementation](#vmc_5)


<span id="vmc_1"><a name="vmc_1"></a></span>

## 1) DPSK3 Buck Converter Average Current Mode Control Implementation

This firmware demonstrates the implementation of a typical dual-loop average current mode controller used to regulate the constant output voltage of the on-board step-down converter of the Digital Power Starter Kit 3 (DPSK3). The implementation of the Current Mode Feedback Loop requires two Analog-to-Digital Converter (ADC) inputs oversampling the output voltage and inductor current of the converter and two PWM outputs (PWM high and PWM low) to drive the power converter half-bridge switch-node in synchronous mode. 

[[back](#startDoc)]
<span id="vmc_2"><a name="vmc_2"></a></span>

## 2) Control Loop Block Diagram

*Figure 1* shows the block diagram of the buck converter average current mode controller, comprised of an outer voltage loop providing the control reference to an inner current loop. The first ADC input is used to sample the most recent level of the output voltage feedback signal. Once converted, the value is then compared against the internal voltage reference value and the inverse of the deviation between reference and feedback (= *error*) is pushed through the first discrete compensation filter stage. An Anti-Windup Limiter is used to limit the control loop output range to user-specified minimum and maximum limits.

The output of the outer voltage loop is passed on to the current reference input of the inner loop, where it gets compared against the most recent current feedback input read through the second ADC input. The inverse of the deviation between reference and feedback (= *error*) is pushed through the second discrete compensation filter stage. The output of the inner current loop is also passed through an Anti-Windup limiter, limiting the current loop control output to a user-specified range. The limiter output value is then written directly to the PWM duty cycle register of the PWM logic.

<div style="text-align:center">
    <img src="images/average-current-mode-control.png" alt="Firmware Quick-Start Guide" width="800">
    <br><i>Figure 1: Control Loop Block Diagram of Dual-Loop Average Current Mode Control Loop</i><br>
</div>
<br>

<span id="vmc_3"><a name="vmc_3"></a></span>

## 3) Control Loop Timing

The average current mode control loop block is triggered by the PWM counter at
50% of the off-time. At this point the outer voltage loop controller is called in parallel with the output voltage ADC trigger. The first stage of the control loop is executing the overhead code of calculating the first part of the compensation filter term (= *A-Term*) until the most recent ADC sample is available to be processed in the later part of the compensation filter term computation (= *B-Term*). This approach helps to shorten the overall response time of the controller measured between ADC trigger and write back event of the most recent controller result to the duty cycle register of the PWM generator. 

The output of the first stage of the control loop is then passed on to the second stage, the inner current loop. This part of the loop compares the new reference with the most recent inductor current feedback value, which was acquired previously at 50% on-time. The reciprocal of the deviation is passed through the second discrete time domain filter H<sub>C</sub>(z) and Anti-Windup Limiter. The new controller output value will then be divided by two. This value will be used to set the ADC trigger of the current loop at 50% of the on-time and added to half of the period value to place the new ADC trigger point at 50% of the off-time for the voltage loop. If the user has specified additional offsets to compensate FET driver propagation delays, this constant time-offset is added before the ADC trigger locations are updated. 

The new output of the current loop will be written to the PWM duty cycle register and will be updated immediately when the new value of the ADC trigger location of the voltage loop is written to the PWM generator logic. 


<div style="text-align:center">
    <img src="images/control_timing_acmc.png" alt="Firmware Quick-Start Guide" width="800">
    <br><i>Figure 2: Control Loop Timing</i><br>
</div>
<br>

[[back](#startDoc)]
<span id="vmc_4"><a name="vmc_4"></a></span>

## 4) Control Loop Flow Chart

*Figure 4* shows a typical flow chart of a discrete software feedback loop called at the desired control frequency. It covers the loop path from ADC trigger to PWM output shown in the block diagram above (see *Figure 2 and 3*) while supporting additional features like an *Enable/Disable Bypass Switch* or advanced features like *Adaptive Gain Control (AGC)*.

- <span style="color:green"> <b>[green]</b></span> boxes represent default building blocks
- <span style="color:grey"> <b>[grey]</b> </span> boxes represent unused optional features 
- <span style="color:blue"> <b>[blue]</b> </span> boxes represent active optional features 

<div style="text-align:center">
    <img src="images/npnz16b-flowchart.png" alt="Firmware Quick-Start Guide" width="460">
    <br><i>Figure 3: Single Control Loop Flow Chart</i><br>
</div>
<br>


[[back](#startDoc)]
<span id="vmc_5"><a name="vmc_5"></a></span>

## 5) Control Loop Firmware Implementation

*Figure 5* shows a typical implementation of the power converter state machine and the high-speed control loop in a task scheduler based firmware environment (order right to left of Figure 5).

- <span style="color:darkorange"> <b>Real Time Control Loop and Low Level Drivers</b> </span>
The control loop is called in an independent high priority Interrupt Service Routine (ISR) by the PWM module simultaneously with triggering the ADC input. Thus, the control loop is tightly coupled to the PWM switching signal and synchronized to the most recent ADC conversion process, allowing a highly deterministic arrangement of code execution, peripheral module activity and external analog circuit operation. The interrupt priority needs to be high enough to override all other software tasks of the firmware to ensure jitter-free execution of the control loop. 
<br><br>
- <span style="color:green"> <b>Topology-Specific State Machine Library</b></span>
Each converter topology requires a specifically tailored configuration of related chip resources as well as start-up, control and monitoring procedures. *Topology State Machine Libraries* support a wide range of circuit configurations, control modes and functional features. Build-in peripheral configuration drivers are used to ease the configuration of required chip resources, such as number of PWM channels and their signal configuration, number of Analog-to-Digital (ADC) inputs, analog comparators, Digital-to-Analog Converter (DAC) channels, etc. 
All user configurations of a topology specific power converter are encapsulated in a comprehensive data object. This approach allows the definition of multiple power supplies of the same type being included, monitored and run independently from each other. Each of these power converter objects also include the declaration of the high-speed control loop object described above, enabling it to control peripherals and control loop code to be synchronized to time-critical states.
<br><br>
- <span style="color:darkblue"> <b>Application Layer of the Power Supply Control Task</b> </span>
The application layer of this task is the proprietary firmware component covering the application-specific configuration of library data objects and high-speed control loops. It also allows to add and tailor functions, which are not covered by the default features of library modules.
<br><br>
- <span style="color:grey"> <b>Scheduler Level</b> </span>
The scheduler level organizes all tasks of the firmware. Besides the power control and related fault handler task, this DPSK3 code example includes the on-board LC display data output, the on-board push-button control of the LC display screens and the on-board debugging LED, which are considered  less time critical, low-priority tasks. The main task scheduler in this firmware example therefore supports two priority levels, one for power control and fault handling, executed at a rate of 10 kHz (= 100 us interval) and the low priority tasks, executed at rates between 0.5 ms and 250 ms. 
<br><br>

<div style="text-align:center">
    <img src="images/control-flow-chart.png" alt="Firmware Quick-Start Guide" width="960">
    <br><i>Figure 4: Control Loop Firmware Implementation</i><br>
</div>

<br> <br> 
More detailed information on the library implementation, such as task and library APIs, can be found in the chapter *Software Overview* on the left side of this window.

[[back](#startDoc)]

_________________________________________________
(c) 2021, Microchip Technology Inc.
