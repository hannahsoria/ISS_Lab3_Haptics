#include "arduino_secrets.h"

// Hannah Soria
// ISS Lab 3: Haptics

// Operation the game! using haptics vibration motor and capacative touch sensing

// Motor connections
const int enA = 13;
const int in1 = 12;
const int in2 = 14;
#define LED_PIN 25

const int TOUCH_PIN = 32;

// array for part 2 of the lab
int vibes[6] = {0, 50, 100, 150, 200, 255};

int untouched;
int threshold;

void setup() {
    // Set all the pins as outputs
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);

    pinMode(LED_PIN, OUTPUT);

    // Turn off the motor to start with
    digitalWrite(enA, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    // calibrate capacitive touch
    untouched = calibrate(TOUCH_PIN);

    // set the threshold
    threshold = untouched - 100;
    Serial.begin(115200);
}

void loop() {
    // get the value from the touch sensor
    int sensed = touchRead(TOUCH_PIN);

    // if ther sensor value is below threshold vibrate and red light on
    if (sensed < threshold) {
        forward();
        digitalWrite(LED_PIN, HIGH);
    // if not nothing happens
    } else {
        stop();
        digitalWrite(LED_PIN, LOW);
    }
}

// vibrate
void forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(enA, HIGH);
}

// stop vibrating
void stop() {
    digitalWrite(enA, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
}

// function from part 2 of lab
void diffVibes() {
    for (int i = 0; i < 6; i++){
        Serial.println("here");
        Serial.println(vibes[i]);
        analogWrite(enA, vibes[i]);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        delay(1000);
    }
}

// function to calibrate the touch sensing
int calibrate(const int pin) {
  int total = 0;

  for(int i = 0; i < 30; i++){
    total += touchRead(pin);
  }
  int result = total / 30;
  return result;
}

// check if it is touched
void check(){
    int sensed = touchRead(TOUCH_PIN);
}