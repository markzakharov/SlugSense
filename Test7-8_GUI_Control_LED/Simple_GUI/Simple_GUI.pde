import controlP5.*;  // import ControlP5 library
import processing.serial.*;

// this program creates buttons to control Arduino Nana BLE 33

Serial port;

ControlP5 cp5;  // create ControlP5 object
PFont font;

void setup() {  // same as Arduino program



  size(900, 1000);  // window size (width, height)
  
  printArray(Serial.list());  // prints all available serial ports
  
  port = new Serial(this, "COM6", 9600);  // Arduino connected to this port
  
  cp5 = new ControlP5(this);
  font = createFont("courier new bold", 40);
  
  cp5.addButton("red")
    .setPosition(350, 170)
    .setSize(200, 150)
    .setColorBackground(color(171, 211, 210))
    .setFont(font)
  ;
  
  cp5.addButton("blue")
    .setPosition(350, 370)
    .setSize(200, 150)
    .setColorBackground(color(171, 211, 210))
    .setFont(font)

  ;
  
  cp5.addButton("green")
    .setPosition(350, 570)
    .setSize(200, 150)
    .setColorBackground(color(171, 211, 210))
    .setFont(font)

  ;
  
  cp5.addButton("All_Off")
    .setPosition(350, 770)
    .setSize(200, 150)
    .setColorBackground(color(171, 211, 210))
    .setFont(font)
  ;

}

void draw() {  // same as loop in Arduino
  
 

  
  background(103, 24, 49);  // background color of window (r,g,b)
  
  textSize(40);
  textFont(font);
  text("ARDUINO CONTROL PANEL", 190, 100);  // ("text", x-coord, y-coord)
}

// Button Functions
void red() {
  port.write('r'); 
}

void blue() {
  port.write('b'); 
}

void green() {
  port.write('g'); 
}

void All_Off() {
  port.write('f'); 
}
