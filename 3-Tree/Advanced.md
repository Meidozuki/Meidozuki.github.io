---
---
# title

## AVL Tree

在Tree章节中我们提到树的基本思想是作为一种操作平均时间复杂度为O(logN)的数据结构。然而如果一颗树的操作（如插入）恰好不幸地使树的左右子结点失衡时，树很有可能退化为单链表，此时操作的时间复杂度退化为O(N)

![树的退化](img/devolution.dot.jpg)

为了避免出现这种情况，我们引入平衡二叉树的概念

AVL树是最早发明的自平衡二叉树，其名字来源于其发明者G. M. Adelson-Velsky和E. M. Landis

### 平衡因子

某结点的平衡因子定义为，其左子树的深度 - 右子树的深度

AVL树中，所有结点的平衡因子因子的绝对值不大于1

### 旋转

AVL树通过一种称为旋转的操作来使失衡的子树重新平衡，分别为左旋和右旋，为了方便起见，记为L旋转和R旋转

```graphviz
digraph  {
    label=L_旋转
    subgraph cluster{
        label=before
        X->p
        X->R_X
        p->L_p
        p->R_p
        L_p[shape=box,height=1]
        
        R_X[shape=box]
        R_p[shape=box]
        node[style=invis]
        edge[style=invis]
        R_X->0
    }
    
    subgraph cluster2{
        label=after
        p2->L_p2
        p2->X2
        X2->R_p2
        X2->R_X2
        L_p2[shape=box,height=1]

        R_X2[label=R_X,shape=box]
        R_p2[label=R_p,shape=box]
        X2[label=X]
        p2[label=p]
        L_p2[label=L_p]

        node[style=invis]
        edge[style=invis]
        L_p2->02
    }
}
```

```graphviz
digraph  {
    label=R_旋转
    subgraph cluster{
        label=before
        X->L_X
        X->p
        p->L_p
        p->R_p
        R_p[shape=box,height=1]
        
        L_X[shape=box]
        L_p[shape=box]
        node[style=invis]
        edge[style=invis]
        L_X->0
    }
    
    subgraph cluster2{
        label=after
        p2->X2
        p2->R_p2
        X2->L_X2
        X2->L_p2
        R_p2[shape=box,height=1]

        L_X2[label=L_X,shape=box]
        L_p2[label=L_p,shape=box]
        X2[label=X]
        p2[label=p]
        R_p2[label=R_p]

        node[style=invis]
        edge[style=invis]
        R_p2->02
    }
}
```

### 失衡的恢复
根据新插入的（导致失衡的）结点所在的结点，可以分为以下4种情况

1. 插入在左子树的左子树,LL
2. 插入在左子树的右子树,LR
3. 插入在右子树的左子树,RL
4. 插入在右子树的右子树,RR

```graphviz
digraph  {
    X->left
    X->right
    node[style=dashed]
    edge[style=dashed]
    left->LL
    left->LR
    right->RL
    right->RR
}
```

四种情况所对应的调整方式为

|失衡|调整|
|--|--|
|LL|L旋转|
|LR|L-R旋转|
|RL|R-L旋转|
|RR|R旋转|

其中L-R旋转表示先L旋转再R旋转，R-L旋转同理
