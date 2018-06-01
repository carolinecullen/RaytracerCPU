#include "BBHTree.hpp"
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
        cur->boundBox.AddBox(&cur->boundBox);
        return;
    }

    sortObjects(objs, axis);

    cur->left = new BNode;
    vector<Object *> left_half(objs.begin(), (objs.begin()+objs.size()/2));
    makeSDS(left_half, cur->left, (axis+1) % 3);

    cur->right = new BNode;
    vector<Object *> right_half((objs.begin()+objs.size()/2), objs.end());
    makeSDS(right_half, cur->right, (axis+1) % 3);

    cur->boundBox.AddBox(&cur->boundBox);
}


void BBHTree::sortObjects(vector<Object *> objs, int axis) 
{
    cout << objs.size() << endl;
   for (int i = 1; i < objs.size(); i++) 
   {
        float key = objs[i]->getCenter()[axis];
        // cout << objs[i]->type << endl;
        // if(objs[i]->type == "Box")
        // {
        //     Box* b = (Box*)objs[i];
        //     cout << b->min.x << endl;
        // }
        // cout << "center: " << objs[i]->getCenter()[0] << objs[i]->getCenter()[1] << objs[i]->getCenter()[2] << endl; 
        int j = i-1;

        while(j>=0 && (objs[i]->getCenter()[axis] > key))
        {
            objs[j+1] = objs[j];
            j = j-1;
        }

        objs[j+1] = objs[key];
    }


    // for (int i = 0; i < objs.size(); i++)
    // {
    //     cout << "obj center on axis " << axis << " " << objs[i]->getCenter()[axis] << endl;
    // }
}

Object* BBHTree::treeDecend(BNode *node, const ray &ray) 
{
	if (node->objs.size() == 1) 
    {
		return node->objs[0];
	}
	
	if (node->boundBox.intersect(ray) > 0.001f) 
    {
		if (node->left != NULL) 
        {
			return treeDecend(node->left, ray);
		}
		if (node->right != NULL) 
        {
			return treeDecend(node->right, ray);
		}
	}

	return NULL;
}


