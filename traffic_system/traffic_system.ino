int A=0,B=0,C=0,D=0;

#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define ir1a 11
#define ir1b 2
#define ir2a 3
#define ir2b 4

#define ledr1 7
#define ledg1 8
#define ledr2 9
#define ledg2 10



Servo S1;
Servo S2;


int up = 0;
int down = 110;

int base_time = 5;
int ir_const1 = 5;
int ir_const2 = 5;



LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  
  S1.attach(6);
  S2.attach(5);
  lcd.init();
  lcd.clear();
  lcd.backlight(); 
  lcd.setCursor(0,0);
  lcd.setCursor(0,1);
  lcd.print("Timer:  ");
  
  
  pinMode(ledr1,OUTPUT); // 1 red
  pinMode(ledg1,OUTPUT); // 1 green
  pinMode(ledr2,OUTPUT); // 2 red
  pinMode(ledg2,OUTPUT); // 2 green
 
  pinMode(ir1a,INPUT); // A ir sensor
  pinMode(ir1b,INPUT); // B ir sensor
  pinMode(ir2a,INPUT); // C ir sensor
  pinMode(ir2b,INPUT); // D ir sensor
}

void print_lcd(int t)
{
  for(int i = t; i>= 0 ; i--)
  {
    lcd.setCursor(7,1);
    lcd.print(i);
    delay(1000);
    } 
  }

void loop() {
  // put your main code here, to run repeatedly:

  A = !digitalRead(ir1a);
  B = !digitalRead(ir1b);

  lcd.setCursor(0,0);
  lcd.print("1A=");
  lcd.print(A);
  lcd.print(" 1B=");
  lcd.print(B);

  digitalWrite(ledr1,LOW);
  digitalWrite(ledg2,LOW);
  digitalWrite(ledr2,HIGH);
  digitalWrite(ledg1,HIGH);
  S1.write(up);
  S2.write(down);
  print_lcd(base_time + A*ir_const1 + B*ir_const2);

  C = !digitalRead(ir2a);
  D = !digitalRead(ir2b);

  lcd.setCursor(10,0);
  lcd.print("2A=");
  lcd.print(C);
  lcd.print(" 2B=");
  lcd.print(D);
 
  digitalWrite(ledr2,LOW);
  digitalWrite(ledg1,LOW);
  digitalWrite(ledr1,HIGH);
  digitalWrite(ledg2,HIGH);
  S1.write(down);
  S2.write(up);
  print_lcd(base_time + C*ir_const1 + D*ir_const2);

}
