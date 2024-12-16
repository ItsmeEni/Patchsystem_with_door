#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
 
#define SS_PIN 53
#define RST_PIN 5
#define GREEN_LED_PIN 6  // Pin für grüne LED (Zutritt erlaubt)
#define RED_LED_PIN 7    // Pin für rote LED (Zutritt verweigert)
#define SERVO_PIN 8      // Pin für den Servomotor
 
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD-Adresse ggf. anpassen
 
// Erlaubte Mitarbeiter-IDs und Namen
String mitarbeiterIDs[] = {"A395E626", "53DF7C13"}; // Beispiel-IDs für mehrere Mitarbeiter
String mitarbeiterNamen[] = {"Enrico", "Fatih"};
int anzahlMitarbeiter = 2;
 
Servo tuerServo;  // Servo-Objekt für den Türöffner
 
void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
 
    // LCD initialisieren
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("RFID Scanner");
    delay(2000);
    lcd.clear();
 
    // LEDs initialisieren
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
 
    // Servo initialisieren
    tuerServo.attach(SERVO_PIN);
    tuerServo.write(0);  // Anfangsposition (Tür geschlossen)
}
 
void loop() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }
 
    String cardID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) cardID += "0";
        cardID += String(mfrc522.uid.uidByte[i], HEX);
    }
    cardID.toUpperCase();
 
    bool karteGefunden = false;
    String mitarbeiterName = "";
 
    for (int i = 0; i < anzahlMitarbeiter; i++) {
        if (cardID == mitarbeiterIDs[i]) {
            karteGefunden = true;
            mitarbeiterName = mitarbeiterNamen[i];
            break;
        }
    }
 
    if (karteGefunden) {
        Serial.print("Zutritt für ");
        Serial.print(mitarbeiterName);
        Serial.println(" genehmigt.");
 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Hallo, ");
        lcd.print(mitarbeiterName);
 
        digitalWrite(GREEN_LED_PIN, HIGH); // Grüne LED an
        tuerServo.write(90);               // Servo auf 90 Grad (Tür öffnen)
        delay(3000);                       // Warte 3 Sekunden (Tür bleibt offen)
        tuerServo.write(0);                // Servo zurück auf 0 Grad (Tür schließen)
        digitalWrite(GREEN_LED_PIN, LOW);  // Grüne LED aus
 
    } else {
        Serial.println("Unbekannte Karte. Zutritt verweigert.");
 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Karte ungültig");
 
        digitalWrite(RED_LED_PIN, HIGH); // Rote LED an
        delay(2000);                     // Warte 2 Sekunden
        digitalWrite(RED_LED_PIN, LOW);  // Rote LED aus
    }
 
    delay(1000);
    lcd.clear();
    mfrc522.PICC_HaltA();
}