# SimSpirit-Motion-Simulator-Platform
This is firmware source code for the mainboard controller a new Open-Source Motion Simulator Platform that is able to perform Yaw, Pitch and Roll based on input from Game-Telemetry Data or Directly from ViewTracer© using LSM6DS3 Inertia Measuring Unit.

![SimSpirit 3-axis platform animation](https://github.com/jpdigitalman/SimSpirit-Motion-Simulator-Platform/blob/master/Hardware/simspirit-axis-animation.gif?raw=true)

Here is an animation of the 3-axis pitch-roll platform. The Yaw motor sits on top of the movable pitch-roll platform.

The Main-Board is designed around ESP32 microcontroler from Expressif.
The code is written in C using Arduino and run on PlatformIO. The supplied code has been fully tested to work. The Pitch/Roll syncronization matrix code has been left out. Contact the developer to get the sync code. Only the yaw simulation works with the supplied code without modification.

Currently the following methods can be used to control the motion-simulator.
1: ViewTracer© with inbuilt IMU chip- Connects to the ESP32 mainboard through Bluetooth or via ESP-Now. Currently, ESPnow has been enabled because of its low latency.
2: WiFi- UDP plugin from Games Telemetary. Some Games support have been added. See Telemetry control for list of supported games.

# SimSpirit Motion Simulator

SimSpirit is an open-source motion simulator platform designed for immersive and realistic experiences. The motion simulation is capable of full 360 degrees yaw, as well as providing synchronized pitch and roll at any given yaw position, thanks to its highly accurate patent-pending sync algorithm.

## Features

- **Open Source:** SimSpirit is an open-source project, allowing developers and enthusiasts to contribute, modify, and enhance the platform.
- **ESP32 Mainboard:** The motion simulator is built around the powerful and versatile ESP32 microcontroller, providing a robust foundation for control and communication.
![Image SimSpirit PCB Layout](https://github.com/jpdigitalman/SimSpirit-Motion-Simulator-Platform/blob/master/SimSpirit_PCB_Layout/Assembly.png?raw=true)

- **View-Tracer with LSM6DS3 IMU:** The ViewTracer© module utilizes the LSM6DS3 inertial measurement unit (IMU) for precise measurement of yaw, pitch, and roll in free space.
  The ViewTracer© Project is in this [Github page](https://github.com/jpdigitalman/SimSpirit-MotionSimulation-Headtracker)
- **Full 360 Degrees Yaw:** SimSpirit enables complete 360 degrees yaw rotation, delivering a comprehensive range of motion for an immersive experience.
- **Synchronized Pitch and Roll:** The motion simulator's patent-pending algorithm ensures synchronized pitch and roll at any specific yaw position, enhancing realism and accuracy.
- **Immersive Experiences:** SimSpirit is designed to provide users with immersive and realistic experiences by precisely simulating the motion corresponding to the virtual environment or application.

## Getting Started

To get started with SimSpirit, follow these steps:

1. **Hardware Requirements:** Ensure you have the necessary hardware components, including the SimSpirit motion simulator platform, ESP32 mainboard, and optional LSM6DS3 IMU ViewTracer©.
2. **Software Setup:** Install the required software dependencies and libraries on your development environment. This typically involves setting up the Arduino Programming in PlatformIO with the ESP32 board support package.
3. **Assembly:** Assemble the SimSpirit motion simulator platform according to the provided instructions (Coming soon). Connect the ESP32 mainboard to their respective interfaces.
4. **Firmware Upload:** Upload the SimSpirit firmware onto the ESP32 mainboard using the PlatformIO IDE or any compatible firmware uploading tool. Ensure proper configuration and calibration settings are applied. The SimSpirit firmware update is based on esp32doit-devkit-v1 setup on the PlatformIO.
5. **Integration:** Integrate the SimSpirit motion simulator with your desired application or virtual environment. Use the provided API or SDK to synchronize the motion simulation with the visual and audio elements of your project.
6. **Testing and Calibration:** Perform thorough testing and calibration to ensure accurate and reliable motion simulation. Adjust parameters, if necessary, to fine-tune the performance according to your requirements. The Yaw movement has no need for manual calibration. Pressing Calibration on the ViewTracer automatically calibrates the Yaw and the Pitch/Roll to initial position.
7. **Contribution and Support:** Join the SimSpirit community on GitHub to contribute to the project, share your experiences, and seek assistance from fellow developers and enthusiasts.

## Controlling SimSpirit

SimSpirit offers the convenience of control through the ViewTracer, which establishes a connection with the mainboard using the ESPnow protocol. The decision to utilize ESPnow instead of Bluetooth mode stems from the protocol's remarkable low latency. By leveraging ESPnow, SimSpirit ensures responsive and real-time control, enhancing the overall user experience.

## Game Telemetry Control

*SimSpirit can be controlled via game telemetry data.*

(udp port default port is 20777) --- *Change the default in /include/pindefines.h  -- find F1_UDP_PORT variable*

In addition to the ViewTracer control, SimSpirit offers the capability to be controlled directly through live games telemetry data. It currently supports several popular games, including F1-2022, Life for Speed, and Epic_RollerCoaster, which runs on the Meta Quest2 VR Headset.

SimSpirit enables direct control via WiFi using UDP datagram plugins. By leveraging UDP telemetry data, any game capable of sending UDP packets can control the SimSpirit without the need for intermediate PC USB control. This feature provides limited latency and a seamless and immersive experience for users.

Furthermore, SimSpirit can also be controlled via USB directly from a PC, offering flexibility in control options to suit different setups and preferences.

The SimSpirit game telemetry control features include:
- Direct control through live games telemetry data.
- Compatibility with popular games such as F1-2022, Life for Speed, and Epic_RollerCoaster (on the Meta Quest2 VR Headset).
- Control via WiFi using UDP datagram plugins.
- Any game capable of sending UDP telemetry data can control the SimSpirit directly, without the need for PC USB control.
- The SimSpirit can also be controlled via USB directly from a PC.
- Flexibility in control options to suit different setups and preferences.

Please note that for compatibility with specific games and setups, appropriate configuration and integration may be required. Refer to the documentation and guides for more information on setting up game telemetry control with SimSpirit.

Feel free to let me know if there's anything else you'd like to add or modify!

## License

SimSpirit is released under the [MIT License](https://opensource.org/licenses/MIT). You are free to use, modify, and distribute the platform in accordance with the terms and conditions stated in the license.

## Acknowledgments

SimSpirit is made possible by the use of open source materials obtained online from contributions of numerous individuals and organizations. Hence the justification in making it open source as well. We would like to express our gratitude to the open-source community for the use of their valuable materials in this project.

## Contact

For inquiries, suggestions, or support regarding SimSpirit, please reach out to the project director.

---
*Note: This README provides a general overview and guide for the SimSpirit motion simulator. For detailed instructions, troubleshooting, and updates, please refer to the project's GitHub repository.*
