#include <vector>

using DType = int;
using Array = std::vector<DType>;

void heapAdjust(int idx, Array& a, int n = -1) {
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