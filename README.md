# SilentSignal: Noiseless Vehicle Horn System

## Overview
SilentSignal is a project designed to reduce noise pollution caused by honking on busy roads. The system aims to replace traditional vehicle horns with an internal communication network between vehicles, where drivers and passengers can receive alerts through an internal notification system. This way, honking is only heard by the people inside the vehicles, helping reduce distractions and contributing to a quieter environment.

## Problem Statement
Vehicle honking has become a significant source of noise pollution in busy cities, contributing to stress and distractions for drivers and pedestrians. Traditional vehicle horns are loud and often used unnecessarily. The goal of this project is to create a solution that reduces the noise pollution while maintaining safety norms by allowing vehicles to communicate with each other without producing loud honking sounds.

## Features
- **Internal Communication**: Vehicles will communicate with each other through an internal system, using radio frequency transceivers.
- **Reduced Honking**: Only the driver and passengers inside the vehicle will hear the horn, reducing road noise.
- **Safety Maintenance**: Despite reducing honking frequency, the system ensures that emergency signals and alerts are still communicated effectively.
- **Multidisciplinary Approach**: Involves electrical engineering, software development, and mathematical calculations for distance-based communication between vehicles.

## Components Required
- **Arduino Boards (UNO & Nano)**
- **16x2 Serial LCD Modules (x2)**
- **NRF24L01+ 2.4GHz Wireless Transceiver Modules (x6)**
- **IR Sensors**
- **Serial MP3 Modules (x2)**
- **Bluetooth Modules**
- **Neo-6M GPS Modules (optional)**
- **Batteries**
- **Jumper Wires**


## Implementation
### System Design
![image alt](https://github.com/abrar-khan-alvi/SilentSignal/blob/main/Screenshot%202025-05-03%20195413.png)
The system consists of two main components:
- **Sender**: The vehicle sending the alert (i.e., honking signal). It includes the Arduino board, NRF24L01+ transceiver, and an MP3 module for playing sound inside the vehicle.
- **Receiver**: The nearby vehicle receiving the honk signal. It uses an NRF24L01+ module, IR sensors, and speakers for delivering the sound alert.

The communication is done wirelessly between vehicles, using the NRF24L01+ transceivers to send and receive signals. The system is programmed using Arduino IDE, and mobile apps (e.g., Android Studio) are used to enhance functionality like distance calculation via GPS.

### Working Principle
- When a driver wants to honk, they press a button that sends a signal through the NRF24L01+ transmitter to other vehicles in range.
- The receiving vehicle gets the signal through its NRF24L01+ receiver and plays the sound internally.
- The system can be extended to calculate distances between vehicles using GPS data (via Neo-6M or a mobile app).

## Multidisciplinary Contributions
1. **Electrical & Electronics**: Design and management of voltage and current for the embedded system components.
2. **Software**: The system is programmed using Arduino IDE, with additional software written in languages like C++ for logic control. The mobile application (Flutter, Android Studio) handles positioning and distance calculation using Google Maps API.
3. **Mathematics**: The calculation of distances between vehicles using longitude and latitude data, integrating GPS systems for more precise vehicle location.

## Challenges
- **GPS Module Integration**: We initially used Neo-6M GPS modules but encountered integration issues. An alternative app using the Google Map API was developed to overcome this challenge.
- **NRF24L01+ Availability**: The required modules were not available on some circuit design software platforms, making virtual testing difficult.
- ![image alt](https://github.com/abrar-khan-alvi/SilentSignal/blob/main/Screenshot%202025-05-03%20195426.png)

## Social and Economic Impacts
### Social Impacts
- **Noise Pollution Reduction**: Helps in significantly lowering the amount of noise on the roads.
- **Improved Driver Focus**: Reduces distractions caused by unnecessary honking.
- **More Concentrated Driving**: Promotes a quieter environment, leading to a more focused driving experience.

### Economic Impacts
- **Affordable System**: The system is cost-effective and affordable for mass adoption.
- **Job Opportunities**: Opens doors for engineers and developers to work on implementing and improving the system.
- **Collaboration with Automobile Companies**: Potential for partnerships with automobile companies to integrate the technology into vehicles.

## Conclusion
The SilentSignal project aims to create a quieter, more peaceful road environment by eliminating the loud, aggressive honking of traditional vehicle horns. By using a wireless communication system between vehicles, this project can improve the driving experience while maintaining safety. Through collaborative efforts with automobile manufacturers and engineers, we hope to develop a solution that can be scaled and integrated into modern vehicles.

## Team Members
- **Abrar Khan Alvi** (20210104016)
- **Fahari Alam Rashed** (20210104017)
- **H.M. Ziyad** (20210104023)
- **Afia Fahmida** (20210104032)

## Contact
For more information, feel free to reach out to the team or check out our social media profiles for updates on the project.

---
