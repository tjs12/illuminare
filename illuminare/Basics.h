#ifndef BASICS_H
#define BASICS_H


#include <cmath>
//�㼰���������
class point
{
public:
	point(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {;} 
	point(const point &p) {this -> x =  p.x; this -> y =  p.y; this -> z =  p.z;}
	double x, y, z;
	void Normalize() {double l = sqrt(x * x + y * y + z * z); if (l!=0) {x = x / l; y = y / l; z = z / l;}}//��ɵ�λ����
	static double Distance2(const point &p1, const point &p2) {return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z);}
	static double DotProduct(const point &p1, const point &p2) {return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;}//���
	static point VecProduct(const point &p1, const point &p2) {return point(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x);}//���
	friend const point operator+(const point &left, const point &right);
	friend const point operator-(const point &left, const point &right);
	friend const point operator*(const double left, const point &right);
	friend const bool operator==(const point &left, const point &right);
	friend const bool operator!=(const point &left, const point &right);
};



//����

class Ray
{
public:
	Ray() {;}
	point start;
	point direction;
};

#endif