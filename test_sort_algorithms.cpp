#include "testtools/test_seq_algorithm.hpp"
#include "datasets/gen_int_sequences.hpp"
#include "testtools/testsort.hpp"

int main(int argc, char ** argv)
{
    TestAllSequenceAlgorithms<int, 1000000, GenIntSeq, SortAlgo>();
    return 0;
}
