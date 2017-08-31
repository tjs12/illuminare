#include "Basics.h"

const point operator+(const point &left, const point &right)
{
	return point(left.x + right.x, left.y + right.y, left.z + right.z);
}

const point operator-(const point &left, const point &right)
{
	return point(left.x - right.x, left.y - right.y, left.z - right.z);
}

const point operator*(const double left, const point &right)
{
	return point(left * right.x, left * right.y, left * right.z);
}

const bool operator==(const point &left, const point &right)
{
	return left.x==right.x && left.y==right.y && left.z==right.z;
}
const bool operator!=(const point &left, const point &right)
{
	return !(left==right);
}