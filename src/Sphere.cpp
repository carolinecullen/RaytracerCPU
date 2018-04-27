#include "Sphere.hpp"
#include <math.h>
using namespace glm;
using namespace std;

Sphere::Sphere()
{
	this->radius = 0.f;
	this->center = vec3(0.f);
	this->translate = vec3(0.f);
	this->roughness = 0.f;
	this->specular = 0.f;
	this->ambient = 0.f;
	this->diffuse = 0.f;
}

float Sphere::intersect(const ray &r)
{
	vec3 distance = r.location - center;

	float A = dot(r.direction, r.direction);
	float B = 2*dot(distance, r.direction);
	float C = dot(distance, distance) - (pow(radius, 2.0));
	float discriminant = (pow(B, 2))-(4*(A*C));
	discriminant = sqrt(discriminant);

	if (discriminant > 0) 
	{
		float val1 = (-B + discriminant)/(2*A);
		float val2 = (-B - discriminant)/(2*A);
		if(val2>val1)
		{
			return val1;
		}
		else
		{
			return val2;
		}
	}
	else if (discriminant==0) 
	{
		float val1 = (-B + discriminant)/(2*A);
		return val1;
	}
	else if(discriminant < 0)
	{
		return -1;
	}
	else
	{
		return -1;
	}
	
}

void Sphere::createSphere(vec3 c, float r, vec3 t)
{
	this->type = "Sphere";
	this->radius = r;
	this->center = c;
	this->translate = t;
}


void Sphere::print()
{
	cout << "- Type: " <<  type << endl;
	cout << "- Center: {" << center.x << " " << center.y << " " << center.z << "}" << endl;
	cout << "- Radius: " << radius << endl;
	cout << "- Color: {" << pigment.x << " " << pigment.y << " " << pigment.z << "}" << endl;
	cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl;

	cout << endl;
}