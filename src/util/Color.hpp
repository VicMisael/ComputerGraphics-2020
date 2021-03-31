#ifndef _COLOR_
#define _COLOR_
#include <cstdint>
class Color
{
public:
    Color() : Color(0, 0, 0){};
    Color(uint8_t color[4]);
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Color operator*(const float &a) const
    {
        float _r=0, _g=0, _b=0;
        if (a > 1) {
            _r = r+(a - 1.0f) * r;
            _g =  g+(a - 1.0f) * g;
            _b = b+(a - 1.0f) * b;
        }
        else {
             _r = r * a, _g = g * a, _b = b * a;
        }
       
       
        return Color(_r>255?255:_r, _g>255?255:_g, _b>255?255:_b,255);
    }
    union
    {
        uint8_t color[4];
        struct
        {
            uint8_t r, g, b, a;
        };
        uint32_t rgba;
    };
};

#endif