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

## Motivation
Over the past decades many different types of sorting algorithms and methods have been developed,
ranging from classical `bubblesort` over `mergesrort`, `qsort`, `heapsort` up to `timsort` or even
specialized sorting algorithms like `radixsort`.

A very interesting subdomain of search algorithms are the so called sorting networks[1]. They work
on a fixed comparator network that guarantees in as few comparisons as possible to sort an array
of fixed length. They are also especially suited for parallel operation.

The optimal sorting networks know today are as follows:

|n 	|1 	|2 	|3 	|4 	|5 	|6 	|7 	|8 	|9 	|10 	|11 	|12 	|13 	|14 	|15 	|16 	|17     |
|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|Depth 	|0 	|1 	|3 	|3 	|5 	|5 	|6 	|6 	|7 	|7 	|8 	|8 	|9 	|9 	|9 	|9 	|10     |
|Size, upper bound 	|0 	|1 	|3 	|5 	|9 	|12 	|16 	|19 	|25 	|29 	|35 	|39 	|45 	|51 	|56 	|60 	|71    |
|Size, lower bound (if different)	| | | | | | | | | |     |33 	|37 	|41 	|45 	|49 	|53 	|58    |

The sorting network for 10 elements is therefor the largest one where the lower bound for the size
is equal to the 

## Getting Started
In order to use this new sort as a pilot test you can simply copy the `mergenetsort.c` and
`mergenetsort.h` to your project directory and include them in your project and then either
replace all your `qsort()` calls with `mergesort()` or define the following macro in your
main header file:

`#define qsort mergesort`

## Building
To build the test application, simply run a

`make`

from your commandline. This will create a test application called `mergenetsort` which takes one
parameter with the size of the array to be sorted.

## Testing

## Installation

## License

    mergenetsort - A qsort replacement for glibc using sorting networks and mergesort
    Copyright (C) 2018  Philipp Knirsch <philippknirsch@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.


[1] [Sorting Networks Wikipedia](https://en.wikipedia.org/wiki/Sorting_network)
