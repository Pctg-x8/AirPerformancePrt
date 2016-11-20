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
  MIDI.begin();
  // Serial.begin(9600);
  // Serial.println("---Gesture Test---");
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
        case DIR_UP: handleUpGesture(); break;
        case DIR_DOWN: handleDownGesture(); break;
        case DIR_LEFT: handleLeftGesture(); break;
        case DIR_RIGHT: handleRightGesture(); break;
        case DIR_NEAR: handleNearGesture(); break;
        case DIR_FAR: handleFarGesture(); break;
        default: /*Serial.println("NONE");*/ ;// Nothing to do
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

/* Gesture Handlers */

void handleUpGesture()
{
  MIDI.sendNoteOn(1, 100, 1);
}
void handleDownGesture()
{
  MIDI.sendNoteOn(2, 100, 1);
}
void handleLeftGesture()
{
  MIDI.sendNoteOn(3, 100, 1);
}
void handleRightGesture()
{
  MIDI.sendNoteOn(4, 100, 1);
}
void handleNearGesture()
{
  MIDI.sendNoteOn(5, 100, 1);
}
void handleFarGesture()
{
  MIDI.sendNoteOn(6, 100, 1);
}

