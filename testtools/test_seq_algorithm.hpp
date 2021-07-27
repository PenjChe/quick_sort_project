#ifndef TESTTOOL_SEQUENCES_ALGORITHMS_HPP
#define TESTTOOL_SEQUENCES_ALGORITHMS_HPP

#include <vector>
#include <iostream>

// All template arguments are required
template <typename T, size_t N, class SeqGen, class Algo>
void TestAllSequenceAlgorithms()
{
    std::vector<T> data(N);
    for (unsigned i = 0; i < static_cast<unsigned>(SeqGen::N); ++i)
    {
        SeqGen::run(i, data.begin(), data.end());
        std::cout << "***** " << SeqGen::last_message << '\n';
        for (unsigned j = 0; j < static_cast<unsigned>(Algo::N); ++j)
        {
            Algo::run(j, data.begin(), data.end());
            std::cout << Algo::last_message << '\n';
            SeqGen::run(i, data.begin(), data.end());
        }
        std::cout << std::endl;
    }
}

#endif
