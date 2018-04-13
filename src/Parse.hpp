#include <string>
#include <sstream>
#include <glm/glm.hpp>
// #include <vector>
#include "Camera.hpp"
#include "Lighting.hpp"
#include "Sphere.hpp"

using namespace std;

class Parse
{

	public:

		Parse() {}

		// static members are independant of objects and can be called with the :: operator 

		static bool tokenParser(std::string);

		static Camera* placeCamera(std::ifstream &);

		static std::string tokenizeHelper(std::ifstream &, std::string &);

		static vector<float> getFloats(std::string);

		static Lighting* lightInsertion(std::string);

		static Sphere* sphereInsertion(std::ifstream &, std::string line);

};