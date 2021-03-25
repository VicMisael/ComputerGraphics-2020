#include "World.hpp"
#include <iostream>



static uint8_t r = 135;
static uint8_t g = 206;
static uint8_t b = 235;


World::World()
{
    camera=Camera(Point3f(5,5,5),Point3f(0,0,0),Point3f(0,1,0));

    bgColor = Color(r, g, b);
    //Plane* p = new Plane(Vector3f(1, 0, 0), Point3f(10, 0, 10), Color(0, 0, 0));
    //objects.push_back(p);

    Circle* c = new Circle(0.5, Color(255, 0, 0));
    c->Translate(0, 0, 5);
    c->ApplyTransformation();
    objects.push_back(c);

    c = new Circle(5, Color(0, 0, 255));
    c->Translate(0, 0, 10);
    c->ApplyTransformation();
    objects.push_back(c);

    Cylinder* cyl = new Cylinder(Vector3f(0, 1, 0), 1.2, 0.2, Color(0, 120, 120));
    cyl->RotateX(PI/6);
    cyl->Translate(0, 1, 3);
    cyl->ApplyTransformation();
    objects.push_back(cyl);

    //Triangle* t = new Triangle(Point3f(0,0,3), Point3f(1, 0, 3),Point3f(0,1,3),Color(255,0,255));
    //objects.push_back(t)

}

Color World::computeColor(Ray &ray,float vz)
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
    //std::cout<<"T minimal"<<tminimal << "X:" << p.x << "Y:" << p.y << "Z:" << p.z << std::endl;
    return retColor;
}