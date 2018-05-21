#include "Plane.hpp"
using namespace glm;
using namespace std;

Plane::Plane()
{
	this->distance = 0.f;
	this->normal = vec3(0.f);
	this->roughness = 0.f;
	this->ior = 0.f;
	this->specular = 0.f;
	this->ambient = 0.f;
	this->diffuse = 0.f;
	this->reflection = 0.f;
	this->refraction = 0.f;
	this->pigment = vec3(-1.0f);
	this->filter = 0.f;
	this->id = -1;
}

float Plane::intersect(const ray &r)
{
	float prod = dot(r.direction, normal);
	float val = distance-dot(r.location, normal);


	if(prod == 0)
	{
		return -1;
	}
	else
	{
		return val/prod;

	}
}

void Plane::createPlane(vec3 n, float d)
{
	this->distance = d;
	this->normal = n;
}

void Plane::print()
{

	cout << "- Type: " <<  type << endl;
	cout << "- Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
	cout << "- Distance: " << distance << endl;
	cout << "- Color: {" << pigment.x << " " << pigment.y << " " << pigment.z << "}" << endl;
	cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl << "  - Specular: " << specular << endl << "  - Roughness: " << roughness << endl << "  - IOR: " << ior << endl << "  - Reflection: " << reflection << endl << "  - Refraction: " << refraction << endl;

	cout << endl;
}