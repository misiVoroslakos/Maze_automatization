// These variables store the flash pattern
// and the current state of the LED

int ledPin1 =  12;      // the number of the LED pin
int IntanTTLSyncLEDPin1 =  10;      // the number of the pin which sends a TTL to Intan
int ledState1 = LOW;             // ledState used to set the LED
unsigned long previousMillis1 = 0;        // will store last time LED was updated
long OnTime1 = 2000;           // milliseconds of on-time
long OffTime1 = 2000;          // milliseconds of off-time

unsigned long trialStartMillis1 = 0;        // will store last time LED was updated
long OnTimeStopWatch = 120000;
boolean enableStopWatch = LOW;

const int InfraredSensorPin = 4;//Connect the signal pin to the digital pin 4
int IRState = LOW;
int lastIRState = LOW;
int IntanTTLSyncIR =  5;      // the number of the pin which sends a TTL to Intan when IR sensor is blocked
const int LedDisp = 13;

const int stopWatchStartPin = 11;//Connect the signal pin to the digital pin 4
int stopWatchStartState = LOW;
const int stopWatchResetPin = 11;//Connect the signal pin to the digital pin 4
int stopWatchResetState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(InfraredSensorPin, INPUT);
  pinMode(LedDisp, OUTPUT);
  // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(IntanTTLSyncIR, OUTPUT);
}

void loop()
{
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  if ((ledState1 == HIGH) && (currentMillis - previousMillis1 >= OnTime1))
  {
    ledState1 = LOW;  // Turn it off
    previousMillis1 = currentMillis;  // Remember the time
    digitalWrite(ledPin1, ledState1);  // Update the actual LED
    digitalWrite(IntanTTLSyncLEDPin1, ledState1);  // Update the TTL
  }
  else if ((ledState1 == LOW) && (currentMillis - previousMillis1 >= OffTime1))
  {
    ledState1 = HIGH;  // turn it on
    previousMillis1 = currentMillis;   // Remember the time
    digitalWrite(ledPin1, ledState1);    // Update the actual LED
    digitalWrite(IntanTTLSyncLEDPin1, ledState1);  // Update the TTL
  }

  if (digitalRead(InfraredSensorPin) == HIGH)
  {
    IRState = LOW;
    digitalWrite(LedDisp, IRState);
    digitalWrite(IntanTTLSyncIR, IRState);
  }
  else
  {
    IRState = HIGH;
    digitalWrite(LedDisp, IRState);
    digitalWrite(IntanTTLSyncIR, IRState);
  }

  // compare the IRState to its previous state
  if (IRState != lastIRState) {
    // if the state has changed, start timer
    if (IRState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      trialStartMillis1 = currentMillis;  // Remember the time
      enableStopWatch = !enableStopWatch;
      stopWatchStartState = HIGH;
      digitalWrite(stopWatchStartPin,stopWatchStartState);
    }
    else
    {
      enableStopWatch = !enableStopWatch;
      stopWatchStartState = LOW;
      digitalWrite(stopWatchStartPin,stopWatchStartState);
    }
    // save the current state as the last state, for next time through the loop
    lastIRState = IRState;
  }

  if ((enableStopWatch = HIGH) && (currentMillis - trialStartMillis1 >= OnTimeStopWatch))
  {
    enableStopWatch = !enableStopWatch;
    stopWatchStartState = LOW;  // Turn it off
    digitalWrite(stopWatchStartPin,stopWatchStartState);
  }
  }
