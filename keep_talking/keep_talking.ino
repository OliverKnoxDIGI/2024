//oliver knox 19308
//keep talking assesment

// using the wire libary so we can communicate using two or more arduinos
#include <Wire.h> 

//Helper address is used as a constant to send the information to the controller
const byte HELPER_ADDR = 1;

// this variable is used to determain if the player is alive or not, and later send to the controller
int alive = 1;

// set the wire pins to constants, allowing changability and readability
const int wire_1 = 1;
const int wire_2 = 2;
const int wire_3 = 3;

// setting the pass and fail LEDs for prev reasons
const int failLed = 9;
const int passedLed = 10;

// same as prev but for the buttons game
const int button1 = 4;
const int button2 = 5;
const int button3 = 6;
const int button4 = 7;
const int button5 = 8;

// setting the "button pressed" vaiable to false, otherwise the player would win instantly
boolean button1_pressed = false;
boolean button2_pressed = false;
boolean button3_pressed = false;
boolean button4_pressed = false;
boolean button5_pressed = false;


void setup() {
  // put your setup code here, to run once:
  // wire begin for helper address, request event, and serial monitor
    Wire.begin(HELPER_ADDR);
   Wire.onRequest(requestEvent);
  Serial.begin(9600);
  
  // setting the wire pins to input
  pinMode(wire_1, INPUT);
  pinMode(wire_2, INPUT);
  pinMode(wire_3, INPUT);
  
  // setting the LED pins to output
  pinMode(failLed, OUTPUT);
  pinMode(passedLed, OUTPUT);


}

void loop() {
  // getting the value from the game code, and determaining if the player passed or not
  boolean val = cut_wires();
  if (val == true) {
  // event won
    alive = 1;
  } else {
   //  event lost
     alive = 0;
  }
  
  // same as prev for buttons game
  boolean val2 = buttons();
  if (val2 == true) {
    //Serial.println("game won");
    alive = 1;
  } else {
    alive = 0;
    //Serial.println("game lost");
  }
}

//cut wires game, if right most wire is cut, player wins.

boolean cut_wires() {
  //3 wires
  digitalWrite(failLed, LOW);
  digitalWrite(passedLed, LOW);
// left most wire
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(wire_1) == LOW) {

    Serial.println("task failed");
    digitalWrite(passedLed, LOW);
    digitalWrite(failLed, HIGH);
    return false;
  }
// middle wire
  if (digitalRead(wire_2) == LOW)  {
    digitalWrite(passedLed, LOW);
    digitalWrite(failLed, HIGH);

    Serial.println("task failed");
    return false;

  }
// right most wire
  if (digitalRead(wire_3) == LOW)  {
    digitalWrite(passedLed, HIGH);
    digitalWrite(failLed, LOW);
    Serial.println("task complete");
    return true;

  }
}

//button seq = 1,2,3,4,5 (right to left)
//TEACHER COMMENTS also explain where the return statement has disappeared to?
boolean buttons() {
button1_pressed = false;
button2_pressed = false;
button3_pressed = false;
button4_pressed = false;

  
  
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
