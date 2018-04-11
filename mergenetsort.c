/*
    mergenetsort - A qsort replacement for glibc using sorting networks
    and mergesort
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
*/

#include <stdlib.h>
#include <string.h>

/* Block of all network sort functions we use, up to 10 in the end. Using a
 * very simple min/max swap macro which gets extremely well optimized by gcc.
 * Using the SWAP2 macro from the latest glibc qsort implementation.
 */
#define min(x, y) (compar(x,y)<0?(x):(y))
#define max(x, y) (compar(x,y)<0?(y):(x))
#define SWAP(x,y) { void *a = min(d + x*size, d + y*size); \
                    void *b = max(d + x*size, d + y*size); \
                    if (a != (d + x*size)) { \
                        SWAP2(a, b); \
                    }}
#define SWAP2(c, d)			        			      \
  do									      \
    {									      \
      register size_t __size = (size);					      \
      register char *__a = (c), *__b = (d);				      \
      do								      \
	{								      \
	  char __tmp = *__a;						      \
	  *__a++ = *__b;						      \
	  *__b++ = __tmp;						      \
	} while (--__size > 0);						      \
} while (0)

void netsort2(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(0, 1);
}

void netsort3(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(1, 2);
    SWAP(0, 2);
    SWAP(0, 1);
}

void netsort4(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(0, 1);
    SWAP(2, 3);
    SWAP(0, 2);
    SWAP(1, 3);
    SWAP(1, 2);
}

void netsort5(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(2, 4);
    SWAP(2, 3);
    SWAP(0, 3);
    SWAP(0, 2);
    SWAP(1, 4);
    SWAP(1, 3);
    SWAP(1, 2);
}

void netsort6(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(1, 2);
    SWAP(0, 2);
    SWAP(0, 1);
    SWAP(4, 5);
    SWAP(3, 5);
    SWAP(3, 4);
    SWAP(0, 3);
    SWAP(1, 4);
    SWAP(2, 5);
    SWAP(2, 4);
    SWAP(1, 3);
    SWAP(2, 3);
}

void netsort7(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(1, 2);
    SWAP(0, 2);
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(5, 6);
    SWAP(3, 5);
    SWAP(4, 6);
    SWAP(4, 5);
    SWAP(0, 4);
    SWAP(0, 3);
    SWAP(1, 5);
    SWAP(2, 6);
    SWAP(2, 5);
    SWAP(1, 3);
    SWAP(2, 4);
    SWAP(2, 3);
}

void netsort8(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(0, 1);
    SWAP(2, 3);
    SWAP(0, 2);
    SWAP(1, 3);
    SWAP(1, 2);
    SWAP(4, 5);
    SWAP(6, 7);
    SWAP(4, 6);
    SWAP(5, 7);
    SWAP(5, 6);
    SWAP(0, 4);
    SWAP(1, 5);
    SWAP(1, 4);
    SWAP(2, 6);
    SWAP(3, 7);
    SWAP(3, 6);
    SWAP(2, 4);
    SWAP(3, 5);
    SWAP(3, 4);
}

void netsort9(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(6, 7);
    SWAP(1, 2);
    SWAP(4, 5);
    SWAP(7, 8);
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(6, 7);
    SWAP(0, 3);
    SWAP(3, 6);
    SWAP(0, 3);
    SWAP(1, 4);
    SWAP(4, 7);
    SWAP(1, 4);
    SWAP(2, 5);
    SWAP(5, 8);
    SWAP(2, 5);
    SWAP(1, 3);
    SWAP(5, 7);
    SWAP(2, 6);
    SWAP(4, 6);
    SWAP(2, 4);
    SWAP(2, 3);
    SWAP(5, 6);
}

void netsort10(void *d, size_t size, int (*compar)(const void *, const void *)) {
    SWAP(4, 9);
    SWAP(3, 8);
    SWAP(2, 7);
    SWAP(1, 6);
    SWAP(0, 5);
    SWAP(1, 4);
    SWAP(6, 9);
    SWAP(0, 3);
    SWAP(5, 8);
    SWAP(0, 2);
    SWAP(3, 6);
    SWAP(7, 9);
    SWAP(0, 1);
    SWAP(2, 4);
    SWAP(5, 7);
    SWAP(8, 9);
    SWAP(1, 2);
    SWAP(4, 6);
    SWAP(7, 8);
    SWAP(3, 5);
    SWAP(2, 5);
    SWAP(6, 8);
    SWAP(1, 3);
    SWAP(4, 7);
    SWAP(2, 3);
    SWAP(6, 7);
    SWAP(3, 4);
    SWAP(5, 6);
    SWAP(4, 5);
}

