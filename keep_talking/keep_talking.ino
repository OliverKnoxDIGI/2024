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
 Serial.begin(9600);
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

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(wire_1) == LOW) {
    
    printf("task failed");
  }
  
  if (digitalRead(wire_2) == LOW)  {

    printf("task failed");
 
  }

    if (digitalRead(wire_3) == LOW)  {

    printf("task complete");
 
  }
}
void buttons() {
  
}
