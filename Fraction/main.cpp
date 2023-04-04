#include"Fraction.h"
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