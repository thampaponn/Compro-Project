#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int buzzer = 13; //กำหนดตัวแปรขา buzzer
LiquidCrystal_I2C lcd(0x27, 20, 4); //เซ็ตจอ lcd
const int trigPin = 7; //กำหนดตัาแปรขาที่ต่อกับขา Trig
const int echoPin = 6;//กำหนดตัวแปรขาที่ต่อกับขา Echo

void setup() {
  // put your setup code here, to run once:
pinMode(buzzer, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);
pinMode(A2, OUTPUT);
lcd.init();
lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, LOW);
delay(2);
digitalWrite(trigPin, HIGH);
delay(10);
digitalWrite(trigPin, LOW);

long duration = pulseIn(echoPin, HIGH);
int distance = duration*0.034/2;

//ถ้าระยะทางอยู่ช่วง 71-100 cm ให้ beep ยาวติดกัน ขึ้นข้อความระยะทางที่เหลือ เเล้วมีไฟกระพริบตามจังหวะ beep
if(distance <= 100 and distance >70){
  lcd.setCursor(0, 0);//บรรทัดเเรกของจอ
  lcd.print("  Distance: ");
  lcd.print(distance);
  lcd.setCursor(0, 1);//บรรทัดสองของจอ
  lcd.print("   Be careful!");
  delay (50);
  tone(buzzer, 1500, 400);//ให้ buzzer ส่งเสียงโดยสองค่าหลังคือความถี่กับช่วงความยาวเสียง
  delay(50);
  digitalWrite(A2, HIGH);
  delay(50);
  tone(buzzer, 1500, 400);
  delay(50);
  digitalWrite(A2, LOW);
  lcd.clear();//เคลียร์หน้าจอไม่ให้คำสั่งทับกัน
  delay (500);
}
//ถ้าระยะทางอยู่ช่วง 41-70 cm ให้ beep สั้นติดกัน ขึ้นข้อความระยะทางที่เหลือ เเล้วมีไฟกระพริบตามจังหวะ beep
else if(distance <= 70 and distance >40){
  lcd.setCursor(0, 0);
  lcd.print("  Distance: ");
  lcd.print(distance);
  lcd.setCursor(0, 1);
  lcd.print("  Be careful!!");
  tone(buzzer, 1500, 300);
  delay(10);
  digitalWrite(A2, HIGH);
  delay(10);
  tone(buzzer, 1500, 300);
  delay(10);
  digitalWrite(A2, LOW);
  lcd.clear();
  delay (350);
}
//ถ้าระยะทางอยู่ช่วง 0-40 cm ให้ beep ยาวต่อเนื่อง ขึ้นข้อความระยะทางที่เหลือ เเล้วมีไฟค้างไว้ตลอด
else if(distance <= 40 and distance >0){
  lcd.setCursor(0, 0);
  lcd.print("  Distance: ");
  lcd.print(distance);
  lcd.setCursor(0, 1);
  lcd.print("  Be careful!!!");
  tone(buzzer, 1500, 30);
  digitalWrite(A2, HIGH);
  
}
//ถ้าไม่อยู่ในช่วง 0-100 cm ให้ ขึ้นข้อความปกติ
else{
  lcd.setCursor(0,0);
  lcd.print("Nothing to worry");
  lcd.setCursor(0,1);
  lcd.print("Have a nice day");
  delay (5000);
  lcd.clear();
  delay (100);
}
}
