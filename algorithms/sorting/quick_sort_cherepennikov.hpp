#ifndef QUICK_SORT_CHRPNNKOV_HPP
#define QUICK_SORT_CHRPNNKOV_HPP

#include <iterator>

namespace sorting {

//NOTE: the default comparison operator is less than (<),
// so "big values" means "values greater than pivot",
// and "small values" stands for "values less than pivot".

template <class RAI, class Comp>
void _quick_sort_mine_new(RAI begin, RAI end, Comp comp)
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
        for(;;)
        {
            while (comp(*b, *m)) ++b;
            if (!comp(*m, *b)) break;
            while (comp(*m, *e)) --e;
            bool br = !comp(*e, *m);
            swap(*b, *e);
            if (br) break;
            ++b;
        }
        RAI pivb = b, pive = ++b; // "Pivots" range

        // Stage 2. Move small values to the beginnig,
        // big values to the end, "pivots" are moving to found "brother".
        for(;;)
        {
            while (comp(*b, *pivb)) ++b;  // skip small items
            if (b == e) break;
            bool fl = comp(*pivb, *b);
            if (fl) {
                while (comp(*pivb, *--e));  // skip big items
                if (b == e+1) break;
                fl = comp(*e, *pivb);
                swap(*b, *e);
            }
            if (fl) ++b;
            else {
                // if current item is equal to pivot then move "pivots" to this one
                for (RAI bbb = b; pive != bbb; ++pivb) {
                    if (pivb == pive) {pivb = bbb; break;}
                    swap(*pivb, *--bbb);
                }
                pive = ++b;
            }
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
            _quick_sort_mine_new(begin, pivb, comp);
            begin = pive;
        }
        else
        {
            _quick_sort_mine_new(pive, end, comp);
            end = pivb;
        }
    }
}


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

} // namespace

#endif
