#ifndef LEDS_BOARD_H
#define LEDS_BOARD_H

class LEDsBoard
{
private:
public:
  LEDsBoard();
  void begin();
  void update();
};

extern LEDsBoard *ledsBoard;

#endif