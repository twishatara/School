#include <stdio.h>
#include <stdlib.h>

uint8_t vec[1024];  //unsigned byte/char

uint32_t result = 0;

 

int main() {

 for (int i = 0; i < 1024; i++) {

 result += vec[i]; 

 }

}
