// Télémètre à ultrason

#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

// La vitesse du son en cm/us
#define VITESSE 0.035
// Les broches
const int trig = 8; // l'émission de l'onde
const int echo = 9; // la reception

void setup() {
  // Déclaration de les entrées et les sorties
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // initialization de la broche de l'émission
  digitalWrite(trig, LOW);

  // initialization de l'écran
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Déclencher l'onde
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Lire la durée de l'état haute sur la broche "echo"
  unsigned long duree = pulseIn(echo, HIGH); // en microseconds
  // calculer la distance
  double distance = VITESSE * duree / 2; // en cm

  lcd.clear();
  lcd.home();
  // Afficher la durée
  lcd.print("Duree = ");
  lcd.print(duree);
  lcd.print(" us");
  
  // Aller à la ligne
  lcd.setCursor(0, 1);
  // Afficher la distance
  lcd.print("Dist = ");
  lcd.print(distance);
  lcd.print(" cm");

  // pause
  delay(1000);
}