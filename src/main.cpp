#include "main.h"

/*
Tasks:
*/

 /*Private Variables BEGIN*/

 /*Private Variables END*/

 /*Private Functions Define BEGIN*/

 /*Private Functions Define END*/

espnow_msg_struct espnow_msg;

String success;
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(9600);
  /*UART2 Init*/
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.setTimeout(50);
  Serial.println("Serial Txd is on pin: "+String(RXD2));
  Serial.println("Serial Rxd is on pin: "+String(RXD2));
  serial_buffer = 0;

  //delay(4000);
  /*Device Informations*/
  Serial.write("Whimsical Software Version: ");
  Serial.println(_VERSION); 
  Serial.write("MAC Address of this device: ");
  Serial.println(WiFi.macAddress()); 


  /*Wi-Fi Init*/
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress_blue, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress_green, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress_purple, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress_red, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  /*Inits*/
  Serial.println("INITS");
  initMotors();
  Serial.println("Motors are initialised.");
  initDistance();
  Serial.println("Sensors are initialised.");
  randomSeed(analogRead(36));
  Serial.println("Random is initialised.");

  #if _MOTORDEBUG
    moveMotors(GO_FORWARD);
    delay(1000);
    moveMotors(GO_BACKWARD);
    delay(1000);
    moveMotors(STOP_ALL);
  #endif
}
 
void loop() {
  //Serial.println("******MAIN LOOP******");

  if (Serial2.available()) {
    msg = Serial2.readStringUntil('\n');
    if(msg.substring(0,2)=="yo") {
      msg_command = "start";
    }
    else if(msg.substring(0,2)=="yc") {
      msg_command = "stop";
    }
    if(msg.substring(2,4)=="bo") {
      espnow_msg.id='b';
      espnow_msg.data='o';
      esp_err_t result = esp_now_send(broadcastAddress_blue, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }
    else if(msg.substring(2,4)=="bc") {
      espnow_msg.id='b';
      espnow_msg.data='c';
      esp_err_t result = esp_now_send(broadcastAddress_blue, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }
    if(msg.substring(4,6)=="go") {
      espnow_msg.id='g';
      espnow_msg.data='o';
      esp_err_t result = esp_now_send(broadcastAddress_green, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }
    else if(msg.substring(4,6)=="gc") {
      espnow_msg.id='g';
      espnow_msg.data='c';
      esp_err_t result = esp_now_send(broadcastAddress_green, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }
    if(msg.substring(6,8)=="po") {
      espnow_msg.id='p';
      espnow_msg.data='o';
      esp_err_t result = esp_now_send(broadcastAddress_purple, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }
    else if(msg.substring(6,8)=="pc") {
      espnow_msg.id='p';
      espnow_msg.data='c';
      esp_err_t result = esp_now_send(broadcastAddress_purple, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }
    if(msg.substring(8,10)=="ro") {
      espnow_msg.id='r';
      espnow_msg.data='o';
      esp_err_t result = esp_now_send(broadcastAddress_purple, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }
    else if(msg.substring(8,10)=="rc") {
      espnow_msg.id='r';
      espnow_msg.data='c';
      esp_err_t result = esp_now_send(broadcastAddress_purple, (uint8_t *) &espnow_msg, sizeof(espnow_msg_struct));
      Serial.print("Sending ID: "); Serial.println(espnow_msg.id);
      Serial.print("Sending Buffer: "); Serial.println(espnow_msg.data);
    }

    //Serial.print("Sub Buffer: "); Serial.println(msg.substring(4,6));
    Serial.print("Reading Buffer: "); Serial.println(msg);
    Serial.print("Message Buffer: "); Serial.println(msg_command);
  }
 
 if(msg_command == "start") {
  /*Algo Code BEGIN*/

  /*Algo Code END*/
 }
}

 /*Private Functions BEGIN*/

 /*Private Functions END*/