#include "World.hpp"
#include <algorithm>
#include <tuple>

static uint8_t r = 203;
static uint8_t g = 224;
static uint8_t b = 233;

Vector3f  ReflectRay(const Vector3f in, const Vector3f normal)
{
	using namespace VectorUtilities;
	return in - 2 * dotProduct(in, normal) * normal;
}

bool World::inShadow(const Point3f p,const Vector3f Ldir,const float lvecLength) const
{
	for (BaseObject* ob : objects)
	{
		const auto r = Ray(p, Ldir);
		const auto [intersects, t_min, normal] = ob->Intersects(r);
		if (intersects && t_min > 0.01f && t_min <= lvecLength)
		{
			return true;
		}
	}
	return false;
}

float World::ComputeLighting(const Point3f& p, const Vector3f& n, const Vector3f& V, const float s)
{
	using namespace VectorUtilities;
	float intensity = 0;
	float distanceFactor = 1.0f;
	Vector3f lVec;
	for (const Light* l : lights)
	{

		switch (l->lt)
		{
		case LightType::ambient:
			intensity += l->getIntensity();
			continue;
		case LightType::point:
			lVec = ((l->getPosition()) - p);
			distanceFactor = inverseSquare(length(lVec));
			break;
		case LightType::directional:
			lVec = l->getDirection();
			//distanceFactor = inverseSquare(length(lVec));
			break;
		default:
			break;
		}
		const float lveclength = length(lVec);
		lVec = normalize(lVec);

		if ( inShadow(p, lVec, lveclength)) continue;

		const float n_dot_l = dotProduct(n, lVec);
		const float _intensity = l->getIntensity();
		if (n_dot_l > 0)
		{
			intensity += (_intensity * distanceFactor) * (n_dot_l / (length(n) * length(lVec)));
		}
		if (s > 0)
		{
			const Vector3f R = ReflectRay(lVec, n);
			const float r_dot_v = dotProduct(R, V);
			if (r_dot_v > 0)
			{
				const float _pow = std::pow(r_dot_v / (length(R) * length(V)), s);
				intensity += _intensity * _pow;
			}
		}

	}
	return intensity;
};

