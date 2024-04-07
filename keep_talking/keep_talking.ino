//oliver knox 19308
//keep talking assesment

#include <Wire.h> 

//TEACHER COMMENTS what is HELPER_ADDR maybe a better name is needed
const byte HELPER_ADDR = 1;


//TEACHER COMMENTS what is this variable used for?
int alive = 1;

//TEACHER COMMENTS what are these for?
const int wire_1 = 1;
const int wire_2 = 2;
const int wire_3 = 3;
const int failLed = 9;
const int passedLed = 10;

//TEACHER COMMENTS what about these?
const int button1 = 4;
const int button2 = 5;
const int button3 = 6;
const int button4 = 7;
const int button5 = 8;

//TEACHER COMMENTS what are these for?
boolean button1_pressed = false;
boolean button2_pressed = false;
boolean button3_pressed = false;
boolean button4_pressed = false;
boolean button5_pressed = false;


void setup() {
  // put your setup code here, to run once:
    Wire.begin(HELPER_ADDR);
   Wire.onRequest(requestEvent);
  Serial.begin(9600);
  pinMode(wire_1, INPUT);
  pinMode(wire_2, INPUT);
  pinMode(wire_3, INPUT);
  pinMode(failLed, OUTPUT);
  pinMode(passedLed, OUTPUT);


}

void loop() {
  //TEACHER COMMENTS what is this chunk of code doing?
  boolean val = cut_wires();
  if (val == true) {
  //send event won
    alive = 1;
    buttons(); //TEACHER COMMENTS does this mean you have to do the cut wires module first? why not separate these out into two 
  } else {
   //  event lost
     alive = 0;
  }
  boolean val2 = buttons();
  if (val2 == true) {
     Serial.println("game won");
  } else{
    alive = 0;
    Serial.println("game Lost");
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

//button seq = 1,2,3,4,5
//TEACHER COMMENTS also explain where the return statement has disappeared to?
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
    return false;
  }

  if (digitalRead(button3) == HIGH && button2_pressed == true) {
    button3_pressed = true;
    Serial.println("correct button pressed");
  }
  else if (digitalRead(button3) == HIGH && button2_pressed == false) {
    Serial.println("task failed");
    return false;
  }

  if (digitalRead(button4) == HIGH && button3_pressed == true) {
    button4_pressed = true;
    Serial.println("correct button pressed");
  }
  else if (digitalRead(button4) == HIGH && button3_pressed == false) {
    Serial.println("task failed");
    return false;
  }

  if (digitalRead(button5) == HIGH && button4_pressed == true) {
    button5_pressed = true;
    Serial.println("correct button pressed");
    return true;
  }
  else if (digitalRead(button5) == HIGH && button4_pressed == false) {
    Serial.println("task failed");
    return false;
  }

}

//TEACHER COMMENTS so what is this method for and what potential values are expected to be sent?
void requestEvent(){
  //reply to the transmission request with this message
  Wire.write(alive);
  Serial.println(alive);
}
