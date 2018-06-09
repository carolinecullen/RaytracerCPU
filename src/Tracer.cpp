#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "Tracer.hpp"
#include "Ray.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Diagnostic.hpp"
#include "Box.hpp"
#include "glm/gtc/matrix_transform.hpp"	

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

float Tracer::checkForIntersection(ray * lRay, Object *obj, int flag)
{
	float hldVal = -1;
	float retVal = numeric_limits<float>::max();
	int hitID = -1;
	Object *initialized = NULL;

	for(auto so: scene->sceneObjects)
	{

		vec3 objl = vec3(so->IM * vec4(lRay->location, 1.0f));
		vec3 objd = vec3(so->IM * vec4(lRay->direction, 0.0f));

		ray *testRay = new ray(objl, objd);
		hldVal = so->intersect(*testRay);
		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				retVal = hldVal;
				hitID = so->id;
				initialized = so;
			}

		}
		delete testRay;
	}

	if(flag == 3)
	{
		vector<Object*> objects = scene->bht->treeDecend(scene->bht->rootBox, *lRay);
    	if (objects.size() != 0) 
    	{
    		for(auto so: objects)
			{	
	      		vec3 objl = vec3(so->IM * vec4(lRay->location, 1.0f));
				vec3 objd = vec3(so->IM * vec4(lRay->direction, 0.0f));
				ray *checkObjRay = new ray(objl, objd);

				hldVal = so->intersect(*checkObjRay);
				if(hldVal > 0)
				{
					if(hldVal < retVal)
					{
						retVal = hldVal;
						hitID = so->id;
						initialized = so;
					}
				}

				delete checkObjRay;
			}
		}
		else
		{
			return -1;
		}
	}

	if(initialized == NULL)
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

float Tracer::calcFresnel(float ior, vec3 d, vec3 norm)
{
	float f0 = (float)(pow((ior-1.f), 2)/pow((ior+1.f), 2));
	float dotprod = (float)(1.f - abs(dot(norm, -d)));
	return (float)(f0 + ((1.f-f0) * pow(dotprod, 5.f)));
}

