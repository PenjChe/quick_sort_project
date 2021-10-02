#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <iterator>
#include <type_traits>

namespace algorithms {
namespace sorting {

#define RAI_VALUE_IS_SCALAR(type) \
    (std::is_scalar< typename std::iterator_traits<type>::value_type >::value)

// This is a common implementation that uses the swap function
template <class RAI, bool = RAI_VALUE_IS_SCALAR(RAI) >
struct _insertion_sort
{

  template <class Comp>
  static void run(RAI begin, RAI end, Comp comp)
  {
    using std::swap;
    typedef typename std::iterator_traits<RAI>::value_type Value;
    if (end-begin < 2) return;
    RAI i = begin;
    while (++i != end)
    {
        RAI e = i, n = i-1;
        if (comp(*e, *begin))
        {
            do {
                swap(*e, *n);
                --e, --n;
            } while (begin != e);
        }
        else
        {
            while (comp(*e, *n))
            {
                swap(*e, *n);
                --e, --n;
            }
        }
    }
  }
}; // end of common implementation


// This is a implementation for scalar types (int, float, double, etc...)
// The insert operation is implemented by shifting method
template <class RAI>
struct _insertion_sort<RAI, true>
{

  template <class Comp>
  static void run(RAI begin, RAI end, Comp comp)
  {
    typedef typename std::iterator_traits<RAI>::value_type Value;
    if (end-begin < 2) return;
    RAI i = begin;
    while (++i != end)
    {
        RAI e = i, n = i-1;
        const Value z = *e;
        if (comp(z, *begin))
        {
            do {
                *e = *n;
                --e, --n;
            } while (begin != e);
            *begin = z;
        }
        else
        {
            while (comp(z, *n))
            {
                *e = *n;
                --e, --n;
            }
            *e = z;
        }
    }
  }
}; // end of specialization

#undef RAI_VALUE_IS_SCALAR
} // namespace sorting
} // namespace algorithms

#endif
