# include <iostream>
# include <string>

using namespace std;

class Student
{
public:
	string Name;
	string LastName;
	int Age;
	virtual ~Student(){	}
	Student()
	{
		Name="";
		LastName="";
		Age=0;
	}
	Student(string name,string lastname,int age)
	{
		Name=name;
		LastName=lastname;
		Age=age;
	}
};

class Aspirant:Student
{
private:
	string Theme;
public:
	Aspirant()
	{
		Theme="";
	}

	Aspirant(string name,string lastname,int age,string theme):Student(name,lastname,age)
	{
		Theme=theme;
	}

	virtual ~Aspirant(){}

	virtual void Show()
	{
		cout<<" Name: "<<Name<<endl;
		cout<<" LastName: "<<LastName<<endl;
		cout<<" Age: "<<Age<<endl;
		cout<<" Theme: "<<Theme<<endl;
	}
};

class Passport
{
public:
	string Name;
	string LastName;
	string Serial;
	int Day;
	int Month;
	int Year;
	virtual ~Passport(){	}
	Passport()
	{
		Name="";
		LastName="";
		Serial="";
		Day=0;
		Month=0;
		Year=0;
	}
	Passport(string name,string lastname,string serial, int day, int month, int year)
	{
		Name=name;
		LastName=lastname;
		Serial=serial;
		Day=day;
		Month=month;
		Year=year;
	}


};

class ForeignPassport:Passport
{
private:
	string Visa;
public:
	ForeignPassport()
	{
		Visa="";
	}

	ForeignPassport(string name,string lastname,string serial, int day, int month, int year,string visa):Passport(name,lastname,serial,day,month,year)
	{
		Visa=visa;
	}

	virtual ~ForeignPassport(){}

	virtual void Show()
	{
		cout<<" Name: "<<Name<<endl;
		cout<<" LastName: "<<LastName<<endl;
		cout<<" Date of birth: "<<Day<<"."<<Month<<"."<<Year<<endl;
		cout<<" Visa: "<<Visa<<endl;
	}


};

void main()
{
	Aspirant A("Evgen","Chul",28,"GSM");
	cout<<"Graduate student data:"<<endl;
	A.Show();
	ForeignPassport FP("Evgen","Chul","AA123456",25,02,2000,"Spain");
	cout<<"ForeignPassport data:"<<endl;
	FP.Show();
}

