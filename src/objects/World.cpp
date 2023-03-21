#include "World.hpp"
#include <algorithm>
#include <tuple>

static uint8_t r = 203;
static uint8_t g = 224;
static uint8_t b = 233;

Vector3f inline ReflectRay(const Vector3f R, const Vector3f N)
{
	using namespace VectorUtilities;
	return ((N * 2.0f) * dotProduct(N, R) - R);
}

float World::ComputeLighting(const Point3f &p, const Vector3f& n,const Vector3f &V,const float s)
{
	using namespace VectorUtilities;
	float intensity = 0;
	Vector3f lVec;
	float distanceFactor = 1;
	for (Light *l : lights)
	{
			switch (l->lt)
			{
			case LightType::ambient:
				intensity += l->getIntensity();
				continue;
				break;
			case LightType::point:
				lVec = ((l->getPosition()) - p);
				distanceFactor = inverseSquare(glm::length(lVec));
				break;
			case LightType::directional:
				lVec = l->getDirection();
				break;
			default:
				break;
			}
			const float lveclength = glm::length(lVec);
			lVec = glm::normalize(lVec);
			if (renderShadows)
			{
				for ( BaseObject *ob : objects)
				{
					const Ray r = Ray(p, lVec);
					const auto [intersects, t_min,normal] = ob->Intersects(r);
					if (intersects && t_min > 0.1f && t_min <= lveclength)
					{
						return intensity;
					}
				}
			}

			const float n_dot_l = dotProduct(n, lVec);
			const float _intensity = l->getIntensity();
			if (n_dot_l > 0)
			{
				intensity += (_intensity * distanceFactor) * (n_dot_l / (glm::length(n) * glm::length(lVec)));
			}
			if (s >= 0)
			{
				const Vector3f R = ReflectRay(lVec, n);
				const float r_dot_v = dotProduct(R, V);
				if (r_dot_v > 0)
				{
					const float _pow = glm::pow(r_dot_v / (glm::length(R)* glm::length(V)), s);
					intensity += _intensity * _pow;
				}
			}
		
	}
	return intensity;
};
void inline World::init()
{
	Matrix4x4 camTransformation;
	if (camera != NULL)
	{
		camTransformation = (camera->getWorldToCamera());
	}
	bgColor = Color(r, g, b);

	Light *lambient = new Light(Point3f(0, 0, 0), Vector3f(0, 1, 0), 0.1);
	lights.push_back(lambient);

	Light *l2 = new Light(Point3f(0, 7, -3), Point3f(0, 0, 0), 3);
	l2->SetType(LightType::point);
	lights.push_back(l2);

	Light *l3 = new Light(Point3f(3, 1.2, 0), Point3f(0, 0, 0), 1);
	l3->SetType(LightType::point);
	lights.push_back(l3);


	Light* l4 = new Light(Point3f(3, 1.2, 6), Point3f(0, 0, 0), 1);
	l4->SetType(LightType::point);
	lights.push_back(l4);


	Light *l5 = new Light(Point3f(0, -1, 0), Point3f(0, 1, 0), 0.1);
	l5->SetType(LightType::directional);
	lights.push_back(l5);
	
	Plane *p = new Plane(Vector3f(0, 1, 0), Point3f(0, -2, 0), Color(255, 226, 198));
	p->setReflectivness(0.5);
	p->setSpecular(1000);
	objects.push_back(p);

	Plane *p2 = new Plane(Vector3f(0, -1, -1), Point3f(0, 5, 10), WHITE);
	p2->setReflectivness(0.6);
	p2->setSpecular(300);
	objects.push_back(p2);


	/*

	Cube *building = new Cube(1, 1, 1, Color(169, 169, 169));
	building->Scale(2, 4, 1);
	//cubeShear->Sheary(1, 1.5);
	building->RotateY(PI / 4);
	building->Translate(-1, -0.5, 6);
	building->setReflectivness(.7);
	objects.push_back(building);


	Cube* building4 = new Cube(1, 1, 1, Color(169, 169, 169));
	building4->Scale(2, 3, 1);
	building4->RotateY(PI / 4);
	building4->Translate(-1, 0, -1);
	building4->setReflectivness(.1);
	objects.push_back(building4);



	Cube *buildin2 = new Cube(1, 1, 1, Color(169, 169, 169));
	buildin2->Scale(2, 4, 1);
	//cubeShear->Sheary(1, 1.5);
	buildin2->RotateY(PI / 6);
	buildin2->Translate(1.5, -0.5, 6);
	buildin2->setReflectivness(.7);
	objects.push_back(buildin2);

	Cube *buildin3 = new Cube(1, 1, 1, Color(255, 255, 255));
	buildin3->Scale(1, 3, 1);
	buildin3->Shearx(1, 1);
	buildin3->RotateY(PI / 6);
	buildin3->Translate(-2, -0.5, 3);
	buildin3->setReflectivness(.07);
	objects.push_back(buildin3);
	*/
	//Objetos extras
	Circle *cBola = new Circle(1, WHITE);
	cBola->setSpecular(1000);
	cBola->Translate(-3, -1, 9);
	cBola->setReflectivness(1);
	objects.push_back(cBola);
	
	Circle* cBola2 = new Circle(1, Color(255,255,0));
	cBola2->Translate(3, 9, 3);
	cBola2->setReflectivness(0.5);
	objects.push_back(cBola2);

	Circle* cBola3 = new Circle(1, Color(255, 255, 0));
	cBola3->Translate(0, 7, 3);
	cBola3->setReflectivness(0.5);
	objects.push_back(cBola3);


	Circle* cBola4 = new Circle(1, Color(255, 255, 0));
	cBola4->Translate(1, 10, 2);
	cBola4->setReflectivness(0.5);
	objects.push_back(cBola4);

	Light* lt = new Light(Point3f(0, 7, 0),Vector3f(1,-1,1),1);
	lt->SetType(LightType::point);
	lights.push_back(lt);

	//Snowman
	//Diferen�a do raio do primeiro pro 0
	float radiusDiff = -0.6;
	Circle *c = new Circle(0.6, Color(255, 255, 255));
	c->setSpecular(1000);
	//c->setReflectivness(1);
	c->Translate(3, radiusDiff, 5);
	c->setReflectivness(1);
	objects.push_back(c);
	c = new Circle(0.4, Color(255, 255, 255));
	c->setSpecular(1000);
	c->Translate(3, radiusDiff + 0.9, 5);
	c->setReflectivness(1);
	objects.push_back(c);
	c = new Circle(0.25, Color(255, 255, 255));
	c->setSpecular(1000);
	c->Translate(3, radiusDiff + 1.4, 5);
	c->setReflectivness(1);
	objects.push_back(c);
	Cone *nose = new Cone(Vector3f(0, 0, 1), 0.5, 0.1, Color(255, 165, 0));
	nose->RotateY(PI / 2);
	nose->Translate(3, radiusDiff + 1.4, 5);
	objects.push_back(nose);
	Cone *snowManHat = new Cone(Vector3f(0, 1, 0), 0.6, 0.30, Color(18, 10, 143));
	snowManHat->setReflectivness(0.5);
	snowManHat->Translate(3, radiusDiff + 1.6, 5);
	snowManHat->setSpecular(900);
	objects.push_back(snowManHat);

	//Cilindro
	Cylinder *cyl = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(100, 120, 120));
	cyl->setSpecular(900);
	cyl->setReflectivness(0.8);
	cyl->Translate(1.4, 0.5, 2);
	objects.push_back(cyl);

	Cylinder *cyl2 = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(0, 120, 120));
	cyl2->setSpecular(900);
	//cyl2->setReflectivness(0.8);
	cyl2->Translate(1.8, 0.5, 2.3);
	objects.push_back(cyl2);


	Cylinder* cylaa = new Cylinder(Vector3f(0, 1, 0), 3, 2, Color(0, 120, 120));
	cylaa->Translate(5, 3, 8);
	cylaa->setReflectivness(0.8);
	objects.push_back(cylaa);

	Cone *cone2 = new Cone(Vector3f(0, 1, 0), 0.7, 0.8, Color(173, 216, 230));
	cone2->setSpecular(1000);
	cone2->LoadIdentity();
	//cone->RotateX(PI / 6);
	cone2->Translate(1.6, 0.5, 2);
	//cone2->setReflectivness(1);
	//cone->ApplyTransformation();
	objects.push_back(cone2);
	//Cubo
	Cone *cone = new Cone(Vector3f(0, 1, 0), 0.7, 0.8, Color(204, 169, 221));
	cone->setSpecular(1000);
	cone->LoadIdentity();
	//cone->RotateX(PI / 6);
	cone->setReflectivness(0.99);
	cone->Translate(-1, 0.5, 2);
	//cone->ApplyTransformation();
	objects.push_back(cone);

	Cube *cube = new Cube(1.5, 0.5, 0.5, Color(249, 234, 195));
	cube->setSpecular(10000);
	cube->setReflectivness(0.4);
	cube->RotateY(-PI / 4);
	cube->Translate(-1.5, -1, 2);
	objects.push_back(cube);

	Cube *cube2 = new Cube(1.5, 0.5, 0.5, Color(249, 234, 195));
	cube2->setSpecular(10000);
	cube2->setReflectivness(0.1);
	cube2->RotateY(PI / 4);
	cube2->Translate(-0.9, -1, 2);
	objects.push_back(cube2);



	for (Light *l : lights)
	{
		l->ApplyCamera(camTransformation);
	}
	for (BaseObject *ob : objects)
	{
		ob->ApplyTransformation();
		ob->ApplyCamera(camTransformation);
	}
}

