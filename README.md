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

A very interesting subdomain of search algorithms are the so called sorting networks[footnote1].
They work on a fixed comparator network that guarantees in as few comparisons as possible to sort
an array of fixed length. They are also especially suited for parallel operation.

The interesting part is that, at lestt for smaller sorting networks up to a size of 10 elements
you can construct a networks that use significantly less comparisons than the best known general
purpose sorting algorithms.

The optimal sorting networks known today are as follows:

|n 	|1 	|2 	|3 	|4 	|5 	|6 	|7 	|8 	|9 	|10 	|11 	|12 	|13 	|14 	|15 	|16 	|17     |
|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|Depth 	|0 	|1 	|3 	|3 	|5 	|5 	|6 	|6 	|7 	|7 	|8 	|8 	|9 	|9 	|9 	|9 	|10     |
|Size, upper bound 	|0 	|1 	|3 	|5 	|9 	|12 	|16 	|19 	|25 	|29 	|35 	|39 	|45 	|51 	|56 	|60 	|71    |
|Size, lower bound (if different)	| | | | | | | | | |     |33 	|37 	|41 	|45 	|49 	|53 	|58    |

The sorting network for 10 elements is therefor the largest one where the lower bound for the size
is equal to the upper bound, which makes it size optimal.

In the mergenetsort i use the sorting network of size 10 to do one intial pass over the whole
array and sort it in blocks of size 10. After that, one could use any sorting algorithm to merge
those blocks, but i chose to use mergesort as an obvious choice as i already had lots of presorted
blocks now. Most likely using `timsort`[2] would have been even better, especially as `timsort` is
designed to benefit from runs of ascending or decending elements.

## Building
To build the test application, simply run a

`make`

from your commandline. This will create a test application called `mergenetsort` which you can
use to run some test.

## Testing
In order to test the algorithm, especially against the original `qosrt()` you can use the
`mergenetsort` application you get when you build the project.

The `mergenetsort` application has 3 parameters: `./mergenetsort [algorithm=[m|q]] [arraysize] [loops]`

The `algorithm` parameter specifies whether you want to run a test using `**m**ergenetsort` or
`**q**sort`. Default is `m`.
The `arraysize` parameter allows you to specify the number of random elements that should be
generated. Default is `1000`.
The `loops` parameter lets you change the number of times the random array will be sorted.
Default is 100.

The output is the sorted array, one element each line. This way you can easily compare outputs for
both algorithms and different arraysizes or redirect the output to `/dev/null` and do runtime
tests via `time` or `perf stat`.

I've also included two Makefile targets for testing and benchmarking:

`make test` will run a few different sizes for both algorithms and compare the results.
`make bench` will run a benchmark test for a larger array size for both algorithms either using
time or, if installed, perf.

## Installation
In order to use this new sort as a pilot test you can simply copy the `mergenetsort.c` and
`mergenetsort.h` to your project directory and include them in your project and then either
replace all your `qsort()` calls with `mergesort()` or define the following macro in your
main header file:

`#define qsort mergesort`

## Benchmarks
### Testsetup:
- CPU: Intel(R) Core(TM)2 Duo CPU     E7500  @ 2.93GHz
- 4 GB Ram
- Fedora 26 x86_64

### Testresults
```
Perf stat for mergenetsort for 100 x 1000000 elements:

 Performance counter stats for './mergenetsort m 1000000':

      10809.182741      task-clock:u (msec)       #    0.999 CPUs utilized
                 0      context-switches:u        #    0.000 K/sec
                 0      cpu-migrations:u          #    0.000 K/sec
             3,953      page-faults:u             #    0.366 K/sec
    31,059,515,392      cycles:u                  #    2.873 GHz                      (50.00%)
    25,477,297,166      instructions:u            #    0.82  insn per cycle           (75.00%)
     4,000,563,161      branches:u                #  370.108 M/sec                    (75.00%)
       958,532,028      branch-misses:u           #   23.96% of all branches          (75.00%)

      10.825215961 seconds time elapsed

Perf stat for qsort for 100 x 1000000 elements:

 Performance counter stats for './mergenetsort q 1000000':

      14428.304055      task-clock:u (msec)       #    0.999 CPUs utilized
                 0      context-switches:u        #    0.000 K/sec
                 0      cpu-migrations:u          #    0.000 K/sec
             3,953      page-faults:u             #    0.274 K/sec
    41,617,295,076      cycles:u                  #    2.884 GHz                      (50.01%)
    39,691,492,367      instructions:u            #    0.95  insn per cycle           (75.00%)
     9,177,729,011      branches:u                #  636.092 M/sec                    (75.00%)
     1,041,465,679      branch-misses:u           #   11.35% of all branches          (75.00%)

      14.442013111 seconds time elapsed
```

## Future outlook/TODO
- Optimize the `mergesort()` and `merge()` functions
- Investigate in-place `mergesort` algorithms
- Look into using `timsort` as a replacement for the `mergesort`

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


<a name="footnote1"> [Sorting Networks Wikipedia](https://en.wikipedia.org/wiki/Sorting_network)
