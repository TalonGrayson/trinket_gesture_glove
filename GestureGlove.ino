#include <Adafruit_LSM303_U.h>
#include <Adafruit_NeoPixel.h>

#define JEWEL_PIN 4

int pixel_count = 7;
int saturation = 255;
int minValue = 0;
int maxValue = 255;
int palmUpHue = 65536/3;
int palmFwdHue = palmUpHue;
int hue = palmUpHue;

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
  accel.begin();

  fade_jewel_to_off(1);

}

void loop() {

  if(gestureIs(palmUp)) {

    // Wait a moment to make sure the gesture is intentional...
    delay(500);

    // If we're still in the same gesture, do the thing...
    if(gestureIs(palmUp)) {
      hue = palmUpHue;
      
      fade_jewel_to_on(1);
      
      while(gestureIs(palmUp)) {}
    
      fade_jewel_to_off(2);
    }
  
  } else if(gestureIs(palmFwd)) {

    // Wait a moment to make sure the gesture is intentional...
    delay(500);

    // If we're still in the same gesture, do the thing...
    if(gestureIs(palmFwd)) {
      hue = palmFwdHue;
      
      fade_jewel_to_on(1);
      
      while(gestureIs(palmFwd)) {}
    
      fade_jewel_to_off(2);
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
