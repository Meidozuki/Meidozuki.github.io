---
layout: page
permalink: /2+/
title: 2-*最大子列和
parent: 2-Linear
---

# 最大子列和问题

问题：已知 $\{a_i | 0 \le i \lt n\}$，定义子列和为 $S=\Sigma_{L,R} \{a_i| L\le i\lt R,L\le R\lt n\}$

如，{0,-5,1,2,3,-1}的最大子列和为6，{-1,-2,-3}的最大子列和为0

## 暴力枚举

$O(n^2)$

## 分而治之

$O(nlog_2 n)$

## 在线算法/线性算法

$O(n)$