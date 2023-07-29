Terminal based RF Design Calculator

This program provides assistance with common formulas used in RF circuit design.

Written in C using Standard Libraries.

Liux:
  To build make sure that gcc and make are installed, then

  make

  To run use ./rfassistant

Windows:
  To build make sure that VS C++ build tools are install, then

  cl src/rfassistant.c src/ghcommon.c src/helperfunctions.c

  To run use rfassistant


   **** RF Calculator Main Menu ****

 1. Turns to Inductance for Toroid Coil
 2. Turns to Inductance for Air Core Coil
 3. Capacitance vs Frequency for Tank Circuit
 4. Inductance vs Frequency for Tank Circuit
 5. Capacitive Reactance @ Frequency
 6. Inductive Reactance @ Frequency
 7. SWR for Input Z vs Output Z
 8. Power Radiated and Lost for SWR @ Power
 9. SWR for Power Forward vs Power Reflected
10. Variable Capacitor Scaling
11. Coax Stub Notch & Pass
12. Transmitter Output Matching PI Network
13. Complex Impedance Matching Networks
14. Decibel Conversions
15. Resistors,Inductors,Capacitors - Series & Parallel
16. Toroid Al Value from Inductance and Turns
17. Chebyshev Filters
18. Butterworth Filters
19. Nearby Powers of 10 Conversion
20. Line of Sight Distance/Free Space Path Loss
21. Resistor Attenuators
22. Coax Loss
23. Wire Antenna Length
24. Image Frequency and Local Oscillator