//Receives the intersection point,the normal vector at the point of intersection, the Vector pointing to the camera

World::World()
{
	//camera = Camera(Point3f(5, 5, 5), Point3f(0, 0, 0), Point3f(0, 1, 0));
	camera = NULL;
	init();
}

World::World(Camera c)
{
	camera = &c;
	init();
}

void World::SetShadowsOn(bool shadows)
{
	this->renderShadows = shadows;
}

Color World::computeColor(Ray &ray, float vz, int rd)
{
	Color retColor = bgColor;
	BaseObject *ClosestIntersected = nullptr;
	float minimalT = INFINITY;
	bool isReflective = false;
	float reflectT;
	Vector3f normalClosest;

	for(BaseObject *ob:objects)
	{
		const auto [intersects, t,normal] = ob->Intersects(ray);
		if (intersects)
		{
			if (t > vz && t < minimalT)
			{
					minimalT = t;
					Point3f point = ray.getPoint(t);

					Vector3f invdir = ray.D * -1.0f;
					retColor = ob->getColor() * ComputeLighting(point, normal, invdir, ob->getSpecular());
					isReflective = (ob->getReflectivness() > 0);
					if (isReflective)
					{
						ClosestIntersected = ob;
						reflectT = t;
						normalClosest.x = normal.x;
						normalClosest.y = normal.y;
						normalClosest.z = normal.z;
					}
			}
		}
	}
	if (isReflective && rd > 0 )
	{
		const float rindex = ClosestIntersected->getReflectivness();
		//const Vector3f Normal = ClosestIntersected->getNormal(ray.getPoint(reflectT));
		const Vector3f dir = ray.D * -1.0f;
		Ray reflected_ray(ray.getPoint(minimalT), ReflectRay(dir, normalClosest));
		retColor = retColor * (1 - rindex) + computeColor(reflected_ray, vz, rd - 1) * rindex;
	}

	return retColor;
}
