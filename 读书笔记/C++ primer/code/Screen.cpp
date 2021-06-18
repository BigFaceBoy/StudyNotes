#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "Screen.h"
#include <string.h>

inline String& String::operator+=(const String &rhs){
    if(rhs._string){
        String tmp(*this);

        _size += rhs._size;
        delete[] _string;

        _string = new char[_size + 1];
        strcpy(_string, tmp._string);
        strcpy(_string + tmp._size, rhs._string);
    }
    return *this;
}

typedef struct
{
unsigned a:8;
unsigned b:30; /*从下一单元开始存放*/
unsigned c:2;
}Bit;



int main(){
    printf("size :%d \n",sizeof(Bit));
    return 0;
}