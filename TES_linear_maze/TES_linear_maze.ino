//  #Farnaz: The difference between int and const int is that int is read/write while const int is read-only.
// #Farnaz: If you want the compiler to catch invalid attempts to write to a variable, make it const.

int rightIRsensor = A0;    // Signal for the right Sensor
int leftIRsensor = A1;    // Signal for the left Sensor
int TES_IRsensor = A2;    // Signal for the left Sensor
const int TES_trigger = 52;      // select the pin for the intan
int TES_LED_indicator = 13;    // Signal for the left Sensor

boolean EnableWaterRight = true;
boolean EnableWaterLeft = false;
boolean EnableStimulation = false;
boolean DeliverStimulation = true;
int CurrentRightInfraState = 0;
int CurrentLeftInfraState = 0;
int CurrentTESInfraState = 0;
int PreviousRightInfraState = 0;
int PreviousLeftInfraState = 0;
int PreviousTESInfraState = 0;
int trialNum = 0;

//Declare pin functions on Arduino for BigEasy driver (syringe pump motor)
void setup() {
  pinMode(rightIRsensor, INPUT);
  pinMode(leftIRsensor, INPUT);
  pinMode(TES_IRsensor, INPUT);
  pinMode(TES_trigger, OUTPUT);
  pinMode(TES_LED_indicator, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  CurrentRightInfraState = analogRead(rightIRsensor);
  CurrentLeftInfraState = analogRead(leftIRsensor);
  CurrentTESInfraState = analogRead(TES_IRsensor);

  if ((CurrentRightInfraState < 100) && (PreviousRightInfraState > 600))  // detect the animal is breaking the IR beam -> goes from Hi->Lo
  {
    if (EnableWaterRight == true)
    {
      trialNum++;
      Serial.print("Trial: ");
      //Serial.println(trialNum);
      EnableWaterRight = !EnableWaterRight;
      EnableWaterLeft = !EnableWaterLeft;
    }
  }
  if ((trialNum > 19) && (trialNum < 34)) 
  {
    EnableStimulation = true;
  } else {
    EnableStimulation = false;
  }
  
   if ((CurrentTESInfraState < 100) && (PreviousTESInfraState > 600))  // detect the animal is breaking the IR beam -> goes from Hi->Lo
  {
    if ((EnableStimulation == true) && (EnableWaterLeft == true) && (DeliverStimulation == true))
    {
      DeliverStimulation = !DeliverStimulation;
      // turn TES on
      digitalWrite(TES_trigger, HIGH);
      digitalWrite(TES_LED_indicator, HIGH);
      delay(50);
      digitalWrite(TES_trigger, LOW);
      digitalWrite(TES_LED_indicator, LOW);
    }
  }

  if ((CurrentLeftInfraState < 100) && (PreviousLeftInfraState > 600)) // detect the animal is breaking the IR beam -> goes from Hi->Lo
  {
    if (EnableWaterLeft == true)
    {
      //Serial.println("Animal is detected on the left");
      EnableWaterRight = !EnableWaterRight;
      EnableWaterLeft = !EnableWaterLeft;
      DeliverStimulation = !DeliverStimulation;
    }
  }

  PreviousRightInfraState = CurrentRightInfraState; //save the previous IR state
  PreviousLeftInfraState = CurrentLeftInfraState; //save the previous IR state
  PreviousTESInfraState = CurrentTESInfraState; //save the previous IR state
}
