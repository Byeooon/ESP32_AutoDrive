#define LED 5 // LED PIN

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH); // on
  delay(500); // ms
  digitalWrite(LED, LOW); // off
  delay(500); // ms
}