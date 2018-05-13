#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "Tracer.hpp"
#include "Ray.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"

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
		ray *testRay = new ray(pt, lRay);
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

float Tracer::computeSpecular(vec3 pt, Object* obj, vec3 lightvec, vec3 normal)
{
	vec3 viewvec = normalize(scene->cam->location - pt);
	vec3 halfvec = normalize(lightvec + viewvec);
	float dotprod = clamp(dot(halfvec, normalize(normal)), 0.f, 1.f);

	float alpha = (2/(pow(obj->roughness, 2)))-2;
	float hldval = pow(dotprod, alpha);

	float outspec = (obj->specular * hldval);
	return outspec;
}

float Tracer::computeDiffuse(vec3 pt, Object* obj, vec3 lightvec, vec3 normal)
{

	float dotprod = clamp((dot(normalize(normal), lightvec)), 0.f, 1.f);
	float diff = obj->diffuse * dotprod;

	return diff;
}

vec3 Tracer::getColor(ray* incRay, int recCount)
{
	if (recCount <= 0)
	{
		return vec3(0.f);
	}

	float retVal = numeric_limits<float>::max();
	float hldVal = -1;
	Object *obj = NULL;

	for(auto so: scene->sceneObjects)
	{
		hldVal = so->intersect(*incRay);
		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				retVal = hldVal;
				obj = so;
			}
		}
	}

	if(obj == NULL)
	{
		return vec3(0.f);
	}


	vec3 intersectPt = incRay->location + incRay->direction*retVal;
	vec3 outcolor = obj->pigment * obj->ambient;
	float val = numeric_limits<float>::max();

	for(auto l: scene->lights)
	{
		bool inShadow = false;
		vec3 lightvec = normalize(l->location - intersectPt);
		ray *testRay = new ray(intersectPt, lightvec);
		val = checkForIntersection(intersectPt + 0.001f*testRay->direction, lightvec);

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
			if(obj->type == "Plane")
			{
				Plane * pPtr = (Plane *) obj;
				normVec = pPtr->normal;
			}
			else if (obj->type == "Sphere")
			{
				Sphere * sPtr = (Sphere *) obj;
				sPtr->calcNormal(intersectPt);
				normVec = sPtr->normal;
			}
			else
			{
				Triangle * tPtr = (Triangle *) obj;
				tPtr->calcNormal(intersectPt);
				normVec = tPtr->normal;
			}
			
			outcolor += (computeDiffuse(intersectPt, obj, lightvec, normVec)* obj->pigment *l->color);
			outcolor += (computeSpecular(intersectPt, obj, lightvec, normVec) * obj->pigment *l->color);

			vec3 reflectColor = vec3(0.f);
			if(obj->reflection > 0)
			{
				float refProd = dot(testRay->direction, normVec);
				vec3 reflectVec = (testRay->direction) - (2*(refProd)*normVec);
				ray *pass = new ray(intersectPt, reflectVec);
				reflectColor = clamp((getColor(pass, recCount)), 0.f, 1.f);
				outcolor += (reflectColor * obj->reflection) * obj->pigment;
			}
			
		}
	}

	return outcolor * (1 - obj->reflection);
	// return outcolor;
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

			
			vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
			vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
			ray *r = new ray(scene->cam->location, dir);

			
			vec3 color = getColor(r, 6);
			data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 0] = (unsigned int) round((clamp(color.x,0.f,1.f)) * 255.f);
	        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 1] = (unsigned int) round((clamp(color.y,0.f,1.f)) * 255.f);
	        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 2] = (unsigned int) round((clamp(color.z,0.f,1.f)) * 255.f);
					
				
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	
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

			
			vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
			vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
			ray *r = new ray(scene->cam->location, dir);


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
}


