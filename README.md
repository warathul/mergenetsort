# mergenetsort
A glibc qsort replacement based on a combination of sorting networks and mergesort.

The idea was to use the largest know size optimal sorting networks which is currently 10 as a
first pass over the array and then use a merge sort as a 2nd stage to iteratively merge all blocks
until we reach a fully sorted array.

The API is exactly the same as for `qsort()` in glibc, so it can be directly used as a 1:1
replacement.

Initial performance measurements i've done show the new algorithm to be about 40% faster than
the original `qsort()` in glibc.

One downside currently though is that the implemented version of mergesort is not an in-place
variant, so a temporary storage is allocated during sort with the size of the original array.

## Getting Started
In order to use this new sort as a pilot test you can simply copy the `mergenetsort.c` and
`mergenetsort.h` to your project directory and include them in your project and then either
replace all your `qsort()` calls with `mergesort()` or define the following macro in your
main header file:

`#define qsort mergesort`


