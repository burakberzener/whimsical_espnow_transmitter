#ifndef distance
#define distance

/*Pin Defines*/
#define sensorFrontLeftEcho 23
#define sensorFrontLeftTrig 22
#define sensorFrontRightEcho 33
#define sensorFrontRightTrig 25

#define sensorSideLeftEcho 26
#define sensorSideLeftTrig 27
#define sensorSideRightEcho 14
#define sensorSideRightTrig 12

#define sensorBackEcho 21
#define sensorBackTrig 19

#define CRICITAL_DISTANCE 50
#define FRONT_TRIG_SIDE_CTRL 69

void initDistance();
int getDistance(int distanceSensorTrig, int distanceSensorEcho);

#endif