#define Trigger 7
#define Echo 8

unsigned int time_dis;
float distance;

void setup() {
  // put your setup code here, to run once:
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
  delay(330);
}
