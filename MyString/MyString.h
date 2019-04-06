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
	bool empty();
	void clear();
	void add(int index, char c);
	char get(int index);
	char set(int index, char c);
	char remove(int index);
	int index(const mystring& target_str);
	int index_kmp(const mystring& target_str);
	friend int* get_next_kmp(const mystring& target_str);
	char operator[](int index);
	mystring operator+(const mystring& add_str);
	bool operator==(const mystring& compare_str);
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

bool mystring::empty()
{
	return length == 0;
}

void mystring::clear()
{
	if (length != 0)
	{
		length = 0;
		delete str;
		str = nullptr;
	}
}

void mystring::add(int index, char c)
{
	if (index < 0 || index > length)
		cout << "add函数错误,index为非法值" << endl;
	else
	{
		char* new_str;
		new_str = new char[length + 2];
		if (index == 0)
		{
			new_str[0] = c;
			for (int i = 0; i < length; i++)
				new_str[i + 1] = str[i];
		}
		else
		{
			for (int i = 0; i < index; i++)
				new_str[i] = str[i];
			new_str[index] = c;
			for (int i = index; i < length; i++)
				new_str[i + 1] = str[i];
		}
		new_str[length + 1] = '\0';
		delete str;
		str = new_str;
		length++;
	}
}

char mystring::get(int index)
{
	if (index < 0 || index >= length)
	{
		cout << "get函数错误,index为非法值" << endl;
		return '\0';
	}
	else
		return str[index];
}

char mystring::set(int index, char c)
{
	if (index < 0 || index >= length)
	{
		cout << "set函数错误,index为非法值" << endl;
		return '\0';
	}
	else
	{
		char return_char = str[index];
		str[index] = c;
		return return_char;
	}
}

char mystring::remove(int index)
{
	if (index < 0 || index >= length)
	{
		cout << "remove函数错误,index为非法值" << endl;
		return '\0';
	}
	else
	{
		char* new_str;
		new_str = new char[length];
		char return_char;
		if (index == 0)
		{
			return_char = str[0];
			for (int i = 1; i < length; i++)
				new_str[i - 1] = str[i];
		}
		else
		{
			return_char = str[index];
			for (int i = 0; i < index; i++)
				new_str[i] = str[i];
			for (int i = index; i < length - 1; i++)
				new_str[i] = str[i + 1];
		}
		new_str[length - 1] = '\0';
		delete str;
		str = new_str;
		length--;
		return return_char;
	}
}

int mystring::index(const mystring& target_str)
{
	if (length < target_str.length)
	{
		cout << "index函数:模式串长度大于主串长度" << endl;
		return -1;
	}
	else if (length == target_str.length)
		if (*this == target_str)
			return 0;
		else
			return -1;
	else
	{
		if (target_str.length == 0)
			return -1;

		int i = 0;
		int j = 0;
		while (i < length && j < target_str.length)
			if (str[i] == target_str.str[j])
			{
				i++;
				j++;
			}
			else
			{
				i = i - j + 1;
				j = 0;
			}
		if (j >= target_str.length)
			return i - target_str.length;
		else
			return -1;
	}
}

int mystring::index_kmp(const mystring& target_str)
{
	if (length < target_str.length)
	{
		cout << "index函数:模式串长度大于主串长度" << endl;
		return -1;
	}
	else if (length == target_str.length)
		if (*this == target_str)
			return 0;
		else
			return -1;
	else
	{
		if (target_str.length == 0)
			return -1;

		int i = 0;
		int j = 0;
		int* next = get_next_kmp(target_str);
		while (i < length && j < target_str.length)
			if (j == -1 || str[i] == target_str.str[j])
			{
				i++;
				j++;
			}
			else
				j = next[j];
		if (j >= target_str.length)
			return i - target_str.length;
		else
			return -1;
	}
}

int* get_next_kmp(const mystring& target_str)
{
	int* next;
	if (target_str.length == 0)
		next = nullptr;
	else
	{
		next = new int[target_str.length];
		next[0] = -1;
		int i = 0;
		int j = -1;
		while (i < target_str.length - 1)
			if (j == -1 || target_str.str[i] == target_str.str[j])
			{
				i++;
				j++;
				if (target_str.str[i] == target_str.str[j])
					next[i] = next[j];
				else
					next[i] = j;
			}
			else
				j = next[j];
	}

	return next;
}

char mystring::operator[](int index)
{
	if (index < 0 || index >= length)
	{
		cout << "[]操作符错误,index为非法值" << endl;
		return '\0';
	}
	else
		return str[index];
}

mystring mystring::operator+(const mystring& add_str)
{
	if (length == 0 && add_str.length == 0)
	{
		mystring result;
		return result;
	}
	if (length != 0 && add_str.length == 0)
	{
		mystring result(*this);
		return result;
	}
	if (length == 0 && add_str.length != 0)
	{
		mystring result(add_str);
		return result;
	}
	if (length != 0 && add_str.length != 0)
	{
		char* new_str;
		int new_str_length = length + add_str.length;
		new_str = new char[new_str_length + 1];
		for (int i = 0; i < length; i++)
			new_str[i] = str[i];
		for (int i = 0; i < add_str.length; i++)
			new_str[length + i] = add_str.str[i];
		new_str[new_str_length] = '\0';
		
		mystring result;
		result.str = new_str;
		result.length = new_str_length;
		return result;
	}
}

bool mystring::operator==(const mystring& compare_str)
{
	if (length == compare_str.length)
	{
		for (int i = 0; i < length; i++)
			if (str[i] != compare_str.str[i])
				return false;
		return true;
	}
	return false;
}

ostream& operator<<(ostream& os, mystring str)
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
