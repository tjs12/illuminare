#include <fstream>
#include <cmath>

#define PI 3.14

using namespace std;

double phi(int s)
{
	if (s <= 24) 
		return (10.0 - 20.0 / 24.0 * s) / 180 * PI;
	else
		return (-10.0 + 20.0 / 24.0 * (s - 24)) / 180 * PI;
}

double theta(int s)
{
	if (s <= 24)
	return (-30.0 + 60.0 / 24.0 * s) / 180 * PI;
	else
		return (30.0 - 60.0 / 24.0 * (s - 24)) / 180 * PI;
}

double x2(int s)
{
	return cos(s / 24.0 * 2 * PI) * 30;
}

double z2(int s)
{
	return sin(s / 24.0 * 2 * PI) * 30;
}

double x1(int s)
{
	return cos(s / 48.0 * 2 * PI) * 20;
}

double z1(int s)
{
	return sin(s / 48.0 * 2 * PI) * 20;
}

void writeinput(int s)
{
	ofstream fout("in.txt");
	fout << "0.09\n0 0 -15\n";
	double p = phi(s);
	double t = theta(s);
	fout << cos(t) << ' ' << -sin(t)*sin(p) << ' ' << -sin(t)*cos(p) << endl;
	fout << 0 << ' ' << cos(p) << ' ' << -sin(p) << endl;
	fout << sin(t) << ' ' << cos(t)*sin(p) << ' ' << cos(t)*cos(p) << endl;
	
	fout << "1 -10 -70 60\n";

	fout << "9\n";

	fout << "1 0 0 70 10 200 200 200 0.1 0.7 1.05 0\n";
	fout << "0 0 0 -1 180 -205 -160 180 1 0 0 0 1 0 255 300 200 0 0 1 1\nEscola_de_atenas_-_vaticano.jpg\n0.35 0.35\n";
	fout << "1 " << x1(s) << " 0 " << z1(s) + 70 << " 6 255 255 255 0 0 1 1\ntex.bmp\n0.001 0.001\n";
	fout << "1 " << x2(s) << " 0 " << z2(s) + 70 << " 3 0 0 255 0.2 0 1 0\n";
	fout << "0 1  0 0 100 -100 -100 -100 0 0 -1 0 1 0 200 100 200 0   0 1 1\n900px-Deliveranceofstpeter.jpg\n0.45 0.45\n";
	fout << "0 -1 0 0 100  100 -100 -100 0 0 -1 0 1 0 200 100 100 0   0 1 1\n900px-Leoattila-Raphael.jpg\n0.45 0.45\n";
	fout << "0 0  0 1 100 -130 -100 -100 1 0  0 0 1 0 200 200 100 0   0 1 1\n900px-Raffael_078.jpg\n0.3 0.3\n";
	fout << "0 0  1 0 100 -100 -100  180 0 0 -1 1 0 0 255 170 170 0   0 1 1\n1200px-Ceiling_SM_Maggiore.jpg\n0.27 0.27\n";
	fout << "0 0 -1 0 100 -100 -100 -100 0 0  1 1 0 0 255 170 170 0.4 0 1 2 0";


	
	fout.close();

}

  
int main(int argn, char **argv)
{
	char str[100];
	for (int i = 0; i < 1; i++) {
		writeinput(i);
		str[0] = 0;
		strcpy(str, argv[1]);
		strcat(str, " ");
		itoa(i, str + strlen(str), 10);
		strcat(str, ".bmp 0");

		system(str);
	}
}