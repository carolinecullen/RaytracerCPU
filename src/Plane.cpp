#include "Plane.hpp"
using namespace glm;
using namespace std;

Plane::Plane()
{
	this->distance = 0.f;
	this->normal = vec3(0.f);
}

float Plane::intersect(const ray &r)
{
	return 1.0f;
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
	cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl;

	cout << endl;
}