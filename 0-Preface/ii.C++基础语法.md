---
layout: page
permalink: /ii/
---

# ii. New to C++

## 前言

对于初学者来说，请抱着“计算机是不会错的，那么我做错了什么，我错在哪”的心态。如果碰到了error，请至少按照以下步骤做：
1. 观察编译器报错，如果是英文，可以在线翻译这是什么意思
2. 检查拼写错误，比如缺分号；main拼成mian，开了中文输入法打了标点
3. 百度

## 准备工作

### 编译器

### IDE

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

### 内置变量类型

1. bool
2. char
3. int
4. float
5. double

## 函数

## 头文件

## using指示

`using namespace std;`的作用是，将形如`std::cout`的声明全都可以用`cout`的简短化形式调用

{: .note }
> 在实际项目中不推荐使用，更推荐using声明`using std::cout;`