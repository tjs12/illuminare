#ifndef LOCALLIGHT_H
#define LOCALLIGHT_H
#include <opencv2\core\core.hpp>
#include "Basics.h"
#include "Scene.h"

#define LNUM 100
class LocalLight
{
public:
	double Kdr, Kdg, Kdb;
	point Sources[LNUM];//光源
	int lnum;//光源数目
	cv::Scalar GetColor(Scene &scene, Geometry *obj, point &n, point &p, point &vp) ;
	void GetColor1(Scene &scene, Geometry *obj, point &n, point &p, point &vp, cv::Scalar &res) ;//获得物体在光照下的颜色；这行的返回值改为引用传值，希望能快一点
	LocalLight() {Kdr = 0.5; Kdg = 0.5; Kdb = 0.5;lnum=0;}
	void addLight(point item){Sources[lnum++] = item;}
private:
	bool isShadow(Scene &scene, point p, point light);//判断是否是阴影
};

#endif