void inline World::init()
{
	Matrix4x4 camTransformation;
	if (camera != nullptr)
	{
		camTransformation = (camera->getWorldToCamera());
	}
	bgColor = Color(r, g, b);



	auto l2 = new Light(Point3f(-60, 60, -100), Point3f(0, 0, 0), 0.5);
	l2->SetType(LightType::point);
	lights.push_back(l2);

	auto l3 = new Light(Point3f(3, 12, -4), Point3f(0, 0, 0),2);
	l3->SetType(LightType::point);
	lights.push_back(l3);

	auto l4 = new Light(Point3f(3, 12, 15), Point3f(0, -1, 0), 1);
	l4->SetType(LightType::directional);
	lights.push_back(l4);

	auto lambient = new Light(Point3f(0, 0, 0), Vector3f(0, 1, 0), 0.1);
	lights.push_back(lambient);



	auto p = new Plane(Vector3f(0, 1, 0), Point3f(0, -2, 0), Color(255, 226, 198));
	p->setReflectivness(0.8);
	p->setSpecular(1000);
	objects.push_back(p);

	auto p2 = new Plane(Vector3f(0, -1, -1), Point3f(0, 5, 10), WHITE);
	p2->setReflectivness(0.7);
	p2->setSpecular(300);
	objects.push_back(p2);

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
	building4->setReflectivness(1);
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
	buildin3->setReflectivness(.7);
	objects.push_back(buildin3);
	
	//Objetos extras
	auto cBola = new Circle(1, WHITE);
	cBola->setSpecular(1000);
	cBola->Translate(-3, -1, -19);
	cBola->setReflectivness(1);
	objects.push_back(cBola);

	auto cBola2 = new Circle(1, Color(255, 255, 0));
	cBola2->Translate(3, 9, 0);
	cBola2->setReflectivness(0.9);
	objects.push_back(cBola2);

	auto cBola3 = new Circle(1, Color(255, 255, 0));
	cBola3->Translate(0, 5, 13);
	cBola3->setReflectivness(0.5);
	objects.push_back(cBola3);


	auto cBola4 = new Circle(1, Color(255, 255, 0));
	cBola4->Translate(1, 10, 2);
	cBola4->setReflectivness(0.5);
	objects.push_back(cBola4);

	auto cBola123 = new Circle(1, Color(255, 255, 0));
	cBola4->Translate(0, 5, -4);
	cBola4->setReflectivness(0.5);
	objects.push_back(cBola123);



	//Snowman
	//Diferen�a do raio do primeiro pro 0
	float radiusDiff = -0.6;
	auto c = new Circle(0.6, Color(255, 255, 255));
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
	auto nose = new Cone(Vector3f(0, 0, 1), 0.5, 0.1, Color(255, 165, 0));
	nose->RotateY(PI / 2);
	nose->Translate(3, radiusDiff + 1.4, 5);
	objects.push_back(nose);
	auto snowManHat = new Cone(Vector3f(0, 1, 0), 0.6, 0.30, Color(18, 10, 143));
	snowManHat->setReflectivness(0.5);
	snowManHat->Translate(3, radiusDiff + 1.6, 5);
	snowManHat->setSpecular(900);
	objects.push_back(snowManHat);

	//Cilindro
	auto cyl = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(100, 120, 120));
	cyl->setSpecular(900);
	cyl->setReflectivness(0.8);
	cyl->Translate(1.4, 0.5, 2);
	objects.push_back(cyl);

	auto cyl2 = new Cylinder(Vector3f(0, 1, 0), 1.5, 0.3, Color(0, 120, 120));
	cyl2->setSpecular(900);
	//cyl2->setReflectivness(0.8);
	cyl2->Translate(1.8, 0.5, 2.3);
	objects.push_back(cyl2);


	auto cylaa = new Cylinder(Vector3f(0, 1, 0), 3, 2, Color(0, 120, 120));
	cylaa->Translate(5, 3, 8);
	cylaa->setReflectivness(0.8);
	objects.push_back(cylaa);

	auto cone2 = new Cone(Vector3f(0, 1, 0), 0.7, 0.8, Color(173, 216, 230));
	cone2->setSpecular(1000);
	cone2->LoadIdentity();
	//cone->RotateX(PI / 6);
	cone2->Translate(1.6, 0.5, 2);
	//cone2->setReflectivness(1);
	//cone->ApplyTransformation();
	objects.push_back(cone2);
	//Cubo
	auto cone = new Cone(Vector3f(0, 1, 0), 0.7, 0.8, Color(204, 169, 221));
	cone->setSpecular(1000);
	cone->LoadIdentity();
	//cone->RotateX(PI / 6);
	cone->setReflectivness(0.99);
	cone->Translate(-1, 0.5, 2);
	//cone->ApplyTransformation();
	objects.push_back(cone);

	auto cube = new Cube(1.5, 0.5, 0.5, Color(249, 234, 195));
	cube->setSpecular(10000);
	cube->setReflectivness(0.4);
	cube->RotateY(-PI / 4);
	cube->Translate(-1.5, -1, 2);
	objects.push_back(cube);

	auto cube2 = new Cube(1.5, 0.5, 0.5, Color(249, 234, 195));
	cube2->setSpecular(10000);
	cube2->setReflectivness(0.1);
	cube2->RotateY(PI / 4);
	cube2->Translate(-0.9, -1, 2);
	objects.push_back(cube2);


	for (Light* l : lights)
	{
		l->ApplyCamera(camTransformation);
	}
	for (BaseObject* ob : objects)
	{
		ob->ApplyTransformation();
		ob->ApplyCamera(camTransformation);
	}
}

//Receives the intersection point,the normal vector at the point of intersection, the Vector pointing to the camera

World::World()
{
	//camera = Camera(Point3f(5, 5, 5), Point3f(0, 0, 0), Point3f(0, 1, 0));
	camera = nullptr;
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

Color World::computeColor(Ray& ray, const float vz,const unsigned int rd)
{
	struct 
	{
		float specular;
		float reflectiveness;
		float t= INFINITY;
		Point3f at;
		Vector3f normal;
		Color color;
		bool hits=false;
	} closest;


	for (BaseObject* ob : objects)
	{
		const auto [intersects, t,normal] = ob->Intersects(ray);
		if (intersects)
		{
			if ( t > vz && t < closest.t)
			{
				closest.hits = true;
				closest.t = t;
				closest.at = ray.getPoint(t);
				closest.normal = normalize(normal);
				closest.color = ob->getColor();
				closest.specular = ob->getSpecular();
				closest.reflectiveness = ob->getReflectivness();
			}
		}
	}
	if(closest.hits){
		if (closest.reflectiveness > 0 && rd > 0)
		{
			const float rindex = closest.reflectiveness;
			// VectorUtilities::random(0, 1.0) * VectorUtilities::random_in_unit_sphere();
			Ray reflected_ray(closest.at, ReflectRay(normalize(ray.D), closest.normal)+ VectorUtilities::random(0, 1.0) * VectorUtilities::random_in_unit_sphere());
			return  (closest.color * ComputeLighting(closest.at, closest.normal, ray.D*-1.0f, closest.specular))
			* (1 - rindex) + 
				computeColor(reflected_ray, vz, rd - 1) * rindex;
		}
		return (closest.color * ComputeLighting(closest.at, closest.normal, ray.D*-1.0f, closest.specular));
	}


	return bgColor;
}
