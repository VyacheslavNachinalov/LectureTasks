#include <iostream>
#include <vector>

using namespace std;
template <class T> class SP
{
	T* ptr;

public:
	SP() 
	{
	}
	SP(T* p) 
	{
		ptr = p;
	}
	~SP() {
		delete ptr;
	}
	T& operator*() 
	{
		return *ptr;
	}
	T* operator->() 
	{
		return ptr;
	}
};

class Person
{
	std::string name;
	int age;
	int number;

public:
	Person() 
	{

	}

	Person(std::string tname, int tage)
	{
		name = tname;
		age = tage;
	}
	void setName(std::string tname)
	{
		name = tname;
	}

	void setAge(int tage)
	{
		age = tage;
	}

	void show() 
	{
		std::cout << "Name: " << name << std::endl;
		std::cout << "Age: " << age<< std::endl;
	}
};

void recurs(int mas[], int n = 0) //рекурсия, ограничение реализуется с помощью исключения
{
	try
	{
		mas[n] = n;
		cout << mas[n];
		n++;
	}
	catch (...)
	{
		return;
	}

}

int main()
{
	SP<Person> p(new Person("Slava",18));
	p->show();
	int mas[20];
	recurs(mas);
	return 0;
}