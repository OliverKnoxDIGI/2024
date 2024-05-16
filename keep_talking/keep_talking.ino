//oliver knox 19308
//keep talking assesment

// using the wire libary so we can communicate using two or more arduinos
#include <Wire.h>

//Helper address is used as a constant to send the information to the controller
const byte HELPER_ADDR = 1;

// this variable is used to determain if the player is alive or not, and later send to the controller
int alive = 0;

// help to determain if player has already passed a minigame
// this means the player cannot cheat and win the whole game by winning the same minigame once
bool wirePassed = false;
bool buttonPassed = false;

//this is to check if the fith button has been pressed, means that the game can still be lost after it has been won
bool finalButtonPressed = false;

// set the wire pins to constants, allowing changability and readability
const int WIRE1 = 1;
const int WIRE2 = 2;
const int WIRE3 = 3;

// setting the pass and fail LEDs for prev reasons

// same as prev but for the buttons game
const int BUTTON1 = 4;
const int BUTTON2 = 5;
const int BUTTON3 = 6;
const int BUTTON4 = 7;
const int BUTTON5 = 8;

int position = 0;

char ans[] = { 'Q', 'W', 'E', 'R', 'T', '\0'};
char guess[] = { 'x', 'x', 'x', 'x', 'x', '\0'};

// these are the ints for the win loss, or untouched game states, used in the void loop
int val = 0;
int val2 = 0;


void setup() {
  // put your setup code here, to run once:
  // wire begin for helper address, request event, and serial monitor
  Wire.begin(HELPER_ADDR);
  Wire.onRequest(requestEvent);

  // setting the wire pins to input
  pinMode(WIRE1, INPUT);
  pinMode(WIRE2, INPUT);
  pinMode(WIRE3, INPUT);
  // set up the serial monitor
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
      // we print a msg to let the player know they have already won that game
    { Serial.println(" already won that!! cheater");
    }
    // if the game is lost, send 99 (lose number) to the controller
  } else if (val == 1) {
    alive = 99;
    Serial.println("game lost");
  }
  // handling the return = 0 (untouched)
  else {}



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
    // if the game has been lost
  } else if (val2 == 1) {
    //alive = 99, in controller is lost
    alive = 99;
    //let the player know they already won
    Serial.println("already won that!! cheater");

    //handling is return = 0
  } else {}



}

//cut wires game, if right most wire is cut, player wins.
// 0 is unplayed, 1 is lose, and 2 is win
int cut_wires() {
  //3 wires

  // left most wire

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(WIRE1) == LOW) {
    //fail
    return 1;
  }
  // middle wire
  if (digitalRead(WIRE2) == LOW)  {

    return 1;

  }
  // right most wire
  //winning wire
  if (digitalRead(WIRE3) == LOW)  {
    return 2;

  }
  // check if all of the wires are untouched, and return 0 if true
  if (digitalRead(WIRE3) == HIGH) {
    if (digitalRead(WIRE2) == HIGH) {
      if (digitalRead(WIRE1) == HIGH) {
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
  if (digitalRead(BUTTON1) == HIGH) {
    //position 0 of the guess array is changed from x to a Q
    guess[position] = 'Q';

    //check if the first letter in the guess array is equal to the ans array
    if ((ans[0]) == (guess[0])) {
      //if it is we do nothing
    }
    // if its not equal we return 1 to lose the game
    else {
      return 1;
    }
    // position equal one, instead of postion++, means player cant press all buttons at once
    position = 1;

  }

  // check if the second "button" is pressed, if it is
  if (digitalRead(BUTTON2) == HIGH) {
    //position 1 of the guess array is changed from x to a W
    guess[position] = 'W';
    //check if guess position 1 is equal to ans position 1, if its not
    if ((ans[1]) == (guess[1])) {
      // do nothing


    }
    // if its not equal we lose
    else {
      return 1;
    }
    //same reason as before
    position = 2;

  }

  // we continue to do the same for each butto
  if (digitalRead(BUTTON3) == HIGH) {
    guess[position] = 'E';


    if ((ans[2]) == (guess[2])) {

    } else {
      return 1;
    }
    position = 3;

  }
  if (digitalRead(BUTTON4) == HIGH) {
    guess[position] = 'R';


    if ((ans[3]) == (guess[3])) {

    } else {
      return 1;
    }
    position = 4;

  }
  if (digitalRead(BUTTON5) == HIGH) {
    guess[position] = 'T';


    if ((ans[4]) == (guess[4])) {

    } else {
      return 1;
    }
    finalButtonPressed = true;
  }
  /* we check every position of the array is correct,
    if any are wrong we immedietly lose, this means the
    player can still lose after the game is won, same
    with the wires game, this is done as a disarmed bomb can still
    go off if a wire is cut. we use the finalButtonPressed bool
    as the game would immediatxely lose otherwise

    if it is we return 2 to win the minigame
  */

  if (finalButtonPressed == true) {
    if (ans[4] == guess[4]) {
      if (ans[3] == guess[3]) {
        if (ans[2] == guess[2]) {
          if (ans[1] == guess[1]) {
            if (ans[0] == guess[0]) {
              return 2;
            } else {
              return 1;
            }
          } else {
            return 1;
          }
        } else {
          return 1;
        }
      } else {
        return 1;
      }
    } else {
      return 1;
    }

  }

}

/* this method will write the alive variable to the controller arduino,
  it will send a 0,1,2,or 99 for alive, passed one game, passed both games,
  or lost.
*/

void requestEvent() {
  //reply to the transmission request with this message
  Wire.write(alive);


}
