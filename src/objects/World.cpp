#include "World.hpp"
#include <iostream>

static uint8_t r = 135;
static uint8_t g = 206;
static uint8_t b = 235;

inline float World::ComputeLighting(Point3f p, Vector3f n)
{
    using namespace VectorUtilities;
    float intensity = 0;
    Vector3f lVec;
    for (Light *l : lights)
    {
        if (l->lt == ambient)
        {
            intensity += l->getIntensity();
        }
        else
        {
            switch (l->lt)
            {
            case point:
                lVec = ((l->getPosition()) - p);
                break;
            case directional:
                lVec = l->getDirection();
                break;
            }

            float n_dot_l = fabs(dotProduct(n, lVec));
            if (n_dot_l > 0)
            {
                intensity += l->getIntensity() * (n_dot_l / (n.length() * lVec.length()));
            }
        }
    }
    return intensity;
}

World::World()
{
    camera = Camera(Point3f(5, 5, 5), Point3f(0, 0, 0), Point3f(0, 1, 0));

    bgColor = Color(r, g, b);

    Light *l = new Light(Point3f(0, 0, 0), Vector3f(0, 0, 0), 0.2);
    lights.push_back(l);

    Light* l2 = new Light(Point3f(2, 1, 0), Vector3f(0, 0, 0), 0.6);
    l2->SetType(point);
    lights.push_back(l2);

    Light* l3 = new Light(Point3f(-2, 1, 0), Vector3f(0, 0, 0), 0.6);
    l3->SetType(point);
    lights.push_back(l3);

    Plane *p = new Plane(Vector3f(0, 1, 0), Point3f(0, -1, 0), Color(255, 0, 0));
    objects.push_back(p);

    Circle *c = new Circle(1, Color(0, 0, 255));
    c->Translate(0, -1, 3);
    c->ApplyTransformation();
    objects.push_back(c);

    Cylinder *cyl = new Cylinder(Vector3f(0, 1, 0), 1.2, 0.2, Color(0, 120, 120));
    cyl->RotateX(PI / 3);
    cyl->Translate(0, 0, 2);
    cyl->ApplyTransformation();
    //objects.push_back(cyl);

    Cone *cone = new Cone(Vector3f(0, 1, 0), 1, 1, Color(0, 255, 0));
    cone->LoadIdentity();
    cone->Translate(0, 0, 6.5);
    cone->ApplyTransformation();
    //objects.push_back(cone);

    Triangle *t = new Triangle(Point3f(0, 0, 4), Point3f(0, 1, 3), Point3f(1, 0, 3), Color(255, 255, 255));
    //t->RotateZ(PI / 3);
    //t->Translate(1, 0, 1);
    t->ApplyTransformation();
    objects.push_back(t);
}

Color World::computeColor(Ray &ray, float vz)
{
    Color retColor = bgColor;

    float minimalT = INFINITY;
    for (BaseObject *ob : objects)
    {

        if (ob->Intersects(ray))
        {
            float t = ob->getTmin();
            if (t >= vz)
            {
                if (t < minimalT)
                {
                    minimalT = t;
                    Point3f p = ray.getPoint(t);
                    retColor = ob->getColor() * ComputeLighting(p, ob->getNormal(p));
                }
            }
        }
    }
    //std::cout<<"T minimal"<<tminimal << "X:" << p.x << "Y:" << p.y << "Z:" << p.z << std::endl;
    return retColor;
}
