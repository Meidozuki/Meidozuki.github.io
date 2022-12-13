---
layout: page
permalink: /1/
---

# 1-初识STL

## 什么是STL

Standard Template Library

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
string s1;
string s2=s1;
string s3("Hello ");
string s4 = "world!";
cout << s3+s4;
}
```

同时还内置了以下这些函数和操作符（因此你可以暂时不用考虑<string.h>的知识）
```
s.empty()
s.size()
s[n]
s.at(n)
operator == != < <= > >=
```

{: .note }
> std::string在实际使用中非常低效，尤其是substr返回子串时，这一点在C++17引入了`<stringview>`

## 标准库类型vector

## 数组

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
