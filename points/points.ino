/*
custom library for modulino bought off amazon, because the pin mappings weren't correct.

we store information for the entire matrix in 12 unsigned 8-bit integers (12 * 8 == 96; one bit for each led).

usage: 

-> declare an instance of the matrix like: 
Matrix matrix 

matrix.begin(); 
matrix.set_rotation ({from one of the enums}); 

matrix.clear(); 

matrix.point(x,y); 

... as many

matrix.show(); 
*/

//include for i2c communication:
#include <Wire.h>

//this is the i2c address of the modulino matrix:
#define MATRIX_ADDR 0x39

struct Point {
  uint8_t x;
  uint8_t y;
};

class Matrix {
public:
  void begin() {
    Wire.begin();
    //wipe everything on it earlier:
    clear();
  }

  void set_rotation(int r) {
    if (r != 0 && r != 90 && r != 180 && r != 270) {
      rotation = 0;
    } else {
      rotation = r;
    }
  }

  uint8_t width() const {
    return (rotation == 0 || rotation == 180) ? 12 : 8;
  }

  uint8_t height() const {
    return (rotation == 0 || rotation == 180) ? 8 : 12;
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
  // void rem_point(uint8_t x, uint8_t y) {

  //   if (x >= width() || y >= height())
  //     return;

  //   Point p = transform(x, y);

  //   int bit = p.y * 12 + p.x;

  //   buffer[bit / 8] &= ~(1 << (bit % 8));
  // }

  //for transformation according to rotation:
private:
  Point transform(uint8_t x, uint8_t y) {
    Point p;
    switch (rotation) {

      case 0:
        p.x = x;
        p.y = y;
        break;

      case 90:
        p.x = y;
        p.y = 7 - x;
        break;

      case 180:
        p.x = 11 - x;
        p.y = 7 - y;
        break;

      case 270:
        p.x = 11 - y;
        p.y = x;
        break;
    }

    return p;
  }

  uint8_t buffer[12] = { 0 };

  //by default, set it to 0; if not specified:
  int rotation = 0;
};

Matrix matrix;

void setup() {
  debug_view(90);

  //set once:
  // matrix.begin();
  // matrix.set_rotation(0);
}

void loop() {
  // //clear before drawing:
  // matrix.clear();

  // //draw:
  // matrix.point(0,0);

  // matrix.point(2,0);

  // matrix.point(4,0);

  // //show everything sent:
  // matrix.show();
  // delay(100);
}

void debug_view(int r) {
  Matrix matrix;

  //init:

  matrix.begin();
  matrix.clear();
  matrix.set_rotation(r);

  int x = 0;
  int y = 0;

  while (true) {
    matrix.clear();
    matrix.point(x, y);
    matrix.show();

    delay(50);

    x++;

    if (x >= matrix.width()) {
      x = 0;
      y++;
    }

    if (y >= matrix.height()) {
      break;
    }
  }
}
