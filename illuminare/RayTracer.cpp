#include "RayTracer.h"
#include <iostream>

using namespace cv;
using namespace std;

Scalar RayTracer::RayTrace(Ray &r, double weight)
{
	if (weight < MinWeight) {
		return Scalar(0,0,0);//权值过小，不再继续
	}
	else {
		/*point current_p, nearest_p, current_n, nearest_n;
		bool valid = false , first = true;
		Geometry *obj;
		for (vector<Geometry*>::iterator i = objects.begin(); i != objects.end(); i++) {
			(*i)->Intersect(r, current_p, current_n, valid);
			if (valid) {
				if ((first || point::Distance2(current_p,r.start) < point::Distance2(nearest_p,r.start)) && point::Distance2(current_p, r.start) > 0.0001) {
					first = false;
					nearest_p = current_p;
					nearest_n = current_n;
					obj = (*i);
				}
			}
		}
		if (first) 
			return Scalar(0,0,0);*/
		Geometry *obj;
		point nearest_p, nearest_n;
		scene.getIntersection(r, nearest_p, nearest_n, obj);//求交点
		if (obj == 0)
			return Scalar(0,0,0);//没有和任何物体相交
		else {
			Scalar Ilocal;
			//Ilocal = local.GetColor(scene, obj, nearest_n, nearest_p, r.start);
			local.GetColor1(scene, obj, nearest_n, nearest_p, r.start, Ilocal);//得到颜色
			/*point R = r.direction - 2 * point::DotProduct(r.direction, nearest_n) * nearest_n;
			R.Normalize();*/
			Ray ref;//反射
			//ref.direction = R;
			ref.direction = r.direction - 2 * point::DotProduct(r.direction, nearest_n) * nearest_n;
			ref.direction.Normalize();
			ref.start = nearest_p;

			Scalar Ir = RayTrace(ref, weight * obj -> wr);

			Ray tr;//折射
			bool valid_t = true;
			getRefraction(r, nearest_p, nearest_n, obj, tr, valid_t);
			Scalar It = valid_t ? RayTrace(tr, weight * obj ->wt) : Scalar(0,0,0);
			
			return (Ilocal*(1 - obj -> wr - (valid_t? obj -> wt : 0)) + obj -> wr * Ir + obj -> wt * It);///(Ir == Scalar(0,0,0) ? 1 : 2);
			//return (Ilocal + obj -> wr * Ir + obj -> wt * It);
		}
	}
}

void RayTracer::getIntersection(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj)//不用了
{
	obj = 0;
	point current_p, current_n;
	bool valid = false , first = true;
	Scalar Ilocal;
	for (vector<Geometry*>::iterator i = objects.begin(); i != objects.end(); i++) {
		(*i)->Intersect(r, current_p, current_n, valid);
		if (valid) {
			if ((first || point::Distance2(current_p,r.start) < point::Distance2(nearest_p,r.start)) && point::Distance2(current_p, r.start) > 0.0001) {
				first = false;
				nearest_p = current_p;
				nearest_n = current_n;
				obj = (*i);
			}
		}
	}

}

void RayTracer::getRefraction(Ray &r, point &nearest_p, point &nearest_n, Geometry *&obj, Ray &r1, bool &valid)
{
	double nr = (point::DotProduct(nearest_n, r.direction) > 0.0001) ? 1 / obj -> nr : obj -> nr;
	point n = (point::DotProduct(nearest_n, r.direction) > 0.0001) ? -1 * nearest_n: nearest_n;
	double costhi = -point::DotProduct(n, r.direction);
	if (1 - nr * nr * (1 - costhi * costhi) < 0.0001) {
		valid = false;
		return;
	}
	if (obj -> wt !=0 && point::DotProduct(nearest_n, r.direction) > 0.0001) {
		int a;
		a = 1;
	}
	double cost = sqrt(1 - nr * nr * (1 - costhi * costhi));
	point T = nr * r.direction + (nr * (-point::DotProduct(/*nearest_*/n, r.direction) - cost)) * /*nearest_*/n;
	T.Normalize();
	r1.direction = T;//r.direction;
	r1.start = nearest_p;
	valid = true;
}