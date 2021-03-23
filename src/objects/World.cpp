#include "World.hpp"
#include <iostream>
#include "Cylinder.hpp"

static uint8_t r = 135;
static uint8_t g = 206;
static uint8_t b = 235;


World::World()
{
  



    Circle *c2 = new Circle((float)0.5f, Color(255, 255, 255));
    c2->RotateY(PI/3);
    c2->Translate(1, 1.8, 3);
    c2->ApplyTransformation();
    objects.push_back(c2);

    c2 = new Circle((float)0.8f, Color(0, 0, 255));
    c2->Translate(1.5, 2, 5);
    c2->ApplyTransformation();
    objects.push_back(c2);

    bgColor = Color(r, g, b);
 

    Cylinder* cyl = new Cylinder(Vector3f(0, 1, 0), 1, 2, Color(0, 255, 0));
    cyl->Translate(7, -0.5 , 10);
    cyl->ApplyTransformation();
    objects.push_back(cyl);
    Circle* c = new Circle((float)0.7f, Color(255, 0, 0));
    c->Translate(3, 1, 6);
    c->ApplyTransformation();
    objects.push_back(c);


    
}

Color World::computeColor(Ray &ray)
{
    Color retColor = bgColor;
    for (BaseObject *ob : objects)
    {
        if (ob->Intersects(ray))
        {
            return ob->getColor();
        }
    }
    return retColor;
}