#include <NeoPixelBus.h>

#define colorSaturation 16
#define Right_IR 37
#define Left_IR 35
#define RM_IR 38
#define LM_IR 34

unsigned int L_value, LM_value;

const uint16_t PixelCount = 4; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

RgbColor yellow(colorSaturation, colorSaturation, 0);
RgbColor black(0);

void setup() {
  // put your setup code here, to run once:
  strip.Begin();
  Serial.begin(9600);

  pinMode(Left_IR, INPUT);
  pinMode(LM_IR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  L_value = analogRead(Left_IR);
  LM_value = analogRead(LM_IR);

  Serial.print("LEFT : ");
  Serial.print(L_value);
  Serial.print("     LEFT MIDDLE : ");
  Serial.println(LM_value);

  if(L_value < 30 || LM_value < 30){
    strip.SetPixelColor(1, yellow); // back left
    strip.SetPixelColor(3, yellow); // front left
    strip.Show(); // on
    delay(500);
  }
  else{
    strip.SetPixelColor(1, black); // back left
    strip.SetPixelColor(3, black); // front left
    strip.Show(); // on
    delay(500);
  }
}
