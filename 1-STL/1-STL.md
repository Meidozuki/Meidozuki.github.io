# 初识STL

## 什么是STL

Standard Template Library

## 标准库类型string

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

```
{
string s1;
string s2=s1;
string s3("Hello ");
string s4 = "world!";
cout << s3+s4;
}
```

```
s.empty()
s.size()
s[n]
s.at(n)
operator == != < <= > >=
```

*std::string在实际使用中非常低效，尤其是substr返回子串时，这一点在C++17引入了`<stringview>`

## 标准库类型vector

## 数组

1. 原生数组

> 建议：快速背模板，多维数组
> 
2. std::vector

> 建议：通用
> 
3. C++ std::array

> 和原生数组几乎一致，但可以用at检查下标越界等
> 
4. std::list std::deque

> 建议：在数组头部操作较多（如queue和双端队列）时使用