// FLAG :: 1 - fresnel, 2 - beers
vec3 Tracer::getColor(ray* incRay, int recCount, bool print, int flag, float& t_val, int bounces, int samples)
{
	if (recCount <= 0)
	{
		return vec3(0.f);
	}

	if (bounces <= 0)
	{
		return vec3(0.f);
	}

	float retVal = numeric_limits<float>::max();
	float hldVal = -1;
	Object *obj = NULL;
	ray *objRay = NULL;
	ray* checkObjRay;

	for(auto so: scene->sceneObjects)
	{
		vec3 objl = vec3(so->IM * vec4(incRay->location, 1.0f));
		vec3 objd = vec3(so->IM * vec4(incRay->direction, 0.0f));
		checkObjRay = new ray(objl, objd);

		hldVal = so->intersect(*checkObjRay);
		if(hldVal > 0)
		{
			if(hldVal < retVal)
			{
				if(objRay != NULL)
				{
					delete objRay;
				}
				retVal = hldVal;
				obj = so;
				objRay = new ray(objl, objd);
			}
		}
		delete checkObjRay;
	}

	if(flag == 3)
	{
		vector<Object*> objects = scene->bht->treeDecend(scene->bht->rootBox, *incRay);
    	if (objects.size() != 0) 
    	{
    		for(auto so: objects)
			{	
	      		vec3 objl = vec3(so->IM * vec4(incRay->location, 1.0f));
				vec3 objd = vec3(so->IM * vec4(incRay->direction, 0.0f));
				checkObjRay = new ray(objl, objd);

				hldVal = so->intersect(*checkObjRay);
				if(hldVal > 0)
				{
					if(hldVal < retVal)
					{
						if(objRay != NULL)
						{
							delete objRay;
						}
						retVal = hldVal;
						obj = so;
						objRay = new ray(objl, objd);
					}
				}

				delete checkObjRay;
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
	vec3 objPt = objRay->location + objRay->direction*retVal;

	vec3 ambient = obj->pigment * obj->ambient;
	float val = numeric_limits<float>::max();

	vec3 diffuse = vec3(0.f);
	vec3 outcolor = vec3(0.f);
	vec3 specular = vec3(0.f);
	vec3 refractionColor = vec3(0.f);
	vec3 reflectColor = vec3(0.f);
	vec3 normVec;
	vec3 lightvec;
	bool entering = false;

	for(auto l: scene->lights)
	{
		bool inShadow = false;
		lightvec = normalize(l->location - intersectPt);
		ray *lRay = new ray(intersectPt + 0.001f*lightvec, lightvec);
		val = checkForIntersection(lRay, obj, flag);

		if(val != -1)
		{
			if (val < length((l->location) - lRay->location))
			{
				inShadow = true;
			}
		}
		delete lRay;

		if(!inShadow)
		{
			if(obj->type == "Plane")
			{
				Plane * pPtr = (Plane *) obj;
				normVec = pPtr->normal;
				vec3 wNormVec = normalize(vec3(transpose(pPtr->IM) * vec4(normVec, 0.0f)));
				normVec = wNormVec;
			}
			else if (obj->type == "Sphere")
			{
				Sphere * sPtr = (Sphere *) obj;
				sPtr->calcNormal(objPt);
				normVec = sPtr->normal;
				vec3 wNormVec = normalize(vec3(transpose(sPtr->IM) * vec4(normVec, 0.0f)));
				normVec = wNormVec;
			}
			else if (obj->type == "Triangle")
			{
				Triangle * tPtr = (Triangle *) obj;
				tPtr->calcNormal(objPt);
				normVec = tPtr->normal;
				vec3 wNormVec = normalize(vec3(transpose(tPtr->IM) * vec4(normVec, 0.0f)));
				normVec = wNormVec;
			}
			else if (obj->type == "Box")
			{
				Box * bPtr = (Box *) obj;
				bPtr->calcNormal(objPt);
				normVec = bPtr->normal;
				vec3 wNormVec = normalize(vec3(transpose(bPtr->IM) * vec4(normVec, 0.0f)));
				normVec = wNormVec;
			}

			if((obj->reflection > 0) || ((obj->filter > 0) && (flag == 1)))
			{
				float refProd = dot(incRay->direction, normVec);
				vec3 reflectVec = (incRay->direction) - (2.f*(refProd)*normVec);
				ray *pass = new ray((intersectPt + reflectVec * 0.001f), reflectVec);
				reflectColor = getColor(pass, recCount-1, print, flag, t_val, bounces, samples) * obj->pigment;
				delete pass;
			}

			
			if(obj->filter > 0)
			{

				if (dot(normVec, incRay->direction) > 0) 
				{
					t_val = retVal;
				}

				ray* refractRay = calcRefractionRay(incRay->direction, normVec, intersectPt, obj, print, entering);
				refractionColor = getColor(refractRay, recCount-1, print, flag, t_val, bounces, samples);
				delete refractRay;

				if(entering && flag != 2)
				{
					refractionColor*=obj->pigment;
				}

				if(flag == 2 && entering)
				{
					vec3 absorbance = (1.f - refractionColor) * (0.15f) * -(t_val);
					vec3 attenuation = exp(absorbance);
					refractionColor = refractionColor * attenuation;
				}
			}

			diffuse = (computeDiffuse(intersectPt, obj, lightvec, normVec)* obj->pigment *l->color);
			specular = (computeSpecular(intersectPt, obj, lightvec, normVec) * obj->pigment *l->color);
		}
	}

	if (flag == 4)
	{
		ambient = vec3(0.f);
		if(bounces == 1 && samples>16)
		{
			samples = 16;
		}

		vector<vec3> samplePts = generate_hemisphere_smpl_pts(samples);

		for(auto pt: samplePts)
		{
			ray *ambRec = alignSampleVector(pt, scene->cam->up, normVec, intersectPt);
			ambient += (getColor(ambRec, recCount, print, flag, t_val, bounces-1, samples));
			delete ambRec;
		}

		if(samplePts.size() > 0)
		{
			ambient *= (float)(1/samplePts.size());
		}
		
	}

	vec3 localcolor = (ambient + diffuse + specular);
	float localContribution = (1 - obj->filter) * (1 - obj->reflection);
	float reflectionContribution, transmissionContribution;

	if(flag == 1)
	{
		float fresnelReflectance = calcFresnel(obj->ior, (incRay->direction), normVec);
		reflectionContribution = ((obj->reflection) * (1 - obj->filter)) + (obj->filter * fresnelReflectance);
		transmissionContribution = (obj->filter) * (1 - fresnelReflectance);
	}
	else
	{
		reflectionContribution = (obj->reflection) * (1 - obj->filter);
		transmissionContribution = (obj->filter); 
	}

	outcolor = (localcolor*localContribution) + (reflectColor*reflectionContribution) + (refractionColor*transmissionContribution);

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
	}

	return outcolor;

}

ray* Tracer::alignSampleVector(vec3 pt, vec3 up, vec3 normal, vec3 intersectPt)
{
	up = vec3(0.f,0.f,1.f);
	float angle = acos(dot(up, normal));
	vec3 axis = cross(up,normal);

	if(axis == up)
	{
		 return new ray((intersectPt + normal * 0.001f), pt);

	}
	if(axis == normal)
	{
		 return new ray((intersectPt + normal * 0.001f), pt);

	}
	if(axis == -normal)
	{
		 return new ray((intersectPt + normal * 0.001f), -pt);

	}

	mat4 matrix = mat4(1.f);

 	matrix = rotate(mat4(1.0f), angle, axis) * matrix;
 	vec4 transformed = normalize(matrix*vec4(pt, 0.f));
 	return new ray((intersectPt + normal * 0.001f), vec3(transformed.x, transformed.y, transformed.z));
}

vector<vec3> Tracer::generate_hemisphere_smpl_pts(int numPts)
{
	vector<vec3> pts;
	for(int i = 0; i < numPts; i++)
	{
		const float u = rand() / (float) RAND_MAX;
		const float v = rand() / (float) RAND_MAX;
		vec3 retWeighted = generateWeightedPoint(u,v);
		pts.push_back(retWeighted);
	}
	
	return pts;
}

vec3 Tracer::generateWeightedPoint(float u, float v)
{
	float radial = sqrt(u);
	float theta = 2.0f * 3.14159f * v;

	float x = (float)(radial * cos(theta));
	float y = (float)(radial * sin(theta));

	return vec3(x, y, (sqrt(1-u)));
}

ray* Tracer::calcRefractionRay(vec3 rayDirection, vec3 &normVec, vec3 intersectPt, Object* obj, bool print, bool& entering)
{
	float n1 = 1.f;
	float n2 = obj->ior;

	// if the ray is coming in the sphere
	if (dot(normVec, rayDirection) < 0)
	{
		entering = true;
	}

	// if the ray is coming out the sphere
	if (dot(normVec, rayDirection) > 0) 
	{
		n1 = n2;
		n2 = 1.f;
		normVec = -normVec;
		entering = false;
	}


	float directionDot = dot(rayDirection, normVec);
	float snell = n1/n2;
	float sqrtVal = 1-(snell*snell)*(1 - pow(directionDot,2));

	vec3 refractVec = snell*(rayDirection-directionDot*normVec)-normVec*sqrt(sqrtVal);
	return (new ray((intersectPt + (refractVec * 0.001f)), refractVec));
}

// FLAG :: 1 - fresnel, 2 - beers, 3 - bounding box
void Tracer::traceRays(int flag, int samples)
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

			float tf = 0.f;
			vec3 color = getColor(r, 6, false, flag, tf, 2, samples);
			data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 0] = (unsigned int) round((clamp(color.x,0.f,1.f)) * 255.f);
	        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 1] = (unsigned int) round((clamp(color.y,0.f,1.f)) * 255.f);
	        data[(size.x * numChannels) * (size.y - 1 - j) + numChannels * i + 2] = (unsigned int) round((clamp(color.z,0.f,1.f)) * 255.f);
			delete r;
				
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	
}

