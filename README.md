# MyString
### 以往的数据结构
[单链表](https://github.com/heiyedeshengyin/LinkedList) 
[双链表](https://github.com/heiyedeshengyin/DoublyLinkedList) 
[二叉树](https://github.com/heiyedeshengyin/BinaryTree) 
[二叉搜索树](https://github.com/heiyedeshengyin/BinarySearchTree) 
[AVL树](https://github.com/heiyedeshengyin/AVLTree) 
[红黑树](https://github.com/heiyedeshengyin/RedBlackTree)

### 简介
字符串，基本的数据结构  
注意:目前只能存储ASCII码表中的字符

### 数据结构
```cpp
class MyString
{
	char *str;	//封装的字符数组
	int length;	//字符串的长度
};
```

### KMP算法
KMP算法是字符串中获取子串位置的高效的算法  
该项目内置了KMP算法，相关函数如下
```cpp
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
```

### 函数列表
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

### 使用说明
下载解压后，使用Visual Studio打开MyString.sln即可  

### 参考资料
[(原创)详解KMP算法 - 孤~影 - 博客园](https://www.cnblogs.com/yjiyjige/p/3263858.html)