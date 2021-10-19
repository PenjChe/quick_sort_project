# QuickSort project
This repository contains my implementation of QuickSort based on the Hoare's algorithm. This is my way of splitting the array into three parts: values that less than pivot, values that equal to pivot, values that greater than pivot. During splitting, unnecessary swaps are avoided, which makes my algorithm adaptive. It does not require to copy the pivot (unless the data type is scalar).

## Details
At short, the sorting algorithm developed by *Charles Hoare* in 1960 contains several simple actions: *select* a 'pivot' item from the array; *split* the array to items that *less* than the pivot and items that *greater* than the pivot; *sort* both parts recursively. The spliting is done using two pointers going toward each other.

Sorting is really fast. However, with all pluses of algorithm, there are minuses. In particular, extra swaps when both pointers stop on items that equal to pivot. If the array contains entirely or mostly of the same items, then there will be a lot of unnecessary work.

In this project, I developed a algorithm that avoids this problem. The splitting process consists of two stages.
1. The *first stage* is like the Hoare's algorithm, two pointers are going toward each other. Items that greater than the pivot are moving to the end of array, lesser items are moving to the beginnig. If a item that equal to the pivot is found, then *second stage* is starting.
2. While the splitting, all found items equal to the pivot are collecting and hold together each iteration. After this splitting into 3 parts, the lesser and greater items are sorting by recursive calls (like Bentley and McIlroy's algorithm).

The test results of (my and Hoare's) algorithms first versions were unsatisfactory. Even Hoare's algorithm produced huge results in some cases, so I optimized it: replace one recursive call with sorting in-place; select the pivot by median of three and put it into the array's center. As for my algorithm, this optimization became the foundation for the new version.

The test results of the latest versions have been impressive. My algorithm is not so slower than Hoare's algorithm but it is faster than `std::sort`. MergeSort is faster than the others thanks to the additional memory. Like all implementations of QuickSort, my algorithm does not require the additional memory.

But that is not all. I optimized my algorithm's final version for working with *scalar* types (integer, floating). By storing the pivot value into a local variable, my algorithm's duration had approached to Hoare's. So I had divided my algorithm's behavior into work with scalar and non-scalar data.

## Testing

[The test results, MCBC, gcc 4.1.3](test_results_mcbc.md)
