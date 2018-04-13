#include "Sphere.hpp"
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
	return 1.0f;
}

void Sphere::createSphere(vec3 c, float r, vec3 t)
{
	this->type = "Sphere";
	this->radius = r;
	this->center = c;
	this->translate = t;
}


void Sphere::printSphere()
{
	cout << "- Type: " <<  type << endl;
	cout << "- Center: {" << center.x << " " << center.y << " " << center.z << "}" << endl;
	cout << "- Radius: " << radius << endl;
	cout << "- Color: {" << pigment.x << " " << pigment.y << " " << pigment.z << "}" << endl;
	cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl;

	cout << endl << "---" << endl << endl;
}