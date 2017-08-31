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
	point Sources[LNUM];//��Դ
	int lnum;//��Դ��Ŀ
	cv::Scalar GetColor(Scene &scene, Geometry *obj, point &n, point &p, point &vp) ;
	void GetColor1(Scene &scene, Geometry *obj, point &n, point &p, point &vp, cv::Scalar &res) ;//��������ڹ����µ���ɫ�����еķ���ֵ��Ϊ���ô�ֵ��ϣ���ܿ�һ��
	LocalLight() {Kdr = 0.5; Kdg = 0.5; Kdb = 0.5;lnum=0;}
	void addLight(point item){Sources[lnum++] = item;}
private:
	bool isShadow(Scene &scene, point p, point light);//�ж��Ƿ�����Ӱ
};

#endif