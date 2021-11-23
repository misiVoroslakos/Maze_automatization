
int IRsensor = A0;    // Signal for the right Sensor
const int LED_digitalOut = 13;      // select the pin for the intan

boolean EnableLED = true;
int CurrentIRsensorState = 0;
int PreviousIRsensorState = 0;
int countWave = 0;

//Declare pin functions on Arduino for BigEasy driver (syringe pump motor)
// # Farnaz : everything exept than Ground, should be pin in setup?
void setup() {
  pinMode(IRsensor, INPUT);
  pinMode(LED_digitalOut, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  CurrentIRsensorState = analogRead(IRsensor);
  //Serial.println(CurrentRightInfraState);
  if ((CurrentIRsensorState < 100) && (PreviousIRsensorState > 600))  // detect the animal is breaking the IR beam -> goes from Hi->Lo
  {
    countWave++;
    Serial.println(countWave);
    delay(100);
  }
   if (countWave % 2 == 0) {
    digitalWrite(LED_digitalOut, HIGH);
  } else {
    digitalWrite(LED_digitalOut, LOW);
  }

  PreviousIRsensorState = CurrentIRsensorState; //save the previous IR state
}
