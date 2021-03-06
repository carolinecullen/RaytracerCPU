#include "BBH.hpp"
#include <algorithm>
#include <vector>

using namespace glm;

BBH::BBH(vec3 min, vec3 max) 
{
    updateBox(min, max);
}


void BBH::AddPoint(vec3 point) 
{
   if(!this->init()) 
   {
      updateBox(point, point);
      return;
   }

   this->min.x = std::min(point.x, this->min.x);
   this->min.y = std::min(point.y, this->min.y);
   this->min.z = std::min(point.z, this->min.z);
   this->max.x = std::max(point.x, this->max.x);
   this->max.y = std::max(point.y, this->max.y);
   this->max.z = std::max(point.z, this->max.z);

   updateBox(this->min, this->max);
}

void BBH::Reset(vec3 point)
{
    this->min = this->max = point;
}

void BBH::AddBox(BBH &box) 
{

    AddPoint(box.min);
    AddPoint(box.max);

}

