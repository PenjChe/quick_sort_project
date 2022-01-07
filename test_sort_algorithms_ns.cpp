#include "testtools/test_seq_algorithm.hpp"
#include "datasets/gen_point_sequences.hpp"
#include "testtools/testsort.hpp"

int main(int argc, char ** argv)
{
    TestAllSequenceAlgorithms<Point, 1000000, GenPointSeq, SortAlgo>();
    return 0;
}
