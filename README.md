Modulares Zugangskontrollsystem mit RFID, LEDs und LCD-Anzeige
Projektbeschreibung
Dieses Projekt ist ein RFID-gesteuertes Zugangskontrollsystem, das einen sicheren und benutzerfreundlichen Zugang zu einem Bereich ermöglicht. Es kombiniert einen Arduino Mega 2560, ein RFID-Modul, LEDs, ein LCD-Display und einen Servo-Motor, um autorisierte Personen zu erkennen und den Zugang zu gewähren oder zu verweigern.
Das System bietet folgende Funktionen:
Erkennung von RFID-Karten.
Visuelle und textuelle Rückmeldung über LEDs und LCD.
Automatisches Öffnen und Schließen einer Tür mithilfe eines Servos.
Erweiterbarkeit durch Hinzufügen neuer RFID-Karten.
Verwendete Komponenten
Hardware
Arduino Mega 2560
RFID-Modul MFRC522
I2C LCD-Display (16x2)
Grüne und rote LEDs
Servo-Motor (SG90)
Steckbrett, Widerstände und Kabel
Software
Entwicklungsumgebung: Arduino IDE
Benötigte Bibliotheken:
SPI.h
MFRC522.h
Wire.h
LiquidCrystal_I2C.h
Servo.h
Anforderungen
Arduino IDE (Version 1.8.0 oder neuer).
Die oben genannten Hardware-Komponenten korrekt gemäß dem Schaltplan anschließen.
Benötigte Bibliotheken installieren (via Bibliotheksmanager in der Arduino IDE).
Installation und Einrichtung
Hardware aufbauen:
RFID-Modul, LEDs, LCD-Display und Servo gemäß Schaltplan mit dem Arduino verbinden.
PIN-Zuweisungen in der Software überprüfen:
#define SS_PIN 53
#define RST_PIN 5
#define GREEN_LED_PIN 6
#define RED_LED_PIN 7
#define SERVO_PIN 8
Sicherstellen, dass die Stromversorgung (5V) stabil ist.
Code auf den Arduino hochladen:
Arduino IDE öffnen und die Datei rfid_access_control.ino laden.
Sicherstellen, dass der richtige Port und Board-Typ (Arduino Mega 2560) in der IDE eingestellt sind.
Kompilieren und den Code hochladen.
Bibliotheken installieren:
In der Arduino IDE auf Sketch -> Bibliotheken einbinden -> Bibliotheken verwalten klicken.
Folgende Bibliotheken suchen und installieren:
MFRC522
LiquidCrystal_I2C
Servo
RFID-Karten IDs anpassen:
Die erlaubten Karten-IDs und Namen in den Arrays im Code anpassen:
String mitarbeiterIDs[] = {"A395E626", "53DF7C13"}; // Erlaubte Karten-IDs
String mitarbeiterNamen[] = {"Enrico", "Fatih"};    // Namen der Besitzer
Die Anzahl der Mitarbeiter entsprechend ändern:
int anzahlMitarbeiter = 2;
Funktionsweise
RFID-Karte scannen:
Wird eine RFID-Karte erkannt, überprüft das System die UID.
Autorisiert:
Grüne LED leuchtet.
Der Servo öffnet die Tür für 3 Sekunden.
Begrüßung wird auf dem LCD angezeigt.
Nicht autorisiert:
Rote LED leuchtet.
"Karte ungültig" wird auf dem LCD angezeigt.
Beispieleingaben und Ausgaben
Konsolenausgabe:
Autorisiert:
Zutritt für Enrico genehmigt.
Nicht autorisiert:
Unbekannte Karte. Zutritt verweigert.
LCD-Anzeige:
Autorisiert:
Hallo, Enrico
Nicht autorisiert:
Karte ungültig
Erweiterung und Anpassung
Neue Karten hinzufügen:
Die UID der Karte im Array mitarbeiterIDs[] hinzufügen.
Den entsprechenden Namen im Array mitarbeiterNamen[] ergänzen.
LCD-Adresse anpassen:
Die Adresse des LCDs ändern, falls das Display nicht reagiert:
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adresse ändern, z. B. auf 0x3F
Servo-Anpassungen:
Servowinkel für Türöffnungs- und Schließpositionen anpassen:
tuerServo.write(90);  // ÖffnentuerServo.write(0);   // Schließen
Testprotokoll
Autorisiert:
Grüne LED leuchtet, LCD zeigt Begrüßung, Servo öffnet die Tür.
Nicht autorisiert:
Rote LED leuchtet, LCD zeigt "Karte ungültig".
Reaktionszeit:
< 2 Sekunden von Scan bis Anzeige.
