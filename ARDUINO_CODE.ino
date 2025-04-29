#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150
#define SERVOMAX  600

// Channels: 0-Base, 1-Shoulder, 2-Elbow, 3-Wrist, 4-Pitch, 5-Gripper
int servoChannels[6] = {0, 1, 2, 3, 4, 5};

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int commaIndex = input.indexOf(',');
    if (commaIndex > 0) {
      int id = input.substring(0, commaIndex).toInt();
      int angle = input.substring(commaIndex + 1).toInt();
      angle = constrain(angle, 0, 180);
      int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      if (id >= 0 && id < 6) {
        pwm.setPWM(servoChannels[id], 0, pulse);
      }
    }
  }
}
