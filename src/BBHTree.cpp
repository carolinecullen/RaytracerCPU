#include "BBHTree.hpp"
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
    // cur->left = new BNode;
    // cur->right = new BNode;

    // vector<Object *> left_half(objs.begin(), (objs.begin()+objs.size()/2));
    // makeSDS(left_half, cur->left, (axis+1) % 3);

    // vector<Object *> right_half((objs.begin()+objs.size()/2), objs.end());
    // makeSDS(right_half, cur->right, (axis+1) % 3);


    // if (cur->left != NULL) 
    // {
    //     cur->boundBox.AddBox(cur->left->boundBox);
    // }
    // if (cur->right != NULL) 
    // {
    //     cur->boundBox.AddBox(cur->right->boundBox);
    // }  
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
	
	if (node->boundBox.intersect(ray)) 
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


