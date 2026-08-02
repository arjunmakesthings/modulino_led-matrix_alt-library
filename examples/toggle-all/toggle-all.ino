/*
  example to toggle each led on / off. 
*/

#include <points.h>

Matrix matrix;

void setup() {
  //begin talking via i2c:
  matrix.begin();

  //set rotation based on where you want 0,0 to be.
  //optional; defaults to 0. acceptable values: 0,90,180,270.
  matrix.set_rotation(90); 
}

void loop() {
  for (int x = 0; x<matrix.width(); x++){
    for (int y = 0; y<matrix.height(); y++){
      //loop over each x & y:

      //manipulate data:
      matrix.point (x,y); 

      //show on matrix:
      matrix.show(); 

      //wait:
      delay (100); 

      //clear: (try moving this outside the loop to see what happens). 
      matrix.clear(); 
    }
  }
}
