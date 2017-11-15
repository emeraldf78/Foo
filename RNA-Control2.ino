#include <AccelStepper.h>
#define STEPPER1_DIR_PIN  14
#define STEPPER1_STEP_PIN 15
#define STEPPER2_DIR_PIN  16
#define STEPPER2_STEP_PIN 17
#define STEPPER3_DIR_PIN  18
#define STEPPER3_STEP_PIN 19
#define STEPPER4_STEP_PIN 20
#define STEPPER5_STEP_PIN 21
#define STEPPER6_STEP_PIN 22

#define STEPPER3_RESET_SLEEP_PIN 7






AccelStepper stepper_A (AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper_B (AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);
AccelStepper stepper_P1(AccelStepper::DRIVER, STEPPER3_STEP_PIN, STEPPER3_DIR_PIN);
AccelStepper stepper_P2(AccelStepper::DRIVER, STEPPER4_STEP_PIN, STEPPER3_DIR_PIN);
AccelStepper stepper_P3(AccelStepper::DRIVER, STEPPER5_STEP_PIN, STEPPER3_DIR_PIN);
AccelStepper stepper_P4(AccelStepper::DRIVER, STEPPER6_STEP_PIN, STEPPER3_DIR_PIN);
AccelStepper pump[] = { stepper_P1, stepper_P2, stepper_P3, stepper_P4 };

const int PP_MICRO_LETER  = 1000;
const int PP_MILI_METER   = 100;
int curPump = 0;
 
void setup()
{  
    pinMode(LED_BUILTIN,    OUTPUT);
    Serial.begin(115200);
    Serial.print("Starting...\n");
 
    stepper_A.setMaxSpeed    (5000.0);
    stepper_A.setAcceleration(2000.0);
    stepper_B.setMaxSpeed    (10000.0);
    stepper_B.setAcceleration(10000.0);
    for(int i=0; i<4; i++) {
      pump[i].setAcceleration(2000.0);
      pump[i].setMaxSpeed    (2000.0);
    }
}

inline void blinkLED(void)  { digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); }

void loop()
{
  blinkLED();
  stepper_A.runToNewPosition(0);     delay(500);
  stepper_A.runToNewPosition(1500);  delay(500);
  //stepper_A.runToNewPosition(2800);  delay(500);
  despense(0, 20);   delay(250);
  
  /*
  
  despense(1, 100);   delay(500);
  despense(2, 100);   delay(500);
  despense(3, 100);   delay(500);
  */
}

void needlePlunge(float mm) { stepper_B.runToNewPosition(mm * PP_MILI_METER); }
void needleRetract()        { stepper_B.runToNewPosition(0); }
void needleDown()           { needlePlunge(24); }

void despense(float uLeter) {
  pump[curPump].setCurrentPosition(0);   // TODO: Use curPump
  pump[curPump].runToNewPosition(uLeter * PP_MICRO_LETER);
}

void despense(int pumpNum, float uLeter) {
  selectPump(pumpNum);
  needleDown();
  despense(uLeter);
}

void selectPump(int i) {
  needleRetract();
  stepper_A.runToNewPosition(100 + i * 400);
  curPump = i;
}

void runPcr_001() {
  despense(0, 44);    delay(5000);
  despense(1, 60);    delay(5000);
  despense(2, 10);    delay(5000);
  despense(3, 100);   delay(5000);
}

void runPcr_002() {
  despense(0, 88);    delay(5000);
  despense(1, 90);    delay(5000);
  despense(2, 20);    delay(5000);
  despense(3, 200);   delay(5000);
}


