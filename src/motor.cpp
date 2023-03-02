#include <esp_now.h>
#include <WiFi.h>
#include "motor.h"

void initMotors() {
  /*Sets the pins as outputs*/
  pinMode(motorLeftPWM, OUTPUT);
  pinMode(motorLeftA, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  pinMode(motorRightPWM, OUTPUT);
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);

  analogWrite(motorLeftPWM, MOTOR_PWM);
  analogWrite(motorRightPWM, MOTOR_PWM);
}

void wSD (int wheelSpinDirection){
  switch (wheelSpinDirection)
  {
  case SPIN_R_FORWARD:
      digitalWrite(motorRightA, HIGH);
      digitalWrite(motorRightB, LOW);
    break;
  case SPIN_L_FORWARD:
      digitalWrite(motorLeftA, HIGH);
      digitalWrite(motorLeftB, LOW);
    break;
    case SPIN_R_BACK: 
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, HIGH);
    break;
    case SPIN_L_BACK:
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, HIGH);
    break;
      case STOP_L:
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, LOW);
    break;
      case STOP_R:
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, LOW);
    break;
  default:
    break;
  }
}

void moveMotors(int motorMovement) {
  switch (motorMovement) {
    //4 basic controls
    case GO_FORWARD:
      Serial.println("GOING FORWARD");
      wSD(SPIN_R_FORWARD);
      wSD(SPIN_L_FORWARD);
      delay(50);
      break;
    case GO_BACKWARD:
      Serial.println("GOING BACKWARD");
      wSD(SPIN_R_BACK);
      wSD(SPIN_L_BACK);
      delay(50);
      break;
    case TURN_LEFT:
      Serial.println("TURNING LEFT");
      wSD(SPIN_R_FORWARD);
      wSD(SPIN_L_BACK);
      delay(50);
      break;
    case TURN_RIGHT:
      Serial.println("TURNING RIGHT");
      wSD(SPIN_R_BACK);
      wSD(SPIN_L_FORWARD);
      delay(50);
      break;
      /*-------------------------------*/
      //Adjusted Controls
    case ROTATE_ON_LEFT_FWD:
      Serial.println("FORWARD ROTATION LWO");//LEFT WHEEL ONLY
      wSD(STOP_R);
      wSD(ROTATE_ON_LEFT_FWD);
      delay(50);
      break;
    case ROTATE_ON_RIGHT_FWD:
      Serial.println("FORWARD ROTATION RWO");//RIGHT WHEEL ONLY
      wSD(STOP_L);
      wSD(ROTATE_ON_RIGHT_FWD);
      delay(50);
      break;
    case ROTATE_ON_LEFT_BWD:
      Serial.println("BACKWARD ROTATION LWO");//LEFT WHEEL ONLY
      wSD(STOP_R);
      wSD(ROTATE_ON_LEFT_BWD);
      delay(50);
      break;
    case ROTATE_ON_RIGHT_BWD:
      Serial.println("BACKWARD ROTATION RWO");//RIGHT WHEEL ONLY
      wSD(STOP_L);
      wSD(ROTATE_ON_RIGHT_BWD);
      delay(50);
      break;
    case STOP_ALL:
      Serial.println("ALL MOTORS STOPPED");
      wSD(STOP_L);
      wSD(STOP_R);
      delay(50);
      break;
    default:
      break;
  }
}