#undef SWAP
#undef SWAP2
#undef min
#undef max

/* Very simple block merge function. Could probably be optimized much more. */
void merge(void *d, void *s1, void *s2, size_t c1, size_t c2, size_t size, int (*compar)(const void *, const void *)) {
    size_t i2 = 0, i1 = 0;

    if (c1 == 0) {
        memcpy(d, s2, size * c2);
        return;
    }

    if (c2 == 0) {
        memcpy(d, s1, size * c1);
        return;
    }

    while(i1 < c1 && i2 < c2) {
        if(compar(s1, s2) < 0) {
            memcpy(d, s1, size);
            s1 += size;
            i1++;
        } else {
            memcpy(d, s2, size);
            s2 += size;
            i2++;
        }
        d += size;
    }

    if (i1 < c1) {
        memcpy(d, s1, size * (c1 - i1));
    }

    if (i2 < c2) {
        memcpy(d, s2, size * (c2 - i2));
    }
}

/* Main sort function. Uses a combination of sorting networks for blocks of up
 * to 10 items and then merge sorts them together with a simple merge sort.
 */
void mergesort(void *d, size_t n, size_t size, int (*compar)(const void *, const void *)) {
    int blocksize = 10;
    int blocks = n / blocksize;
    int rest = n % blocksize;

    /* Sort all blocks of size 10 first plus the last block with the remaining items.
     */
    for (int i = 0; i < blocks; i++) {
        netsort10(d + i * blocksize * size, size, compar);
    }

    /* Sort the last block with less than 10 items. Can be 0 or 1 as well, but
     * obviously thats a no-op.
     */
    switch(rest) {
        case 2:
            netsort2(d + (n - rest) * size, size, compar);
            break;
        case 3:
            netsort3(d + (n - rest) * size, size, compar);
            break;
        case 4:
            netsort4(d + (n - rest) * size, size, compar);
            break;
        case 5:
            netsort5(d + (n - rest) * size, size, compar);
            break;
        case 6:
            netsort6(d + (n - rest) * size, size, compar);
            break;
        case 7:
            netsort7(d + (n - rest) * size, size, compar);
            break;
        case 8:
            netsort8(d + (n - rest) * size, size, compar);
            break;
        case 9:
            netsort9(d + (n - rest) * size, size, compar);
            break;
    }

    /* If we have no blocks that means we had less than 10 items, so
     * we don't need to merge anything and are done.
     */
    if (blocks == 0 ) {
        return;
    }

    /* Swap variables for merging plus a merge storage (not bothering with
    * in place merging).
    */
    void *td1 = d;
    void *td2 = malloc(n * size);

    /* Consecutively merge bigger blocks together, starting with our 10 items
     * big blocks.
     */
    void *s1, *s2, *d1;
    while (blocks > 1) {
        s1 = td1;
        s2 = td1 + blocksize * size;
        d1 = td2;

        /* Start merging the big blocks first */
        for (int i = 0; i < blocks / 2; i++) {
            merge(d1, s1, s2, blocksize, blocksize, size, compar);
            s1 += (2 * blocksize * size);
            s2 += (2 * blocksize * size);
            d1 += (2 * blocksize * size);
        }

        /* In case we have an uneven number of blocks we need to merge the
         * last block with the rest at the end. For even we need to copy the
         * rest (if there is any) to the destination store at the end instead.
         */
        if (blocks % 2 == 1) {
            merge(d1, s1, s2, blocksize, rest, size, compar);
            rest += blocksize;
        } else {
            //printf("Copy Rest form s1[%d-%d]\n", (s1 - td1)/size, (s1 - td1)/size + rest);
            if (rest > 0) {
                memcpy(d1, s1, rest * size);
            }
        }

        s1 = td1;
        td1 = td2;
        td2 = s1;
        blocksize = blocksize * 2;
        blocks = blocks / 2;
    }

    /* And merge the last big block with the remainder of the items */
    s1 = td1;
    s2 = td1 + blocksize * size;
    d1 = td2;
    merge(d1, s1, s2, blocksize, rest, size, compar);

    /* In case we end up with the last merge buffer being our temporary one
     * we need to do one last copy to the original.
     */
    if (td1 == d) {
        memcpy(d, td2, n * size);
        free(td2);
    } else {
        free(td1);
    }
}
