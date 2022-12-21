#include <cassert>

using DType = int;
using Array = std::vector<DType>;

void bubble(Array &a) {
    const int n = a.size();
    for (int i=0;i < n;++i) {
        for (int j=1;j < n;++j) {
            if (a[j] < a[j-1]) {
                std::swap(a[j-1],a[j]);
            }
        }
    }
}

void bubbleMend(Array &a) {
    const int n = a.size();
    int last, upper=n;
    for (int i=0;i < n;++i) {
        for (int j=1;j < upper;++j) {
            if (a[j] < a[j-1]) {
                std::swap(a[j-1],a[j]);
                last=j;
            }
        }
        upper=last;
    }
}

void insert(Array &a) {
    const int n = a.size();
    for (int i=1;i < n;++i) {
        int temp = a[i];
        int j;
        for (j=i;j > 0;--j) {
            if (a[j-1] > temp) {
                a[j]=a[j-1];
            }
            else
                break;
        }
        a[j]=temp;
    }
}

void select(Array &a) {
    const int n = a.size();
    for (int i=0;i < n;++i) {
        int maxv = a[0];
        int maxid=0;
        for (int j=0;j < n-i;++j) {
            if (a[j] > maxv) {
                maxv=a[j];
                maxid=j;
            }
        }
        std::swap(a[n-1-i],a[maxid]);
    }
}

void selectMend(Array &a) {
    const int n = a.size();
    for (int i=0;i < n/2;++i) {
        int maxv = a[0], minv = a[n-1];
        int maxid = 0, minid = n-1;
        for (int j=i;j < n-i;++j) {
            if (a[j] < minv) {
                minv=a[j];
                minid=j;
            }
            else if (a[j] > maxv) {
                maxv=a[j];
                maxid=j;
            }
        }

        assert(maxid != minid);
        std::swap(a[i],a[minid]);
        if (i == maxid) maxid=minid;
        std::swap(a[n-1-i],a[maxid]);
    }
}