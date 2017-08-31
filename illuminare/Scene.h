#ifndef SCENE_H
#define SCENE_H

#define NUM 100

#include "Basics.h"
#include "Geometry.h"
#include <vector>

class Scene
{
public:
	Scene() {num = 0;}
	void add(Geometry *item) {/*objects.push_back(item)*/objects[num++]=item;}
	void getIntersection(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj, bool shadow = false);
private:
	//std::vector<Geometry*> objects;
	Geometry* objects[NUM];
	int num;
};
#endif