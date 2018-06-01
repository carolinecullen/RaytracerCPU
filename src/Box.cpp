#include "Box.hpp"
#include "BBH.hpp"
using namespace std;
using namespace glm;

Box::Box()
{
    this->normal = vec3(0.f);
    this->roughness = 0.f;
    this->ior = 0.f;
    this->specular = 0.f;
    this->ambient = 0.f;
    this->diffuse = 0.f;
    this->reflection = 0.f;
    this->refraction = 0.f;
    this->pigment = vec3(-1.0f);
    this->filter = 0.f;
    this->id = -1;
    this->IM = mat4(1.f);

    float highestFloat = numeric_limits<float>::max();
    this->min = vec3(highestFloat);
    this->max = vec3(highestFloat); 
}

BBH* Box::makeBoundingBox()
{ 
    return new BBH(min, max); 
}

void Box::updateBox(vec3 min, vec3 max) 
{
    this->min = min;
    this->max = max;
}

vec3 Box::getCenter() 
{
    // cout << "min " << min.x << endl;
    // cout << "max " << max.x << endl;
    // cout << (max.x+min.x)/2 << endl;
    // cout << vec3((float)((max.x+min.x)/2.f), (float)((max.y+min.y)/2.f), (float)((max.z+min.z)/2.f)).x << endl;

    return vec3((float)((max.x+min.x)/2.f), (float)((max.y+min.y)/2.f), (float)((max.z+min.z)/2.f));
}

float Box::intersect(const ray &ray) 
{

    float tgmin = -numeric_limits<float>::max();
    float tgmax =  numeric_limits<float>::max();

    if (!this->init()) 
    {
        return -1;
    }

    for (int i = 0; i < 3; i++) 
    {
        if (isParallel(this, ray, i)) 
        {
            return -1;
        }
        else
        {
            updateVals(ray, tgmin, tgmax, i);
        }
    }

    if ((tgmax<0) || (tgmin>tgmax)) 
    {
        return -1;
    }
    else if (tgmin > 0) 
    {
        return tgmin;
    }
    else 
    {   
        return tgmax;
    }
}

bool Box::isParallel(Box* b, const ray &ray, int a)
{
    if(ray.direction[a] == 0)
    {
        if((ray.location[a] > b->min[a]) || (ray.location[a] < b->max[a]))
        {
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

void Box::updateVals(const ray &ray, float &tgmin, float &tgmax, int a) 
{
    float t1 = (this->min[a] - ray.location[a])/ray.direction[a];
    float t2 = (this->max[a] - ray.location[a])/ray.direction[a];

    if (t1 > t2) 
    {
        swap(t1, t2);
    }
    if (t2 < tgmax) 
    {
        tgmax = t2;
    }
    if (t1 > tgmin) 
    {
        tgmin = t1;
    }
  
}

void Box::calcNormal(vec3 pt)
{

    if (Equals(pt.x, min.x, 0.001f))
        this->normal = vec3(-1, 0, 0);
    else if (Equals(pt.x, max.x, 0.001f))
        this->normal = vec3(1, 0, 0);
    else if (Equals(pt.y, min.y, 0.001f))
        this->normal = vec3(0, -1, 0);
    else if (Equals(pt.y, max.y, 0.001f))
        this->normal = vec3(0, 1, 0);
    else if (Equals(pt.z, min.z, 0.001f))
        this->normal = vec3(0, 0, -1);
    else if (Equals(pt.z, max.z, 0.001f))
        this->normal = vec3(0, 0, 1);
}

bool Box::init() 
{
    if (this->max[0] < numeric_limits<float>::max())
        return true;
    else 
        return false;
}

bool Box::Equals(float const a, float const b, float const epsilon)
{
    return abs(a - b) < epsilon;
}

void Box::print()
{
  cout << "- Type: " <<  type << endl;
  cout << "- Min: {" << min.x << " " << min.y << " " << min.z << "}" << endl;
  cout << "- Max: {" << max.x << " " << max.y << " " << max.z << "}" << endl;
  cout << "- Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
  cout << "- Color: {" << pigment.x << " " << pigment.y << " " << pigment.z << "}" << endl;
  cout << "- Material: " << endl << "  - Ambient: " << ambient << endl << "  - Diffuse: " << diffuse << endl << "  - Specular: " << specular << endl << "  - Roughness: " << roughness << endl << "  - IOR: " << ior << endl << "  - Reflection: " << reflection << endl << "  - Refraction: " << refraction << endl;
  cout << " - Model Transform: " << endl;
  cout << "  " << IM[0][0] << " " << IM[1][0] << " " << IM[2][0] << " " << IM[3][0] << endl;
  cout << "  " << IM[0][1] << " " << IM[1][1] << " " << IM[2][1] << " " << IM[3][1] << endl;
  cout << "  " << IM[0][2] << " " << IM[1][2] << " " << IM[2][2] << " " << IM[3][2] << endl;
  cout << "  " << IM[0][3] << " " << IM[1][3] << " " << IM[2][3] << " " << IM[3][3] << endl;
  cout << endl;
  
}


