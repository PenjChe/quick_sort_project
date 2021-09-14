#ifndef QUICK_SORT_HOARE_HPP
#define QUICK_SORT_HOARE_HPP

#include "insertion_sort.hpp"

namespace sorting {


enum {
    QS2IS_THRESHOLD = 32
};

//--------------------------- optimized version -------------------------
// Optimizations:
// 1) Check two items - at the beginning and at the end.
// 2) Check middle item and move median to the center.
// 3) After the cycle, recursive call for a smaller range,
//    and recheck a larger range in-place.

template <typename RAI, class Comp>
void _quick_sort_hoare_new(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::value_type Value;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    for(;;)
    {
        const Distance sz = end-begin;
        if (sz < 2) return;

        RAI b = begin, e = end-1;
        if (comp(*e, *b)) swap(*b, *e);
        if (sz == 2) return;           // (1)

        RAI m = begin + sz/2;
        if (comp(*m, *b)) swap(*b, *m);
        if (comp(*e, *m)) swap(*m, *e);
        if (sz == 3) return;           // (2)

        {
            const Value pivot = *m;
            while (++b <= --e)
            {
                while (comp(*b, pivot)) ++b;
                while (comp(pivot, *e)) --e;
                if (!(b <= e)) break;
                swap(*b, *e);
            }
        }
        ++e;
        if (e - begin < end - b)       // (3)
        {
            _quick_sort_hoare_new(begin, e, comp);
            begin = b;
        }
        else
        {
            _quick_sort_hoare_new(b, end, comp);
            end = e;
        }
    }
}

template <typename RAI, class Comp>
void _quick_sort_hoare_ins_new(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::value_type Value;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    for(;;)
    {
        const Distance sz = end-begin;
        if (sz < static_cast<Distance>(QS2IS_THRESHOLD))
        {
            sorting::_insertion_sort<RAI>::run(begin, end, comp);
            return;
        }

        RAI b = begin, e = end-1, m = begin + sz/2;
        if (comp(*e, *b)) swap(*b, *e);
        if (comp(*m, *b)) swap(*b, *m);
        if (comp(*e, *m)) swap(*m, *e);

        {
            const Value pivot = *m;
            while (++b <= --e)
            {
                while (comp(*b, pivot)) ++b;
                while (comp(pivot, *e)) --e;
                if (!(b <= e)) break;
                swap(*b, *e);
            }
        }
        ++e;
        if (e - begin < end - b)
        {
            _quick_sort_hoare_ins_new(begin, e, comp);
            begin = b;
        }
        else
        {
            _quick_sort_hoare_ins_new(b, end, comp);
            end = e;
        }
    }
}


//-------------------------- unoptimized version ------------------------

template <class RAI, class Comp>
void _quick_sort_hoare_old(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::value_type Value;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    const Distance sz = end-begin;
    if (sz < 2) return;
    if (sz == 2)
    {
        if (comp(*--end, *begin)) swap(*begin, *end);
        return;
    }

    RAI b = begin, e = end - 1;
    {
        const Value pivot = *(begin + sz/2);
        do {
            while (comp(*b, pivot)) ++b;
            while (comp(pivot, *e)) --e;
            if (!(b <= e)) break;
            swap(*b, *e);
        } while(++b <= --e);
    }

    _quick_sort_hoare_old(begin, e+1, comp);
    _quick_sort_hoare_old(b, end, comp);
}

template <class RAI, class Comp>
void _quick_sort_hoare_ins_old(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::value_type Value;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    const Distance sz = end-begin;
    if (sz < static_cast<Distance>(QS2IS_THRESHOLD))
    {
        sorting::_insertion_sort<RAI>::run(begin, end, comp);
        return;
    }

    RAI b = begin, e = end - 1;
    {
        const Value pivot = *(begin + sz/2);
        do {
            while (comp(*b, pivot)) ++b;
            while (comp(pivot, *e)) --e;
            if (!(b <= e)) break;
            swap(*b, *e);
        } while(++b <= --e);
    }

    _quick_sort_hoare_ins_old(begin, e+1, comp);
    _quick_sort_hoare_ins_old(b, end, comp);
}

} // namespace

#endif
