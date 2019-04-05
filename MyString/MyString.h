/*
	Copyright 2019 heiyedeshengyin All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
#include <cstring>
using namespace std;

class mystring
{
private:
	char* str;
	int length;
public:
	mystring();
	mystring(const char* _str);
	mystring(const mystring& ano);
	~mystring();
	int get_length();
	char get(int index);
};

mystring::mystring()
{
	str = nullptr;
	length = 0;
}

mystring::mystring(const char* _str)
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

mystring::mystring(const mystring& ano)
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

mystring::~mystring()
{
	if (length != 0)
		delete str;
}

int mystring::get_length()
{
	return length;
}

char mystring::get(int index)
{
	if (index < 0 && index >= length)
	{
		cout << "get函数错误,index为非法值" << endl;
		return '\0';
	}
	else
		return str[index];
}

ostream& operator<<(ostream& os, mystring& str)
{
	if (str.get_length() == 0)
		return os;
	else
	{
		for (int i = 0; i < str.get_length(); i++)
			os << str.get(i);
		return os;
	}
}

#endif // !MYSTRING_H

