#define LED_RED 0
#define LED_GREEN 2
#define LED_BLUE 4
#define LED_YELLOW 6

#define NUM_LEDS 4
#define SEQUENCE_LENGTH 32 // Maximum sequence length (adjust as needed)

int leds[NUM_LEDS] = {LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW};
int buttons[NUM_LEDS] = {3, 5, 7, 9};

int sequence[SEQUENCE_LENGTH];  // Stores the sequence of colors
int currentLevel = 0;           // Current level (sequence length)
int sequenceIndex = 0;          // Index for iterating through sequence

bool isNewGame = true;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP); // Use pull-up resistors for buttons
  }
  randomSeed(analogRead(0));
}

void loop() {
  if (isNewGame) {
    generateSequence();
    currentLevel = 0;
    sequenceIndex = 0;
    displaySequence(currentLevel);
    isNewGame = false;
  }

  // Add visual feedback like a bar sweep or flashing LEDs here (optional)

  while (!isNewGame && sequenceIndex <= currentLevel) {
    Serial.println("Reading buttons...");
    Serial.println(sequence[sequenceIndex]);

    int buttonPressed = readButtons();
    Serial.println(buttonPressed);

    lightLED(buttonPressed);
    delay(250);
    turnOffLED(buttonPressed);

    if (sequence[sequenceIndex] != buttonPressed) {
      Serial.println("Game Over");
      Serial.print("Level: ");
      Serial.println(currentLevel);
      isNewGame = true;
    } else {
      sequenceIndex++;
      delay(250);
    }
  }

  if (sequenceIndex > currentLevel) {
    // Player completed the level, move to the next one
    currentLevel++;
    sequenceIndex = 0;
  }
}

void generateSequence() {
  for (int i = 0; i < SEQUENCE_LENGTH; i++) {
    sequence[i] = random(NUM_LEDS);
  }
}

void displaySequence(int length) {
  for (int i = 0; i <= length; i++) {
    delay(300);
    lightLED(sequence[i]);
    delay(300);
    turnOffLED(sequence[i]);
  }
}

int readButtons() {
  int flag = 0, btn;
  while (!flag) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (!digitalRead(buttons[i])) {  // Check for button press (active low)
        flag = 1;
        btn = i;
        break;
      }
    }
  }
  return btn;
}

void lightLED(int led) {
  digitalWrite(leds[led], HIGH);
}

void turnOffLED(int led) {
  digitalWrite(leds[led], LOW);
}
