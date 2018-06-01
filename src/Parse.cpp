#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "Parse.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"	
#include "Triangle.hpp"
#include "glm/gtc/matrix_transform.hpp"	
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
			return cam;
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

	vector<float> checkFirstLine;
	checkFirstLine = Parse::getFloats(line);

	if(checkFirstLine.size() > 0)
	{
		for(int i = 0; i < checkFirstLine.size(); i++)
		{
			aVals.push_back(checkFirstLine[i]);
		}
	}

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{
		if(tok == "pigment")
		{
			parse_triangle_pigment(t, buf);
		} 

		if(tok == "scale")
		{
			vector<float> nums;
			nums = Parse::getFloats(buf);
			vec3 s = vec3(nums[0], nums[1], nums[2]);
			t->M = scale(mat4(1.0f), s) * t->M;
		}

		if(tok == "rotate")
		{
			vector<float> nums;
			nums = Parse::getFloats(buf);
			vec3 r = vec3(radians(nums[0]), radians(nums[1]), radians(nums[2]));
         	t->M = glm::rotate(mat4(1.0f), r.z, vec3(0, 0, 1)) * t->M;
         	t->M = glm::rotate(mat4(1.0f), r.y, vec3(0, 1, 0)) * t->M;
			t->M = glm::rotate(mat4(1.0f), r.x, vec3(1, 0, 0)) * t->M;
		}

		if(tok == "translate")
		{
			vector<float> nums;
			nums = Parse::getFloats(buf);
			vec3 tr = vec3(nums[0], nums[1], nums[2]);
			t->M = translate(mat4(1.0f), tr) * t->M;
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

	t->A = vec3(aVals[0], aVals[1], aVals[2]);
	t->B = vec3(aVals[3], aVals[4], aVals[5]);
	t->C = vec3(aVals[6], aVals[7], aVals[8]);

	t->IM = inverse(t->M);
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
		vector<float> fNums;
		if(tok == "pigment")
		{
			parse_sphere_pigment(s, buf);
		}

		if(tok == "scale")
		{
			fNums = Parse::getFloats(buf);
			vec3 sc = vec3(fNums[0], fNums[1], fNums[2]);
			s->M = scale(mat4(1.0f), sc) * s->M;
		}

		if(tok == "rotate")
		{
			fNums = Parse::getFloats(buf);
			vec3 r = vec3(radians(fNums[0]), radians(fNums[1]), radians(fNums[2]));
         	s->M = rotate(mat4(1.0f), r.z, vec3(0, 0, 1)) * s->M;
         	s->M = rotate(mat4(1.0f), r.y, vec3(0, 1, 0)) * s->M;
			s->M = rotate(mat4(1.0f), r.x, vec3(1, 0, 0)) * s->M;
		}

		if(tok == "translate")
		{
			fNums = Parse::getFloats(buf);
			vec3 t = vec3(fNums[0], fNums[1], fNums[2]);
			s->M = translate(mat4(1.0f), t) * s->M;
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

		buf = "";	
	}

	s->IM = inverse(s->M);

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
		vector<float> fNums;
		if(tok == "pigment")
		{
			parse_plane_pigment(p, buf);
		}

		if(tok == "scale")
		{
			fNums = Parse::getFloats(buf);
			vec3 s = vec3(fNums[0], fNums[1], fNums[2]);
			p->M = glm::scale(mat4(1.0f), s) * p->M;
		}

		if(tok == "rotate")
		{
			fNums = Parse::getFloats(buf);
			vec3 rotation = vec3(radians(fNums[0]), radians(fNums[1]), radians(fNums[2]));
         	p->M = rotate(mat4(1.0f), rotation.z, vec3(0.f, 0.f, 1.f)) * p->M;
         	p->M = rotate(mat4(1.0f), rotation.y, vec3(0.f, 1.f, 0.f)) * p->M;
			p->M = rotate(mat4(1.0f), rotation.x, vec3(1.f, 0.f, 0.f)) * p->M;
		}

		if(tok == "translate")
		{
			fNums = Parse::getFloats(buf);
			vec3 t = vec3(fNums[0], fNums[1], fNums[2]);
			p->M = translate(mat4(1.0f), t) * p->M;
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

	p->IM = inverse(p->M);

	return p;
}

Box* Parse::boxInsertion(ifstream &FileHandle, string line)
{
	Box* b = new Box();
	b->type = "Box";
	vector<float> bVals = Parse::getFloats(line);
	b->min = vec3(bVals[0], bVals[1], bVals[2]);
	b->max = vec3(bVals[3], bVals[4], bVals[5]);

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{
		vector<float> fNums;
		if(tok == "pigment")
		{
			parse_box_pigment(b, buf);
		}

		if(tok == "scale")
		{
			fNums = Parse::getFloats(buf);
			vec3 s = vec3(fNums[0], fNums[1], fNums[2]);
			b->M = glm::scale(mat4(1.0f), s) * b->M;
		}

		if(tok == "rotate")
		{
			fNums = Parse::getFloats(buf);
			vec3 rotation = vec3(radians(fNums[0]), radians(fNums[1]), radians(fNums[2]));
         	b->M = rotate(mat4(1.0f), rotation.z, vec3(0.f, 0.f, 1.f)) * b->M;
         	b->M = rotate(mat4(1.0f), rotation.y, vec3(0.f, 1.f, 0.f)) * b->M;
			b->M = rotate(mat4(1.0f), rotation.x, vec3(1.f, 0.f, 0.f)) * b->M;
		}

		if(tok == "translate")
		{
			fNums = Parse::getFloats(buf);
			vec3 t = vec3(fNums[0], fNums[1], fNums[2]);
			b->M = translate(mat4(1.0f), t) * b->M;
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
			parse_box_finish(b, buf);
			if(flag)
			{
				return b;
			}
		}
		buf = "";	
	}

	b->IM = inverse(b->M);

	return b;
}

void Parse::parse_box_pigment(Box *box, string buf)
{
	vector<float> nums;
	nums = Parse::getFloats(buf);

	istringstream iss(buf);

	int i = 0;
	for(string s; iss >> s; )
	{
		if(s == "rgb")
		{
			box->pigment = vec3(nums[0], nums[1], nums[2]);
			i++;
		}
		else if(s == "rgbf")
		{
			box->pigment = vec3(nums[0], nums[1], nums[2]);
			box->filter = nums[3];
			i++;
		}
		else if(s == "rgba")
		{
			box->pigment = vec3(nums[0], nums[1], nums[2]);
			box->filter = nums[3];
			i++;
		}
	}
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

void Parse::parse_box_finish(Box *b, string buf)
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
			b->ambient = nums[i];
			i++;
		}
		else if(s == "diffuse")
		{
			b->diffuse = nums[i];
			i++;
		}
		else if(s == "specular")
		{
			b->specular = nums[i];
			i++;
		}
		else if(s == "ior")
		{
			b->ior = nums[i];
			i++;
		}
		else if(s == "reflection")
		{
			b->reflection = nums[i];
			i++;
		}
		else if(s == "refraction")
		{
			b->refraction = nums[i];
			i++;
		}
		else if(s == "roughness")
		{
			b->roughness = nums[i];
			i++;
		}
	}
}

bool Parse::tokenParser(string fName, Scene *scene, bool bound)
{
	ifstream FileHandle("../resources/" + fName);
	Camera *cam;
	vector<Lighting *> allLights;
	std::vector<Object *> objects;
	vector<Object *> planes;

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
				objects.push_back(sphere);
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
				plane->id = i;
				if(bound)
				{
					planes.push_back(plane);
				}
				else
				{
					objects.push_back(plane);
				}
				i++;
			}
			else if (token == "box")
			{
				Box *box = boxInsertion(FileHandle, holdBuf);
				objects.push_back(box);
				box->id = i;
				i++;
			}
			else if (token == "triangle")
			{
				Triangle *triangle = triangleInsertion(FileHandle, holdBuf);
				objects.push_back(triangle);
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

	if(bound)
	{
		scene->sceneObjects = planes;
		BBHTree *bbhPtr = scene->bht;
		bbhPtr->makeSDS(objects, bbhPtr->rootBox, 0);
	}
	else
	{
		scene->sceneObjects = objects;
	}

	scene->cam = cam;
	scene->lights = allLights;
	

	return true;
}


