#define Right_IR 37
#define Left_IR 35
#define RM_IR 38
#define LM_IR 34

unsigned int R_value, L_value, RM_value, LM_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Right_IR, INPUT);
  pinMode(Left_IR, INPUT);
  pinMode(RM_IR, INPUT);
  pinMode(LM_IR, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  R_value = analogRead(Right_IR);
  L_value = analogRead(Left_IR);
  RM_value = analogRead(RM_IR);
  LM_value = analogRead(LM_IR);

  Serial.print("LEFT : ");
  Serial.print(L_value);
  Serial.print("LEFT MIDDLE : ");
  Serial.print(LM_value);

  Serial.print("     RIGHT : ");
  Serial.println(R_value);
  Serial.print("     RIGHT MIDDLE : ");
  Serial.println(RM_value);

  delay(330);
}
