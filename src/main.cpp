#include "Parse.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <stdio.h>
#include <string.h>
#include "Tracer.hpp"

using namespace std;
using namespace glm;

int main(int argc, char** argv)
{
	if(argc < 3 || argc > 7)
	{
		cout << "Invalid run commands." << endl;
		cout << "Choose raycast, sceneinfo, pixelray, firsthit with the proper parameters." << endl;
		return -1;
	}

	cout << std::setiosflags(std::ios::fixed);
   	cout << std::setprecision(4);
   	
	Scene *s = new Scene();

	if(strcmp(argv[1], "raycast") == 0)
	{
		if(argc != 5)
		{
			cout << "Invalid run commands: ./raytrace raycast <input_filename> <width> <height>" << endl;
			return -1;
		}

		if(!Parse::tokenParser(argv[2], s))
		{
			return -1;
		}

		Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
		tracer->castRays();
	}
	else if(strcmp(argv[1], "sceneinfo") == 0)
	{
		if(argc != 3)
		{
			cout << "Invalid run commands: ./raytrace sceneinfo <input_filename>" << endl;
			return -1;
		}

		if(!Parse::tokenParser(argv[2], s))
		{
			return -1;
		}

		s->cam->printCamera();
		cout << s->lights.size() << " light(s)" << endl << endl;
		int i = 0;
		for(auto l: s->lights)
		{
			cout << "Light[" << i << "]:" << endl;
			l->printLight();
			i++;
		}

		cout << s->sceneObjects.size() << " object(s)" << endl << endl;
		i = 0;
		for(auto so: s->sceneObjects)
		{
			cout << "Object[" << i << "]:" << endl;
			so->print();
			i++;
		}
	}
	else if(strcmp(argv[1], "pixelray") == 0)
	{
		if(argc != 7)
		{
			cout << "Invalid run commands: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}

		if(!Parse::tokenParser(argv[2], s))
		{
			return -1;
		}

		Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
		tracer->pixelRay(stoi(argv[5]), stoi(argv[6]));
	}
	else if(strcmp(argv[1], "firsthit") == 0)
	{
		if(argc != 7)
		{
			cout << "Invalid run commands: ./raytrace firsthit <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}

		if(!Parse::tokenParser(argv[2], s))
		{
			return -1;
		}

		Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
		ray * r= NULL;
		unsigned char * c= NULL;
		tracer->firstHit(stoi(argv[5]), stoi(argv[6]), true, r, c);
	}
	else if(strcmp(argv[1], "render") == 0)
	{
		if(argc == 6 || argc == 5)
		{
			if(!Parse::tokenParser(argv[2], s))
			{
				return -1;
			}

			Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
			tracer->traceRays();
		}
		else
		{
			cout << "Invalid run commands: ./raytrace render <input_filename> <width> <height>" << endl;
			return -1;
		}
	}
	else if(strcmp(argv[1], "pixelcolor") == 0)
	{
		if(argc == 8 || argc == 7)
		{
			if(!Parse::tokenParser(argv[2], s))
			{
				return -1;
			}

			Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
			tracer->pixelColor(stoi(argv[5]), stoi(argv[6]));
		}
		else
		{
			cout << "Invalid run commands: ./raytrace render <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}

		
	}
	else if(strcmp(argv[1], "printrays") == 0)
	{
		if(argc == 8 || argc == 7)
		{
			if(!Parse::tokenParser(argv[2], s))
			{
				return -1;
			}

			Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
			tracer->pixelColor(stoi(argv[5]), stoi(argv[6]));
		}
		else
		{
			cout << "Invalid run commands: ./raytrace render <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}

		
	}
	else
	{
		cout << "Invalid command: use pixelcolor, render, raycast, sceneinfo, pixelray, firsthit run with proper parameters." << endl;
		return -1;
	}


}

