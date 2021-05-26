/*
  Peripheral Explorer

  This example scans for BLE peripherals until one with a particular name ("LED")
  is found. Then connects, and discovers + prints all the peripheral's attributes.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use it with another board that is compatible with this library and the
  Peripherals -> LED example.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

const int ledPin = 12; // pin to use for the LED

void setup() {
  // begin initialization
  if (!BLE.begin()) {
    while (1);
  }

  Serial.println("BLE Central - Peripheral Explorer");

  // start scanning for peripherals
  BLE.scan();
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // see if peripheral is a LED
    if (peripheral.localName() == "LED") {
      // stop scanning
      BLE.stopScan();

      explorerPeripheral(peripheral);

      while(1){}
    }
    
  }
}


void explorerPeripheral(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
      uint32_t value;
      BLECharacteristic ledCharacteristic = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");
      while (peripheral.connected()) {
          //BLECharacteristic ledCharacteristic = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");
          ledCharacteristic.readValue(value);
          Serial.println(value);
          /*if (value) {
            Serial.println("Write High");
            //digitalWrite(ledPin, HIGH);
          } else {
            Serial.println("Write Low");
            //digitalWrite(ledPin, LOW);
          }*/
      }
    
  } else {
    //Serial.println("Failed to connect!");
    return;
  }

  // we are done exploring, disconnect
  //Serial.println("Disconnecting ...");
  //peripheral.disconnect();
  //Serial.println("Disconnected");
}


/*


void exploreService(BLEService service) {
  // print the UUID of the service
  //Serial.print("Service ");
  //Serial.println(service.uuid());

  // loop the characteristics of the service and explore each
  for (int i = 0; i < service.characteristicCount(); i++) {
    BLECharacteristic characteristic = service.characteristic(i);

    exploreCharacteristic(characteristic);
  }
}

void exploreCharacteristic(BLECharacteristic characteristic) {
  // print the UUID and properties of the characteristic
  //Serial.print("\tCharacteristic ");
  //Serial.print(characteristic.uuid());
  //Serial.print(", properties 0x");
  //Serial.print(characteristic.properties(), HEX);
  
  // check if the characteristic is readable
  if (characteristic.canRead()) {
    // read the characteristic value
    characteristic.read();

    if (characteristic.valueLength() > 0) {
      // print out the value of the characteristic
      //Serial.print(", value 0x");
      printData(characteristic.value(), characteristic.valueLength());
    }
  }
  //Serial.println();

  // loop the descriptors of the characteristic and explore each
  for (int i = 0; i < characteristic.descriptorCount(); i++) {
    BLEDescriptor descriptor = characteristic.descriptor(i);

    exploreDescriptor(descriptor);
  }
}

void exploreDescriptor(BLEDescriptor descriptor) {
  // print the UUID of the descriptor
  //Serial.print("\t\tDescriptor ");
  //Serial.print(descriptor.uuid());

  // read the descriptor value
  descriptor.read();

  // print out the value of the descriptor
  //Serial.print(", value 0x");
  printData(descriptor.value(), descriptor.valueLength());

  //Serial.println();
}

void printData(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];

    if (b < 16) {
      //Serial.print("0");
    }

    //Serial.print(b, HEX);
  }
}


*/
