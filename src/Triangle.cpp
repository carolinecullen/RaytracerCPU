#include "Triangle.hpp"
#include <math.h>
using namespace glm;
using namespace std;

Triangle::Triangle()
{
	this->A = vec3(0.f);
	this->B = vec3(0.f);
	this->C = vec3(0.f);
	this->alpha = 0.f;
	this->beta = 0.f;
	this->gamma = 0.f;
	this->roughness = 0.f;
	this->specular = 0.f;
	this->ambient = 0.f;
	this->diffuse = 0.f;
	this->pigment = vec3(0.f);
	this->normal = vec3(0.f);
	this->ior = 0.f;
}

float Triangle::intersect(const ray &r)
{
	return 1.f;
}

void Triangle::calculateValues()
{

}

void Triangle::calcNormal(vec3 pt)
{

}

void Triangle::print()
{
	cout << "- Type: " <<  type << endl;
	cout << "- Coordinates: \n  - A = {" << A.x << " " << A.y << " " << A.z << "}" << endl;
	cout << "  - B = {" << B.x << " " << B.y << " " << B.z << "}" << endl;
	cout << "  - C = {" << C.x << " " << C.y << " " << C.z << "}" << endl;
	cout << "- Color: {" << pigment.x << " " << pigment.y << " " << pigment.z << "}" << endl;
	cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl << "  - Specular: " << specular << endl << "  - Roughness: " << roughness << endl << "  - IOR: " << ior << endl;

	cout << endl;
}