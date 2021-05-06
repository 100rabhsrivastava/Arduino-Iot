

#include <Arduino.h>
#include <ESP8266WiFi.h>       // Download & Install ESP8266 Board
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>  // Download & Install https://github.com/Links2004/arduinoWebSockets/releases
#include <ArduinoJson.h>       // Download & Install https://github.com/bblanchon/ArduinoJson/tags
#include <StreamString.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "f6ced464-9099-4d4f-9c69-048a218c02b0"  // Enter the Sinric API Key
#define MySSID "DIR-615-A612"                    // Enter your WiFi Name
#define MyWifiPassword "12345678"            // Enter your WiFi Password

#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

String device_ID_1 = "606757abc26766757ec63f54"; // Enter Sinric Device ID
String device_ID_2 = "606757bfc26766757ec63f5a"; // Enter Sinric Device ID
String device_ID_3 = "606757f2c26766757ec63f64"; // Enter Sinric Device ID
String device_ID_4 = "60675809c26766757ec63f69"; // Enter Sinric Device ID
String device_ID_5 = "6077b8f8c26766757ec80836";
// define the GPIO connected with Relays and switches

// Relays
#define RelayPin1 D6  //D6
#define RelayPin2 D0  //D0
#define RelayPin3 D2  //D2
#define RelayPin4 2  //D1

// Switches
#define SwitchPin1 D3  //D4
#define SwitchPin2 D5   //D5
#define SwitchPin3 D7  //D7
#define SwitchPin4 1   //TX

//WiFi Status LED
#define wifiLed    D4   //D3

int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 1; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 1; //Define integer to remember the toggle state for relay 4


void setPowerStateOnServer(String deviceId, String value);

// deviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it here

void turnOn(String deviceId) {
  if (deviceId == device_ID_1) // Device ID of 1st device
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin1, LOW);
    toggleState_1 = 0;
  }
  if (deviceId == device_ID_2) // Device ID of 2nd device
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin2, LOW);
    toggleState_2 = 0;
  }
  if (deviceId == device_ID_3) // Device ID of 3rd device
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin3, LOW);
    toggleState_3 = 0;
  }
  if (deviceId == device_ID_4) // Device ID of 4th device
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin4, LOW);
    toggleState_4 = 0;
  }
  if (deviceId == device_ID_5) // Device ID of 4th device
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin1, LOW);
    digitalWrite(RelayPin2, LOW);
    digitalWrite(RelayPin3, LOW);
    digitalWrite(RelayPin4, LOW);
    toggleState_1 = 0;
    toggleState_2 = 0;
    toggleState_3 = 0;
    toggleState_4 = 0;
  }
}

