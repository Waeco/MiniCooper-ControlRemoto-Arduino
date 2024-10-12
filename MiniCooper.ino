#include <Servo.h>

Servo servoMotor;

const int pinMotor1A = 9;
const int pinMotor1B = 10;

const int pinMotor2A = 3;
const int pinMotor2B = 5;

const int led1Pin = 6;
const int led2Pin = 7;

unsigned long lastMillis = 0;

int motorSpeed = 255;

void forward() {
  analogWrite(pinMotor1A, motorSpeed);
  digitalWrite(pinMotor1B, LOW);
}

void backward() {
  digitalWrite(pinMotor1A, LOW);
  analogWrite(pinMotor1B, motorSpeed);
}

void left() {
  analogWrite(pinMotor2A, motorSpeed);
  digitalWrite(pinMotor2B, LOW);
  delay(400);
  digitalWrite(pinMotor2A, LOW);
  digitalWrite(pinMotor2B, LOW);
}

void right() {
  digitalWrite(pinMotor2A, LOW);
  analogWrite(pinMotor2B, motorSpeed);
  delay(400);
  digitalWrite(pinMotor2A, LOW);
  digitalWrite(pinMotor2B, LOW);
}

void stopMotors() {
  digitalWrite(pinMotor1A, LOW);
  digitalWrite(pinMotor1B, LOW);
  digitalWrite(pinMotor2A, LOW);
  digitalWrite(pinMotor2B, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(pinMotor1A, OUTPUT);
  pinMode(pinMotor1B, OUTPUT);
  pinMode(pinMotor2A, OUTPUT);
  pinMode(pinMotor2B, OUTPUT);

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  servoMotor.attach(2);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    unsigned long currentMillis = millis();

    if (command >= '0' && command <= '9') {
      motorSpeed = map(command - '0', 0, 9, 0, 255);
    } else {
      switch (command) {
        case 'F':
          forward();
          break;
        case 'B':
          backward();
          break;
        case 'L':
          left();
          break;
        case 'R':
          right();
          break;
        case 'S':
          stopMotors();
          break;
        case 'U':
          digitalWrite(led1Pin, HIGH);
          break;
        case 'u':
          digitalWrite(led1Pin, LOW);
          break;
        case 'W':
          digitalWrite(led2Pin, HIGH);
          break;
        case 'w':
          digitalWrite(led2Pin, LOW);
          break;
        case 'V':
          servoMotor.write(135);
          break;
        case 'v':
          servoMotor.write(90);
          break;
        default:
          Serial.println("Invalid command");
      }
    }
    lastMillis = currentMillis;
  }
}
