#pragma once

#include <Arduino.h>
#include <Wire.h>

#define MATRIX_ADDR 0x39

struct Point {
    uint8_t x;
    uint8_t y;
};

class Matrix {
public:
    void begin() {
        Wire.begin();
        clear();
    }

    void set_rotation(int r) {
        if (r != 0 && r != 90 && r != 180 && r != 270)
            rotation = 0;
        else
            rotation = r;
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
        int bit = p.y * 12 + p.x;
        buffer[bit / 8] |= (1 << (bit % 8));
    }

private:
    Point transform(uint8_t x, uint8_t y) {
        switch (rotation) {
            case 0:   return {x, y};
            case 90:  return {y, uint8_t(7 - x)};
            case 180: return {uint8_t(11 - x), uint8_t(7 - y)};
            case 270: return {uint8_t(11 - y), x};
        }
        return {x, y};
    }

    uint8_t buffer[12] = {};
    int rotation = 0;
};