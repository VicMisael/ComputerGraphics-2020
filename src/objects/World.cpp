#include "World.hpp"
#include <iostream>

static uint8_t r = 135;
static uint8_t g = 206;
static uint8_t b = 235;

void World::init()
{
    //camera = Camera(Point3f(5, 5, 5), Point3f(0, 0, 0), Point3f(0, 1, 0));
    Matrix4x4 camTransformation;
    if (camera != NULL) {
        camTransformation = (camera->getWorldToCamera());
    }
    bgColor = Color(r, g, b);


    Light* lambient = new Light(Point3f(0, 0, 0), Vector3f(0, 1, 0), 0.2);
    lights.push_back(lambient);
    
    Light* l2 = new Light(Point3f(1,3, 2),Point3f(0,0,0),1);
    l2->SetType(point);
    lights.push_back(l2);

    //Light* l3 = new Light(camera->getEyePosition(), Point3f(0, 0, 0), 1);
    //l3->SetType(point);
    //lights.push_back(l3);

    Plane* p = new Plane(Vector3f(0,1,0),Point3f(0,-1,0),Color(0,244,0));
    objects.push_back(p);
    Plane* p2 = new Plane(Vector3f(0, 0, 1), Point3f(0, -1, 6), Color(120, 120, 120));
    objects.push_back(p2);

    Circle* c = new Circle(.6, Color(0, 0, 255));
    c->setSpecular(500);
    c->Translate(0, 1, 4);
    c->ApplyTransformation();

    objects.push_back(c);

    Cylinder* cyl = new Cylinder(Vector3f(0, 1, 0), 1.2, 0.2, Color(0, 120, 120));
    cyl->setSpecular(100);
    cyl->Translate(0, 0,4);
    cyl->ApplyTransformation();

    objects.push_back(cyl);

    Cone* cone = new Cone(Vector3f(0, 1, 0), 1, 1, Color(0, 255, 0));
    cone->setSpecular(1000);
    cone->LoadIdentity();
    cone->RotateY(PI / 4);
    cone->Translate(0, 0, 4);
    cone->ApplyTransformation();
    objects.push_back(cone);
    
    Cube* cube = new Cube(1, 1, 1, Color(0, 0, 255));
    cube->setSpecular(600);
    cube->Translate(0, 0, 2);
    cube->ApplyTransformation();
    objects.push_back(cube);
    //for (Light* l : lights) {
    //    l->ApplyCamera(camTransformation);
    //}
    for (BaseObject* ob : objects) {
        ob->ApplyCamera(camTransformation);
   }

}

//Receives the intersection point,the normal vector at the point of intersection, the Vector pointing to the camera
float World::ComputeLighting(Point3f p, Vector3f n,Vector3f V,float s)
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
            float lveclength = lVec.length();
            lVec.normalize();
#ifdef _RENDERWITHSHADOWS_
            for (BaseObject* ob : objects) {
                Ray r = Ray(p, lVec, 0);
                if (ob->Intersects(r)) {
                    if (ob->getTmin() > 0.2) {
                        return intensity;
                    }
                }
            }
#endif
         

            float n_dot_l = dotProduct(n, lVec);
            if (n_dot_l > 0)
            {
                intensity += l->getIntensity() * (n_dot_l / (n.length() * lVec.length()));
            }
            if (s >=0) {
                Vector3f R =  (n*2)* dotProduct(n, lVec) - lVec;
                float r_dot_v = dotProduct(R, V);
                if (r_dot_v>0) {
                    intensity += l->getIntensity() * pow(r_dot_v / (R.length() * V.length()), s);
                }
            
            }
        }
    }
    return intensity;
}

World::World()
{
    //camera = Camera(Point3f(5, 5, 5), Point3f(0, 0, 0), Point3f(0, 1, 0));
    camera=NULL;
    init();
}

World::World(Camera c)
{
    camera = &c;
    init();
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
            if (t > vz)
            {
                if (t < minimalT)
                {
                    minimalT = t;
                    Point3f p = ray.getPoint(t);
                    retColor = ob->getColor() * ComputeLighting(p, ob->getNormal(p),ray.D*-1,ob->getSpecular());
                }
            }
        }
    }
    return retColor;
}
