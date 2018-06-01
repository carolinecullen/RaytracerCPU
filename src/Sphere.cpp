#include "Sphere.hpp"
#include <math.h>
#include <vector>
using namespace glm;
using namespace std;

Sphere::Sphere()
{
	this->radius = 0.f;
	this->center = vec3(0.f);
	this->pigment = vec3(-1.0f);
	this->filter = 0.f;
	this->roughness = 0.f;
	this->specular = 0.f;
	this->ambient = 0.f;
	this->diffuse = 0.f;
	this->ior = 0.f;
	this->id = -1;
	this->refraction = 0.f;
	this->reflection = 0.f;
	this->normal = vec3(0.f);
	this->IM = glm::mat4(1.f);
}

float Sphere::intersect(const ray &r)
{
	vec3 distance = r.location - center;

	float A = dot(r.direction, r.direction);
	float B = 2*dot(distance, r.direction);
	float C = dot(distance, distance) - (pow(radius, 2.0));
	float discriminant = (pow(B, 2))-(4*(A*C));

	if (discriminant > 0) 
	{
		discriminant = sqrt(discriminant);
		float val2 = (-B + discriminant)/(2*A);
		float val1 = (-B - discriminant)/(2*A);

		if(val1 < 0)
		{
			return val2;
		}
		else
		{
			return val1;
		}	

		return val2;
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

void Sphere::calcNormal(glm::vec3 v)
{
	this->normal = normalize(v - this->center);
}

vec3 Sphere::getCenter() 
{
	return center;
}

BBH* Sphere::makeBoundingBox() 
{
	vec3 min = this->center;
	vec3 max = this->center;
	for (int i = 0; i < 3; i++) 
	{
		min[i] -= radius;
		max[i] += radius;
	}
	BBH* box = new BBH(min, max);

	if (box->init()) 
    {
        std::vector<vec3> corners;
	    corners.push_back(vec3(box->min.x, box->min.y, box->min.z));
	    corners.push_back(vec3(box->min.x, box->min.y, box->max.z));
	    corners.push_back(vec3(box->min.x, box->max.y, box->min.z));
	    corners.push_back(vec3(box->min.x, box->max.y, box->max.z));
	    corners.push_back(vec3(box->max.x, box->min.y, box->min.z));
	    corners.push_back(vec3(box->max.x, box->min.y, box->max.z));
	    corners.push_back(vec3(box->max.x, box->max.y, box->min.z));
	    corners.push_back(vec3(box->max.x, box->max.y, box->max.z));

	    box->min = vec3(-numeric_limits<float>::max());
	    box->max = vec3( numeric_limits<float>::max());

	    for (int i = 0; i < 8; i++) 
	    {
	        corners[i] = vec3(this->M * vec4(corners[i], 1.f));
	        box->AddPoint(corners[i]);
	    }

	    box->updateBox(box->min, box->max);
    }

	return box;
}


void Sphere::print()
{
	cout << "- Type: " <<  type << endl;
	cout << "- Center: {" << center.x << " " << center.y << " " << center.z << "}" << endl;
	cout << "- Radius: " << radius << endl;
	cout << "- Color: {" << pigment.x << " " << pigment.y << " " << pigment.z << "}" << endl;
	cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl << "  - Specular: " << specular << endl << "  - Roughness: " << roughness << endl << "  - IOR: " << ior << endl << "  - Reflection: " << reflection << endl << "  - Refraction: " << refraction << endl;
	cout << " - Model Transform: " << endl;
    cout << "  " << IM[0][0] << " " << IM[1][0] << " " << IM[2][0] << " " << IM[3][0] << endl;
    cout << "  " << IM[0][1] << " " << IM[1][1] << " " << IM[2][1] << " " << IM[3][1] << endl;
    cout << "  " << IM[0][2] << " " << IM[1][2] << " " << IM[2][2] << " " << IM[3][2] << endl;
	cout << "  " << IM[0][3] << " " << IM[1][3] << " " << IM[2][3] << " " << IM[3][3] << endl;
	cout << endl;
}