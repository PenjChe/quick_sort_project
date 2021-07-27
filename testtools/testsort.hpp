#ifndef TESTSORT_HPP
#define TESTSORT_HPP

#include <ctime>   // for std::clock()
#include <string>
#include <algorithm>
#include <functional> // for std::greater
#include "../algorithms/quick_sort_algorithms.hpp"

#include <sstream>
#include <iomanip>

struct SortAlgo
{
    enum {
        SA_QUICKSORT_MY = 0,
        SA_QUICKSORT_HOARE,
        SA_QUICKSORT_HOARE_I,
        SA_STD_HEAPSORT,
        SA_STD_SORT,
        SA_STD_MERGESORT,
        N
    };

    static std::string last_message;

    template <class RAI>
    static void run(unsigned n, RAI begin, RAI end)
    {
        std::stringstream ss;
        std::clock_t _c_start, _c_finish;
        ss << std::left << std::setfill(' ') << std::setw(30);
        switch(n)
        {
        default:
        case SA_QUICKSORT_MY:
            _c_start = std::clock();
            algorithms::quick_sort_cherepennikov(begin, end);
            _c_finish = std::clock();
            ss << "quick sort Cherepennikov";
            break;
        case SA_QUICKSORT_HOARE:
            _c_start = std::clock();
            algorithms::quick_sort_hoare(begin, end);
            _c_finish = std::clock();
            ss << "quick sort Hoare";
            break;
        case SA_QUICKSORT_HOARE_I:
            _c_start = std::clock();
            algorithms::quick_sort_hoare_ins(begin, end);
            _c_finish = std::clock();
            ss << "quick insert sort Hoare";
            break;
        case SA_STD_HEAPSORT:
            _c_start = std::clock();
            std::make_heap(begin, end);
            std::sort_heap(begin, end);
            _c_finish = std::clock();
            ss << "std heap sort";
            break;
        case SA_STD_SORT:
            _c_start = std::clock();
            std::sort(begin, end);
            _c_finish = std::clock();
            ss << "std sort";
            break;
        case SA_STD_MERGESORT:
            _c_start = std::clock();
            std::stable_sort(begin, end);
            _c_finish = std::clock();
            ss << "std stable sort";
            break;
        }
        double worktime = static_cast<double>(_c_finish - _c_start) / CLOCKS_PER_SEC;
        ss << ": "
           << (is_sorted_asc(begin, end) ? "   " : "NOT")
           << " sorted in " << worktime << " s";
        last_message = ss.str();
    }
    
    template <class _It>
    static inline
    bool is_sorted_asc(_It begin, _It end)
    {
        return end == std::adjacent_find(begin, end,
            std::greater< typename std::iterator_traits<_It>::value_type >());
    }
};

std::string SortAlgo::last_message;


struct SortOldAlgo : public SortAlgo
{
    enum {
        SOA_QUICKSORT_MY = 0,
        SOA_QUICKSORT_HOARE,
        SOA_QUICKSORT_HOARE_I,
        N
    };
    
    template <class RAI>
    static void run(unsigned n, RAI begin, RAI end)
    {
        std::stringstream ss;
        std::clock_t _c_start, _c_finish;
        ss << std::left << std::setfill(' ') << std::setw(30);
        switch(n)
        {
        default:
        case SOA_QUICKSORT_MY:
            _c_start = std::clock();
            algorithms::oldfuncs::quick_sort_cherepennikov(begin, end);
            _c_finish = std::clock();
            ss << "quick sort Cherepennikov (old)";
            break;
        case SOA_QUICKSORT_HOARE:
            _c_start = std::clock();
            algorithms::oldfuncs::quick_sort_hoare(begin, end);
            _c_finish = std::clock();
            ss << "quick sort Hoare (old)";
            break;
        case SOA_QUICKSORT_HOARE_I:
            _c_start = std::clock();
            algorithms::oldfuncs::quick_sort_hoare_ins(begin, end);
            _c_finish = std::clock();
            ss << "quick insert sort Hoare (old)";
            break;
        }
        double worktime = static_cast<double>(_c_finish - _c_start) / CLOCKS_PER_SEC;
        ss << ": "
           << (is_sorted_asc(begin, end) ? "   " : "NOT")
           << " sorted in " << worktime << " s";
        last_message = ss.str();
    }
};

#endif
