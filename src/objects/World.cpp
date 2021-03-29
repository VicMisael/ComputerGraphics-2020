#include "World.hpp"
#include <iostream>



static uint8_t r = 135;
static uint8_t g = 206;
static uint8_t b = 235;


World::World()
{
    camera=Camera(Point3f(5,5,5),Point3f(0,0,0),Point3f(0,1,0));

    bgColor = Color(r, g, b);
   

   

    Plane* p = new Plane(Vector3f(0, 1, 0), Point3f(0,-1, 0), Color(0, 0, 0));
    objects.push_back(p);
    

    Circle* c = new Circle(1, Color(0, 0, 255));
    c->Translate(0, 0, 7);
    c->ApplyTransformation();
    objects.push_back(c);


     Cylinder* cyl = new Cylinder(Vector3f(0, 1, 0), 1.2, 0.2, Color(0, 120, 120));
     cyl->RotateX(PI/3);
     cyl->Translate(0, 0, 7);
     cyl->ApplyTransformation();
     objects.push_back(cyl);

    Cone* cone = new Cone(Vector3f(0, 1 , 0), 1, 1, Color(0, 255, 0));
    cone->LoadIdentity();
    cone->Translate(0, 0, 6.5);
    cone->ApplyTransformation();
    objects.push_back(cone);

    Triangle* t = new Triangle(Point3f(0, 0, 4), Point3f(0, 1, 3), Point3f(1, 0, 3), Color(255, 255, 255));
    t->RotateZ(PI / 3);
    //t->Translate(1, 0, 1);
    t->ApplyTransformation();
    objects.push_back(t);

}

Color World::computeColor(Ray &ray,float vz)
{
    Color retColor = bgColor;

    float minimalT = INFINITY;
    for (BaseObject *ob : objects)
    {
     
        if (ob->Intersects(ray))
        {
           float t= ob->getTmin();
           if (t >= vz) {
               if (t < minimalT) {
                   minimalT = t;
                   retColor = ob->getColor();
               }
           }
        }
        
    }
    //std::cout<<"T minimal"<<tminimal << "X:" << p.x << "Y:" << p.y << "Z:" << p.z << std::endl;
    return retColor;
}