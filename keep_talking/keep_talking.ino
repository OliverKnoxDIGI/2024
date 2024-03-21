//oliver knox 19308
//keep talking assesment

#include "LibPrintf.h"

const int wire_1 = 1;
const int wire_2 = 2;
const int wire_3 = 3;
const int CORRECTWIRE = 3;

int wire_cut = 0;

void setup() {
  // put your setup code here, to run once:
 pinMode(wire_1, INPUT);
 pinMode(wire_2, INPUT);
 pinMode(wire_3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
cut_wires();
}

void cut_wires() {
 //3 wires
 // digital 
 wire_cut = digitalRead(CORRECTWIRE);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (wire_cut == HIGH) {
    
    printf("task complete");
  } else {

    printf("task failed");
 
  }
}
void buttons() {
  
}
