#define DigitalReadPin 10
#define CountsPerInchMeasured 98
#define ArrayLength 10
#define JumpThreshold 15
#define AvgThreshold 2
volatile uint32_t count;
uint32_t movAvg[ArrayLength] = {0}; //moving average array
uint32_t movIndex;      //array index
uint32_t movSum;         //current array sum
uint32_t oldAvg;
uint32_t cycleCount;
void setup() {
  Serial.begin(9600);
  pinMode(DigitalReadPin,INPUT);
  movIndex =0;
  movSum=0;
  oldAvg=0;
  cycleCount=0;
}

void loop() {
  
  

  if(digitalRead(DigitalReadPin)){  //once pin goes high, enters function
    reading();
  }
  if(((count-JumpThreshold) < (movSum/ArrayLength)) || (movAvg[movIndex]==0)){  //independent reading threshold
    movSum = movSum - movAvg[movIndex];
    movAvg[movIndex] = count;
    movSum += count;
    movIndex = (movIndex+1)%ArrayLength;
  }
  if(((oldAvg-AvgThreshold) < (movSum/ArrayLength)) ||((oldAvg+AvgThreshold) > (movSum/ArrayLength)) || (cycleCount<1000)){ //moving average threshold
    Serial.println(movSum/ArrayLength, DEC);
    oldAvg = movSum/ArrayLength;
    cycleCount++;
  }
}

void reading()  {
  count = 0;   //reset count
  while(digitalRead(DigitalReadPin)){  //increments count as long as pin is high
    count++;
  }
  count = count/CountsPerInchMeasured;  //sets count to inches
}
