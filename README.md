### what: 
i bought a [modulino matrix](https://www.amazon.com/dp/B0GVGXMVHP?ref=ppx_yo2ov_dt_b_fed_asin_title) off of amazon. 

the default library just didn't work, because the pin mappings were all wrong. so, i wrote my own. 

since i wanted to use the matrix to make a [nametag](https://arjunmakesthings.github.io/itp-blog/shop-nametag) for myself, i also ended up converting a [7x12 serif font](https://fontstruct.com/fontstructions/show/243645/7_12_serif) into `x, y` coordinates to send them directly to the matrix.

the library has two headers that you can include in your sketches under `./src`:
- `point.h` -> to draw points using x, y coordinates.
- `font.h` -> to draw letters. however, to draw them on the matrix, you must include point.h also.

example code to upload to an arduino can be found in `./examples`. 

---

### points: 
information for the entire matrix is stored in 12 unsigned 8-bit integers (12 * 8 == 96); one bit for each led (on / off). 

usage:
- include the header file with `#include <points.h>`. 
- define a matrix-instance using `Matrix matrix`. 
- set once: 
    - `matrix.begin()` -> initates i2c communication with the driver. 
    - `matrix.set_rotate(int)` -> set rotation for the matrix. if you render text later, you have to make sure that the matrix is in portrait-mode (90 or 270). by default, it's set to 0 (horizontal mode). 
- `matrix.point(x, y)` -> this will enable the led for that point. you can call this as many times as you want, before sending it to the matrix (because we send data for all the leds at once). 
- `matrix.show()` -> to show on the matrix. 
- `matrix.clear()` -> to wipe everything off the matrix, so that we can draw again on a fresh slate.

### letters: 
each character of a 7x12 font (as mentioned above) is stored as `x, y` tuples. since someone actually made the font, this stores more than 8000 glyphs. 

usage: 
- store output into an inferred-type variable with `auto {name} = serif_font::pixels({string});`.
- you can call the method `.length()` on the variable to be able to loop through all points. 
- using `points.h` from above, loop through each point; like so:
    ```cpp
    for (int i = 0; i<pts.size(); i++){
        matrix.point(pts[i].x pts[i].y); 
        matrix.show(); 
    }
    ```
- remember that the font is designed for a 7x12 matrix (and not for a 12x7 matrix). so, your matrix-rotation should be set to 90 or 270 (to ensure that it's in vertical mode).  
