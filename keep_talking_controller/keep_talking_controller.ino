

// inclue adafruit libary for the IC2 LCD display
#include <LiquidCrystal_I2C.h>

//So we can use the Wire library
#include <Wire.h>

// desclaring the LCD variable and initiating the LCD
LiquidCrystal_I2C lcd(32, 16, 2);

//need an id to use for the peripheral/slave
const byte HELPER_ADDR = 1;
//need an id to use for the peripheral/slave
const byte MESSAGE_SIZE = 1;


const int ONOFF = 2;

/*
  this variable is where we will save the
  message/reply from the peripheral/slave
  its only an int because we know that is the
  datatype that will be passed,
  it will be a 0, 1, 2, or 99 for alive, passed, won and lost.
*/
int alive = 0;




// setting time variable for the 15 minute timer
unsigned long time = millis();

void setup() {
  //start the LCD, this is from the official webpage
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();



  // setting the on off switch to read/write from pin 2
  pinMode(ONOFF, INPUT);

  //initialize Wire library
  Wire.begin();
  // begin the serial monitor
  Serial.begin(9600);

}

void loop() {

  while ((digitalRead((ONOFF)) == 1)) {
    // millis tracks the time that the arudiono has been turned on
    // while time is less than 15 mins * 60 seconds * 1000 ms
    while (millis() < (15 * 60 * 1000)) {


      //request a transmission with this id and message size
      Wire.requestFrom(HELPER_ADDR, MESSAGE_SIZE);

      /*
        while more bytes of the message are available to
        do the following. This is needed as the
        peripheral/slave may send less than requested
      */
      while (Wire.available()) {
        //read the transmission and save it to the alive variable
        alive = Wire.read();
      }
      // check is alive is 0
      if (alive == 0) {
        // pritn to the LCD
        lcd.print("alive...");
        //small delay to let the player read the msg
        delay(200);
        //clear the LCD
        lcd.clear();
        while ((digitalRead((ONOFF)) == 0)) {
          lcd.clear();
        }


      }
      // check is alive is 1, then we print passed
      if (alive == 1) {
        lcd.print("passed...");
        delay(200);
        lcd.clear();
        //code fo rthe on off switch
        while ((digitalRead((ONOFF)) == 0)) {
          lcd.clear();
        }
      }
      // alive alive is 2 then we know we've won the game
      if (alive == 2) {
        lcd.print("GAME WON!!!");
        delay(200);
        lcd.clear();
        while ((digitalRead((ONOFF)) == 0)) {
          lcd.clear();
        }

      }
      //if alive is 99 then we lose
      if (alive == 99) {
        // print "game over to the LCD screen, this lets the player know they have lost
        lcd.print("Game Over");
        delay(2000);
        lcd.clear();

        // this delay is to ensure player cannot wait out timer (aprox 115 days)
        // only having a delay means we
        delay(9999999999);

      }





      /*
        the tinkercar simulation will need to be
        restarted if the player loses. if this were to be
        wired into a real arduino, the player would have
        to power down the arduino to restart the game
      */
    }
    //if the time is up (over 15 minutes)
    lcd.print("times up");
    delay(2000);
    //end the game
    lcd.print("Game Over");
    // large delay to ensure player has to restart game, not 100% nessacery but ensure player cannot cheat the system
    delay(9999999999);
    //clear the LCD to ensure the player knows the game is over
    lcd.clear();


  }
  //if the LED is off do nothing and clear the LCD
  lcd.clear();

}
