

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
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  
  
  
// setting the on off switch to read/write from pin 2
  pinMode(ONOFF, INPUT);

  //initialize Wire library
  Wire.begin();

  Serial.begin(9600);
}

void loop() {
  // the on off switch for the game, left is high, right is low
 while (digitalRead(ONOFF == HIGH)){
  // while time is less than 15 mins * 60 seconds * 1000 ms
  while (time < (15 * 60 * 1000)) {

    
    
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
   
      if (alive == 0) {
        lcd.print("alive...");
        delay(200);
        lcd.clear();
   

      }
      if (alive == 1) {
        lcd.print("passed...");
        delay(200);
        lcd.clear();
    
      }

      if (alive == 2) {
        lcd.print("GAME WON!!!");
        delay(200);
        lcd.clear();
     
      }
    
    if (alive == 99) {
      // print "game over to the LCD screen, this lets the player know they have lost
      lcd.print("Game Over");
      delay(200000);
      lcd.clear();

      // this delay is to ensure player cannot wait out timer (aprox 277 hours)
      delay(9999999999);
    }





    /*
      the tinkercar simulation will need to be
      restarted if the player loses. if this were to be
      wired into a real arduino, the player would have
      to power down the arduino to restart the game
    */
  }
  lcd.print("times up");
  alive = 99;
     
   }
  lcd.clear();
  
}
