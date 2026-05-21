# ENVIROGUARD - A Smart Waste Management System

## Overview
ENVIROGUARD is an IoT-based smart waste management system designed to improve hygiene, automate waste segregation, and monitor bin levels in real time. The system automatically classifies waste into dry, wet, and metal categories while also providing fill-level monitoring and GPS-based tracking using IoT technology.

## Features
- Automatic lid opening using ultrasonic sensor
- Automated waste segregation
- Dry, wet, and metal waste classification
- Real-time fill level monitoring
- GPS location tracking
- Notification alerts using Blynk IoT
- Touch-free waste disposal system
- Smart city and eco-friendly solution

## Technologies Used
- Arduino UNO
- ESP8266 (NodeMCU)
- Blynk IoT Platform
- Embedded C / Arduino IDE

## Components Used
- Arduino UNO
- ESP8266 NodeMCU
- Ultrasonic Sensors
- IR Sensor
- Soil Moisture Sensor
- Inductive Proximity Sensor
- MG995 Servo Motor
- SG90 Servo Motor
- GPS Module (NEO-6M)
- 12V Power Supply

## System Architecture

### Automatic Lid Opening and Waste Segregation
- Ultrasonic sensor detects human presence
- Lid opens automatically using servo motor
- Waste is detected using IR sensor
- Moisture sensor identifies wet waste
- Metal sensor detects metal waste
- Servo motors direct waste into corresponding bins

### Fill Level Monitoring and GPS Tracking
- Ultrasonic sensors monitor bin levels
- ESP8266 sends data to Blynk IoT platform
- GPS module tracks bin location
- Alerts are generated when bins become full

## Working Principle
1. Human presence is detected using ultrasonic sensor
2. Lid opens automatically
3. Waste is detected by IR sensor
4. Sensors classify waste type
5. Servo motors rotate bins accordingly
6. Fill level is continuously monitored
7. GPS sends location details
8. Alerts are sent through Blynk IoT

## Schematic Diagram
![Shematic Diagram](schematic1.jpg)
![Shematic Diagram](schematic2.jpg)
## Prototype
![Prototype](prototype.jpg)

## Software Implementation
The system is programmed using Arduino IDE. The ESP8266 module communicates with the Blynk IoT platform for real-time monitoring and notifications.

## Results
- Successful automatic waste segregation
- Real-time waste level monitoring
- GPS-based location tracking
- Smart notification system implemented
- Improved hygiene through touchless operation

## Applications
- Smart cities
- Public waste management
- Railway stations
- Shopping malls
- Offices and campuses
- Residential areas

## Future Improvements
- AI-based waste classification
- Solar-powered operation
- Mobile application integration
- Cloud database support
- Larger-scale deployment

## Team Members
- Namitha Mariyam Joji
- Archana R
- Devika K
- Lakshmi Prakash S

## Project Report
![Report](report.pdf)

## License
This project is licensed under the MIT License.
