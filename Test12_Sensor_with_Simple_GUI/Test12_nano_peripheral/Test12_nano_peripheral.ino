/*
  LED

  This example creates a BLE peripheral with service that contains a
  characteristic to control an LED.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic BLE central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>


BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
BLEByteCharacteristic motorCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
BLEByteCharacteristic notifyCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

const int ledPin = LED_BUILTIN; // pin to use for the LED
int prevVal = 1;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    // Serial.println("starting BLE failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);
  ledService.addCharacteristic(motorCharacteristic);
  ledService.addCharacteristic(notifyCharacteristic);
  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);
  motorCharacteristic.writeValue(0);
  notifyCharacteristic.writeValue(0);
  // start advertising
  BLE.advertise();

  // Serial.println("BLE LED Peripheral");
}



void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    // Serial.print("Connected to central: ");
    // print the central's MAC address:
    // Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      // if (switchCharacteristic.written()) {
      //   Serial.println(switchCharacteristic.value());
      //   if (switchCharacteristic.value()%2) {   // any value other than 0
      //     Serial.println("LED on");
      //     digitalWrite(ledPin, HIGH);         // will turn the LED on
      //     switchCharacteristic.writeValue(1);
      //   } else {                              // a 0 value
      //     Serial.println(F("LED off"));
      //     digitalWrite(ledPin, LOW);          // will turn the LED off
      //     switchCharacteristic.writeValue(0);
      //   }
      //   // switchCharacteristic.writeValue(switchCharacteristic.value());
      //   // switchCharacteristic.writeValue(1);
      // }

      if(Serial.available()) {  // if data is available to read
        int val = Serial.read();
        
        if(val != prevVal){
          prevVal = val;
          if(val <= 6){
            switchCharacteristic.writeValue(val);
            // notifyCharacteristic.writeValue(val);
          } else if (val >= 25){
            motorCharacteristic.writeValue(val);
          } 
        } 
        // if(val == 50) {
        //   // Serial.println("RED ON");
        //   switchCharacteristic.writeValue(1);
        // }
        // if(val == 100) {
        //   // Serial.println("BLUE ON");
        //   switchCharacteristic.writeValue(2);
        // }
        // if(val == 150) {
        //   // Serial.println("GREEN ON");
        //   switchCharacteristic.writeValue(3);
        // }
        // if(val == 200) {
        //   // Serial.println("ALL OFF");
        //   switchCharacteristic.writeValue(0);
        // }
      }   
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
