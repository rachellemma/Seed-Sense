Seed Sense 

An assistive robot that helps visually impaired users plant seeds accurately within a structured grid system.

🏆 2nd Place — Assistive Robotics Project, Medford, MA (April 2025)

Overview

Seed Sense guides a user through a planting grid and ensures each seed is placed at a consistent, precise spacing — removing the need for the user to visually judge distance or alignment. The robot moves forward a fixed distance (20 inches per grid cell) on command, using closed-loop feedback from a wheel encoder rather than relying on timing alone, so movement stays accurate even as battery voltage or surface friction varies.

My Role — Tech Lead
Co-designed the overall robot concept and grid-based planting workflow
Developed the Arduino firmware controlling dual DC motors via quadrature encoder feedback and hardware interrupts for precise, autonomous distance control
Integrated embedded hardware (motors, motor driver, encoder, button input) with the control software to enable reliable navigation and user-focused functionality
How It Works
User presses a button to trigger the next move.
Both drive motors engage forward.
A quadrature encoder on the drive wheel generates interrupt-driven tick counts as the wheel turns.
Ticks are converted to real-world distance using the wheel's circumference and the encoder's ticks-per-revolution.
Once the measured distance reaches the 20-inch (0.508 m) target, both motors stop automatically.
The system resets and waits for the next button press.

This closed-loop approach (encoder feedback instead of a fixed time delay) keeps each grid movement consistent regardless of minor speed variation, so the planting grid stays evenly spaced.

Hardware
Component	Details
Microcontroller	Arduino (Uno/compatible)
Motor Driver	Dual H-bridge driver (e.g. L298N-style), ENA/ENB PWM enable
Motors	2x DC gear motors (RK 370CA-2470 or similar)
Encoder	Quadrature encoder, 12 ticks/revolution
Wheel	6.5 cm diameter
Input	Push button (start/trigger)
Pin Mapping
Function	Arduino Pin
Motor 1 IN1 / IN2	2 / 3
Motor 2 IN3 / IN4	4 / 5
Encoder Channel A / B	6 / 7
Enable A / Enable B (PWM)	9 / 10
Button	12
Firmware

The main sketch (seed_sense.ino) is written in Arduino C++ and:

Uses a hardware interrupt on the encoder's A channel to track ticks in real time without blocking the main loop
Converts ticks to distance via wheel circumference ÷ ticks-per-revolution
Drives motors forward on button press and halts them once the target distance is reached
Uses Serial output for debugging/status messages
Future Improvements
Add a second encoder (currently only one wheel is monitored) to detect and correct drift between the two motors
Add PWM-based speed ramping instead of running motors at full enable voltage
Add auditory/haptic feedback for the visually impaired user at each grid stop
Closed-loop turning between grid rows
Team / Context

Built for Tufts Robotics Club Robotathon Competition, April 2025. Teammates: Vicky Lin, Flory Mendez Merida, Andrew Barreda 
