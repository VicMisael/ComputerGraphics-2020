#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"

class Cylinder : public BaseObject
{
    private:
    Point3f Center; // center of cylinder 
    Vector3f axis; // cylinder axis 
    float height;
    float radius;

    public:
    Cylinder(Vector3f axis, float height, float radius);
    int Intersects(Ray& ray);
    void Translate(float tx, float ty, float tz);
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    void ApplyTransformation();
};