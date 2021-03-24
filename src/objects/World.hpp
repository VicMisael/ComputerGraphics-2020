
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
class World{
     std::vector<BaseObject*> objects;
public:
    World();
    Color bgColor;
    Color computeColor(Ray &ray);
};  
#endif