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

