#include <Adafruit_LSM303_U.h>
#include <Adafruit_NeoPixel.h>

#define JEWEL_PIN 4           // An available PWM pin
#define TRINKET_LED 1         // Used during boot if the accelerometer fails

int pixel_count = 7;          // 1 Jewel = 7 Pixels
int saturation = 255;         // Saturation is constant in this case
int minValue = 0;             // This is the V in HSV, as in the brightness value.
int maxValue = 255;           // This is the V in HSV, as in the brightness value.
int palmUpHue = 65536/3;      // Hue
int palmFwdHue = palmUpHue;   // Hue
int hue = palmUpHue;          // Hue

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixel_count, JEWEL_PIN, NEO_GRBW + NEO_KHZ800);

double palmUp[] = {-99, 99, -99, 99, -99, -7};
double palmFwd[] = {8, 10, -99, 99, -99, 99};

void setup() {
  
  //Init Jewel:
  strip.begin();
  strip.fill(strip.ColorHSV(hue, saturation, maxValue));
  strip.show();
  
  //Init Accelermeter:
  if(!accel.begin())
  {
    // There was a problem detecting the accelerometer ... check your connections
    pinMode(TRINKET_LED, OUTPUT);
    digitalWrite(TRINKET_LED, HIGH);
    while(1);
  }

  // Everything looks good to go!
  fade_jewel_to_off(3);

}

void loop() {

  if(gestureIs(palmUp)) {

    // Wait a moment to make sure the gesture is intentional...
    delay(500);

    // If we're still in the same gesture, do the thing...
    if(gestureIs(palmUp)) {
      palmUpAction();
    }
  
  } else if(gestureIs(palmFwd)) {

    // Wait a moment to make sure the gesture is intentional...
    delay(500);

    // If we're still in the same gesture, do the thing...
    if(gestureIs(palmFwd)) {
      palmFwdAction();
    }
  }
  
}

boolean gestureIs(double gesture[]) {
  sensors_event_t event;
  accel.getEvent(&event);
  return (event.acceleration.x > gesture[0] && event.acceleration.x < gesture[1]
          && event.acceleration.y > gesture[2] && event.acceleration.y < gesture[3]
          && event.acceleration.z > gesture[4] && event.acceleration.z < gesture[5]);
}

void fade_jewel_to_off(int delayInt) {
  
  for(int value=maxValue; value>=minValue; value--) {
    strip.fill(strip.ColorHSV(hue, saturation, value));
    strip.show();
    delay(delayInt);
  }
}

void fade_jewel_to_on(int delayInt) {
  
  for(int value=minValue; value<=maxValue; value++) {
    strip.fill(strip.ColorHSV(hue, saturation, value));
    strip.show();
    delay(delayInt);
  }
}

void palmUpAction() {
  hue = palmUpHue;
  fade_jewel_to_on(1);
  while(gestureIs(palmUp)) {}
  fade_jewel_to_off(2);
}

void palmFwdAction() {
  hue = palmFwdHue;
  fade_jewel_to_on(1);
  while(gestureIs(palmFwd)) {}
  fade_jewel_to_off(2);
}
