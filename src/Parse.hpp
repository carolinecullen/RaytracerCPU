#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Lighting.hpp"

class Parse
{

	public:

		Parse() {}

		// static members are independant of objects and can be called with the :: operator 

		static bool tokenParser(std::string);

		static Camera* placeCamera(std::ifstream &);

		static std::string tokenizeHelper(std::ifstream &, std::string &);

		static std::vector<float> getFloats(std::string);

		static Lighting* lightInsertion(std::string);

};