void turnOff(String deviceId) {
  if (deviceId == device_ID_1) // Device ID of 1st device
  {
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin1, HIGH);
    toggleState_1 = 1;
  }
  if (deviceId == device_ID_2) // Device ID of 2nd device
  {
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin2, HIGH);
    toggleState_2 = 1;
  }
  if (deviceId == device_ID_3) // Device ID of 3rd device
  {
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin3, HIGH);
    toggleState_3 = 1;
  }
  if (deviceId == device_ID_4) // Device ID of 4th device
  {
    Serial.print("Turn off Device ID: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin4, HIGH);
    toggleState_4 = 1;
  }
    if (deviceId == device_ID_5) // Device ID of 4th device
  {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(RelayPin1, HIGH);
    digitalWrite(RelayPin2, HIGH);
    digitalWrite(RelayPin3, HIGH);
    digitalWrite(RelayPin4, HIGH);
    toggleState_1 = 1;
    toggleState_2 = 1;
    toggleState_3 = 1;
    toggleState_4 = 1;
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      isConnected = false;
      WiFiMulti.addAP(MySSID, MyWifiPassword);
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
        isConnected = true;
        Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
        Serial.printf("Waiting for commands from sinric.com ...\n");
      }
      break;
      case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);

        #if ARDUINOJSON_VERSION_MAJOR == 5
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject((char*)payload);
        #endif
        #if ARDUINOJSON_VERSION_MAJOR == 6
                DynamicJsonDocument json(1024);
                deserializeJson(json, (char*) payload);
        #endif
        String deviceId = json ["deviceId"];
        String action = json ["action"];

        if (action == "setPowerState") { // Switch or Light
          String value = json ["value"];
          if (value == "ON") {
            turnOn(deviceId);
          } else {
            turnOff(deviceId);
          }
        }
        else if (action == "test") {
          Serial.println("[WSc] received test command from sinric.com");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void with_internet(){
    //Manual Switch Control
    if (digitalRead(SwitchPin1) == LOW){
      delay(200);
      if(toggleState_1 == 1){
        digitalWrite(RelayPin1, LOW); // turn on relay 1
        toggleState_1 = 0;
        setPowerStateOnServer(device_ID_1, "ON");
        Serial.println("Device1 ON");
        }
      else{
        digitalWrite(RelayPin1, HIGH); // turn off relay 1
        toggleState_1 = 1;
        setPowerStateOnServer(device_ID_1, "OFF");
        Serial.println("Device1 OFF");
        }
     }
    else if (digitalRead(SwitchPin2) == LOW){
      delay(200);
      if(toggleState_2 == 1){
        digitalWrite(RelayPin2, LOW); // turn on relay 2
        toggleState_2 = 0;
        setPowerStateOnServer(device_ID_2, "ON");
        Serial.println("Device2 ON");
        }
      else{
        digitalWrite(RelayPin2, HIGH); // turn off relay 2
        toggleState_2 = 1;
        setPowerStateOnServer(device_ID_2, "OFF");
        Serial.println("Device2 OFF");
        }
    }
    else if (digitalRead(SwitchPin3) == LOW){
      delay(200);
      if(toggleState_3 == 1){
        digitalWrite(RelayPin3, LOW); // turn on relay 3
        toggleState_3 = 0;
        setPowerStateOnServer(device_ID_3, "ON");
        Serial.println("Device3 ON");
        }
      else{
        digitalWrite(RelayPin3, HIGH); // turn off relay 3
        toggleState_3 = 1;
        setPowerStateOnServer(device_ID_3, "OFF");
        Serial.println("Device3 OFF");
        }
    }
    else if (digitalRead(SwitchPin4) == LOW){
      delay(200);
      if(toggleState_4 == 1){
        digitalWrite(RelayPin4, LOW); // turn on relay 4
        toggleState_4 = 0;
        setPowerStateOnServer(device_ID_4, "ON");
        Serial.println("Device4 ON");
        }
      else{
        digitalWrite(RelayPin4, HIGH); // turn off relay 4
        toggleState_4 = 1;
        setPowerStateOnServer(device_ID_4, "OFF");
        Serial.println("Device4 OFF");
        }
    }
    delay(100);
}
void without_internet(){
    //Manual Switch Control
    if (digitalRead(SwitchPin1) == LOW){
      delay(200);
      if(toggleState_1 == 1){
        digitalWrite(RelayPin1, LOW); // turn on relay 1
        toggleState_1 = 0;
        Serial.println("Device1 ON");
        }
      else{
        digitalWrite(RelayPin1, HIGH); // turn off relay 1
        toggleState_1 = 1;
        Serial.println("Device1 OFF");
        }
     }
    else if (digitalRead(SwitchPin2) == LOW){
      delay(200);
      if(toggleState_2 == 1){
        digitalWrite(RelayPin2, LOW); // turn on relay 2
        toggleState_2 = 0;
        Serial.println("Device2 ON");
        }
      else{
        digitalWrite(RelayPin2, HIGH); // turn off relay 2
        toggleState_2 = 1;
        Serial.println("Device2 OFF");
        }
    }
    else if (digitalRead(SwitchPin3) == LOW){
      delay(200);
      if(toggleState_3 == 1){
        digitalWrite(RelayPin3, LOW); // turn on relay 3
        toggleState_3 = 0;
        Serial.println("Device3 ON");
        }
      else{
        digitalWrite(RelayPin3, HIGH); // turn off relay 3
        toggleState_3 = 1;
        Serial.println("Device3 OFF");
        }
    }
    else if (digitalRead(SwitchPin4) == LOW){
      delay(200);
      if(toggleState_4 == 1){
        digitalWrite(RelayPin4, LOW); // turn on relay 4
        toggleState_4 = 0;
        Serial.println("Device4 ON");
        }
      else{
        digitalWrite(RelayPin4, HIGH); // turn off relay 4
        toggleState_4 = 1;
        Serial.println("Device4 OFF");
        }
    }
    delay(100);
}

void setup() {
  Serial.begin(9600);

  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);

  // Waiting for Wifi connect
  if (WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting...");
  }
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);
  
  //During Starting WiFi LED should TURN OFF
  digitalWrite(wifiLed, HIGH);

  // server address, port and URL
  webSocket.begin("iot.sinric.com", 80, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);

  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {

  if (WiFiMulti.run() != WL_CONNECTED)
  {  
     Serial.println("Not Connected");
    digitalWrite(wifiLed, HIGH);
    without_internet();
  }
  else
  {
    Serial.println(" Connected");
    digitalWrite(wifiLed, LOW);
    with_internet();
    webSocket.loop();
  }

  if (isConnected) {
    uint64_t now = millis();

    // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
    if ((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
      heartbeatTimestamp = now;
      webSocket.sendTXT("H");
    }
  }
}

void setPowerStateOnServer(String deviceId, String value) {
  #if ARDUINOJSON_VERSION_MAJOR == 5
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
  #endif
  #if ARDUINOJSON_VERSION_MAJOR == 6
    DynamicJsonDocument root(1024);
  #endif
  
    root["deviceId"] = deviceId;
    root["action"] = "setPowerState";
    root["value"] = value;
    StreamString databuf;
  #if ARDUINOJSON_VERSION_MAJOR == 5
    root.printTo(databuf);
  #endif
  #if ARDUINOJSON_VERSION_MAJOR == 6
    serializeJson(root, databuf);
  #endif
  webSocket.sendTXT(databuf);
}
