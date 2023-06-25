# Digitalman-Motion-Simulator-Platform
This is firmware source code for the mainboard controller a new Open-Source Motion Simulator Platform that is able to perform Yaw, Pitch and Roll based on input from Game-Telemetry Data or Directly from Head-tracker using BNO085 Inertia Measuring Unit

The Main-Board is designed around ESP32 microcontroler from Expressif.
The code is written in C using Arduino and run on PlatformIO

Currently the following methods can be used to control the motion-simulator.
1: Head-tracker with inbuilt IMU chip- Connects to the ESP32 through Bluetooth or via ESP-Now.
2: UDP plugin from Games Telemetary. Some Games support have been added and will be listed soon.
