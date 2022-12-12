#include <Arduino.h>

#define PUMP_SPEED 5
#define PUMP_DIR1 2
#define PUMP_DIR2 3


#define WATER_TIME 5000
#define WATER_SPEED 100
#define INTERVAL_DAYS 4 // 5 days 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(PUMP_SPEED, OUTPUT);
  pinMode(PUMP_DIR1, OUTPUT);
  pinMode(PUMP_DIR2, OUTPUT);
  digitalWrite(PUMP_SPEED, LOW);
  digitalWrite(PUMP_DIR1, LOW);
  digitalWrite(PUMP_DIR2, LOW);
  delay(1000);

  digitalWrite(PUMP_DIR1, HIGH);
  digitalWrite(PUMP_DIR2, LOW);
  analogWrite(PUMP_SPEED, 100);
  Serial.println("TESTING");
  delay(1000);
  digitalWrite(PUMP_DIR1, LOW);
  digitalWrite(PUMP_DIR2, LOW);
  Serial.println("READY");
  delay(1000);
}


unsigned long long prevWaterTime = 0;

void waterPlant() {
  digitalWrite(PUMP_DIR1, HIGH);
  digitalWrite(PUMP_DIR2, LOW);
  analogWrite(PUMP_SPEED, WATER_SPEED);
  Serial.print("watering");
  for (int i = 0; i < 4; i++) {
    delay(WATER_TIME / 4);
    Serial.print(".");
  }
  digitalWrite(PUMP_DIR1, LOW);
  digitalWrite(PUMP_DIR2, LOW);
  Serial.println("done.");
  delay(0);
}

void plantDelay(unsigned long delayTimeDays) {
  unsigned long long currentTime = millis();
  unsigned long long delayTimeMs = delayTimeDays * 24 * 60 * 60 * 1000;
  if (currentTime - prevWaterTime > delayTimeMs) {
    Serial.println("Time since last watering: " + String((int)((currentTime - prevWaterTime) / 1000)) + " seconds");
    prevWaterTime = currentTime;
    waterPlant();
  }
  delay(0);
}


void loop() {
  // put your main code here, to run repeatedly:
  plantDelay(INTERVAL_DAYS);
  delay(1000);
  Serial.println(String((float)millis() / 1000) + " seconds elapsed. ");
}