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

	int i = 0;
	int j = 0;
	int k = 0;
	while(j <= 480)
	{
		float pixelX = (float)((-0.5) + ((i + 0.5)/width));
		float pixelY = (float)((-0.5) + ((j + 0.5)/height));

		ray *r = new ray();
		vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
		vec3 dir = normalize(normalize(pixelX * scene->cam->right) + (pixelY * normalize(scene->cam->up)) + w*(1.0f));
		r->createRay(scene->cam->location, dir);


		float retVal = 1000;
		for(auto so: scene->sceneObjects)
		{
			float hldVal = -1;
			cout << so->type << endl;
			hldVal = so->intersect(*r);

			// cout << r->direction.x << " " << r->direction.y << endl;
			// cout << "hldval: " << hldVal << endl;
			if(hldVal != 0 && hldVal != -1)
			{
				if(hldVal < retVal)
				{
					retVal = hldVal;
					data[(k * 3)] = (unsigned int) round(so->pigment.x * 255.f);
					data[(k * 3)+1] = (unsigned int) round(so->pigment.y * 255.f);
					data[(k * 3)+2] = (unsigned int) round(so->pigment.z * 255.f);

					// cout << "dta: " << data[(k*3)] << endl;
				}

				// cout << so->type << endl;
				// cout << "Pigment vals: " << so->pigment.x << " " << so->pigment.y << " " << so->pigment.z << endl;
			}
		}



		if (retVal == 1000)
		{
			data[(k * 3)] = (unsigned int) round(0.0 * 255.f);
			data[(k * 3)+1] = (unsigned int) round(0.0 * 255.f);
			data[(k * 3)+2] = (unsigned int) round(0.0 * 255.f);
		}

		if(i < 640)
		{
			i++;
		}
		else if(i == 640)
		{
			i = 0;
			j++;
		}
		k++;
	}

	// for(int i = 0; i < (size.x * size.y * numChannels); i++)
	// {
	// 	if(i%3 == 0)
	// 	{
	// 		cout << data[i] << " " << endl;
	// 	}
	// 	cout << data[i] << " ";
	// }

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	// delete[] data;
	
}

void Tracer::firstHit(int x, int y)
{

	float pixelX = (float)((-0.5) + ((x + 0.5)/width));
	float pixelY = (float)((-0.5) + ((y + 0.5)/height));

	ray *r = new ray();
	vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
	vec3 dir = normalize(((float)pixelX * scene->cam->right) + ((float)pixelY * normalize(scene->cam->up)) + w*(1.0f));
	r->createRay(scene->cam->location, dir);

	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << r->location.x << " " << r->location.y << " " << r->location.z << "} -> {";
	cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;

	Object *hit = NULL;
	float retVal = 1000;
	for(auto so: scene->sceneObjects)
	{
		float hldVal = -1;
		hldVal = so->intersect(*r);

		if(hldVal != 0 && hldVal != -1)
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
		cout << "Object Type: " << hit->type << endl;
		cout << "Color: " << hit->pigment.x << " " << hit->pigment.y << " " << hit->pigment.z << endl;
	}
	else
	{
		cout << "Not Hit" << endl;
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