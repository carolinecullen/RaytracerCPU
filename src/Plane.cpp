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
	this->IM = glm::mat4(1.f);
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
	this->IM = glm::mat4(1.f);
	this->M = glm::mat4(1.f);
}

void Plane::print()
{

	cout << "- Type: " <<  type << endl;
	cout << "- Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
	cout << "- Distance: " << distance << endl;
	cout << "- Color: {" << pigment.x << " " << pigment.y << " " << pigment.z << "}" << endl;
	cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl << "  - Specular: " << specular << endl << "  - Roughness: " << roughness << endl << "  - IOR: " << ior << endl << "  - Reflection: " << reflection << endl << "  - Refraction: " << refraction << endl;
	cout << " - Model Transform: " << endl;
    cout << "  " << IM[0][0] << " " << IM[1][0] << " " << IM[2][0] << " " << IM[3][0] << endl;
    cout << "  " << IM[0][1] << " " << IM[1][1] << " " << IM[2][1] << " " << IM[3][1] << endl;
    cout << "  " << IM[0][2] << " " << IM[1][2] << " " << IM[2][2] << " " << IM[3][2] << endl;
	cout << "  " << IM[0][3] << " " << IM[1][3] << " " << IM[2][3] << " " << IM[3][3] << endl;
	cout << endl;
}