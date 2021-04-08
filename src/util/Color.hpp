#ifndef _COLOR_
#define _COLOR_
#include <cstdint>
class Color
{
private:
    Color(float _r, float _g, float _b,float normalizefactor);
public:
    Color();
    Color(uint8_t color[3]) :Color(color[0], color[1], color[2]) {};
    Color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t rgba();
    Color operator*(const float &a) const
    {  
        return Color((float)r*a,(float)g*a,(float)b*a,1);
    }
    union
    {
        float color[3];
        struct
        {
            float r, g, b;
        };
    };
};

#endif