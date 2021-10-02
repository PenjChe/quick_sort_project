#ifndef PROJECT_GREAT_ALGORITHMS_HPP
#define PROJECT_GREAT_ALGORITHMS_HPP

#include "sorting/quick_sort_hoare.hpp"
#include "sorting/quick_sort_cherepennikov.hpp"
#include <functional>  // for std::less

namespace algorithms {

template <class RAI>
inline
void quick_sort_hoare(RAI begin, RAI end)
{
    sorting::version2::_quick_sort_hoare(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare(RAI begin, RAI end, Comp comp)
{
    sorting::version2::_quick_sort_hoare(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_hoare_ins(RAI begin, RAI end)
{
    sorting::version2::_quick_sort_hoare_ins(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare_ins(RAI begin, RAI end, Comp comp)
{
    sorting::version2::_quick_sort_hoare_ins(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_cherepennikov(RAI begin, RAI end)
{
    sorting::version2::_quick_sort_mine<RAI>::run(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_cherepennikov(RAI begin, RAI end, Comp comp)
{
    sorting::version2::_quick_sort_mine<RAI>::run(begin, end, comp);
}


namespace oldfuncs {

template <class RAI>
inline
void quick_sort_hoare(RAI begin, RAI end)
{
    sorting::version1::_quick_sort_hoare(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare(RAI begin, RAI end, Comp comp)
{
    sorting::version1::_quick_sort_hoare(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_hoare_ins(RAI begin, RAI end)
{
    sorting::version1::_quick_sort_hoare_ins(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare_ins(RAI begin, RAI end, Comp comp)
{
    sorting::version1::_quick_sort_hoare_ins(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_cherepennikov(RAI begin, RAI end)
{
    sorting::version1::_quick_sort_mine(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_cherepennikov(RAI begin, RAI end, Comp comp)
{
    sorting::version1::_quick_sort_mine(begin, end, comp);
}

} // namespace old

} // namespace algorithms

#endif
