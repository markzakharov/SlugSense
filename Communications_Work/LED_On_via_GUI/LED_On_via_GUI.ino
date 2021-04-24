 #define RED 22u     
 #define BLUE 24u   
 #define GREEN 23u
 //#define LED_PWR 25

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(LED_PWR, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if(Serial.available()) {  // if data is available to read
    char val = Serial.read();

    if(val == 'r') {
      digitalWrite(RED, HIGH);
    }
    if(val == 'b') {
      digitalWrite(BLUE, HIGH);
    }
    if(val == 'g') {
      digitalWrite(GREEN, HIGH);
    }
    if(val == 'f') {
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);
    }
  }*/
  digitalWrite(RED, HIGH);
  delay(1000);
}
