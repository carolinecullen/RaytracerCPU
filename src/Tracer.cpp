#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "Tracer.hpp"
#include "Ray.hpp"
#include "Plane.hpp"

using namespace std; 
using namespace glm;

Tracer::Tracer()
{
	this->scene = NULL;
	this->width = 0;
	this->height = 0;
}

Tracer::Tracer(Scene *s, int w, int h)
{
	this->scene = s;
	this->width = w;
	this->height = h;
}

float Tracer::checkForIntersection(vec3 pt, vec3 lRay)
{
	float hldVal = -1;
	float retVal = numeric_limits<float>::max();
	for(auto so: scene->sceneObjects)
	{
		ray *testRay = new ray();
		testRay->createRay(pt, lRay);
		hldVal = so->intersect(*testRay);
		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				retVal = hldVal;
			}

		}
	}

	if(hldVal == -1)
	{
		return -1;
	}
	else
	{
		return retVal;
	}
}

float Tracer::computeSpecular(vec3 pt, Object* obj, vec3 lightvec)
{
	vec3 viewvec = normalize(scene->cam->location - pt);
	vec3 halfvec = normalize(lightvec + viewvec);
	vec3 normal;
	if(obj->type == "Plane")
	{
		Plane * pPtr = (Plane *) obj;
		normal = pPtr->normal;
	}
	else
	{
		normal = pt;
	}

	float dotprod = clamp(dot(halfvec, normal), 0.f, 1.f);
	float hldval = pow(dotprod, obj->roughness);

	float outspec = (obj->specular * hldval);
	return outspec;
}

float Tracer::computeDiffuse(vec3 pt, Object* obj, vec3 lightvec)
{
	vec3 normal;

	if(obj->type == "Plane")
	{
		Plane * pPtr = (Plane *) obj;
		normal = pPtr->normal;
	}
	else
	{
		normal = pt;
	}
	float dotprod = clamp((dot(normal, lightvec)), 0.f, 1.f);
	float diff = obj->diffuse * dotprod;

	return diff;
}

vec3 Tracer::getColor(ray *r, Object* obj, float t)
{
	vec3 pt = r->calculate(t)+0.001f;
	vec3 outcolor = obj->pigment * obj->ambient;
	float val = numeric_limits<float>::max();;

	for(auto l: scene->lights)
	{
		bool inShadow = false;

		vec3 lightvec = normalize(l->location - pt);
		val = checkForIntersection(pt, lightvec);

		if (val < length((l->location) - pt))
		{
			inShadow = true;
		}

		if(!inShadow)
		{
			// outcolor = obj->pigment;
			outcolor += computeDiffuse(pt, obj, lightvec) * obj->pigment;
			// outcolor += (computeDiffuse(pt, obj, lightvec)* obj->pigment *l->color);
			outcolor += computeSpecular(pt, obj, lightvec) * obj->pigment;
		}
	}

	return outcolor;
}

void Tracer::traceRays()
{

	const int numChannels = 3;
 	const glm::ivec2 size = glm::ivec2(width, height);
 	const string fileName = "output.png";
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	
	for (int j = 0; j < size.y; ++ j)
	{
	    for (int i = 0; i < size.x; ++ i)
	    {
			float pixelX = (float)((-0.5) + ((i + 0.5)/width));
			float pixelY = (float)((-0.5) + ((j + 0.5)/height));

			ray *r = new ray();
			vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
			vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
			r->createRay(scene->cam->location, dir);


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

						vec3 color = getColor(r, so, retVal);
						data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 0] = (unsigned int) round(color.x * 255.f);
				        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 1] = (unsigned int) round(color.y * 255.f);
				        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 2] = (unsigned int) round(color.z * 255.f);
					}

				}
			}
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	
}

void Tracer::pixelColor(int x, int y)
{
	unsigned char *data = new unsigned char[3];

	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	ray *r = new ray();
	vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
	vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
	r->createRay(scene->cam->location, dir);

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
				vec3 color = getColor(r, so, retVal);
				data[0] = (unsigned int) round(color.x * 255.f);
		        data[1] = (unsigned int) round(color.y * 255.f);
		        data[2] = (unsigned int) round(color.z * 255.f);
			}

		}
	}
	
	firstHit(x, y, false, r, data);
}

void Tracer::castRays()
{

	const int numChannels = 3;
 	const glm::ivec2 size = glm::ivec2(width, height);
 	const string fileName = "output.png";
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	
	for (int j = 0; j < size.y; ++ j)
	{
	    for (int i = 0; i < size.x; ++ i)
	    {
			float pixelX = (float)((-0.5) + ((i + 0.5)/width));
			float pixelY = (float)((-0.5) + ((j + 0.5)/height));

			ray *r = new ray();
			vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
			vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
			r->createRay(scene->cam->location, dir);


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
						data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 0] = (unsigned int) round(so->pigment.x * 255.f);
				        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 1] = (unsigned int) round(so->pigment.y * 255.f);
				        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 2] = (unsigned int) round(so->pigment.z * 255.f);
						
					}

				}
			}
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	// delete[] data;
	
}

void Tracer::firstHit(int x, int y, bool flag, ray *r, unsigned char* data)
{
	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	if ( r == NULL)
	{
		r = new ray();
		vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
		vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
		r->createRay(scene->cam->location, dir);
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
			// cout << "data " << static_cast<unsigned>(data[0]) <<endl;

			cout << "Color: (" << static_cast<unsigned>(data[0]) << ", " << static_cast<unsigned>(data[1]) << ", " << static_cast<unsigned>(data[2]) << ")" << endl;
		}
	}
	else
	{
		cout << "No Hit" << endl;
	}


}

void Tracer::pixelRay(int x, int y)
{

	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	ray *r = new ray();
	vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
	vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
	r->createRay(scene->cam->location, dir);

	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << r->location.x << " " << r->location.y << " " << r->location.z << "} -> {";
	cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;


}