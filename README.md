# Offboard Skywriting Mode
# MAVSDK Application
## Gordon Keller
## Rev. 1 1/3/20

A MAVSDK-based implementation of a multirotor skywriting mode that:
1. Establishes connection to PX4 system
2. Takes a string argument of the form 'WRITE THIS' and converts it to waypoints and trajectories
3. Executes mission with an optional trigger for light, laser, smoke element, etc.

## Building

*MAVSDK libraries must be installed on the system

```
cd /{PROJECT DIR}
mkdir build
cd build
cmake ..
make
```

## Running (in simulation)

1. Run JMavSim
```
cd .../src/Firmware/ (wherever you have PX4 source installed)
make px4_sitl_default jmavsim
```

2. Run Offboard Program
```
./offboard_skywriting udp://:14540 'ABCDEFGHIJKLM
NOPQRSTUVWXYZ'
```

Output (retrieved from flight log):
![alt text](/imgs/alphabet_p_3_0.png "Alphabet Path")


This command will initialize vehicle takeoff sequence (if not already airborne) and will traverse the alphabet in two lines.
*Program start quirk will reject first offboard call in simulation -- simply run the program again and the sequence will start.

## Project To-Dos

- Implement better PID for trajectory control
- Add flags/modifiers for skywriting setting #defines in main
- Add safety protocols
- Create GTests for each library
- Add external instrument (LED, smoke machine) controls (refer to https://ardupilot.org/copter/docs/common-external-leds.html -- even though this reference is for ardupilot, should be a programming option for PX4)
- Add build information/changes to allow for local install of MAVSDK, not just system-wide install out of the box
- Change this section to a proper project roadmap rather than a list of to-dos


