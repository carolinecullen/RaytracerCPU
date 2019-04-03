#include "Parse.hpp"
#include <iostream>
#include <string>
#include "../glm/glm/glm.hpp"
#include <stdio.h>
#include <string.h>
#include "Tracer.hpp"
#include "Diagnostic.hpp"

using namespace std;
using namespace glm;

int main(int argc, char** argv)
{
	if(argc < 3 || argc > 10)
	{
		cout << "Invalid run commands." << endl;
		cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
		return -1;
	}

	cout << std::setiosflags(std::ios::fixed);
   	cout << std::setprecision(4);
   	
	Scene *s = new Scene();
	int flagParam = 0;
	int gi_samples = 64;
	bool Bounding = false;
	string output = "";
	glm::vec3 cameraPos;
	if(strcmp(argv[1], "render") == 0)
	{
		if(argc == 5 || argc == 6 || argc == 7 || argc==8 || argc==9 || argc == 10)
		{
			if(argc > 5)
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
					else if(flag.compare("focal") == 0)
					{
						flagParam = 5;
						float aperture = 0.f;
						float focal = 0.f;
						vector<float> camVals;

						if(argc < 8)
						{
							cout << "expected focal length and aperture size" << endl;
						}
						else
						{
							string flagGI(argv[6]);
							flagGI = flagGI.substr(1);
							if(argv[6][0] == '-')
							{
								string flagGIcheck = flagGI.substr(0, 12);
								if(flagGIcheck.compare("focalLength=") == 0)
								{
									focal = stof(flagGI.substr(12));
								}
								flagGIcheck = flagGI.substr(0, 9);
								if(flagGIcheck.compare("aperture=") == 0)
								{
									aperture = stof(flagGI.substr(9));
								}
							}

							string newflagGI(argv[7]);
							newflagGI = newflagGI.substr(1);
							if(argv[7][0] == '-')
							{
								string flagGIcheck = newflagGI.substr(0, 12);
								if(flagGIcheck.compare("focalLength=") == 0)
								{
									focal = stof(newflagGI.substr(12));
								}
								flagGIcheck = newflagGI.substr(0, 9);
								if(flagGIcheck.compare("aperture=") == 0)
								{
									aperture = stof(newflagGI.substr(9));
								}
							}

							if(argc >= 9)
							{
								if(argv[8][0] == '-')
								{
									string newflagGI(argv[8]);
									string flagGIcheck = newflagGI.substr(0, 8);
									if(flagGIcheck.compare("-output=") == 0)
									{
										output = newflagGI.substr(8);
									}
								}
							}

							// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							// ALWAYS MAKE SURE THAT CAMERA TWO IS LAST PARAMETER
							if(argc >= 10)
							{
								if(argv[9][0] == '-')
								{
									string newflagGI(argv[9]);
									string flagGIcheck = newflagGI.substr(0, 8);
									if(flagGIcheck.compare("-camera=") == 0)
									{
										camVals = Parse::getFloats(newflagGI.substr(8));
										if (camVals.size() == 3)
										{
											cameraPos = vec3(camVals[0], camVals[1], camVals[2]);
										}
										else
										{
											cout << "Invalid camera values" << endl;
										}
									}
								}
							}

							

							s->aperture = aperture;
							s->focalLength = focal;
						}
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

					string flagGIcheck = flag.substr(0, 3);
					if(flagGIcheck.compare("ss=") == 0)
					{
						if(!Parse::tokenParser(argv[2], s, false))
						{
							return -1;
						}
						int ssInt = stoi(flag.substr(3));
						Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
						tracer->traceRaysSuper(ssInt);
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

			if(flagParam == 5 && argc >= 10)
			{
				s->cam->location.x = cameraPos.x;
				s->cam->location.y = cameraPos.y;
				s->cam->location.z = cameraPos.z;
			}
			
			Tracer *tracer = new Tracer(s, stoi(argv[3]), stoi(argv[4]));
			tracer->traceRays(flagParam, gi_samples, output);
		}
		else
		{
			cout << "Invalid run commands." << endl;
			cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
			return -1;
		}
	}
	else if(strcmp(argv[1], "raycast") == 0)
	{
		if(argc != 5)
		{
			cout << "Invalid run commands." << endl;
			cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
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
			cout << "Invalid run commands." << endl;
			cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
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
			cout << "Invalid run commands." << endl;
			cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
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
			cout << "Invalid run commands." << endl;
			cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
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
			cout << "Invalid run commands." << endl;
			cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
			return -1;
		}

		
	}
	else
	{
		cout << "Invalid run commands." << endl;
		cout << "Usage: \n\t./raytrace render <file.pov> <width> <height> [optional flags]\n\t./raytrace sceneinfo <input_filename>\n\t./raytrace pixelray <input_filename> <width> <height> <x> <y>\n\t./raytrace firsthit <input_filename> <width> <height> <x> <y>\n" << endl;
		return -1;
	}


}

