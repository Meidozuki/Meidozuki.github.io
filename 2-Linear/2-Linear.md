---
layout: page
title: 2-Linear
has_children: true
permalink: /2/
---

# 2-线性结构

对于我们为什么要学数据结构与算法分析，可以看[最大子列和](MaxSubseqSum.md)的例子

## ADT 逻辑结构和物理结构

## 数组

上一节我们讲了数组，数组的插入和删除可以发生在任何位置
我们将下标为0的这一头称为头部front，另一头称为尾部back。
栈插入和删除都只能发生在尾部（栈顶），队列只能在尾部插入和头部删除。进一步的，如果同时允许在头部和尾部进行插入和删除，称为双端队列(double-ended queue, deque)

## 栈stack

栈插入和删除都只能发生在尾部，完成了push和pop函数就可以认为是一个栈了

栈的常见操作

1. push
2. pop
3. size
4. empty

```cpp
void stack_dynamic() {
    //动态数组
    //优点：vector封装友好，仅需手动实现pop; 同时尾部操作底层实现也很高效
    vector<int> s;

    auto pop = [&s] () {
        int t = s.back();
        s.pop_back();
        return t;
    };

    s.push_back(1);
    s.push_back(2);
    std::cout << "size of stack is " << s.size() << '\n';
    while (!s.empty()) {
        std::cout << pop() << ' ';
    }
    std::cout << '\n';
}
```

由于C++不支持在函数内声明函数，为了保持代码整体在一个函数内，我使用了lambda表达式来声明pop，其等价于
```cpp
int pop(vector<int> &s) {
    int t = s.back();
    s.pop_back();
    return t;
}
//以下为上面的lambda表达式代码，除了第一行的函数声明外，两者一模一样
auto pop = [&s] () {
    int t = s.back();
    s.pop_back();
    return t;
};
```

{: .note}
> 函数pop接收一个vector\<int>&，返回int。vector\<int>为上一节讲过的STL可变数组，其成员类型为int。`&`为C++特性，表示引用，在[前言](../0-Preface/ii.C++基础语法.md)中提到过，可以认为引用创建了一个别名

此外由于vector动态分配大小，在push_back时和静态数组不同，可以省去检查栈满。同时由于stack在尾部操作，vector动态实现足够高效

也可以用原生数组和静态vector实现，它们的代码写法十分类似。原生数组和静态vector实现见[stack](stack.cpp)

## 队列queue

队列的常见操作

1. enqueue
2. dequeue
3. size
4. empty

```cpp
void queue_static() {
    int Q[100];
    int front,rear;
    front=rear=0;

    auto empty=[](int front,int rear) {
        return rear<=front;
    };

    auto enqueue=[](int x,int Q[],int &rear) {
        Q[rear++]=x;
    };

    auto dequeue=[&empty](int Q[],int &front,int &rear) {
        if (!empty(front,rear)) {
            int f = Q[front++];
            return f;
        }
    };


    enqueue(1,Q,rear);
    enqueue(2,Q,rear);
    std::cout << "size of queue is " << rear-front << '\n';

    while (!empty(front,rear)) {
        std::cout << dequeue(Q,front,rear) << ' ';
    }
    std::cout << '\n';
}
```

由于queue同时在头部和尾部操作，而vector在头部操作时性能较低，因此推荐用静态数组实现  
使用vector的实现见[queue](queue.cpp)

## 链表list

链表的实现需要借助指针

链表常用以下结构定义
```cpp
struct ListNode {
    int data;
    ListNode *next;
};
```
{: .highlight}
> struct在结尾的}后还有一个分号;不过绝大部分编译器都会自动填充上

## 代码封装 struct和class

{: .note }
接下来的内容可以暂时跳过  

上述代码实现中，我们看到，为了实现一个stack或者queue，需要在外部定义一些函数，这相对来说不如vector的API方便。我们可以考虑将vector的数据和stack/queue的操作封装在一起，称为一个类class，这就是面向对象编程（OOP）的思想

在C++中，struct和class几乎一致，唯一的区别仅仅是struct默认的访问指示符是public。即，下述代码是等价的
```cpp
struct MyVector : vector<int> {
    //成员
}

class MyVector : public vector<int> {
public:
    //成员
}
```

如，我们可以改造一下之前的stack
```cpp
struct Stack {
    vector<int> data;

    void push(int x) { data.push_back(x); }
    int top() { return data.back(); }
    int pop() {
        int t = s.back();
        s.pop_back();
        return t;
    }

    int size() { return data.size(); }
    bool empty() { return data.empty(); }
}

int main(void) {
    Stack s;
    
    s.push(1);
    s.push(2);
    std::cout << "size of stack is " << s.size() << '\n';
    while (!s.empty()) {
        std::cout << pop() << ' ';
    }
    std::cout << '\n';
}
```

## 容器适配器

STL定义了3个顺序容器适配器，stack，queue和priority_queue，其内部可以为std::vector和std::deque实现。容器适配器是指，使某种事物的行为看起来像另外一种事物一样，比如让deque操作起来像stack一样。

```cpp
#include <stack>
#include <queue>
std::stack<int> s;
std::queue<int> q;
```

你也可以自己试着写一个你自己的容器适配器，比如MyStack。初步的实现很简单，将vector作为private成员，将stack的操作作为public函数即可（不考虑模板的话）