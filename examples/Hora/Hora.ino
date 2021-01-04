/**
 * Fichero de ejemplo para la libreria TimeElapsed
 *
 */
#include <TimeElapsed.h>

/**
 * Variable global
 */
TimeElapsed timeCounter;

unsigned long tiempo;
int numero;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  
  timeCounter.reset();
  tiempo = millis();
  delay(2000);
  randomSeed(analogRead(0));
  numero = random(1,10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buffer[20];

  timeCounter.loopTimeElapsed();
  if (millis() - tiempo > numero) {
    timeCounter.getTimeElapsed(buffer,19);
    Serial.println(buffer);
    tiempo = millis();
    numero = random(1,10000);
  }
}
