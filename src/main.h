#ifndef main
#define main

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "motor.h"
#include  "distance.h"

/*User Defines*/
#define _VERSION "0.2"
#define _MACADDRESS "84:CC:A8:7A:CF:E8"
#define _DEBUGMODE 1
#define _MOTORDEBUG 0
#define _ESPNOWDEBUG 0

/*UART2 Pins*/
#define RXD2 16
#define TXD2 17

/*Wi-Fi Message*/
typedef struct espnow_msg_struct {
    char id; // must be unique for each sender board
    char data;
} espnow_msg_struct;

/*Broadcast Addresses*/

#if _ESPNOWDEBUG
  uint8_t broadcastAddress_blue[] = {0xC8, 0xF0, 0x9E, 0x9E, 0xF5, 0xF4}; //Green
  uint8_t broadcastAddress_yellow[] = {0xEC, 0x62, 0x60, 0x83, 0xA2, 0xEC}; //Yellow
  uint8_t broadcastAddress_green[] = {0xEC, 0x62, 0x60, 0x9A, 0xB5, 0x84}; //Green
  uint8_t broadcastAddress_purple[] = {0x84, 0xCC, 0xA8, 0x7A, 0x60, 0x00}; //Purple
  uint8_t broadcastAddress_red[] = {0xEC, 0x62, 0x60, 0x83, 0xC3, 0xA8}; //Red
#else
uint8_t broadcastAddress_blue[] = {0xEC, 0x62, 0x60, 0x94, 0xBB, 0xB4}; //Blue (Master, this device)
uint8_t broadcastAddress_yellow[] = {0x84, 0xCC, 0xA8, 0x7A, 0xCF, 0x88}; //Yellow
uint8_t broadcastAddress_green[] = {0x84, 0xCC, 0xA8, 0x7A, 0xCF, 0xE4}; //Green
uint8_t broadcastAddress_purple[] = {0x84, 0xCC, 0xA8, 0x7A, 0x60, 0x00}; //Purple
uint8_t broadcastAddress_red[] = {0xEC, 0x62, 0x60, 0x83, 0xC3, 0xA8}; //Red
#endif

/*Wi-Fi SSID and Password*/
const char* ssid     = "Whimsical-Blue";
const char* password = "123456789";

/*ESPNow receive data structure*/
typedef struct struct_message_espnow {
  int id;
  int isActive;
  unsigned int data;
} struct_message_espnow;

enum sensorChecker{NO_OBSTACLES, SIDE_SENSOR_ALARM, FRONT_SENSOR_ALARM};

volatile long echo_start = 0;                         // Records start of echo pulse 
volatile long echo_end = 0;                           // Records end of echo pulse
volatile long echo_duration = 0;                      // Duration - difference between end and start
volatile int trigger_time_count = 0;                  // Count down counter to trigger pulse time
int serial_buffer;

#endif