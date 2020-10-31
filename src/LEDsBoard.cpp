#include "LEDsBoard.h"

#include <OctoWS2811.h>

#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 8

const int NUMPIXELS = NUM_LEDS_PER_STRIP * NUM_STRIPS;
DMAMEM int displayMemory[NUM_LEDS_PER_STRIP * 6];
int drawingMemory[NUM_LEDS_PER_STRIP * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(NUM_LEDS_PER_STRIP, displayMemory, drawingMemory, config);

// Packet Serial -----------------------------
#include <PacketSerial.h>

#define PACKET_SIZE 8
// #define PACKET_BUFFER_SIZE 256;
uint8_t packet[PACKET_SIZE] = {0, 0, 0};
// PacketSerial audioPacketSerial;

// PacketSerial audioPacketSerial;
PacketSerial_<COBS, 0, PACKET_SIZE> audioPacketSerial;
// PacketSerial_<SLIP, 0, PACKET_SIZE> audioPacketSerial;

LEDsBoard::LEDsBoard()
{
}

void LEDsBoard::begin()
{
  leds.begin();
  audioPacketSerial.begin(80000000);
  audioPacketSerial.setStream(&Serial6);
  audioPacketSerial.setPacketHandler(&onPacketReceived_external);
}

void LEDsBoard::update()
{
  audioPacketSerial.update();
  float time = millis();
  for (int i = 0; i < NUMPIXELS; i++)
  {
    float osc = sinf(time * 0.003 + i * 0.08) * 0.5 + 0.5;

    leds.setPixel(i, packet[0], osc * 255, packet[2]);
    // leds.setPixel(i, 255, 0, 0);
    // leds.setPixel(i, 255, 0, 0);
  }

  leds.show();
}

void LEDsBoard::onPacketReceived(const uint8_t *buffer, size_t size)
{
  memcpy(packet, buffer, size);

  Serial.print(packet[0]);
  Serial.print(" ");
  Serial.print(packet[1]);
  Serial.print(" ");
  Serial.print(packet[2]);
  Serial.println("");
}

LEDsBoard *ledsBoard = new LEDsBoard();