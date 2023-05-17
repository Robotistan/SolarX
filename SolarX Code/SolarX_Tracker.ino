/*
  SolarX / Arduino Solar Tracker System

  SolarX detects the position of the sun via LDRs and follows the sunlight by the motors. Project works better with updated code.

  Website, Contact and Product Link:
  
  https://www.robotistan.com/
  https://www.robotistan.com/iletisim.xhtml
  https://www.robotistan.com/solarx-gunes-takip-sistemi-elektronikli

  You can check the other products:
  https://www.robotistan.com/robotistan-special-products

  by Robotistan R&D

*/

#include <Servo.h>                  //    Library for servo motors.

Servo servo_horizontal;             //    Define horizontal servo.
int servoh = 90;                    //    Horizontal servo first position. 
int servohLimitHigh = 150;          //    Servo move positon maximum limit.
int servohLimitLow = 30;            //    Servo move positon minimum limit.

Servo servo_vertical;               //    Define vertical servo.
int servov = 90;                    //    Vertical servo first position.
int servovLimitHigh = 150;          //    Servo move positon maximum limit.
int servovLimitLow = 30;            //    Servo move positon minimum limit.

#define SERVO_H_LIMIT_H     160     //    Servo horizontal high limit value.
#define SERVO_H_LIMIT_L     30      //    Servo horizontal low limit value.
#define SERVO_V_LIMIT_H     140     //    Servo vertical high limit value.
#define SERVO_V_LIMIT_L     60      //    Servo vertical low limit value.
#define LTL_PIN          A0         //    LDR top left definedinput.
#define LTR_PIN          A4         //    LDR top right defined input.
#define LBL_PIN          A1         //    LDR bottom left defined input.
#define LBR_PIN          A3         //    LDR bottom right defined input.


void setup() { 
  Serial.begin(9600);
  pinMode(LTL_PIN, INPUT);
  pinMode(LTR_PIN, INPUT);
  pinMode(LBL_PIN, INPUT);
  pinMode(LBR_PIN, INPUT);
  servo_vertical.attach(9);        
  servo_vertical.write(90);
  servo_horizontal.attach(11);
  servo_horizontal.write(90);
  Serial.println("TL\tTR\tBL\tBR\tT\tL\tB\tR\tservov\tservoh");  //    Shows the values that described on the Serial Port.
}

void loop() {
  int TL_value = analogRead(LTL_PIN);              //    Reading value of top left LDR.
  int TR_value = analogRead(LTR_PIN);              //    Reading value of top right LDR.
  int BL_value = analogRead(LBL_PIN);              //    Reading value of bottom left LDR.
  int BR_value = analogRead(LBR_PIN);              //    Reading value of bottom right LDR.
  int T_value = (TR_value + TL_value) / 2;         //    Average of top LDRs.
  int L_value = (BL_value + TL_value) / 2;         //    Average of left LDRs.
  int B_value = (BR_value + BL_value) / 2;         //    Average of bottom LDRs.
  int R_value = (TR_value + BR_value) / 2;         //    Average of right LDRs.
  
  //Serial.println("TL\tTR\tBL\tBR\tT\tL\tB\tR\tservov\tservoh");    //    Shows the values that described on the Serial Port.
  Serial.print(TL_value);                                          //    Printing Values to Serial port.
  Serial.print("\t");
  Serial.print(TR_value);
  Serial.print("\t");
  Serial.print(BL_value);
  Serial.print("\t");
  Serial.print(BR_value);
  Serial.print("\t");
  Serial.print(T_value);
  Serial.print("\t");
  Serial.print(L_value);
  Serial.print("\t");
  Serial.print(B_value);
  Serial.print("\t");
  Serial.print(R_value);
  Serial.print("\t");
  Serial.print(servov);
  Serial.print("\t");
  Serial.print(servoh);
  Serial.println("\t");

  
  if (T_value - B_value < 0) {            //    if difference of top value and bottom value are smaller than 0, decrease servo vertical angle value.
    servov--;
  }
  else if (T_value - B_value > 0){        //    else if difference of top value and bottom value are bigger than 0, increase servo vertical angle value.
      servov++;
  }
  if (L_value - R_value < 0) {            //    if difference of left value and right value are smaller than 0, decrease servo horizontal angle value.
    servoh--;
  }
  else if (L_value - R_value > 0){        //    else if difference of left value and right value are bigger than 0, increase servo horizontal angle value.
    servoh++;
  }

  if (servoh <  SERVO_H_LIMIT_L)          //    if servo horizontal angle value smaller than servo horizontal limit low value, equalize servo horizontal angle value and servo horizontal limit low value.
  {
    servoh = SERVO_H_LIMIT_L;
  }
  else if (servoh >  SERVO_H_LIMIT_H)     //    if servo horizontal angle value smaller than servo horizontal limit low value, equalize servo horizontal angle value and servo horizontal limit low value.
  {
    servoh = SERVO_H_LIMIT_H;
  }

  if (servov >  SERVO_V_LIMIT_H)          //    if servo vertical angle value bigger than servo vertical limit high value, equalize servo horizontal angle value and servo vertical limit high value.
  {
    servov = SERVO_V_LIMIT_H;
  }
  else if (servov <  SERVO_V_LIMIT_L)     //    else if servo vertical angle value smaller than servo vertical limit low value, equalize servo horizontal angle value and servo vertical limit low value.
  {
    servov = SERVO_V_LIMIT_L;
  }
  
  servo_horizontal.write(servoh);         // Available this delays if you have shutdown when you run your project.
  delay(50);
  servo_vertical.write(servov);
  delay(50);
 
}
