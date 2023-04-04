#include<iostream>
using namespace std;

class String;
String operator+(const String& left, const String& right);

class String
{
	int size;		//размер строки в байтах
	char* str;		//адрес строки в динамической памяти 
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	//							Constructors:
	explicit String(int size = 80):size(size), str(new char[size]{})
	{
		//this->size = size;
		//this->str = new char[size] {}; //создание 
		cout << "DefConstructor:\t\t" << this << endl;
	}
	String(const char* str):size(strlen(str)+1), str(new char[size] {})
	{
		//this->size = strlen(str) + 1; //strlen - возвращает кол-во символов без 0, то есть реальный объем равен strlen + 1
		//this->str = new char[size] {};

		for (int i = 0; i < size; i++)this->str[i] = str[i];

		cout << "1ArgConstructor:\t" << this << endl; 
	}
	String(const String& other):size (other.size), str(new char[size]{})
	{
		//Deep copy 
		//this->size = other.size; 
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	String(String&& other)noexcept:size(other.size), str(other.str) //R-value reference
	{
		//Shallow copy
		//this->size = other.size;
		//this->str = other.str;
		other.size = 0;
		other.str = nullptr;			//указатель на ноль
		cout << "MoveConstructor:\t" << this << endl;
	}
	~String()
	{
		delete this->str;
		cout << "Destructor:\t\t" << this << endl; 
	}
	//							Operators:
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl; 
		return *this;
	}
	String& operator=(String&& other)
	{
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	char& operator[](int i)
	{
		return str[i];
	}
	const char& operator[](int i)const
	{
		return str[i];
	}
	String& operator+= (const String& other)
	{
		return *this = *this + other;
	}
	//							Methods:
	void Print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() -1); //-1, чтобы строка была с одним нулем, а не с двумя
													  //создание самой строки для будущих действий 
	for (int i = 0; i < left.get_size(); i++)
		cat[i] = left[i];
		//cat.get_str()[i] = left.get_str()[i];

	for (int i = 0; i < right.get_size(); i++)
		cat[i + left.get_size() - 1] = right[i];
		//cat.get_str()[i + left.get_size() - 1] = right.get_str()[i]; //копируем со смещением за счет левого объекта

	return cat;
}

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