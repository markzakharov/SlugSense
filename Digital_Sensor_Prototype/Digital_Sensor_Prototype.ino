#define DigitalReadPin 10
#define RXCmdPin 9          // sends control signals to get sensor readings
#define MicrosToInches 147  // digital width conversion, 147 microseconds per inch measured
#define AnalogToInches 2    // Unit conversion of int reading to inches measured
#define ArrayLength 10      // captures 1 sec of sensor readings
#define JumpThreshold 75    // may need to change to increase/decrease sensitivity
#define AvgThreshold 2
#define ReadIntervalUs 100000 // delay between sensor readings (in us)

unsigned long microTime;
unsigned long readTime = 0; // time of last reading (in us)
uint32_t cycleCount;        // number of readings since startup

volatile uint32_t inches;
uint32_t movAvg[ArrayLength] = {0}; //moving average array
uint8_t movIndex;        //array index
uint32_t movSum;         //current array sum
uint32_t oldAvg;

void setup() {
  Serial.begin(9600);
  pinMode(DigitalReadPin,INPUT);
  pinMode(RXCmdPin, OUTPUT);
  cycleCount=0;
  
  inches=0;
  movIndex=0;
  movSum=0;
  oldAvg=0;
  
  digitalWrite(RXCmdPin, LOW);
}

void loop() {

  if (micros() - readTime >= ReadIntervalUs) {
    digitalWrite(RXCmdPin, HIGH);
  }

  if(digitalRead(DigitalReadPin)){  //once pin goes high, enters function
    reading();
  }
  
}

void reading()  {

  
  //DIGITAL WIDTH EVALUATION, COMPARE ME TO ANALOG VALUES
  
  microTime = micros();   //reset inches
  while(digitalRead(DigitalReadPin)){  //busy wait
  }
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
    Serial.print(micros(),DEC);
    Serial.print(" , ");
    Serial.println(movSum/ArrayLength, DEC);
    
    oldAvg = movSum/ArrayLength;
    cycleCount++;
  }
  else{
    Serial.print(micros(),DEC);
    Serial.print(" , ");
    Serial.println(oldAvg, DEC);
  }
  
  digitalWrite(RXCmdPin, LOW);
  readTime = micros();

}
