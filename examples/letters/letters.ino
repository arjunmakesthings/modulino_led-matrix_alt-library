/*
  see a single letter.
*/

#include <points.h>
#include <font.h>

Matrix matrix;

//the header file will return an array of vectors ([{}, {}]) for the passed string.
auto pts = serif_font::pixels('a');

void setup() {
  matrix.begin();

  //matrix has to be vertical for font to work correctly:
  matrix.set_rotation(90);
}

void loop() {
  for (int i = 0; i < pts.size(); i++) {
    matrix.point(pts[i].x, pts[i].y);
    matrix.show();
  }
}
