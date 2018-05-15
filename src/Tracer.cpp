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

float Tracer::checkForIntersection(vec3 pt, vec3 lRay, Object* obj)
{
	float hldVal = -1;
	float retVal = numeric_limits<float>::max();
	int hitID = -1;
	for(auto so: scene->sceneObjects)
	{
		ray *testRay = new ray(pt, lRay);
		hldVal = so->intersect(*testRay);
		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				retVal = hldVal;
				hitID = so->id;
			}

		}
	}

	if(hldVal == -1) //|| (hitID == -1)) 
	{
		return -1;
	}
	else if(hitID == obj->id)
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

vec3 Tracer::getColor(ray* incRay, int recCount, bool print)
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
		// cout << "id: " << so->id << endl;
		// cout << "hldval: " << hldVal << endl;
		// cout << "---------" << endl;
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
		if(print)
		{
			cout << "No intersection." << endl;
			cout << "Extra Info: into-air" << endl;
		}
		return vec3(0.f);
	}


	vec3 intersectPt = incRay->location + incRay->direction*retVal;
	vec3 ambient = obj->pigment * obj->ambient;
	float val = numeric_limits<float>::max();

	vec3 diffuse = vec3(0.f);
	vec3 outcolor = vec3(0.f);
	vec3 specular = vec3(0.f);
	vec3 refractionColor = vec3(0.f);
	vec3 reflectColor = vec3(0.f);
	vec3 normVec;
	for(auto l: scene->lights)
	{
		bool inShadow = false;
		vec3 lightvec = normalize(l->location - intersectPt);
		ray *testRay = new ray(intersectPt, lightvec);
		val = checkForIntersection(intersectPt + 0.001f*testRay->direction, lightvec, obj);

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

			if(obj->reflection > 0)
			{
				float refProd = dot(incRay->direction, normVec);
				vec3 reflectVec = (incRay->direction) - (2.f*(refProd)*normVec);
				ray *pass = new ray((intersectPt + reflectVec * 0.001f), reflectVec);
				reflectColor = getColor(pass, recCount-1, print) * obj->pigment;
			}

			
			if(obj->refraction > 0)
			{
				ray* refractRay = calcRefractionRay(incRay->direction, normVec, intersectPt, obj, print);
				refractionColor = getColor(refractRay, recCount-1, print) * obj->pigment;
			}

			diffuse = (computeDiffuse(intersectPt, obj, lightvec, normVec)* obj->pigment *l->color);
			specular = (computeSpecular(intersectPt, obj, lightvec, normVec) * obj->pigment *l->color);
		}
	}

	vec3 localcolor = (ambient + diffuse + specular) * (1 - obj->filter) * (1 - obj->reflection);
	outcolor = localcolor + reflectColor*(obj->reflection)*(1 - obj->filter) + refractionColor*(obj->filter);

	if(print)
	{
		cout << "Ray: {";
		cout << incRay->location.x << " " << incRay->location.y << " " << incRay->location.z << "} -> {";
		cout << incRay->direction.x << " " << incRay->direction.y << " " << incRay->direction.z << "}" << endl;
		cout << "Hit Object: (ID #" << obj->id << " - " << obj->type << ")" << endl;
		cout << "Intersection: {" << intersectPt.x << " " << intersectPt.y << " " << intersectPt.z;
		cout << "} at T = " << retVal << endl;
		cout << "Normal: {" << normVec.x << " " << normVec.y << " " << normVec.z << "}" << endl;
		cout << "Final Color: {" << outcolor.x << " " << outcolor.y << " " << outcolor.z << "}" << endl;
		cout << "Ambient: {" << ambient.x << " " << ambient.y << " " << ambient.z << "}" << endl;
		cout << "Diffuse: {" << diffuse.x << " " << diffuse.y << " " << diffuse.z << "}" << endl;
		cout << "Specular: {" << specular.x << " " << specular.y << " " << specular.z << "}" << endl;
		cout << "Reflection: {" << reflectColor.x << " " << reflectColor.y << " " << reflectColor.z << "}" << endl;
		cout << "Refraction: {" << refractionColor.x << " " << refractionColor.y << " " << refractionColor.z << "}" << endl;
		cout << "----" << endl;
		// cout << "Color: " << obj->pigment.x << " " << obj->pigment.y << " " << obj->pigment.z << endl;
	}

	return outcolor;

}

ray* Tracer::calcRefractionRay(vec3 rayDirection, vec3 &normVec, vec3 intersectPt, Object* obj, bool print)
{
	float n1 = 1.f;
	float n2 = obj->ior;

	if (dot(normVec, rayDirection) > 0) 
	{
		n1 = n2;
		n2 = 1.f;
		normVec = -normVec;
	}

	float directionDot = dot(rayDirection, normVec);
	float snell = n1/n2;
	float sqrtVal = 1-(snell*snell)*(1 - directionDot*directionDot);

	vec3 refractVec = snell*(rayDirection-directionDot*normVec)-normVec*sqrt(sqrtVal);
	return (new ray((intersectPt + (refractVec * 0.001f)), refractVec));
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

			
			vec3 color = getColor(r, 6, false);
			data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 0] = (unsigned int) round((clamp(color.x,0.f,1.f)) * 255.f);
	        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 1] = (unsigned int) round((clamp(color.y,0.f,1.f)) * 255.f);
	        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 2] = (unsigned int) round((clamp(color.z,0.f,1.f)) * 255.f);
					
				
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	
}

void Tracer::printrays(int x, int y)
{
	cout << "Pixel: [" << x << ", " << y << "]\n----" << endl ;
	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));
	
	vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
	vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * scene->cam->up) + w*(1.0f));
	ray *r = new ray(scene->cam->location, dir);

	// cout << "Ray: {";
	// cout << r->location.x << " " << r->location.y << " " << r->location.z << "} -> {";
	// cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;
	
	vec3 color = getColor(r, 6, true);	

	// cout << "Color: " << color.x << " " << color.y << " " << color.z << endl;	
	cout << "--------------------------------------------------------" << endl;	
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


