#include <vector>

#include "simple_sort.cpp"

using DType = int;
using Array = std::vector<DType>;

inline void heapAdjust(int idx, Array& a, int n = -1) {
    if (n == -1) n=a.size();
    if (idx >= n)
        return;

    while (idx*2 < n) {
        //选择子结点中较大的
        const int left = idx*2, right = idx*2 + 1;
        int child = left;
        if (right < n && a[right] > a[left]) {
            child = right;
        }

        if (a[idx] < a[child]) {
            std::swap(a[idx],a[child]);
            idx = child;
        }
        else {
            break;
        }
    }
}

void heapSortInplace(Array &a) {
    int n = a.size();

    //建堆
    for (int i = n/2-1;i >= 0;--i) {
        heapAdjust(i,a);
    }

    //堆排序
    for (int i = n;i > 0;--i) {
        std::swap(a[0],a[i-1]);
        heapAdjust(0,a,i-1);
    }
}

void mergeSortFn(int beg, int end, Array &arr, Array &temp) {
    const int n = end - beg;
    if (n <= 2) {
        if (n == 2) {
            if (arr[beg] > arr[beg+1])
                std::swap(arr[beg], arr[beg+1]);
        }
        return;
    }

    //recursion
    int mid = beg + n/2;
    mergeSortFn(beg, mid, arr, temp);
    mergeSortFn(mid, end, arr, temp);

    //merge
    int *pl = &arr[beg], *pr = &arr[mid],
        *lend = pr, *rend = &arr[end];
    auto it = temp.begin();
    while (pl < lend && pr < rend) {
        if (*pl <= *pr) {
            *it = *(pl++);
        }
        else {
            *it = *(pr++);
        }
        ++it;
    }

    while (pl < lend) *(it++) = *(pl++);
    while (pr < rend) *(it++) = *(pr++);

    //copy
    std::copy(&temp[0],&temp[n],&arr[beg]);
}

void mergeSort(Array &a) {
    Array temp(a.size());

    mergeSortFn(0,a.size(),a,temp);
}

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

void quickSortFn(int beg, int end, Array &a) {
    const int n = end-beg;

    if (n <= 10) {
        selectFn(&a[beg],n);
        return;
    }

    int pivot_idx = pickPivot(beg, end-1, beg + n/2,&a[0]);

    int pivot = a[pivot_idx];
    std::swap(a[pivot_idx],a[end-1]);
    int *pl = &a[beg], *pr = &a[end-2];

    //partition
    while (pl <= pr) {
        while (*pl < pivot && pl <= pr) ++pl;
        while (*pr > pivot && pl <= pr) --pr;

        if (pl >= pr) {
            break;
        }
        std::swap(*pl,*pr);
        ++pl,--pr;
    }
    std::swap(*pl,a[end-1]);

    pivot_idx = beg + (pl - &a[beg]);
    quickSortFn(beg,pivot_idx,a);
    quickSortFn(pivot_idx+1,end,a);
}

void quickSort(Array &a) {
    quickSortFn(0,a.size(),a);
}