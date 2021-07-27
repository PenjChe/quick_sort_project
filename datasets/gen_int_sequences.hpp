#ifndef GENERATION_SEQUENCES_INTEGER_HPP
#define GENERATION_SEQUENCES_INTEGER_HPP

#include <string>

struct GenIntSeq
{
    enum {
        I_ASC = 0,
        I_DUPLICATES,
        I_10,
        I_DESC,
        I_ROTATED,
        I_BITONIC1,
        I_BITONIC2,
        I_BITONIC3,
        I_BITONIC4,
        N
    };

    static std::string last_message;

    template <class RAI>
    static void run(unsigned n, RAI begin, RAI end)
    {
        const int sz = (end - begin);
        register int value = 0;
        if (sz < 2) return;
        switch(n)
        {
        default:
        case I_ASC: // [0 1 2 3 4 5 6 7] without duplicates
            while (begin != end)
            {
                *begin = value++;
                ++begin;
            }
            last_message = "Already sorted";
            break;
        case I_DUPLICATES:
            while (begin != end)
            {
                *begin = 0;
                ++begin;
            }
            last_message = "Duplicates only";
            break;
        case I_10: // only '0' and '1'
            do {
                *begin = value & 1;
                ++begin;
            } while (++value < (sz>>1));
            while (value < sz) {
                *begin = (value++ & 2) >> 1;
                ++begin;
            }
            last_message = "0 & 1 only";
            break;
        case I_DESC: // [7 6 5 4 3 2 1 0] without duplicates
            value = sz;
            while (begin != end)
            {
                *begin = --value;
                ++begin;
            }
            last_message = "Reversed order";
            break;
        case I_ROTATED: // [1 2 3 4 5 6 7 0] without duplicates
            *--end = value++;
            while (begin != end)
            {
                *begin = value++;
                ++begin;
            }
            last_message = "Almost straight order";
            break;
        case I_BITONIC1: // [7 6 5 4 4 5 6 7] with duplicates
            value = sz;
            do {
                *begin = --value;
                if (++begin == end) break;
                *--end = value;
            } while (begin != end);
            last_message = "First half is reversed, second half is mirrored";
            break;
        case I_BITONIC2: // [0 1 2 3 3 2 1 0] with duplicates
            do {
                *begin = value;
                if (++begin == end) break;
                *--end = value++;
            } while (begin != end);
            last_message = "First half is straight, second half is mirrored";
            break;
        case I_BITONIC3: // [7 5 3 1 0 2 4 6] without duplicates
            value = sz;
            do {
                *begin = --value;
                if (++begin == end) break;
                *--end = --value;
            } while (begin != end);
            last_message = "First half is reversed, second half is straight";
            break;
        case I_BITONIC4: // [0 2 4 6 7 5 3 1] without duplicates
            do {
                *begin = value++;
                if (++begin == end) break;
                *--end = value++;
            } while (begin != end);
            last_message = "First half is straight, second half is reversed";
            break;
        }
    }
};

std::string GenIntSeq::last_message;

#endif
