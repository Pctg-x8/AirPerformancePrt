#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const byte GestureIntPin = 2;
// const uint8_t ProximityDetectionThresholdLow = 27;
// const uint8_t ProximityDetectionThresholdHigh = 32;

static auto gesture = SparkFun_APDS9960();
static bool interrupted = false;

void setup()
{
  // MIDI.begin();
  Serial.begin(9600);
  Serial.println("---Gesture Test---");
  pinMode(GestureIntPin, INPUT);
  attachInterrupt(0, gestureInterrupt, FALLING);
  if(!gesture.init()) Serial.println("Something went wrong during APDS-9960 init");
  // gesture.setProximityGain(PGAIN_2X);
  // gesture.enableProximitySensor(false);
  gesture.enableGestureSensor(true);
}

void loop()
{
  if(interrupted)
  {
    detachInterrupt(0);
    if(gesture.isGestureAvailable())
    {
      switch(gesture.readGesture())
      {
        case DIR_UP: Serial.println("UP"); break;
        case DIR_DOWN: Serial.println("DOWN"); break;
        case DIR_LEFT: Serial.println("LEFT"); break;
        case DIR_RIGHT: Serial.println("RIGHT"); break;
        case DIR_NEAR: Serial.println("NEAR"); break;
        case DIR_FAR: Serial.println("FAR"); break;
        default: Serial.println("NONE");
      }
    }
    interrupted = false;
    attachInterrupt(0, gestureInterrupt, FALLING);
  }
  /*static uint8_t prox = 0;
  gesture.readProximity(prox);
  if(prox >= ProximityDetectionThresholdLow && prox <= ProximityDetectionThresholdHigh)
  {
    Serial.print("Proximity: ");
    Serial.println(prox);
  }*/
}

void gestureInterrupt() { interrupted = true; }

