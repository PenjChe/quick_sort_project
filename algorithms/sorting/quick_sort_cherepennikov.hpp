#ifndef QUICK_SORT_CHRPNNKOV_HPP
#define QUICK_SORT_CHRPNNKOV_HPP

#include <iterator>
#include <type_traits>

namespace algorithms {
namespace sorting {

//NOTE: the default comparison operator is less than (<),
// so "big values" means "values greater than pivot",
// and "small values" stands for "values less than pivot".

#define RAI_VALUE_IS_SCALAR(type) \
    (std::is_scalar< typename std::iterator_traits<type>::value_type >::value)

#define ORDER(a, b) if(comp(*(b), *(a))) swap(*(a), *(b))

namespace version3 {

// This is a common implementation
template <class RAI, bool = RAI_VALUE_IS_SCALAR(RAI) >
struct _quick_sort_mine
{
  template <class Comp>
  static void run(RAI begin, RAI end, Comp comp)
  {
    using std::swap;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    RAI b,e,pivb,pive;
    for(;;)
    {
        {
            // Stage 0. Prepare.
            const Distance sz = end-begin;
            if (sz < 2) return;

            b = begin, e = end, --e;
            ORDER(b, e);
            if (sz == 2) return;

            pivb = begin, pivb += (sz >> 1);

            RAI b025 = begin + (sz >> 2);
            RAI b075 = b025 + (sz >> 1);

            ORDER(b, b075);
            ORDER(b025, e);
            ORDER(b025, b075);

            ORDER(b, pivb);
            ORDER(pivb, e);
            if (sz < 4) return;

            ORDER(b, b025);
            ORDER(b025, pivb);
            ORDER(pivb, b075);
            ORDER(b075, e);
            if (sz < 6) return;
        }

        // Stage 1. Find the pivot value while sorting.
        // If predicate is false, that means *b == pivot
        while (comp(*b, *pivb))
        {
            while (comp(*++b, *pivb));
            if (!comp(*pivb, *b)) break;
            while (comp(*pivb, *e)) --e;
            swap(*b, *e);
        }
        pivb = b, pive = pivb, ++pive; // "pivots" range

        // Stage 2. Move small values to the beginnig,
        // big values to the end, "pivots" are moving to found "brother".
        bool still_not_empty = true;
        do
        {
            while (comp(*++b, *pivb));    // skip small items
            still_not_empty = (b != e);
            if (still_not_empty && comp(*pivb, *b)) {
                while (comp(*pivb, *--e));  // skip big items
                still_not_empty = (b != e+1);
                if (still_not_empty) {
                    swap(*b, *e);
                    if (comp(*b, *pivb)) continue;
                }
            }
            // if current item is equal to pivot, then move "pivots" to this one
            // or if all items are checked, then put "pivots" into right place
            if (pive != b) {
                RAI bbb = b;
                do {
                    if (pivb == pive) {pivb = bbb; break;}
                    swap(*pivb, *--bbb);
                    ++pivb;
                } while (pive != bbb);
                pive = b;
            }
            pive += still_not_empty;
        } while (still_not_empty);

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
struct _quick_sort_mine<RAI, true>
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

            b = begin, e = end, --e;
            ORDER(b, e);
            if (sz == 2) return;

            pivb = begin, pivb += (sz >> 1);

            RAI b025 = begin + (sz >> 2);
            RAI b075 = b025 + (sz >> 1);

            ORDER(b, b075);
            ORDER(b025, e);
            ORDER(b025, b075);

            ORDER(b, pivb);
            ORDER(pivb, e);
            if (sz < 4) return;

            ORDER(b, b025);
            ORDER(b025, pivb);
            ORDER(pivb, b075);
            ORDER(b075, e);
            if (sz < 6) return;
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
            pivb = b, pive = pivb, ++pive; // "pivots" range

            // Stage 2. Move small values to the beginnig,
            // big values to the end, "pivots" are moving to found "brother".
            bool still_not_empty = true;
            do
            {
                while (comp(*++b, pivot));    // skip small items
                still_not_empty = (b != e);
                if (still_not_empty && comp(pivot, *b)) {
                    while (comp(pivot, *--e));  // skip big items
                    still_not_empty = (b != e+1);
                    if (still_not_empty) {
                        swap(*b, *e);
                        if (comp(*b, pivot)) continue;
                    }
                }
                // if current item is equal to pivot, then move "pivots" to this one
                // or if all items are checked, then put "pivots" into right place
                if (pive != b) {
                    RAI bbb = b;
                    do {
                        if (pivb == pive) {pivb = bbb; break;}
                        swap(*pivb, *--bbb);
                        ++pivb;
                    } while (pive != bbb);
                    pive = b;
                }
                pive += still_not_empty;
            } while (still_not_empty);
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

} // namespace version3


//-----------------------------------------------------------------------
//----------------------------- second version --------------------------
//-----------------------------------------------------------------------

namespace version2 {

// This is a common implementation
template <class RAI, bool = RAI_VALUE_IS_SCALAR(RAI) >
struct _quick_sort_mine
{
  template <class Comp>
  static void run(RAI begin, RAI end, Comp comp)
  {
    using std::swap;
    typedef typename std::iterator_traits<RAI>::difference_type Distance;
    RAI b,e,pivb,pive;
    for(;;)
    {
        {
            // Stage 0. Prepare.
            const Distance sz = end-begin;
            if (sz < 2) return;

            b = begin, e = end, --e;
            ORDER(b, e);
            if (sz == 2) return;

            pivb = begin, pivb += (sz >> 1);
            ORDER(b, pivb);
            ORDER(pivb, e);
            if (sz == 3) return;
        }

        // Stage 1. Find the pivot value while sorting.
        // If predicate is false, that means *b == pivot
        while (comp(*b, *pivb))
        {
            while (comp(*++b, *pivb));
            if (!comp(*pivb, *b)) break;
            while (comp(*pivb, *e)) --e;
            swap(*b, *e);
        }
        pivb = b, pive = pivb, ++pive; // "pivots" range

        // Stage 2. Move small values to the beginnig,
        // big values to the end, "pivots" are moving to found "brother".
        bool still_not_empty = true;
        do
        {
            while (comp(*++b, *pivb));    // skip small items
            still_not_empty = (b != e);
            if (still_not_empty && comp(*pivb, *b)) {
                while (comp(*pivb, *--e));  // skip big items
                still_not_empty = (b != e+1);
                if (still_not_empty) {
                    swap(*b, *e);
                    if (comp(*b, *pivb)) continue;
                }
            }
            // if current item is equal to pivot, then move "pivots" to this one
            // or if all items are checked, then put "pivots" into right place
            if (pive != b) {
                RAI bbb = b;
                do {
                    if (pivb == pive) {pivb = bbb; break;}
                    swap(*pivb, *--bbb);
                    ++pivb;
                } while (pive != bbb);
                pive = b;
            }
            pive += still_not_empty;
        } while (still_not_empty);

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
struct _quick_sort_mine<RAI, true>
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

            b = begin, e = end, --e;
            ORDER(b, e);
            if (sz == 2) return;

            pivb = begin, pivb += (sz >> 1);
            ORDER(b, pivb);
            ORDER(pivb, e);
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
            pivb = b, pive = pivb, ++pive; // "pivots" range

            // Stage 2. Move small values to the beginnig,
            // big values to the end, "pivots" are moving to found "brother".
            bool still_not_empty = true;
            do
            {
                while (comp(*++b, pivot));    // skip small items
                still_not_empty = (b != e);
                if (still_not_empty && comp(pivot, *b)) {
                    while (comp(pivot, *--e));  // skip big items
                    still_not_empty = (b != e+1);
                    if (still_not_empty) {
                        swap(*b, *e);
                        if (comp(*b, pivot)) continue;
                    }
                }
                // if current item is equal to pivot, then move "pivots" to this one
                // or if all items are checked, then put "pivots" into right place
                if (pive != b) {
                    RAI bbb = b;
                    do {
                        if (pivb == pive) {pivb = bbb; break;}
                        swap(*pivb, *--bbb);
                        ++pivb;
                    } while (pive != bbb);
                    pive = b;
                }
                pive += still_not_empty;
            } while (still_not_empty);
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

} // namespace version2

//-----------------------------------------------------------------------
//------------------------------ first version --------------------------
//-----------------------------------------------------------------------

namespace version1 {

template <class RAI, class Comp>
void _quick_sort_mine(RAI begin, RAI end, Comp comp)
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
    _quick_sort_mine(begin, pivb, comp);
    _quick_sort_mine(pive, end, comp);
}

} // namespace version1

#undef ORDER
#undef RAI_VALUE_IS_SCALAR
} // namespace sorting
} // namespace algorithms

#endif
