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

// SENSOR DEFINES
#define DigitalReadPin 10
#define RXCmdPin 9 // sends control signals to get sensor readings
#define MicrosToInches 147  //digital width conversion, 147 microseconds per inch measured
#define ArrayLength 10
#define JumpThreshold 75
#define AvgThreshold 2
#define ReadIntervalUs 100000 // delay between sensor readings (in us)

#define RED 22     
#define BLUE 24  
#define GREEN 23

//BLEByteCharacteristic switchCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// SENSOR VARIABLES
unsigned long microTime = 0;
unsigned long readTime = 0; // time of last reading (in us)
uint32_t cycleCount = 0;

uint32_t inches = 0;
uint32_t movAvg[ArrayLength] = {0}; //moving average array
uint8_t movIndex = 0;      //array index
uint32_t movSum = 0;         //current array sum
uint32_t oldAvg = 0;

// variables for button
const int buttonPin = 2;
int oldButtonState = LOW;

int prevValue = 1;

void setup() {
  // SENSOR INITS
  Serial.begin(9600);
  pinMode(DigitalReadPin,INPUT);
  pinMode(RXCmdPin, OUTPUT);
  digitalWrite(RXCmdPin, LOW);
  
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
    //if (ledCharacteristic.valueUpdated()) {
      Serial.print("1 ");
      Serial.println(micros(),DEC);
      
      ledCharacteristic.readValue(value);
      
      Serial.print("2 ");
      Serial.println(micros(),DEC);
      
      // SENSOR RUN
      if (micros() - readTime >= ReadIntervalUs) {
      digitalWrite(RXCmdPin, HIGH);
      }
    
      if(digitalRead(DigitalReadPin)){  //once pin goes high, enters function
        // DIGITAL WIDTH EVALUATION
        microTime = micros();   //reset inches
        readTime = microTime;
        //while(digitalRead(DigitalReadPin)){  //busy wait
        //}
        microTime = micros()- microTime;  //sets inches to inches
        inches = (uint32_t) microTime/MicrosToInches;
        //inches_analog = (uint32_t) (analogRead(AnalogReadPin)/AnalogToInches);
      
        // Apply digital moving filter
        if(((movAvg[movIndex]-JumpThreshold) < inches) || ((movAvg[movIndex]+JumpThreshold) > inches) || (movAvg[movIndex]==0)){  //independent reading threshold
          movSum = movSum - movAvg[movIndex];
          movAvg[movIndex] = inches;
          movSum += inches;
          movIndex = (movIndex+1)%ArrayLength;
        }
      
        if(((oldAvg-AvgThreshold) < (movSum/ArrayLength)) || ((oldAvg+AvgThreshold) > (movSum/ArrayLength)) || (cycleCount<1000)){ //moving average threshold
          //Serial.print(micros(),DEC);
          //Serial.print(" , ");
          //Serial.println(movSum/ArrayLength, DEC);
          
          oldAvg = movSum/ArrayLength;
          cycleCount++;
        }
        else{
          //Serial.print(micros(),DEC);
          //Serial.print(" , ");
          //Serial.println(oldAvg, DEC);
        }
        
        digitalWrite(RXCmdPin, LOW);
        
        
        Serial.print("3 ");
        Serial.println(micros(),DEC);
      }
      
    //}
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
