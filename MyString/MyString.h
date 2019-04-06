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

//----------------数据结构----------------
/*字符串*/
class mystring
{
private:
	char* str;	//封装的字符数组
	int length;	//字符串的长度
public:
	mystring();	//无参构造函数
	mystring(const char* _str);	//有参构造函数
	mystring(const mystring& ano);	//拷贝构造函数
	~mystring();	//析构函数
	int get_length();	//获取字符个数
	bool empty();	//判断是否为空
	void clear();	//把字符串清空
	void add(int index, char c);	//增加一个字符
	char get(int index);	//获取一个字符
	char set(int index, char c);	//改变一个字符
	char remove(int index);	//删除一个字符
	int index(const mystring& target_str);	//查询子串的位置
	int index(const mystring& target_str, int from_index);
	int index_kmp(const mystring& target_str);	//用KMP算法查询子串的位置
	int index_kmp(const mystring& target_str, int from_index);
	friend int* get_next_kmp(const mystring& target_str);
	mystring sub_string(int begin_index);	//截取字符串
	mystring sub_string(int begin_index, int end_index);
	char operator[](int index);	//重载[]运算符
	mystring operator+(const mystring& add_str);	//重载+运算符
	bool operator==(const mystring& compare_str);	//重载==运算符
};

//----------------函数的具体实现----------------
/*
	无参构造函数
*/
mystring::mystring()
{
	str = nullptr;
	length = 0;
}

/*
	有参构造函数

	const char* _str:传入的字符串
*/
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

/*
	拷贝构造函数

	const mystring& ano:被拷贝的字符串
*/
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

/*
	析构函数
*/
mystring::~mystring()
{
	if (length != 0)
		delete str;
}

/*
	获取字符的个数

	@Return int
*/
int mystring::get_length()
{
	return length;
}

/*
	判断字符串是否为空

	@Return bool
*/
bool mystring::empty()
{
	return length == 0;
}

/*
	清空字符串

	@Return void
*/
void mystring::clear()
{
	if (length != 0)
	{
		length = 0;
		delete str;
		str = nullptr;
	}
}

/*
	增加一个字符
	int index:增加之后增加的字符所在的索引
	char c:增加的字符

	@Return void
*/
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

/*
	获取一个字符
	int index:获取的字符所在的索引

	@Return char
*/
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

/*
	改变一个字符
	int index:改变的字符所在的索引
	char c:改变后的字符

	@Return char
*/
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

/*
	删除一个字符
	int index:删除的字符所在的索引

	@Return char
*/
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

/*
	获取子串第一次出现在字符串中的索引
	const mystring& target_str:子串

	@Return int
*/
int mystring::index(const mystring& target_str)
{
	return index(target_str, 0);
}

/*
	获取子串从指定位置开始第一次出现在字符串中的索引
	const mystring& target_str:子串
	int from_index:开始位置的索引

	@Return int
*/
int mystring::index(const mystring& target_str, int from_index)
{
	if (length < target_str.length)
	{
		cout << "index函数错误:模式串长度大于主串长度" << endl;
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

		int i = from_index;
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

/*
	使用KMP算法,获取子串第一次出现在字符串中的索引
	const mystring& target_str:子串

	@Return int
*/
int mystring::index_kmp(const mystring& target_str)
{
	return index_kmp(target_str, 0);
}

/*
	使用KMP算法,获取子串从指定位置开始第一次出现在字符串中的索引
	const mystring& target_str:子串
	int from_index:开始位置的索引

	@Return int
*/
int mystring::index_kmp(const mystring& target_str, int from_index)
{
	if (length < target_str.length)
	{
		cout << "index_kmp函数错误:模式串长度大于主串长度" << endl;
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

		int i = from_index;
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

/*
	获取字符串在KMP算法中的next数组
	const mystring& target_str:字符串

	@Return int*
*/
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

/*
	截取字符串,从指定起始位置到结尾
	int begin_index:开始位置的索引

	@Return mystring
*/
mystring mystring::sub_string(int begin_index)
{
	mystring return_str;
	if (begin_index < 0 || begin_index >= length)
	{
		cout << "sub_string函数错误,index为非法值" << endl;
		return return_str;
	}
	else
	{
		char* result;
		result = new char[length - begin_index + 1];
		return_str.length = length - begin_index;
		for (int i = 0; i < return_str.length; i++)
			result[i] = str[begin_index + i];
		result[return_str.length] = '\0';

		return_str.str = result;
	}
	return return_str;
}

/*
	截取字符串,从指定起始位置到指定结束位置
	int begin_index:开始位置的索引
	int end_index:结束位置的索引

	@Return mystring
*/
mystring mystring::sub_string(int begin_index, int end_index)
{
	mystring return_str;
	if (begin_index < 0 || begin_index >= length || end_index < 0 || end_index >= length || begin_index >= end_index)
	{
		cout << "sub_string函数错误,index为非法值" << endl;
		return return_str;
	}
	else
	{
		char* result;
		result = new char[end_index - begin_index + 1];
		return_str.length = end_index - begin_index;
		for (int i = 0; i < return_str.length; i++)
			result[i] = str[begin_index + i];
		result[return_str.length] = '\0';

		return_str.str = result;
	}
	return return_str;
}

/*
	重载[]运算符
	int index:索引

	@Return char
*/
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

/*
	重载+运算符,使两个字符串拼接到一起
	const mystring& add_str:字符串

	@Return mystring
*/
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

/*
	重载==运算符,判断两个字符串是否完全相等
	const mystring& compare_str:字符串

	@Return bool
*/
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

/*
	重载<<运算符
	ostream& os:输出流
	mystring str:输出的字符串

	@Return ostream&
*/
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
