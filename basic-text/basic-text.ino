/*

*/

//include for i2c communication:
#include "font.hpp"
#include <Wire.h>

//this is the i2c address of the modulino matrix:
#define MATRIX_ADDR 0x39

enum Rotation {
  ROTATE_0,
  ROTATE_90,
  ROTATE_180,
  ROTATE_270
};

struct Point {
  uint8_t x;
  uint8_t y;
};

class Matrix {
public:
  void begin() {
    Wire.begin();
    clear();
    // show();
  }

  void set_rotation(Rotation r) {
    rotation = r;
  }

  uint8_t width() const {
    return (rotation == ROTATE_0 || rotation == ROTATE_180) ? 12 : 8;
  }

  uint8_t height() const {
    return (rotation == ROTATE_0 || rotation == ROTATE_180) ? 8 : 12;
  }

  void clear() {
    memset(buffer, 0, sizeof(buffer));
  }

  void show() {
    Wire.beginTransmission(MATRIX_ADDR);
    Wire.write(buffer, sizeof(buffer));
    Wire.endTransmission();
  }

  void point(uint8_t x, uint8_t y) {

    if (x >= width() || y >= height())
      return;

    Point p = transform(x, y);

    //kind of like pixels (a 1-d array). bit or i = (y*width) + x.
    int bit = p.y * 12 + p.x;

    buffer[bit / 8] |= (1 << (bit % 8));
  }

  //instead of clearing the whole screen, we can also turn off a single point (led) on the matrix:
  void rem_point(uint8_t x, uint8_t y) {

    if (x >= width() || y >= height())
      return;

    Point p = transform(x, y);

    int bit = p.y * 12 + p.x;

    buffer[bit / 8] &= ~(1 << (bit % 8));
  }

  //for transformation according to rotation:
private:
  Point transform(uint8_t x, uint8_t y) {
    Point p;
    switch (rotation) {

      case ROTATE_0:
        p.x = x;
        p.y = y;
        break;

      case ROTATE_90:
        p.x = y;
        p.y = 7 - x;
        break;

      case ROTATE_180:
        p.x = 11 - x;
        p.y = 7 - y;
        break;

      case ROTATE_270:
        p.x = 11 - y;
        p.y = x;
        break;
    }

    return p;
  }

  uint8_t buffer[12] = { 0 };

  //by default, set it to 0; if not specified:
  Rotation rotation = ROTATE_0;
};

Matrix matrix;
String msg = "jaye is coOl";

void setup() {
  //set once:
  matrix.begin();
  matrix.set_rotation(ROTATE_90);
}

void loop() {


  for (int i = 0; i < msg.length(); i++) {
    //clear before drawing:
    matrix.clear();
    //get letter for character:
    auto pts = font7x12::pixels(msg[i]);

    for (int j = 0; j < pts.size(); ++j) {
      matrix.point(pts[j].x, pts[j].y);
    }
    //show everything sent:
    matrix.show();
    delay(500);
  }
}
