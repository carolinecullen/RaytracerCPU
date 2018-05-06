#include "Triangle.hpp"
#include <math.h>
using namespace glm;
using namespace std;

Triangle::Triangle()
{
	this->A = vec3(0.f);
	this->B = vec3(0.f);
	this->C = vec3(0.f);
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
	float a = (A.x - B.x);
	float b = (A.y - B.y);
	float c = (A.z - B.z);
	float d = (A.x - C.x);
	float e = (A.y - C.y);
	float f = (A.z - C.z);
	float g = (r.direction.x);
	float h = (r.direction.y);
	float i = (r.direction.z);
	float j = (A.x - r.location.x);
	float k = (A.y - r.location.y);
	float l = (A.z - r.location.z);

	mat3 Amat = mat3 (a, d, g,
					  b, e, h,
					  c, f, i);
	float detAmat = determinant(Amat);

	mat3 Tmat = mat3 (a, d, j,
					  b, e, k,
					  c, f, l);
	float detTmat = determinant(Tmat);
	float t = (detTmat)/(detAmat);
	if(t < 0)
	{
		return -1.f;
	}


	mat3 Gmat = mat3 (a, j, g,
					  b, k, h,
					  c, l, i);
	float detGmat = determinant(Gmat);
	float gamma = detGmat/detAmat;
    if((gamma < 0) || (gamma > 1))
    {
    	return -1.f;
    }

    mat3 Bmat = mat3 (j, d, g,
					  k, e, h,
					  l, f, i);
	float detBmat = determinant(Bmat);
	float beta = detBmat/detAmat;
    if((beta < 0) || (beta > (1 - gamma)))
    {
    	return -1.f;
    }

    return t;
}

void Triangle::calcNormal(vec3 pt)
{
	vec3 rV = B - A;
    vec3 lV = C - A;

	this->normal = normalize(vec3(((rV.y*lV.z)-(rV.z*lV.y)), ((rV.z*lV.x)-(rV.x*lV.z)), ((rV.x*lV.y)-(rV.y*lV.x))));
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