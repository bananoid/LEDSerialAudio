#include <Arduino.h>

#include "AudioBoard.h"

void setup()
{

  Serial.begin(2000000);

  while (!Serial && millis() < 3000)
  {
  }

  Serial.println("Srart");

  audioBoard->begin();
}

void loop()
{
  audioBoard->update();
}