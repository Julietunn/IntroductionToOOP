#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right); 
Fraction operator-(Fraction left, Fraction right);
Fraction operator+(Fraction left, Fraction right);

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
	void set_denominator(int denominator)				//фильтрация данных, так как на ноль делить нельзя
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//							Constructors
	Fraction(int integer, int numerator, int denominator) //вызывается во всех трех ситуациях, потому что за счет значений по умолчанию, но если убрать - все работает
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator); //записываем через set, так как там была выполнена фильтрация данных
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefConstructor:\t\t" << this << endl; 
	}
	Fraction(double decimal)
	{
		this->integer = decimal; //сохраняем целую часть
		decimal -= integer;		//убираем целую часть из десятичной дроби 
		this->denominator = 1e+9;
		this->numerator = decimal * denominator; 
		reduce();
		cout << "DConstructor:\t" << this << endl; 
	}
	explicit Fraction(int integer)
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
	Fraction& operator()(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		return *this;
	}
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
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator--()
	{
		integer--;
		return *this;
	}
	Fraction operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
	}

	//							Type-cast operators
	explicit operator int()const
	{

		return Fraction(*this).to_proper().integer;
	}
	explicit operator double()const
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
	std::ostream& Print(std::ostream& os)const
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
	left.to_improper(); //переводим в неправильную дробь для того, чтобы было легче сравнивать 
	right.to_improper(); 

	return 
		left.get_numerator() * right.get_denominator() == 
		right.get_numerator() * left.get_denominator();

}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right); //НЕ равно 
}

bool operator>(Fraction left, Fraction right)
{
	left.to_improper(); //переводим в неправильную дробь для того, чтобы было легче сравнивать 
	right.to_improper();

	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper(); //переводим в неправильную дробь для того, чтобы было легче сравнивать 
	right.to_improper();

	return
		left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	//return left > right || left == right;
	return !(left < right); //Больше или равно - это НЕ меньше 
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

	int n = 0;	//счетчик чисел в веденной строке
	for (char* pch =  strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
		number[n++] = atoi(pch);	//функция atoi(...) ASCII-string to integer преобразует строку в число, если строка является числом, т.е., содержит цифры.

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
/////////////////////////////////////////////////////////////////////////////////////

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define COMPARISON_OPERATORS
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER
//#define HOMEWORK_1
#define HOMEWORK_2


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

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2,3 4);
	//A.Print();

	Fraction B(3,4,5);
	B.Print();

	Fraction C = A * B;
	C.Print();

	Fraction D = A / B;
	D.Print();

	Fraction E = A + B;
	E.Print();

	Fraction F = A - B;
	F.Print();

	A *= B;
	A /= B;
	A -= B;
	A += B;
	A.Print();

#endif

#ifdef COMPARISON_OPERATORS
	
	cout << (Fraction(1, 2) > Fraction(5, 10)) << endl; 

#endif
	/*Fraction A(2, 3, 4);
	cout << A << endl; */

#ifdef CONVERSION_FROM_OTHER_TO_CLASS

	Fraction A = (Fraction)5; //Conversion from other to class preformed by Single-argument constructor
	A.Print();

	Fraction B;
	B = Fraction(8);			//Conversion from other to class preformed by Assignment operator
	B.Print();
#endif

#ifdef CONVERSION_FROM_CLASS_TO_OTHER
	Fraction A(2, 3, 4);
	A.Print();
	int a = (int)A; 

	cout << a << endl; 
#endif

#ifdef HOMEWORK_1
	Fraction B(2, 3, 4);
	double b =(double) B;
	cout << b << endl; 
#endif

#ifdef HOMEWORK_2
	Fraction B = 2.75;
	//B.Print(cout) << endl;
	cout << B << endl;
#endif

	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;

	cout << A--;
}