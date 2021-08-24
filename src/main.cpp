#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#ifdef PLATFORM_MICRO
#define RST_PIN         9
#define SS_PIN          10
const int buzzer = 11;
const int led = 4;
#elif defined(PLATFORM_PROMICRO)
#define RST_PIN         9
#define SS_PIN          10
const int buzzer = 7;
const int led = 5;
#endif

int ledPin = LED_BUILTIN;

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

    // buzzer
    tone(buzzer, 5000); // Send 1KHz sound signal...
    digitalWrite(led, HIGH);
    delay(100);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    digitalWrite(led, LOW);

    delay(50);        // ...for 1 sec

    tone(buzzer, 5000); // Send 1KHz sound signal...
    digitalWrite(led, HIGH);
    delay(100);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    digitalWrite(led, LOW);
}

void loop() {
    execReader();
    delay(100);
}