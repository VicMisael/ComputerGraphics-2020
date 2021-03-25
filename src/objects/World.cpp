#include "World.hpp"
#include <iostream>


static uint8_t r = 135;
static uint8_t g = 206;
static uint8_t b = 235;


World::World()
{
  

    bgColor = Color(r, g, b);
    //Plane* p = new Plane(Vector3f(0, 1, 0), Point3f(10, 0, 10), Color(0, 0, 0));
    //objects.push_back(p);

    Circle* c = new Circle(0.5, Color(255, 0, 0));
    c->Translate(3, 1, 5);
    c->ApplyTransformation();
    objects.push_back(c);

    Cylinder* cyl = new Cylinder(Vector3f(0,1,0),1,0.2,Color(0,120,120));
    cyl->Translate(3, 2, 5);
    cyl->ApplyTransformation();
    objects.push_back(cyl);

    Circle *b= new Circle(0.25, Color(255, 255, 255));
    b->Translate(3, 0.5, 6);
    b->ApplyTransformation();
    objects.push_back(b);

    Circle* b1 = new Circle(0.5, Color(255, 255, 255));
    b1->Translate(3, 1, 6);
    b1->ApplyTransformation();
    objects.push_back(b1);

    Circle* b2 = new Circle(1, Color(255, 255, 255));
    b2->Translate(3, 2, 6);
    b2->ApplyTransformation();
    objects.push_back(b2);

    c = new Circle(0.5, Color(0, 0, 200));
    c->Translate(1, 1, 5);
    c->ApplyTransformation();
    objects.push_back(c);

    cyl = new Cylinder(Vector3f(0, 1, 0), 1, 0.2, Color(0, 120, 120));
    cyl->Translate(1, 2, 5);
    cyl->ApplyTransformation();
    objects.push_back(cyl);


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
    Point3f p = ray.getPoint(tminimal);
    //std::cout<<"T minimal"<<tminimal << "X:" << p.x << "Y:" << p.y << "Z:" << p.z << std::endl;
    return retColor;
}