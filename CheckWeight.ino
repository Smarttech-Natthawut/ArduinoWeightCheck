/*
ตัวอย่างโคด โดย www.arduinoall.com
โคดสำหรับแสดงนำหนัก

ปรับค่าเริ่มต้นจากโคดบรรทัดนี้ float calibration_factor = -380000;
ค่านี้ได้มาจากโคดส่วน calibration.ino

VCC - 5V
GND - GND
DOUT - 3
CLK - 2

*/
#include <Wire.h>

//Example By ArduinoAll.com
//แก้ไขเพิ่มเติมจาก code เดิม เพื่อให้ส่ง output เมื่อครบจำนวนนับที่ต้องการ และ reset ค่าใหม่
// เพื่อให้มั่นใจว่า เซนเซอร์จะ นับ ทันที ทุกครั้ง 
//เราจะใช้การทำงานแบบ interrupt เพื่อให้ทำงานทันที ที่เซนเซอร์ตรวจจับได้

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   //Module IIC/I2C Interface บางรุ่นอาจจะใช้ 0x3f

#include "HX711.h"
#define calibration_factor 101000// เอาค่าที่ได้จากการปรับ มาใส่ตรงนี้
//#define DOUT  3
//#define CLK  2

const int LOADCELL_DOUT_PIN_1 = 3;
const int LOADCELL_SCK_PIN_1 = 2;

HX711 scale; //(DOUT, CLK)
void setup() {
lcd.init();
//lcd.noBacklight();   // ปิด backlight
lcd.backlight();       // เปิด backlight
lcd.print("WEIGHT CHECK ATO");
lcd.setCursor(0, 1);
lcd.print("      (Kgs.)");
lcd.setCursor(0, 1);

  
  Serial.begin(9600);
  Serial.println("FT2K Development Calibrating...");
  scale.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN_1);
  scale.set_scale(calibration_factor); // ปรับค่า calibration factor
  scale.tare(); //รีเซตน้ำหนักเป็น 0
  Serial.println("OK Start :");
  lcd.print("OK Start ");
  lcd.setCursor(0, 1);
  lcd.print("      (Kgs.)");
  lcd.setCursor(0, 1);
}
void loop() {
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3); //แสดงผลน้ำหนัก 2 ตำแหน่ง
  Serial.println(" kg");
  lcd.print(scale.get_units());
  lcd.setCursor(0, 1);
  delay(1000);
      
}
