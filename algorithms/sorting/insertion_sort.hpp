#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <iterator>

namespace sorting {

// In this algorithm, insert operation is implemented by shifting method.

template <class RAI, class Comp>
void _insertion_sort(RAI begin, RAI end, Comp comp)
{
    typedef typename std::iterator_traits<RAI>::value_type Value;
    if (end-begin < 2) return;
    RAI i = begin;
    while (++i != end)
    {
        if (comp(*i, *begin))
        {
            Value z = *i;
            RAI e = i;
            do { *e = *(e-1); } while (begin != --e);
            *begin = z;
        }
        else if (comp(*i, *(i-1)))
        {
            Value z = *i;
            RAI e = i, n = i-1;
            do {
                *e = *n;
                e = n;
            } while (comp(z, *--n));
            *e = z;
        }
    }
}

} // namespace

#endif