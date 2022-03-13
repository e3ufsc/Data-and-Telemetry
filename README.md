# Data-and-Telemetry

How to run the simulation:

First download the library from the repository: https://github.com/Proteus-LIBRARY/Arduino-Library. Unzip the files. Copy the files to your Proteus library folder (generally located at: C:\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\DATA\LIBRARY).
Download the “Simulation” folder and open Proteus project.

Insert the code in Arduino for the simulation clicking 2 times at the componente “ARD1”, and in "Program file" indicate the path to "code_arduino_uno", and select "code_arduino_uno.ino.hex". Now just click "Ok".

For you to simulate, press the button "Run" located in the lower left corner.

When the simulation is open, you can choose the RPM and throttle. The RPM is selected at “pulse” based on frequency, so remember that Hz = RPM/60. To change the throttle you can select up or down at “RV1”.
The RPM can’t change while the simulation is running, just the throttle can, so you need to choose a fixed RPM each time you star running the simulation.
