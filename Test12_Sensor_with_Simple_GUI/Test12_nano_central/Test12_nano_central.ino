/*
  LED Control

  This example scans for BLE peripherals until one with the advertised service
  "19b10000-e8f2-537e-4f6c-d104768a1214" UUID is found. Once discovered and connected,
  it will remotely control the BLE Peripheral's LED, when the button is pressed or released.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button with pull-up resistor connected to pin 2.

  You can use it with another board that is compatible with this library and the
  Peripherals -> LED example.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

#define RED 22     
#define BLUE 24  
#define GREEN 23

//BLEByteCharacteristic switchCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// variables for button
const int buttonPin = 2;
int oldButtonState = LOW;

int prevValue = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  // Serial.begin(9600);

  // initialize LEDs
  digitalWrite(RED, HIGH); 
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);

  // while (!Serial);

  // configure the button pin as input
  pinMode(buttonPin, INPUT);

  // initialize the BLE hardware
  BLE.begin();

  // Serial.println("BLE Central - LED control");

  // add characteristic to the service
  //ledService.addCharacteristic(switchCharacteristic);

  // start scanning for peripherals
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    // Serial.print("Found ");
    // Serial.print(peripheral.address());
    // Serial.print(" '");
    // Serial.print(peripheral.localName());
    // Serial.print("' ");
    // Serial.print(peripheral.advertisedServiceUuid());
    // Serial.println();

    if (peripheral.localName() != "LED") {
      return;
    }

    // stop scanning
    BLE.stopScan();

    controlLed(peripheral);

    // peripheral disconnected, start scanning again
    BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  }
}

void controlLed(BLEDevice peripheral) {
  // connect to the peripheral
  // Serial.println("Connecting ...");

  if (peripheral.connect()) {
    // Serial.println("Connected");
    // When connected are discovered, RED LED blinks twice
    digitalWrite(RED, LOW);
    delay(1000);
    digitalWrite(RED, HIGH);
    delay(1000);
    digitalWrite(RED, LOW);
    delay(1000);
    digitalWrite(RED, HIGH);
  } else {
    // Serial.println("Failed to connect!");
    return;
  }

  // discover peripheral attributes
  // Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    // Serial.println("Attributes discovered");
    // When attributes are discovered, BLUE LED blinks twice
    digitalWrite(BLUE, LOW);
    delay(1000);
    digitalWrite(BLUE, HIGH);
    delay(1000);
    digitalWrite(BLUE, LOW);
    delay(1000);
    digitalWrite(BLUE, HIGH);
  } else {
    // Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  // retrieve the LED characteristic
  BLECharacteristic ledCharacteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");

  if (!ledCharacteristic) {
    // Serial.println("Peripheral does not have LED characteristic!");
    peripheral.disconnect();
    return;
  } else if (!ledCharacteristic.canWrite()) {
    // Serial.println("Peripheral does not have a writable LED characteristic!");
    peripheral.disconnect();
    return;
  }

  byte var = 0;
  uint32_t value;

  while (peripheral.connected()) {
    // while the peripheral is connected

    // ledCharacteristic.writeValue(var);
    // var =  var + 1;
    if (ledCharacteristic.valueUpdated()) {
      Serial.println("Value updated");
      ledCharacteristic.readValue(value);
      
      if(value != prevValue){
        prevValue = value;
        Serial.println(value);
        if(value == 50) {  // RED ON
          digitalWrite(RED, LOW);
          digitalWrite(GREEN, HIGH);
          digitalWrite(BLUE, HIGH);
        } else if(value == 100) { // BLUE ON
          digitalWrite(RED, HIGH);
          digitalWrite(GREEN, HIGH);
          digitalWrite(BLUE, LOW);
        } else if(value == 150) {  // GREEN ON
          digitalWrite(RED, HIGH);
          digitalWrite(GREEN, LOW);
          digitalWrite(BLUE, HIGH);
        } else if (value == 0) {  // ALL OFF
          digitalWrite(RED, HIGH);
          digitalWrite(BLUE, HIGH);
          digitalWrite(GREEN, HIGH);
        }
      }
    }
    // Serial.println(value);

    // read the button pin
    //int buttonState = digitalRead(buttonPin);
    /*int buttonState = !oldButtonState;
    
    if (oldButtonState != buttonState) {
      // button changed
      oldButtonState = buttonState;

      if (buttonState) {
        Serial.println("button pressed");
        // button is pressed, write 0x01 to turn the LED on
        
        ledCharacteristic.writeValue((byte)0x01);
      } else {
        Serial.println("button released");

        // button is released, write 0x00 to turn the LED off
        ledCharacteristic.writeValue((byte)0x00);
      }
    }*/
  }

  // Serial.println("Peripheral disconnected");
}
