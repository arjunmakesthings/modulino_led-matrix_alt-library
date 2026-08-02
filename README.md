### what: 
i bought a [modulino matrix](https://www.amazon.com/dp/B0GVGXMVHP?ref=ppx_yo2ov_dt_b_fed_asin_title) off of amazon. 

the default library just didn't work (the pin mappings were all wrong). so, i wrote my own. 

---

### points: 
we communicate to the driver directly. information for the entire matrix is in 12 unsigned 8-bit integers (12 * 8 == 96); one bit for each led (on / off). 

usage: 
- define a matrix-instance using `Matrix matrix`. 
- set once: 
    - `matrix.begin()` -> initates i2c communication with the driver. 
    - `matrix.set_rotate({value})` -> values are stored as enums
