# dspic33ck-power-isolated-voltage-acquisition-board v1.0.0

### Release Highlights

This firmware controls the dsPIC33CK on the Isolated Voltage Acquisition Board.
It facilitates isolated measurement of up to 3 voltages.
Upon receipt of a trigger on pin 3 of header J4, the dsPIC33CK will digitize the voltages on L1, L2 and L3 with respect to N with its on-board 12-bit ADC.
The 3 measurements, along with a checksum, are transmitted across the 4kV isolation barrier via optocouplers.

2-wire SPI is used for transmisson
* SPI clock on pin 5 of J4
* SPI data on pin 4 of J4


### Features Added\Updated

(none / initial release)

