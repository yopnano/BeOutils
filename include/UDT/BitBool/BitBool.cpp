#include "BitBool.h"

//Lookup tables for BitRef
template<> const uint8_t BitRef<false>::shift[8] = { 1,2,4,8,16,32,64,128 };
template<> const uint8_t BitRef<true>::shift[8] = { 128,64,32,16,8,4,2,1 };