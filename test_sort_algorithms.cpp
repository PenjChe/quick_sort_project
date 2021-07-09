#include <iostream>
#include "datasets/gen_int_sequences.hpp"
#include "algorithms/quick_sort_algorithms.hpp"
#include "testtools/testsort.hpp"
#include <vector>


#define VSIZE 1000000


int main(int argc, char ** argv)
{
    using namespace gena;
    TestAllSortAlgorithms("Already sorted",
        int, VSIZE, ints_asc);
    TestAllSortAlgorithms("Duplicates only",
        int, VSIZE, ints_duplicates_only);
    TestAllSortAlgorithms("0 & 1 only",
        int, VSIZE, ints_10);
    TestAllSortAlgorithms("Reversed order",
        int, VSIZE, ints_reversed_order);
    TestAllSortAlgorithms("Almost straight order",
        int, VSIZE, ints_almost_straight_order);
    TestAllSortAlgorithms("First half is reversed, second half is mirrored",
        int, VSIZE, ints_reverse_mirror_straight);
    TestAllSortAlgorithms("First half is straight, second half is mirrored",
        int, VSIZE, ints_straight_mirror_reverse);
    TestAllSortAlgorithms("First half is reversed, second half is straight",
        int, VSIZE, ints_reverse_straight);
    TestAllSortAlgorithms("First half is straight, second half is reversed",
        int, VSIZE, ints_straight_reverse);
    return 0;
}
