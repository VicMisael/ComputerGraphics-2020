#include "Triangle.hpp"


Triangle::Triangle(Point3f Vertexes[3], Color c)
{
	for (int i = 0; i < 3; i++)
	{
		Vertex[i] = Vertexes[i];
	}
	this->c = c;
	CalculateNormal();
}

Triangle::Triangle(Point3f Vertex1, Point3f Vertex2, Point3f Vertex3, Color c)
{
	Vertex[0] = Vertex1;
	Vertex[1] = Vertex2;
	Vertex[2] = Vertex3;
	this->c = c;
	CalculateNormal();
}

void Triangle::CalculateNormal()
{
	using namespace VectorUtilities;
	Vector3f v = Vertex[1] - Vertex[0];
	Vector3f w = Vertex[2] - Vertex[0];
	Normal = crossProduct(v, w);
	//Normal.normalize();
}

std::tuple<int, float, Vector3f> Triangle::Intersects(const Ray& ray)
{
	static const float epsilon = 0.0000001;
	static const float epsilon2 = 0.000001;

	float t_min = INFINITY;
	using namespace VectorUtilities;
	Vector3f e1 = Vertex[1] - Vertex[0];
	Vector3f e2 = Vertex[2] - Vertex[0];
	Vector3f q = crossProduct(ray.D, e2);
	float a = dotProduct(e1, q);
	if (a <= epsilon)
	{
		return NO_INTERSECT;
	}
	Vector3f s = ray.O - Vertex[0];
	Vector3f r = crossProduct(s, e1);
	float weight[3];
	weight[1] = dotProduct(s, q) / a;
	weight[2] = dotProduct(ray.D, r) / a;
	weight[0] = 1.0f - (weight[1] + weight[2]);

	if ((weight[0] < -epsilon2) || (weight[1] < -epsilon2) || (weight[2] < -epsilon2))
	{
		return NO_INTERSECT;
	}

	const float dist = dotProduct(e2, r) / a;
	if (dist <= epsilon)
	{
		return NO_INTERSECT;
	}

	return {1, dist, this->Normal};
}

void Triangle::ApplyTransformation()
{
	//Vector4f e1 =Vector4f(Vertex[1] - Vertex[0],0);
	//Vector4f e2 = Vector4f(Vertex[2] - Vertex[0],0);
	//e1=transFMat*e1;
	//e2 = transFMat * e2;
	//Vector4f mainVertex=Vector4f(Vertex[0], 1);
	//mainVertex=transFMat*mainVertex;
	//Vertex[0]=mainVertex.toVector3f();
	//Vector3f e13f=e1.toVector3f();
	//Vector3f e23f = e2.toVector3f();
	//Vertex[1] = Vertex[0] + e13f;
	//Vertex[2] = Vertex[0] + e23f;
	for (Point3f& p : Vertex)
	{
		p = transFMat * p;
	}
	CalculateNormal();
}

Vector3f Triangle::getNormal(const Point3f p)
{
	//    using namespace VectorUtilities;
	//    Vector3f v=  Vertex[1]- Vertex[0] ;
	//    Vector3f w= Vertex[2]- Vertex[0]  ;
	//    Vector3f N=crossProduct(v, w);
	//    N.normalize();
	return this->Normal;
}

void Triangle::ApplyCamera(const Matrix4x4 m)
{
	for (Point3f& v : Vertex)
	{
		v = m * v;
	}
	CalculateNormal();
}