void Tracer::traceRaysSuper(int numSamples)
{

	const int numChannels = 3;
 	const glm::ivec2 size = glm::ivec2(width, height);
 	const string fileName = "output.png";
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	for (int j = 0; j < size.y; ++ j)
	{
	    for (int i = 0; i < size.x; ++ i)
	    {
	    	vec3 color = vec3(0.f);
	    	for (int n = 0; n < numSamples; ++ n)
			{
			    for (int m = 0; m < numSamples; ++ m)
			    {
			    	float pixelX = (float)((-0.5) + ((m + 0.5)/numSamples));
			    	float pixelY = (float)((-0.5) + ((n + 0.5)/numSamples));
					float Us = (float)((-0.5) + ((i + 0.5 + pixelX)/width));
					float Vs = (float)((-0.5) + ((j + 0.5 + pixelY)/height));

					vec3 w = normalize((scene->cam->lookat) - (scene->cam->location));
					vec3 dir = normalize(((float)Us * scene->cam->right) + ((float)Vs * scene->cam->up) + w*(1.0f));
					ray *r = new ray(scene->cam->location, dir);
					
					float tf = 0.f;
					color += getColor(r, 6, false, 0, tf, 2, 256);
				}
			}

			color = color/((float)(numSamples*numSamples));
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
	float tf = 0.f;
	vec3 color = getColor(r, 6, true, 0, tf, 2, 256);	

	cout << "Color: " << "[" << color.x << ", " << color.y << ", " << color.z << "]" << endl;
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


