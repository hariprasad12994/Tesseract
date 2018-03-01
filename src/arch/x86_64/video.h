#ifndef __VIDEO_H
#define __VIDEO_H

#include "types.h"

/*
Resolution 640 x 400
*/
#define BUFFER_HEIGHT 25
#define BUFFER_WIDTH 80

/*
Pixel colors possible in basic VGA text mode
*/
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

/*
Class to handle print to screen operation in basic VGA text mode
*/
class primitiveVGA{
private:
  /*
  Private data members:
  Pointer to VGA BIOS memory, x and y position on screen, color code are made
  static so that they are available across all the vga handler classes
  */
  static volatile uint16_t* textMemoryPointer;
  static uint8_t cursor_x;
  static uint8_t cursor_y;
  static uint8_t color;
  /*
  Private member function:
  Printing individual characters to screen, format handling and scrolling
  functionalities are made internal to the class
  */
  void printCharToScreen(char ch);
  void printFmt(int num, char specifier);
  void printFmt(const char* str, char specifier);
  void scroll();

public:
  /*
  Public member function:
  A generic print function which behaves like standard printf is implemented using
  variadic template.
  Public APIs are provided for printing formatted strings and clearing screen 
  */
  primitiveVGA(uint8_t foregroundColor, uint8_t backgroundColor);
  void clearScreen();
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
