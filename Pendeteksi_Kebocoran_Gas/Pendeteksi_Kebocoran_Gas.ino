 ------------------------------------------
  Rangkaian Pin:
 * LCD -----------------------------
 * VSS ke -
 * VDD/VCC LCD ke +
 * V0 ke Wiper Potensio
 * Pin RS LCD ke pin digital 12
 * Pin RW LCD ke -
 * Pin E (Enable)ke pin digital 11
 * Pin D4 LCD ke pin digital 7
 * Pin D5 LCD ke pin digital 6
 * Pin D6 LCD ke pin digital 5
 * Pin D7 LCD ke pin digital 4
 * Pin A ke Resistor 10k ohm
 * Resistor ke +
 * Pin K ke -
 * Potensio ------------------------
 * Terminal 1 ke +
 * Wiper ke V0 LCD
 * Terminal 2 ke -
 * Sensor Gas ----------------------
 * B1 ke pin analog 0 (A0)
 * H2 ke -
 * B2 ke Terminal 2 Resistor 10k
 * Terminal 1 Resistor 10k ke -
 * A1 ke +
 * H1 ke +
 * A2 ke +
 * Buzzer --------------------------
 * Positif Buzzer ke pin digital 9
 * Negatif Buzzer ke ground
 * LED -----------------------------
 * led merah ke pin digital 3
 * led hijau ke pin digital 2
 ------------------------------------------
 */

//library untuk lcd
#include <LiquidCrystal.h>
//pin lcd yang terhubung
//urutan pin (RS,E,D4,D5,D6,D7)
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

//variabel led
int merah = 3;
int hijau = 2;
//variabel buzzer
int buzzer = 9;
//variabel sensor gas
int sensor = A0;
//nilai batas
int batas = 600;

//setup
void setup()
{
//aktifin output pin
//LED merah
pinMode(merah, OUTPUT);
//LED hijau
pinMode(hijau,OUTPUT);
//Buzzer
pinMode(buzzer,OUTPUT);
//Sensor Gas
pinMode(sensor,INPUT);
//serial monitor di baud 9600
Serial.begin(9600);
//lcd nyala , 16x2
lcd.begin(16,2);
}

//perulangan
void loop()
{
  //baca nilai dari sensor gas (metode analog)
  int analogValue = analogRead(sensor);
  //tampilkan nilai sensor di serial monitor
  Serial.print(analogValue);
  //jika nilai lebih dari nilai batas , maka
  if(analogValue>batas)
  {
    //led merah nyala
    digitalWrite(merah,HIGH); 
    //led hijau mati
    digitalWrite(hijau,LOW);
    //bunyi buzzer
    tone(buzzer,220,130);
    //waktu delay
    delay(2);
    //bersihkan layar
    lcd.clear();
    //display bagian atas
    lcd.setCursor(0,0);
    //Tampilkan Teks
    lcd.print("BAHAYA GAS BOCOR");
    //display bagian bawah
    lcd.setCursor(0,1);
    //tampilkan teks nilai kadar gas
    lcd.print("Kadar : ");
    //tampilkan nilai dari sensor (analog)
    lcd.print(analogValue);
    //waktu refresh / delay 0.5 detik
    delay(500);
    //bersihkan layar
    lcd.clear();
  }
  else
  { 
    //led hijau nyala
    digitalWrite(hijau,HIGH);
    //led merah mati
    digitalWrite(merah,LOW);
    //buzzer tidak bunyi
    noTone(buzzer);
    //display bagian atas
  lcd.setCursor(0,0);
    //Tampilkan Teks
    lcd.print("Kadar Gas : ");
    lcd.print(analogValue);
    //bagian display bawah
    lcd.setCursor(0,1);
    //tampilkan teks gas aman
    lcd.print("Gas Aman");
    //delay 0.5 detik
    delay(500);
  }  
}
