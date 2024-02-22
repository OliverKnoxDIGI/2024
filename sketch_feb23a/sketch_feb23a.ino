//oli knox 19308

#include <Adafruit_LiquidCrystal.h> // Include the Adafruit LiquidCrystal library

long randNumber; // Declare a variable to store random numbers

const byte BTNPIN = 1; // Define the pin number for the button
const byte POTPIN = A2; // Define the pin number for the potentiometer
const byte NOISEPIN = 0; // Define the pin number for noise

Adafruit_LiquidCrystal screen(0); // Create an instance of the Adafruit LiquidCrystal object

void setup() {
  pinMode(BTNPIN, INPUT); // Set the button pin as input
  pinMode(POTPIN, INPUT); // Set the potentiometer pin as input

  Serial.begin(9600); // Initialize serial communication

  randomSeed(analogRead(0)); // Seed the random number generator with an analog reading

  if(!screen.begin(16, 2)) { // Initialize the LCD screen with 16 columns and 2 rows
    Serial.println("couldn't start the screen? check wiring"); // Print error message if screen initialization fails
    while(1); // Enter an infinite loop
  }
}

void loop() {
  if (digitalRead(BTNPIN) == HIGH) { // Check if the button is pressed
    Serial.print("rolling dice"); // Print message indicating dice rolling
    int diceType = analogRead(POTPIN); // Read the value from the potentiometer
    diceType = map(diceType, 0, 1023, 1, 6); // Map the potentiometer value to a dice type
    rollDice(diceType); // Call the function to roll the dice
  }
}

void rollDice(byte numSides) { // Function to roll the dice with a given number of sides
  byte diceRoll = 255; // Initialize dice roll variable

  switch (numSides) { // Check the number of sides of the dice
    case 1:
      Serial.print("a 4 sided dice rolls: "); // Print message for a 4-sided dice
      diceRoll = random(1, 4); // Generate a random number between 1 and 3
      break;
    case 2:
      Serial.print("a 6 sided dice rolls: "); // Print message for a 6-sided dice
      diceRoll = random(1, 6); // Generate a random number between 1 and 5
      break;
    case 3:
      Serial.print("a 8 sided dice rolls: "); // Print message for an 8-sided dice
      diceRoll = random(1, 8); // Generate a random number between 1 and 7
      break;
    case 4:
      Serial.print("a 10 sided dice rolls: "); // Print message for a 10-sided dice
      diceRoll = random(1, 10); // Generate a random number between 1 and 9
      break;
    case 5:
      Serial.print("a 12 sided dice rolls: "); // Print message for a 12-sided dice
      diceRoll = random(1, 12); // Generate a random number between 1 and 11
      break;
    case 6:
      Serial.print("a 20 sided dice rolls: "); // Print message for a 20-sided dice
      diceRoll = random(1, 20); // Generate a random number between 1 and 19
      break;
    default:
      Serial.print("issue with mapping potentiometer values"); // Print error message for invalid dice type
      break;
  }
  Serial.println(diceRoll); // Print the result of the dice roll
}
