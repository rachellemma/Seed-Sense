# Seed Sense 🌱

An assistive robot that helps visually impaired users plant seeds accurately within a structured grid system.

**🏆 2nd Place — Assistive Robotics Project, Medford, MA (April 2025)**

## Overview

Seed Sense guides a user through a planting grid and ensures each seed is placed at a consistent, precise spacing — removing the need for the user to visually judge distance or alignment. The robot moves forward a fixed distance (20 inches per grid cell) on command, using closed-loop feedback from a wheel encoder rather than relying on timing alone, so movement stays accurate even as battery voltage or surface friction varies.

## My Role — Tech Lead

- Co-designed the overall robot concept and grid-based planting workflow
- Developed the Arduino firmware controlling dual DC motors via quadrature encoder feedback and hardware interrupts for precise, autonomous distance control
- Integrated embedded hardware (motors, motor driver, encoder, button input) with the control software to enable reliable navigation and user-focused functionality

## How It Works

1. User presses a button to trigger the next move.
2. Both drive motors engage forward.
3. A quadrature encoder on the drive wheel generates interrupt-driven tick counts as the wheel turns.
4. Ticks are converted to real-world distance using the wheel's circumference and the encoder's ticks-per-revolution.
5. Once the measured distance reaches the 20-inch (0.508 m) target, both motors stop automatically.
6. The system resets and waits for the next button press.

This closed-loop approach (encoder feedback instead of a fixed time delay) keeps each grid movement consistent regardless of minor speed variation, so the planting grid stays evenly spaced.

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino (Uno/compatible) |
| Motor Driver | Dual H-bridge driver (e.g. L298N-style), ENA/ENB PWM enable |
| Motors | 2x DC gear motors (RK 370CA-2470 or similar) |
| Encoder | Quadrature encoder, 12 ticks/revolution |
| Wheel | 6.5 cm diameter |
| Input | Push button (start/trigger) |

### Pin Mapping

| Function | Arduino Pin |
|---|---|
| Motor 1 IN1 / IN2 | 2 / 3 |
| Motor 2 IN3 / IN4 | 4 / 5 |
| Encoder Channel A / B | 6 / 7 |
| Enable A / Enable B | 9 / 10 |
| Button | 12 |

## Firmware

The main sketch (`seed_sense.ino`) is written in Arduino C++ and:
- Uses a hardware interrupt on the encoder's A channel to track ticks in real time without blocking the main loop
- Converts ticks to distance via wheel circumference ÷ ticks-per-revolution
- Drives motors forward on button press and halts them once the target distance is reached
- Currently runs motors at a fixed full-on enable state (`digitalWrite(enA/enB, HIGH)`) rather than variable PWM speed — the enable pins are PWM-capable but not yet used that way
- Uses Serial output for debugging/status messages

## Getting Started (How to Run)

1. **Install the Arduino IDE** — download the free IDE from [arduino.cc/en/software](https://www.arduino.cc/en/software).
2. **Connect the Arduino** to your computer via USB. Drivers usually install automatically; clone boards may need the CH340 driver.
3. **Select your board and port** — in the IDE, go to `Tools > Board` and choose your board (e.g. Arduino Uno), then `Tools > Port` and pick the port that appears when the board is plugged in.
4. **Open the sketch** — open the `.ino` file from this repo in the IDE.
5. **Verify** the code (checkmark button) to make sure it compiles with no errors.
6. **Upload** the code (arrow button) to flash it onto the board.
7. **Wire up the hardware** per the pin mapping above (motor driver, motors, encoder, button, power).
8. **Test it** — open `Tools > Serial Monitor` at 9600 baud to see status messages, then press the button to trigger a 20-inch move.

## Future Improvements

- Add a second encoder (currently only one wheel is monitored) to detect and correct drift between the two motors
- Use `analogWrite()` on the enable pins for actual PWM speed control/ramping instead of the current fixed full-on state
- Add auditory/haptic feedback for the visually impaired user at each grid stop
- Closed-loop turning between grid rows

## Team / Context

Built for Tufts Robotics Club Robotathon Competition, April 2025. Teammates: Vicky Lin, Flory Mendez Merida, Andrew Barreda 
