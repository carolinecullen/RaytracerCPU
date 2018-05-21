#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "Parse.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"	
#include "Triangle.hpp"
using namespace std;
using namespace glm;

string Parse::tokenizeHelper(ifstream &FileHandle, string &holdBuf)
{
	if(getline(FileHandle, holdBuf))
	{
		string token;
		stringstream fileString;

		fileString << holdBuf;
		fileString >> token;

		fileString.flush();
		return token;
	}
	else
	{
		return NULL;
	}
}

vector<float> Parse::getFloats(string buf)
{
	int pos = 0;
	vector<float> floatVals;
	while(pos < buf.size())
	{
		char cur = buf[pos];
		bool flag = false;
		char actualNum[640];

		int i = 0;
		while(cur == '.'|| (cur <= '9' && cur >= '0') || cur == '-')
		{
			flag = true;
			actualNum[i] = cur;
			i++;
			pos++;
			cur = buf[pos];
		}

		if(flag)
		{
			actualNum[i] = '\0';
			float f = strtof(actualNum, 0);
			floatVals.push_back(f);
		}
		pos++;
	}

	return floatVals;
}

Camera* Parse::placeCamera(ifstream &FileHandle)
{
	Camera* cam = new Camera;

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{
		if(tok == "location")
		{
			vector<float> locVals;
			locVals = Parse::getFloats(buf);

			if(locVals.size() > 3 || locVals.size() < 3)
			{
				cout << "Malformed Camera location in POV file." << endl;
				return NULL;
			}
			cam->location = vec3(locVals[0], locVals[1], locVals[2]);
		}

		if(tok == "up")
		{
			vector<float> upVals;
			upVals = Parse::getFloats(buf);

			if(upVals.size() > 3 || upVals.size() < 3)
			{
				cout << "Malformed Camera up in POV file." << endl;
				return NULL;
			}
			cam->up = vec3(upVals[0], upVals[1], upVals[2]);
		}

		if(tok == "right")
		{
			vector<float> rightVals;
			rightVals = Parse::getFloats(buf);

			if(rightVals.size() > 3 || rightVals.size() < 3)
			{
				cout << "Malformed Camera right in POV file." << endl;
				return NULL;
			}
			cam->right = vec3(rightVals[0], rightVals[1], rightVals[2]);
		}

		if(tok == "look_at")
		{
			vector<float> lookVals;
			lookVals = Parse::getFloats(buf);

			if(lookVals.size() > 3 || lookVals.size() < 3)
			{
				cout << "Malformed Camera look_at in POV file." << endl;
				return NULL;
			}
			cam->lookat = vec3(lookVals[0], lookVals[1], lookVals[2]);
		}

		buf = "";	
	}

	return cam;
}

Lighting* Parse::lightInsertion(string line)
{
	Lighting* light = new Lighting;
	vector<float> lVals;

	lVals = Parse::getFloats(line);

	if(lVals.size() > 6 || lVals.size() < 6)
	{
		cout << "Malformed lighting color in POV file." << endl;
		return NULL;
	}
	light->location = vec3(lVals[0], lVals[1], lVals[2]);
	light->color = vec3(lVals[3], lVals[4], lVals[5]);
	
	return light;
}

Triangle* Parse::triangleInsertion(ifstream &FileHandle, string line)
{
	Triangle* t = new Triangle();
	t->type = "Triangle";

	vector<float> aVals;

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{

		if(tok == "pigment")
		{
			parse_triangle_pigment(t, buf);
		} 
		else if(tok == "finish")
		{
			parse_triangle_finish(t, buf);
		}
		else
		{
			vector<float> hldVals = Parse::getFloats(buf);
			for(int i = 0; i < hldVals.size(); i++)
			{
				aVals.push_back(hldVals[i]);
			}
		}
		buf = "";	
	}

	if(aVals.size() == 9)
	{
		t->A = vec3(aVals[0], aVals[1], aVals[2]);
		t->B = vec3(aVals[3], aVals[4], aVals[5]);
		t->C = vec3(aVals[6], aVals[7], aVals[8]);
	}
	else
	{
		cout << "Must have 3 verticies to form a triangle." << endl;
		return NULL;
	}

	return t;
}

