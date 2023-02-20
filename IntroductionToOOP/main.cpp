#include<iostream>
using namespace std;

#define delimiter "\n--------------------------------------\n"

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
	//							Constructors:
	/*Point()
	{
		x = y = 0;
		//RAII - выделение ресурсов - инициализация 
		cout << "DefConstructor:\t" << this << endl;
	}
	Point(double x)
	{
		this->x = x;
		this->y = 0;
		cout << "1ArgConstructor:" << this << endl;
	}*/
	Point(double x=0, double y=0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	Point(const Point& other)//copy-construct всегда принимает const ссылку на объект 
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}
	//							Operators
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Point& operator++()
	{
		x++;
		y++;
		return *this;
	}
	Point operator++(int)
	{
		Point old = *this;
		x++;
		y++;
		return old;
	}
	Point& operator()(double x, double y)
	{
		setX(x);
		setY(y);
		return *this;

	}

	//							Methods
	double distance(const Point& other)const //выбираем точку, до которой хотим узнать расстояние (называться может абсолютно по-разному, но удобнее исп other)
	{
	
		double x_distance = this->x - other.x; //находим расстояние по Х
		double y_distance = this->y - other.y; //расстояние по Y
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
		return distance;

	}
	void Print()const
	{
		cout << "X=" << x << "\t" << "Y=" << y << endl;
	}
};
//double distance(const Point& A, const Point& B);

Point operator+(const Point& left, const Point& right)
{
	Point res;
	res.setX(left.getX() + right.getX());
	res.setY(left.getY() + right.getY());
	return res;
}

//							Comparison operators

bool operator==(const Point& left, const Point& right)
{
	/*if (left.getX() == right.getX() && left.getY() == right.getY()) //выражение возвращает либо true, либо false
		return true;
	else
		return false;*/
	return left.getX() == right.getX() && left.getY() == right.getY();
}
bool operator!=(const Point& left, const Point& right)
{
	return !(left == right);
}
std::ostream& operator<<(std::ostream& os, const Point& obj)
{
	return os << "X=" << obj.getX() << "\t" << "Y=" << obj.getY();
}
std::istream& operator>>(std::istream& is, Point& obj)//Point& obj будет не конст, тк мы его будем изменять
{
	double x, y;
	is >> x >> y;
	obj(x, y);
	return is;
}

//#define STRUCT_POINT
//#define DISTANCE_CHECK
//#define CONSTRUCTOR_CHECK
//#define ASSIGNMENT_CHECK_1
//#define ASSIGNMENT_CHECK_2

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
	cout << delimiter << endl;
	cout << "Расстояние от точки А до точки В:" << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки B до точки A:" << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками А и В:" << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками B и A:" << distance(B, A) << endl;
	cout << delimiter << endl;
	//A.Print();
}

double distance(const Point& A, const Point& B)
{

	double x_distance = A.getX() - B.getX();
	double y_distance = A.getY() - B.getY();
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}
#endif

#ifdef CONSTRUCTOR_CHECK

Point A;
//cout << A.getX() << "\t" << A.getY() << endl;
A.Print();

Point B(2, 3);
B.Print();

Point C = 4; //Single-Argument contructor
C.Print();

Point D = C; //Copy constructor
//Deep copy - побитовое/побайтовое/поэлементное копирование
//Shallow copy - поверхностное копирование (копирование адреса вместо содержимого памяти)
D.Print();
}
#endif

#ifdef ASSIGNMENT_CHECK_1
//CopyAssignment
Point A(2, 3);
A.Print();
Point B = A; //CopyConstr, так как объект В здесь создается
B.Print();
Point C;
C = B; //Assignment operator, тк он уже создан, и только потом присваивается 
C.Print();
#endif

#ifdef ASSIGNMENT_CHECK_2
Point A, B, C;
cout << delimiter << endl;
A = B = C = Point(2, 3); //Point(2,3) - это явный вызов кон-ра
cout << delimiter << endl;
#endif

/*Point A(2, 3);
Point B(4, 5);
Point C = A + B + A + B;
C.Print();
cout << delimiter << endl;
C++;
C.Print();*/

//Point A(2, 3);
//Point B(2, 3);
//cout << (A != B) << endl; 
Point A(2, 3);
A.Print();

A(22, 33);
//A.Print();

cout << A << endl;

cout << "Введите координаты точки:"; cin >> A;
cout << A << endl;

}


