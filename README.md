# SimSpirit-Motion-Simulator-Platform
This is firmware source code for the mainboard controller a new Open-Source Motion Simulator Platform that is able to perform Yaw, Pitch and Roll based on input from Game-Telemetry Data or Directly from Head-tracker using BNO085 Inertia Measuring Unit

The Main-Board is designed around ESP32 microcontroler from Expressif.
The code is written in C using Arduino and run on PlatformIO

Currently the following methods can be used to control the motion-simulator.
1: Head-tracker with inbuilt IMU chip- Connects to the ESP32 through Bluetooth or via ESP-Now.
2: UDP plugin from Games Telemetary. Some Games support have been added and will be listed soon.

# SimSpirit Motion Simulator

SimSpirit is an open-source motion simulator platform designed for immersive and realistic experiences. The motion simulation is capable of full 360 degrees yaw, as well as providing synchronized pitch and roll at any given yaw position, thanks to its highly accurate patent-pending algorithm.

## Features

- **Open Source:** SimSpirit is an open-source project, allowing developers and enthusiasts to contribute, modify, and enhance the platform.
- **ESP32 Mainboard:** The motion simulator is built around the powerful and versatile ESP32 microcontroller, providing a robust foundation for control and communication.
- **Head-Tracker with LSM6DS3 IMU:** The head-tracker module utilizes the LSM6DS3 or BNO085 inertial measurement unit (IMU) for precise measurement of yaw, pitch, and roll in free space.
- **Full 360 Degrees Yaw:** SimSpirit enables complete 360 degrees yaw rotation, delivering a comprehensive range of motion for an immersive experience.
- **Synchronized Pitch and Roll:** The motion simulator's patent-pending algorithm ensures synchronized pitch and roll at any specific yaw position, enhancing realism and accuracy.
- **Immersive Experiences:** SimSpirit is designed to provide users with immersive and realistic experiences by precisely simulating the motion corresponding to the virtual environment or application.

## Getting Started

To get started with SimSpirit, follow these steps:

1. **Hardware Requirements:** Ensure you have the necessary hardware components, including the SimSpirit motion simulator platform, ESP32 mainboard, and optional LSM6DS3 or BNO085 IMU head-tracker.
2. **Software Setup:** Install the required software dependencies and libraries on your development environment. This typically involves setting up the Arduino Programming in PlatformIO with the ESP32 board support package.
3. **Assembly:** Assemble the SimSpirit motion simulator platform according to the provided instructions. Connect the ESP32 mainboard and the LSM6DS3 IMU to their respective interfaces.
4. **Firmware Upload:** Upload the SimSpirit firmware onto the ESP32 mainboard using the Arduino IDE or any compatible firmware uploading tool. Ensure proper configuration and calibration settings are applied.
5. **Integration:** Integrate the SimSpirit motion simulator with your desired application or virtual environment. Use the provided API or SDK to synchronize the motion simulation with the visual and audio elements of your project.
6. **Testing and Calibration:** Perform thorough testing and calibration to ensure accurate and reliable motion simulation. Adjust parameters, if necessary, to fine-tune the performance according to your requirements.
7. **Contribution and Support:** Join the SimSpirit community on GitHub to contribute to the project, share your experiences, and seek assistance from fellow developers and enthusiasts.

## License

SimSpirit is released under the [MIT License](LICENSE). You are free to use, modify, and distribute the platform in accordance with the terms and conditions stated in the license.

## Acknowledgments

SimSpirit is made possible by the contributions of numerous individuals and organizations. We would like to express our gratitude to the open-source community for their support, feedback, and valuable contributions to the project.

## Contact

For inquiries, suggestions, or support regarding SimSpirit, please reach out to the project team at simspirit@example.com.

---
*Note: This README provides a general overview and guide for the SimSpirit motion simulator. For detailed instructions, troubleshooting, and updates, please refer to the project's GitHub repository.*
