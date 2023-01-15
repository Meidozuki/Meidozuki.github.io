---
layout: page
title: 2-*最大子列和
permalink: /2+/
parent: 2-Linear
---

# 最大子列和问题

问题：已知 $\{a_i\mid 0 \le i \lt n\}$，定义子列和为 $S=\Sigma_{L,R} \{a_i\mid L\le i\lt R,L\le R\lt n\}$

（简单起见我们先假定 $a_i \ne 0$，可以通过微调条件判断包括 $a_i = 0$ 的情况）

如，{0,-5,1,2,3,-1}的最大子列和为6，{-1,-2,-3}的最大子列和为0

## 暴力枚举

最简单粗暴的方式是对每一个子列求和，可以看到总共有 ${(n+1)n \over 2}+1=\Theta (n^2)$项

```cpp
int MaxSubSum(int a[], int n) {
    int max_sum=0;
    for (int i=0;i < n;++i) {
        int s=0;
        for (int j=i;j < n;++j) {
            s+=a[j];
            if (s > max_sum) {
                max_sum = s;
            }
        }
    }
    return max_sum;
}
```

## 分而治之

我们可以采用一种被称为分而治之（Divide and Conquer）的思路，将整个数组分为左右两部分，然后分别求出左边的最大子列和，右边的最大子列和，横跨中点的最大子列和，再求它们的最大值，该算法的时间复杂度为$\Theta(nlog_2 n)$

```cpp
int DivideAndConquer(int *left, int *right) {
    int n = right-left;
    //递归结束条件
    if (n <= 0) return 0;
    if (n == 1) return *left;

    int *mid = left + n/2;
    //递归查找左右半边最大子列和
    int left_sum = DivideAndConquer(left,mid);
    int right_sum = DivideAndConquer(mid+1, right);

    //查找跨过中点的最大子列和
    int left_cross=0, right_cross=0, s=0;
    for (auto p=--mid;p >= left;--p) {
        s += *p;
        left_cross = std::max(left_cross, s);
    }
    s = 0;
    for (auto p=++mid;p < right;++p) {
        s += *p;
        right_cross = std::max(right_cross, s);
    }

    int re = std::max(left_sum,right_sum);
    re = std::max(re, left_cross+*mid+right_cross);
    return re;
}

int MaxSubSum(int a[],int n) {
    //&a[0]+n不是a[]的内容，它只用来判断循环结束条件，这被称为尾后迭代器
    DivideAndConquer(&a[0],&a[0]+n);
}
```

思考一下，横跨中点的最大子列和为什么可以这么求，为什么不求出*所有*横跨中点的子列和，再求其最大值（下述代码）

```cpp
for (int i=0;i <= n/2;++i) {
    s = a[n/2];
    for (int j=n/2+1;j < n;++j) {
        s += a[j];
        cross_sum = std::max(cross_sum,s);
    }
}
```

## 在线算法/线性算法

我们可以采用一种在线算法实时计算当前的最大子列和，它的时间复杂度仅为$\Theta(n)$，不过要理解其正确性不太容易

```cpp
int MaxSubSum(int a[],int n) {
    int max_sum = 0, cur_sum = 0;
    for (int i=0;i < n;++i) {
        cur_sum += a[i];
        if (cur_sum < 0) {
            cur_sum = 0;
        }
        else if (cur_sum > max_sum) {
            max_sum = cur_sum;
        }
    }
    return max_sum;
}
```

第二个if语句与前文没有什么区别，描述了max_sum的更新规则

再来看第一个if语句，如果某一段的子列和为负，那么它一定不是最大子列的头部（或尾部）。证明是容易的，假设 $a_i,...,a_j,a_{j+1},...,a_k$ 为最大子列，其子列和为 $S$，并且 $a_i,...,a_j$ 段子列和为负值，其子列和为 $Neg$，那么 $a_{j+1},...,a_k$ 段子列和为 $S+Neg\gt S$，这与假设矛盾，所以最大子列不会以包含子列和为负的序列开头。（类似的可以证明尾部也是这样。但尾部的情况已经被max_sum更新规则包括了）

接下来看整体算法。我们已经证明了一些不是最大子列的情况不会被包含，那么最大子列是否一定被包含在遍历序列中呢？答案是肯定的

观察最大子列的特征，上文已经证明，最大子列不以子列和为负的序列开头或结尾。同时，可以通过类似的证明，最大子列尽可能地延展、去包含非负的序列。我们实际上遍历了所有极大的候选子列。如对于序列{1,2,3,4}，我们遍历到{1,2,3}，此时的最大子列是{1,2,3}，既然我们选择了{1,2,3}，就不用考虑它的子列了（如{2,3}），同样的，下一步我们遍历到{1,2,3,4}，也不用考虑它的子列了（如{2,3,4}，{3,4}）。*换句话说*，由于最大子列的性质，如果我们当前的最大字串候选cur_max_seq是 $a_i,...,a_j$,那么**真正的最大子列max_seq一定不以 $a_{i+1},...,a_j$ 中的元素开头**。这就是为什么理论上在线算法能比暴力枚举更快（分而治之只在中间点运用了这点，而在线算法对数组全体都运用了这点）

## Summary

最大子列和是一个非常经典的问题。它直观地展示了对于同一个问题，不同的算法之间能有十分大的区别。通过这个问题，我们也可以直观地认识到一个好的算法有多么重要