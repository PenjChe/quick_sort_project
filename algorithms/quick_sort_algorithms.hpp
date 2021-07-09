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
    sorting::_quick_sort_hoare_new(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare(RAI begin, RAI end, Comp comp)
{
    sorting::_quick_sort_hoare_new(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_hoare_ins(RAI begin, RAI end)
{
    sorting::_quick_sort_hoare_ins_new(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare_ins(RAI begin, RAI end, Comp comp)
{
    sorting::_quick_sort_hoare_ins_new(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_cherepennikov(RAI begin, RAI end)
{
    sorting::_quick_sort_mine_new(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_cherepennikov(RAI begin, RAI end, Comp comp)
{
    sorting::_quick_sort_mine_new(begin, end, comp);
}


namespace oldfuncs {

template <class RAI>
inline
void quick_sort_hoare(RAI begin, RAI end)
{
    sorting::_quick_sort_hoare_old(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare(RAI begin, RAI end, Comp comp)
{
    sorting::_quick_sort_hoare_old(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_hoare_ins(RAI begin, RAI end)
{
    sorting::_quick_sort_hoare_ins_old(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_hoare_ins(RAI begin, RAI end, Comp comp)
{
    sorting::_quick_sort_hoare_ins_old(begin, end, comp);
}


template <class RAI>
inline
void quick_sort_cherepennikov(RAI begin, RAI end)
{
    sorting::_quick_sort_mine_old(begin, end,
        std::less<typename std::iterator_traits<RAI>::value_type>());
}

template <class RAI, class Comp>
inline
void quick_sort_cherepennikov(RAI begin, RAI end, Comp comp)
{
    sorting::_quick_sort_mine_old(begin, end, comp);
}

} // namespace old

} // namespace algorithms

#endif
