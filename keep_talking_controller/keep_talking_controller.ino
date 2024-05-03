

// inclue adafruit libary for the IC2 LCD display
#include <LiquidCrystal_I2C.h>

//So we can use the Wire library
#include <Wire.h>
int t = 3000;
// desclaring the LCD variable and initiating the LCD
LiquidCrystal_I2C lcd(32, 16, 2);

//need an id to use for the peripheral/slave
const byte HELPER_ADDR = 1;
//need an id to use for the peripheral/slave
const byte MESSAGE_SIZE = 1;

const int aliveLED = 2;

/*
  this variable is where we will save the
  message/reply from the peripheral/slave
  its only an boolean because we know that is the
  datatype that will be passed,
  it will be a true or false/alive or dead
*/
boolean alive = true;


void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();


  pinMode(aliveLED, OUTPUT);

  //initialize Wire library
  Wire.begin();

  Serial.begin(9600);
}

void loop() {
  delay(50);

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

  digitalWrite(aliveLED, alive);


  if (alive == 1) {
    lcd.print("alive...");
    delay(2000);
    lcd.clear();

  }
  if (alive == 0) {
    // print "game over to the LCD screen, this lets the player know they have lost
    lcd.print("Game Over");
    delay(2000);
    lcd.clear();

    // this delay is to ensure
    delay(999999999);
  }





  /*
    the tinkercar simulation will need to be
    restarted if the player loses. if this were to be
    wired into a real arduino, the player would have
    to power down the arduino to restart the game
  */
}
