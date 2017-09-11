#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int ThermistorPin = 1;
int Vo;
float R1 = 1000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int ThermistorPin0 = 2;
int Vo0;
float R10 = 1000;
float logR20, R20, T0;

int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R11 = 100000.0; // resistance of R1 (100K) -see text!
float R21 = 10000.0; // resistance of R2 (10K) - see text!
int value = 0;
byte degree[8] = 
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

LiquidCrystal_I2C lcd(0x3f,16,2);

void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.createChar(1, degree);
  lcd.home();
  Serial.begin(9600);
  lcd.print(" Hello Hydra...");
  lcd.setCursor(0, 1);
  lcd.print("   Let's win!");
  //lcd.printByte(3);
  //lcd.print(" win!");
  delay(5000);
  lcd.clear();  
}

void loop() {
  
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15; 

  Vo0 = analogRead(ThermistorPin0);
  R20 = R10 * (1023.0 / (float)Vo0 - 1.0);
  logR20 = log(R20);
  T0 = (1.0 / (c1 + c2*logR20 + c3*logR20*logR20*logR20));
  T0 = T0 - 273.15; 

  Serial.print("Temperature0: "); 
  Serial.print(T);

  lcd.print("M:");
  lcd.print(T);   
  //lcd.write(1);
  lcd.print("C");

  lcd.print(" B:");
  lcd.print(T0);   
  //lcd.write(1);
  lcd.print("C");

   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; // see text
   vin = vout / (R21/(R11+R21)); 
   if (vin<0.09) {
   vin=0.0;//statement to quash undesired reading !
   }
  lcd.setCursor(1, 1);
  lcd.print("Vbat.=");
  lcd.print(vin);
  delay(500);          
  lcd.clear();
  
}

