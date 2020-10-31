#include <Arduino.h>

// #define IS_AUDIO_BOARD

#ifdef IS_AUDIO_BOARD
#include "AudioBoard.h"
#else
#include "LEDsBoard.h"
#endif

void setup()
{
  Serial6.begin(80000000);
  Serial.begin(2000000);

  // while (!Serial && millis() < 3000)
  // {
  // }

  Serial.println("Srart");

#ifdef IS_AUDIO_BOARD
  audioBoard->begin();
#else
  ledsBoard->begin();
#endif
}

void loop()
{
#ifdef IS_AUDIO_BOARD
  audioBoard->update();
#else
  ledsBoard->update();
#endif
}