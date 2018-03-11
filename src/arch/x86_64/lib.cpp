#include "lib.h"

char* itoa(uint64_t num, char* str, int base){
    int i = 0;
    bool isNegative = false;

    if(num == 0){
      str[i++] = '0';
      str[i] = '\0';
      return str;
    }

    if(num < 0 && base == 10){
      isNegative = true;
      num = -num;
    }

    while(num != 0){
      int rem = num % base;
      str[i++] = (rem > 9) ? (rem-10) + 'a' : rem + '0' ;
      num = num/base;
    }

    if (isNegative)
      str[i++] = '-';

    str[i] = '\0';

    int stringLength = 0;
    int stringIndex = 0;
    while(str[stringIndex] != '\0'){
      stringLength++;
      stringIndex++;
    }

    int leftIndex = 0;
    int rightIndex = stringLength-1;
    char temp;
    while(leftIndex < rightIndex){
      temp = str[leftIndex];
      str[leftIndex] = str[rightIndex];
      str[rightIndex] = temp;
      leftIndex++;
      rightIndex--;
    }

    return str;
}
