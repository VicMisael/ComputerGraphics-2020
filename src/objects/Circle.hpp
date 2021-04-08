#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"
class Circle : public BaseObject
{
private:
    float radius;
    Point3f Center;
public:
    Circle(float radius,const Color c);  
    int Intersects(Ray& ray);
    void ApplyTransformation();
    Vector3f getNormal(const Point3f p) override;
    void ApplyCamera(const Matrix4x4 m);
};