#include "World.hpp"
#include <iostream>



static uint8_t r = 203;
static uint8_t g = 224;
static uint8_t b = 233;

Vector3f inline ReflectRay(const Vector3f R,const Vector3f N) {
    using namespace VectorUtilities;
    return ((N * 2) * dotProduct(N, R) - R);
}

float inline World::ComputeLighting(Point3f& p, Vector3f& n, Vector3f& V, float s)
{
    using namespace VectorUtilities;
    float intensity = 0;
    Vector3f lVec;
    float distanceFactor=1;
    for (Light* l : lights)
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
                distanceFactor=1/sqrtf(fabs(lVec.length()));
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
                        if (t_min>0.01&&t_min <=lveclength) {
                            return intensity;

                        }
                    }
                }
            }
#endif

            float n_dot_l = dotProduct(n, lVec);
            if (n_dot_l > 0)
            {
                intensity += (l->getIntensity()* distanceFactor)*(n_dot_l / (n.length() * lVec.length()));
            }
            if (s >= 0) {
                Vector3f R = ReflectRay(lVec, n);
                float r_dot_v = dotProduct(R, V);
                if (r_dot_v > 0) {
                    intensity += l->getIntensity() * pow(r_dot_v / (R.length() * V.length()), s);
                }

            }
        }
    }
    return intensity;
}

void inline World::init()
{
    //camera = Camera(Point3f(5, 5, 5), Point3f(0, 0, 0), Point3f(0, 1, 0));
    Matrix4x4 camTransformation;
    if (camera != NULL) {
        camTransformation = (camera->getWorldToCamera());
    }
    bgColor = Color(r, g, b);


    Light* lambient = new Light(Point3f(0, 0, 0), Vector3f(0, 1, 0), 0.25);
    //lights.push_back(lambient);
    
    Light* l2 = new Light(Point3f(0,7,-3), Point3f(0, 0, 0), 3);
    l2->SetType(point);
    lights.push_back(l2);

    Light* l3 = new Light(Point3f(3, 1.2, 0), Point3f(0, 0, 0), 1);
    l3->SetType(point);
    lights.push_back(l3);

    Light* l4 = new Light(Point3f(0,0,0), Point3f(0, 1,0 ), 0.1);
    l4->SetType(directional);
    lights.push_back(l4);


    Plane* p = new Plane(Vector3f(0,1,0),Point3f(0,-1,0),Color(255,226,198));
    p->setSpecular(1000);
    objects.push_back(p);


    Plane* p2 = new Plane(Vector3f(0, 0, -1), Point3f(0, -1, 19), WHITE);
    p2->setSpecular(300);

    objects.push_back(p2);

    Cube* building = new Cube(1, 1, 1, Color(169, 169, 169));
    building->Scale(2, 4, 1);
    //cubeShear->Sheary(1, 1.5);
    building->RotateY(PI / 4);
    building->Translate(-1, -0.5, 6);
    building->setReflectivness(.7);
    objects.push_back(building);

    Cube* buildin2 = new Cube(1, 1, 1, Color(169,169,169));
    buildin2->Scale(2, 4, 1);
    //cubeShear->Sheary(1, 1.5);
    buildin2->RotateY(PI / 6);
    buildin2->Translate(1.5, -0.5, 6);
    buildin2->setReflectivness(.7);
    objects.push_back(buildin2);

    Cube* buildin3 = new Cube(1, 1, 1, Color(255, 255, 255));
    buildin3->Scale(1, 3, 1);
    buildin3->Shearx(1, 1);
    buildin3->RotateY(PI / 6);
    buildin3->Translate(-2, -0.5, 3);
    buildin3->setReflectivness(.07);
    objects.push_back(buildin3);
    
    //Objetos extras
    Circle* cBola = new Circle(0.6 , WHITE);
    cBola->setSpecular(1000);
    cBola->Translate(1,-1,2);
    cBola->setReflectivness(0.5);
    objects.push_back(cBola);

    //Snowman
    //Diferen�a do raio do primeiro pro 0
    float radiusDiff=-0.6;
    Circle* c = new Circle(0.6 , Color(255, 255, 255));
    c->setSpecular(1000);
    //c->setReflectivness(1);
    c->Translate(1,radiusDiff,5);
    objects.push_back(c);
    c = new Circle(0.4, Color(255, 255, 255));
    c->setSpecular(1000);
    c->Translate(1, radiusDiff+0.9, 5);
    objects.push_back(c);
    c = new Circle(0.25, Color(255, 255, 255));
    c->setSpecular(1000);
    c->Translate(1, radiusDiff+1.4 , 5);
    objects.push_back(c);
    Cone* nose = new Cone(Vector3f(0, 0, 1), 0.5, 0.1, Color(255, 165, 0));
    nose->RotateY(PI / 2);
    nose->Translate(1, radiusDiff+1.4, 5);
    objects.push_back(nose);
    Cone* snowManHat = new Cone(Vector3f(0, 1, 0), 0.6, 0.30, Color(18, 10, 143));
    snowManHat->setReflectivness(0.5);
    snowManHat->Translate(1, radiusDiff + 1.6, 5);
    snowManHat->setSpecular(900);
    objects.push_back(snowManHat);

//Cilindro
    Cylinder* cyl = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(100, 120, 120));
    cyl->setSpecular(900);
    //cyl->setReflectivness(0.8);
    cyl->Translate(1.4, 0.5,2);
    objects.push_back(cyl);

    Cylinder* cyl2 = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(0, 120, 120));
    cyl2->setSpecular(900);
    //cyl2->setReflectivness(0.8);
    cyl2->Translate(1.8, 0.5,2.3);
    objects.push_back(cyl2);

    Cone* cone2 = new Cone(Vector3f(0, 1, 0), 0.7, 0.8, Color(173, 216, 230));
    cone2->setSpecular(1000);
    cone2->LoadIdentity();
    //cone->RotateX(PI / 6);
    cone2->Translate(1.6, 0.5, 2);
    //cone2->setReflectivness(1);
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
    cube->setReflectivness(0.4);
    cube->RotateY(-PI/4);
    cube->Translate(-1.5, -1, 2);
    objects.push_back(cube);

    Cube* cube2 = new Cube(1.5, 0.5, 0.5, Color(249, 234, 195));
    cube2->setSpecular(10000);
    cube2->setReflectivness(0.1);
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

Color World::computeColor(Ray &ray, float vz,int rd)
{   
 
    Color retColor = bgColor;
    
    BaseObject* ClosestIntersected=NULL;
    float minimalT = INFINITY;
    bool isReflective = false;
    float reflectivness;
    float reflectT;
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
                    Point3f point =ray.getPoint(t);
                    
                    Vector3f Normal = ob->getNormal(point);
                    
                    Vector3f invdir=ray.D * -1;
                    retColor = ob->getColor() * ComputeLighting(point,Normal,invdir ,ob->getSpecular());
                    if(isReflective=(ob->getReflectivness()>0)){
                        ClosestIntersected = ob;
                        reflectT=t;
                    }
                }
            }           
        }
    }
#ifdef _RENDERWITHREFLECTIONS_
    if (rd>0&&isReflective) {
        const float rindex = ClosestIntersected->getReflectivness();
        const Vector3f Normal=ClosestIntersected->getNormal(ray.getPoint(reflectT));
        Vector3f dir=ray.D*-1;
        Ray reflected_ray(ray.getPoint(minimalT), ReflectRay(dir, Normal), 0);
        Color refCol = computeColor(reflected_ray,vz ,rd - 1);
        retColor= retColor * (1 - rindex) + refCol * rindex;
       
    }
#endif
    return retColor;
}
