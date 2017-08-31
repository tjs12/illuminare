#include "Scene.h"
#include <opencv2\core\core.hpp>

#define OCTREE true

using namespace cv;

void Scene::getIntersection(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj, bool shadow)
{
	obj = 0;
	point current_p, current_n;
	bool valid = false , first = true;
	Scalar Ilocal;
	//for (vector<Geometry*>::iterator i = objects.begin(); i != objects.end(); i++) {
	for (int i = 0; i < num; i++) {
		//(*i)->Intersect(r, current_p, current_n, valid);

		if (!OCTREE) {
			objects[i] -> Intersect(r, current_p, current_n, valid);
			if (valid) {
				if ((first || point::Distance2(current_p,r.start) < point::Distance2(nearest_p,r.start)) && point::Distance2(current_p, r.start) > 0.0001) {
					first = false;
					nearest_p = current_p;
					nearest_n = current_n;
					//obj = (*i);
					obj = objects[i];
				}
			}
		}

		else {//using octree
			Geometry *current_obj;
			objects[i] -> Intersect(r, current_p, current_n, valid, current_obj);
			if (valid) {
				if ((first || point::Distance2(current_p,r.start) < point::Distance2(nearest_p,r.start)) && point::Distance2(current_p, r.start) > 0.0001 && (!shadow || current_obj->wt==0)) {
					first = false;
					nearest_p = current_p;
					nearest_n = current_n;
					obj = current_obj;
				}
			}
		}

	}

}