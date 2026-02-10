#include <Servo.h>

int potPin = A0;
int servoPin = 6;

int greenLed = 9;
int redLed = 10;

Servo myServo;

void setup() {
  myServo.attach(servoPin);

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  Serial.begin(9600);
  Serial.println("=== SAFETY INTERLOCK START ===");
}

void loop() {
  int potValue = analogRead(potPin);            // 0 ~ 1023
  int angle = map(potValue, 0, 1023, 0, 180);   // 0 ~ 180

  myServo.write(angle);

  // ----- 안전 범위 체크 -----
  if (angle >= 30 && angle <= 150) {
    // 정상 범위
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  } else {
    // 위험 범위
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print(" | Angle: ");
  Serial.print(angle);
  Serial.print(" | State: ");
  Serial.println((angle >= 30 && angle <= 150) ? "SAFE" : "DANGER");

  delay(20);
}
