#include <iostream>
#include <random>
#include <functional>
#include <map>

#include "sort.cpp"

using SortFn = std::function<void(Array&)>;

constexpr int REPEAT = 3;
constexpr int testing_arr_size=20;

std::random_device rd;
std::default_random_engine engine(rd());

constexpr int base = 100'000;
constexpr int seq[] = {base, base*10, base*10*4};

void timing(int n, const SortFn &sorting);
void test(const SortFn &sorting);
void bench(const SortFn &sortF, bool bTest=false);

int main (void) {
    std::map<const char*,SortFn> names;


    if (base < 10000) {
        names["bubble sort"] = bubble;
        names["select sort"] = select;
        names["insert sort"] = insert;
    }

    names["heap sort"] = heapSortInplace;
    names["merge sort"] = mergeSort;
    names["quick sort"] = quickSort;

    for (auto &pair : names) {
        std::cout << "Start benchmark for " << pair.first << '\n';
        bench(pair.second);
    }

}

void bench(const SortFn &sortF, bool bTest) {
    if (bTest) test(sortF);
    for (int n : seq) {
        timing(n, sortF);
    }
};

Array initialize(int n) {
    static std::uniform_int_distribution<DType> dist(0,10000);

    std::vector<DType> v;
    v.reserve(n);

    for (int i=0;i < n;++i)
        v.push_back(dist(engine));

    return v;
}

void test(const SortFn &sorting) {
    auto v= initialize(testing_arr_size);
    for (auto x:v)
        std::cout << x << ' ';
    std::cout << std::endl;

    sorting(v);
    for (auto x:v)
        std::cout << x << ' ';
    std::cout << '\n';
}

void timing(int n, const SortFn &sorting) {
    auto v1 = initialize(n), v2 = initialize(n), v3 = initialize(n);
    Array *(ptr[]) = {&v1,&v2,&v3};

    std::cout << "Timing with n = " << n << ". ";
    auto start = clock();
    decltype(start) step[REPEAT];
    for (int i=0;i < REPEAT;++i) {
        std::cout << i+1 << "/" << REPEAT << ' ';
        sorting(*ptr[i]);
        step[i] = clock()-start;
    }
    auto end = clock();
//    std::cout << "\n" << step[0] << " " << step[1] << " " << step[2] << " ";
    std::cout << "Total time = " << end-start << "ms, avg = " << (end-start)/REPEAT << "ms. ";

    std::cout << "Checking...";
    int i;
    for (i=1;i < n;++i) {
        if (v1[i-1] > v1[i]) {
            break;
        }
    }
    if (i < n) std::cout << "not ";
    std::cout << "ordered." << std::endl;
}