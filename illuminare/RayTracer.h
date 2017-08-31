#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Basics.h"
#include "Geometry.h"
#include "Scene.h"
#include "LocalLight.h"
#include <opencv2\core\core.hpp>
#include <vector>

class RayTracer
{
public:
	cv::Scalar RayTrace(Ray &r, double weight);
	Scene scene;//场景
	std::vector<Geometry*> objects;//这个现在不用了，被scene取代了
	double MinWeight;
	LocalLight local;
	void getIntersection(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj);//这个现在不用了，同上
private:
	void getRefraction(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj, Ray &r1, bool &valid);//计算折射光线
};

#endif
