#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"
class Circle : public BaseObject
{
private:
    double radius;
    Point3f Center;
public:
    Circle(float radius,Color c);
  
    int Intersects(Ray& ray);

    void ApplyTransformation();
};