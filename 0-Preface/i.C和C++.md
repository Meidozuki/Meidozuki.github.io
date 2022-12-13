---
layout: page
permalink: /i/
title: '0-i. C and C++'
---

# I. C and C++

## C++和C很像

C++语法上和C很像，面向过程编程部分和C十分相像，同时C++也允许使用<stdio.h>或<cstdio>等头文件保持兼容性

如，C中的<stdbool.h>可以在C++11-17中使用<cstdbool>，不过这个头文件在C++20去除了

详细可以查看 https://en.cppreference.com/w/cpp/standard_library

## C++并不是C的超集

C++之父曾经建议过缩小C与C++之间的差距，然而在C99中，虽然相较于C89它吸收了一些C++的特性，但有些内容被有意无意地塑造成了与C++不兼容的情况

1. C中允许void*隐式转换

```C
void *ptr;
/* Implicit conversion from void* to int* */
int *i = ptr;

int *p = malloc(2*sizeof(int));
```
这段代码能顺利通过C编译，而在C++中会报错`error: invalid conversion from 'void*' to 'int*'`（gcc），必须在i和p前加上`(int*)`显式转换


2. C支持`int foo(int a[const]); // equivalent to int *const a` 声明，但C++不支持


3. C支持选择部分初始化数组，如`char s[20] = {[0] = 'a', [8] = 'g'};`而C++不支持


4. 对于char字面量的不同解释

在C中，'a'被解释为int，即sizeof('a')等于sizeof(int) ,并且'a'总是signed int
在C++中，'a'被解释为char，即sizeof('a')等于1，而其是否signed由编译器实现决定

etc.

引用自：https://codedocs.org/what-is/compatibility-of-c-and-c  
如果无法科学上网，我在本目录下留了一份print to PDF存档
