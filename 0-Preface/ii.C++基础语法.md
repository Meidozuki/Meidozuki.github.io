---
layout: page
permalink: /0/ii/
title: 'ii. C++基础语法'
parent: 0-Preface
---

# ii. New to C++

## 前言

对于初学者来说，请抱着“计算机是不会错的，那么我做错了什么，我错在哪”的心态。如果碰到了error，请至少按照以下步骤做：
1. 观察编译器报错，如果是英文，可以在线翻译这是什么意思
2. 检查拼写错误，比如缺分号；main拼成mian，开了中文输入法打了标点
3. 百度

## 准备工作

### 编译器

Windows: MinGW, MSVC, Clang...

Unix: GCC...

### IDE

- DevC++(很老，自带MinGW)
- CLion(功能全，巨无霸，收费)
- VS(不推荐，自带MSVC)
- VSCode(体积小，免费)

## hello world
```cpp
#include <iostream>
using namespace std;
 
int main() 
{
    cout << "Hello, World!";
    return 0;
}
```

## 变量

### 基本内置类型

- void
- bool
- 整数类型(interger types)
[signed/unsigned]

| type | 最少bits |Win64|Linux64|
| -- | -- | -- | -- |
|char|8|
|short int|16|
|int|16|32|32|
|long int|32|32|64|
|long long int<br>(since C++11)|64|64|64|

- float
- double
- long double

### 复合类型

- 引用

{: .note}
> C++11增加一种引用——右值引用，我们这里指的引用实际上是左值引用
>
引用实际上是一种别名，将引用和它的初始量**绑定**在一起

```cpp
int ival=1024;
int &ref_val = ival; //声明引用
// int &ref_val2; //编译错误，引用必须被初始化
int &ref_val3 = ref_val; //将ref3绑定到ref所绑定的对象上，等价于int &ref_val3 = ival;

cout << ival << endl;
// Output: 1024
ref_val = 2; //对引用的操作等价于对它绑定的对象进行操作
cout << ival << endl;
// Output: 2
```

- 指针

## 函数

## 头文件

## using指示

`using namespace std;`的作用是，将形如`std::cout`的声明全都可以用`cout`的简短化形式调用

{: .note }
> 在实际项目中不推荐使用，更推荐using声明`using std::cout;`