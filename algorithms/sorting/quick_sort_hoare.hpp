#ifndef QUICK_SORT_HOARE_HPP
#define QUICK_SORT_HOARE_HPP

#include "insertion_sort.hpp"

namespace algorithms {
namespace sorting {

#define ORDER(a, b) if(comp(*(b), *(a))) swap(*(a), *(b))


enum {
    QS2IS_THRESHOLD = 32
};


//-----------------------------------------------------------------------
//---------------------------- super version ----------------------------
//-----------------------------------------------------------------------

namespace version3 {

template <typename RAI, class Comp>
void _quick_sort_hoare(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::value_type Value;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    RAI b, m, e;
    for(;;)
    {
        {
            const Distance sz = end-begin;
            if (sz < 2) return;

            b = begin, e = end, --e;
            ORDER(b, e);
            if (sz == 2) return;

            m = begin, m += (sz >> 1);

            RAI b025 = begin + (sz >> 2);
            RAI b075 = b025 + (sz >> 1);

            ORDER(b, b075);
            ORDER(b025, e);
            ORDER(b025, b075);

            ORDER(b, m);
            ORDER(m, e);
            if (sz < 4) return;

            ORDER(b, b025);
            ORDER(b025, m);
            ORDER(m, b075);
            ORDER(b075, e);
            if (sz < 6) return;
        }

        {
            const Value pivot = *m;
            while (1)
            {
                while (comp(*++b, pivot));
                while (comp(pivot, *--e));
                if (!(b <= e)) break;
                swap(*b, *e);
            }
        }
        ++e;
        if (e - begin < end - b)
        {
            _quick_sort_hoare(begin, e, comp);
            begin = b;
        }
        else
        {
            _quick_sort_hoare(b, end, comp);
            end = e;
        }
    }
}

template <typename RAI, class Comp>
void _quick_sort_hoare_ins(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::value_type Value;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    RAI b, m, e;
    for(;;)
    {
        {
            const Distance sz = end-begin;
            if (sz < static_cast<Distance>(QS2IS_THRESHOLD))
            {
                sorting::_insertion_sort<RAI>::run(begin, end, comp);
                return;
            }

            b = begin, e = end, --e, m = begin, m += (sz >> 1);
            ORDER(b, e);

            RAI b025 = begin + (sz >> 2);
            RAI b075 = b025 + (sz >> 1);

            ORDER(b, b075);
            ORDER(b025, e);
            ORDER(b025, b075);
            ORDER(b, m);
            ORDER(m, e);

            ORDER(b, b025);
            ORDER(b025, m);
            ORDER(m, b075);
            ORDER(b075, e);
        }

        {
            const Value pivot = *m;
            while (1)
            {
                while (comp(*++b, pivot));
                while (comp(pivot, *--e));
                if (!(b <= e)) break;
                swap(*b, *e);
            }
        }
        ++e;
        if (e - begin < end - b)
        {
            _quick_sort_hoare_ins(begin, e, comp);
            begin = b;
        }
        else
        {
            _quick_sort_hoare_ins(b, end, comp);
            end = e;
        }
    }
}

} // namespace version3


//-----------------------------------------------------------------------
//--------------------------- optimized version -------------------------
//-----------------------------------------------------------------------
// Optimizations:
// 1. Check two items - at the beginning and at the end.
// 2. Check middle item and move median to the center.
// 3. After the cycle, recursive call for a smaller range,
//    and recheck a larger range in-place.
namespace version2 {

template <typename RAI, class Comp>
void _quick_sort_hoare(RAI begin, RAI end, Comp comp)
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

        RAI m = begin + (sz >> 1);
        if (comp(*m, *b)) swap(*b, *m);
        if (comp(*e, *m)) swap(*m, *e);
        if (sz == 3) return;           // (2)

        {
            const Value pivot = *m;
            while (1)
            {
                while (comp(*++b, pivot));
                while (comp(pivot, *--e));
                if (!(b <= e)) break;
                swap(*b, *e);
            }
        }
        ++e;
        if (e - begin < end - b)       // (3)
        {
            _quick_sort_hoare(begin, e, comp);
            begin = b;
        }
        else
        {
            _quick_sort_hoare(b, end, comp);
            end = e;
        }
    }
}

template <typename RAI, class Comp>
void _quick_sort_hoare_ins(RAI begin, RAI end, Comp comp)
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

        RAI b = begin, e = end-1, m = begin + (sz >> 1);
        if (comp(*e, *b)) swap(*b, *e);
        if (comp(*m, *b)) swap(*b, *m);
        if (comp(*e, *m)) swap(*m, *e);

        {
            const Value pivot = *m;
            while (1)
            {
                while (comp(*++b, pivot));
                while (comp(pivot, *--e));
                if (!(b <= e)) break;
                swap(*b, *e);
            }
        }
        ++e;
        if (e - begin < end - b)
        {
            _quick_sort_hoare_ins(begin, e, comp);
            begin = b;
        }
        else
        {
            _quick_sort_hoare_ins(b, end, comp);
            end = e;
        }
    }
}

} // namespace version2

//-----------------------------------------------------------------------
//-------------------------- unoptimized version ------------------------
//-----------------------------------------------------------------------

namespace version1 {

template <class RAI, class Comp>
void _quick_sort_hoare(RAI begin, RAI end, Comp comp)
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

    _quick_sort_hoare(begin, e+1, comp);
    _quick_sort_hoare(b, end, comp);
}

template <class RAI, class Comp>
void _quick_sort_hoare_ins(RAI begin, RAI end, Comp comp)
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

    _quick_sort_hoare_ins(begin, e+1, comp);
    _quick_sort_hoare_ins(b, end, comp);
}

} // namespace version1

#undef ORDER
} // namespace sorting
} // namespace algorithms

#endif
