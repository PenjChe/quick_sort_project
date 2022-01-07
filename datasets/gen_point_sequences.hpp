#ifndef GENERATION_SEQUENCES_POINT_HPP
#define GENERATION_SEQUENCES_POINT_HPP

#include <string>

struct Point
{
    double x,y;
};

inline bool operator< (const Point &a, const Point &b)
{
    return a.x < b.x ||
        (!(b.x < a.x) && a.y < b.y);
}
inline bool operator> (const Point &a, const Point &b)
{
    return b < a;
}

void swap(Point &a, Point &b)
{
    register double
    tmp = a.x;
    a.x = b.x;
    b.x = tmp;
    tmp = a.y;
    a.y = b.y;
    b.y = tmp;
}


struct GenPointSeq
{
    enum {
        P_DUPLICATES = 0,
        P_10,
        P_ASC_X,
        P_ASC_Y,
        P_DESC_X,
        P_DESC_Y,
        P_ROTATED_X,
        P_ROTATED_Y,
        P_BITONIC1_X,
        P_BITONIC1_Y,
        P_BITONIC2_X,
        P_BITONIC2_Y,
        P_BITONIC3_X,
        P_BITONIC3_Y,
        P_BITONIC4_X,
        P_BITONIC4_Y,
        N
    };

    static std::string last_message;

    template <class RAI>
    static void run(unsigned n, RAI begin, RAI end)
    {
        const int sz = (end - begin);
        if (sz < 2) return;
        switch(n)
        {
        default:
        case P_DUPLICATES:
            while (begin != end)
            {
                begin->x = begin->y = 0.0;
                ++begin;
            }
            last_message = "Duplicates only";
            break;
        case P_10: // only '0' and '1'
            {
              register int value = 0;
              do {
                begin->x = begin->y = double(value & 1);
                ++begin;
              } while (++value < (sz>>1));
              while (value < sz) {
                begin->x = begin->y = double((value++ & 2) >> 1);
                ++begin;
              }
            }
            last_message = "0 & 1 only";
            break;
        case P_ASC_X: // y = 0, x = [0 1 2 3 4 5 6 7] without duplicates
            {
              register double value = 0;
              while (begin != end)
              {
                begin->x = value++;
                begin->y = 0.0;
                ++begin;
              }
            }
            last_message = "Already sorted (x)";
            break;
        case P_ASC_Y: // x = 0, y = [0 1 2 3 4 5 6 7] without duplicates
            {
              register double value = 0;
              while (begin != end)
              {
                begin->x = 0.0;
                begin->y = value++;
                ++begin;
              }
            }
            last_message = "Already sorted (y)";
            break;
        case P_DESC_X: // y = 0, x = [7 6 5 4 3 2 1 0] without duplicates
            {
              register double value = double(sz);
              while (begin != end)
              {
                begin->x = --value;
                begin->y = 0.0;
                ++begin;
              }
            }
            last_message = "Reversed order (x)";
            break;
        case P_DESC_Y: // x = 0, y = [7 6 5 4 3 2 1 0] without duplicates
            {
              register double value = double(sz);
              while (begin != end)
              {
                begin->x = 0.0;
                begin->y = --value;
                ++begin;
              }
            }
            last_message = "Reversed order (y)";
            break;
        case P_ROTATED_X: // y = 0, x = [1 2 3 4 5 6 7 0] without duplicates
            {
              register double value = 0.0;
              --end;
              end->x = end->y = 0.0;
              while (begin != end)
              {
                begin->x = ++value;
                begin->y = 0.0;
                ++begin;
              }
            }
            last_message = "Almost straight order (x)";
            break;
        case P_ROTATED_Y: // x = 0, y = [1 2 3 4 5 6 7 0] without duplicates
            {
              register double value = 0.0;
              --end;
              end->x = end->y = 0.0;
              while (begin != end)
              {
                begin->x = 0.0;
                begin->y = ++value;
                ++begin;
              }
            }
            last_message = "Almost straight order (y)";
            break;
        case P_BITONIC1_X: // y = 0, x = [7 6 5 4 4 5 6 7] with duplicates
            {
              register double value = double(sz);
              do {
                begin->x = --value;
                begin->y = 0.0;
                if (++begin == end) break;
                --end;
                end->x = value;
                end->y = 0.0;
              } while (begin != end);
            }
            last_message = "First half is reversed, second half is mirrored (x)";
            break;
        case P_BITONIC1_Y: // x = 0, y = [7 6 5 4 4 5 6 7] with duplicates
            {
              register double value = double(sz);
              do {
                begin->x = 0.0;
                begin->y = --value;
                if (++begin == end) break;
                --end;
                end->x = 0.0;
                end->y = value;
              } while (begin != end);
            }
            last_message = "First half is reversed, second half is mirrored (y)";
            break;
        case P_BITONIC2_X: // y = 0, x = [0 1 2 3 3 2 1 0] with duplicates
            {
              register double value = 0;
              do {
                begin->x = value;
                begin->y = 0.0;
                if (++begin == end) break;
                --end;
                end->x = value++;
                end->y = 0.0;
              } while (begin != end);
            }
            last_message = "First half is straight, second half is mirrored (x)";
            break;
        case P_BITONIC2_Y: // x = 0, y = [0 1 2 3 3 2 1 0] with duplicates
            {
              register double value = 0;
              do {
                begin->x = 0.0;
                begin->y = value;
                if (++begin == end) break;
                --end;
                end->x = 0.0;
                end->y = value++;
              } while (begin != end);
            }
            last_message = "First half is straight, second half is mirrored (y)";
            break;
        case P_BITONIC3_X: // y = 0, x = [7 5 3 1 0 2 4 6] without duplicates
            {
              register double value = double(sz);
              do {
                begin->x = --value;
                begin->y = 0.0;
                if (++begin == end) break;
                --end;
                end->x = --value;
                end->y = 0.0;
              } while (begin != end);
            }
            last_message = "First half is reversed, second half is straight (x)";
            break;
        case P_BITONIC3_Y: // x = 0, y = [7 5 3 1 0 2 4 6] without duplicates
            {
              register double value = double(sz);
              do {
                begin->x = 0.0;
                begin->y = --value;
                if (++begin == end) break;
                --end;
                end->x = 0.0;
                end->y = --value;
              } while (begin != end);
            }
            last_message = "First half is reversed, second half is straight (y)";
            break;
        case P_BITONIC4_X: // y = 0, x = [0 2 4 6 7 5 3 1] without duplicates
            {
              register double value = 0;
              do {
                begin->x = value++;
                begin->y = 0.0;
                if (++begin == end) break;
                --end;
                end->x = value++;
                end->y = 0.0;
              } while (begin != end);
            }
            last_message = "First half is straight, second half is reversed (x)";
            break;
        case P_BITONIC4_Y: // x = 0, y = [0 2 4 6 7 5 3 1] without duplicates
            {
              register double value = 0;
              do {
                begin->x = 0.0;
                begin->y = value++;
                if (++begin == end) break;
                --end;
                end->x = 0.0;
                end->y = value++;
              } while (begin != end);
            }
            last_message = "First half is straight, second half is reversed (y)";
            break;
        }
    }
};

std::string GenPointSeq::last_message;

#endif
