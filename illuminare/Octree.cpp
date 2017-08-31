#include "Octree.h"
#include "SimpleObject.h"

#define MAXNUM 5

void Octree::Intersect(Ray &r, point &p, point &n, bool &valid, Geometry *&obj)
{
	valid = false;
	bool valid1;
	pBox *pb;
	Geometry *obj1;
	bool first = true;
	double shortestdist, tempd;
	point current_p, current_n;
	for (int i = 0 ; i < nc; i++) {
		pb = children[i];
		if (pb == 0) continue;
		pb->Intersect(r, current_p, current_n, valid1);
		if (valid1) {
			valid1 = false;
			children[i]->Intersect(r, current_p, current_n, valid1, obj1);
		}
		if (valid1) {
			valid = true;
			tempd = point::Distance2(current_p, r.start);
			if (first || tempd < shortestdist) {
				obj = obj1;
				p = current_p;
				n = current_n;
				first = false;
				shortestdist = tempd;
			}
		}
	}

	if (!valid) {
		objects.getIntersection(r, p, n, obj);
		if (obj != 0)
			valid = true;
	}
}

#define SIGN(x) x >= 0 ? 1 : -1

using namespace SimpleOBJ;

void Octree::GetObj(char *file) 
{
	CSimpleObject obj;
	obj.LoadFromObj(file);
	if (obj.m_nVertices == 0) return;
	double xmax = obj.m_pVertexList[0].x, ymax = obj.m_pVertexList[0].y, zmax = obj.m_pVertexList[0].z, xmin= obj.m_pVertexList[0].x, ymin= obj.m_pVertexList[0].y, zmin= obj.m_pVertexList[0].z;
	//int maxn = -1, minn = -1
	for (int i  = 0; i < obj.m_nVertices; i++) {
		if (xmax < obj.m_pVertexList[i].x) xmax = obj.m_pVertexList[i].x;
		if (ymax < obj.m_pVertexList[i].y) ymax = obj.m_pVertexList[i].y;
		if (zmax < obj.m_pVertexList[i].z) zmax = obj.m_pVertexList[i].z;
		if (xmin > obj.m_pVertexList[i].x) xmin = obj.m_pVertexList[i].x;
		if (ymin > obj.m_pVertexList[i].y) ymin = obj.m_pVertexList[i].y;
		if (zmin > obj.m_pVertexList[i].z) zmin = obj.m_pVertexList[i].z;
	}
	double cx = 0.5 * (xmax + xmin), cy = 0.5 * (ymax + ymin), cz= 0.5 * (zmax + zmin), tx, ty, tz;
	int attr[9] = {0,0,0,0,0,0,0,0,0};
	for (int i = 0; i < obj.m_nTriangles; i++)
	{
		for (int j = 0; j < 3; j++) {
			tx = obj.m_pVertexList[obj.m_pTriangleList[i][j]].x;
			ty = obj.m_pVertexList[obj.m_pTriangleList[i][j]].y;
			tz = obj.m_pVertexList[obj.m_pTriangleList[i][j]].z;
			if (tx < cx && ty < cy && tz < cz) attr[0]++;
			if (tx > cx && ty < cy && tz < cz) attr[1]++;
			if (tx < cx && ty > cy && tz < cz) attr[2]++;
			if (tx > cx && ty > cy && tz < cz) attr[3]++;
			if (tx < cx && ty < cy && tz > cz) attr[4]++;
			if (tx > cx && ty < cy && tz > cz) attr[5]++;
			if (tx < cx && ty > cy && tz > cz) attr[6]++;
			if (tx > cx && ty > cy && tz > cz) attr[7]++;
			else attr[8]++;
		}
	}
	children[0] = new Octree;
	children[0] -> p1 = point(xmin, cy, zmin);
	children[0] -> p2 = point(cx, ymin, cz);
	children[1] = new Octree;
	children[1] -> p1 = point(cx, cy, zmin);
	children[1] -> p2 = point(xmax, ymin, cz);
	children[2] = new Octree;
	children[2] -> p1 = point(xmin, ymax, zmin);
	children[2] -> p2 = point(cx, cy, cz);
	children[3] = new Octree;
	children[3] -> p1 = point(cx, ymax, zmin);
	children[3] -> p2 = point(xmax, cy, cz);
	children[4] = new Octree;
	children[4] -> p1 = point(xmin, cy, cz);
	children[4] -> p2 = point(cx, ymin, zmax);
	children[5] = new Octree;
	children[5] -> p1 = point(cx, cy, cz);
	children[5] -> p2 = point(xmax, ymin, zmax);
	children[6] = new Octree;
	children[6] -> p1 = point(xmin, ymax, cz);
	children[6] -> p2 = point(cx, cy, zmax);
	children[7] = new Octree;
	children[7] -> p1 = point(cx, ymax, cz);
	children[7] -> p2 = point(xmax, cy, zmax);

	for (int j = 0; j < 8; j++) {
		if (attr[j]!=0) {
			children[j] -> GetObj1(obj.m_nTriangles, obj.m_nVertices, obj.m_pTriangleList, obj.m_pVertexList);
		}
	}

}

