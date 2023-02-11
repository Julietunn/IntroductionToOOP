#include<iostream>
using namespace std;

class Point
{
	double x;
	double y;
public:
	int getX()const
	{
		return x;
	}

	void setX(double x)
	{
		this->x = x;
	}
	int getY()const
	{
		return y;
	}
	void setY(double y)
	{
		this->y = y;
	}
	//							Methods
	double distance(Point other) //выбираем точку, до которой хотим узнать расстояние (называться может абсолютно по-разному, но удобнее исп other)
	{
		double x_distance = this->x - other.x; //находим расстояние по Х
		double y_distance = this->y - other.y; //расстояние по Y
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
		return distance;

	}
	/*void Print()
	{
		cout << "X=" << x << "\t" << "Y=" << y << endl;
	}*/
};
double distance(Point A, Point B);

//#define STRUCT_POINT
//#define DISTANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRUCT_POINT
	Point A;
	A.x = 2;
	A.y = 3;

	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl
#endif

#ifdef DISTANCE_CHECK
	Point A;
	A.setX(2);
	A.setY(3);
	Point B;
	B.setX(7);
	B.setY(8);
	cout << A.getX() << "\t" << A.getY() << "\n" << B.getX() << "\t" << B.getY() << endl;
	cout << "Расстояние от точки А до точки В:" << A.distance(B) << endl;
	cout << "Расстояние от точки B до точки A:" << B.distance(A) << endl;
	cout << "Расстояние между точками А и В:" << distance(A, B) << endl;
	cout << "Расстояние между точками B и A:" << distance(B, A) << endl;
	//A.Print();
}
double distance(Point A, Point B)
{
	double x_distance = A.getX() - B.getX();
	double y_distance = A.getY() - B.getY();
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}
#endif