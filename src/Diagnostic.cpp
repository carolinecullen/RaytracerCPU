#include "Diagnostic.hpp"
#include "Tracer.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include <math.h>
using namespace glm;
using namespace std;

Diagnostic::Diagnostic()
{
	this->scene = NULL;
	this->width = 0;
	this->height = 0;
}

Diagnostic::Diagnostic(Scene * s, int w, int h)
{
	this->scene = s;
	this->width = w;
	this->height = h;
}

void Diagnostic::sceneInfo()
{
	scene->cam->printCamera();
	cout << scene->lights.size() << " light(s)" << endl << endl;
	int i = 0;
	for(auto l: scene->lights)
	{
		cout << "Light[" << i << "]:" << endl;
		l->printLight();
		i++;
	}

	cout << scene->sceneObjects.size() << " object(s)" << endl << endl;
	i = 0;
	for(auto so: scene->sceneObjects)
	{
		cout << "Object[" << i << "]:" << endl;
		so->print();
		i++;
	}
}

void Diagnostic::pixelRay(int x, int y)
{

	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	
	vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
	vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
	ray *r = new ray(scene->cam->location, dir);

	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << r->location.x << " " << r->location.y << " " << r->location.z << "} -> {";
	cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;

}

void Diagnostic::printrays(int x, int y)
{
	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	cout << "Pixel: [" << x << ", " << y << "] Color: (";
	vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
	vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
	ray *r = new ray(scene->cam->location, dir);

	Object *hit = NULL;
	float retVal = numeric_limits<float>::max();
	float hldVal = -1;
	for(auto so: scene->sceneObjects)
	{
		hldVal = so->intersect(*r);

		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				retVal = hldVal;
				hit = so;
			}

		}
	}


	cout << hit->pigment.x << ", " << hit->pigment.y << ", " << hit->pigment.z << ")" << endl;
	cout << "----" << endl;

	printraysHelper(r, 0);


}

