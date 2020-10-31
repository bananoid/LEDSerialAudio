#ifndef AUDIO_BOARD_H
#define AUDIO_BOARD_H

class AudioBoard
{
private:
public:
  float bandLowVal = 0;
  float bandMidVal = 0;
  float bandHighVal = 0;

  AudioBoard();
  void begin();
  void update();
};

extern AudioBoard *audioBoard;

#endif