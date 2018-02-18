#ifndef __VIDEO_H
#define __VIDEO_H

#include "types.h"

#define BUFFER_HEIGHT 25
#define BUFFER_WIDTH 80

enum Color{
  Black = 0,
  Blue,
  Green,
  Cyan,
  Red,
  Magenta,
  Brown,
  LightGray,
  DarkGray,
  LightBlue,
  LightCyan,
  LightRed,
  Pink,
  Yellow,
  White
};

class videoHandler{
private:
  volatile uint16_t* textMemoryPointer;
  uint8_t cursor_x;
  uint8_t cursor_y;
  uint8_t textColor;

public:
  videoHandler();
  videoHandler(uint8_t foregroundColor, uint8_t backgroundColor);
  void clearScreen();
  void printToScreen(char* string);
  void scroll();
};

#endif
