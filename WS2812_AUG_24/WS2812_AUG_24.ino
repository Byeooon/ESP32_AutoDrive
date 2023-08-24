#include <NeoPixelBus.h>

#define colorSaturation 32

const uint16_t PixelCount = 4; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

RgbColor orange(255, colorSaturation/2, 0);
RgbColor yellow(colorSaturation, colorSaturation, 0);
RgbColor mint(0, colorSaturation, colorSaturation-2);
RgbColor purple(colorSaturation, 0, colorSaturation);

void setup() {
  // put your setup code here, to run once:
  strip.Begin();
  // strip.Show();
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.SetPixelColor(0, red); // (gpio, color) // back right
  strip.SetPixelColor(1, orange); // back left
  strip.SetPixelColor(2, yellow); // front right
  strip.SetPixelColor(3, purple); // front left
  strip.Show(); // on
  delay(500);

  strip.SetPixelColor(0, green);
  strip.SetPixelColor(1, mint);
  strip.SetPixelColor(2, orange);
  strip.SetPixelColor(3, red);
  strip.Show(); // on
  delay(500);
}
