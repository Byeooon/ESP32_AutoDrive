#include <NeoPixelBus.h>

#define Trigger 7
#define Echo 8

#define colorSaturation 32

unsigned int time_dis;
float distance;

const uint16_t PixelCount = 4; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor white(colorSaturation);
RgbColor black(0);

void setup() {
  // put your setup code here, to run once:
  strip.Begin();
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT); // IN ESP32 POS
  pinMode(Echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Trigger, LOW);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  time_dis = pulseIn(Echo, HIGH);
  distance = 17.0 * (time_dis/100); // time to distance
  Serial.println(distance);

  strip.SetPixelColor(2, white); // front right
  strip.SetPixelColor(3, white); // front left

  if(distance < 50){
    strip.SetPixelColor(0, red); // back right
    strip.SetPixelColor(1, red); // back left
  }
  else{
    strip.SetPixelColor(0, black); // back right
    strip.SetPixelColor(1, black); // back left
  }
  strip.Show(); // Show the colors after setting them
  delay(100);
}
