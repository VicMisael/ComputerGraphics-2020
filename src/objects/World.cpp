#include "World.hpp"
#include <iostream>

static uint8_t r = 203;
static uint8_t g = 224;
static uint8_t b = 233;

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
    
    Light* l2 = new Light(Point3f(1,0,-0.7), Point3f(0, 0, 0), 1);
    l2->SetType(point);
    //lights.push_back(l2);

    Light* l3 = new Light(Point3f(0, 0, 0), Point3f(0, 1, 0), 1);
    l3->SetType(directional);
    lights.push_back(l3);

    Plane* p = new Plane(Vector3f(0,1,0),Point3f(0,-1,0),Color(255,226,198));
    objects.push_back(p);

    Circle* c = new Circle(.2, Color(255, 255, 255));
    c->setSpecular(500);
    c->Translate(1, 0, -1);
    objects.push_back(c);

//Cilindro
    Cylinder* cyl = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(100, 120, 120));
    cyl->setSpecular(900);
    cyl->Translate(1.4, 0.5,2);
    objects.push_back(cyl);

    Cylinder* cyl2 = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(0, 120, 120));
    cyl2->setSpecular(900);
    cyl2->Translate(1.8, 0.5,2.3);
    objects.push_back(cyl2);

    Cone* cone2 = new Cone(Vector3f(0, 1, 0), 0.7, 0.8, Color(189, 236, 182));
    cone2->setSpecular(1000);
    cone2->LoadIdentity();
    //cone->RotateX(PI / 6);
    cone2->Translate(1.3, 0.5, 2);
    //cone->ApplyTransformation();
    objects.push_back(cone2);
//Cubo
    Cone* cone = new Cone(Vector3f(0, 1, 0), 0.7, 0.8, Color(204, 169, 221));
    cone->setSpecular(1000);
    cone->LoadIdentity();
    //cone->RotateX(PI / 6);
    cone->Translate(-1, 0.5, 2);
    //cone->ApplyTransformation();
    objects.push_back(cone);
    
    Cube* cube = new Cube(1.5, 0.5, 0.5, Color(249, 234, 195));
    cube->setSpecular(10000);
    cube->RotateY(-PI/4);
    cube->Translate(-1.5, -1, 2);
    objects.push_back(cube);

    Cube* cube2 = new Cube(1.5, 0.5, 0.5, Color(249, 234, 195));
    cube2->setSpecular(10000);
    cube2->RotateY(PI/4);
    cube2->Translate(-0.9, -1, 2);
    objects.push_back(cube2);

    for (Light* l : lights) {
       l->ApplyCamera(camTransformation);
    }
    for (BaseObject* ob : objects) {
        ob->ApplyTransformation();
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
            if (renderShadows) {
                for (BaseObject* ob : objects) {
                    Ray r = Ray(p, lVec, 0);
                    if (ob->Intersects(r)) {
                        float t_min = ob->getTmin();
                        if (t_min > 0.1) {
                            return intensity;
                        }
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

void World::SetShadowsOn(bool shadows)
{
    this->renderShadows = shadows;
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
