#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// define pins number
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 7;
const int relayPin = 8;
const int stopButton = 6;

//define variable
long duration;
int distance;
int waterDistance;
int lowLevel = 100;
int middiumLevel2 = 60;
int fullLevel = 30;
int state1;
int value;
int addr = 1;


void setup() {
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode (buzzerPin, OUTPUT);
  pinMode (relayPin, OUTPUT);
  pinMode (stopButton, INPUT);

  digitalWrite(buzzerPin, HIGH);
  delay(2000);
  digitalWrite(buzzerPin, LOW);
  Serial.begin(9600);

  value = EEPROM.read(addr);
  state1 = value;

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" INITIALIZING... ");
  lcd.setCursor(0, 1);
  lcd.print(" GB Tech. World ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" BOREHOLE PUMP ");
  lcd.setCursor(0, 1);
  lcd.print("   CONTROLLER   ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  waterDistance = distance;

  /*while (stopButton == HIGH) {
    digitalWrite(relayPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    delay(700);
    digitalWrite(buzzerPin, LOW);
    delay(200);

    }*/

  /* while (waterDistance >= lowLevel) {*/



  if (waterDistance >= fullLevel && waterDistance >= lowLevel ) {
    if (waterDistance >= lowLevel) {
      digitalWrite(relayPin, HIGH);
      state1 = 1;
      EEPROM.write(addr, state1);

      lcd.setCursor(0, 0);
      lcd.print(" Low WaterLevel ");
      lcd.setCursor(0, 1);
      lcd.print("Pumping Mach. ON");
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(500);
    }
    else {
      digitalWrite(buzzerPin, LOW);

    }

  }

  if (waterDistance <= fullLevel) {
    digitalWrite(relayPin, LOW);
    state1 = 0;
    EEPROM.write(addr, state1);
    lcd.setCursor(0, 0);
    lcd.print("WaterLevel Full.");
    lcd.setCursor(0, 1);
    lcd.print("  Pumping Stop  ");
    delay(1000);

  }
  /* if (waterDistance == fullLevel) {
     digitalWrite(buzzerPin, HIGH);
     delay(1000);
     digitalWrite(buzzerPin, LOW);
     delay(500);
    }*/

  if (state1 == 1) {
    digitalWrite(relayPin, HIGH);
    if (waterDistance <= middiumLevel2) {
      lcd.setCursor(0, 0);
      lcd.print(" Mid - Highlevel");
      lcd.setCursor(0, 1);
      lcd.print("Pumping Mach. ON");
      delay(1000);


    }
    else if (waterDistance > middiumLevel2) {
      lcd.setCursor(0, 0);
      lcd.print(" Mid - Lowlevel ");
      lcd.setCursor(0, 1);
      lcd.print("Pumping Mach. ON");
      delay(1000);


    }
  }

  if (state1 == 0) {
    digitalWrite(relayPin, LOW);
    if (waterDistance < middiumLevel2) {
      lcd.setCursor(0, 0);
      lcd.print(" Mid - Highlevel");
      lcd.setCursor(0, 1);
      lcd.print("  Pump Standby");
      delay(1000);

    }
    else if (waterDistance >= middiumLevel2) {
      lcd.setCursor(0, 0);
      lcd.print(" Mid - Lowlevel ");
      lcd.setCursor(0, 1);
      lcd.print("  Pump Standby");
      delay(1000);
    }

  }


}
