#include <SoftwareSerial.h>
#include <Servo.h>
#include "DFRobotDFPlayerMini.h"

#define TRIGGER_PIN  2 // Arduino pin connected to trigger pin of ultrasonic sensor
#define ECHO_PIN     3 // Arduino pin connected to echo pin of ultrasonic sensor
#define DISTANCE_THRESHOLD 100 // Distance threshold in centimeters
#define RX_PIN 10 // Arduino pin connected to RX pin of DFPlayer Mini
#define TX_PIN 11 // Arduino pin connected to TX pin of DFPlayer Mini
#define SERVO_PIN 7 // Pin connected to the control pin of the servo motor
#define MAX_DISTANCE 100 // Maximum distance in centimeters

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Create a SoftwareSerial object to communicate with DFPlayer Mini
DFRobotDFPlayerMini mp3; // Define the DFPlayer object
Servo servoMotor; // Define servo object

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  mySerial.begin(9600); // Start communication with DFPlayer Mini

  // Set serial for DFPlayer Mini
  mp3.begin(mySerial);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servoMotor.attach(SERVO_PIN); // Attaches the servo on pin servoPin to the servo object
}

void loop() {
  long duration, distance;

  // Clear trigger pin
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  // Send 10 microsecond pulse to trigger pin
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the duration of pulse on echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the distance is less than threshold
  if (distance < DISTANCE_THRESHOLD) {
    // If an object is detected, play audio
    playAudio();

    // Rotate the servo by 90 degrees
    servoMotor.write(60); // Rotate the servo to 90 degrees
    delay(100); // Delay to allow the servo to reach the desired position
  } else {
    // If no object is detected, keep the servo at 0 degrees
    servoMotor.write(0); // Rotate the servo to 0 degrees
    delay(100); // Delay to allow the servo to reach the desired position
  }

  delay(500); // Delay before next reading
}

void playAudio() {
  // Play a specific audio track
  mp3.play(1);
  delay(9300);
  mp3.play(2);
  delay(200); // Adjust delay as per the length of the audio track
}