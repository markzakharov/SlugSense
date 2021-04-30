#define AnalogReadPin A2
#define DigitalReadPin 10
#define MicrosToInches 147  //digital width conversion, 147 microseconds per inch measured
#define AnalogToInches 2   //Unit conversion of int reading to inches measured
#define ArrayLength 100
#define JumpThreshold 75
#define AvgThreshold 2

unsigned long microTime;
uint32_t cycleCount;

volatile uint32_t inches;
uint32_t movAvg[ArrayLength] = {0}; //moving average array
uint32_t movIndex;      //array index
uint32_t movSum;         //current array sum
uint32_t oldAvg;

volatile uint32_t inches_analog;
uint32_t movAvg_analog[ArrayLength] = {0}; //moving average array
uint32_t movIndex_analog;      //array index
uint32_t movSum_analog;         //current array sum
uint32_t oldAvg_analog;


void setup() {
  Serial.begin(9600);
  pinMode(DigitalReadPin,INPUT);
  cycleCount=0;
  
  inches=0;
  movIndex=0;
  movSum=0;
  oldAvg=0;
  
  inches_analog=0;
  movIndex_analog=0;
  movSum_analog=0;
  oldAvg_analog=0;
}

void loop() {

  if(digitalRead(DigitalReadPin)){  //once pin goes high, enters function
    reading();
  }
  
  //DIGITAL WIDTH MOVING FILTER, COMPARE ME TO ANALOG VALUES
  
  if(((movAvg[movIndex]-JumpThreshold) < inches) || ((movAvg[movIndex]+JumpThreshold) > inches) || (movAvg[movIndex]==0)){  //independent reading threshold
    movSum = movSum - movAvg[movIndex];
    movAvg[movIndex] = inches;
    movSum += inches;
    movIndex = (movIndex+1)%ArrayLength;
  }
  if(((oldAvg-AvgThreshold) < (movSum/ArrayLength)) || ((oldAvg+AvgThreshold) > (movSum/ArrayLength)) || (cycleCount<1000)){ //moving average threshold
    Serial.print(micros(),DEC);
    Serial.print(" , ");
    Serial.print(movSum/ArrayLength, DEC);
    
    oldAvg = movSum/ArrayLength;
    cycleCount++;
  }
  else{
    Serial.print(micros(),DEC);
    Serial.print(" , ");
    Serial.print(oldAvg, DEC);
  }

  //PRINTED RESULTS ARE THE SAME, MAYBE ANALOG MIGHT NEED LESS FILTERING????? MAYBE
  if(((movAvg_analog[movIndex_analog]-JumpThreshold) < inches_analog) || ((movAvg_analog[movIndex_analog]+JumpThreshold) > inches_analog) || (movAvg_analog[movIndex_analog]==0)){  //independent reading threshold
    movSum_analog = movSum_analog - movAvg_analog[movIndex_analog];
    movAvg_analog[movIndex_analog] = inches_analog;
    movSum_analog += inches_analog;
    movIndex_analog = (movIndex_analog+1)%ArrayLength;
  }
  if(((oldAvg_analog-AvgThreshold) < (movSum_analog/ArrayLength)) || ((oldAvg_analog+AvgThreshold) > (movSum_analog/ArrayLength)) || (cycleCount<1000)){ //moving average threshold
    Serial.print(" , ");
    Serial.println(movSum_analog/ArrayLength, DEC);
    
    oldAvg_analog = movSum_analog/ArrayLength;
    cycleCount++;
  }
  else{
    Serial.print(" , ");
    Serial.println(oldAvg_analog, DEC);
  }
  
}

void reading()  {

  
  //DIGITAL WIDTH EVALUATION, COMPARE ME TO ANALOG VALUES
  
  microTime = micros();   //reset inches
  while(digitalRead(DigitalReadPin)){  //busy wait
  }
  microTime = micros()- microTime;  //sets inches to inches
  inches = (uint32_t) microTime/MicrosToInches;
  inches_analog = (uint32_t) (analogRead(AnalogReadPin)/AnalogToInches);

}
