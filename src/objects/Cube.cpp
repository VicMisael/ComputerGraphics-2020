#include "Cube.hpp"
#include <algorithm>


Cube::Cube(float height, float width, float depth, Color c)
{
	Point3f p0(0, 0, 0);
	Vector3f right(1, 0, 0);
	Vector3f up(0, 1, 0);
	Vector3f forward(0, 0, 1);
	//Colocando as faces em sentido horario
	face[0] = p0;
	face[1] = p0 + right * width;
	face[2] = p0 + up * height + right * width,
		face[3] = p0 + up * height;



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
	triangles[i++] = Triangle(face[2], face[1], face[0]);
	triangles[i++] = Triangle(face[0], face[3], face[2]);
	//Interseção face traseira
	triangles[i++] = Triangle(face2[0], face2[1], face2[2]);
	triangles[i++] = Triangle(face2[2], face2[3], face2[0]);
	//topo
	triangles[i++] = Triangle(face[2], face[3], face2[3]);
	triangles[i++] = Triangle(face2[3], face2[2], face[2]);
	//Base
	triangles[i++] = Triangle(face[0], face[1], face2[0]);
	triangles[i++] = Triangle(face2[1], face2[0], face[1]);
	//Interseção na lateral 2
	triangles[i++] = Triangle(face2[0], face[3], face[0]);
	triangles[i++] = Triangle(face[3], face2[0], face2[3]);
	//Interseção na Lateral 1
	triangles[i++] = Triangle(face[1], face[2], face2[1]);
	triangles[i] = Triangle(face[2], face2[2], face2[1]);

}


std::tuple<int, float, Vector3f> Cube::Intersects(const Ray& ray)
{	
	if (this->aabb.intersects(ray)) {
		float t_min = INFINITY;
		using namespace std;
		using namespace VectorUtilities;
		int intersectionCount = 0;
		for (Triangle t : triangles)
		{
				const auto [intersects_t,t_tmin,normal]=t.Intersects(ray);
				if (intersects_t && VectorUtilities::dotProduct(ray.D,normal)<0)
				{
					if (t_tmin < t_min)
					{
						t_min = t_tmin;
						this->Normal = normal;
					}
					intersectionCount++;
				}
		}
		return { intersectionCount > 0 ,t_min,this->Normal};
	}
	return NO_INTERSECT;
}


void Cube::ApplyTransformation()
{
	for (Point3f& p : face)
	{
		p = transFMat * p;
	}

	for (Point3f& p : face2)
	{
		p = transFMat * p;
	}
	CalculateTriangles();
}

Vector3f Cube::getNormal(const Point3f p)
{
	Normal.normalize();
	return Normal;
}

void Cube::ApplyCamera(const Matrix4x4 mm)
{
	for (Triangle& t : triangles) {
		t.ApplyCamera(mm);
	}
	computeAABB();
}

void Cube::computeAABB() {
	float xmin = HUGE_VALF;
	float ymin = HUGE_VALF;
	float zmin = HUGE_VALF;
	float xmax = -1 * HUGE_VALF;
	float ymax = -1 * HUGE_VALF;
	float zmax = -1 * HUGE_VALF;
	for (Triangle t : triangles) {
		for (Vector3f vertex : t.Vertex) {
			xmax = vertex.x > xmax ? vertex.x : xmax;
			ymax = vertex.y > ymax ? vertex.y : ymax;
			zmax = vertex.z > zmax ? vertex.z : zmax;
			xmin = vertex.x < xmin ? vertex.x : xmin;
			ymin = vertex.y < ymin ? vertex.y : ymin;
			zmin = vertex.z < zmin ? vertex.z : zmin;
		}
	}
	this->aabb = AABB(Vector3f(xmin, ymin, zmin), Vector3f(xmax, ymax, zmax));
}
