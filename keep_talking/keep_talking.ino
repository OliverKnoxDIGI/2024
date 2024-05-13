//oliver knox 19308
//keep talking assesment

// using the wire libary so we can communicate using two or more arduinos
#include <Wire.h>

//Helper address is used as a constant to send the information to the controller
const byte HELPER_ADDR = 1;

// this variable is used to determain if the player is alive or not, and later send to the controller
int alive = 0;
// help to determain if player has already passed a minigame
bool wirePassed = false;
bool buttonPassed = false;

// set the wire pins to constants, allowing changability and readability
const int wire_1 = 1;
const int wire_2 = 2;
const int wire_3 = 3;

// setting the pass and fail LEDs for prev reasons

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

  // setting the wire pins to input
  pinMode(wire_1, INPUT);
  pinMode(wire_2, INPUT);
  pinMode(wire_3, INPUT);

  Serial.begin(9600);

}

void loop() {

  // getting the value from the game code, and determaining if the player passed or not
  int val = cut_wires();
  // check if won
  if (val == 2) {
    // check if minigame has already been won, if not
    if (wirePassed == false) {
      // make sure game cannot be won again
      wirePassed = true;
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
    if (buttonPassed == false) {
      // make sure game cannot be won again
      buttonPassed = true;
      // send alive value to controller ( add one)
      alive = alive + 1;

    }
    // if the game has already been won
    else
    { Serial.println("cheater");
    }
  } else if (val2 == 1) {
    alive = 99;
    //Serial.println("game lost");

    //handling is return = 0
  } else {}



}

//cut wires game, if right most wire is cut, player wins.
// 0 is unplayed, 1 is lose, and 2 is win
int cut_wires() {
  //3 wires

  // left most wire

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(wire_1) == LOW) {
    //fail
    return 1;
  }
  // middle wire
  if (digitalRead(wire_2) == LOW)  {

    return 1;

  }
  // right most wire
  //winning wire
  if (digitalRead(wire_3) == LOW)  {
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
  // LOW = untouched
  // HIGH = pressed

  // check if the first "button" is pressed, if it is
  if (digitalRead(button1) == HIGH) {
    
      
    //position 0 of the guess array is changed from x to a Q
    guess[position] = 'Q';

    if ((ans[0]) == (guess[0])) {   

    } else {return 1;}
    // add one to the position
    position=1;
     
    }

  // check if the second "button" is pressed, if it is
   if (digitalRead(button2) == HIGH) {
    //position 1 of the guess array is changed from x to a W
    guess[position] = 'W';
    //check if guess position 1 is equal to ans position 1, if its not
   
    if ((ans[1]) == (guess[1])) {   
       
    } else {return 1;}
    position=2;

  }
  if (digitalRead(button3) == HIGH) {
    guess[position] = 'E';

   
    if ((ans[2]) == (guess[2])) {   
     
    } else {return 1;}
    position=3;

  }
 if (digitalRead(button4) == HIGH) {
    guess[position] = 'R';

    
    if ((ans[3]) == (guess[3])) {   
      
    } else {return 1;}
    position=4;

  }
 if (digitalRead(button5) == HIGH) {
    guess[position] = 'T';

    
    if ((ans[4]) == (guess[4])) {   

    } else {return 1;}
  }

  if (ans[4] == guess[4]) {
    return 2;
  }






}

//TEACHER COMMENTS so what is this method for and what potential values are expected to be sent?
void requestEvent() {
  //reply to the transmission request with this message
  Wire.write(alive);


}
