# epc9149-power-1kw-8th-brick-power-module, release v1.0.0

### Release Highlights

This initial firmware release of the EPC9149 1 kW LLC 8th Brick Size Power Module demonstrates operation as fixed, 4:1 Voltage Transfomer Module (VTM). VTMs operate from a regulated power distribution bus. Operating at a center frequency of 1 MHz, this converter transforms input voltages down by a fixed ratio of 4:1, effectively quartrupling the output current. The LLC resonant converter topology continuously operatings in soft-switching conditions minimizing losses, maximizing efficiency of this conversion step.

### Features Added\Updated

In this first, basic implementation the firmware is used to configure the peripherals required to drive switch node and synchronous rectifier in continuous soft-switching conditions optimizing conversion efficeincy. In addition, voltage, current and tempperature threshold monitoring as well as hardware triggered over current protection adds a basic level of protection.

### Next Release Feature Outlook

This first release will be updated shortly, introducing 

- improvements on runtime diagnostics
- real-time communication of status information with PC via the USB interface of the EPC9533 test fixture
- improved state machine mechanisms and fault response

