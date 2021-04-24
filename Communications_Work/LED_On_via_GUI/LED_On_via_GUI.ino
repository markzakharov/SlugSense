 #define RED 22     
 #define BLUE 24  
 #define GREEN 23
 //#define LED_PWR 25

// this program is to turn on an LED based on input from GUI

//const int RED = 22;
//const int BLUE = 23;
//const int GREEN = 24;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  //pinMode(LED_PWR, OUTPUT);

  //digitalWrite(RED, LOW);
  //digitalWrite(BLUE, LOW);
  //digitalWrite(GREEN, LOW);
  
  Serial.begin(9600);

   digitalWrite(RED, HIGH);
   digitalWrite(BLUE, HIGH);
   digitalWrite(GREEN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

 
  
  if(Serial.available()) {  // if data is available to read
    char val = Serial.read();

    if(val == 'r') {
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
    }
    if(val == 'b') {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
    }
    if(val == 'g') {
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);
    }
    /*if(val == 'f') {
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);
    }*/
  }
}
