//oliver knox 19308
//keep talking assesment

// using the wire libary so we can communicate using two or more arduinos
#include <Wire.h>

//Helper address is used as a constant to send the information to the controller
const byte HELPER_ADDR = 1;

// this variable is used to determain if the player is alive or not, and later send to the controller
int alive = 0;
int wirePassed = 0;
int buttonPassed = 0;

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

int position = 0;

char ans[] = { 'Q', 'W', 'E', 'R', 'T', '\0'};
char guess[] = { 'x', 'x', 'x', 'x', 'x', '\0'};
  

int val = 0;
int val2 = 0;


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
  int val = cut_wires();
  // check if won
  if (val == 2) {
    // check if minigame has already been won, if not
    if (wirePassed == 0) {
      // make sure game cannot be won again
      wirePassed = 1;
      // send alive value to controller (add one)
      alive = alive + 1;
    }
    // if the game has already been won
    else
    { Serial.println("cheater");
    }
    // if the game is lost, send 99 (lose number) to the controller
  } else if (val == 1) {
    alive = 99;
    //Serial.println("game lost");
  } else {}


  // same as prev for buttons game

  int val2 = buttons();
  if (val2 == 2) {
    // event won
    // check if minigame has already been won, if not
    if (buttonPassed == 0) {
      // make sure game cannot be won again
      buttonPassed = 1;
      // send alive value to controller ( add one)
      alive = alive + 8;

    }
    // if the game has already been won
    else
    { Serial.println("cheater");
    }
  } else if (val2 == 1) {
    alive = 99;
    //Serial.println("game lost");
  } else {}



}

//cut wires game, if right most wire is cut, player wins.
// 0 is unplayed, 1 is lose, and 2 is win
int cut_wires() {
  //3 wires
  digitalWrite(failLed, LOW);
  digitalWrite(passedLed, LOW);
  // left most wire
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(wire_1) == LOW) {
    digitalWrite(passedLed, LOW);
    digitalWrite(failLed, HIGH);
    return 1;
  }
  // middle wire
  if (digitalRead(wire_2) == LOW)  {
    digitalWrite(passedLed, LOW);
    digitalWrite(failLed, HIGH);
    return 1;

  }
  // right most wire
  //winning wire
  if (digitalRead(wire_3) == LOW)  {
    digitalWrite(passedLed, HIGH);
    digitalWrite(failLed, LOW);
    return 2;

  }
  // check if all of the wires are untouched, and return 0 if true
  if (digitalRead(wire_3) == HIGH) {
    if (digitalRead(wire_2) == HIGH) {
      if (digitalRead(wire_1) == HIGH) {
        return 0;
      }
    }
  }
}





//button seq = 1,2,3,4,5 (right to left)
// 0 is unplayed, 1 is lose, and 2 is win
int buttons() {
  
  //5 buttons pressed in correct sequence
  // LOW = pressed
  // HIGH = untouched

  
  if (digitalRead(button1) == LOW){
    guess[position] = 'Q';
    position++;
    delay(500);   
  }
    if (digitalRead(button2) == LOW){
    guess[position] = 'W';
    position++;
    delay(500);
    if ((ans[position]) != (guess[position])){return 1;}
  }
    if (digitalRead(button3) == LOW){
    guess[position] = 'E';
    position++;
    delay(500);
    if ((ans[position]) != (guess[position])){return 1;}
  }
   if (digitalRead(button4) == LOW){
    guess[position] = 'R';
    position++;
    delay(500);
    if ((ans[position]) != (guess[position])){return 1;}
  }
    if (digitalRead(button5) == LOW){
    guess[position] = 'T';
    position++;
    delay(500);
    if ((ans[position]) != (guess[position])){return 1;}
  }
  
  if (ans[2] == guess[2]) {return 2;}
  
  
  
  
  

}

//TEACHER COMMENTS so what is this method for and what potential values are expected to be sent?
void requestEvent() {
  //reply to the transmission request with this message
  Wire.write(alive);


}
