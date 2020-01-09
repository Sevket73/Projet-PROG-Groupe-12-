#ifndef __big_endian_h__
#define __big_endian_h__
#include <stdint.h>

  uint16_t Traduire_uint16(uint16_t val);
  int16_t swap_int16(int16_t val);
  uint32_t Traduire_uint32(uint32_t val);
  int32_t swap_int32(int32_t val);

#endif