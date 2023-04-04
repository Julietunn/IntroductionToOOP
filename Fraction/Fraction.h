//Fraction
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/////////////////////////////////////////////////////////////////
//							CLASS DECLARATION

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);
Fraction operator-(Fraction left, Fraction right);
Fraction operator+(Fraction left, Fraction right);
std::istream& operator>>(std::istream& is, Fraction& obj);
std::ostream& operator<<(std::ostream& os, const Fraction& obj);

class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	//							Get/Set
	int get_integer()const;
	int get_numerator()const;
	int get_denominator()const;
	void set_integer(int integer);
	void set_numerator(int numerator);
	void set_denominator(int denominator);
	//							Constructors
	Fraction(int integer, int numerator, int denominator);
	Fraction();
	Fraction(double decimal);
	explicit Fraction(int integer);
	Fraction(int numerator, int denominator);
	Fraction(const Fraction& other);
	~Fraction();
	//							Operators
	Fraction& operator()(int integer, int numerator, int denominator);
	Fraction& operator=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator+=(const Fraction& other);
	Fraction& operator++();
	Fraction operator++(int);
	Fraction& operator--();
	Fraction operator--(int);

	//							Type-cast operators
	explicit operator int()const;
	explicit operator double()const;
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
	Fraction& to_improper();
	Fraction& to_proper();
	Fraction inverted()const;
	Fraction& reduce();
	std::ostream& Print(std::ostream& os)const;
	Fraction& to_proper(int integer, int numerator, int denominator);
};

/////////////////////////////////////////////////////////////////
//						CLASS DECLARATION END