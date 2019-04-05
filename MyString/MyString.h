#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
private:
	char* str;
	int length;
public:
	MyString();
	MyString(const char* _str);
	MyString(const MyString& ano);
	~MyString();

};

MyString::MyString()
{
	str = nullptr;
	length = 0;
}

MyString::MyString(const char* _str)
{
	length = strlen(_str);
	if (length == 0)
		str = nullptr;
	else
	{
		str = new char[length + 1];
		for (int i = 0; i < length; i++)
			str[i] = _str[i];
		str[length] = '\0';
	}
}

MyString::MyString(const MyString& ano)
{
	length = ano.length;
	if (length == 0)
		str = nullptr;
	else
	{
		str = new char[length + 1];
		for (int i = 0; i < length; i++)
			str[i] = ano.str[i];
		str[length] = '\0';
	}
}

MyString::~MyString()
{
	if (length != 0)
		delete str;
}



#endif // !MYSTRING_H

