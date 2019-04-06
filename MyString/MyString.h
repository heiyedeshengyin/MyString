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

//----------------���ݽṹ----------------
/*�ַ���*/
class mystring
{
private:
	char* str;	//��װ���ַ�����
	int length;	//�ַ����ĳ���
public:
	mystring();	//�޲ι��캯��
	mystring(const char* _str);	//�вι��캯��
	mystring(const mystring& ano);	//�������캯��
	~mystring();	//��������
	int get_length();	//��ȡ�ַ�����
	bool empty();	//�ж��Ƿ�Ϊ��
	void clear();	//���ַ������
	void add(int index, char c);	//����һ���ַ�
	char get(int index);	//��ȡһ���ַ�
	char set(int index, char c);	//�ı�һ���ַ�
	char remove(int index);	//ɾ��һ���ַ�
	int index(const mystring& target_str);	//��ѯ�Ӵ���λ��
	int index(const mystring& target_str, int from_index);
	int index_kmp(const mystring& target_str);	//��KMP�㷨��ѯ�Ӵ���λ��
	int index_kmp(const mystring& target_str, int from_index);
	friend int* get_next_kmp(const mystring& target_str);
	mystring sub_string(int begin_index);	//��ȡ�ַ���
	mystring sub_string(int begin_index, int end_index);
	char operator[](int index);	//����[]�����
	mystring operator+(const mystring& add_str);	//����+�����
	bool operator==(const mystring& compare_str);	//����==�����
};

//----------------�����ľ���ʵ��----------------
/*
	�޲ι��캯��
*/
mystring::mystring()
{
	str = nullptr;
	length = 0;
}

/*
	�вι��캯��

	const char* _str:������ַ���
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
	�������캯��

	const mystring& ano:���������ַ���
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
	��������
*/
mystring::~mystring()
{
	if (length != 0)
		delete str;
}

/*
	��ȡ�ַ��ĸ���

	@Return int
*/
int mystring::get_length()
{
	return length;
}

/*
	�ж��ַ����Ƿ�Ϊ��

	@Return bool
*/
bool mystring::empty()
{
	return length == 0;
}

/*
	����ַ���

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
	����һ���ַ�
	int index:����֮�����ӵ��ַ����ڵ�����
	char c:���ӵ��ַ�

	@Return void
*/
void mystring::add(int index, char c)
{
	if (index < 0 || index > length)
		cout << "add��������,indexΪ�Ƿ�ֵ" << endl;
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
	��ȡһ���ַ�
	int index:��ȡ���ַ����ڵ�����

	@Return char
*/
char mystring::get(int index)
{
	if (index < 0 || index >= length)
	{
		cout << "get��������,indexΪ�Ƿ�ֵ" << endl;
		return '\0';
	}
	else
		return str[index];
}

/*
	�ı�һ���ַ�
	int index:�ı���ַ����ڵ�����
	char c:�ı����ַ�

	@Return char
*/
char mystring::set(int index, char c)
{
	if (index < 0 || index >= length)
	{
		cout << "set��������,indexΪ�Ƿ�ֵ" << endl;
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
	ɾ��һ���ַ�
	int index:ɾ�����ַ����ڵ�����

	@Return char
*/
char mystring::remove(int index)
{
	if (index < 0 || index >= length)
	{
		cout << "remove��������,indexΪ�Ƿ�ֵ" << endl;
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
	��ȡ�Ӵ���һ�γ������ַ����е�����
	const mystring& target_str:�Ӵ�

	@Return int
*/
int mystring::index(const mystring& target_str)
{
	return index(target_str, 0);
}

/*
	��ȡ�Ӵ���ָ��λ�ÿ�ʼ��һ�γ������ַ����е�����
	const mystring& target_str:�Ӵ�
	int from_index:��ʼλ�õ�����

	@Return int
*/
int mystring::index(const mystring& target_str, int from_index)
{
	if (length < target_str.length)
	{
		cout << "index��������:ģʽ�����ȴ�����������" << endl;
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
	ʹ��KMP�㷨,��ȡ�Ӵ���һ�γ������ַ����е�����
	const mystring& target_str:�Ӵ�

	@Return int
*/
int mystring::index_kmp(const mystring& target_str)
{
	return index_kmp(target_str, 0);
}

/*
	ʹ��KMP�㷨,��ȡ�Ӵ���ָ��λ�ÿ�ʼ��һ�γ������ַ����е�����
	const mystring& target_str:�Ӵ�
	int from_index:��ʼλ�õ�����

	@Return int
*/
int mystring::index_kmp(const mystring& target_str, int from_index)
{
	if (length < target_str.length)
	{
		cout << "index_kmp��������:ģʽ�����ȴ�����������" << endl;
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
	��ȡ�ַ�����KMP�㷨�е�next����
	const mystring& target_str:�ַ���

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
	��ȡ�ַ���,��ָ����ʼλ�õ���β
	int begin_index:��ʼλ�õ�����

	@Return mystring
*/
mystring mystring::sub_string(int begin_index)
{
	mystring return_str;
	if (begin_index < 0 || begin_index >= length)
	{
		cout << "sub_string��������,indexΪ�Ƿ�ֵ" << endl;
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
	��ȡ�ַ���,��ָ����ʼλ�õ�ָ������λ��
	int begin_index:��ʼλ�õ�����
	int end_index:����λ�õ�����

	@Return mystring
*/
mystring mystring::sub_string(int begin_index, int end_index)
{
	mystring return_str;
	if (begin_index < 0 || begin_index >= length || end_index < 0 || end_index >= length || begin_index >= end_index)
	{
		cout << "sub_string��������,indexΪ�Ƿ�ֵ" << endl;
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
	����[]�����
	int index:����

	@Return char
*/
char mystring::operator[](int index)
{
	if (index < 0 || index >= length)
	{
		cout << "[]����������,indexΪ�Ƿ�ֵ" << endl;
		return '\0';
	}
	else
		return str[index];
}

/*
	����+�����,ʹ�����ַ���ƴ�ӵ�һ��
	const mystring& add_str:�ַ���

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
	����==�����,�ж������ַ����Ƿ���ȫ���
	const mystring& compare_str:�ַ���

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
	����<<�����
	ostream& os:�����
	mystring str:������ַ���

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
