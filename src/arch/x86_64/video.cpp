#include "video.h"
#include "lib.h"

primitiveVGA :: primitiveVGA(uint8_t foregroundColor, uint8_t backgroundColor){
  this->textMemoryPointer = (uint16_t*)0xb8000;
  this->cursor_x = 0;
  this->cursor_y = 0;
  this->color = (backgroundColor << 4) | (foregroundColor & 0x0F);
}

void primitiveVGA :: clearScreen(){
  uint16_t blank = 0x20;
  uint16_t charToBeWritten = blank | (this->color << 8);
  uint16_t index;
  uint8_t cursor_x = this->cursor_x;
  uint8_t cursor_y = this->cursor_y;
  for(cursor_y = 0; cursor_y < BUFFER_HEIGHT; cursor_y++){
    for(cursor_x = 0; cursor_x < BUFFER_WIDTH; cursor_x++){
      index = cursor_y * 80 + cursor_x;
      *(this->textMemoryPointer + index) = charToBeWritten;
    }
  }
}

void primitiveVGA :: scroll(){
  uint8_t cursor_x;
  uint8_t cursor_y;
  uint16_t srcIndex, destIndex;
  for(cursor_y = 0; cursor_y < BUFFER_HEIGHT; cursor_y++){
    for(cursor_x = 0; cursor_x < BUFFER_WIDTH; cursor_x++){
      srcIndex = (cursor_y + 1) * 80 + cursor_x;
      destIndex = cursor_y * 80 + cursor_x;
      *(this->textMemoryPointer + destIndex) = *(this->textMemoryPointer + srcIndex);
    }
  }
}

void primitiveVGA :: printCharToScreen(char ch) {
  uint16_t screen_index = this->cursor_y * 80 + this->cursor_x;
  switch(ch){
    case '\n':
      {
        this->cursor_x = 0;
        this->cursor_y += 1;
        break;
      }

    case '\r':
      {
        this->cursor_x = 0;
        break;
      }

    case '\t':
      {
        uint16_t blank = 0x20;
        uint16_t charToBeWritten = blank | (this->color << 8);
        int iter = 0;
        for(iter = 0; iter < 5; iter++){
          *(this->textMemoryPointer + screen_index) = (*(this->textMemoryPointer +
                                                      screen_index) & 0xFF00) |
                                                      ch;
          this->cursor_x += 1;
        }
        break;
        }

    default :
      {
        *(this->textMemoryPointer + screen_index) = (*(this->textMemoryPointer +
                                                    screen_index) & 0xFF00) |
                                                    ch;
        this->cursor_x += 1;
      }
  }
  // handle line wraps and scrolling
  if(this->cursor_x >= BUFFER_WIDTH){
    this->cursor_x = 0;
    this->cursor_y += 1;
  }

  if(this->cursor_y >= BUFFER_HEIGHT){
    scroll();
  }
}

void primitiveVGA :: printFmt(const char* str, char specifier){
  while(*str){
      printCharToScreen(*str++);
  }
}

void primitiveVGA :: printFmt(int num, char specifier){
  char* buffer;
  char temp[20];
  int base;
  switch(specifier){
    case 'x': base = 16;
              break;
    case 'd': base = 10;
              break;
    case 'o': base = 8;
              break;
  }

  buffer = itoa(num, temp, base);
  int i = 0;
  while(buffer[i] != '\0'){
    printCharToScreen(buffer[i]);
    i++;
  }
}

void primitiveVGA :: print(const char* s){
  while(*s){
      printCharToScreen(*s++);
  }
}
