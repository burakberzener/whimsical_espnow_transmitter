#include <esp_now.h>
#include <WiFi.h>
#include "distance.h"

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration = 0;
float distance_cm = 0;

void initDistance() {
    pinMode(sensorFrontLeftEcho, INPUT);
    pinMode(sensorFrontLeftTrig, OUTPUT);
    pinMode(sensorFrontRightEcho, INPUT);
    pinMode(sensorFrontRightTrig, OUTPUT);
    pinMode(sensorSideLeftEcho, INPUT);
    pinMode(sensorSideLeftTrig, OUTPUT);
    pinMode(sensorSideRightEcho, INPUT);
    pinMode(sensorSideRightTrig, OUTPUT);
    pinMode(sensorBackEcho, INPUT);
    pinMode(sensorBackTrig, OUTPUT);
}


int getDistance(int distanceSensorTrig, int distanceSensorEcho) {
    digitalWrite(distanceSensorTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(distanceSensorTrig, HIGH);
    delayMicroseconds(10); 
    digitalWrite(distanceSensorTrig, LOW);
    duration = pulseIn(distanceSensorEcho, HIGH);
    distance_cm = (duration*SOUND_SPEED)/2;
    return distance_cm;
}
