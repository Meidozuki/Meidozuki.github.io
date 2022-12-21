#include <iostream>
#include <random>
#include <functional>
#include <map>

#include "simple_sort.cpp"
#include "sort.cpp"

using SortFn = std::function<void(Array&)>;

constexpr int REPEAT = 3;
constexpr int testing_arr_size=20;


Array initialize(int n) {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    static std::uniform_int_distribution<DType> dist(0,10000);

    std::vector<DType> v;
    v.reserve(n);

    for (int i=0;i < n;++i)
        v.push_back(dist(engine));

    return v;
}

constexpr int base = 1000;
constexpr int seq[] = {base, base*10, base*10*3};

void timing(int n, const SortFn &sorting);
void test(const SortFn &sorting);
void bench(const SortFn &sortF, bool bTest=false);

int main (void) {


//    bench(bubble);
//    bench(bubbleMend);
//    bench(select);
//    bench(selectMend);
//    bench(insert);
    bench(heapSortInplace,true);

}

void bench(const SortFn &sortF, bool bTest) {
    if (bTest) test(sortF);
    for (int n : seq) {
        timing(n, sortF);
    }
};

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

    auto start = clock();
    decltype(start) step[REPEAT];
    for (int i=0;i < REPEAT;++i) {
        std::cout << i+1 << "th iter.";
        sorting(*ptr[i]);
        step[i] = clock()-start;
    }
    auto end = clock();
//    std::cout << "\n" << step[0] << " " << step[1] << " " << step[2] << " ";
    std::cout << " Total time = " << end-start << "ms, avg = " << (end-start)/REPEAT << "ms." << std::endl;
}