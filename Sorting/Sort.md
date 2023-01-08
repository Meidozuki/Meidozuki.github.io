---
layout: page
permalink: /sort/
---

<head>
    <script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>
    <script type="text/x-mathjax-config">
        MathJax.Hub.Config({
            tex2jax: {
            skipTags: ['script', 'noscript', 'style', 'textarea', 'pre'],
            inlineMath: [['$','$']]
            }
        });
    </script>
</head>

# 排序
{: .no_toc}
1. TOC  
{:toc}

### 交换
{: .no_toc}

交换变量a,b有以下方法

1. 临时变量  
    > t=a; a=b; b=t;
    > 
    > STL中的std::swap()就是这种方法，这种方法通用且容易理解
2. 基础数据位运算^=  
    > a^=b^=a^=b;
    >
    > 仅限基础数据，并且需要&a != &b，否则第一步之后就变成0了
3. 代数运算法
    > 在高代证明*交换行列式两行行列式不变*时用到过
    > 
    > a+=b; b-=a; b=-b; a-=b;
    >
    > 同样需要&a != &b,否则在第二步就变成0了

以下排序均用std::swap来进行交换。由于升序和降序排序没有本质区别且易相互转换，以下以升序排序为例。

### 3种简单排序
{: .no_toc}

接下来我们介绍3种简单排序，它们的代码量都在10行左右甚至更少（也可能出现在中学的信息课本中）。分别是冒泡排序、选择排序、插入排序

下面以python语法的伪代码描述排序算法，C++实现见simple_sort.cpp

## 冒泡排序BubbleSort

```python
@loop_n_times # 循环重复n次
def f():
    for i in range(1,n): # 从左到右遍历
        if a[i] < a[i-1]: # 遇到逆序就交换
            swap()
```

冒泡排序的特征：每一趟会交换出最大值到右边，并且沿途也可能会发生交换

最差情况为原本即为逆序排列，这时每一趟相当于仅把最左边的元素“搬运”到最右边，比较次数= $\Theta(n^2)$

