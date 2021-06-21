#ifndef TESTSORT_HPP
#define TESTSORT_HPP

#include <ctime>   // for std::clock()
#include <algorithm>
#include <functional> // for std::greater


template <typename _It>
static inline
bool is_sorted_asc(_It begin, _It end)
{
    return end == std::adjacent_find(begin, end,
        std::greater< typename std::iterator_traits<_It>::value_type >());
}

template <typename _It>
static inline
void heap_sort(_It begin, _It end)
{
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
}


#define TestSortAlgorithm(data, type, header, sortfunc) \
do { \
    std::vector< type > copy(data); \
    std::clock_t __c_start = std::clock(); \
    sortfunc(copy.begin(), copy.end()); \
    std::clock_t __c_finish = std::clock(); \
    double worktime = static_cast<double>(__c_finish - __c_start) / CLOCKS_PER_SEC; \
    std::cout << header << ": " << \
        (is_sorted_asc(copy.begin(), copy.end()) ? "sorted" : "NOT sorted") << \
        " in " << worktime << " s\n"; \
}while(0)

#define TestAllSortAlgorithms(header, type, size, genfunc) \
do {\
    std::vector< type > data(size); \
    genfunc(data.begin(), data.end()); \
    std::cout << "*****" << header << '\n'; \
    TestSortAlgorithm(data, type, "quick sort Cherepennikov", algorithms::quick_sort_cherepennikov); \
    TestSortAlgorithm(data, type, "quick sort Hoare        ", algorithms::quick_sort_hoare); \
    TestSortAlgorithm(data, type, "quick insert sort Hoare ", algorithms::quick_sort_hoare_ins); \
    TestSortAlgorithm(data, type, "std heap sort           ", heap_sort); \
    TestSortAlgorithm(data, type, "std sort                ", std::sort); \
    TestSortAlgorithm(data, type, "std stable sort         ", std::stable_sort); \
    std::cout << std::endl; \
}while(0)

#define TestAllOldSortAlgorithms(header, type, size, genfunc) \
do {\
    std::vector< type > data(size); \
    genfunc(data.begin(), data.end()); \
    std::cout << "*****" << header << '\n'; \
    TestSortAlgorithm(data, type, "quick sort Cherepennikov", algorithms::oldfuncs::quick_sort_cherepennikov); \
    TestSortAlgorithm(data, type, "quick sort Hoare        ", algorithms::oldfuncs::quick_sort_hoare); \
    TestSortAlgorithm(data, type, "quick insert sort Hoare ", algorithms::oldfuncs::quick_sort_hoare_ins); \
    TestSortAlgorithm(data, type, "std heap sort           ", heap_sort); \
    TestSortAlgorithm(data, type, "std sort                ", std::sort); \
    TestSortAlgorithm(data, type, "std stable sort         ", std::stable_sort); \
    std::cout << std::endl; \
}while(0)

#endif