Sphere* Parse::sphereInsertion(ifstream &FileHandle, string line)
{
	Sphere* s = new Sphere();
	s->type = "Sphere";
	vector<float> sVals = Parse::getFloats(line);
	s->center = vec3(sVals[0], sVals[1], sVals[2]);
	s->radius = sVals[3];

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{
		if(tok == "pigment")
		{
			parse_sphere_pigment(s, buf);
		}

		if(tok == "finish")
		{	
			char cur = buf[buf.size()-1];
			bool flag = false;
			if(cur == '}')
			{
				
				char cur2 = buf[buf.size()-2];
				if(cur2 == '}')
				{
					flag = true;
				}
				
			}

			parse_sphere_finish(s, buf);
			if(flag)
			{
				return s;
			}
		}

		if(tok == "translate")
		{
			vector<float> tranVals;
			tranVals = Parse::getFloats(buf);

			if(tranVals.size() > 3 || tranVals.size() < 3)
			{
				cout << "Malformed Camera translate in POV file." << endl;
				return NULL;
			}
			s->translate = vec3(tranVals[0], tranVals[1], tranVals[2]);
		}

		buf = "";	
	}

	return s;
}

Plane* Parse::planeInsertion(ifstream &FileHandle, string line)
{
	Plane* p = new Plane();
	p->type = "Plane";
	vector<float> pVals = Parse::getFloats(line);
	p->normal = vec3(pVals[0], pVals[1], pVals[2]);
	p->distance = pVals[3];

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{
		if(tok == "pigment")
		{
			parse_plane_pigment(p, buf);
		}

		if(tok == "finish")
		{
			char cur = buf[buf.size()-1];
			bool flag = false;
			if(cur == '}')
			{
				
				char cur2 = buf[buf.size()-2];
				if(cur2 == '}')
				{
					flag = true;
				}
				
			}
			parse_plane_finish(p, buf);
			if(flag)
			{
				return p;
			}
		}
		buf = "";	
	}

	return p;
}


void Parse::parse_sphere_pigment(Sphere *sphere, string buf)
{
	vector<float> nums;
	nums = Parse::getFloats(buf);

	vector<string> sVals;
	istringstream iss(buf);

	int i = 0;
	for(string s; iss >> s; )
	{
		if(s == "rgb")
		{
			sphere->pigment = vec3(nums[0], nums[1], nums[2]);
			i++;
		}
		else if(s == "rgbf")
		{
			sphere->pigment = vec3(nums[0], nums[1], nums[2]);
			sphere->filter = nums[3];
			i++;
		}
		else if(s == "rgba")
		{
			sphere->pigment = vec3(nums[0], nums[1], nums[2]);
			sphere->filter = nums[3];
			i++;
		}
	}
}

void Parse::parse_triangle_pigment(Triangle *t, string buf)
{
	vector<float> nums;
	nums = Parse::getFloats(buf);

	vector<string> sVals;
	istringstream iss(buf);

	int i = 0;
	for(string s; iss >> s; )
	{
		if(s == "rgb")
		{
			t->pigment = vec3(nums[0], nums[1], nums[2]);
			i++;
		}
		else if(s == "rgbf")
		{
			t->pigment = vec3(nums[0], nums[1], nums[2]);
			t->filter = nums[3];
			i++;
		}
		else if(s == "rgba")
		{
			t->pigment = vec3(nums[0], nums[1], nums[2]);
			t->filter = nums[3];
			i++;
		}
	}
}

void Parse::parse_plane_pigment(Plane *p, string buf)
{
	vector<float> nums;
	nums = Parse::getFloats(buf);

	vector<string> sVals;
	istringstream iss(buf);

	int i = 0;
	for(string s; iss >> s; )
	{
		if(s == "rgb")
		{
			p->pigment = vec3(nums[0], nums[1], nums[2]);
			i++;
		}
		else if(s == "rgbf")
		{
			p->pigment = vec3(nums[0], nums[1], nums[2]);
			p->filter = nums[3];
			i++;
		}
		else if(s == "rgba")
		{
			p->pigment = vec3(nums[0], nums[1], nums[2]);
			p->filter = nums[3];
			i++;
		}
	}
}

