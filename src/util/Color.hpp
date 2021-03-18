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