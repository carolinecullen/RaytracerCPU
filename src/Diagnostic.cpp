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
	vec3 color = t->getColor(r, 1, false, 0);
	data[0] = (unsigned int) round(color.x * 255.f);
    data[1] = (unsigned int) round(color.y * 255.f);
    data[2] = (unsigned int) round(color.z * 255.f);

	
	firstHit(x, y, false, r, data);
}

