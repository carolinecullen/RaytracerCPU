#include "Sphere.hpp"
#include <math.h>
using namespace glm;
using namespace std;

Sphere::Sphere()
{
	this->radius = 0.f;
	this->center = vec3(0.f);
	this->translate = vec3(0.f);
}

float Sphere::intersect(const ray &r)
{
	vec3 distance = center - r.location;

	float A = dot(r.location, r.location);
	float B = dot(r.location + r.location, distance);
	float C = dot(distance, distance) - (radius * radius);

	float discriminant = (pow(B, 2.0))-(4*(A*C));
	discriminant = sqrt(discriminant);

	float val1 = (-B + discriminant)/(2*A);
	float val2 = (-B - discriminant)/(2*A);

	// cout << "val1: " << val1 << endl;
	// cout << "val2: " << val2 << endl;

	if (val2>0 && val1>0) 
	{
		if(val2>val1)
		{
			return val2;
		}
		else
		{
			return val1;
		}
	}
	else if (val2>0) 
	{
		return val2;
	}
	else if (val1>0) 
	{
		return val1;
	}
	else if(val1 < 0 || val2 < 0)
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