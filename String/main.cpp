#include"String.h"

#define BASE_CHECK
//#define CALLING_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "");
	
#ifdef BASE_CHECK
	String str(5);
	str.Print();

	String str1 = "Hello";		//"Hello" - строковая константа
	str1 = str1;				//"Hello" самоуничтожилось 
	cout << str1 << endl;

	String str2 = "World";
	cout << str2 << endl;

	str1 += str2;
	cout << str1 << endl;

	/*String str3;
	str3 = str1 + str2; //конкатенация (слияние) строк 
	cout << str3 << endl;

	str1 = str3;
	cout << str1 << endl;*/

	String str3 = str1 + str2;	//Move constructor
	cout << str3 << endl;

	String str4 = str3;			//Copy constructor
	str4.Print();
#endif
	
#ifdef CALLING_CONSTRUCTORS

	String str1;				//Default C-R
	String str2 = "Hello";		//1Arg C-R
	String str3 = str2;			//Copy C-R
	String str4();				//Without C-R (Function)
	String str5{};
	String str6{ 22 };
	String str7{ "World" };
	String str8{ str7 };
#endif
}