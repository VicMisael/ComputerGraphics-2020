#ifndef _CONE_
#define _CONE_
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"

// Definindo o código do cone
class Cone : public BaseObject
{
    private:
        Point3f center;
        Point3f vertice;
        Vector3f axis;
        float height;
        float radius;
        float cosTheta;
        //Point3f scale_aux;

    public:
        Cone( Vector3f axis, float height, float radius,const Color c);
        int Intersects(Ray& ray);
        void ApplyTransformation();
        Vector3f getNormal(const Point3f p) override;
};

#endif