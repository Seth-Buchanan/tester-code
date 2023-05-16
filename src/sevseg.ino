#include "SevSeg.h"
#include "Servo.h"

#define TOTAL_SHOTS    700
#define OUTPUT_PIN     4
#define BUTTON_PIN     0
#define ONE_SECOND     1000

#define SERVO_LAG      30    // Time that the servo takes to move (ms)
#define SERVO_DWELL    100   // Time to keep switch pressed (ms)
#define SERVO_WAIT     150   // Time to keep switch unpressed (ms)
#define SERVO_ORIGIN   0     // The position when the switch is unpressed in degrees
#define SERVO_DEST     10    // The position when the switch is pressed in degrees

const int TIMER_DURATION = ((SERVO_DWELL + SERVO_WAIT) * TOTAL_SHOTS) / ONE_SECOND;
/* const int TIMER_DURATION = 69; */
bool stopProgram, done = false;
long secondsLeft = TIMER_DURATION;
unsigned long clockPrevMillis, servoPrevMillis;
bool servoState = true;


SevSeg sevseg;

void setup(){
	/* Serial.begin(9600); */
	
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

	/* myservo.attach(OUTPUT); */
	pinMode(BUTTON_PIN, INPUT);
}

void loop(){
	unsigned long currMillis = millis();
  // if button is pressed then timer resets to duration
	if (!digitalRead(BUTTON_PIN)){  
		secondsLeft = TIMER_DURATION;
		stopProgram = false;
	}
	
 	if (currMillis - clockPrevMillis >= ONE_SECOND){ // Timer loop
		clockPrevMillis = currMillis;
		if(secondsLeft > 0){  // Active
			sevseg.setNumber(formatTime(secondsLeft));
			secondsLeft--;        // Decrement seconds left in the timer
		} else {  //Deactiveated
			sevseg.setChars("done");
			stopProgram = true;
		}
	}
	
	if(stopProgram == false){
		servo(currMillis);
	}
  sevseg.refreshDisplay();	
}


void clock(int ms){

}

void servo(int ms){
	Serial.println(TIMER_DURATION);
	if (ms - servoPrevMillis > (servoState ? SERVO_DWELL - SERVO_LAG : SERVO_WAIT - SERVO_LAG)) {
		servoState = !servoState;
		
		if (servoState){
			digitalWrite(OUTPUT_PIN, HIGH);
			/* myservo.write(SERVO_DEST); */
		} else {
			digitalWrite(OUTPUT_PIN, LOW);
			/* myservo.write(SERVO_ORIGIN); */
		}
		servoPrevMillis = ms;
	}
}
	
int formatTime(int sec){
	int h, m, s;

	h = (sec / 3600);
	m = (sec - (3600 * h)) / 60;
	s = (sec - (3600 * h) - (m * 60));
	
	if (h != 0){					  // If time is greater than 1hr display HH:MM else MM:SS
		return (h * 100) + m;
	} else {
		return (m * 100) + s;
	}
}
