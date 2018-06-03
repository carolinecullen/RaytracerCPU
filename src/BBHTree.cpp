#include "BBHTree.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include <algorithm>
using namespace std;
using namespace glm;


BBHTree::BBHTree() 
{
   this->rootBox = new BNode;
}

void BBHTree::makeSDS(vector<Object *> objs, BNode *cur, int axis) 
{
    if (objs.size() <= 1) 
    {
        cur->objs = objs;
        BBH* bbox = objs[0]->makeBoundingBox();
        cur->boundBox.AddBox(*bbox);
        return;
    }

    sortObjects(objs, axis);

    cur->objs = objs;
    cur->left = new BNode;
    cur->right = new BNode;

    vector<Object *> left_half(objs.begin(), (objs.begin()+objs.size()/2));
    makeSDS(left_half, cur->left, (axis+1) % 3);

    vector<Object *> right_half((objs.begin()+objs.size()/2), objs.end());
    makeSDS(right_half, cur->right, (axis+1) % 3);

    BBH newBox = makeBoundBox(objs, axis);
    cur->boundBox = newBox;
}

BBH BBHTree::makeBoundBox(vector<Object *> objs, int axis)
{
    BBH allBox;
    
    for (int i = 0; i < objs.size(); i++)
    {
        BBH newBox;
        if(objs[i]->type == "Sphere")
        {
            Sphere* sptr = (Sphere *)objs[i];
            newBox.Reset(sptr->center - sptr->radius);
            newBox.AddPoint(sptr->center + sptr->radius);

            // if (newBox->init()) 
            // {
            //     std::vector<vec3> corners;
            //     corners.push_back(vec3(newBox->min.x, newBox->min.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->min.x, newBox->min.y, newBox->max.z));
            //     corners.push_back(vec3(newBox->min.x, newBox->max.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->min.x, newBox->max.y, newBox->max.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->min.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->min.y, newBox->max.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->max.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->max.y, newBox->max.z));

            //     newBox->min = vec3(-numeric_limits<float>::max());
            //     newBox->max = vec3( numeric_limits<float>::max());

            //     for (int i = 0; i < 8; i++) 
            //     {
            //         corners[i] = vec3(this->M * vec4(corners[i], 1.f));
            //         newBox->AddPoint(corners[i]);
            //     }

            //     newBox->updateBox(newBox->min, newBox->max);
            // }
            allBox.AddBox(newBox);
        }
        else if(objs[i]->type == "Triangle")
        {
            Triangle* tptr = (Triangle *)objs[i];
            newBox.Reset(tptr->A);
            newBox.AddPoint(tptr->B);
            newBox.AddPoint(tptr->C);

            // if (newBox->init()) 
            // {
            //     std::vector<vec3> corners;
            //     corners.push_back(vec3(newBox->min.x, newBox->min.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->min.x, newBox->min.y, newBox->max.z));
            //     corners.push_back(vec3(newBox->min.x, newBox->max.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->min.x, newBox->max.y, newBox->max.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->min.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->min.y, newBox->max.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->max.y, newBox->min.z));
            //     corners.push_back(vec3(newBox->max.x, newBox->max.y, newBox->max.z));

            //     newBox->min = vec3(-numeric_limits<float>::max());
            //     newBox->max = vec3( numeric_limits<float>::max());

            //     for (int i = 0; i < 8; i++) 
            //     {
            //         corners[i] = vec3(this->M * vec4(corners[i], 1.f));
            //         newBox->AddPoint(corners[i]);
            //     }

            //     newBox->updateBox(newBox->min, newBox->max);
            // }
            allBox.AddBox(newBox);
        }
        else
        {
            Box* bptr = (Box *)objs[i];
            newBox.AddPoint(bptr->min);
            newBox.AddPoint(bptr->max);
            allBox.AddBox(newBox);
        }
    }
    return allBox;
}
 
void BBHTree::sortObjects(vector<Object *> &objs, int axis) 
{
   if (axis == 0)
   {
    std::sort(objs.begin(), objs.end(), [](Object* a, Object* b) -> bool
        { 
            return a->getCenter()[0] > b->getCenter()[0]; 
        });
   }
   else if (axis == 1)
   {
    std::sort(objs.begin(), objs.end(), [](Object* a, Object* b) -> bool
        { 
            return a->getCenter()[1] > b->getCenter()[1]; 
        });
   }
   else if (axis == 2)
   {
    std::sort(objs.begin(), objs.end(), [](Object* a, Object* b) -> bool
        { 
            return a->getCenter()[2] > b->getCenter()[2]; 
        });
   }
    

}

vector<Object *> BBHTree::treeDecend(BNode *node, const ray &ray) 
{
	if (node->objs.size() == 1) 
    {
		return node->objs;
	}
	
	if (node->boundBox.intersect(ray) != 0) 
    {
		if (node->left != NULL) 
        {
			return treeDecend(node->left, ray);
		}
        else
        {
            return node->objs;
        }
		if (node->right != NULL) 
        {
			return treeDecend(node->right, ray);
		}
        else
        {
            return node->objs;
        }
	}

    vector<Object *> nothing;
	return nothing;
}


