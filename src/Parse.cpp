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
			vector<float> tVals;
			tVals = Parse::getFloats(buf);

			if(tVals.size() > 3 || tVals.size() < 3)
			{
				cout << "Malformed Plane Pigment in POV file." << endl;
				return NULL;
			}
			t->pigment = vec3(tVals[0], tVals[1], tVals[2]);
		} 
		else if(tok == "finish")
		{
			vector<float> tVals;
			tVals = Parse::getFloats(buf);

			if(tVals.size() == 2)
			{
				t->ambient = tVals[0];
				t->diffuse = tVals[1];
			}
			else if(tVals.size() == 3)
			{
				t->ambient = tVals[0];
				t->diffuse = tVals[1];
				t->specular = tVals[2];
			}
			else if(tVals.size() == 4)
			{
				t->ambient = tVals[0];
				t->diffuse = tVals[1];
				t->specular = tVals[2];
				t->roughness = tVals[3];
			}
			else if(tVals.size() == 5)
			{
				t->ambient = tVals[0];
				t->diffuse = tVals[1];
				t->specular = tVals[2];
				t->roughness = tVals[3];
				t->ior = tVals[4];
			}
			else
			{
				cout << "Malformed Triangle Finish in POV file." << endl;
				return NULL;
			}
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
		t->calculateValues();
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
			vector<float> sVals;
			sVals = Parse::getFloats(buf);

			if(sVals.size() > 3 || sVals.size() < 3)
			{
				cout << "Malformed sphere pigment in POV file." << endl;
				return NULL;
			}
			s->pigment = vec3(sVals[0], sVals[1], sVals[2]);
		}

		if(tok == "finish")
		{
			vector<float> fVals;
			fVals = Parse::getFloats(buf);

			s->ambient = 0.f;
			s->diffuse = 0.f;
			s->specular = 0.f;
			s->roughness = 0.f;

			if(fVals.size() == 2)
			{
				s->ambient = fVals[0];
				s->diffuse = fVals[1];
			}
			else if(fVals.size() == 3)
			{
				s->ambient = fVals[0];
				s->diffuse = fVals[1];
				s->specular = fVals[2];
			}
			else if(fVals.size() == 4)
			{
				s->ambient = fVals[0];
				s->diffuse = fVals[1];
				s->specular = fVals[2];
				s->roughness = fVals[3];
			}
			else if(fVals.size() == 5)
			{
				s->ambient = fVals[0];
				s->diffuse = fVals[1];
				s->specular = fVals[2];
				s->roughness = fVals[3];
				s->ior = fVals[4];
			}
			else
			{
				cout << "Malformed sphere finish in POV file." << endl;
				return NULL;
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
			vector<float> pVals;
			pVals = Parse::getFloats(buf);

			if(pVals.size() > 3 || pVals.size() < 3)
			{
				cout << "Malformed Plane Pigment in POV file." << endl;
				return NULL;
			}
			p->pigment = vec3(pVals[0], pVals[1], pVals[2]);
		}

		if(tok == "finish")
		{
			vector<float> pVals;
			pVals = Parse::getFloats(buf);

			p->ambient = 0.f;
			p->diffuse = 0.f;
			p->specular = 0.f;
			p->roughness = 0.f;

			if(pVals.size() == 2)
			{
				p->ambient = pVals[0];
				p->diffuse = pVals[1];
			}
			else if(pVals.size() == 3)
			{
				p->ambient = pVals[0];
				p->diffuse = pVals[1];
				p->specular = pVals[2];
			}
			else if(pVals.size() == 4)
			{
				p->ambient = pVals[0];
				p->diffuse = pVals[1];
				p->specular = pVals[2];
				p->roughness = pVals[3];
			}
			else if(pVals.size() == 5)
			{
				p->ambient = pVals[0];
				p->diffuse = pVals[1];
				p->specular = pVals[2];
				p->roughness = pVals[3];
				p->ior = pVals[4];
			}
			else
			{
				cout << "Malformed Plane Finish in POV file." << endl;
				return NULL;
			}
		}
		buf = "";	
	}

	return p;
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
				Sphere *s = sphereInsertion(FileHandle, holdBuf);
				objs.push_back(s);
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
			}
			else if (token == "triangle")
			{
				Triangle *triangle = triangleInsertion(FileHandle, holdBuf);
				objs.push_back(triangle);
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


