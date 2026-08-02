/*
  see a string, over time.
*/

#include <points.h>
#include <font.h>

Matrix matrix;

//string to show:
//remember that spaces are rendered as pauses (no on leds).
String msg = "hi, i'm arjun.";

void setup() {
  matrix.begin();

  //matrix has to be vertical for font to work correctly:
  matrix.set_rotation(90);
}

void loop() {
  for (int i = 0; i < msg.length(); i++) {
    //loop over each character of the message:
    auto pts = serif_font::pixels(msg[i]);

    for (int j = 0; j < pts.size(); j++) {
      const int x = pts[j].x;
      const int y = pts[j].y;
      matrix.point(x, y);
      matrix.show();
    }
    delay(1000);
    matrix.clear(); 
  }
}
