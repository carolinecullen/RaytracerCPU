#include "Parse.hpp"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <stdio.h>
#include <string.h>
#include "Tracer.hpp"
#include "Diagnostic.hpp"

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
	int flagParam = 0;
	int gi_samples = 0;
	bool Bounding = false;
	if(strcmp(argv[1], "render") == 0)
	{
		if(argc == 6 || argc == 5 || argc == 7)
		{
			if(argc == 6 || argc==7)
			{
				string flag(argv[5]);
				if(argv[5][0] == '-')
				{

					flag = flag.substr(1);
					if(flag.compare("fresnel") == 0)
						flagParam = 1;
					else if(flag.compare("beers") == 0)
						flagParam = 2;
					else if(flag.compare("sds") == 0)
					{
						Bounding = true;
						flagParam = 3;
					}
					else if(flag.compare("gi") == 0)
					{
						flagParam = 4;
						if(argc == 7)
						{
							string flagGI(argv[6]);
							flagGI = flagGI.substr(1);
							if(argv[6][0] == '-')
							{
								string flagGIcheck = flagGI.substr(0, 11);
								if(flagGIcheck.compare("gi_samples=") == 0)
								{
									gi_samples = stoi(flagGI.substr(11));
								}
							}
						}
						
					}

					if(flag.find("ss") != -1)
					{
						int sspos = flag.find("=");
						int ssint = 0;
						ssint = flag.at(sspos+1)-'0';
						Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
						tracer->traceRaysSuper(ssint);
						return 0;
					}
				}
				else
				{
					cout << "Invalid arguments: flags require a '-' command" << endl;
					return -1;
				}
			}

			if(!Parse::tokenParser(argv[2], s, Bounding))
			{
				return -1;
			}

			Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
			tracer->traceRays(flagParam, gi_samples);
		}
		else
		{
			cout << "Invalid run commands: ./raytrace render <input_filename> <width> <height>" << endl;
			return -1;
		}
	}
	else if(strcmp(argv[1], "raycast") == 0)
	{
		if(argc != 5)
		{
			cout << "Invalid run commands: ./raytrace raycast <input_filename> <width> <height>" << endl;
			return -1;
		}

		if(!Parse::tokenParser(argv[2], s, false))
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

		if(!Parse::tokenParser(argv[2], s, false))
		{
			return -1;
		}

		Diagnostic *diag = new Diagnostic(s, 0, 0);
		diag->sceneInfo();

	}
	else if(strcmp(argv[1], "pixelray") == 0)
	{
		if(argc != 7)
		{
			cout << "Invalid run commands: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}

		if(!Parse::tokenParser(argv[2], s, false))
		{
			return -1;
		}

		Diagnostic *diag = new Diagnostic(s, stoi(argv[3]), stoi(argv[4]));
		diag->pixelRay(stoi(argv[5]), stoi(argv[6]));
	}
	else if(strcmp(argv[1], "firsthit") == 0)
	{
		if(argc != 7)
		{
			cout << "Invalid run commands: ./raytrace firsthit <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}

		if(!Parse::tokenParser(argv[2], s, false))
		{
			return -1;
		}

		Diagnostic *diag = new Diagnostic(s, stoi(argv[3]), stoi(argv[4]));
		ray * r= NULL;
		unsigned char * c= NULL;
		diag->firstHit(stoi(argv[5]), stoi(argv[6]), true, r, c);

	}
	else if(strcmp(argv[1], "pixelcolor") == 0)
	{
		if(argc == 8 || argc == 7)
		{
			if(!Parse::tokenParser(argv[2], s, false))
			{
				return -1;
			}

			Diagnostic *diag = new Diagnostic(s, stoi(argv[3]), stoi(argv[4]));
			diag->pixelColor(stoi(argv[5]), stoi(argv[6]));
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
			if(!Parse::tokenParser(argv[2], s, false))
			{
				return -1;
			}

			Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
			tracer->printrays(stoi(argv[5]), stoi(argv[6]));
		}
		else
		{
			cout << "Invalid run commands: ./raytrace printrays <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}

		
	}
	else
	{
		cout << "Invalid command: use pixelcolor, render, raycast, sceneinfo, pixelray, firsthit run with proper parameters." << endl;
		return -1;
	}


}

