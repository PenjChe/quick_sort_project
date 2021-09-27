#ifndef QUICK_SORT_CHRPNNKOV_HPP
#define QUICK_SORT_CHRPNNKOV_HPP

#include <iterator>
#include <type_traits>

namespace sorting {

//NOTE: the default comparison operator is less than (<),
// so "big values" means "values greater than pivot",
// and "small values" stands for "values less than pivot".

#define RAI_VALUE_IS_SCALAR(type) \
    (std::is_scalar< typename std::iterator_traits<type>::value_type >::value)

// This is a common implementation
template <class RAI, bool = RAI_VALUE_IS_SCALAR(RAI) >
struct _quick_sort_mine_new
{

template <class Comp>
static void run(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    for(;;)
    {
        const Distance sz = end-begin;
        if (sz < 2) return;

        // Stage 0. Prepare.
        RAI b = begin, e = end;
        if (comp(*--e, *b)) swap(*b, *e);
        if (sz == 2) return;

        RAI m = begin + sz/2;
        if (comp(*m, *b)) swap(*b, *m);
        if (comp(*e, *m)) swap(*m, *e);
        if (sz == 3) return;

        // Stage 1. Find the pivot value while sorting.
        // If predicate is false, that means *b == pivot
        while (comp(*b, *pivb))
        {
            while (comp(*++b, *pivb));
            if (!comp(*pivb, *b)) break;
            while (comp(*pivb, *e)) --e;
            swap(*b, *e);
        }
        RAI pivb = b, pive = pivb+1; // "pivots" range

        // Stage 2. Move small values to the beginnig,
        // big values to the end, "pivots" are moving to found "brother".
        for(;;)
        {
            while (comp(*++b, *pivb));    // skip small items
            if (b == e) break;
            if (comp(*pivb, *b)) {
                while (comp(*pivb, *--e));  // skip big items
                if (b == e+1) break;
                swap(*b, *e);
                if (comp(*b, *pivb)) continue;
            }
            // if current item is equal to pivot then move "pivots" to this one
            for (RAI bbb = b; pive != bbb; ++pivb) {
                if (pivb == pive) {pivb = bbb; break;}
                swap(*pivb, *--bbb);
            }
            pive = b+1;
        }
        // finally, put "pivots" into right place
        for (RAI bbb = b; pive != bbb; ++pivb) {
            if (pivb == pive) {pivb = bbb; break;}
            swap(*pivb, *--bbb);
        }
        pive = b;

        // Stage 3. Sort a smaller range by recursive call.
        // Sort a larger range in-place.
        if (pivb-begin < end-pive)
        {
            run(begin, pivb, comp);
            begin = pive;
        }
        else
        {
            run(pive, end, comp);
            end = pivb;
        }
    }
}

}; // end of common implementation


// This is a implementation for scalar types (int, float, double, etc...)
// It stores the pivot value in a local cell to accelerate the function
template <class RAI>
struct _quick_sort_mine_new<RAI, true>
{

template <class Comp>
static void run(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    typedef typename std::iterator_traits<RAI>::value_type Value;

    RAI b,e,pivb,pive;
    for(;;)
    {
        {
            // Stage 0. Prepare.
            const Distance sz = end-begin;
            if (sz < 2) return;

            b = begin, e = end;
            if (comp(*--e, *b)) swap(*b, *e);
            if (sz == 2) return;

            pivb = begin + sz/2;
            if (comp(*pivb, *b)) swap(*b, *pivb);
            if (comp(*e, *pivb)) swap(*pivb, *e);
            if (sz == 3) return;
        }

        {
            // Stage 1. Find the pivot value while sorting.
            const Value pivot = *pivb; // !!! Store the pivot value

            // If predicate is false, that means *b == pivot
            while (comp(*b, pivot))
            {
                while (comp(*++b, pivot));
                if (!comp(pivot, *b)) break;
                while (comp(pivot, *e)) --e;
                swap(*b, *e);
            }
            pivb = b, pive = pivb+1; // "pivots" range

            // Stage 2. Move small values to the beginnig,
            // big values to the end, "pivots" are moving to found "brother".
            for(;;)
            {
                while (comp(*++b, pivot));    // skip small items
                if (b == e) break;
                if (comp(pivot, *b)) {
                    while (comp(pivot, *--e));  // skip big items
                    if (b == e+1) break;
                    swap(*b, *e);
                    if (comp(*b, pivot)) continue;
                }
                // if current item is equal to pivot then move "pivots" to this one
                for (RAI bbb = b; pive != bbb; ++pivb) {
                    if (pivb == pive) {pivb = bbb; break;}
                    swap(*pivb, *--bbb);
                }
                pive = b+1;
            }
            // finally, put "pivots" into right place
            for (RAI bbb = b; pive != bbb; ++pivb) {
                if (pivb == pive) {pivb = bbb; break;}
                swap(*pivb, *--bbb);
            }
            pive = b;
        }

        // Stage 3. Sort a smaller range by recursive call.
        // Sort a larger range in-place.
        if (pivb-begin < end-pive)
        {
            run(begin, pivb, comp);
            begin = pive;
        }
        else
        {
            run(pive, end, comp);
            end = pivb;
        }
    }
}

}; // end of specialization

//------------------------------ first version --------------------------

template <class RAI, class Comp>
void _quick_sort_mine_old(RAI begin, RAI end, Comp comp)
{
    using std::swap;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    const Distance sz = end-begin;
    if (sz < 2) return;
    if (sz == 2)
    {
        if (comp(*--end, *begin)) swap(*begin, *end);
        return;
    }

    RAI b = begin, e = end;
    RAI pivb = begin + sz/2;
    RAI pive = pivb;
    bool pivot_found = false;

    // Stage 1
    do {
        if (comp(*b, *pivb)) ++b;
        else if (comp(*pivb, *b))
        {
            while (b != --e)
            {
                if (comp(*e, *pivb))
                {
                    swap(*b, *e);
                    ++b;
                    break;
                }
                else if (!comp(*pivb, *e))
                {
                    swap(*b, *e);
                    pivot_found = true;
                    break;
                }
            }
        }
        else
        {
            pivot_found = true;
        }
    } while (!pivot_found);
    pivb = b;
    pive = ++b;

    // Stage 2
    while (b != e)
    {
        if (comp(*b, *pivb))
        {
            swap(*pivb, *b);
            ++b, ++pivb, ++pive;
        }
        else if (comp(*pivb, *b))
        {
            while (b != --e)
            {
                if (comp(*e, *pivb))
                {
                    swap(*b, *e);
                    swap(*pivb, *b);
                    ++b, ++pivb, ++pive;
                    break;
                }
                else if (!comp(*pivb, *e))
                {
                    swap(*b, *e);
                    ++b, ++pive;
                    break;
                }
            }
        }
        else
        {
            ++b, ++pive;
        }
    }

    // Stage 3
    _quick_sort_mine_old(begin, pivb, comp);
    _quick_sort_mine_old(pive, end, comp);
}

#undef RAI_VALUE_IS_SCALAR
} // namespace

#endif
