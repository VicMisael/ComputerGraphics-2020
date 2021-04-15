#ifndef _COLOR_
#define _COLOR_
#include <cstdint>
class Color
{
private:
    
public:
    Color();
    Color(float _r, float _g, float _b,float normalizefactor);
    Color(uint8_t color[3]) :Color(color[0], color[1], color[2]) {};
    Color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t rgba();
    Color operator+(const Color& a) const {
        Color NewColor;
        float greater = 1;
        NewColor.color[0] = color[0] + a.color[0];
        NewColor.color[1] = color[1] + a.color[1];
        NewColor.color[2] = color[2] + a.color[2];
        bool normalize=false;
        for (float r : NewColor.color) {
            if (r > greater) {
                greater = r;
                normalize = true;
            }
        }
        if (normalize) {
            for (int i = 0; i < 3; i++) {
                NewColor.color[i] /= r;
            }
        }

        return NewColor;
    }
    Color operator*(const float &a) const
    {  
        float components[3];
        components[0] = r * a;
        components[1] = g * a;
        components[2] = b * a;
        float greater = 1;

        for (float component : components) {
            if (component > greater) {
                greater = component;
            }
        }
        return Color(components[0],components[1],components[2],greater);
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