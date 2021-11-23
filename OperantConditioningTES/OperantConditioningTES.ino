// These variables store the flash pattern
// and the current state of the LED

int soundPin1 =  12;      // the number of the sound pin
int soundState = LOW;             // soundState used to set the sound pin
unsigned long SoundOffTime = 0;        // will store last time sound was updated
unsigned long SoundOnTime = 0;        // will store last time sound was updated
long SoundOnInterval = 400;           // milliseconds of on-time
long SoundOffInterval = 1350;          // milliseconds of off-time

int TESPin =  13;      // the number of the TTL pin to TES stimulator
int TESState = LOW;             // TESState used to set the TES
unsigned long TESOffTime = 0;        // will store last time TES was updated
unsigned long TESOnTime = 0;        // will store last time TES was updated
long TESStartTime = 350;           // milliseconds of on-time
long TESOnInterval = 400;           // milliseconds of on-time
long TESOffInterval = 1350;          // milliseconds of off-time
boolean EnableTES = false;
int trial =  0;      // the number of the TTL pin to TES stimulator

unsigned long delayTime;

boolean startSoundFlag = false;
boolean startTESFlag = false;
boolean startDelay = false;
boolean EnableDelay = true;

int IntanTTLPin =  11;      // the number of the TTL pin to recording device (Intan)
int IntanTTLState = LOW;      // IntanTTLState is set to low by default

void setup()
{
  // set the digital pin as output:
  pinMode(soundPin1, OUTPUT);
  pinMode(TESPin, OUTPUT);
  pinMode(IntanTTLPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
  
  if (EnableDelay = true)
  {
    if ((currentMillis - TESOffTime >= random(3000, 5000)) && (startSoundFlag == false) && (startTESFlag == false))
    {
      delayTime = currentMillis; // Remember the time when the delay elapsed
      EnableDelay = !EnableDelay;
      startSoundFlag = !startSoundFlag;
    }
  }

  if (startSoundFlag == true)
{
  if (currentMillis - delayTime >= SoundOffInterval)
    {
      if (soundState == LOW)
      {
        startSoundFlag = !startSoundFlag;
        soundState = HIGH;  // turn it on
        IntanTTLState = HIGH; // send TTL to recording device
        startTESFlag = !startTESFlag;
        SoundOffTime = currentMillis;   // Remember the time when the sound turned on
        tone(soundPin1, 4000);    // Update the actual pin
        digitalWrite(IntanTTLPin, IntanTTLState);   // Update the actual pin
      }
    }
  }

  if ((soundState == HIGH) && (currentMillis - SoundOffTime >= SoundOnInterval))
{
  soundState = LOW;  // Turn it off
  //SoundOnTime = currentMillis;  // Remember the time
  noTone(soundPin1);  // Update the actual pin
  IntanTTLState = LOW;
  digitalWrite(IntanTTLPin, IntanTTLState);   // Update the actual pin
  }

  if (startTESFlag == true)
{
  if (currentMillis - SoundOffTime >= TESStartTime)
    {
      EnableTES = true;
      if (EnableTES == true) //((TESState == LOW) && (currentMillis - TESOnTime >= TESOffInterval) &&
      {
        startTESFlag = !startTESFlag;
        TESState = HIGH;  // turn it on
        TESOffTime = currentMillis;  // Remember the time when TES turned on
        digitalWrite(TESPin, TESState);   // Update the actual LED
      }
    }
  }
  if (startTESFlag == false)
  {
   if ((TESState == HIGH) && (currentMillis - TESOffTime >= TESOnInterval))
{
  TESState = LOW;  // Turn it off
  //TESOnTime = currentMillis;  // Remember the time
  digitalWrite(TESPin, TESState);  // Update the actual LED
  trial = ++trial;
  EnableDelay = !EnableDelay;
  Serial.println(startSoundFlag); 
  }
  }
}
