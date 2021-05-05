import controlP5.*;  // import ControlP5 library
import processing.serial.*;

// this program creates buttons to control Arduino Nana BLE 33

Serial port;

ControlP5 cp5;  // create ControlP5 object
PFont font;

int slider = 0;

void setup() {  // same as Arduino program



  size(300, 100);  // window size (width, height)
  
  printArray(Serial.list());  // prints all available serial ports
  
  // DON'T FORGET TO CHANGE COM PORT!!
  port = new Serial(this, "/dev/cu.usbmodem14201", 9600);  // Arduino connected to this port
  
  cp5 = new ControlP5(this);
  font = createFont("courier new bold", 40);

  // int value = 0;
  
  // cp5.addButton("red")
  //   .setPosition(350, 170)
  //   .setSize(200, 150)
  //   .setColorBackground(color(171, 211, 210))
  //   .setFont(font)
  // ;
  
  // cp5.addButton("blue")
  //   .setPosition(350, 370)
  //   .setSize(200, 150)
  //   .setColorBackground(color(171, 211, 210))
  //   .setFont(font)

  // ;
  
  // cp5.addButton("green")
  //   .setPosition(350, 570)
  //   .setSize(200, 150)
  //   .setColorBackground(color(171, 211, 210))
  //   .setFont(font)

  // ;
  
  // cp5.addButton("All_Off")
  //   .setPosition(350, 770)
  //   .setSize(200, 150)
  //   .setColorBackground(color(171, 211, 210))
  //   .setFont(font)
  // ;

  cp5.addSlider("slider")
    .setPosition(50, 40)
    .setSize(200, 20)
    .setRange(0, 200)
    .setNumberOfTickMarks(5)
    // .setValue(50)
    ;
}

void draw() {  // same as loop in Arduino
  
 

    
 
  background(103, 24, 49);  // background color of window (r,g,b)
  
  textSize(40);
  textFont(font);
  // text("ARDUINO CONTROL PANEL", 190, 100);  // ("text", x-coord, y-coord)
}

// // Button Functions
// void red() {
//   port.write('r'); 
// }

// void blue() {
//   port.write('b'); 
// }

// void green() {
//   port.write('g'); 
// }

// void All_Off() {
//   port.write('f'); 
// }

// Slider Functions
void slider(int slider) {
  port.write(slider);
  
}

