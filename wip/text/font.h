#ifndef FONT_H
#define FONT_H

#include <Arduino.h>

struct Glyph {
  char c;
  uint8_t rows[7];
};

extern const Glyph font[];

#endif