<<<<<<< HEAD
#include <Servo.h>


=======
//shared with Mr Hansen successfully
>>>>>>> 80b398d654209021c5cd8ea39d2e1b2af958805f
const byte PAWPIN1 = 1;
const byte PAWPIN2 = 2;
const byte PAWPIN3 = 3;
const byte PAWPIN4 = 4;
const byte LEDPIN = 5;
const byte LEFTEARPIN = 6;
const byte RIGHTEARPIN = 7;

Servo leftEar;
Servo rightEar;

void setup() {

  pinMode(LEDPIN, OUTPUT);
  pinMode(PAWPIN1, INPUT);
  pinMode(PAWPIN2, INPUT);
  pinMode(PAWPIN3, INPUT);
  pinMode(PAWPIN4, INPUT);
  leftEar.attach(LEFTEARPIN);
  rightEar.attach(RIGHTEARPIN);
}

void loop() {
  if (digitalRead(PAWPIN1) == HIGH) {
    digitalWrite (LEDPIN, HIGH);
  }
  if (digitalRead(PAWPIN2) == HIGH) {
    digitalWrite (LEDPIN, LOW);

  } if (digitalRead(PAWPIN3) == HIGH) {
   

  } if (digitalRead(PAWPIN4) == HIGH) {
    playMusic();

  }
}

void playMusic() {
Serial.print("music");
}
