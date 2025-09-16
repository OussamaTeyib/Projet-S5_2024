// Contrôle de pompe en fonction de la température

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Broches
#define CAPTEUR_PIN A0   // Capteur de température
#define RELAIS_PIN 2     // Relai pour la pompe

// Plages de température
#define TEMPERATURE_MIN 20
#define TEMPERATURE_MAX 30

// Constantes pour le calcul de la résistance
#define RREF 10000.0
float A = 0.0003950;
float B = 0.00000263;
float C = 0.000000001;

// État de la pompe
bool pompeEtat = true;

// Variable pour stocker la température mesurée
int temperatureMesuree;

void setup() {
  // Déclarer les broches en entrée/sortie
  pinMode(RELAIS_PIN, OUTPUT);

  // Initialiser l'écran LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Lire la résistance du capteur
  float resistance = RREF * (1023.0 / analogRead(CAPTEUR_PIN) - 1.0);

  // Calculer la température à partir de la résistance
  temperatureMesuree = 1.0 / (A + B * log(resistance) + C * pow(log(resistance), 2));
  temperatureMesuree = (temperatureMesuree - 100.15) / 100 + 10; 
  temperatureMesuree = temperatureMesuree + 10; 

  // Afficher la température sur le LCD
  lcd.clear();
  lcd.home();
  lcd.print("Temp: ");
  lcd.print(temperatureMesuree);
  lcd.print(" C");

  // Contrôle du relai et de la pompe
  if (temperatureMesuree < TEMPERATURE_MIN) {
    // Température inférieure au minimum : activer le relai et la pompe
    digitalWrite(RELAIS_PIN, HIGH);
    pompeEtat = true;
  } 
  else if (temperatureMesuree > TEMPERATURE_MAX) {
    // Température supérieure au maximum : désactiver le relai et la pompe
    digitalWrite(RELAIS_PIN, LOW);
    pompeEtat = false;
  } 
  else {
    // Température dans la plage : ne rien changer
  }

  // Afficher l'état de la pompe sur le LCD
  lcd.setCursor(0, 1);
  lcd.print("Pompe: ");
  if (pompeEtat) {
    lcd.print("Ouverte");
  } else {
    lcd.print("Fermee");
    delay(300000); // Pause de 5 minutes
  }

  // Pause avant la prochaine lecture
  delay(1000);
}
