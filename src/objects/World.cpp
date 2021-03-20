#include "World.hpp"
#include <iostream>

World::World(){


    bgColor = Color(135, 206, 235);
    Circle* c = new Circle((float)0.7f, Color(255, 0, 0));
    c->Translate(3,1,6);
    c->ApplyTransformation();
    objects.push_back(c);

    Circle* c2 = new Circle((float)0.5f, Color(123, 255, 0));
    c2->Translate(2, 4, 3);
    c2->ApplyTransformation();
    objects.push_back(c2);


    
}

Color World::computeColor(Ray &ray)
{

    for (BaseObject* ob : objects)
    {
        if (ob->Intersects(ray)>0)
        {
            return ob->getColor();
        }
    }
    return bgColor;
}