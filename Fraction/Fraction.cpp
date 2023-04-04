//Fraction.cpp
#include "Fraction.h"

//---------------------------------------------------------------

/////////////////////////////////////////////////////////////////
//							CLASS DEFINITION

//							Get/Set
int Fraction::get_integer()const
{
	return integer;
}
int Fraction::get_numerator()const
{
	return numerator;
}
int Fraction::get_denominator()const
{
	return denominator;
}
void Fraction::set_integer(int integer)
{
	this->integer = integer;
}
void Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
}
void Fraction::set_denominator(int denominator)				//���������� ������, ��� ��� �� ���� ������ ������
{
	if (denominator == 0)denominator = 1;
	this->denominator = denominator;
}
//							Constructors
Fraction::Fraction(int integer, int numerator, int denominator) //���������� �� ���� ���� ���������, ������ ��� �� ���� �������� �� ���������, �� ���� ������ - ��� ��������
{
	this->integer = integer;
	this->numerator = numerator;
	this->set_denominator(denominator); //���������� ����� set, ��� ��� ��� ���� ��������� ���������� ������
	cout << "Constructor:\t\t" << this << endl;
}
Fraction::Fraction()
{
	this->integer = 0;
	this->numerator = 0;
	this->denominator = 1;
	cout << "DefConstructor:\t\t" << this << endl;
}
Fraction::Fraction(double decimal)
{
	this->integer = decimal; //��������� ����� �����
	decimal -= integer;		//������� ����� ����� �� ���������� ����� 
	this->denominator = 1e+9;
	this->numerator = decimal * denominator;
	reduce();
	cout << "DConstructor:\t" << this << endl;
}
Fraction::Fraction(int integer)
{
	this->integer = integer;
	this->numerator = 0;
	this->denominator = 1;
	cout << "1ArgConstructor:\t" << this << endl;
}
Fraction::Fraction(int numerator, int denominator)
{
	this->integer = 0;
	this->numerator = numerator;
	this->set_denominator(denominator);
	cout << "Constructor:\t\t" << this << endl;
}
Fraction::Fraction(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator; //����� ���������� �� �����, ��� ��� ������������� ��� � �������� �������
	cout << "CopyConstructor:\t" << this << endl;
}
Fraction::~Fraction()
{
	cout << "Destructor:\t\t" << this << endl;
}
//							Operators
Fraction& Fraction::operator()(int integer, int numerator, int denominator)
{
	set_integer(integer);
	set_numerator(numerator);
	set_denominator(denominator);
	return *this;
}
Fraction& Fraction:: operator=(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}
Fraction& Fraction::operator*=(const Fraction& other)
{
	return *this = *this * other;
}
Fraction& Fraction::operator/=(const Fraction& other)
{
	return *this = *this / other;
}
Fraction& Fraction::operator-=(const Fraction& other)
{
	return *this = *this - other;
}
Fraction& Fraction::operator+=(const Fraction& other)
{
	return *this = *this + other;
}
Fraction& Fraction::operator++()
{
	integer++;
	return *this;
}
Fraction Fraction::operator++(int)
{
	Fraction old = *this;
	integer++;
	return old;
}
Fraction& Fraction::operator--()
{
	integer--;
	return *this;
}
Fraction Fraction::operator--(int)
{
	Fraction old = *this;
	integer--;
	return old;
}

