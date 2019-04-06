# MyString
### ���������ݽṹ
[������](https://github.com/heiyedeshengyin/LinkedList) 
[˫����](https://github.com/heiyedeshengyin/DoublyLinkedList) 
[������](https://github.com/heiyedeshengyin/BinaryTree) 
[����������](https://github.com/heiyedeshengyin/BinarySearchTree) 
[AVL��](https://github.com/heiyedeshengyin/AVLTree) 
[�����](https://github.com/heiyedeshengyin/RedBlackTree)

### ���
�ַ��������������ݽṹ  
ע��:Ŀǰֻ�ܴ洢ASCII����е��ַ�

### ���ݽṹ
```cpp
class MyString
{
	char *str;	//��װ���ַ�����
	int length;	//�ַ����ĳ���
};
```

### KMP�㷨
KMP�㷨���ַ����л�ȡ�Ӵ�λ�õĸ�Ч���㷨  
����Ŀ������KMP�㷨����غ�������
```cpp
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
```

### �����б�
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

### ʹ��˵��
���ؽ�ѹ��ʹ��Visual Studio��MyString.sln����  

### �ο�����
[(ԭ��)���KMP�㷨 - ��~Ӱ - ����԰](https://www.cnblogs.com/yjiyjige/p/3263858.html)