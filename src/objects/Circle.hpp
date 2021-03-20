
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"
class Circle : public BaseObject
{
public:
    Circle(float radius,Color c);
    float radius;
    Point3f Center;
    int Intersects(Ray& ray);
    void Translate(float tx, float ty, float tz);
    void ApplyTransformation();
};