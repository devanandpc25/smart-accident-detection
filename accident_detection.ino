#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
SoftwareSerial ss(2, 3);
TinyGPSPlus gps;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define sw A0
#define limit A1
#define buz 11
String LatLng = "";
int keep = 0, i = 0, lock = 0;
//==================================== ALERT SMS FUNCTION ============================//
void Alert_sms1(String Phone_Number) {
  Serial.println("\n\rALERT SMS SENDING.....");
  Serial.println();
  Serial.println("AT");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.write('"');
  Serial.print(Phone_Number);
  Serial.write('"');
  Serial.println();
  delay(500);
  Serial.print("Accident Occurred!!! \r\n");
  Serial.print("TN 99 EC 3815 \r\n");
  Serial.println();
  Serial.print("http://maps.google.com/maps?q=loc:\n");
  Serial.print(LatLng);
  Serial.print("ASSISTANCE REQUIRED \r\n");
  delay(500);
  Serial.println();
  Serial.write(26);
  delay(2000);
  Serial.println("\n\rALERT SMS SUCCESSFULLY DELIVERED !!!");
}
void Alert_sms2(String Phone_Number) {
  Serial.println("\n\rALERT SMS SENDING.....");
  Serial.println();
  Serial.println("AT");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.write('"');
  Serial.print(Phone_Number);
  Serial.write('"');
  Serial.println();
  delay(500);
  Serial.print("Accident Occurred!!! \r\n");
  Serial.print("TN99 EC3815 \r\n");
  Serial.println();
  Serial.print("http://maps.google.com/maps?q=loc:");
  Serial.print(LatLng);
  Serial.print("ASSISTANCE REQUIRED \r\n");
  delay(500);
  Serial.println();
  Serial.write(26);
  delay(2000);
  Serial.println("\n\rALERT SMS SUCCESSFULLY DELIVERED !!!");
}
//=================================POWER UP ONE TIME RUN MAIN FUNCTION ============================//
void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(limit, INPUT_PULLUP);
  pinMode(sw, INPUT_PULLUP);
  pinMode(buz, OUTPUT);
  digitalWrite(buz, LOW);
  lcd.setCursor(0, 0);
  lcd.print("GPS DATA...     ");
  Serial.println("OK");
  delay(500);
}

//================================= MAIN LOOP FUNCTION ============================//
void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      LatLng = String(gps.location.lat(), 6);
      LatLng += ",";
      LatLng += String(gps.location.lng(), 6);
      Serial.println("Location: " + LatLng);
      delay(500);
      lcd.setCursor(0, 0);
      lcd.print("Lat:            ");
      lcd.setCursor(0, 1);
      lcd.print("Lng:            ");
      lcd.setCursor(4, 0);
      lcd.print(gps.location.lat(), 6);
      lcd.setCursor(4, 1);
      lcd.print(gps.location.lng(), 6);
      delay(1000);
    }
  }

  if (digitalRead(limit) == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Time Left:      ");
    for (i = 0; i < 16; i++) {
      delay(1000);
      lcd.setCursor(10, 0);
      lcd.print(i);
      if (digitalRead(sw) == 0) {
        i = 20;
        lcd.setCursor(0, 0);
        lcd.print("SMS Stop...     ");
        delay(1500);
      }
    }
    if ((i > 13) && (i < 17)) {
      lcd.setCursor(0, 0);
      lcd.print("sms sending...  ");
      digitalWrite(buz, HIGH);
      delay(500);
      Alert_sms1("XXXXXXXXXX");
      delay(2000);
      Alert_sms2("xxxxxxxxxx");
      delay(500);
      lcd.setCursor(0, 0);
      lcd.print("Process done1...");
      delay(1000);
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("GPS DATA...     ");
}
