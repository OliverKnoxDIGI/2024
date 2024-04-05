//So we can use the Wire library
#include <Wire.h> 

//need an id to use for the peripheral/slave
const byte HELPER_ADDR = 1;
//need an id to use for the peripheral/slave
const byte MESSAGE_SIZE = 1;
const byte LED = 13;
const int aliveLED = 1;

/*
  this variable is where we will save the 
  message/reply from the peripheral/slave
  its only an int because we know that is the
  datatype that will be passed
*/
int alive = 1;

void setup(){
  pinMode(LED, OUTPUT);
  pinmode(aliveLED, OUTPUT);
  
  //initialize Wire library 
  Wire.begin();
  
  Serial.begin(9600);
}

void loop(){
  delay(50);
  
  //request a transmission with this id and message size
  Wire.requestFrom(HELPER_ADDR, MESSAGE_SIZE); 

  /*
    while more bytes of the message are available to
    do the following. This is needed as the
    peripheral/slave may send less than requested
  */
  while (Wire.available()) { 
    //read the transmission and save it to the blinkSpeed variable
    alive = Wire.read();
    Serial.println(alive); 
  }
  
  digitalWrite(aliveLED, alive);
}
