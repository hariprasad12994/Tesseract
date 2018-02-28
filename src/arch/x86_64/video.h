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

class primitiveVGA{
private:
  volatile uint16_t* textMemoryPointer;
  uint8_t cursor_x;
  uint8_t cursor_y;
  uint8_t color;

public:
  primitiveVGA(uint8_t foregroundColor, uint8_t backgroundColor);
  void clearScreen();
  void printCharToScreen(char ch);
  void scroll();
  void printFmt(int num, char specifier);
  void printFmt(const char* str, char specifier);
  void print(const char* c);
  template<typename T, typename... Args>
  void print(const char* s, T value, Args... args){
    while(*s){
      if(*s == '%' && *(s+1)!= '%'){
        char fmt = *(s+1);
        s++;
        printFmt(value, fmt);
        print(++s, args...);
        return;
      }
      else
        printCharToScreen(*s++);
    }
  }
};

#endif
