/* Demo sketch to illustrate how we can detect the zero crossing
 * points for mains based applications, eg Triac control
 *
 * Ralph Bacon May 2020
 */

#include "Arduino_Zero_Crossing_Detector.h"

// The pin to which we connect the full wave rectified voltage
#define zeroPointPin 2

// Beeper pin
#define beepPin 11

// The counter we update in the Interrupt Service Routine (ISR)
// which must be marked as volatile
volatile unsigned int zpCounter;

// Forward declarations of all functions
void zeroPointDetect();
void beep();

// Setup    Setup     Setup
void setup()
{
	Serial.begin(115200);

	// Initialise beeper
	pinMode(beepPin, OUTPUT);
	beep();

	// Initialise zero point counter (100 counts per second)
	zpCounter = 0;

	// Interrupt on pin 2 to detect zero point threshold
	pinMode(2, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(2), zeroPointDetect, FALLING);

	// All done
	Serial.println("Setup complete");
}

// Loop just for demo
void loop()
{
	// If we have exactly 1 second's worth of counters
	// then beep and reset counter
	if (zpCounter > 99)
	{
		zpCounter = 0;
		beep();
	}
}

// This is the ISR and all it does is increment a count.
void zeroPointDetect() {
	// Each AC cycle (50Hz = 50 times a second) gives 100 zero points per second
	zpCounter++;
}

// Beep just for demo
void beep() {
	digitalWrite(beepPin, HIGH);
	delay(40);
	digitalWrite(beepPin, LOW);
}
