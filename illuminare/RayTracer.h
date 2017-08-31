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
	Scene scene;//����
	std::vector<Geometry*> objects;//������ڲ����ˣ���sceneȡ����
	double MinWeight;
	LocalLight local;
	void getIntersection(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj);//������ڲ����ˣ�ͬ��
private:
	void getRefraction(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj, Ray &r1, bool &valid);//�����������
};

#endif
