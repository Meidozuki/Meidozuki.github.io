---
layout: page
permalink: /1/
---

# 1-初识STL

## 什么是STL

Standard Template Library, 简称STL, 中文又叫标准库。

前言中提到的内置类型是由C++语言直接定义的。而标准库还定义了另外一些具有更高级性质的类型，它们尚未直接实现到计算机硬件中。

使用标准库类型，需要使用类似`std::cin`的形式访问命名空间std中的名字cin。可以使用using声明来避免每次都加上前缀（如std::），如接下来要介绍的string类型  
```cpp
#include <string>
using std::string;
```  
或者使用using指示`using namespace std;`

## 标准库类型string

std::string是STL提供的字符串类型，可以比较方便的使用，比如改写之前的Hello world程序

```cpp
#include <iostream>
#include <string>
using namespace std;
 
int main() 
{
    string s("Hello, World!")
    cout << s;
    return 0;
}
```

std::string的初始化、赋值、拼接
```cpp
{
string s1;  //空string
string s2=s1;   //复制构造s2
string s3("Hello ");    //s3是字面量"Hello "的副本
string s4 = "world!";
cout << s3+s4;
}
```

同时还内置了以下这些函数和操作符（因此你可以暂时不用考虑<string.h>的知识）
```
s.empty()       //为空返回true，否则返回false
s.size()        //返回s中字符的个数
s.length()      //同上
s[n]            //返回s中第n个字符的引用
s.at(n)         //同上，但是下标越界时抛出异常
operator == != < <= > >=    //按照字典顺序对字符进行比较
```

更详细的介绍可以阅读《C++ primer》P75

{: .note }
> std::string在实际使用中非常低效，尤其是substr返回子串时，这一点在C++17引入了`<stringview>`

## 标准库类型vector

std::vector是STL提供的一种表示对象的集合，集合中每个对象都有个与之对应的索引，索引用于访问对象。vector也常被称作容器

使用vector需要包含头文件
```cpp
#include <vector>
using std::vector;

vector<int> ivec;
```
其中int指明vector所包含的元素，即ivec保存int类型的对象。（这种带<>的方式称为模板，我们可以暂时不管它的语法）

{: .note }
> C++11新标准正式允许写形如vector<vector<int>>的数组的数组，但在C++11之前或在一些老版本编译器上（比如DevCpp）应该在> >间添加空格表示和流操作运算符>>区分

vector的初始化
```cpp
{
vector<T> v1;   //空string
vector<T> v2(v1);   //复制构造v2
vector<T> v3(n, val);   //创建长度为n的数组，每个元素的值都为val
vector<T> v4(n);    //创建长度为n的数组，每个元素的值都是T的初始化值（比如0）
vector<T> v5{1,2,3}; //v5包含了列表长度(3)个元素，每个元素被赋予响应的初始值(1,2,3)
}
```

{: .highlight}
> 注意：v5在列表初始化时用的是花括号而不是圆括号

与string类似，vector的常用操作如下

```
v.push_back(t)  //向v尾部添加一个值为t的元素
v.empty()       //为空返回true，否则返回false
v.size()        //返回v中字符的个数
v[n]            //返回v中第n个字符的引用
v.at(n)         //同上，但是下标越界时抛出异常
operator == != < <= > >=    //按照字典顺序对字符进行比较
```

### range-based for
{: .highlight }
(since C++11)  

可以使用以下形式来输出vector中的元素（使用cout需要include<iostream>）
```cpp
vector<int> v{1,2,3,4,5};
for (auto &i : v) {
    cout << i << " ";
}
```

类似`for (auto &i : v)`的语句被称为range-based for，在其他语言中也被称为加强for循环。上述代码等价于以下普通for循环
```cpp
vector<int> v{1,2,3,4,5};
for (int idx = 0;idx < v.size();++idx) {
    cout << v[idx] << " ";
}
```

### 数组的可选择形式

1. 原生数组

`int a[10];`

> 建议：性能高，但需要提前确定长度。用于快速背模板，多维数组等

2. std::vector

```
#include <vector>
std::vector<int> a;
```
> 建议：较为通用，在数组大小可变时替代array

3. C++ std::array

```
#include <array>
std::array<int,10> a;
```
{: .highlight }
(since C++11)  
> 和原生数组几乎一致，但配备了STL的许多通用方法如size,at等

4. std::list std::deque

```
#include <list>
std::list<int> a;
```
> 建议：在数组头部操作较多（如queue和双端队列）时使用
