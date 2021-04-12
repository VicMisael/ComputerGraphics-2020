#include "Cube.hpp"

Cube::Cube(float height, float width, float depth, Color c)
{
    Point3f p0(0, 0, 0);
    Vector3f right(1, 0, 0);
    Vector3f up(0, 1, 0);
    Vector3f forward(0, 0, 1);
    //Colocando as faces em sentido horario
    face[0] = p0;
    face[1] = p0 + up * height;
    face[2] = p0 + up * height + right * width,
    face[3] = p0 + right * width;

    face2[0] = face[0] + forward * depth;
    face2[1] = face[1] + forward * depth;
    face2[2] = face[2] + forward * depth;
    face2[3] = face[3] + forward * depth;

    this->c = c;
    CalculateTriangles();
}
void Cube::CalculateTriangles()
{
    int i = 0;
    //Interseção na face frontal
    triangles[i++] = Triangle(face[0], face[1], face[2]);
    triangles[i++] = Triangle(face[2], face[3], face[0]);
    //Interseção face traseira
    triangles[i++] = Triangle(face2[0], face2[1], face2[2]);
    triangles[i++] = Triangle(face2[2], face2[3], face2[0]);
    //Interseção na lateral 1
    triangles[i++] = Triangle(face[0], face2[0], face[1]);
    triangles[i++] = Triangle(face2[0], face2[1], face[1]);
    //Interseção da lateral 2
    triangles[i++] = Triangle(face[2], face[3], face2[3]);
    triangles[i++] = Triangle(face2[3], face2[2], face[2]);
    //Topo
    triangles[i++] = Triangle(face[1], face[2], face2[2]);
    triangles[i++] = Triangle(face2[2], face2[1], face[1]);
    //Base
    triangles[i++] = Triangle(face[0], face[3], face2[3]);
    triangles[i] = Triangle(face2[3], face2[0], face[0]);
}

int Cube::Intersects(Ray &ray)
{
    t_min = INFINITY;
    int intersectionCount = 0;
    for (Triangle t : triangles)
    {
        if (t.Intersects(ray))
        {
            if (t.getTmin() < t_min)
            {
                t_min = t.getTmin();
                this->Normal = t.getNormal(ray.getPoint(t_min));
            }
            intersectionCount++;
        }
    }
    return intersectionCount > 0;
}
void Cube::ApplyTransformation()
{
    for (Point3f &p : face)
    {
        p = transFMat * p;
    }

    for (Point3f &p : face2)
    {
        p = transFMat * p;
    }
    CalculateTriangles();
}

Vector3f Cube::getNormal(const Point3f p)
{
    return Normal;
    //Vector3f normal;
    //for (Triangle& t : triangles) {
    //    normal = normal + t.getNormal(p);
    //}
    //normal.normalize();
    //return normal;


    //Vector3f normal;
    //for (Triangle& t : triangles) {
    //    normal = normal+ t.getNormal(p);
    //}
    //normal.normalize();
    //return normal;
}

void Cube::ApplyCamera(const Matrix4x4 mm)
{
    for (Triangle &t : triangles) {
        t.ApplyCamera(mm);
    }
}