void Parse::parse_sphere_finish(Sphere *sphere, string buf)
{
	vector<float> nums;
	nums = Parse::getFloats(buf);

	vector<string> sVals;
	istringstream iss(buf);

	int i = 0;
	for(string s; iss >> s; )
	{
		if(s == "{ambient" || s == "ambient")
		{
			sphere->ambient = nums[i];
			i++;
		}
		else if(s == "diffuse")
		{
			sphere->diffuse = nums[i];
			i++;
		}
		else if(s == "specular")
		{
			sphere->specular = nums[i];
			i++;
		}
		else if(s == "ior")
		{
			sphere->ior = nums[i];
			i++;
		}
		else if(s == "reflection")
		{
			sphere->reflection = nums[i];
			i++;
		}
		else if(s == "refraction")
		{
			sphere->refraction = nums[i];
			i++;
		}
		else if(s == "roughness")
		{
			sphere->roughness = nums[i];
			i++;
		}
	}

}

void Parse::parse_triangle_finish(Triangle *t, string buf)
{
	vector<float> nums;
	nums = Parse::getFloats(buf);

	vector<string> sVals;
	istringstream iss(buf);

	int i = 0;
	for(string s; iss >> s; )
	{
		if(s == "{ambient" || s == "ambient")
		{
			t->ambient = nums[i];
			i++;
		}
		else if(s == "diffuse")
		{
			t->diffuse = nums[i];
			i++;
		}
		else if(s == "specular")
		{
			t->specular = nums[i];
			i++;
		}
		else if(s == "ior")
		{
			t->ior = nums[i];
			i++;
		}
		else if(s == "reflection")
		{
			t->reflection = nums[i];
			i++;
		}
		else if(s == "refraction")
		{
			t->refraction = nums[i];
			i++;
		}
		else if(s == "roughness")
		{
			t->roughness = nums[i];
			i++;
		}
	}
}

void Parse::parse_plane_finish(Plane *p, string buf)
{
	vector<float> nums;
	nums = Parse::getFloats(buf);

	vector<string> sVals;
	istringstream iss(buf);

	int i = 0;
	for(string s; iss >> s; )
	{
		if(s == "{ambient" || s == "ambient")
		{
			p->ambient = nums[i];
			i++;
		}
		else if(s == "diffuse")
		{
			p->diffuse = nums[i];
			i++;
		}
		else if(s == "specular")
		{
			p->specular = nums[i];
			i++;
		}
		else if(s == "ior")
		{
			p->ior = nums[i];
			i++;
		}
		else if(s == "reflection")
		{
			p->reflection = nums[i];
			i++;
		}
		else if(s == "refraction")
		{
			p->refraction = nums[i];
			i++;
		}
		else if(s == "roughness")
		{
			p->roughness = nums[i];
			i++;
		}
	}
}

bool Parse::tokenParser(string fName, Scene *scene)
{
	ifstream FileHandle("../resources/" + fName);
	Camera *cam;
	vector<Lighting *> allLights;
	vector<Object *> objs;

	if(!FileHandle)
	{
		printf("Problem opening file!\n");
		return false;
	}

	string holdBuf;

	int i = 1;
	while(getline(FileHandle, holdBuf))
	{
		string token;
		stringstream fileString;

		fileString << holdBuf;
		fileString >> token;

		if(token != "")
		{
			if (token == "//")
			{
				continue;
			}
			else if (token == "sphere")
			{
				Sphere *sphere = sphereInsertion(FileHandle, holdBuf);
				objs.push_back(sphere);
				sphere->id = i;
				i++;
			}
			else if (token == "light_source")
			{
				Lighting *light = lightInsertion(holdBuf);
				allLights.push_back(light);
			}
			else if (token == "plane")
			{
				Plane *plane = planeInsertion(FileHandle, holdBuf);
				objs.push_back(plane);
				plane->id = i;
				i++;
			}
			else if (token == "triangle")
			{
				Triangle *triangle = triangleInsertion(FileHandle, holdBuf);
				objs.push_back(triangle);
				triangle->id = i;
				i++;
			}
			else if (token == "camera")
			{
				cam = placeCamera(FileHandle);
			}
		}

		fileString.flush();
		holdBuf = "";
	}

	scene->cam = cam;
	scene->lights = allLights;
	scene->sceneObjects = objs;

	return true;
}