void Octree::GetObj1(int m_nTriangles, int m_nVertices, Array<int, 3>* m_pTriangleList, Vec3f* m_pVertexList)
{
	if (m_nVertices == 0) return;
	double xmax = p2.x, ymax = p2.y, zmax = p2.z, xmin = p1.x, ymin = p1.y, zmin = p1.z;
	//int maxn = -1, minn = -1
	int num  = 0;
	for (int i  = 0; i < m_nTriangles; i++) {
		for (int j = 0; j < 3; j++) {
			if (m_pVertexList[m_pTriangleList[i][j]].x >= xmin && m_pVertexList[m_pTriangleList[i][j]].x <= xmax &&
				m_pVertexList[m_pTriangleList[i][j]].y <= ymin && m_pVertexList[m_pTriangleList[i][j]].y >= ymax &&
				m_pVertexList[m_pTriangleList[i][j]].z >= zmin && m_pVertexList[m_pTriangleList[i][j]].z <= zmax) {
					num++;
					break;
			}
		}
	}
	if (num==0) return;
	if (num <= MAXNUM) {
		for (int i  = 0; i < m_nTriangles; i++) {
			for (int j = 0; j < 3; j++) {
				if (m_pVertexList[m_pTriangleList[i][j]].x >= xmin && m_pVertexList[m_pTriangleList[i][j]].x <= xmax &&
					m_pVertexList[m_pTriangleList[i][j]].y <= ymin && m_pVertexList[m_pTriangleList[i][j]].y >= ymax &&
					m_pVertexList[m_pTriangleList[i][j]].z >= zmin && m_pVertexList[m_pTriangleList[i][j]].z <= zmax) {
						Triangle *tri = new Triangle;
						tri -> P[0].x = m_pVertexList[m_pTriangleList[i][0]].x;
						tri -> P[0].y = m_pVertexList[m_pTriangleList[i][0]].y;
						tri -> P[0].z = m_pVertexList[m_pTriangleList[i][0]].z;
						tri -> P[1].x = m_pVertexList[m_pTriangleList[i][1]].x;
						tri -> P[1].y = m_pVertexList[m_pTriangleList[i][1]].y;
						tri -> P[1].z = m_pVertexList[m_pTriangleList[i][1]].z;
						tri -> P[2].x = m_pVertexList[m_pTriangleList[i][2]].x;
						tri -> P[2].y = m_pVertexList[m_pTriangleList[i][2]].y;
						tri -> P[2].z = m_pVertexList[m_pTriangleList[i][2]].z;
						tri -> color = cv::Scalar(0,0,200);
						tri -> wr = 0;
						tri -> wt = 0;
						for (int k = 0; k < 8; k++) children[k] = 0;
						objects.add(tri);
						break;
				}
			}
		}
		return;
	}
	double cx = 0.5 * (xmax + xmin), cy = 0.5 * (ymax + ymin), cz= 0.5 * (zmax + zmin), tx, ty, tz;
	int attr[9] = {0,0,0,0,0,0,0,0,0};
	for (int i = 0; i < m_nTriangles; i++)
	{
		for (int j = 0; j < 3; j++) {
			tx = m_pVertexList[m_pTriangleList[i][j]].x;
			ty = m_pVertexList[m_pTriangleList[i][j]].y;
			tz = m_pVertexList[m_pTriangleList[i][j]].z;
			if (tx < cx && ty < cy && tz < cz) attr[0]++;
			if (tx > cx && ty < cy && tz < cz) attr[1]++;
			if (tx < cx && ty > cy && tz < cz) attr[2]++;
			if (tx > cx && ty > cy && tz < cz) attr[3]++;
			if (tx < cx && ty < cy && tz > cz) attr[4]++;
			if (tx > cx && ty < cy && tz > cz) attr[5]++;
			if (tx < cx && ty > cy && tz > cz) attr[6]++;
			if (tx > cx && ty > cy && tz > cz) attr[7]++;
			else attr[8]++;
		}
	}
	children[0] = new Octree;
	children[0] -> p1 = point(xmin, cy, zmin);
	children[0] -> p2 = point(cx, ymin, cz);
	children[1] = new Octree;
	children[1] -> p1 = point(cx, cy, zmin);
	children[1] -> p2 = point(xmax, ymin, cz);
	children[2] = new Octree;
	children[2] -> p1 = point(xmin, ymax, zmin);
	children[2] -> p2 = point(cx, cy, cz);
	children[3] = new Octree;
	children[3] -> p1 = point(cx, ymax, zmin);
	children[3] -> p2 = point(xmax, cy, cz);
	children[4] = new Octree;
	children[4] -> p1 = point(xmin, cy, cz);
	children[4] -> p2 = point(cx, ymin, zmax);
	children[5] = new Octree;
	children[5] -> p1 = point(cx, cy, cz);
	children[5] -> p2 = point(xmax, ymin, zmax);
	children[6] = new Octree;
	children[6] -> p1 = point(xmin, ymax, cz);
	children[6] -> p2 = point(cx, cy, zmax);
	children[7] = new Octree;
	children[7] -> p1 = point(cx, ymax, cz);
	children[7] -> p2 = point(xmax, cy, zmax);

	for (int j = 0; j < 8; j++) {
		if (attr[j]!=0) {
			children[j] -> GetObj1(m_nTriangles, m_nVertices, m_pTriangleList, m_pVertexList);
		}
	}
}
