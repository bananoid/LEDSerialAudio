#include "AudioBoard.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioInputI2S i2s1;            //xy=356,458
AudioOutputI2S i2s2;           //xy=867,361
AudioAnalyzeFFT1024 fft1024_1; //xy=746,538
AudioConnection patchCord1(i2s1, 0, fft1024_1, 0);
AudioConnection patchCord2(i2s1, 0, i2s2, 0);
AudioConnection patchCord3(i2s1, 1, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1; //xy=736,779

#include <PacketSerial.h>

#define PACKET_SIZE 3
// #define PACKET_BUFFER_SIZE 256;
uint8_t packet[PACKET_SIZE] = {0, 0, 0};
// PacketSerial audioPacketSerial;

// PacketSerial audioPacketSerial;
PacketSerial_<COBS, 0, PACKET_SIZE> audioPacketSerial;
// PacketSerial_<SLIP, 0, PACKET_SIZE> audioPacketSerial;

AudioBoard::AudioBoard()
{
  pinMode(13, OUTPUT);
}

void AudioBoard::begin()
{
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);

  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  // sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);

  sgtl5000_1.micGain(10); // from 0db to 63db
  sgtl5000_1.lineInLevel(0);

  // try 2000000
  // audioPacketSerial.begin(115200, 6); // 0 is Serial, 1 is Serial1
  // audioP acketSerial.begin(115200); // 0 is Serial, 1 is Serial1
  // audioPacketSerial.setPacketHandler(&onPacketReceived);

  audioPacketSerial.begin(80000000);
  audioPacketSerial.setStream(&Serial6);
}

void AudioBoard::update()
{
  if (fft1024_1.available())
  {
    bandLowVal = fft1024_1.read(0, 10);
    bandMidVal = fft1024_1.read(11, 80);
    bandHighVal = fft1024_1.read(81, 500);

    analogWrite(13, bandLowVal * 255);

    packet[0] = bandLowVal * 255;
    packet[1] = bandMidVal * 255;
    packet[2] = bandHighVal * 255;
    // packet[0] = 102;
    // packet[1] = 255;
    // packet[2] = 55;

    audioPacketSerial.send(packet, PACKET_SIZE);
  }
}

AudioBoard *audioBoard = new AudioBoard();