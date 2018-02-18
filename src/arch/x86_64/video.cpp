#include "video.h"
// #include "lib.h"

videoHandler :: videoHandler(uint8_t foregroundColor, uint8_t backgroundColor){
  this->textMemoryPointer = (uint16_t*)0xb8000;
  this->cursor_x = 0;
  this->cursor_y = 0;
  this->textColor = (backgroundColor << 4) | (foregroundColor & 0x0F);
}

void videoHandler :: clearScreen(){
  uint16_t blank = 0x20;
  uint16_t charToBeWritten = blank | (this->textColor << 8);
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

void videoHandler :: scroll(){

}

void videoHandler :: printToScreen(char* string) {
  uint16_t screen_index, string_index;
  for(screen_index = this->cursor_y * 80 + this->cursor_x, string_index = 0;
    string[string_index] != '\0';
    ++screen_index, ++string_index){

      if(this->cursor_y > BUFFER_HEIGHT){
        // To Do: Scrolling method
      }

      if(string[string_index] != '\n'){
        *(this->textMemoryPointer + screen_index) = (*(this->textMemoryPointer +
                                                      screen_index) & 0xFF00) |
                                                      string[string_index];
        this->cursor_x += 1;
        if(this->cursor_x > BUFFER_WIDTH){
          this->cursor_x = 0;
          this->cursor_y += 1;
            if(this->cursor_y > BUFFER_HEIGHT){
              // To Do: Scrolling method
            }
        }
      }
      else{
        this->cursor_x = 0;
        this->cursor_y += 1;
        if(this->cursor_y > BUFFER_HEIGHT){
          // To Do: Scrolling method
        }
      }
    }
}
