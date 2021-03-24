#include "World.hpp"
#include <iostream>


static uint8_t r = 0;
static uint8_t g = 0;
static uint8_t b = 0;


World::World()
{
  

    bgColor = Color(r, g, b);

    Circle *c2 = new Circle((float)0.5f, Color(255, 255, 255));
    c2->RotateY(PI/3);
    c2->Translate(1, 1.8, 3);
    c2->ApplyTransformation();
    objects.push_back(c2);

    c2 = new Circle((float)0.8f, Color(0, 0, 255));
    c2->Translate(1.5, 2, 5);
    c2->ApplyTransformation();
    objects.push_back(c2);

   
 

    Cylinder* cyl = new Cylinder(Vector3f(0, 1, 0), 1, 0.5 , Color(0, 255, 0));
    cyl->RotateZ(PI / 6);
    cyl->RotateX(PI / 16);
    cyl->Translate(1, 0 , 5);
    cyl->ApplyTransformation();
    objects.push_back(cyl);
    Circle* c = new Circle((float)0.7f, Color(255, 0, 0));
    c->Translate(0, 0, 5);
    c->ApplyTransformation();
    objects.push_back(c);

    
}

Color World::computeColor(Ray &ray)
{
    Color retColor = bgColor;
    float tminimal = INFINITY;
    for (BaseObject *ob : objects)
    {
        if (ob->Intersects(ray))
        {
            if (ob->getTmin() < tminimal) {
                tminimal = ob->getTmin();
                retColor = ob->getColor();
            }
        }
    }
    return retColor;
}