//							Type-cast operators
Fraction::operator int()const
{

	return Fraction(*this).to_proper().integer;
}
Fraction::operator double()const
{
	return integer + (double)numerator / denominator;
}
//						Methods
/*void Print()const
{
	if (integer) cout << integer;
	if (numerator)
	{
		if (integer) cout << "(";
		cout << numerator << "/" << denominator;
		if (integer) cout << ")";
	}
	else if (integer == 0) cout << 0;
	cout << endl;
}*/
Fraction& Fraction::to_improper()
{
	numerator += integer * denominator;
	integer = 0;
	return *this;
}
Fraction& Fraction::to_proper()
{
	integer += numerator / denominator;
	numerator %= denominator;
	return *this;
}
Fraction Fraction::inverted()const
{
	Fraction inverted = *this;
	inverted.to_improper();
	swap(inverted.numerator, inverted.denominator);
	return inverted;

}
Fraction& Fraction::reduce()
{
	int more, less, rest = 0;
	if (numerator > denominator)more = numerator, less = denominator;
	else less = numerator, more = denominator;
	do
	{
		rest = more % less; //���������� ������� �� ������� �������� �� �������
		more = less; //������ ������� ���������� �������
		less = rest; //������� ���������� �������� 
	} while (rest);  //�� ��� ���, ���� ������� �� �������� � ����
	int GCD = more;  //GCD - Greatest Common Divisor (���������� ����� ��������)
	numerator /= GCD;//��������� ��������� � ����������� �� ���������� ����� 
	denominator /= GCD;
	return *this;
}
std::ostream& Fraction::Print(std::ostream& os)const
{
	if (integer)os << integer;
	if (numerator)
	{
		if (integer)os << "(";
		os << numerator << "/" << denominator;
		if (integer)os << ")";
	}
	else if (integer == 0)os << 0;
	//os << endl;
	return os;
}
Fraction& Fraction::to_proper(int integer, int numerator, int denominator)//����� ����� ����������� � ���������
{
	int res = 0;
	if (this->integer != 0)
	{
		res = this->integer * this->denominator + this->numerator;
		this->numerator = res;
		this->integer = 0;
	}
	return *this;
}

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	// ���� �������� ����������� � ������� ��������� ���������� ������, ��� ����� �� ������������ �� ����� ������
	return Fraction
	(left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
	/*
	result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denominator(left.get_denominator() * right.get_denominator());*/
	//return result;
}

Fraction operator/(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();

	return Fraction
	(
		left.get_numerator() * right.get_denominator(),
		right.get_numerator() * left.get_denominator()
	).to_proper();*/
	return left * right.inverted();
}
Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	return Fraction
	(
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).reduce().to_proper();
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	return Fraction
	(
		left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).reduce().to_proper();
}

////////////////////////////////////////////////////////////////
//						Comparisons operators
////////////////////////////////////////////////////////////////

bool operator==(Fraction left, Fraction right)
{
	left.to_improper(); //��������� � ������������ ����� ��� ����, ����� ���� ����� ���������� 
	right.to_improper();

	return
		left.get_numerator() * right.get_denominator() ==
		right.get_numerator() * left.get_denominator();

}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right); //�� ����� 
}

bool operator>(Fraction left, Fraction right)
{
	left.to_improper(); //��������� � ������������ ����� ��� ����, ����� ���� ����� ���������� 
	right.to_improper();

	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper(); //��������� � ������������ ����� ��� ����, ����� ���� ����� ���������� 
	right.to_improper();

	return
		left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	//return left > right || left == right;
	return !(left < right); //������ ��� ����� - ��� �� ������ 
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return left < right || left == right;
}

//////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	return obj.Print(os);
}
std::istream& operator>>(std::istream& is, Fraction& obj)
{
	/*int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	obj(integer, numerator, denominator);*/

	/*
		5;
		1/2;
		2(3/4);
		2 3/4;
	*/

	int number[3] = {};

	const int SIZE = 32;
	char buffer[SIZE] = {};
	char delimiters[] = "/ ()";

	//is >> buffer;
	is.getline(buffer, SIZE);

	int n = 0;	//������� ����� � �������� ������
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
		number[n++] = atoi(pch);	//������� atoi(...) ASCII-string to integer ����������� ������ � �����, ���� ������ �������� ������, �.�., �������� �����.

	switch (n)
	{
	case 1:obj.set_integer(number[0]); break;
	case 2:
		obj.set_numerator(number[0]);
		obj.set_denominator(number[1]);
		break;
	case 3:obj(number[0], number[1], number[2]);
	}

	return is;
}
/////////////////////////////////////////////////////////////////
//							CLASS DEFINITION END
/////////////////////////////////////////////////////////////////////////////////////