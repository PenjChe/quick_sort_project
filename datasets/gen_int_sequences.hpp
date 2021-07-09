#ifndef GENERATION_SEQUENCES_INTEGER_HPP
#define GENERATION_SEQUENCES_INTEGER_HPP

namespace gena {

template <class ITER>
void ints_asc(ITER begin, ITER end)
{
    register int value = 0;
    if (end - begin) return;
    while (begin != end)
    {
        *begin = value++;
        ++begin;
    }
}

template <class ITER>
void ints_duplicates_only(ITER begin, ITER end)
{
    if (end - begin < 1) return;
    while (begin != end)
    {
        *begin = 0;
        ++begin;
    }
}

// [7 6 5 4 3 2 1 0] without duplicates
template <class ITER>
void ints_reversed_order(ITER begin, ITER end)
{
    register int value = (end - begin);
    if (value < 1) return;
    while (begin != end)
    {
        *begin = value--;
        ++begin;
    }
}

// [1 2 3 4 5 6 7 0] without duplicates
template <class ITER>
void ints_almost_straight_order(ITER begin, ITER end)
{
    register int value = (end - begin);
    if (value < 3) return;
    ITER ee = end-1;
    do {
        *--ee = value--;
    } while (begin != ee);
    *(end-1) = value;
}

// [7 6 5 4 4 5 6 7] with duplicates
template <class ITER>
void ints_reverse_mirror_straight(ITER begin, ITER end)
{
    register int value = (end - begin);
    if (value < 2) return;
    do {
        *begin = value;
        if (++begin == end) break;
        *--end = value--;
    } while (begin != end);
}

// [0 1 2 3 3 2 1 0] with duplicates
template <class ITER>
void ints_straight_mirror_reverse(ITER begin, ITER end)
{
    if (end - begin < 2) return;
    register int value = 0;
    do {
        *begin = value;
        if (++begin == end) break;
        *--end = value++;
    } while (begin != end);
}

// [7 5 3 1 0 2 4 6] without duplicates
template <class ITER>
void ints_reverse_straight(ITER begin, ITER end)
{
    register int value = (end - begin);
    if (value < 2) return;
    do {
        *begin = value--;
        if (++begin == end) break;
        *--end = value--;
    } while (begin != end);
}

// [0 2 4 6 7 5 3 1] without duplicates
template <class ITER>
void ints_straight_reverse(ITER begin, ITER end)
{
    if (end - begin < 2) return;
    register int value = 0;
    do {
        *begin = value++;
        if (++begin == end) break;
        *--end = value++;
    } while (begin != end);
}

// only '0' and '1'
template <class ITER>
void ints_10(ITER begin, ITER end)
{
    const int sz = (end - begin);
    if (sz < 2) return;
    register int value = 0;
    do {
        *begin = value & 1;
        ++begin;
    } while (++value < (sz>>1));
    while (value < sz) {
        *begin = (value++ & 2) >> 1;
        ++begin;
    }
}

} // namespace

#endif
