#include <Keypad.h>

extern "C" float surfaceTensionCalc(float P0, float P1, float d);
extern "C" float PBmaxCalc(float* PBarr, int size);

// Keypad configuration
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Button pins
const int POWER_BUTTON_PIN = 10;
const int ENTER_BUTTON_PIN = 11;
const int CALCULATE_BUTTON_PIN = 12;

// Functions
float surfaceTensionCalc(float P0, float P1, float d);
float PBmaxCalc(float PBarr[], int size);
void readPotentiometers(float &P0, float PBarr[], int size);
float getDFromKeypad();

// Constants
const int POT_P0_PIN = A0;  // Pin for P0 potentiometer
const int POT_PB_PIN = A1;  // Pin for PB potentiometer
const int ARRAY_SIZE = 300; // Size of PBarr array
const int SAMPLE_INTERVAL = 10; // Sampling interval in milliseconds

// Linear scaling constants
const float VOLTAGE_MIN = 0.0;    // 0V
const float VOLTAGE_MAX = 5.0;    // 5V
const float VALUE_MIN = 0.0;      // 0
const float VALUE_MAX = 120000.0;  // 40000

// Global variables
float d = 0;

// Variables to store potentiometer readings
float P0;
float PBarr[ARRAY_SIZE];

void setup() {
  Serial.begin(9600);

  pinMode(POT_P0_PIN, INPUT);
  pinMode(POT_PB_PIN, INPUT);

  pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ENTER_BUTTON_PIN, INPUT_PULLUP);
  pinMode(CALCULATE_BUTTON_PIN, INPUT_PULLUP);
}


void readPotentiometers(float &P0, float PBarr[], int size) {
  // Read P0 value and scale it linearly from 0-5V to 0-40000
  int rawP0 = analogRead(POT_P0_PIN); // Read raw analog value (0-1023)
  float voltageP0 = rawP0 * (VOLTAGE_MAX / 1023.0); // Convert to voltage (0-5V)
  P0 = mapFloat(voltageP0, VOLTAGE_MIN, VOLTAGE_MAX, VALUE_MIN, VALUE_MAX); // Scale to 0-40000

  // Read PBarr values at 10 ms intervals and scale them linearly
  for (int i = 0; i < size; i++) {
    int rawPB = analogRead(POT_PB_PIN); // Read raw analog value (0-1023)
    float voltagePB = rawPB * (VOLTAGE_MAX / 1023.0); // Convert to voltage (0-5V)
    PBarr[i] = mapFloat(voltagePB, VOLTAGE_MIN, VOLTAGE_MAX, VALUE_MIN, VALUE_MAX); // Scale to 0-40000
    delay(SAMPLE_INTERVAL);
  }
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getDFromKeypad() {
  String inputString = "";
  Serial.println("Enter the density:");

  while (digitalRead(ENTER_BUTTON_PIN) == HIGH) {
    char key = keypad.getKey();
    if (key) {
      if (key == '*') {
        break;
      } else if (key >= '0' && key <= '9') {
        inputString += key;
        Serial.print(key);
      }
    }
  }

  Serial.println();
  return inputString.toFloat();
}

void loop() {
  while (digitalRead(POWER_BUTTON_PIN) == HIGH) {
  }

  d = getDFromKeypad();

  while (digitalRead(ENTER_BUTTON_PIN) == HIGH) {
  }
  Serial.println("Push the syringe gradually");
  Serial.println("Press the calculate button after the gas bubble breaks.");

  readPotentiometers(P0, PBarr, ARRAY_SIZE);

  while (digitalRead(CALCULATE_BUTTON_PIN) == HIGH) {
  }

  float P1 = PBmaxCalc(PBarr, ARRAY_SIZE);

  float T = surfaceTensionCalc(P0, P1, d);

  Serial.print("Surface Tension T: ");
  Serial.print(T);
  Serial.println(" N/m");

  delay(1000);
}