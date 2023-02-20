#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right); 

class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	//							Get/Set
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//							Constructors
	Fraction(int integer, int numerator, int denominator) //вызывается во всех трех ситуациях, потому что за счет значений по умолчанию, но если убрать - все работает
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefConstructor:\t\t" << this << endl; 
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1ArgConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator) 
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator; //здесь фильтрация не нужна, так как отфильтровали все в основном объекте
		cout << "CopyConstructor:\t" << this << endl; 
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}
	//							Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other; 
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	//							Methods
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator);
		return inverted;

	}
	Fraction& reduce()
	{
		int more, less, rest = 0;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do
		{
			rest = more % less; //записываем остаток от деления большего на меньшее
			more = less; //теперь большее становится меньшим
			less = rest; //меньшее становится остатком 
		} while (rest);  //до тех пор, пока остаток не сольется в ноль
		int GCD = more;  //GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;//сокращаем числитель и знаменатель на одинаковое число 
		denominator /= GCD;
		return *this;
	}
	void Print()const
	{
		if (integer) cout << integer; 
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
	Fraction& to_proper(int integer, int numerator, int denominator)//целую часть интегрирует в числитель
	{
		int res=0;
		if (this->integer != 0)
		{
			res = this->integer * this->denominator + this->numerator;
			this->numerator = res;
			this->integer = 0;
		}
		return *this;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

// Явно вызываем конструктор и создаем временный безымянной объект, кот сразу же возвращается на место вызова
	return Fraction
	(left.get_numerator() * right.get_numerator(),
		left.get_denominator()*right.get_denominator()
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
//#define CONSTRUCTORS_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	A.Print();

	Fraction B = 5;
	B.Print();

	Fraction C(2, 3);
	C.Print();

	Fraction D(2, 3, 4);
	D.Print();
	
	Fraction E = D;
	E.Print();
#endif

	Fraction A(2, 3, 4);
	A.Print();

	Fraction B(3, 4, 5);
	B.Print();

	Fraction C = A * B;
	C.Print();

	Fraction D = A / B;
	D.Print();

	A *= B;
	A /= B;
	A.Print();
	
}