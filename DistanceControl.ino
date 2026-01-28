// Motor control pins
// Motor control pins
int motor1pin1 = 2;  // Connect to IN1 on the motor driver
int motor1pin2 = 3;  // Connect to IN2 on the motor driver
int motor2pin1 = 4;  // Connect to IN3 on the motor driver
int motor2pin2 = 5;  // Connect to IN4 on the motor driver
int enA = 9;         // Connect to ENA on the motor driver (PWM pin for Motor 1)
int enB = 10;        // Connect to ENB on the motor driver (PWM pin for Motor 2)

// Button pin
const int buttonPin = 12;
int buttonState = 0; // Variable for reading the pushButton status

// Encoder pins
const int encoder1PinA = 6; // Encoder Channel A (Yellow wire)
const int encoder1PinB = 7; // Encoder Channel B (White wire)

// Encoder tick counter
volatile long encoder1Ticks = 0;

// Wheel and encoder parameters
const float wheelDiameter = 0.065; // Wheel diameter in meters (6.5 cm)
const float wheelCircumference = 3.14159 * wheelDiameter; // Circumference in meters
const int ticksPerRevolution = 12; // Encoder ticks per revolution (12 for RK 370CA-2470)
const float distancePerTick = wheelCircumference / ticksPerRevolution; // Distance per tick

// Fixed distance to travel (20 inches = 0.508 meters)
const float targetDistance = 0.508; // Distance in meters

// Motor control variables
bool isMoving = false; // Flag to track if the motors are moving

// Encoder interrupt function
void updateEncoder1() {
  if (digitalRead(encoder1PinB) == HIGH) {
    encoder1Ticks++; // Increment ticks if encoder B is HIGH
  } else {
    encoder1Ticks--; // Decrement ticks if encoder B is LOW
  }
}

void setup() {
  // Set motor control pins as outputs
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Set encoder pins as inputs
  pinMode(encoder1PinA, INPUT);
  pinMode(encoder1PinB, INPUT);

  // Attach encoder interrupt
  attachInterrupt(digitalPinToInterrupt(encoder1PinA), updateEncoder1, RISING);

  // Enable the motor driver
  digitalWrite(enA, HIGH); // Enable Motor 1
  digitalWrite(enB, HIGH); // Enable Motor 2

  // Initialize Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Press the button to start moving 20 inches.");
}

void loop() {
  // Check button state
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && !isMoving) {
    isMoving = true; // Set flag to indicate motors are moving
    encoder1Ticks = 0; // Reset encoder counter

    // Move both motors forward
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  }

  // Check if the desired distance has been traveled
  if (isMoving) {
    float distanceTraveled = encoder1Ticks * distancePerTick;
    if (distanceTraveled >= targetDistance) {
      // Stop both motors
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      // Reset variables
      isMoving = false;
      Serial.println("20 inches reached. Motors stopped.");
    }
  }
}
