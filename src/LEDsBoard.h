#ifndef LEDS_BOARD_H
#define LEDS_BOARD_H

#include <Arduino.h>

class LEDsBoard
{
private:
public:
  LEDsBoard();
  void begin();
  void update();
  void onPacketReceived(const uint8_t *buffer, size_t size);
};

extern LEDsBoard *ledsBoard;

static void onPacketReceived_external(const uint8_t *buffer, size_t size)
{
  ledsBoard->onPacketReceived(buffer, size);
}

#endif