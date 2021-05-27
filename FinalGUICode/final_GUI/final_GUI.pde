import controlP5.*;  // import ControlP5 library
import processing.serial.*;

// this program creates buttons to control Arduino Nana BLE 33

Serial port;

ControlP5 cp5;  // create ControlP5 object
PFont font;

int slider = 0;

void setup() {  // same as Arduino program



  size(325, 215);  // window size (width, height)
  
  printArray(Serial.list());  // prints all available serial ports
  
  // DON'T FORGET TO CHANGE COM PORT!!
  port = new Serial(this, "COM7", 9600);  // Arduino connected to this port, peripheral
  
  cp5 = new ControlP5(this);
  font = createFont("Times", 20);

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

  cp5.addSlider("max_distance")
    .setPosition(30, 60)
    .setSize(200, 30)
    .setRange(1, 6)
    .setNumberOfTickMarks(6)
    .setColorBackground(color(39, 88, 179))
    // .setValue(50)
    ;

  cp5.addSlider("motor_intensity")
    .setPosition(30, 140)
    .setSize(200, 30)
    .setRange(25, 100)
    .setNumberOfTickMarks(4)
    .setColorBackground(color(39, 88, 179))
    // .setValue(50)
    ;  
}

void draw() {  // same as loop in Arduino
 
  background(0, 139, 139);  // background color of window (r,g,b)
  
  textSize(20);
  textFont(font);
  text("SLUG SENSE GUI CONTROL", 30, 40);  // ("text", x-coord, y-coord)
  textSize(16);
  text("(feet)", 115, 115);
  text("(%)", 120, 195);
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
void max_distance(int slider1) {
  port.write(slider1);
  
}
void motor_intensity(int slider2) {
  port.write(slider2);
  
}
