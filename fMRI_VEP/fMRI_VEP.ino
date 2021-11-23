//controlling Relay for VEP-fMRI experiments
// Misi Voroslakos, Buzsaki Lab, 2021. July 06.
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
// constants won't change
#define RELAY_PIN 3           // the Arduino pin, which connects to the IN pin of relay
#define IntanTTL 10           // the Arduino pin, which connects to the Intan
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
// manual switch to start VEP relay
#define arduinoSwitch 12
boolean enableStimulation = false;
int buttonState = 0;         // variable for reading the pushbutton status

long LEDsOnTime = 5;        // milliseconds of on-time
long LEDsOffTime = 5000;     // milliseconds of off-time

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin as an output
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(IntanTTL, OUTPUT);
  // initialize digital pin as an input for user switch
  pinMode(arduinoSwitch, INPUT);

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // keep relay turned off and Intan pin low
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(IntanTTL, LOW);
  // read the state of the pushbutton value:
  buttonState = digitalRead(arduinoSwitch);
  if (buttonState == HIGH) {
    enableStimulation = true;
  } else {
    enableStimulation = false;
  }
  // if push button is activate once, start 200 trials
  if (enableStimulation == true)
  {
    for (int i = 0; i < 200; i++) {
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(IntanTTL, HIGH);
      delay(LEDsOnTime);
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(IntanTTL, LOW);
      delay(LEDsOffTime);
      //Serial.println(i);
    }
  }
}
