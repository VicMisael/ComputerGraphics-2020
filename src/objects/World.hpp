
#ifndef _WORLD_
#define _WORLD_
#include "BaseObject.hpp"
#include "Circle.hpp"
#include "Cylinder.hpp"
#include "Plane.hpp"
#include "../util/Ray.hpp"
#include "../util/Color.hpp"
#include <iostream>
#include <vector>
#include "Camera.hpp"
#include "Triangle.hpp"
#include "Cone.hpp"
#include "Cube.hpp"
#include "../util/Light.hpp"
class World{
     std::vector<BaseObject*> objects;
     std::vector<Light*> lights;
     Camera camera;
     float ComputeLighting(Point3f p,Vector3f n,Vector3f V,float s);
public:
    World();
    Color bgColor;
    Color computeColor(Ray &ray,float vz);
};  
#endif