效率低，被[wiki](https://en.wikipedia.org/wiki/Sorting_algorithm)评价为
> Bubble sort, and variants such as the Comb sort and cocktail sort, are simple, highly inefficient sorting algorithms. They are frequently seen in introductory texts due to ease of analysis, but they are rarely used in practice.

## 选择排序SelectionSort

```python
for i in range(0,n):
    
    min_idx = argmin(i,n) # 选定一个最小值
    swap(a[i],a[min_idx]) # 交换到最左边
```

选择排序每次仅在当前无序序列中选择一个最值（最大值/最小值）放到两端（最右边/最左边）

最差情况也为原本即为逆序排列，比较次数= $\Theta(n^2)$

选择排序由于每次仅交换一个最大值，对于其他位置，不改变局部单调性。

选择排序推荐在数据类型 $time(Copy) \gt time(Compare)$ 时使用

## 插入排序InsertionSort

```python
for i in range(1,n):
    # 将a[i]插入到a[0]~a[i-1]中
    pos = lower_bound(0,i,a[i])
    a[0:i] = a[0:i-1].insert(pos,a[i])
```

插入排序每次将有序序列长度扩大1，即对于a[i]，在插入后a[0]-a[i]都是有序的。对于新加入的元素a[i]，小于它的元素不动，大于它的元素右移一格，然后插入a[i]。该过程如同扑克牌插入牌一样因此称为插入排序

最差情况也为原本即为逆序排列，比较次数= $\Theta(n^2)$

插入排序利用了局部有序性，因此可以在子序列比较时提前停止。每次插入时相当于一次改进的冒泡算法，在a[i]左边只有比较没有交换，相比于冒泡排序减少了比较次数。

插入排序在简单数据的实际测试中是3种简单排序算法中相对高效的。

## 简单排序算法的分析
{: .no_toc}

{: .highlight}
> 本节可略过

基于邻位比较算法（冒泡和插入）的最差时间复杂度不会低于 $\Theta(n^2)$

将待排序视为一个排列(permutation)，其最大的逆序数为 $1+2+3+...+n-1={n^2+n \over 2}$，平均逆序数为 ${n^2+n \over 4}$。而一次相邻元素的交换只能使逆序数-1，因此平均需要 ${n^2+n \over 4}=\Theta(n^2)$次比较

### 进一步的排序算法
{: .no_toc}

3种简单排序算法的平均时间复杂度都为 $\Theta(n^2)$，接下来我们来探究如何进一步优化排序算法

- 插入排序在使用了叫做希尔增量的技巧后，时间复杂度可以减少到 $O(n^{1.5})$ 甚至更低，但时间复杂度分析很复杂（冒泡排序也可以使用这种方法，称为梳子排序）  
- 选择排序在使用堆优化寻找最值后，时间复杂度为 $\Theta (nlogn)$  
- 使用了一种分而治之的思想，先分别排序左半边和右半边，然后合并左右段，就得到了归并排序，时间复杂度为 $\Theta (nlogn)$
- 一种被称为快速排序的算法，基于交换排序，使用了分而治之的思想，平均时间复杂度可以为 $\Theta(nlogn)$ ，但本身时间复杂度 $\omicron(n^2)$  

## 堆排序HeapSort

先看选择排序

```python
for i in range(0,n):
    max_idx = argmax(0,n-i)
    swap(a[n-1-i],a[max_idx])
```

当我们不采用遍历寻找最大值（即argmax），而采用最大堆获得最大值时，就得到了堆排序，下面是一段非原位生成(Out-place)的伪代码

```python
heap = Heap.create(a)
for i in range(0,n):
    max_val = heap.pop()
    a[n-1-i] = max_val
```

由于堆在出堆时，会将最大元素移动到末尾，因此只需要稍微改动下出堆的代码就完成了原位生成(In-place)的堆排序，代码见sort.cpp

由于建堆需要 $O(n)$ 时间，每次调整需要 $O(logn)$时间，调整n次，可得堆排序 $T(n)=O(nlogn)$ 。最好情况下省去了建堆时间可得 $T(n)= \Omega(nlogn)$ 。因此堆排序的时间复杂度为 $\Theta(nlogn)$


## 希尔排序ShellSort

```python
increasement = [1,3,7] # ... 
increasement.reverse()
for d in increasement: # 对于从大到小的每一个增量
    for i in range(d): # 按照增量d的间隔进行插入排序
        insert_sort(a[i::d])
```

希尔排序算法的时间复杂度不仅与待排序序列有关，还与增长序列的选取有关，希尔排序的平均复杂度分析极为复杂，希尔排序的最差时间复杂度为 $O(n^{1.3})$~ $O(n^2)$

Shell增量序列，即希尔排序在1959年刚发明时提出

Hibbard增量序列在1963年提出，其通项为 $a_n=2^k -1$ ，即 $1,3,7,15,31,...$ ，可以证明采用Hibbard增量的希尔排序具有 $T(n)=O(n^{3/2})$ 。根据[wikiwand](https://www.wikiwand.com/en/Shellsort#Gap_sequences)，在实际场景中，希尔排序的平均时间复杂度为 $O(n^{5/4})$

此外，根据[wikiwand](https://www.wikiwand.com/en/Shellsort)，具有长度为p的增量序列的希尔排序，对N个元素进行排序时，其平均时间复杂度具有下界：当 $p\le log_2N$ 时, $\Omega(pN^{1+1/p})$ ；当 $p\gt log_2N$时, $\Omega(pN)$ 。即希尔排序可以达到近似 $NlogN$ 的时间复杂度。并且目前已知的所有希尔排序的平均时间复杂度和最好时间复杂度同阶

## 归并排序MergeSort

```python
def merge_sort(begin,end,n):
    if (n < threshold): # 当小于某个值（比如2）的时候停止递归
        simple_sort(begin,end,n) # （比如2）只剩1个元素则直接返回，剩2个元素的时候进行比较，然后返回
    else: # 递归排序
        mid = begin + n//2
        merge_sort(begin,mid,n//2) # 递归排序左半边
        merge_sort(mid,end,n - n//2) # 递归排序右半边

        # 将有序段[begin,mid)和[mid,end)合并
        merge(begin,end,mid)
```

> 此处可以看到python代码和C++代码差别已经很小了，但为了精简篇幅，我们忽略大括号和变量类型  
> ps: 此处的begin和end既可以是下标(如int)，也可以是随机读取迭代器(如std::vector\<int>::iterator)

归并排序由于其对于左半段和右半段进行的合并操作(merge)而得名

时间复杂度和堆排序一样为 $\Theta(nlogn)$，需要额外的 $O(n)$空间来存储merge的结果

在本机跑出的结果大约比堆排序快一倍。但由于归并排序需要额外复制，不建议在copy-heavy的情况下使用

## 快速排序QuickSort

```python
def quick_sort(begin,end):
    if (n < threshold): # 当小于某个值（比如10）的时候停止递归
        simple_sort(begin,end,n) # 进行简单排序，如插入排序
    else: # 递归排序
        pivot = pick() # 选择pivot
        mid = partition(begin,end,pivot) # 将序列划分为比pivot的小的左半边和比pivot大的右半边
        quick(begin,mid) # 递归排序左半边
        # 注意与归并不同的地方，此处mid是pivot的最终位置
        quick(mid+1,end) # 递归排序右半边
```

### pivot的选择
{: .no_toc}

1. 随机选择一个元素，在大多数情况下表现不错
2. 选择头或尾，在逆序情况下退化为 $O(n^2)$
3. 选择left,right,mid中间大的元素，常用

可以用if-else分支也可以像以下这样
```cpp
inline int pickPivot(int a,int b,int c,const int *p) {
    int max, min;
    if (p[a] < p[b]) {
        max = b;
        min = a;
    }
    else {
        max = a;
        min = b;
    }

    if (p[c] > p[max]) {
        max = c;
    }
    else if (p[c] < p[min]) {
        min = c;
    }

    return a+b+c-max-min;
}
```

### 分割方法
{: .no_toc}

用pLeft和pRight指向最左和最后，pLeft遇到大的元素停下来，pRight遇到小的元素停下来，交换，继续下一轮直到pLeft > pRight

## 通用排序算法的 $nlogn$ 下界

二叉决策树

任何一种基于比较的排序算法至少需要 $\Theta(nlog n)$ 时间

## 基数排序
