//oliver knox 19308
//keep talking assesment

#include <Wire.h> 


const byte HELPER_ADDR = 1;
const byte POT = A0;

int alive = 1;


const int wire_1 = 1;
const int wire_2 = 2;
const int wire_3 = 3;
const int failLed = 9;
const int passedLed = 10;


const int button1 = 4;
const int button2 = 5;
const int button3 = 6;
const int button4 = 7;
const int button5 = 8;


boolean button1_pressed = false;
boolean button2_pressed = false;
boolean button3_pressed = false;
boolean button4_pressed = false;
boolean button5_pressed = false;


void setup() {
  // put your setup code here, to run once:
    Wire.begin(HELPER_ADDR);
   pinMode(POT, INPUT);
   Wire.onRequest(requestEvent);
  Serial.begin(9600);
  pinMode(wire_1, INPUT);
  pinMode(wire_2, INPUT);
  pinMode(wire_3, INPUT);
  pinMode(failLed, OUTPUT);
  pinMode(passedLed, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  boolean val = cut_wires();
  if (cut_wires() == true) {
  //send event won
    Wire.write(alive = 1);
    buttons();
  }
  else {
   // send event lost
     Wire.write(alive = 0);
    
    
  }
}

boolean cut_wires() {
  //3 wires

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(wire_1) == LOW) {

    Serial.println("task failed");
    digitalWrite(passedLed, LOW);
    digitalWrite(failLed, HIGH);
    return false;
  }

  if (digitalRead(wire_2) == LOW)  {
    digitalWrite(passedLed, LOW);
    digitalWrite(failLed, HIGH);

    Serial.println("task failed");
    return false;

  }

  if (digitalRead(wire_3) == LOW)  {
    digitalWrite(passedLed, HIGH);
    digitalWrite(failLed, LOW);
    Serial.println("task complete");
    return true;

  }
}
boolean buttons() {

  //5 buttons pressed in correct sequence

  if (digitalRead(button1) == HIGH) {
    button1_pressed = true;
    Serial.println("correct button pressed");
  }

  if (digitalRead(button2) == HIGH && button1_pressed == true) {
    button2_pressed = true;
    Serial.println("correct button pressed");
  } else if (digitalRead(button2) == HIGH && button1_pressed == false) {
    Serial.println("task failed");
  }

  if (digitalRead(button3) == HIGH && button2_pressed == true) {
    button3_pressed = true;
    Serial.println("correct button pressed");
  }
  else if (digitalRead(button3) == HIGH && button2_pressed == false) {
    Serial.println("task failed");
  }

  if (digitalRead(button4) == HIGH && button3_pressed == true) {
    button4_pressed = true;
    Serial.println("correct button pressed");
  }
  else if (digitalRead(button4) == HIGH && button3_pressed == false) {
    Serial.println("task failed");
  }

  if (digitalRead(button5) == HIGH && button4_pressed == true) {
    button5_pressed = true;
    Serial.println("correct button pressed");
  }
  else if (digitalRead(button5) == HIGH && button4_pressed == false) {
    Serial.println("task failed");
  }

}

void requestEvent(){
  //reply to the transmission request with this message
  Wire.write(alive);
  Serial.println(alive);
}
