#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define capteurPin A0
#define relaisPin 2
#define temperatureMin 20
#define temperatureMax 30

#define Rref 10000.0
float A = 0.0003950;
float B = 0.00000263;
float C = 0.000000001;

bool pompeEtat =true;
int temperatureMesuree;

void setup() {
  pinMode(relaisPin, OUTPUT);
 
  lcd.init();
  lcd.backlight();
}

void loop() {
  float resistance = Rref * (1023.0 / analogRead(capteurPin) - 1.0);
  temperatureMesuree = 1.0 / (A + B * log(resistance) + C * pow(log(resistance), 2));
  temperatureMesuree = (temperatureMesuree - 100.15) / 100 + 10; 
  temperatureMesuree = temperatureMesuree + 10; 

  lcd.home();
  lcd.print("Temp: ");
  lcd.print(temperatureMesuree);
   lcd.print("  c");
  if (temperatureMesuree < temperatureMin) {
    // Température inférieure au minimum, activation du relai et de la pompe
    digitalWrite(relaisPin, HIGH);
    pompeEtat = true;
  } 
  else if (temperatureMesuree > temperatureMax) {
    // Température supérieure au maximum, désactivation du relai et de la pompe
    digitalWrite(relaisPin, LOW);
    pompeEtat = false;
  } 
  else {
    // c'est temps de échange la temperature
  }

  lcd.setCursor(0, 1);
  lcd.print("Pompe: ");
  if (pompeEtat) {
    lcd.print("Ouverte");
  } else {
    lcd.print("Fermée");
    delay(300000); // 5 min
  }

  delay(1000);
}