
const byte PAWPIN1 = 1;
const byte PAWPIN2 = 2;
const byte PAWPIN3 = 3;
const byte PAWPIN4 = 4;
const byte LEDPIN = 5;

void setup() {

  pinMode(LEDPIN, OUTPUT);
  pinMode(PAWPIN1, INPUT);
  pinMode(PAWPIN2, INPUT);
  pinMode(PAWPIN3, INPUT);
  pinMode(PAWPIN4, INPUT);
}

void loop() {
  if (digitalRead(PAWPIN1) == HIGH) {
    digitalWrite (LEDPIN, HIGH);
  }
  if (digitalRead(PAWPIN2) == HIGH) {
    digitalWrite (LEDPIN, LOW);

  } if (digitalRead(PAWPIN3) == HIGH) {
    playMusic();

  } if (digitalRead(PAWPIN4) == HIGH) {
    //playGame();

  }
}

void playMusic() {

}