void Diagnostic::printraysHelper(ray* incRay, int times)
{

	cout << "Iteration type: ";
	if(times == 0)
	{
		cout << "Primary" << endl;
	}
	else 
	{
		cout << "Refraction" << endl;
	}

	Object *hit = NULL;
	float retVal = numeric_limits<float>::max();
	float hldVal = -1;
	for(auto so: scene->sceneObjects)
	{
		hldVal = so->intersect(*incRay);

		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				retVal = hldVal;
				hit = so;
			}

		}
	}

	if(hit != NULL)
	{
		cout << "Ray: {";
		cout << incRay->location.x << " " << incRay->location.y << " " << incRay->location.z << "} -> {";
		cout << incRay->direction.x << " " << incRay->direction.y << " " << incRay->direction.z << "}" << endl;
		cout << "Hit Object: (ID #" << hit->id << " - " << hit->type << ")" << endl;
		cout << "Color: " << hit->pigment.x << " " << hit->pigment.y << " " << hit->pigment.z << endl;
	}
	else
	{
		cout << "No intersection." << endl;
		cout << "Extra Info: into-air" << endl;
		return;
	}

	vec3 intersectPt = incRay->location + incRay->direction*retVal;
	cout << "Intersection: {" << intersectPt.x << " " << intersectPt.y << " " << intersectPt.z;
	cout << "} at T = " << retVal << endl;

	Tracer *t = new Tracer(scene, width, height);
	vec3 ambient = hit->pigment * hit->ambient;
	vec3 outcolor = hit->pigment * hit->ambient;

	float val = numeric_limits<float>::max();

	for(auto l: scene->lights)
	{
		bool inShadow = false;
		vec3 lightvec = normalize(l->location - intersectPt);
		ray *testRay = new ray(intersectPt, lightvec);
		val = t->checkForIntersection(intersectPt + 0.001f*testRay->direction, lightvec);

		if(val != -1)
		{
			if (val < length((l->location) - intersectPt))
			{
				inShadow = true;
			}
		}
		

		if(!inShadow)
		{
			vec3 normVec;
			if(hit->type == "Plane")
			{
				Plane * pPtr = (Plane *) hit;
				normVec = pPtr->normal;
			}
			else if (hit->type == "Sphere")
			{
				Sphere * sPtr = (Sphere *) hit;
				sPtr->calcNormal(intersectPt);
				normVec = sPtr->normal;
			}
			else
			{
				Triangle * tPtr = (Triangle *) hit;
				tPtr->calcNormal(intersectPt);
				normVec = tPtr->normal;
			}


			cout << "Normal: {" << normVec.x << " " << normVec.y << " " << normVec.z << "}" << endl;
			vec3 diffuseC = (t->computeDiffuse(intersectPt, hit, lightvec, normVec)* hit->pigment *l->color);
			vec3 specularC = (t->computeSpecular(intersectPt, hit, lightvec, normVec) * hit->pigment *l->color);

			vec3 reflectColor;
			if(hit->reflection > 0)
			{
				float refProd = dot(testRay->direction, normVec);
				vec3 reflectVec = normalize((testRay->direction) - (2*(refProd)*normVec));
				ray *pass = new ray((intersectPt + reflectVec * 0.001f), reflectVec);
				vec3 reflectColor = t->getColor(pass, 6);
				outcolor += (reflectColor * hit->reflection) * hit->pigment;
			}

			vec3 refractColor;
			if(hit->refraction > 0)
			{
				ray* refractRay = t->calcRefractionRay(testRay->direction, normVec, intersectPt, hit);
				refractColor = t->getColor(refractRay, 6);
				outcolor += (refractColor * hit->refraction) * hit->pigment;
			}

			outcolor = diffuseC + specularC;
			cout << "Final Color: {" << outcolor.x << " " << outcolor.y << " " << outcolor.z << "}" << endl;
			cout << "Ambient: {" << ambient.x << " " << ambient.y << " " << ambient.z << "}" << endl;
			cout << "Diffuse: {" << diffuseC.x << " " << diffuseC.y << " " << diffuseC.z << "}" << endl;
			cout << "Specular: {" << specularC.x << " " << specularC.y << " " << specularC.z << "}" << endl;
			cout << "Reflection: {" << reflectColor.x << " " << reflectColor.y << " " << reflectColor.z << "}" << endl;
			cout << "Refraction: {" << refractColor.x << " " << refractColor.y << " " << refractColor.z << "}" << endl;

			
		}
	}

}


void Diagnostic::firstHit(int x, int y, bool flag, ray *r, unsigned char* data)
{
	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	if ( r == NULL)
	{
		
		vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
		vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
		r = new ray(scene->cam->location, dir);
	}
	

	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << r->location.x << " " << r->location.y << " " << r->location.z << "} -> {";
	cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;

	Object *hit = NULL;
	float retVal = numeric_limits<float>::max();
	float hldVal = -1;
	for(auto so: scene->sceneObjects)
	{
		hldVal = so->intersect(*r);

		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				retVal = hldVal;
				hit = so;
			}

		}
	}

	if(hit != NULL)
	{
		cout << "T = " << retVal << endl;
		cout << "Object Type: " << hit->type << endl;

		if(flag)
		{
			cout << "Color: " << hit->pigment.x << " " << hit->pigment.y << " " << hit->pigment.z << endl;
		}
		else
		{
			cout << "BRDF: Blinn-Phong" << endl;
			cout << "Color: (" << static_cast<unsigned>(data[0]) << ", " << static_cast<unsigned>(data[1]) << ", " << static_cast<unsigned>(data[2]) << ")" << endl;
		}
	}
	else
	{
		cout << "No Hit" << endl;
	}
}


void Diagnostic::pixelColor(int x, int y)
{
	unsigned char *data = new unsigned char[3];

	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	
	vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
	vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
	ray *r = new ray(scene->cam->location, dir);

	
	Tracer *t = new Tracer(scene, width, height);
	vec3 color = t->getColor(r, 1);
	data[0] = (unsigned int) round(color.x * 255.f);
    data[1] = (unsigned int) round(color.y * 255.f);
    data[2] = (unsigned int) round(color.z * 255.f);

	
	firstHit(x, y, false, r, data);
}

