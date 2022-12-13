
# 线性结构

上一节我们讲了数组，数组的插入和删除可以发生在任何位置  
我们将下标为0的这一头称为头部front，另一头称为尾部back。  
栈是插入和删除都只能发生在尾部（栈顶），队列是只能在尾部插入和头部删除。进一步的，如果同时允许在头部和尾部进行插入和删除，称为双端队列(double-ended queue, deque)

## ADT 逻辑结构和物理结构

## 数组


## 栈stack

栈的常见操作
1. push
2. pop
3. size
4. empty

## 队列queue

队列的常见操作
1. enqueue 
2. dequeue 
3. size 
4. empty

## 链表list


{: .note }
接下来的内容可以跳过

## 封装

## 类的声明

STL已经有stack和queue预先的实现，称为容器适配器，其内部可以为std::vector和std::deque实现
```cpp
#include <stack>
#include <queue>
std::stack<int> s;
std::queue<int> q;
```