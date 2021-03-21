#include "World.hpp"
#include <iostream>

static uint8_t r = 135;
static uint8_t g = 206;
static uint8_t b = 235;


World::World()
{

    bgColor = Color(r, g, b);
    Circle *c = new Circle((float)0.7f, Color(255, 0, 0));
    c->Translate(3, 1, 6);
    c->ApplyTransformation();
    objects.push_back(c);

    Circle *c2 = new Circle((float)0.5f, Color(255, 255, 255));
    c2->RotateY(PI/3);
    c2->Translate(1, 1.8, 3);
    c2->ApplyTransformation();
    objects.push_back(c2);

    c2 = new Circle((float)0.8f, Color(0, 0, 255));
    c2->Translate(1.5, 2, 5);
    c2->ApplyTransformation();
    objects.push_back(c2);
}

Color World::computeColor(Ray &ray)
{

    for (BaseObject *ob : objects)
    {
        if (ob->Intersects(ray))
        {
            return ob->getColor();
        }
    }
    return bgColor;
}