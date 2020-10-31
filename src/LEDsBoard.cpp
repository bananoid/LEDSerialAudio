#include "LEDsBoard.h"

#include <OctoWS2811.h>

#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 8

const int NUMPIXELS = NUM_LEDS_PER_STRIP * NUM_STRIPS;
DMAMEM int displayMemory[NUM_LEDS_PER_STRIP * 6];
int drawingMemory[NUM_LEDS_PER_STRIP * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(NUM_LEDS_PER_STRIP, displayMemory, drawingMemory, config);

LEDsBoard::LEDsBoard()
{
}

void LEDsBoard::begin()
{
  leds.begin();
}

void LEDsBoard::update()
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    // leds[i] = CHSV(0, 255, 255);
    // osc = sinf(t + i * 0.02f) * 0.5f + 0.5f;
    // osc = osc * osc * osc * pick;
    // leds[i] = CRGB(osc * 255, osc * 255 * pick * 10, osc * 255 * pick * 10);
    // leds[i] = CRGB(osc * 255, 0, 0);

    // leds.setPixel(i, 0xFF0000);
    leds.setPixel(i, 255, 0, 0);
  }

  leds.show();
}

LEDsBoard *ledsBoard = new LEDsBoard();