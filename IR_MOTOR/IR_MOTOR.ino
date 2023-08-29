#include "iFMotors.h"

#define R_IR 37
#define L_IR 35
#define RM_IR 38
#define LM_IR 34

unsigned int R, L, RM, LM;

void iFMotors::init(){
    // including this does not change anything
    pinMode(LEFT_F, OUTPUT);
    pinMode(LEFT_R, OUTPUT);
    pinMode(RIGHT_F, OUTPUT);
    pinMode(RIGHT_R, OUTPUT);
    pinMode(14, INPUT_PULLDOWN);
    pinMode(25, INPUT_PULLDOWN);
    pinMode(13, INPUT_PULLDOWN);
    pinMode(15, INPUT_PULLDOWN);

    ledcSetup(LEFT_F_CH, FREQUENCY, _nPWMResBit);
    ledcSetup(LEFT_R_CH, FREQUENCY, _nPWMResBit);
    ledcSetup(RIGHT_F_CH, FREQUENCY, _nPWMResBit);                
    ledcSetup(RIGHT_R_CH, FREQUENCY, _nPWMResBit);

    ledcAttachPin(LEFT_F, LEFT_F_CH);                  
    ledcAttachPin(LEFT_R, LEFT_R_CH);
    ledcAttachPin(RIGHT_F, RIGHT_F_CH);   
    ledcAttachPin(RIGHT_R, RIGHT_R_CH);   

    ledcWrite(LEFT_F_CH, 0 );
    ledcWrite(LEFT_R_CH, 0 );  
    ledcWrite(RIGHT_F_CH, 0 );
    ledcWrite(RIGHT_R_CH, 0 );

    LT_LW_MS = TURNING_MIN_SPEED;
    LT_RW_MS = TURNING_MIN_SPEED;
    RT_LW_MS = TURNING_MIN_SPEED;
    RT_RW_MS = TURNING_MIN_SPEED;

    ui32MAX_FORWARD_SPEED = MAX_FORWARD_SPEED;
    ui32MIN_FORWARD_SPEED = MIN_FORWARD_SPEED;
    LW_FS = MIN_FORWARD_SPEED;
    RW_FS = MIN_FORWARD_SPEED;
    LW_BS = MIN_BACK_SPEED;
    RW_BS = MIN_BACK_SPEED;
}

void iFMotors::pwmWrite(int wheel, int direct, uint32_t value)
{
    if( direct == BACKWARD ){
        if( wheel == WHEEL_LEFT ){
            ledcWrite(LEFT_R_CH, 0 ); 
            ledcWrite(LEFT_F_CH, value );
        }
        else{
            ledcWrite(RIGHT_R_CH, 0 );       
            ledcWrite(RIGHT_F_CH, value );     
        }
    }
    else{
        if( wheel == WHEEL_LEFT ){
            ledcWrite(LEFT_F_CH, 0 );            
            ledcWrite(LEFT_R_CH, value ); 
        }
        else{
            ledcWrite(RIGHT_F_CH, 0 ); 
            ledcWrite(RIGHT_R_CH, value );  
        }
    }
}

void iFMotors::motorStop()
{
    pwmWrite(WHEEL_LEFT, FORWARD, 0);
    pwmWrite(WHEEL_RIGHT, FORWARD, 0);
    pwmWrite(WHEEL_LEFT, BACKWARD, 0);
    pwmWrite(WHEEL_RIGHT, BACKWARD, 0);            
}

void iFMotors::motorGo()
{
    // pwmWrite(WHEEL_LEFT, FORWARD, FORWARD_SPEED);
    // pwmWrite(WHEEL_RIGHT, FORWARD, FORWARD_SPEED);

    //// this slowly increases speed
    if (LW_FS < ui32MAX_FORWARD_SPEED) LW_FS += MOTOR_SPEED_STEP;
    else LW_FS = ui32MIN_FORWARD_SPEED;

    if (RW_FS < ui32MAX_FORWARD_SPEED) RW_FS += MOTOR_SPEED_STEP;
    else RW_FS = ui32MIN_FORWARD_SPEED;
    //// this slowly increases speed
    
    pwmWrite(WHEEL_LEFT, FORWARD, LW_FS);
    pwmWrite(WHEEL_RIGHT, FORWARD, RW_FS);
}

