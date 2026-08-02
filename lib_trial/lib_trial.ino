#include "points.h"

Matrix matrix; 

void setup() {
  // put your setup code here, to run once:

  matrix.begin(); 

  matrix.clear(); 

}

void loop() {
  // put your main code here, to run repeatedly:

  matrix.point(0,0); 

  matrix.show(); 

  delay (1000); 

}
