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

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergenetsort.h"
#include "mergenetsort.c"

u_int64_t state[2];
u_int64_t __rand() {
    u_int64_t x = state[0];
    u_int64_t const y = state[1];
    state[0] = y;
    x ^= x << 23; // a
    state[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return state[1] + y;
}

int int_cmp(const void *a, const void *b)
{
    const int *ia = (const int *)a; // casting pointer types
    const int *ib = (const int *)b;
    return *ia  - *ib;
	/* integer comparison: returns negative if b > a
	and positive if a > b */
}

int main(int argc, char *argv[]) {
    int ELEMS = 1000;
    int LOOP = 100;
    char algo = 'm';

    if (argc > 1) {
        algo = argv[1][0];
    }

    if (argc > 2) {
        ELEMS = atoi(argv[2]);
    }

    if (argc > 3) {
        LOOP = atoi(argv[3]);
    }

    int *t = malloc(sizeof(int) * ELEMS);
    int *v = malloc(sizeof(int) * ELEMS);

    state[0] = 0x87654321;
    for (int i = 0; i < ELEMS; i++) {
        t[i] = (__rand() % ELEMS) + 1;
    }

    for (int i = 0; i < LOOP; i++) {
        memcpy(v, t, ELEMS * sizeof(int));
        if (algo == 'm') {
            mergesort(v, ELEMS, sizeof(int), int_cmp);
        } else {
            qsort(v, ELEMS, sizeof(int), int_cmp);
        }
    }

    for(int i = 0; i < ELEMS; i++) {
        printf("%d\n", v[i]);
    }

    free(v);
    free(t);

    return 0;
}