void iFMotors::motorBack()
{
    //// this slowly increases speed
    if (LW_BS < MAX_BACK_SPEED) LW_BS += MOTOR_SPEED_STEP;
    else LW_BS = MIN_BACK_SPEED;
    if (RW_BS < MAX_BACK_SPEED) RW_BS += MOTOR_SPEED_STEP;
    else RW_BS = MIN_BACK_SPEED;

    pwmWrite(WHEEL_LEFT, BACKWARD, LW_BS);
    pwmWrite(WHEEL_RIGHT, BACKWARD, RW_BS);
    //// this slowly increases speed
}
          
void iFMotors::motorLeftTurn()
{
    //// this slowly increases speed
    if (LT_LW_MS < TURNING_LM_MAX_SPEED) LT_LW_MS += MOTOR_SPEED_STEP;
    else LT_LW_MS = TURNING_MIN_SPEED;

    if (LT_RW_MS < TURNING_RM_MAX_SPEED) LT_RW_MS += MOTOR_SPEED_STEP;
    else LT_RW_MS = TURNING_MIN_SPEED;
    //// this slowly increases speed
    
    pwmWrite(WHEEL_LEFT, FORWARD, 0);
    pwmWrite(WHEEL_RIGHT, FORWARD, LT_RW_MS);
}

void iFMotors::motorRightTurn()
{
    //// this slowly increases speed
    if (RT_LW_MS < TURNING_LM_MAX_SPEED) RT_LW_MS += MOTOR_SPEED_STEP;
    else RT_LW_MS = TURNING_MIN_SPEED;

    if (RT_RW_MS < TURNING_RM_MAX_SPEED) RT_RW_MS += MOTOR_SPEED_STEP;
    else RT_RW_MS = TURNING_MIN_SPEED;
    //// this slowly increases speed

    pwmWrite(WHEEL_RIGHT, FORWARD, 0);
    pwmWrite(WHEEL_LEFT, FORWARD, RT_LW_MS);
}

void iFMotors::reset_ltrt_ms()
{
    LT_LW_MS = TURNING_MIN_SPEED;
    LT_RW_MS = TURNING_MIN_SPEED;
    RT_LW_MS = TURNING_MIN_SPEED;
    RT_RW_MS = TURNING_MIN_SPEED;
}

void iFMotors::reset_max_forwardSpeed()
{
    ui32MAX_FORWARD_SPEED = MAX_FORWARD_SPEED;
}

iFMotors ifMotor;

void setup() {
  // put your setup code here, to run once:
  ifMotor.init();
  Serial.begin(9600);
  pinMode(R_IR, INPUT);
  pinMode(L_IR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  R = analogRead(R_IR);
  L = analogRead(L_IR);

  // Control the Delay!
  // Control the Speed!

  if((R < 250) && (L > 1000)){ // turn left
    ifMotor.pwmWrite(WHEEL_RIGHT, BACKWARD, 550);
    ifMotor.pwmWrite(WHEEL_LEFT, FORWARD, 700);
    //delay(2);
  }
  else if((R > 1000) && (L < 250)){ // turn right
    ifMotor.pwmWrite(WHEEL_RIGHT, FORWARD, 700);
    ifMotor.pwmWrite(WHEEL_LEFT, BACKWARD, 550);
    //delay(2);
  }
  else{ // forward
    ifMotor.pwmWrite(WHEEL_RIGHT, FORWARD, 700);
    ifMotor.pwmWrite(WHEEL_LEFT, FORWARD, 700);
    //delay(2);
  }
}