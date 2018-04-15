#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "Tracer.hpp"
#include "Ray.hpp"

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


			float retVal = 100000000000;
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

void Tracer::firstHit(int x, int y)
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

	Object *hit = NULL;
	float retVal = 100000000000;
	float hldVal = -1;
	for(auto so: scene->sceneObjects)
	{
		hldVal = so->intersect(*r);
		// cout << so->type << endl;
		// cout << hldVal << endl;

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
		cout << "Color: " << hit->pigment.x << " " << hit->pigment.y << " " << hit->pigment.z << endl;
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