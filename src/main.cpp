#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
const int buzzer = 7;
const int led = 5;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

#include <read.h>

void setup() {
    pinMode(buzzer, OUTPUT);
    pinMode(led, INPUT_PULLUP);

    // turn off led first
    digitalWrite(led, LOW);
    
    Serial.begin(115200);
    SPI.begin();
    mfrc522.PCD_Init();
    Keyboard.begin();
}

void loop() {
    execReader();
    delay(100);
}